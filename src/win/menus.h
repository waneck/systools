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

NOTIFYICONDATA* systools_win_set_tray_icon(HWND* wnd,const char* ico,const char* tooltip);
void systools_win_destroy_tray_icon(NOTIFYICONDATA* ico);
void* tray_menu_cb(void* hook, void* msgid, void* p1, void* p2);

DEFINE_KIND(k_window_msg_cb);

#define val_hwnd(x) ((HWND*)val_data(x))
#define val_trayicon(x) ((NOTIFYICONDATA*)val_data(x))
#define val_menu(x) ((HMENU*)val_data(x))