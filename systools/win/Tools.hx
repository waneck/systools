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

package systools.win;

class Tools {

	/**
	Optional iconResourceID argument is the _target_ ID of the icon i.e. the resource ID that
	the supplied icon will be given in the resulting .exe. Defaults to 1 - normally
	the main icon.
	Peculiarly, the current SWHX.exe icon is at 104.
	*/
	public static function replaceExeIcon(exe: String, icon: String, ?iconResourceID: Int) : Bool {

		if (iconResourceID==null)
			iconResourceID=1;

		// Only tries to load this if called.
		if (_win_replace_exe_icon==null)
		{
			if (Sys.systemName()!="Windows")
				throw "Windows is required to run systools.win.Tools.replaceExeIcon";

			_win_replace_exe_icon=systools.Loader.load("systools","win_replace_exe_icon",3);
		}

		return if(_win_replace_exe_icon(exe, icon,iconResourceID)) true else false;
	}
	static var _win_replace_exe_icon;


	public static function createProcess( app: String, cmds: String, workingdir: String, hide: Bool, wait: Bool): Int {

		if (_win_create_process==null)
		{
			if (Sys.systemName()!="Windows")
				throw "Windows is required to run systools.win.Tools.createProcess";

			_win_create_process=systools.Loader.load("systools","win_create_process",5);
		}

		return _win_create_process
				( app
				, cmds
				, workingdir
				, if (hide) 1 else 0
				, if (wait) 1 else 0
				);
	}
	static var _win_create_process;
}
