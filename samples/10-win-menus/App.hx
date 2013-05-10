import systools.win.Tray;
import systools.win.Menus;
import systools.win.Events;

class App {
	
	static var flash : swhx.Flash;
	static var cnx: swhx.Connection;
	static var window: swhx.Window;
	static var hook: swhx.MessageHook;
	static var thook: swhx.MessageHook;
	static var mhook: swhx.MessageHook;
	static var tray: Tray;
	static var m: Menus;
	static var mm: Menus;
	static var ms1: Menus;
	static var ms11: Menus;
	static var ms2: Menus;
	static var ms3: Menus;

    static function main() {
    	 // initialize ScreenWeaver HX
        swhx.Application.init();

        // create a 400x300 window
        window = new swhx.Window("Window Message Hooks",400,300);
		
		window.onRightClick = function() {
			return false;
		}
		
		// clean up after ourselves:
		window.onClose = cleanUp;

		// create an incoming communication Server
		var server = new neko.net.RemotingServer();

		// share the App object
		server.addObject("App",App);

        // create a flash object inside this window
        // pass the server as parameter
        flash = new swhx.Flash(window,server);

        // set the HTML attributes of this flash object
        flash.setAttribute("src","ui.swf");
        
        // capture loaded event:
        flash.onSourceLoaded = onSourceLoaded;

        // activate the Flash object
        flash.start();

        // enter the system event loop (will exit when window is closed)
        swhx.Application.loop();

        // cleanup SWHX properly
        swhx.Application.cleanup();    	
    }
    
    static function onSourceLoaded() {
    	cnx = swhx.Connection.flashConnect(flash);
    	window.show(true);
    	trace("Window handle is:"+window.handle+" (will be readable when passed to an .ndll)");
		
		/*
		* The numeric value passed to addItem, addDivider and addSubmenu dictate where 
		* the item will be placed as well as what value is returned to the window hook
		* handler.  Make sure these are unique throughout the entire menu hierarchy
		*/
		
		mm = new systools.win.Menus( false );
		
		ms1 = new systools.win.Menus( true );
		ms1.addItem( "sub 1-1", 4 );
		ms1.addItem( "sub 1-2", 5 );
		ms1.addItem( "sub 1-3", 6 );
		
		ms11 = new systools.win.Menus( true );
		ms11.addItem( "sub 1-4-1", 4 );
		ms11.addItem( "sub 1-4-2", 5 );
		ms11.addItem( "sub 1-4-3", 6 );
		
		ms1.addSubmenu( ms11, "sub 1-4", 13 );
		
		ms2 = new systools.win.Menus( true );
		ms2.addItem( "sub 2-1", 7 );
		ms2.addItem( "sub 2-2", 8 );
		ms2.addItem( "sub 2-3", 9 );
		
		ms3 = new systools.win.Menus( true );
		ms3.addItem( "sub 3-1", 10 );
		ms3.addItem( "sub 3-2", 11 );
		ms3.addItem( "sub 3-3", 12 );
		
		mm.addSubmenu( ms1, "option 1", 1 );
		mm.addSubmenu( ms2, "option 2", 2 );
		mm.addSubmenu( ms3, "option 3", 3 );
		
		mm.show( window.handle );
		m = new systools.win.Menus( true );
		m.addItem( "option 1", 1 );
		m.addItem( "option 2", 2 );
		m.addItem( "option 3", 3 );
		
    	hook = window.addMessageHook(untyped Events.RBUTTONUP);
		hook.setNekoCallback(mouseMoveHook);
    	mhook = window.addMessageHook(untyped Events.MENUEVENT);
		mhook.setNekoCallback(menuClickHook);
    	thook = window.addMessageHook(untyped Events.TRAYEVENT);
		thook.setNekoCallback(mouseRightClickHook);
		
		tray = new Tray(window,"swhx_16x16.ico","Hello Tray!");
    }
    
    static function mouseMoveHook() {    	
		trace( "Option " + m.showPopup( window.handle ) + " was selected!" );
    	return 0;
    }
	
	static function menuClickHook() {
		trace( "Option " + mhook.p1 + ", " + mhook.p2 + ", " + hook.callbackData + " was clicked!");
		return 0;
	}
	
	static function mouseRightClickHook() {
		if ( Std.string(thook.p2) == Std.string(Events.RBUTTONUP) )
			trace( "Option " + m.showPopup( window.handle ) + " was selected!" );
		return 0;
	}
		
	static function cleanUp() {
		/*
		All release methods fire exceptions!Needs looking into ...
		*/
		
		//ms11.dispose();
		//ms1.dispose();
		//ms2.dispose();
		//ms3.dispose();
		//mm.dispose();
		//m.dispose();
		window.removeMessageHook(hook);
		window.removeMessageHook(mhook);
		window.removeMessageHook(thook);
		//tray.dispose();
		// allow window to close:
		return true;		
	}
}
