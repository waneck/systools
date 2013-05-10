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

const char tray_icon_error[255];
#define set_tray_error(x) strcpy((char*)&tray_icon_error,x)

tray_icon *systools_win_create_tray_icon(HWND *wnd,const char *ico,const char *tooltip){
	
	HICON hIcon = 0;
	
	if (!ico && !tooltip) {
		set_tray_error("SetTrayIcon; invalid arguments");
		return NULL;
	}

	if (strlen (ico) == 0) {
		set_tray_error("SetTrayIcon; invalid icon path");
		return NULL;
	}

	hIcon = (HICON) LoadImage( 0, ico, IMAGE_ICON, 0, 0, LR_LOADFROMFILE );
	
	if (hIcon==NULL) {
		set_tray_error("SetTrayIcon; failed loading icon");
		return NULL; 
	} else {	
		long nid_size = sizeof(NOTIFYICONDATA);
		tray_icon *tray = malloc(sizeof(tray_icon));
		DWORD dwSetType = NIM_ADD;
		tray->icon_data = malloc(nid_size);
		tray->icon_handle = hIcon;
		tray->msg_callback = tray_menu_cb;	
				
		tray->icon_data->cbSize				= nid_size;
		tray->icon_data->hWnd				= wnd;								// handle to window:
		tray->icon_data->uID				= 0;								// unique id, for support of more than 1 tray icon at the same, not using this.
		tray->icon_data->uFlags				= NIF_ICON | NIF_MESSAGE | NIF_TIP;	// flags
		tray->icon_data->uCallbackMessage	= 9001;								// WMU_TRAYICON_HOVER  callback
		tray->icon_data->hIcon				= hIcon;										// the icon
		strcpy( tray->icon_data->szTip, tooltip );								// tooltip:

		if( !Shell_NotifyIcon( dwSetType, tray->icon_data ) ) {
			free(tray->icon_data);
			free(tray);
			set_tray_error("SetTrayIcon Failed");
			return NULL;
		}
		return tray;
	}	
	return 0; 
}

void systools_win_destroy_tray_icon( tray_icon *icon )
{
	Shell_NotifyIcon( NIM_DELETE, icon->icon_data );
	DestroyIcon(icon->icon_handle);
	free(icon->icon_data);
	free(icon);
}

void* tray_menu_cb( void* data, void* msgid, void* msgid2, void* p1, void* p2 )
{
	tray_icon *tray = (tray_icon*) data;
	printf( "%i - %i - %i - %i\n", msgid, msgid2, p1, p2 );
}



// Menus code
HMENU *systools_menu_create()
{
	HMENU *hmenu = malloc(sizeof(HMENU));
	*hmenu = CreateMenu();
	return hmenu;
}

HMENU *systools_popup_menu_create()
{
	HMENU *hmenu = malloc(sizeof(HMENU));
	*hmenu = CreatePopupMenu();
	return hmenu;
}

void systools_menu_destroy( HMENU *hmenu )
{
	DestroyMenu( *hmenu );
}

int systools_menu_add_item( HMENU *hmenu, const char *caption, DWORD callbackID )
{
	int bResult = 0;

	if (caption)
	{
		MENUITEMINFO mii;
		memset(&mii, 0, sizeof(MENUITEMINFO));
		mii.cbSize		= sizeof( MENUITEMINFO );
		mii.fMask		= MIIM_TYPE | MIIM_ID;
		if (strcmp(caption,"--"))
			mii.fType		= MFT_STRING;
		else
			mii.fType		= MFT_SEPARATOR;
		mii.dwTypeData	= caption;
		mii.wID			= callbackID;
		mii.hSubMenu	= *hmenu;

		InsertMenuItem(
			*hmenu,
			callbackID,
			TRUE,
			&mii );
		
		bResult = 1;
	}

	return bResult;
}

int systools_menu_add_submenu( HMENU *hmenu, HMENU *submenu, const char *caption, DWORD callbackID )
{
	int bResult = 0;

	if (caption)
	{
		InsertMenu(*hmenu, callbackID, MF_STRING | MF_POPUP, (UINT)*submenu, caption);
		bResult = 1;
	}

	return bResult;
}

int systools_popup_menu_show( HWND *hwnd, HMENU *hmenu )
{
	int t;
	POINT pt;
	GetCursorPos(&pt);
	t = TrackPopupMenu(*hmenu, 
		TPM_RIGHTBUTTON | TPM_RETURNCMD, 
		pt.x, 
		pt.y, 
		0, 
		hwnd, 
		NULL);
	return t;
}

int systools_menu_show( HWND *hwnd, HMENU *hmenu )
{
	int t;
	POINT pt;
	GetCursorPos(&pt);
	t = SetMenu(hwnd, *hmenu);
	return t;
}