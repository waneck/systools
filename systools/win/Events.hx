/*
 * Copyright (c) 2006, Edwin van Rijkom, Nicolas Cannasse, Lee McColl-Sylvester
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
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

class Events {
	public static var TRAYEVENT						= 0x2329;
	public static var COMMAND						= 0x0111;
	public static var RBUTTONUP						= 0x0204;
	public static var LBUTTONUP						= 0x0205;

	public static var CREATE						= 0x0001;
	public static var DESTROY						= 0x0002;
	public static var MOVE							= 0x0003;
	public static var SIZE							= 0x0005;
	public static var ACTIVATE						= 0x0006;
	public static var SETFOCUS						= 0x0007;
	public static var KILLFOCUS						= 0x0008;
	public static var ENABLE						= 0x000A;
	public static var PAINT							= 0x000F;
	public static var CLOSE							= 0x0010;
	public static var QUIT							= 0x0012;
	public static var SHOWWINDOW					= 0x0018;
	public static var MOUSEACTIVATE					= 0x0021;
	public static var WINDOWPOSCHANGING				= 0x0046;
	public static var WINDOWPOSCHANGED				= 0x0047;
	public static var CONTEXTMENU					= 0x007B;
	public static var DISPLAYCHANGE					= 0x007E;
	public static var NCCREATE						= 0x0081;
	public static var NCDESTROY						= 0x0082;
	public static var NCCALCSIZE					= 0x0083;
	public static var NCHITTEST						= 0x0084;
	public static var NCPAINT						= 0x0085;
	public static var NCACTIVATE					= 0x0086;
	public static var NCMOUSEMOVE					= 0x00A0;
	public static var NCLBUTTONDOWN					= 0x00A1;
	public static var NCLBUTTONUP					= 0x00A2;
	public static var NCLBUTTONDBLCLK				= 0x00A3;
	public static var NCRBUTTONDOWN					= 0x00A4;
	public static var NCRBUTTONUP					= 0x00A5;
	public static var NCRBUTTONDBLCLK				= 0x00A6;
	public static var NCMBUTTONDOWN					= 0x00A7;
	public static var NCMBUTTONUP					= 0x00A8;
	public static var NCMBUTTONDBLCLK				= 0x00A9;
	public static var NCXBUTTONDOWN					= 0x00AB;
	public static var NCXBUTTONUP					= 0x00AC;
	public static var NCXBUTTONDBLCLK				= 0x00AD;
	public static var KEYDOWN						= 0x0100;
	public static var KEYUP							= 0x0101;
	public static var SYSKEYDOWN					= 0x0104;
	public static var SYSKEYUP						= 0x0105;
	public static var INITDIALOG					= 0x0110;
	public static var INITMENU						= 0x0116;
	public static var INITMENUPOPUP					= 0x0117;
	public static var MENUSELECT					= 0x011F;
	public static var MENUCHAR						= 0x0120;
	public static var ENTERIDLE						= 0x0121;
	public static var MENURBUTTONUP					= 0x0122;
	public static var MENUDRAG						= 0x0123;
	public static var MENUGETOBJECT					= 0x0124;
	public static var UNINITMENUPOPUP				= 0x0125;
	public static var MENUCOMMAND					= 0x0126;
	public static var MOUSEFIRST					= 0x0200;
	public static var MOUSEMOVE						= 0x0200;
	public static var LBUTTONDOWN					= 0x0201;
	public static var LBUTTONDBLCLK					= 0x0203;
	public static var RBUTTONDOWN					= 0x0204;
	public static var RBUTTONDBLCLK					= 0x0206;
	public static var MBUTTONDOWN					= 0x0207;
	public static var MBUTTONUP						= 0x0208;
	public static var MBUTTONDBLCLK					= 0x0209;
	public static var XBUTTONDOWN					= 0x020B;
	public static var XBUTTONUP						= 0x020C;
	public static var XBUTTONDBLCLK					= 0x020D;
	public static var ENTERMENULOOP					= 0x0211;
	public static var EXITMENULOOP					= 0x0212;
	public static var SIZING						= 0x0214;
	public static var CAPTURECHANGED				= 0x0215;
	public static var MOVING						= 0x0216;
	public static var ENTERSIZEMOVE					= 0x0231;
	public static var EXITSIZEMOVE					= 0x0232;
	public static var DROPFILES						= 0x0233;
	public static var MOUSEHOVER					= 0x02A1;
	public static var MOUSELEAVE					= 0x02A3;
	public static var NCMOUSEHOVER					= 0x02A0;
	public static var NCMOUSELEAVE					= 0x02A2;
	public static var CUT							= 0x0300;
	public static var COPY							= 0x0301;
	public static var PASTE							= 0x0302;
	public static var CLEAR							= 0x0303;
	public static var UNDO							= 0x0304;
}