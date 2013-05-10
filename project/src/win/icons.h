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

/* 
 * Based on: 
 * http://www.koders.com/c/fidFB995E4CBABD7E2D87CD5C771C59EBF4EBB5B803.aspx 
 * Copyright: (c) 2000, 2001, 2002, 2003 Thomas Heller 
 */

/*
 * Ref for the icon code, from MSDN:
 *   Icons in Win32
 *   John Hornick 
 *   Microsoft Corporation
 *     Created: September 29, 1995
 */

#pragma pack(2)

/* Structure of .ico files */

typedef struct {
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD wPlanes;
    WORD wBitCount;
    DWORD dwBytesInRes;
    DWORD dwImageOffset;
} ICONDIRENTRY;

typedef struct {
    WORD idReserved; /* Must be 0 */
    WORD idType; /* Should check that this is 1 for icons */
    WORD idCount; /* Number os ICONDIRENTRYs to follow */
    ICONDIRENTRY idEntries[0];
} ICONDIRHEADER;

/* Format of RT_GROUP_ICON resources */

typedef struct {
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD wPlanes;
    WORD wBitCount;
    DWORD dwBytesInRes;
    WORD nID;
} GRPICONDIRENTRY;

typedef struct {
    WORD idReserved;
    WORD idType;
    WORD idCount;
    GRPICONDIRENTRY idEntries[0];
} GRPICONDIRHEADER;

#pragma pack()

/*
 * Map a file into memory for reading.
 *
 * Pointer returned must be freed with UnmapViewOfFile().
 */
static char *MapExistingFile (const char*path, DWORD *psize)
{
    HANDLE hFile, hFileMapping;
    DWORD nSizeLow, nSizeHigh;
    char *data;
    
    hFile = CreateFile
			( path,GENERIC_READ, FILE_SHARE_READ, NULL
			, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
			);
    if (hFile == INVALID_HANDLE_VALUE)
		return NULL;
    nSizeLow = GetFileSize(hFile, &nSizeHigh);
    hFileMapping = CreateFileMapping(hFile,
				     NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle (hFile);

    if (hFileMapping == INVALID_HANDLE_VALUE)
		return NULL;
    
    data = MapViewOfFile(hFileMapping,FILE_MAP_READ, 0, 0, 0);

    CloseHandle(hFileMapping);
    *psize = nSizeLow;
    return data;
}

/*
 * Create a GRPICONDIRHEADER from an ICONDIRHEADER.
 *
 * Returns malloc()'d memory.
 */
static GRPICONDIRHEADER *CreateGrpIconDirHeader(ICONDIRHEADER *pidh, int icoid)
{
    GRPICONDIRHEADER *pgidh;
    size_t size;
    int i;

    size = sizeof(GRPICONDIRHEADER) + sizeof(GRPICONDIRENTRY) * pidh->idCount;
    pgidh = (GRPICONDIRHEADER *)malloc(size);
    pgidh->idReserved = pidh->idReserved;
    pgidh->idType = pidh->idType;
    pgidh->idCount = pidh->idCount;

    for (i = 0; i < pidh->idCount; ++i) {
	pgidh->idEntries[i].bWidth = pidh->idEntries[i].bWidth;
	pgidh->idEntries[i].bHeight = pidh->idEntries[i].bHeight;
	pgidh->idEntries[i].bColorCount = pidh->idEntries[i].bColorCount;
	pgidh->idEntries[i].bReserved = pidh->idEntries[i].bReserved;
	pgidh->idEntries[i].wPlanes = pidh->idEntries[i].wPlanes;
	pgidh->idEntries[i].wBitCount = pidh->idEntries[i].wBitCount;
	pgidh->idEntries[i].dwBytesInRes = pidh->idEntries[i].dwBytesInRes;
	pgidh->idEntries[i].nID = icoid + i ;
    }
    return pgidh;
}