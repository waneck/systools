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

#include "../clipboard.h"
#include <windows.h>

void systools_clipboard_set_data( const char * data, int format ) {
	size_t datalength;
	char * datacopy;
	HGLOBAL hglbCopy;
	if (!OpenClipboard(NULL))
		return;
	EmptyClipboard();

	// Allocate global memory for the data
	datalength = strlen(data);
	hglbCopy = GlobalAlloc(GMEM_MOVEABLE, datalength + 1);
	if (hglbCopy == NULL) { 
		CloseClipboard(); 
		return;
	}
 
    // Lock the handle and copy the data to the buffer. 
    datacopy = GlobalLock(hglbCopy); 
    memcpy(datacopy, data, datalength); 
    datacopy[datalength] = 0;    // null character 
    GlobalUnlock(hglbCopy); 

    // Place the handle on the clipboard. 

    SetClipboardData(format, hglbCopy); 
	CloseClipboard();
}

const char * systools_clipboard_get_data( int format ) {
	HGLOBAL   hglb; 
	char const * data;
	char const * datacopy;
	if (!IsClipboardFormatAvailable(format)) {
		return NULL;
	}
	if (!OpenClipboard(NULL)) {
		return NULL;
	}

	datacopy = NULL;
	hglb = GetClipboardData(format); 
	if (hglb != NULL) { 
		data = GlobalLock(hglb); 
        if (data != NULL) { 
			datacopy = strdup(data);
            GlobalUnlock(hglb);
        } 
    } 
    CloseClipboard();

	return datacopy;
}

void systools_clipboard_clear() {
	OpenClipboard(NULL);
	EmptyClipboard();
	CloseClipboard();
}

int systools_clipboard_is_format_available( int format ) {
	return IsClipboardFormatAvailable(format);
}