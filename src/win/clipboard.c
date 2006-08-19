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

int systools_clipboard_set_text( const char * text ) {
	size_t textlength;
	char * textcopy;
	HGLOBAL hglbCopy;
	if (!OpenClipboard(NULL))
		return 1;
	EmptyClipboard();

	// Allocate global memory for the text
	textlength = strlen(text);
	hglbCopy = GlobalAlloc(GMEM_MOVEABLE, textlength + 1);
	if (hglbCopy == NULL) { 
		CloseClipboard(); 
		return 1;
	}
 
    // Lock the handle and copy the text to the buffer. 
    textcopy = GlobalLock(hglbCopy); 
    memcpy(textcopy, text, textlength); 
    textcopy[textlength] = 0;    // null character 
    GlobalUnlock(hglbCopy); 

    // Place the handle on the clipboard. 
	// Format is now set fixed to text. Supporting other formats will require
	// returning an array, for string will not work well with data containing
	// zeros
    SetClipboardData(1, hglbCopy); 
	CloseClipboard();
	
	return 0;
}

size_t systools_clipboard_get_text(char *text, size_t len) {
	// if length is 0, we're expected to return the 
	// clipboards string' lenght. Other wise a non-zero
	// return code signals failure:
	int err = len ? 1 : 0;
	HGLOBAL   hglb;	
	
	if (!OpenClipboard(NULL))
		return err;

	// Format is now set fixed to text. Supporting other formats will require
	// returning an array, for string will not work well with data containing
	// zeros
	hglb = GetClipboardData(1); 
	if (hglb != NULL) { 
		const char* globtext = GlobalLock(hglb); 
        if (globtext != NULL) {
			if (len == 0) { 
				err = (int) strlen(globtext+1);
			} else {	
				if (strlen(globtext)+1 >= len) {
					text = strdup(globtext);
					err = 0;
				}				
			}
            GlobalUnlock(hglb);
        } 
    } 
    CloseClipboard();
	return err;
}

void systools_clipboard_clear() {
	OpenClipboard(NULL);
	EmptyClipboard();
	CloseClipboard();
}