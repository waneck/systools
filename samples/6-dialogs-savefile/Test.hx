import systools.Dialogs;

class Test {
		
	static function main() {
		var result = Dialogs.saveFile
			( "Select a file please, or type name"
			, "c:/"
			);
		trace(result);		
	}
}
