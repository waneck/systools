/* ************************************************************************ */
/*																			*/
/*  Systool - a Neko VM library												*/
/*  Copyright (c)2006														*/
/*  Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom, Ian Thomas		*/
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

#ifndef STATIC_LINK
	#define IMPLEMENT_API
#endif
#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif
#include <hx/CFFI.h>

#include <stdio.h>
#include <stdlib.h>

extern "C"
{
	#include "api.h"
	#include "clipboard.h"
	#include "misc.h"
	#include "registry.h"
	#include "dialogs.h"
	#include "fileutils.h"
	#ifndef HX_LINUX
	#include "browser.h"
	#include "display.h"
	#endif
}

// init

static value systools_init()
{
	systools_misc_initialize();
	return val_null;
}
DEFINE_PRIM(systools_init,0);

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

static value dialogs_save_file( value title, value msg, value initialdir, value mask) {
	char * v;
	struct ARG_FILEFILTERS filters = {0,0,0};

	value result = val_null;
	val_check(title, string);
	val_check(msg, string);
	val_check(initialdir, string);

	if (val_is_object(mask)) {
		value count = val_field(mask,val_id("count"));
		value descriptions = val_field(mask,val_id("descriptions"));
		value extensions = val_field(mask,val_id("extensions"));

		val_check(count,int);
		val_check(descriptions,array);
		val_check(extensions,array);

		filters.count = val_int(count);
		if (filters.count) {
			long i = filters.count;
			filters.descriptions = (const char**) malloc(i*sizeof(char*));
			filters.extensions = (const char**) malloc(i*sizeof(char*));
			while(i) {
				i--;
				filters.descriptions[i] = val_string(val_array_i(descriptions,i));
				filters.extensions[i] = val_string(val_array_i(extensions,i));
			}
		}
	}

	result = val_null;
	v = systools_dialogs_save_file(val_string(title),val_string(msg),val_string(initialdir),filters.count? &filters : NULL);
	if (v) {
		result = alloc_string(v);
		free((void*)v);
	}

	// clean up allocated mem. for filters:
	if (val_is_object(mask)) {
		free(filters.descriptions);
		free(filters.extensions);
	}

	return result;

}
DEFINE_PRIM(dialogs_save_file,4);

static value dialogs_open_file( value title, value msg, value mask ) {
	value result = val_null;
	struct ARG_FILEFILTERS filters = {0,0,0};
	struct RES_STRINGLIST files;

	val_check(title,string);
	val_check(msg,string);

	if (val_is_object(mask)) {
		value count = val_field(mask,val_id("count"));
		value descriptions = val_field(mask,val_id("descriptions"));
		value extensions = val_field(mask,val_id("extensions"));

		val_check(count,int);
		val_check(descriptions,array);
		val_check(extensions,array);

		filters.count = val_int(count);
		if (filters.count) {
			long i = filters.count;
			filters.descriptions = (const char**) malloc(i*sizeof(char*));
			filters.extensions = (const char**) malloc(i*sizeof(char*));
			while(i) {
				i--;
				filters.descriptions[i] = val_string(val_array_i(descriptions,i));
				filters.extensions[i] = val_string(val_array_i(extensions,i));
			}
		}
	}

	systools_dialogs_open_file(val_string(title),val_string(msg),filters.count? &filters : NULL,&files);
	if (files.count) {
		result = alloc_array(files.count);
		while(files.count) {
			files.count--;
			val_array_set_i(result, files.count, alloc_string(files.strings[files.count]));
			free(files.strings[files.count]);
		}
		free(files.strings);
	}

	// clean up allocated mem. for filters:
	if (val_is_object(mask)) {
		free(filters.descriptions);
		free(filters.extensions);
	}

	return result;
}
DEFINE_PRIM(dialogs_open_file,3);

static value dialogs_folder( value title, value msg ) {
	char * v;
	value result = val_null;
	val_check(title, string);
	val_check(msg, string);
	result = val_null;
	v = systools_dialogs_folder(val_string(title),val_string(msg));
	if (v) {
		result = alloc_string(v);
		free(v);
	}
	return result;

}
DEFINE_PRIM(dialogs_folder,2);


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

// ---------------- Browser tools ---------------------------------------
static value browser_launch( value url )
{
#ifndef HX_LINUX
	int r;
	val_check(url, string);
	r=systools_browser_launch(val_string(url));
	return alloc_bool(r);
#else
	val_throw(alloc_string("this function is not available for this platform"));
	return val_null;
#endif
}
DEFINE_PRIM(browser_launch,1);

// ---------------- File Utils ---------------------------------------
static value fileutils_get_temp_folder()
{
	char * v;
	value result = val_null;
	v = systools_fileutils_get_temp_folder();
	if (v) {
		result = alloc_string(v);
		free((void*)v);
	}
	return result;
}
DEFINE_PRIM(fileutils_get_temp_folder,0);

// ---------------- Display tools --------------------

// Display specific code
static value display_get_screen_size()
{
#ifndef HX_LINUX
    dimensions dim;
	value w;
	value h;
	value o = alloc_empty_object();
	systools_display_get_screen_size(&dim);
	w=alloc_int(dim.width);
	h=alloc_int(dim.height);
	alloc_field( o, val_id("w"), w );
	alloc_field( o, val_id("h"), h );
	return o;
#else
	val_throw(alloc_string("function not available for this platform"));
	return val_null;
#endif
}
DEFINE_PRIM(display_get_screen_size,0);

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


// -- Windows specific


#ifdef NEKO_WINDOWS

