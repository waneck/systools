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
#ifdef CARBON
#include <Carbon/Carbon.h>
#else
#include <Cocoa/Cocoa.h>
#endif

#define PATH_SIZE 2048

// helpers:
#if CARBON
static Boolean filterProc(AEDesc * theItem, void * info, void * callBackUD, NavFilterModes filterMode);
static OSStatus GetFSRefFromAEDesc( FSRef *fsRef, AEDesc* theItem );
#endif

// main:

void systools_dialogs_message_box( const char *title, const char *message, int error ) {
#ifdef CARBON
	CFOptionFlags result;
	CFUserNotificationDisplayAlert
		( 0, error? 0 : kCFUserNotificationCautionAlertLevel
		, 0, 0, 0
		, CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8)
		, CFStringCreateWithCString(NULL,message,kCFStringEncodingUTF8)
		, 0, 0, 0
		, &result );
#else
	NSAlert *alert = [[NSAlert alloc] init];
	[alert setMessageText:[NSString stringWithUTF8String:title]];
	[alert setInformativeText:[NSString stringWithUTF8String:message]];
	[alert runModal];
#endif
}

int systools_dialogs_dialog_box( const char *title, const char *message, int error ) {
#ifdef CARBON
	CFOptionFlags result;
	CFUserNotificationDisplayAlert
		( 0,  error? 0 : kCFUserNotificationCautionAlertLevel
		, 0, 0, 0
		, CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8)
		, CFStringCreateWithCString(NULL,message,kCFStringEncodingUTF8)
		, CFSTR("Yes"), CFSTR("No"), 0
		, &result );

	return kCFUserNotificationDefaultResponse == result ? 1 : 0;
#else
	NSAlert *alert = [[NSAlert alloc] init];
	[alert setMessageText:[NSString stringWithUTF8String:title]];
	[alert setInformativeText:[NSString stringWithUTF8String:message]];
	[alert addButtonWithTitle:@"OK"];
	[alert addButtonWithTitle:@"Cancel"];
	return [alert runModal] == NSAlertFirstButtonReturn ? 1 : 0;
#endif
}

char* systools_dialogs_save_file( const char *title, const char* msg, const char *initialdir, struct ARG_FILEFILTERS *filters ) {
#ifdef CARBON
	char *result = NULL;
	NavDialogRef ref;
	NavDialogCreationOptions opt;

	NavGetDefaultDialogCreationOptions(&opt);
	opt.clientName = CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8);
	opt.message = CFStringCreateWithCString(NULL,msg,kCFStringEncodingUTF8);
	opt.modality = kWindowModalityAppModal;

	if (NavCreatePutFileDialog(&opt,0,kNavGenericSignature,NULL,NULL,&ref) == noErr) {

		if (NavDialogRun(ref) == noErr) {
			if (NavDialogGetUserAction(ref) == kNavUserActionSaveAs) {
				NavReplyRecord reply;
				if (NavDialogGetReply(ref,&reply)  == kNavNormalState) {
					FSRef fsref;
					result = malloc(PATH_SIZE);
					memset(result,0,PATH_SIZE);
					GetFSRefFromAEDesc(&fsref,&reply.selection);
					if (FSRefMakePath (&fsref,(UInt8*)result,PATH_SIZE)==noErr) {
						strcat(result,"/");
						CFStringGetCString(reply.saveFileName,result+strlen(result),PATH_SIZE-strlen(result),kCFStringEncodingUTF8);
					} else {
						free(result);
						result = NULL;
					}
					NavDisposeReply(&reply);
				}
			}
		}
		NavDialogDispose(ref);
	}
	return result;
#else
	NSSavePanel *savePanel = [NSSavePanel savePanel];
	[savePanel setTitle:[NSString stringWithUTF8String:title]];
	[savePanel setMessage:[NSString stringWithUTF8String:msg]];
	[savePanel setDirectoryURL:[NSURL fileURLWithFileSystemRepresentation:initialdir isDirectory:YES relativeToURL:nil]];

	if (filters)
	{
		NSMutableArray *nsFilters = [[NSMutableArray alloc] init];
		for (int i = 0; i < filters->count; i++)
		{
			NSString *extension = [[NSString stringWithUTF8String:filters->extensions[i]] pathExtension];
			[nsFilters addObject:extension];
		}
		[savePanel setAllowedFileTypes:[NSArray arrayWithArray:nsFilters]];
	}

	if ([savePanel runModal] == NSOKButton)
	{
		NSString *path = [[savePanel URL] path];
		if (path)
		{
			char *result = malloc([path length]);
			strcpy(result, [path UTF8String]);
			return result;
		}
	}
	return 0;
#endif
}

