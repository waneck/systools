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

#include <gtk/gtk.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
#include "clipboard.h"

static GtkClipboard *getClipboard()
{
    static GtkClipboard *sClipboard = NULL;
    if ( sClipboard == NULL )
    {
		sClipboard = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
    }
    return sClipboard;
}

int systools_clipboard_set_text( const char * text ) {	
	gtk_clipboard_set_text( getClipboard(), text, strlen(text) );
	return 0;	
}

char* systools_clipboard_get_text() {
	char* result = gtk_clipboard_wait_for_text( getClipboard() );
	return result;
}

void systools_clipboard_clear() {
	gtk_clipboard_clear( getClipboard() );
}

#ifdef __cplusplus
}
#endif
