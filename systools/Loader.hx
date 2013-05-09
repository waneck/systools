package systools;
#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

class Loader
{
	private static var init = false;

	public static function load(lib:String, s:String):Dynamic
	{

		if (!init)
		{
#if neko
			loadNekoAPI();
#end
			load("systools","systools_init",0)();
			init = true;
		}

		return Lib.load(lib,s);
	}

#if neko
	public static function loadNekoAPI()
	{
		var i = load("systools","neko_init", 5);
		if (i != null)
		{
			i(function(s) return new String(s), function(len:Int) { var r = []; if (len > 0) r[len - 1] = null; return r; }, null, true, false);
		}
	}
#end
}
