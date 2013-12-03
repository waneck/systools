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
#ifdef CARBON
#include <Carbon/Carbon.h>
#else
#include <Cocoa/Cocoa.h>
#endif

#if CARBON
static PasteboardRef getPasteboard()
{
    static PasteboardRef sPasteboard = NULL;
    if ( sPasteboard == NULL )
    {
        PasteboardCreate( kPasteboardClipboard, &sPasteboard );
    }
    return sPasteboard;
}
#endif

int systools_clipboard_set_text( const char * text ) {
#if CARBON
	CFDataRef data = CFDataCreate(kCFAllocatorDefault,(const UInt8*)text,strlen(text));

	PasteboardClear(getPasteboard());
	PasteboardSynchronize(getPasteboard());

	return PasteboardPutItemFlavor(getPasteboard(),(PasteboardItemID)1,CFSTR("utf8"),data,kPasteboardFlavorNoFlags);
#else
	NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
	[pasteboard clearContents];
	[pasteboard writeObjects:[NSArray arrayWithObject:[NSString stringWithUTF8String:text]]];
	return 0;
#endif
}

char* systools_clipboard_get_text() {
#if CARBON
	OSStatus err;
	CFDataRef data;
	ItemCount itemCount;
	UInt32 itemIndex = 1;
	char* result = 0;

    PasteboardSynchronize(getPasteboard());

	err = PasteboardGetItemCount(getPasteboard(), &itemCount );
    if (err != noErr || itemCount == 0)
		return result;

    for(; itemIndex <= itemCount; itemIndex++) {
		PasteboardItemID itemID;
		err = PasteboardGetItemIdentifier(getPasteboard(),itemIndex,&itemID);
		if (err == noErr) {
			PasteboardFlavorFlags flavorFlags;
			err = PasteboardGetItemFlavorFlags(getPasteboard(),itemID,CFSTR("utf8"),&flavorFlags );
			if (err == noErr) {
				err = PasteboardCopyItemFlavorData(getPasteboard(),itemID,CFSTR("utf8"),&data);
				if (err == noErr) {
					CFIndex length = CFDataGetLength(data);
					result = malloc(length+1);
					memcpy(result,CFDataGetBytePtr(data),length);
					result[length] = 0;
				}
				CFRelease(data);
			}
			if (result) break;
		}
	}
	return result;
#else
	NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
	NSArray *classes = [[NSArray alloc] initWithObjects:[NSString class], nil];
	NSArray *strings = [pasteboard readObjectsForClasses:classes options:nil];
	if (strings != nil) {
		return (char *)[[strings objectAtIndex:0] UTF8String];
	}
	return 0;
#endif
}

void systools_clipboard_clear() {
#if CARBON
	PasteboardSynchronize(getPasteboard());
	PasteboardClear(getPasteboard());
#else
	NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
	[pasteboard clearContents];
#endif
}