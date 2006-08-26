/**
 * For x-plat compatibility, always specify a Windows
 * root key identifier (Registry.HKEY_xxx_xxx). The 
 * value is ignored on OSX, but required on Windows.
 *
 * Mac registry entries (or 'Preferences') require a
 * non-empty key name. For example:
 *
 *    Registry.setValue(Registry.HKEY_CLASSES_ROOT, "myApp//someData", "", "Hello");
 *
 * will fail on OSX.
 */  

import systools.Registry;

class Test {
		
	static function main() {
		var path: String = "org\\nekovm\\systools";
		var key: String = "Greeting";

		// Write a registry entry:			
		Registry.setValue(Registry.HKEY_CLASSES_ROOT, path, key,"Hello World!");
		
		// Read back and trace the entry:
		var value: String = Registry.getValue(Registry.HKEY_CLASSES_ROOT, path, key);
		trace( "Greeting (from registry) is '"+value+"'"); 	
		
		// Remove all values listed at our path:
		Registry.deleteKey(Registry.HKEY_CLASSES_ROOT, path);

		// Try to read once more, sh
		value = Registry.getValue(Registry.HKEY_CLASSES_ROOT, path, key);
		trace( "Greeting (after delete) is '"+value+"'"); 
		
	}
}
