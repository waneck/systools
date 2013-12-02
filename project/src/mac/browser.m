/*
 * Copyright (c) 2007, Edwin van Rijkom, Nicolas Cannasse, Lee McColl-Sylvester, Ian Thomas
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE HAXE PROJECT CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE HAXE PROJECT CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#include "../browser.h"
#if CARBON
#include <Carbon/Carbon.h>
#else
#include <Cocoa/Cocoa.h>
#endif

int systools_browser_launch( const char *url)
{
    #if CARBON
    OSStatus err;
    ICInstance inst;
	long selStart, selEnd;
    err = ICStart(&inst,'????'); // No known creator code
    if (err == noErr)
	{
		selStart=0;
		selEnd=strlen(url);
		err = ICLaunchURL(inst, "\p", url, strlen(url),&selStart,&selEnd);
        ICStop(inst);
    }
    return (err==0);
    #else
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithUTF8String:url]];
    return [[NSWorkspace sharedWorkspace] openURL:nsurl] ? 1 : 0;
    #endif
}