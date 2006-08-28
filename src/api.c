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

#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "clipboard.h"
#include "misc.h"
#include "registry.h"


// ---------------- Dialog methods -------------------------------------------


static value dialogs_message_box( value title, value msg, value error ) {
	val_check(title,string);
	val_check(msg,string);
	val_check(error,bool);
	systools_dialogs_message_box(val_string(title),val_string(msg),val_bool(error));
	return val_null;
}
DEFINE_PRIM(dialogs_message_box,3);


static value dialogs_dialog_box( value title, value msg, value error ) {
	int r;
	val_check(title,string);
	val_check(msg,string);
	val_check(error,bool);
	r = systools_dialogs_dialog_box(val_string(title),val_string(msg),val_bool(error));
	return alloc_bool(r);
}
DEFINE_PRIM(dialogs_dialog_box,3);


static value dialogs_open_file( value title, value msg, value mask ) {
	value result = val_null;
	struct RES_STRINGLIST files;
	
	val_check(title,string);
	val_check(msg,string);
	val_check(mask,string);	
	systools_dialogs_open_file(val_string(title),val_string(msg),val_string(mask),&files);
	if (files.count) {	
		result = alloc_array(files.count);
		while(files.count) {
			val_array_ptr(result)[--files.count] = alloc_string(files.strings[files.count]);
			free(files.strings[files.count]);
		}
		free(files.strings);
	}
	
	return result;
}
DEFINE_PRIM(dialogs_open_file,3);


// ---------------- Clipboard methods ----------------------------------------


static value clipboard_set_text( value text ) {
	val_check(text, string);
	return alloc_int(systools_clipboard_set_text(val_string(text)));	
}
DEFINE_PRIM(clipboard_set_text,1);


static value clipboard_get_text() {
	value result = val_null;
	char* v = systools_clipboard_get_text(); 
	if (v) {			
		result = alloc_string(v);			
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

// ---------------- Registry tools --------------------------------------


static value registry_set_value( value key, value subkey, value valuename, value v) {
	val_check(key, int);
	val_check(subkey, string);
	val_check(valuename, string);
	val_check(v, string);
	systools_registry_set_value(val_int(key), val_string(subkey), val_string(valuename), val_string(v));
	return val_null;
}
DEFINE_PRIM(registry_set_value,4);

static value registry_get_value( value key, value subkey, value valuename) {
	char * v;
	value result = val_null;
	val_check(key, int);
	val_check(subkey, string);
	val_check(valuename, string);
	result = val_null;
	v = systools_registry_get_value(val_int(key), val_string(subkey), val_string(valuename)); 
	if (v) {			
		result = alloc_string(v);
		free((void*)v);
	}
	return result;		
}
DEFINE_PRIM(registry_get_value,3);

static value registry_delete_key( value key, value subkey) {
	val_check(key, int);
	val_check(subkey, string);
	systools_registry_delete_key(val_int(key), val_string(subkey)); 
	return val_null;
}
DEFINE_PRIM(registry_delete_key,2);