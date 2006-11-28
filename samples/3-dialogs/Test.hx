import systools.Dialogs;

class Test {
		
	static function main() {
		Dialogs.message("neko-systools","Hello World!",false);
		trace("confirm: "+Dialogs.confirm("neko-systools","Please confirm?",false));
		Dialogs.message("neko-systools","Message error test", true);
		trace("confirm error: "+Dialogs.confirm("neko-systools","Confirm error test", true));
	}
}
