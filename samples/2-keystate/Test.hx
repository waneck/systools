import systools.Key;
import systools.Misc;
class Test {

	static function main() {
		trace("Press ALT to end sample");
		while (!Misc.getKeyState(Key.Alt)) {
			// sleep for 25 milliseconds
			Sys.sleep(0.0025);

			if	(	Misc.getKeyState(Key.LeftCtrl)
				|| 	Misc.getKeyState(Key.RightCtrl)
				)
				trace("CTRL is down");

			if 	(	Misc.getKeyState(Key.LeftShift)
				||	Misc.getKeyState(Key.RightShift)
				)
				trace("SHIFT is down");

		}
	}
}
