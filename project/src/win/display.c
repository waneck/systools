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

#include <windows.h>
#include "../display.h"
#include "display.h"

/** Set the screen resolution (set temporarily - when the app quits the
screen mode will be restored. */
int systools_win_display_set_mode(int width, int height, int depth) {	
	
	DEVMODE devMode;
	LONG error;
	
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth=width;
	devMode.dmPelsHeight=height;
	devMode.dmBitsPerPel=depth;
	devMode.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	error=ChangeDisplaySettingsEx(NULL,&devMode,NULL,CDS_FULLSCREEN,NULL);

	return (error==DISP_CHANGE_SUCCESSFUL);
}

/** Set the screen resolution to default */
void systools_win_display_set_default_mode() {
	ChangeDisplaySettingsEx(NULL,NULL,NULL,0,NULL);
}

/** Tests to see if a specific screen resolution is supported */
int systools_win_display_is_mode_supported(int width, int height, int depth) {	
	
	DEVMODE devMode;
	LONG error;
	
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth=width;
	devMode.dmPelsHeight=height;
	devMode.dmBitsPerPel=depth;
	devMode.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	error=ChangeDisplaySettingsEx(NULL,&devMode,NULL,CDS_FULLSCREEN|CDS_TEST,NULL);

	return (error==DISP_CHANGE_SUCCESSFUL);
}

void systools_display_get_screen_size(dimensions *pDim)
{
	pDim->width=GetSystemMetrics(SM_CXSCREEN);
	pDim->height=GetSystemMetrics(SM_CYSCREEN);
}