/***************************************************************************
                        stdafx.h  -  description
                             -------------------
    begin                : Sun Oct 28 2001
    copyright            : (C) 2001 by Pete Bernert
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
// 2001/10/28 - Pete  
// - generic cleanup for the Peops release
//
//*************************************************************************// 

#ifndef _SDL
#define __X11_C_ 
//X11 render
#define __inline inline
#define CALLBACK

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/time.h> 
#include <GL/gl.h>  
#include <GL/glx.h>  
#include <math.h> 
#include <X11/cursorfont.h> 

#else 		//SDL render

#define __inline inline
#define CALLBACK

#ifndef __GX__
#include <SDL/SDL.h>
#endif //!__GX__
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/time.h> 
#include <math.h> 

#endif

