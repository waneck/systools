/* ************************************************************************ */
/*																			*/
/*  Systool - a Neko VM library												*/
/*  Copyright (c)2006														*/
/*  Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom					*/
/*																			*/
/* This library is free software; you can redistribute it and/or			*/
/* modify it under the terms of the GNU Lesser General Public				*/
/* License as published by the Free Software Foundation; either				*/
/* version 2.1 of the License, or (at your option) any later version.		*/
/*																			*/
/* This library is distributed in the hope that it will be useful,			*/
/* but WITHOUT ANY WARRANTY; without even the implied warranty of			*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU		*/
/* Lesser General Public License or the LICENSE file for more details.		*/
/*																			*/
/* ************************************************************************ */

#include "../registry.h"
#include <windows.h>

void systools_registry_set_value( int key, const char * subkey, const char * valuename, const char * value) {
	HKEY k;
	HKEY hkey = (HKEY) (key | 0x80000000);
	if (RegCreateKeyEx(hkey, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &k, NULL) == ERROR_SUCCESS)
	{
		RegSetValueEx(k, valuename, 0, REG_SZ, value, (DWORD)(strlen(value)+1));
		RegCloseKey(k);
	}
}

char * systools_registry_get_value( int key, const char * subkey, const char * valuename ) {
	HKEY k;
	DWORD ktype;
	DWORD ksize = 16000;
	char kdata[16000];
	HKEY hkey = (HKEY) (key | 0x80000000);
	char *out = NULL;

	if (RegOpenKeyEx(hkey, subkey, 0, KEY_READ, &k) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(k, valuename, NULL, &ktype,(LPBYTE)kdata,&ksize) ==  ERROR_SUCCESS) 
		{
			out = _strdup(kdata);
		}
		RegCloseKey(k);
	}
	return out;
}

void systools_registry_delete_key( int key, const char * subkey ) {
	HKEY hkey = (HKEY) (key | 0x80000000);
	RegDeleteKey(hkey, subkey);
}
