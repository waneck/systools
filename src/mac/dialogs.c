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

void systools_dialogs_open_file( const char *title, const char *msg, struct ARG_FILEFILTERS *filters, struct RES_STRINGLIST *result) {
	result->count = 0;
	result->strings = NULL;
	NavDialogRef ref;
	NavDialogCreationOptions opt;
	NavTypeListPtr ntl;
						
	NavGetDefaultDialogCreationOptions(&opt);		
	opt.clientName = CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8);
	opt.message = CFStringCreateWithCString(NULL,msg,kCFStringEncodingUTF8);
	opt.modality = kWindowModalityAppModal;
		
	if (NavCreateGetFileDialog(&opt,NULL,NULL,NULL,NULL,NULL,&ref) == noErr) {
	
		if (filters) {			
			CFMutableArrayRef array = CFArrayCreateMutable(NULL,0,(CFArrayCallBacks*) kCFTypeArrayCallBacks);
			long i = filters->count;
			while(i){
				//CFStringRef ext = CFStringCreateWithCString(NULL,filters->mactypes[--i], kCFStringEncodingUTF8);
				//CFStringRef type= CFStringCreateWithCString(NULL,filters->mactypes[i], kCFStringEncodingUTF8);
				//CFArrayAppendValue(array,ext);
				//CFArrayAppendValue(array,type);
				CFArrayAppendValue(array,CFSTR("public.plain-text"));
			}			
			NavDialogSetFilterTypeIdentifiers(ref,array);
		}
	
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
	
	if (filters) free(ntl);		
}