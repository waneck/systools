import systools.Dialogs;
import systools.win.Tools;

class Test {
		
	static function main() {		
		var exefilter: FILEFILTERS = 
			{ count: 1
			, descriptions: ["executables"]
			, extensions: ["*.exe"]			
			};			
		var icofilter: FILEFILTERS = 
			{ count: 1
			, descriptions: ["icons"]
			, extensions: ["*.ico"]			
			};	
		
		// collect exe target file:	
		var exefile = Dialogs.openFile("Select file","",exefilter);			
		if (exefile==null) {
			trace("No executable file selected");
			return;
		}
		
		// collect ico source file:
		var icofile = Dialogs.openFile("Select a new icon file","ignore",icofilter);
		if (icofile==null) {
			trace("No icon file selected");
			return;
		}
		
		// replace icon:
		if (systools.win.Tools.replaceExeIcon(exefile[0],icofile[0]))
			trace("Successfully replaced "+exefile[0]+"'s icon.");
		else	
			trace("Failed to replace "+exefile[0]+"'s icon.");
	}
}
