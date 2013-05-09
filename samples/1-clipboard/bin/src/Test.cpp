#include <hxcpp.h>

#ifndef INCLUDED_Test
#include <Test.h>
#endif
#ifndef INCLUDED_haxe_Log
#include <haxe/Log.h>
#endif
#ifndef INCLUDED_systools_Clipboard
#include <systools/Clipboard.h>
#endif

Void Test_obj::__construct()
{
	return null();
}

Test_obj::~Test_obj() { }

Dynamic Test_obj::__CreateEmpty() { return  new Test_obj; }
hx::ObjectPtr< Test_obj > Test_obj::__new()
{  hx::ObjectPtr< Test_obj > result = new Test_obj();
	result->__construct();
	return result;}

Dynamic Test_obj::__Create(hx::DynamicArray inArgs)
{  hx::ObjectPtr< Test_obj > result = new Test_obj();
	result->__construct();
	return result;}

Void Test_obj::main( ){
{
		HX_STACK_PUSH("Test::main","Test.hx",3);
		HX_STACK_LINE(4)
		::String cbtext = ::systools::Clipboard_obj::getText();		HX_STACK_VAR(cbtext,"cbtext");
		HX_STACK_LINE(5)
		::haxe::Log_obj::trace((HX_CSTRING("Current text on clipboard: ") + cbtext),hx::SourceInfo(HX_CSTRING("Test.hx"),5,HX_CSTRING("Test"),HX_CSTRING("main")));
		HX_STACK_LINE(7)
		::systools::Clipboard_obj::clear();
		HX_STACK_LINE(8)
		::haxe::Log_obj::trace(HX_CSTRING("Cleared clipboard"),hx::SourceInfo(HX_CSTRING("Test.hx"),8,HX_CSTRING("Test"),HX_CSTRING("main")));
		HX_STACK_LINE(10)
		cbtext = ::systools::Clipboard_obj::getText();
		HX_STACK_LINE(11)
		::haxe::Log_obj::trace((HX_CSTRING("Current text on clipboard: ") + cbtext),hx::SourceInfo(HX_CSTRING("Test.hx"),11,HX_CSTRING("Test"),HX_CSTRING("main")));
		HX_STACK_LINE(13)
		::haxe::Log_obj::trace(HX_CSTRING("Setting clipboard text to: Hello World"),hx::SourceInfo(HX_CSTRING("Test.hx"),13,HX_CSTRING("Test"),HX_CSTRING("main")));
		HX_STACK_LINE(14)
		::systools::Clipboard_obj::setText(HX_CSTRING("Hello World"));
		HX_STACK_LINE(16)
		cbtext = ::systools::Clipboard_obj::getText();
		HX_STACK_LINE(17)
		::haxe::Log_obj::trace((HX_CSTRING("Current text on clipboard: ") + cbtext),hx::SourceInfo(HX_CSTRING("Test.hx"),17,HX_CSTRING("Test"),HX_CSTRING("main")));
		HX_STACK_LINE(19)
		::systools::Clipboard_obj::clear();
		HX_STACK_LINE(20)
		::haxe::Log_obj::trace(HX_CSTRING("Cleared clipboard (again)"),hx::SourceInfo(HX_CSTRING("Test.hx"),20,HX_CSTRING("Test"),HX_CSTRING("main")));
		HX_STACK_LINE(22)
		cbtext = ::systools::Clipboard_obj::getText();
		HX_STACK_LINE(23)
		::haxe::Log_obj::trace((HX_CSTRING("Current text on clipboard: ") + cbtext),hx::SourceInfo(HX_CSTRING("Test.hx"),23,HX_CSTRING("Test"),HX_CSTRING("main")));
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Test_obj,main,(void))


Test_obj::Test_obj()
{
}

void Test_obj::__Mark(HX_MARK_PARAMS)
{
	HX_MARK_BEGIN_CLASS(Test);
	HX_MARK_END_CLASS();
}

void Test_obj::__Visit(HX_VISIT_PARAMS)
{
}

Dynamic Test_obj::__Field(const ::String &inName,bool inCallProp)
{
	switch(inName.length) {
	case 4:
		if (HX_FIELD_EQ(inName,"main") ) { return main_dyn(); }
	}
	return super::__Field(inName,inCallProp);
}

Dynamic Test_obj::__SetField(const ::String &inName,const Dynamic &inValue,bool inCallProp)
{
	return super::__SetField(inName,inValue,inCallProp);
}

void Test_obj::__GetFields(Array< ::String> &outFields)
{
	super::__GetFields(outFields);
};

static ::String sStaticFields[] = {
	HX_CSTRING("main"),
	String(null()) };

static ::String sMemberFields[] = {
	String(null()) };

static void sMarkStatics(HX_MARK_PARAMS) {
	HX_MARK_MEMBER_NAME(Test_obj::__mClass,"__mClass");
};

static void sVisitStatics(HX_VISIT_PARAMS) {
	HX_VISIT_MEMBER_NAME(Test_obj::__mClass,"__mClass");
};

Class Test_obj::__mClass;

void Test_obj::__register()
{
	hx::Static(__mClass) = hx::RegisterClass(HX_CSTRING("Test"), hx::TCanCast< Test_obj> ,sStaticFields,sMemberFields,
	&__CreateEmpty, &__Create,
	&super::__SGetClass(), 0, sMarkStatics, sVisitStatics);
}

void Test_obj::__boot()
{
}

