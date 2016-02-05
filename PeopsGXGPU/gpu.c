/***************************************************************************
                          gpu.c  -  description
                             -------------------
    begin                : Fri Feb 5 2016
    copyright            : (C) 2016 Jeremy Newton

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

//TODO This whole file is just a stub to act as a starting point

//These are the only two variables actually passed back
int iUseDither = 0;
unsigned char  * psxVub;
//All the following functions are all the functions that are passed back

////////////////////////////////////////////////////////////////////////
// Display Text, such as debug
////////////////////////////////////////////////////////////////////////
 
void PEOPS_GPUdisplayText(char * pText)
{
 //TODO STUB
}

////////////////////////////////////////////////////////////////////////
// GPU Init, init for vars and whatnot
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUinit()
{
 //TODO STUB
 return 0;
}

////////////////////////////////////////////////////////////////////////
// Open GPU, start
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUopen(unsigned long * disp,char * CapText,char * CfgFile)
{
 //TODO STUB
 return 0;
}

////////////////////////////////////////////////////////////////////////
// Close GPU, ending and cleanup
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUclose()
{
 return 0;
}

////////////////////////////////////////////////////////////////////////
// Shutdown GPU, likely abrupt or on error/fault
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUshutdown()
{
  //TODO STUB
 return 0;
}

////////////////////////////////////////////////////////////////////////
// Update Lace, called every VSync
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUupdateLace(void)
{
 //TODO STUB
}

////////////////////////////////////////////////////////////////////////
// Read Request, process request from GPU status register
////////////////////////////////////////////////////////////////////////

unsigned long PEOPS_GPUreadStatus(void)
{
 return 0;//TODO STUB lGPUstatusRet;
}

////////////////////////////////////////////////////////////////////////
// Write data to GPU status register
// These should be single packet commands.
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUwriteStatus(unsigned long gdata)
{
  //TODO STUB
}

////////////////////////////////////////////////////////////////////////
// Read core data from vram
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUreadDataMem(unsigned long * pMem, int iSize)
{
  //TODO STUB
}

////////////////////////////////////////////////////////////////////////

unsigned long PEOPS_GPUreadData(void)
{
 //TODO STUB
 return 0;
}

////////////////////////////////////////////////////////////////////////
// Write core data to vram
////////////////////////////////////////////////////////////////////////

void PEOPS_GPUwriteDataMem(unsigned long * pMem, int iSize)
{
  //TODO STUB
}

////////////////////////////////////////////////////////////////////////

void PEOPS_GPUwriteData(unsigned long gdata)
{
 PEOPS_GPUwriteDataMem(&gdata,1);
}

////////////////////////////////////////////////////////////////////////
// Unsure what this does
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUdmaChain(unsigned long * baseAddrL, unsigned long addr)
{
  //TODO STUB
  return 0;
}

////////////////////////////////////////////////////////////////////////
// GPU Freeze save state functions (taken from PeopsSoftGPU)
////////////////////////////////////////////////////////////////////////

typedef struct GPUFREEZETAG
{
 unsigned long ulFreezeVersion;      // should be always 1 for now (set by main emu)
 unsigned long ulStatus;             // current gpu status
 unsigned long ulControl[256];       // latest control register values
 //unsigned char psxVRam[1024*1024*2]; // current VRam image (full 2 MB for ZN)
} GPUFreeze_t;

////////////////////////////////////////////////////////////////////////
// Freeze GPU
////////////////////////////////////////////////////////////////////////

long PEOPS_GPUfreeze(unsigned long ulGetFreezeData, GPUFreeze_t * pF)
{
  //TODO STUB
 return 0;
}

////////////////////////////////////////////////////////////////////////
// Unsure what this does
////////////////////////////////////////////////////////////////////////

void GPUsetframelimit(unsigned long option)
{
  //TODO STUB
}