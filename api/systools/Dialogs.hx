/*
 * Copyright (c) 2006, Edwin van Rijkom, Nicolas Cannasse
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

package systools;

typedef FILEFILTERS = {
	var count: Int;
	var descriptions: Array<String>;
	var extensions: Array<String>;
}

class Dialogs {
	
	static var _message_box = neko.Lib.load("systools","dialogs_message_box",3);
	public static function message( title : String, msg : String, isError : Bool ) {
		_message_box(untyped title.__s,untyped msg.__s,isError);
	}
	
	static var _dialog_box = neko.Lib.load("systools","dialogs_dialog_box",3);
	public static function confirm( title : String, msg : String, isError : Bool ) : Bool {
		return _dialog_box(untyped title.__s,untyped msg.__s,isError);
	}
	
	static var _dialog_save_file = neko.Lib.load("systools","dialogs_save_file",2);
	public static function saveFile( title : String, initialDir : String ) : String {
		return _dialog_save_file(untyped title.__s,untyped initialDir.__s );
	}
	
	static var _open_file = neko.Lib.load("systools","dialogs_open_file",3);
	public static function openFile( title : String, msg : String, mask : FILEFILTERS ) : Array<String> {
		var result = _open_file(untyped title.__s,untyped msg.__s,untyped __dollar__new(mask));
		if (result == null) 
			return null;
		else {
			var a : Array<String> = untyped Array.new1(result,__dollar__asize(result));
			for( i in 0...a.length ) a[i] = new String(a[i]);
			return a;
		}	
	}	
}
