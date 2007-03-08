/* ******************************************************************************** */
/*																					*/
/*  Systool - a Neko VM library														*/
/*  Copyright (c)2006																*/
/*  Lee McColl-Sylvester, Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom	*/
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

#include "menus.h"
#include <stdio.h>
#include <stdlib.h>

NOTIFYICONDATA* systools_win_set_tray_icon(HWND *wnd,char *ico,char *tooltip)
{
	HICON hIcon = 0;
	NOTIFYICONDATA structNid;
	
	if (!ico && !tooltip)
	{
		printf( "SetTrayIcon; invalid arguments" );
	}
	
	if (strlen (ico) != 0)
	{
		hIcon = (HICON) LoadImage( 0, ico, IMAGE_ICON, 0, 0, LR_LOADFROMFILE ); 
	}

	if (hIcon)
	{	
		DWORD dwSetType;
		dwSetType = NIM_ADD;
		memset(&structNid, 0 , sizeof(structNid));
		
		structNid.cbSize			= sizeof(structNid);
		structNid.hWnd				= wnd;								// handle to window:
		structNid.uID				= 0;								// unique id, for support of more than 1 tray icon at the same, not using this.
		structNid.uFlags			= NIF_ICON | NIF_MESSAGE | NIF_TIP;	// flags
		structNid.uCallbackMessage	= 9001;								// WMU_TRAYICON_HOVER  callback
		structNid.hIcon	= hIcon;										// the icon
		strcpy( structNid.szTip, tooltip );								// tooltip:


		if( !Shell_NotifyIcon( dwSetType, &structNid) )
			printf( "SetTrayIcon Failed" );
	}
	else printf( "Unable to get icon %s", ico );
	return &structNid;
}

void systools_win_destroy_tray_icon(NOTIFYICONDATA *ico)
{
	Shell_NotifyIcon( NIM_DELETE, ico );
}

void* tray_menu_cb( void* hook, void* msgid, void* p1, void* p2 )
{
	printf( "%i - %i - %i\n", msgid, p1, p2 );
}