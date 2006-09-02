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

#include "dialogs.h"
#include <Carbon/Carbon.h>

void systools_dialogs_message_box( const char *title, const char *message, int error ) {
	CFOptionFlags result;
	CFUserNotificationDisplayAlert
		( 0, error? 0 : kCFUserNotificationCautionAlertLevel
		, 0, 0, 0
		, CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8)
		, CFStringCreateWithCString(NULL,message,kCFStringEncodingUTF8)
		, 0, 0, 0 
		, &result );			
}

int systools_dialogs_dialog_box( const char *title, const char *message, int error ) {
	CFOptionFlags result;
	CFUserNotificationDisplayAlert
		( 0,  error? 0 : kCFUserNotificationCautionAlertLevel
		, 0, 0, 0
		, CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8)
		, CFStringCreateWithCString(NULL,message,kCFStringEncodingUTF8)
		, CFSTR("Yes"), CFSTR("No"), 0 
		, &result );
		
	return kCFUserNotificationDefaultResponse == result ? 1 : 0;
}


static OSStatus GetFSRefFromAEDesc( FSRef *fsRef, AEDesc* theItem ) {
	OSStatus err = noErr;
	AEDesc coerceDesc= { 0, NULL };	
	if ( theItem->descriptorType != typeFSRef )	{
		err = AECoerceDesc( theItem, typeFSRef, &coerceDesc );
		if ( err == noErr )
		theItem = &coerceDesc;
	}	
	if ( err == noErr )
	err = AEGetDescData( theItem, fsRef, sizeof(*fsRef) );
	AEDisposeDesc( &coerceDesc );
	
	if ( err != noErr )	{
		FSSpec fsSpec;
		AEDesc coerceDesc2 = {0, NULL};
		if ( theItem->descriptorType != typeFSS ) {
			err = AECoerceDesc( theItem, typeFSS, &coerceDesc2 );
			theItem = &coerceDesc2;
		}	
		if ( err == noErr )
		err = AEGetDescData( theItem, &fsSpec, sizeof(fsSpec) );
		AEDisposeDesc( &coerceDesc2 );
		if ( err == noErr )
		err = FSpMakeFSRef( &fsSpec, fsRef );
	}
	return(err);
}

static Boolean filterProc(AEDesc * theItem, void * info, void * callBackUD, NavFilterModes filterMode) {
	struct ARG_FILEFILTERS *filters = (struct ARG_FILEFILTERS *) callBackUD;
	NavFileOrFolderInfo *i = (NavFileOrFolderInfo*) info;
	if (i->isFolder) 
		return 1;
	
	if (theItem->descriptorType==typeFSRef) {
		FSRef f;
		UInt8 path[2048];
		
		GetFSRefFromAEDesc(&f,theItem);
		if (FSRefMakePath (&f,path,2048)==noErr) {			
			char *ext = NULL;
			char *next = (char*) path;
			while(next) {
				next = strstr(next,".");				
				if (next) 
					ext = ++next;					
			}
			if(ext) {
				long j = filters->count;
				while(j) {
					if (strcasestr(filters->extensions[--j],ext) !=0) 
						return 1;
				}
			}
		}
		return 0;		
	}
	return 1;	
}

void systools_dialogs_open_file( const char *title, const char *msg, struct ARG_FILEFILTERS *filters, struct RES_STRINGLIST *result) {
	result->count = 0;
	result->strings = NULL;
	NavDialogRef ref;
	NavDialogCreationOptions opt;
							
	NavGetDefaultDialogCreationOptions(&opt);		
	opt.clientName = CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8);
	opt.message = CFStringCreateWithCString(NULL,msg,kCFStringEncodingUTF8);
	opt.modality = kWindowModalityAppModal;
	
	printf("dialogs-open-file");
	
	if (filters) {			
		long i = filters->count;		
		while(i){
			i--;			
		}			
	}
		
	if (NavCreateGetFileDialog(&opt,NULL,NULL,NULL,filterProc,filters,&ref) == noErr) {
				
		if (NavDialogRun(ref) == noErr) {
			if (NavDialogGetUserAction(ref)==kNavUserActionOpen) {
				NavReplyRecord reply;
				if (NavDialogGetReply(ref,&reply)) {
					long count;
					AEKeyword keyword;
					DescType type;					
					Size size;
					
					AECountItems(&reply.selection, &count);
					if (count) {
						result->count = count;
						result->strings = malloc(count*sizeof(char*));
						while(count>0) {
							AEGetNthPtr(&reply.selection,count+1,typeFileURL,&keyword,&type,0,0,&size);
							result->strings[count] = malloc(size);
							AEGetNthPtr(&reply.selection,count+1,typeFileURL,&keyword,&type,result->strings[count],size,&size);
						}
					}	
					NavDisposeReply(&reply);
				}
			}
		}
	}	
}


