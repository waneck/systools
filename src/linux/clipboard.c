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
#include <gtk/gtk.h>
#include <string.h>

int systools_clipboard_set_text( const char * text ) {	
	GtkClipboard* clipboard = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
	gtk_clipboard_set_text( clipboard, text, strlen(text) );
	return 0;	
}

char* systools_clipboard_get_text() {
	GtkClipboard* clipboard = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
	char* result = gtk_clipboard_wait_for_text( clipboard );

	return result;
}

void systools_clipboard_clear() {
	GtkClipboard* clipboard = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
	gtk_clipboard_clear( clipboard );
}
