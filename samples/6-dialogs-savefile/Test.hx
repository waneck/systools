import systools.Dialogs;

class Test {
		
	static function main() {
		var result = Dialogs.saveFile
			( "Select a file please, or type name"
			, "This additional message will only be shown on OSX"
			, "c:/" // initial path, for windows only
			);
		trace(result);		
	}
}
