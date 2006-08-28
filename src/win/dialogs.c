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

#include "../dialogs.h"
#include <windows.h>

void systools_dialogs_message_box( const char *title, const char *message, int error ) {		
	MessageBox(NULL,message,title,MB_OK | (error ? MB_ICONERROR : MB_ICONINFORMATION));
}

int systools_dialogs_dialog_box( const char *title, const char *message, int error ) {
	return MessageBox(NULL,message,title,MB_TASKMODAL | MB_OK | MB_YESNO | (error ? MB_ICONERROR : MB_ICONINFORMATION)) == IDYES;		
}

void systools_dialogs_open_file( const char *title, const char *msg, const char *mask, struct RES_STRINGLIST *r){
	OPENFILENAME ofn;
	r->count = 0;
	r->strings = NULL;
	
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFileTitle = (char*) title;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER; 
	ofn.nMaxFile = 8192;	/*	This is madnes: Windows wants us to 
								predict how many characters the user
								selected files will be at max. Let me
								fetch my glass ball...
								Using 8k for now. */
	ofn.lpstrFile = malloc(8192);
	ofn.lpstrFile[0] = 0;

	if (GetOpenFileName(&ofn)) {		
		char* file = ofn.lpstrFile;
		char* folder = NULL;
		long pass = 1;
		while(*file!=0) {
			size_t len = strlen(file);			
			len++;
			if (pass==1) {
				r->strings = realloc(r->strings,sizeof(char*)*(r->count+1));
				r->strings[r->count] = strdup(file);
				folder = file;			
				r->count++;
			} else if (pass==2) {
				r->strings[0] = realloc(r->strings[0],strlen(r->strings[0])+strlen(file)+2);
				strcat(r->strings[0], file);
				strcat(r->strings[0], "\\");				
			} else {
				r->strings = realloc(r->strings,sizeof(char*)*(r->count+1));
				r->strings[r->count] = malloc(strlen(folder)+strlen(file)+2);
				strcpy(r->strings[r->count], folder);
				strcat(r->strings[r->count], "\\");
				strcat(r->strings[r->count], file);
				r->count++;
			}
			file += len;
			pass++;		
		}		
	}	
	free(ofn.lpstrFile);	
}