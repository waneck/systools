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
#include "shlobj.h"

void systools_dialogs_message_box( const char *title, const char *message, int error ) {		
	MessageBox(NULL,message,title,MB_OK | (error ? MB_ICONERROR : MB_ICONINFORMATION));
}

int systools_dialogs_dialog_box( const char *title, const char *message, int error ) {
	return MessageBox(NULL,message,title,MB_TASKMODAL | MB_OK | MB_YESNO | (error ? MB_ICONERROR : MB_ICONINFORMATION)) == IDYES;		
}

char* systools_dialogs_save_file( const char *title, const char *_, const char *initialdir, struct ARG_FILEFILTERS *mask) {
	char* result = 0;
	OPENFILENAME ofn;

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrTitle	= (char*) title;
	ofn.lpstrInitialDir = (char*) initialdir;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER; 
	ofn.nMaxFile = 8192;	/*	This is madnes: Windows wants us to 
								predict how many characters the user
								selected files will be at max. Let me
								fetch my glass ball...
								Using 8k for now. */
	ofn.lpstrFile = malloc(8192);
	ofn.lpstrFile[0] = 0;

	if (mask && mask->count) {
		long i = mask->count;
		size_t s = 0, el = 0, dl = 0;
		
		while (i) {			
			i--;
			el = +strlen(mask->extensions[i])+1;
			dl = strlen(mask->descriptions[i])+1;
			ofn.lpstrFilter = realloc
					( ofn.lpstrFilter
					, s + dl + el + (i==0? 1 : 0)
					);			
			strcpy(ofn.lpstrFilter+(s),mask->descriptions[i]);
			strcpy(ofn.lpstrFilter+(s+=dl),mask->extensions[i]);
			s+=el;
			// last pass, add term. zero:
			if (i==0) 
				memset(ofn.lpstrFilter+s,0,1);
		}		
	}

	if( GetSaveFileName(&ofn ) ){
		result = strdup( ofn.lpstrFile );
		free(ofn.lpstrFile);
		return result;
	}else{
		return NULL;
	}
}

void systools_dialogs_open_file( const char *title, const char *msg, struct ARG_FILEFILTERS *mask, struct RES_STRINGLIST *r){
	OPENFILENAME ofn;
	r->count = 0;
	r->strings = NULL;
	
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrTitle = (char*) title;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER; 
	ofn.nMaxFile = 8192;	/*	This is madnes: Windows wants us to 
								predict how many characters the user
								selected files will be at max. Let me
								fetch my glass ball...
								Using 8k for now. */
	ofn.lpstrFile = malloc(8192);
	ofn.lpstrFile[0] = 0;	

	if (mask && mask->count) {
		long i = mask->count;
		size_t s = 0, el = 0, dl = 0;
		
		while (i) {			
			i--;
			el = +strlen(mask->extensions[i])+1;
			dl = strlen(mask->descriptions[i])+1;
			ofn.lpstrFilter = realloc
					( ofn.lpstrFilter
					, s + dl + el + (i==0? 1 : 0)
					);			
			strcpy(ofn.lpstrFilter+(s),mask->descriptions[i]);
			strcpy(ofn.lpstrFilter+(s+=dl),mask->extensions[i]);
			s+=el;
			// last pass, add term. zero:
			if (i==0) 
				memset(ofn.lpstrFilter+s,0,1);
		}		
	}

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
				strcat(r->strings[0], "\\");
				strcat(r->strings[0], file);								
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

char* systools_dialogs_folder( const char *title, const char *msg ) {
	BROWSEINFO bi;
	LPCITEMIDLIST folderID;
	TCHAR	szFolderDisplay[MAX_PATH];
	TCHAR	szFolderPath[MAX_PATH];

	memset( szFolderDisplay, 0, MAX_PATH);
	memset( szFolderPath, 0, MAX_PATH);	
	
	bi.hwndOwner		= NULL;					// handle of parent window
	bi.pidlRoot			= NULL;					// Starting directory..NULL for "My Computer"
	bi.pszDisplayName	= szFolderDisplay;		// buffer which recieves the path of chosen	directory.
	bi.lpszTitle		= title;				// text displayed in dialog's static	control.
	bi.ulFlags	 		= BIF_RETURNONLYFSDIRS;	// flag saying only directory's can be returned.
	bi.lpfn				= NULL;					// NULL meaning no hook proc.

	folderID= SHBrowseForFolder(&bi);	
	
	if(folderID)
	{
		SHGetPathFromIDList(folderID,szFolderPath);
		return strdup(szFolderPath);
	}
	return NULL;
}