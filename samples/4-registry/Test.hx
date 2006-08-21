import systools.win.Registry;

class Test {
		
	static function main() {
		var hxmlCommand : String = systools.win.Registry.getValue(systools.win.Registry.HKEY_CLASSES_ROOT, ".hxml\\shell\\Compile\\command", "");
		trace("Current .hxml command: "+ hxmlCommand);
		
		var sk = ".systools\\shell\\Systool\\command";
		trace("Setting .systools command");
		systools.win.Registry.setValue(systools.win.Registry.HKEY_CLASSES_ROOT, sk, "", "c:\\windows\\notepad.exe -prompt \"%1\"");

		var systoolCommand : String = systools.win.Registry.getValue(systools.win.Registry.HKEY_CLASSES_ROOT, sk, "");
		trace("Current .systools command: "+ systoolCommand);
		
		trace("Deleting key " + sk);
		systools.win.Registry.deleteKey(systools.win.Registry.HKEY_CLASSES_ROOT, ".systools\\shell\\Systool\\command");
		systools.win.Registry.deleteKey(systools.win.Registry.HKEY_CLASSES_ROOT, ".systools\\shell\\Systool");
		systools.win.Registry.deleteKey(systools.win.Registry.HKEY_CLASSES_ROOT, ".systools\\shell");
		systools.win.Registry.deleteKey(systools.win.Registry.HKEY_CLASSES_ROOT, ".systools");

		systoolCommand = systools.win.Registry.getValue(systools.win.Registry.HKEY_CLASSES_ROOT, sk, "");
		trace("After delete .systools command: "+ systoolCommand);
	}
}
