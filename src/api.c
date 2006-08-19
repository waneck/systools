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

#include <neko/neko.h>
#include <neko/neko_vm.h>

#include "clipboard.h"
#include "misc.h"
#include <stdlib.h>

// ---------------- Clipboard methods ----------------------------------------


static value clipboard_set_text( value text ) {
	val_check(text, string);
	return alloc_int(systools_clipboard_set_text( val_string(text)));	
}
DEFINE_PRIM(clipboard_set_text,1);


static value clipboard_get_text() {
	value result = val_null;
	char *v;
	// calling with zero length should return required buffer size:
	size_t len = systools_clipboard_get_text(0,0);
		
	if (len) {		
		v = malloc(len);
		if (systools_clipboard_get_text(v,len)) {
			result = alloc_string(v);
		}
		free((void*)v);
	}
	return result;		
}
DEFINE_PRIM(clipboard_get_text,0);


static value clipboard_clear( ) {
	systools_clipboard_clear();
	return val_null;
}
DEFINE_PRIM(clipboard_clear,0);


// ---------------- Miscellanious tools --------------------------------------


static value misc_get_key_state( value key ) {
	int r;
	val_check(key,int);
	r = systools_misc_get_key_state(val_int(key));
	return alloc_int(r);
}
DEFINE_PRIM(misc_get_key_state,1);