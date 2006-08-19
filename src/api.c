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

// ---------------- Clipboard methods ----------------------------------------

static value clipboard_set_data( value data, value format ) {
	val_check(data, string);
	val_check(format, int);
	systools_clipboard_set_data( val_string(data), val_int(format) );
	return val_null;
}
DEFINE_PRIM(clipboard_set_data,2);

static value clipboard_get_data( value format ) {
	const char *v;
	val_check(format, int);
	v = systools_clipboard_get_data( val_int(format) );
	if( v == NULL )
		return val_null;
	return alloc_string(v);
}
DEFINE_PRIM(clipboard_get_data,1);

static value clipboard_clear( ) {
	systools_clipboard_clear();
	return val_null;
}
DEFINE_PRIM(clipboard_clear,0);

static value clipboard_is_format_available( value format ) {
	int r;
	val_check(format, int);
	r = systools_clipboard_is_format_available(val_int(format));
	return alloc_bool(r);
}
DEFINE_PRIM(clipboard_is_format_available,1);

// ---------------- Miscellanious tools --------------------------------------

static value misc_get_key_state( value key ) {
	int r;
	val_check(key,int);
	r = systools_misc_get_key_state(val_int(key));
	return alloc_int(r);
}

DEFINE_PRIM(misc_get_key_state,1);