/* ************************************************************************ */
/*																			*/
/*  Systools - a Neko VM library												*/
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

#include <windows.h>
#include "win.h"
#include "icons.h"

/* 
 * Based on: 
 * http://www.koders.com/c/fidFB995E4CBABD7E2D87CD5C771C59EBF4EBB5B803.aspx 
 * Copyright: (c) 2000, 2001, 2002, 2003 Thomas Heller 
 */
int systools_win_replaceExeIcon( const char *exe, const char *ico ) {	
	/* from the .ico file */
    ICONDIRHEADER *pidh;
    WORD idh_size;
    /* for the resources */
    GRPICONDIRHEADER *pgidh = NULL;
    WORD gidh_size;
    HANDLE hUpdate = NULL;
    int i;
    char *icodata;
    DWORD icosize;
    icodata = MapExistingFile(ico, &icosize);
    if (!icodata)
        return 0;
        
    pidh = (ICONDIRHEADER *)icodata;
    idh_size = sizeof(ICONDIRHEADER) + sizeof(ICONDIRENTRY) * pidh->idCount;

    pgidh = CreateGrpIconDirHeader(pidh, 1);
    gidh_size = sizeof(GRPICONDIRHEADER) + sizeof(GRPICONDIRENTRY) * pgidh->idCount;

	hUpdate = BeginUpdateResource(exe, FALSE);
    if (!hUpdate) goto failed;
    
    if (!UpdateResource
			( hUpdate
			, MAKEINTRESOURCE(RT_GROUP_ICON)
			, MAKEINTRESOURCE(1)
			, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)
			, pgidh, gidh_size))	
		goto failed;
    
    for (i = 0; i < pidh->idCount; ++i) {
        char *cp = &icodata[pidh->idEntries[i].dwImageOffset];
        int cBytes = pidh->idEntries[i].dwBytesInRes;
        if (!UpdateResource
				( hUpdate
				, MAKEINTRESOURCE(RT_ICON)
				, MAKEINTRESOURCE(i+1)
				, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)
				, cp, cBytes))
            goto failed;        
    }

    free(pgidh);
    UnmapViewOfFile(icodata);

    if (!EndUpdateResource(hUpdate, FALSE))
        return 0;    
    return 1;

  failed:
    if (pgidh)
        free(pgidh);
    if (hUpdate)
        EndUpdateResource(hUpdate, TRUE);
    if (icodata)
        UnmapViewOfFile(icodata);
    return 0;
}