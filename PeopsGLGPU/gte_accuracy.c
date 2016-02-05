/***************************************************************************
 *   Copyright (C) 2011 by Blade_Arma                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/

#include "stdafx.h"
#include "externals.h"

#include <math.h>

// TODO: use malloc and pointer to the array's center.
float gteCoords[0x800 * 2][0x800 * 2][2];

void CALLBACK GPUaddVertex(short sx, short sy, long long fx, long long fy, long long fz)
{
	if(bGteAccuracy)
	{
		if(sx >= -0x800 && sx <= 0x7ff &&
		   sy >= -0x800 && sy <= 0x7ff)
		{
			gteCoords[sy + 0x800][sx + 0x800][0] = fx / 65536.0f;
			gteCoords[sy + 0x800][sx + 0x800][1] = fy / 65536.0f;
		}
	}
}

void resetGteVertices()
{
	if(bGteAccuracy)
	{
		memset(gteCoords, 0x00, sizeof(gteCoords));
	}
}

int getGteVertex(short sx, short sy, float *fx, float *fy)
{
	if(bGteAccuracy)
	{
		if(sx >= -0x800 && sx <= 0x7ff &&
		   sy >= -0x800 && sy <= 0x7ff)
		{
			if((fabsf(gteCoords[sy + 0x800][sx + 0x800][0] - sx) < 1.0) &&
			   (fabsf(gteCoords[sy + 0x800][sx + 0x800][1] - sy) < 1.0))
			{
				*fx = gteCoords[sy + 0x800][sx + 0x800][0];
				*fy = gteCoords[sy + 0x800][sx + 0x800][1];
				
				return 1;
			}
		}
	}
	
	return 0;
}
