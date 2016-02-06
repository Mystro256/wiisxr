/***************************************************************************
 *                          gpu.c  -  description
 *                             -------------------
 *    begin                : Fri Feb 5 2016
 *    copyright            : (C) 2016 Jeremy Newton
 *
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version. See also the license.txt file for *
 *   additional informations.                                              *
 *                                                                         *
 ***************************************************************************/

//TODO These are variables are "stubbed"
//TODO Delete these after implementation
int iUseDither = 0;
unsigned long dwCoreFlags = 0;
int iResX = 640;
int iResY = 480;
int UseFrameLimit = 1;
int UseFrameSkip = 1;
float fFrameRate = 60.0f;
int iFrameLimit = 2;
unsigned long dwCfgFixes = 0;
int iUseFixes = 0;

//TODO WIP, lots of stubbed functions

#include "stdafx.h"

#include "../Gamecube/DEBUG.h"
#include "../Gamecube/wiiSXconfig.h"

#define _IN_GPU

#include "externals.h"
//#include "gpu.h"
//#include "draw.h"
//#include "cfg.h"
//#include "prim.h"
#include "psemu.h"
//#include "menu.h"
//#include "key.h"
//#include "fps.h"

////////////////////////////////////////////////////////////////////////
// PPDK developer must change libraryName field and can change revision and build
////////////////////////////////////////////////////////////////////////

const unsigned char version = 1;    // do not touch - library for PSEmu 1.x
const unsigned char revision = 1;
const unsigned char build = 0;

static char *libraryName = "P.E.Op.S. GX Driver";
static char *libraryInfo =
		"P.E.Op.S. GX Driver V1.0\nCoded by Jeremy Newton, based on code from Pete Bernert and the P.E.Op.S. team\n";

static char *PluginAuthor =
		"Jeremy Newton, Pete Bernert, and the P.E.Op.S. team";

////////////////////////////////////////////////////////////////////////
// memory image of the PSX vram
////////////////////////////////////////////////////////////////////////

unsigned char psxVSecure[(iGPUHeight * 2) * 1024 + (1024 * 1024)];
unsigned char *psxVub;
signed char *psxVsb;
unsigned short *psxVuw;
unsigned short *psxVuw_eom;
signed short *psxVsw;
unsigned long *psxVul;
signed long *psxVsl;

////////////////////////////////////////////////////////////////////////
// GPU globals
////////////////////////////////////////////////////////////////////////

static long lGPUdataRet;
long lGPUstatusRet;
char szDispBuf[64];
char szDebugText[512];
unsigned long ulStatusControl[256];

static unsigned long gpuDataM[256];
static unsigned char gpuCommand = 0;
static long gpuDataC = 0;
static long gpuDataP = 0;

VRAMLoad_t VRAMWrite;
VRAMLoad_t VRAMRead;
DATAREGISTERMODES DataWriteMode;
DATAREGISTERMODES DataReadMode;

BOOL bSkipNextFrame = FALSE;

short sDispWidths[8] = { 256, 320, 512, 640, 368, 384, 512, 640 };

PSXDisplay_t PSXDisplay;
PSXDisplay_t PreviousPSXDisplay;
long lSelectedSlot = 0;
unsigned long lGPUInfoVals[16];
int iFakePrimBusy = 0;
int iRumbleVal = 0;
int iRumbleTime = 0;

////////////////////////////////////////////////////////////////////////
// some misc external display funcs
////////////////////////////////////////////////////////////////////////

#include <time.h>
time_t tStart;

void PEOPS_GPUdisplayText(char * pText)             // some debug func
{
	if (!pText) {
		szDebugText[0] = 0;
		return;
	}
	if (strlen(pText) > 511)
		return;
	time(&tStart);
	strcpy(szDebugText, pText);
}

////////////////////////////////////////////////////////////////////////

void CALLBACK GPUdisplayFlags(unsigned long dwFlags)   // some info func
{
	dwCoreFlags = dwFlags;
	BuildDispMenu(0);
}

////////////////////////////////////////////////////////////////////////
// stuff to make this a true PDK module
////////////////////////////////////////////////////////////////////////

char * CALLBACK PSEgetLibName(void) {
	return libraryName;
}

unsigned long CALLBACK PSEgetLibType(void) {
	return PSE_LT_GPU;
}

unsigned long CALLBACK PSEgetLibVersion(void) {
	return version << 16 | revision << 8 | build;
}

char * GPUgetLibInfos(void) {
	return libraryInfo;
}

////////////////////////////////////////////////////////////////////////
// Snapshot func
////////////////////////////////////////////////////////////////////////

