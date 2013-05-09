#include <hxcpp.h>

#include <systools/Clipboard.h>
#include <systools/Loader.h>
#include <haxe/Log.h>
#include <cpp/Lib.h>
#include <Test.h>
#include <Std.h>

void __boot_all()
{
hx::RegisterResources( hx::GetResources() );
::systools::Clipboard_obj::__register();
::systools::Loader_obj::__register();
::haxe::Log_obj::__register();
::cpp::Lib_obj::__register();
::Test_obj::__register();
::Std_obj::__register();
::cpp::Lib_obj::__boot();
::haxe::Log_obj::__boot();
::Std_obj::__boot();
::Test_obj::__boot();
::systools::Loader_obj::__boot();
::systools::Clipboard_obj::__boot();
}

