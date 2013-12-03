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

// debug
// #define DEBUG_REGISTRY

// helper macro
#ifdef CARBON

#import <Carbon/Carbon.h>

#define CONVERT_APP\
	CFMutableStringRef app = CFStringCreateMutableCopy(NULL,0,CFStringCreateWithCString(NULL,subkey,kCFStringEncodingUTF8));\
	CFRange range = CFRangeMake(0,CFStringGetLength(app));\
	CFStringFindAndReplace(app,CFSTR("\\"),CFSTR("."),range,0);\

void systools_registry_set_value(int _, const char *subkey, const char *valuename, const char *value) {
	CONVERT_APP;

#ifdef DEBUG_REGISTRY
	char capp[1024];
	CFStringGetCString(app,capp,1024,kCFStringEncodingUTF8);
	printf("set: (%s - %s)\n[%s]\n",subkey,valuename,capp);
#endif

	if (strlen(valuename)) {
		CFStringRef key = CFStringCreateWithCString(0,valuename,kCFStringEncodingUTF8);
		CFPreferencesSetAppValue
			( key
			, strlen(value)? CFStringCreateWithCString(0,value,kCFStringEncodingUTF8) : CFSTR("")
			, app);
		CFPreferencesAppSynchronize(app);
	}
}

char * systools_registry_get_value( int _, const char *subkey, const char *valuename ) {
	char *result = NULL;
	CONVERT_APP;
	CFPreferencesAppSynchronize(app);

#ifdef DEBUG_REGISTRY
	char capp[1024];
	CFStringGetCString(app,capp,1024,kCFStringEncodingUTF8);
	printf("get: (%s - %s)\n[%s]\n",subkey,valuename,capp);
#endif

	if (strlen(valuename)) {
		CFStringRef key = CFStringCreateWithCString(NULL,valuename,kCFStringEncodingUTF8);
		CFPropertyListRef property = CFPreferencesCopyAppValue(key,app);

		if (property && CFGetTypeID(property) == CFGetTypeID(CFSTR(""))) {
			CFStringRef cfvalue = (CFStringRef) property;
			CFIndex length = CFStringGetMaximumSizeForEncoding(CFStringGetLength(cfvalue),kCFStringEncodingUTF8);
			result = malloc(length+1);
			CFStringGetCString(cfvalue,result,length,kCFStringEncodingUTF8);
			result[length] = 0;
			CFRelease(property);
		}
	}
	return result;
}

void systools_registry_delete_key( int _, const char * subkey ) {
	CONVERT_APP;
	CFIndex i = 0;
	CFPreferencesAppSynchronize(app);

#ifdef DEBUG_REGISTRY
	char capp[1024];
	CFStringGetCString(app,capp,1024,kCFStringEncodingUTF8);
	printf("del: (%s)\n[%s]\n",subkey,capp);
#endif

	CFArrayRef keys = CFPreferencesCopyKeyList(app,kCFPreferencesCurrentUser,kCFPreferencesAnyHost);
	if(keys) {
		while(i < CFArrayGetCount(keys)) {
			CFStringRef key = CFArrayGetValueAtIndex(keys,i);
			CFRetain(key);
			if (key) {
				char ckey[1024];
				CFStringGetCString(key,ckey,1024,kCFStringEncodingUTF8);
				CFPreferencesSetAppValue(key,NULL,app);
				i++;
			}
			CFRelease(key);
		}
		CFRelease(keys);
	}
	CFPreferencesAppSynchronize(app);
}

#else

// use Cocoa instead
#import <Cocoa/Cocoa.h>

void systools_registry_set_value(int key, const char *subkey, const char *valuename, const char *value) {
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	[userDefaults setObject:[NSString stringWithUTF8String:value] forKey:[NSString stringWithUTF8String:valuename]];
}

char *systools_registry_get_value(int key, const char *subkey, const char *valuename) {
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	NSString *obj = [userDefaults stringForKey:[NSString stringWithUTF8String:valuename]];
	char *string = malloc([obj length]);
	strcpy(string, [obj UTF8String]);
	return string;
}

void systools_registry_delete_key(int key, const char * subkey) {
	NSLog(@"Registry deletion not supported on OSX");
}

#endif