char * pGetConfigInfos(void) {
	char szO[2][4] = { "off", "on " };
	char szTxt[256];
	char * pB = (char *) malloc(32767);

	if (!pB)
		return NULL;
	*pB = 0;
	//----------------------------------------------------//
	sprintf(szTxt, "Plugin: %s %d.%d.%d\r\n", libraryName, version, revision,
			build);
	strcat(pB, szTxt);
	sprintf(szTxt, "Author: %s\r\n\r\n", PluginAuthor);
	strcat(pB, szTxt);
	//----------------------------------------------------//
	sprintf(szTxt, "Resolution/Color:\r\n- %dx%d ", iResX, iResY);
	strcat(pB, szTxt);
	strcpy(szTxt, "Window mode\r\n");
	strcat(pB, szTxt);

	sprintf(szTxt, "Dither mode: %d\r\n\r\n", iUseDither);
	strcat(pB, szTxt);
	//----------------------------------------------------//
	sprintf(szTxt, "Framerate:\r\n- FPS limit: %s\r\n", szO[UseFrameLimit]);
	strcat(pB, szTxt);
	sprintf(szTxt, "- Frame skipping: %s", szO[UseFrameSkip]);
	strcat(pB, szTxt);
	strcat(pB, "\r\n");
	if (iFrameLimit == 2)
		strcpy(szTxt, "- FPS limit: Auto\r\n\r\n");
	else
		sprintf(szTxt, "- FPS limit: %.1f\r\n\r\n", fFrameRate);
	strcat(pB, szTxt);
	//----------------------------------------------------//
	sprintf(szTxt, "Misc:\r\n- Game fixes: %s [%08lx]\r\n", szO[iUseFixes], dwCfgFixes);
	strcat(pB, szTxt);
	//----------------------------------------------------//
	return pB;
}

void DoTextSnapShot(int iNum) {
	FILE *txtfile;
	char szTxt[256];
	char * pB;

	sprintf(szTxt, "%s/peopssoft%03d.txt", getenv("HOME"), iNum);

	if ((txtfile = fopen(szTxt, "wb")) == NULL)
		return;
	//----------------------------------------------------//
	pB = pGetConfigInfos();
	if (pB) {
		fwrite(pB, strlen(pB), 1, txtfile);
		free(pB);
	}
	fclose(txtfile);
}

////////////////////////////////////////////////////////////////////////

void CALLBACK GPUmakeSnapshot(void)                    // snapshot of whole vram
{
	FILE *bmpfile;
	char filename[256];
	unsigned char header[0x36];
	long size, height;
	unsigned char line[1024 * 3];
	short i, j;
	unsigned char empty[2] = { 0, 0 };
	unsigned short color;
	unsigned long snapshotnr = 0;

	height = iGPUHeight;

	size = height * 1024 * 3 + 0x38;

	// fill in proper values for BMP

	// hardcoded BMP header
	memset(header, 0, 0x36);
	header[0] = 'B';
	header[1] = 'M';
	header[2] = size & 0xff;
	header[3] = (size >> 8) & 0xff;
	header[4] = (size >> 16) & 0xff;
	header[5] = (size >> 24) & 0xff;
	header[0x0a] = 0x36;
	header[0x0e] = 0x28;
	header[0x12] = 1024 % 256;
	header[0x13] = 1024 / 256;
	header[0x16] = height % 256;
	header[0x17] = height / 256;
	header[0x1a] = 0x01;
	header[0x1c] = 0x18;
	header[0x26] = 0x12;
	header[0x27] = 0x0B;
	header[0x2A] = 0x12;
	header[0x2B] = 0x0B;

	// increment snapshot value & try to get filename
	do {
		snapshotnr++;
		sprintf(filename, "%s/peopsgx%03ld.bmp", getenv("HOME"), snapshotnr);

		bmpfile = fopen(filename, "rb");
		if (bmpfile == NULL)
			break;
		fclose(bmpfile);
	} while (TRUE);

	// try opening new snapshot file
	if ((bmpfile = fopen(filename, "wb")) == NULL)
		return;

	fwrite(header, 0x36, 1, bmpfile);
	for (i = height - 1; i >= 0; i--) {
		for (j = 0; j < 1024; j++) {
			color = psxVuw[i * 1024 + j];
			line[j * 3 + 2] = (color << 3) & 0xf1;
			line[j * 3 + 1] = (color >> 2) & 0xf1;
			line[j * 3 + 0] = (color >> 7) & 0xf1;
		}
		fwrite(line, 1024 * 3, 1, bmpfile);
	}
	fwrite(empty, 0x2, 1, bmpfile);
	fclose(bmpfile);

	DoTextSnapShot(snapshotnr);
}