void systools_dialogs_open_file( const char *title, const char *msg, struct ARG_FILEFILTERS *filters, struct RES_STRINGLIST *result) {
#ifdef CARBON
	result->count = 0;
	result->strings = NULL;
	NavDialogRef ref;
	NavDialogCreationOptions opt;

	NavGetDefaultDialogCreationOptions(&opt);
	opt.clientName = CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8);
	opt.message = CFStringCreateWithCString(NULL,msg,kCFStringEncodingUTF8);
	opt.modality = kWindowModalityAppModal;

	if (NavCreateGetFileDialog(&opt,NULL,NULL,NULL,filterProc,filters,&ref) == noErr) {

		if (NavDialogRun(ref) == noErr) {
			if (NavDialogGetUserAction(ref)==kNavUserActionOpen) {
				NavReplyRecord reply;
				if (NavDialogGetReply(ref,&reply) == kNavNormalState) {
					long count;
					AEKeyword keyword;
					DescType type;
					Size size;

					AECountItems(&reply.selection, &count);
					if (count) {
						result->count = count;
						result->strings = malloc(count*sizeof(char*));
						while(count>0) {
							count--;
							AEGetNthPtr(&reply.selection,count+1,typeFileURL,&keyword,&type,0,0,&size);
							result->strings[count] = malloc(size);
							AEGetNthPtr(&reply.selection,count+1,typeFileURL,&keyword,&type,result->strings[count],size,&size);
							result->strings[count][size]=0;
							if(strncmp(result->strings[count], "file://localhost", 16) == 0) {
								memmove(result->strings[count],result->strings[count]+16,size-16);
								result->strings[count][size-16]=0;
							}
						}
					}
					NavDisposeReply(&reply);
				}
			}
		}
		NavDialogDispose(ref);
	}
#else
	NSOpenPanel *openPanel = [[NSOpenPanel alloc] init];
	[openPanel setTitle:[NSString stringWithUTF8String:title]];
	[openPanel setMessage:[NSString stringWithUTF8String:msg]];

	if (filters)
	{
		NSMutableArray *nsFilters = [[NSMutableArray alloc] init];
		for (int i = 0; i < filters->count; i++)
		{
			NSString *extension = [[NSString stringWithUTF8String:filters->extensions[i]] pathExtension];
			[nsFilters addObject:extension];
		}
		[openPanel setAllowedFileTypes:[NSArray arrayWithArray:nsFilters]];
	}

	if ([openPanel runModal] == NSOKButton) {
		result->count = [openPanel.URLs count];
		int count = result->count;
		result->strings = malloc(count*sizeof(char*));
		while (count) {
			count--;
			NSString *path = [[openPanel.URLs objectAtIndex:count] path];
			if (path) {
				result->strings[count] = malloc([path length]);
				strcpy(result->strings[count], [path UTF8String]);
			} else {
				result->strings[count] = 0;
			}
		}
	} else {
		result->count = 0;
	}
#endif
}

char* systools_dialogs_folder( const char *title, const char *msg ) {
#ifdef CARBON
	char *result = NULL;
	NavDialogRef ref;
	NavDialogCreationOptions opt;

	NavGetDefaultDialogCreationOptions(&opt);
	opt.clientName = CFStringCreateWithCString(NULL,title,kCFStringEncodingUTF8);
	opt.message = CFStringCreateWithCString(NULL,msg,kCFStringEncodingUTF8);
	opt.modality = kWindowModalityAppModal;

	if (NavCreateChooseFolderDialog(&opt,NULL,NULL,NULL,&ref) == noErr) {

		if (NavDialogRun(ref) == noErr) {
			NavUserAction action = NavDialogGetUserAction(ref);
			if ( action != kNavUserActionCancel && action != kNavUserActionNone) {
				NavReplyRecord reply;
				if (NavDialogGetReply(ref,&reply)  == kNavNormalState) {
					AEKeyword keyword;
					AEDesc desc;
					FSRef fsref;

					AEGetNthDesc(&reply.selection, 1, typeFSRef, &keyword, &desc);

					result = malloc(PATH_SIZE);
					memset(result,0,PATH_SIZE);
					GetFSRefFromAEDesc(&fsref,&reply.selection);
					if (FSRefMakePath (&fsref,(UInt8*)result,PATH_SIZE)!=noErr) {
						free(result);
						result = NULL;
					}
					NavDisposeReply(&reply);
				}
			}
		}
		NavDialogDispose(ref);
	}
	return result;
#else
	NSOpenPanel *openPanel = [[NSOpenPanel alloc] init];
	[openPanel setTitle:[NSString stringWithUTF8String:title]];
	[openPanel setMessage:[NSString stringWithUTF8String:msg]];
	[openPanel setCanChooseFiles:NO];
	[openPanel setCanChooseDirectories:YES];

	if ([openPanel runModal] == NSOKButton) {
		NSString *path = [[openPanel.URLs objectAtIndex:0] path];
		if (path) {
			char *result = malloc([path length]);
			strcpy(result, [path UTF8String]);
			return result;
		}
	}
	return 0;
#endif
}

// helpers:
#ifdef CARBON
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
	if (!filters)
		return 1;

	NavFileOrFolderInfo *i = (NavFileOrFolderInfo*) info;
	if (i->isFolder)
		return 1;

	if (theItem->descriptorType==typeFSRef) {
		FSRef f;
		UInt8 path[PATH_SIZE];

		GetFSRefFromAEDesc(&f,theItem);
		if (FSRefMakePath (&f,path,PATH_SIZE)==noErr) {
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
#endif

