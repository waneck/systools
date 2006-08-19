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

#include "clipboard.h"

#define ST_CLIPBOARD_ID CFSTR( "org.nekovm.pasteboard.clipboard" )

static PasteboardRef getPasteboard( void )
{
    static PasteboardRef sPasteboard = NULL;

    if ( sPasteboard == NULL )
    {
        PasteboardCreate( ST_CLIPBOARD_ID, &sPasteboard );
    }

    return sPasteboard;
}

int systools_clipboard_set_text( const char * text ) {	
	CFStringRef type = CFSTR("utf8");
	CFDataRef data;
	CFDataCreate(kCFAllocatorDefault,(const UInt8*)text,strlen(text));
	return PasteboardPutItemFlavor(getPasteboard(),0,type,data,kPasteboardFlavorNoFlags);	
}

size_t systools_clipboard_get_text( char* text, size_t size) {
	OSStatus err;
	CFStringRef type = CFSTR("utf8");
	CFDataRef data;
	err = PasteboardCopyItemFlavorData(getPasteboard(),0,type,&data);
	if (err != noErr) 
		return err;
	if (size == 0)
		return CFDataGetLength(data);
	if (size < CFDataGetLength(data)) 
		return 1;
	CFDataGetBytes(data,CFRangeMake(0,CFDataGetLength(data)),(UInt8*)text);
	return 0;			
}

void systools_clipboard_clear() {
	PasteboardClear(getPasteboard());
}