////////////////////////////////////////////////////////////////////////
// GPU Init, init for vars and whatnot
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUinit() {
	memset(ulStatusControl, 0, 256 * sizeof(unsigned long)); // init save state scontrol field

	szDebugText[0] = 0;                                // init debug text buffer

	//!!! ATTENTION !!!
	psxVub = psxVSecure + 512 * 1024; // security offset into double sized psx vram!

	psxVsb = (signed char *) psxVub;     // different ways of accessing PSX VRAM
	psxVsw = (signed short *) psxVub;
	psxVsl = (signed long *) psxVub;
	psxVuw = (unsigned short *) psxVub;
	psxVul = (unsigned long *) psxVub;

	psxVuw_eom = psxVuw + 1024 * iGPUHeight;          // pre-calc of end of vram

	memset(psxVSecure, 0x00, (iGPUHeight * 2) * 1024 + (1024 * 1024));
	memset(lGPUInfoVals, 0x00, 16 * sizeof(unsigned long));

	//TODO
	//SetFPSHandler();

	PSXDisplay.RGB24 = FALSE;                      // init some stuff
	PSXDisplay.Interlaced = FALSE;
	PSXDisplay.DrawOffset.x = 0;
	PSXDisplay.DrawOffset.y = 0;
	PSXDisplay.DisplayMode.x = 320;
	PSXDisplay.DisplayMode.y = 240;

	PSXDisplay.Disabled = FALSE;
	PreviousPSXDisplay.Range.x0 = 0;
	PreviousPSXDisplay.Range.y0 = 0;
	PSXDisplay.Range.x0 = 0;
	PSXDisplay.Range.x1 = 0;
	PreviousPSXDisplay.DisplayModeNew.y = 0;
	PSXDisplay.Double = 1;
	lGPUdataRet = 0x400;

	DataWriteMode = DR_NORMAL;

	// Reset transfer values, to prevent mis-transfer of data
	memset(&VRAMWrite, 0, sizeof(VRAMLoad_t));
	memset(&VRAMRead, 0, sizeof(VRAMLoad_t));

	// device initialised already !
	lGPUstatusRet = 0x14802000;
	GPUIsIdle;
	GPUIsReadyForCommands;

	return 0;
}

////////////////////////////////////////////////////////////////////////
// Open GPU, start
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUopen(unsigned long * disp, char * CapText, char * CfgFile) {
	//TODO STUB
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Close GPU, ending and cleanup
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUclose() {
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Shutdown GPU, likely abrupt or on error/fault
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUshutdown() {
	//TODO STUB
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Update Lace, called every VSync
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUupdateLace(void) {
	//TODO STUB
}

////////////////////////////////////////////////////////////////////////
// Read Request, process request from GPU status register
////////////////////////////////////////////////////////////////////////

unsigned long PEOPS_GPUreadStatus(void) {
	return 0; //TODO STUB lGPUstatusRet;
}

////////////////////////////////////////////////////////////////////////
// Write data to GPU status register
// These should be single packet commands.
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUwriteStatus(unsigned long gdata) {
	//TODO STUB
}

////////////////////////////////////////////////////////////////////////
// Read core data from vram
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUreadDataMem(unsigned long * pMem, int iSize) {
	//TODO STUB
}

////////////////////////////////////////////////////////////////////////

unsigned long PEOPS_GPUreadData(void) {
	//TODO STUB
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Write core data to vram
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUwriteDataMem(unsigned long * pMem, int iSize) {
	//TODO STUB
}

////////////////////////////////////////////////////////////////////////

void PEOPS_GPUwriteData(unsigned long gdata) {
	PEOPS_GPUwriteDataMem(&gdata, 1);
}

////////////////////////////////////////////////////////////////////////
// Unsure what this does
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUdmaChain(unsigned long * baseAddrL, unsigned long addr) {
	//TODO STUB
	return 0;
}

////////////////////////////////////////////////////////////////////////
// GPU Freeze save state functions (taken from PeopsSoftGPU)
////////////////////////////////////////////////////////////////////////

typedef struct GPUFREEZETAG {
	unsigned long ulFreezeVersion; // should be always 1 for now (set by main emu)
	unsigned long ulStatus;             // current gpu status
	unsigned long ulControl[256];       // latest control register values
//unsigned char psxVRam[1024*1024*2]; // current VRam image (full 2 MB for ZN)
} GPUFreeze_t;

////////////////////////////////////////////////////////////////////////
// Freeze GPU
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUfreeze(unsigned long ulGetFreezeData, GPUFreeze_t * pF) {
	//TODO STUB
	return 0;
}

////////////////////////////////////////////////////////////////////////
// Unsure what this does
////////////////////////////////////////////////////////////////////////

void CALLBACK GPUsetframelimit(unsigned long option) {
	//TODO STUB
}
