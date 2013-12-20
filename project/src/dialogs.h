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

#include "api.h"

void systools_dialogs_message_box( const char *title, const char *message, int error );
int systools_dialogs_dialog_box( const char *title, const char *message, int error );
void systools_dialogs_open_file( const char *title, const char *msg, struct ARG_FILEFILTERS *filters, struct RES_STRINGLIST *result) ;
char* systools_dialogs_save_file( const char *title, const char *msg, const char *initialdir, struct ARG_FILEFILTERS *filters);
char* systools_dialogs_folder( const char *title, const char *msg );
