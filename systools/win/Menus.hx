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

class Menus {
	var m : Void;

	public function new( isPopup : Bool )
	{
		if ( isPopup )
			m = _win_popup_menu_create();
		else
			m = _win_menu_create();
	}

	public function dispose()
	{
		_win_destroy_menu( m );
	}

	public function addItem( caption : String, msgid : Int ) : Void
	{
		_win_add_menu_item( m, caption, msgid );
	}

	public function addDivider( msgid : Int ) : Void
	{
		_win_add_menu_divider( m, msgid );
	}

	public function addSubmenu( menu : Menus, caption : String, msgid : Int ) : Void
	{
		_win_add_menu_submenu( m, menu.getHandle(), caption, msgid );
	}

	public function show( hwnd : Void )
	{
		return _win_show_menu( hwnd, m );
	}

	public function showPopup( hwnd : Void )
	{
		return _win_show_popup_menu( hwnd, m );
	}

	public function getHandle() : Dynamic
	{
		return m;
	}

	static var _win_menu_create = systools.Loader.load("systools", "win_menu_create", 0);
	static var _win_popup_menu_create = systools.Loader.load("systools", "win_popup_menu_create", 0);
	static var _win_destroy_menu = systools.Loader.load("systools","win_destroy_menu",1);
	static var _win_add_menu_item = systools.Loader.load("systools","win_add_menu_item",3);
	static var _win_add_menu_submenu = systools.Loader.load("systools", "win_add_menu_submenu", 4);
	static var _win_add_menu_divider = systools.Loader.load("systools","win_add_menu_divider",2);
	static var _win_show_menu = systools.Loader.load("systools","win_show_menu",2);
	static var _win_show_popup_menu = systools.Loader.load("systools","win_show_popup_menu",2);
}
