import systools.Dialogs;

class Test {
		
	static function main() {
		var result = Dialogs.folder
			( "Select a folder"
			, "This additional message will only be shown on OSX"			
			);
		trace(result);		
	}
}
