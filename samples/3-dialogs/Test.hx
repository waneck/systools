import systools.Dialogs;

class Test {
		
	static function main() {
		Dialogs.message("neko-systools","Hello World!",false);
		Dialogs.confirm("neko-systools","Please confirm?",false);
		Dialogs.message("neko-systools","Message error test", true);
		Dialogs.message("neko-systools","Confirm error test", true);
	}
}
