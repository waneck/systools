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

#include "win.h"
#include <windows.h>

int systools_win_replaceExeIcon( const char *exe, const char *ico ) {
	int result = 0;
	HANDLE icofile = CreateFile
		(ico,GENERIC_READ,0
		,NULL,OPEN_EXISTING
		,FILE_ATTRIBUTE_NORMAL,NULL
		);
	if (icofile!=INVALID_HANDLE_VALUE) {
		DWORD icoread = 0;
		DWORD icosize = GetFileSize(icofile,NULL);
		void *icodata = malloc(icosize);
		ReadFile(icofile,icodata,icosize,&icoread,NULL);
		if (icosize == icoread) {
			HANDLE exefile = BeginUpdateResource(exe, FALSE);
			if (exefile!=NULL) {
				if (UpdateResource
						(exefile,RT_ICON,MAKEINTRESOURCE(1)
						,MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
						,icodata,icosize)) 
				{
					result = 1;
				}
				EndUpdateResource(exefile,FALSE);
			} 
		}
		free(icodata);		
		CloseHandle(icofile);
	}
	return result;
}