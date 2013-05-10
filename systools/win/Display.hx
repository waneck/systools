/*
 * Copyright (c) 2006, Edwin van Rijkom, Nicolas Cannasse, Lee McColl-Sylvester, Ian Thomas
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

class Display {
	/** Set the screen resolution (set temporarily - when the neko app quits the screen mode will be restored.)
		@param width Width in pixels
		@param height Height in pixels
		@param depth Bit-depth (usual is 16 or 32)
		@return true if successful
	*/
	public static function setMode(width:Int,height:Int,depth:Int):Bool
	{
		return _display_set_mode(width,height,depth);
	}
	
	/** Sets the display back to the default resolution. */
	public static function setDefaultMode():Void
	{
		_display_set_default_mode();
	}
	
	/** Check if a screen resolution is supported
		@param width Width in pixels
		@param height Height in pixels
		@param depth Bit-depth (usual is 16 or 32)
		@return true if the mode is supported, false otherwise
	*/
	public static function isModeSupported(width:Int,height:Int,depth:Int):Bool
	{
		return _display_is_mode_supported(width,height,depth);
	}
	
	/**
	Retrieves the screen dimensions of the primary device and returns as an object with the
	fields h and w for height and width respectively
	**/
	public static function getScreenSize()
	{
		return _get_screen_size();
	}

	static var _get_screen_size = systools.Loader.load("systools","display_get_screen_size",0);
	static var _display_set_mode = systools.Loader.load("systools","display_set_mode",3);
	static var _display_set_default_mode = systools.Loader.load("systools","display_set_default_mode",0);
	static var _display_is_mode_supported = systools.Loader.load("systools","display_is_mode_supported",3);
}
