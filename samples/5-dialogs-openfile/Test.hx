import systools.Dialogs;

class Test {
		
	static function main() {
		var filters: FILEFILTERS = 
			{ count: 2
			, descriptions: ["Text files", "JPEG files"]
			, extensions: ["*.txt","*.jpg;*.jpeg"]			
			};		
		var result = Dialogs.openFile
			( "Select a file please!"
			, "Please select one or more files, so we can see if this method works"
			, filters 
			);
		trace(result);		
	}
}
