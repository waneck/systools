/*
 * Copyright (c) 2006, Edwin van Rijkom, Nicolas Cannasse, Lee McColl-Sylvester
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

package systools.win;

import systools.win.Events;

class Tray {
	
	var t : Void;
	var window : swhx.Window;
	public var hook : swhx.MessageHook;
	public var param1(getParam1,null) : Dynamic;
	public var param2(getParam2,null) : Dynamic;
	
	public function new( ico : Void, hw : swhx.Window )
	{
		untyped t = ico;
		window = hw;
	}
	
	public function getParam1() : Dynamic
	{
		return hook.p1;
	}
	
	public function getParam2() : Dynamic
	{
		return hook.p2;
	}

	public function setTrayEvent( evtHandler : Void->Int )
	{
		hook = window.addMessageHook( untyped 0x200 );  // untyped Events.TRAYEVENT
    	//hook.setNekoCallback(evtHandler);
	}
	
	static var _systray_destroy_icon = neko.Lib.load("systools","systray_destroy_icon",1);
	public function dispose() {
		return _systray_destroy_icon(t);
	}
	
	static var _systray_create_icon = neko.Lib.load("systools","systray_create_icon",3);
	public static function createTrayIcon( wnd : swhx.Window, iconPath : String, tooltip : String ) {
		var t = _systray_create_icon(untyped wnd.handle,untyped iconPath.__s,untyped tooltip.__s);
		return new Tray(t,wnd);
	}
}
