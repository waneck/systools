/* ******************************************************************************** */
/*																					*/
/*  Systool - a Neko VM library														*/
/*  Copyright (c)2006																*/
/*  Lee McColl-Sylvester, Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom,	*/
/*	Ian Thomas																		*/
/*																					*/
/* This library is free software; you can redistribute it and/or					*/
/* modify it under the terms of the GNU Lesser General Public						*/
/* License as published by the Free Software Foundation; either						*/
/* version 2.1 of the License, or (at your option) any later version.				*/
/*																					*/
/* This library is distributed in the hope that it will be useful,					*/
/* but WITHOUT ANY WARRANTY; without even the implied warranty of					*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU				*/
/* Lesser General Public License or the LICENSE file for more details.				*/
/*																					*/
/* ******************************************************************************** */

#include "../display.h"
#if CARBON
#include <Carbon/Carbon.h>
#else
#include <Cocoa/Cocoa.h>
#endif

void systools_display_get_screen_size(dimensions *pDim)
{
#if CARBON
	pDim->width=CGDisplayPixelsWide(CGMainDisplayID());
	pDim->height=CGDisplayPixelsHigh(CGMainDisplayID());
#else
	NSRect screenRect = [[NSScreen mainScreen] frame];
	pDim->width = screenRect.size.width;
	pDim->height = screenRect.size.height;
#endif
}