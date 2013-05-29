/*
 * Copyright (c) 2006,
 * Asger Ottar Alstrup, Edwin van Rijkom, Nicolas Cannasse
 * All rights reserved.
 *
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

class Registry {

	/**
	 * HKEY_xxx_xxx values ignored on MacOS
	 */
	static public var HKEY_CLASSES_ROOT = 0;
	static public var HKEY_CURRENT_USER = 1;
	static public var HKEY_LOCAL_MACHINE = 2;
	static public var HKEY_USERS = 3;
	static public var HKEY_PERFORMANCE_DATA = 4;
	static public var HKEY_CURRENT_CONFIG = 5;
	static public var HKEY_DYN_DATA = 6;

	/**
	 * Set a value in the registry. If it does not exist, it is created first.
	 */
	static public function setValue( key : Int, subKey : String, valuename : String, value : String) : Void {
		_set_value( key, subKey, valuename, value);
	}

	/**
	 * Get the value of a key in registry.
	 */
	static public function getValue( key : Int, subKey : String, valuename : String ) : String {
		return _get_value( key, subKey, valuename);
	}

	static public function deleteKey( key : Int, subKey : String) : Void {
		_delete_key( key, subKey);
	}

	static var _set_value = systools.Loader.load("systools","registry_set_value", 4);
	static var _get_value = systools.Loader.load("systools","registry_get_value", 3);
	static var _delete_key = systools.Loader.load("systools","registry_delete_key", 2);
}
