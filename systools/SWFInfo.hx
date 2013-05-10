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
package systools;

import neko.FileSystem;
import neko.io.File;
import neko.io.FileInput;
import neko.io.StringInput;

class SWFInfo
{
	public var width:Int;
	public var height:Int;
	public var version:Int;
	public var frameRate:Float;
	public var totalFrames:Int;
	
	/** Creates a new SWFInfo object and reads in the header of the file.
	* Note if it's a compressed file, the entire file has to be read in.
	* This only works for local files, not URLs
	*/
	public function new(file:String)
	{
		if (!FileSystem.exists(file))
			throw "SWFInfo: Can't find SWF file '"+file+"'";
			
		var f:FileInput=File.read(file,true);
		var magic:String=f.read(3);
		if ((magic!="FWS")&&(magic!="CWS"))
			throw "SWFInfo: Not a SWF file '"+file+"'";
			
		version=f.readChar();	// SWF Version
		f.read(4);	// Skip file length
		
		// If it's a compressed file, we'll need to decompress
		var buffer:String;
		if (magic=="CWS")
			buffer=neko.zip.Uncompress.run(f.readAll());	// Got to decompress the file *sigh*
		else
			buffer=f.read(24); // Should be plenty
		
		// Can close the file now	
		f.close();
					
		// Rect structure consists of a 5-bit size for the fields, followed by 4 fields of that size
		var b:Int=readBits(buffer,0,5);	// Read the number of bits allocated to each rect entry
		var rectXMin:Int=readBits(buffer,5,b);
		var rectXMax:Int=readBits(buffer,5+b,b);
		var rectYMin:Int=readBits(buffer,5+b*2,b);
		var rectYMax:Int=readBits(buffer,5+b*3,b);
		
		width=Std.int((rectXMax-rectXMin)/20); // Convert from Twips
		height=Std.int((rectYMax-rectYMin)/20); // Convert from Twips
		
		// Now having done odd bit-field stuff, realign
		var rectLength:Int=Std.int((5+b*4)/8)+1; // That's how many chars the rect was stored in
		
		// Start a new input stream (so we can use it's methods)
		var input:StringInput=new StringInput(buffer,rectLength);
		
		// Frame rate stored as fixed point 8.8 (little-endian)
		var lsb:Int=input.readInt8();
		var msb:Int=input.readInt8();
		frameRate=Std.parseFloat(msb+"."+lsb);
		
		// Total frames - nice simply 2-byte value
		totalFrames=input.readInt16();
	}
	
	// Extracts arbitrary-bit-length values from a string buffer starting at a particular pos (in bits)
	private function readBits(buffer:String,pos:Int,count:Int):Int
	{
		var loop:Int=pos;
		var result:Int=0;
		while(loop<pos+count)
		{
			if ((1<<(7-loop%8))&(buffer.charCodeAt(Std.int(loop/8)))!=0)
				result+=(1 << (count-(1+loop-pos)));
			loop++;
		}
		return result;
	}
}