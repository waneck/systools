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
#include <gconf/gconf-client.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "misc.h"

void systools_misc_initialize() {
	gtk_init(NULL,NULL);
	gconf_init(0,NULL,NULL);
}
/* DEFINE_ENTRY_POINT(systools_misc_initialize); */

int systools_misc_get_key_state( int code ) {
	printf("SYSTOOLS: systools_misc_get_key_state NYI\n");
	return 0;
}
#ifdef __cplusplus
}
#endif
