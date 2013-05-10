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

#include <windows.h>

typedef void* (*_tray_menu_cb)(void* custom, void* id1, void *id2, void* p1, void* p2);

typedef struct _tray_icon {	
	NOTIFYICONDATA* icon_data;
	HICON			icon_handle;	
	_tray_menu_cb	msg_callback;
} tray_icon;


// ---------------- Type Conversion -----------------------

DEFINE_KIND(k_icondata);
DEFINE_KIND(k_menu);
DEFINE_KIND(k_void_pointer);
DEFINE_KIND(k_tray_icon);
DEFINE_KIND(k_window_msg_cb);

extern const char tray_icon_error[255];

#define val_tray_icon(x) ((tray_icon*)val_data(x))
#define val_hwnd(x) ((HWND*)val_data(x))
#define val_menu(x) ((HMENU*)val_data(x))

tray_icon *systools_win_create_tray_icon(HWND *wnd,const char *ico,const char *tooltip);
//tray_icon *systools_create_set_tray_icon(HWND* wnd,const char* ico,const char* tooltip);
void systools_win_destroy_tray_icon(tray_icon *tray);
void* tray_menu_cb(void* custom, void* id1, void *id2, void* p1, void* p2);

HMENU *systools_menu_create();
HMENU *systools_popup_menu_create();
void systools_menu_destroy( HMENU *hmenu );
int systools_menu_add_item( HMENU* hmenu, const char* caption, DWORD callbackID );
int systools_menu_add_submenu( HMENU *hmenu, HMENU *submenu, const char *caption, DWORD callbackID );
int systools_popup_menu_show( HWND *hwnd, HMENU *hmenu );
int systools_menu_show( HWND *hwnd, HMENU *hmenu );
