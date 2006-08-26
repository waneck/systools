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

#include <Carbon/Carbon.h>

void systools_dialogs_message_box( const char *title, const char *message, int error ) {
	CFOptionFlags result;
	CFUserNotificationDisplayAlert
		( 0, error? 0 : kCFUserNotificationCautionAlertLevel
		, 0, 0, 0
		, CFStringCreateWithCString(0,title,kCFStringEncodingUTF8)
		, CFStringCreateWithCString(0,message,kCFStringEncodingUTF8)
		, 0, 0, 0 
		, &result );			
}

int systools_dialogs_dialog_box( const char *title, const char *message, int error ) {
	CFOptionFlags result;
	CFUserNotificationDisplayAlert
		( 0,  error? 0 : kCFUserNotificationCautionAlertLevel
		, 0, 0, 0
		, CFStringCreateWithCString(0,title,kCFStringEncodingUTF8)
		, CFStringCreateWithCString(0,message,kCFStringEncodingUTF8)
		, CFSTR("Yes"), CFSTR("No"), 0 
		, &result );
		
	return kCFUserNotificationDefaultResponse == result ? 1 : 0;
}
