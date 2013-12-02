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

#include "misc.h"
#if CARBON
#include <Carbon/Carbon.h>
#else
#include <Cocoa/Cocoa.h>
#endif

void systools_misc_initialize()
{
}

int systools_misc_get_key_state( int code ) {
	#if CARBON
	KeyMap theKeys;
	unsigned char *keybytes;
	if (code >= 0 && code <= 127) {
		GetKeys(theKeys);
		keybytes = (unsigned char *) theKeys;
		return (keybytes[code>>3] & (1 << (code&7)));
	}
	#endif
	return 0;
}
