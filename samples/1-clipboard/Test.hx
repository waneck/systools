class Test {
		
	static function main() {
		var cbtext: String = systools.Clipboard.getText();
		trace("Current text on clipboard: "+ cbtext);
		
		systools.Clipboard.clear();
		trace("Cleared clipboard");
		
		cbtext = systools.Clipboard.getText();
		trace("Current text on clipboard: "+ cbtext);
		
		trace("Setting clipboard text to: Hello World");
		systools.Clipboard.setText("Hello World");
		
		cbtext = systools.Clipboard.getText();
		trace("Current text on clipboard: "+ cbtext);
		
		systools.Clipboard.clear();
		trace("Cleared clipboard (again)");
		
		cbtext = systools.Clipboard.getText();
		trace("Current text on clipboard: "+ cbtext);
	}

}
