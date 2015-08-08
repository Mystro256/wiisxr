/***************************************************************************
                            cfg.c  -  description
                             -------------------
    begin                : Wed May 15 2002
    copyright            : (C) 2002 by Pete Bernert
    email                : BlackDove@addcom.de
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

//*************************************************************************//
// History of changes:
//
// 2003/06/07 - Pete
// - added Linux NOTHREADLIB define
//
// 2003/02/28 - Pete
// - added option for kode54's interpolation and linuzappz's mono mode
//
// 2003/01/19 - Pete
// - added Neill's reverb
//
// 2002/08/04 - Pete
// - small linux bug fix: now the cfg file can be in the main emu directory as well
//
// 2002/06/08 - linuzappz
// - Added combo str for SPUasync, and MAXMODE is now defined as 2
//
// 2002/05/15 - Pete
// - generic cleanup for the Peops release
//
//*************************************************************************//

#include "stdafx.h"

#define _IN_CFG

#include "externals.h"

extern int iZincEmu;

////////////////////////////////////////////////////////////////////////
// LINUX CONFIG/ABOUT HANDLING
////////////////////////////////////////////////////////////////////////
            
char * pConfigFile=NULL;

#include <unistd.h>

////////////////////////////////////////////////////////////////////////
// START EXTERNAL CFG TOOL
////////////////////////////////////////////////////////////////////////

void StartCfgTool(char * pCmdLine)
{
 FILE * cf;char filename[255],t[255];

 strcpy(filename,"cfg/cfgPeopsOSS");
 cf=fopen(filename,"rb");
 if(cf!=NULL)
  {
   fclose(cf);
   getcwd(t,255);
   chdir("cfg");
   sprintf(filename,"./cfgPeopsOSS %s",pCmdLine);
   system(filename);
   chdir(t);
  }
 else
  {
   strcpy(filename,"cfgPeopsOSS");
   cf=fopen(filename,"rb");
   if(cf!=NULL)
    {
     fclose(cf);
     sprintf(filename,"./cfgPeopsOSS %s",pCmdLine);
     system(filename);
    }
   else
    {
     sprintf(filename,"%s/cfgPeopsOSS",getenv("HOME"));
     cf=fopen(filename,"rb");
     if(cf!=NULL)
      {
       fclose(cf);
       getcwd(t,255);
       chdir(getenv("HOME"));
       sprintf(filename,"./cfgPeopsOSS %s",pCmdLine);
       system(filename);
       chdir(t);
      }
     else printf("cfgPeopsOSS not found!\n");
    }
  }
}

/////////////////////////////////////////////////////////
// READ LINUX CONFIG FILE
/////////////////////////////////////////////////////////

void ReadConfigFile(void)
{
 FILE *in;char t[256];int len;
 char * pB, * p;

 if(pConfigFile)  
  {
   strcpy(t,pConfigFile); 
   in = fopen(t,"rb"); 
   if(!in) return;
  }
 else 
  {
   strcpy(t,"cfg/spuPeopsOSS.cfg");
   in = fopen(t,"rb"); 
   if(!in) 
    {
     strcpy(t,"spuPeopsOSS.cfg");
     in = fopen(t,"rb"); 
     if(!in) 
      {
       sprintf(t,"%s/spuPeopsOSS.cfg",getenv("HOME")); 
       in = fopen(t,"rb"); 
       if(!in) return;
      }
    }
  } 

 pB=(char *)malloc(32767);
 memset(pB,0,32767);

 len = fread(pB, 1, 32767, in);
 fclose(in);

 strcpy(t,"\nVolume");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;}
 if(p) iVolume=atoi(p+len);
 if(iVolume<1) iVolume=1;
 if(iVolume>4) iVolume=4;

 strcpy(t,"\nUseXA");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;}
 if(p) iUseXA=atoi(p+len);
 if(iUseXA<0) iUseXA=0;
 if(iUseXA>1) iUseXA=1;

 strcpy(t,"\nXAPitch");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;}
 if(p) iXAPitch=atoi(p+len);
 if(iXAPitch<0) iXAPitch=0;
 if(iXAPitch>1) iXAPitch=1;

 strcpy(t,"\nHighCompMode");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;} 
 if(p)  iUseTimer=atoi(p+len); 
 if(iUseTimer<0) iUseTimer=0; 
 // note: timer mode 1 (win time events) is not supported
 // in linux. But timer mode 2 (spuupdate) is safe to use.
 if(iUseTimer)   iUseTimer=2; 

#ifdef NOTHREADLIB
 iUseTimer=2; 
#endif

 strcpy(t,"\nSPUIRQWait");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;} 
 if(p)  iSPUIRQWait=atoi(p+len); 
 if(iSPUIRQWait<0) iSPUIRQWait=0; 
 if(iSPUIRQWait>1) iSPUIRQWait=1; 

 strcpy(t,"\nUseReverb");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;} 
 if(p)  iUseReverb=atoi(p+len); 
 if(iUseReverb<0) iUseReverb=0; 
 if(iUseReverb>2) iUseReverb=2; 

 strcpy(t,"\nUseInterpolation");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;} 
 if(p)  iUseInterpolation=atoi(p+len); 
 if(iUseInterpolation<0) iUseInterpolation=0; 
 if(iUseInterpolation>3) iUseInterpolation=3; 

 strcpy(t,"\nDisStereo");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;} 
 if(p)  iDisStereo=atoi(p+len); 
 if(iDisStereo<0) iDisStereo=0; 
 if(iDisStereo>1) iDisStereo=1; 

 strcpy(t,"\nDecodedBufIRQ");p=strstr(pB,t);if(p) {p=strstr(p,"=");len=1;} 
 if(p)  iUseDBufIrq=atoi(p+len); 
 if(iUseDBufIrq<0) iUseDBufIrq=0; 
 if(iUseDBufIrq>1) iUseDBufIrq=1; 

 free(pB);
}

/////////////////////////////////////////////////////////
// READ CONFIG called by spu funcs
/////////////////////////////////////////////////////////

void ReadConfig(void)             
{
#ifndef __GX__
 iVolume=3; 
#endif //!__GX__
 iUseXA=1; 
 iXAPitch=0;
 iSPUIRQWait=1;  
 iUseTimer=2;
 iUseReverb=2;
 iUseInterpolation=2;
 iDisStereo=0;
 iUseDBufIrq=0;

 ReadConfigFile();

 if(iZincEmu) 
  {
   iVolume=1;    // with ZINC, max volume is needed (or qsound will be too loud)
   iDisStereo=0; // with ZINC, no mono possible (or qsound mixing troubles)
  }

}