extern "C"
{
	#include "win/win.h"
	#include "win/menus.h"
	#include "win/display.h"
}

static value win_replace_exe_icon( value exe, value icon, value iconResourceID) {
	int r = 0;
	value result = val_null;
	val_check(exe, string);
	val_check(icon, string);
	val_check(iconResourceID,int);
	r = systools_win_replaceExeIcon(val_string(exe),val_string(icon),val_int(iconResourceID));
	return r==1? val_true : val_false;
}
DEFINE_PRIM(win_replace_exe_icon,3);

static value win_create_process( value app, value args, value wd, value hide, value wait) {
	int r;
	const char *_args = 0;
	const char *_wd = 0;
	val_check(app,string);
	val_check(hide,int);
	val_check(wait,int);
	if (args != val_null) {
		val_check(args,string);
		_args = val_string(args);
	}
	if (wd != val_null) {
		val_check(wd,string);
		_wd = val_string(wd);
	}
	r = systools_win_create_process
		( val_string(app)
		, _args
		, _wd
		, val_int(hide)
		, val_int(wait)
		);
	return alloc_int(r);
}
DEFINE_PRIM(win_create_process,5);


// Tray Icon specific code


static value systray_create_icon( value w, value iconpath, value tooltip )
{
	val_check(tooltip,string);
	if ( !(val_is_string(iconpath) || val_is_null(iconpath)) )
		val_throw(alloc_string(tray_icon_error));
	else {
		tray_icon *tray = systools_win_create_tray_icon(val_hwnd(w),val_string(iconpath),val_string(tooltip));
		if (!tray)
			val_throw(alloc_string(tray_icon_error));

		return alloc_abstract(k_tray_icon,tray);
	}
	return val_null;
}
DEFINE_PRIM(systray_create_icon,3);

static value systray_destroy_icon( value tray )
{
	val_check_kind(tray,k_tray_icon);
	systools_win_destroy_tray_icon(val_tray_icon(tray));
	return val_null;
}
DEFINE_PRIM(systray_destroy_icon,1);

static value systray_menu_callback()
{
	return alloc_abstract(k_window_msg_cb,&tray_menu_cb);
}
DEFINE_PRIM(systray_menu_callback,0);

// Menu specific code
static value win_menu_create()
{
	return alloc_abstract(k_menu,systools_menu_create());
}
DEFINE_PRIM(win_menu_create,0);

static value win_popup_menu_create()
{
	return alloc_abstract(k_menu,systools_popup_menu_create());
}
DEFINE_PRIM(win_popup_menu_create,0);

static void win_destroy_menu( value menu )
{
	val_check_kind(menu,k_menu);
	systools_menu_destroy(val_menu(menu));
}
DEFINE_PRIM(win_destroy_menu,1);

static value win_destroy_tray_icon( value ico )
{
	val_check_kind(ico,k_icondata);
	systools_win_destroy_tray_icon(val_tray_icon(ico));
	return val_null;
}
DEFINE_PRIM(win_destroy_tray_icon,1);

static value win_add_menu_item( value menu, value caption, value callbackid )
{
	val_check_kind(menu,k_menu);
	val_check(caption,string);
	val_check(callbackid,int);
	systools_menu_add_item(val_menu(menu), val_string(caption), val_int(callbackid));
	return val_null;
}
DEFINE_PRIM(win_add_menu_item,3);

static value win_add_menu_submenu( value menu, value submenu, value caption, value callbackid )
{
	val_check_kind(menu,k_menu);
	val_check_kind(submenu,k_menu);
	val_check(caption,string);
	val_check(callbackid,int);
	systools_menu_add_submenu(val_menu(menu), val_menu(submenu), val_string(caption), val_int(callbackid));
	return val_null;
}
DEFINE_PRIM(win_add_menu_submenu,4);

static value win_add_menu_divider( value menu, value callbackid )
{
	val_check_kind(menu,k_menu);
	val_check(callbackid,int);
	systools_menu_add_item(val_menu(menu), (char*)"--", val_int(callbackid));
	return val_null;
}
DEFINE_PRIM(win_add_menu_divider,2);

static value win_show_menu( value w, value m )
{
	val_check_kind(m,k_menu);
	return alloc_int(systools_menu_show( val_hwnd(w), val_menu(m) ));
}
DEFINE_PRIM(win_show_menu,2);

static value win_show_popup_menu( value w, value m )
{
	val_check_kind(m,k_menu);
	return alloc_int(systools_popup_menu_show( val_hwnd(w), val_menu(m) ));
}
DEFINE_PRIM(win_show_popup_menu,2);

static value display_set_mode( value width, value height, value depth )
{
	int r;
	val_check(width,int);
	val_check(height,int);
	val_check(depth,int);
	r=systools_win_display_set_mode(val_int(width),val_int(height),val_int(depth));
	return alloc_bool(r);
}
DEFINE_PRIM(display_set_mode,3);

static value display_set_default_mode()
{
	systools_win_display_set_default_mode();
	return val_null;
}
DEFINE_PRIM(display_set_default_mode,0);

static value display_is_mode_supported( value width, value height, value depth )
{
	int r;
	val_check(width,int);
	val_check(height,int);
	val_check(depth,int);
	r=systools_win_display_is_mode_supported(val_int(width),val_int(height),val_int(depth));
	return alloc_bool(r);
}
DEFINE_PRIM(display_is_mode_supported,3);

#endif

// Neko specific code

extern "C" void systools_main()
{
    val_int(0); // fix neko init
}
DEFINE_ENTRY_POINT(systools_main);

extern "C" int systools_register_prims () { return 0; }
