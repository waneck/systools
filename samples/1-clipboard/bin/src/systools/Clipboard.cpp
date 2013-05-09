#include <hxcpp.h>

#ifndef INCLUDED_cpp_Lib
#include <cpp/Lib.h>
#endif
#ifndef INCLUDED_systools_Clipboard
#include <systools/Clipboard.h>
#endif
namespace systools{

Void Clipboard_obj::__construct()
{
	return null();
}

Clipboard_obj::~Clipboard_obj() { }

Dynamic Clipboard_obj::__CreateEmpty() { return  new Clipboard_obj; }
hx::ObjectPtr< Clipboard_obj > Clipboard_obj::__new()
{  hx::ObjectPtr< Clipboard_obj > result = new Clipboard_obj();
	result->__construct();
	return result;}

Dynamic Clipboard_obj::__Create(hx::DynamicArray inArgs)
{  hx::ObjectPtr< Clipboard_obj > result = new Clipboard_obj();
	result->__construct();
	return result;}

Void Clipboard_obj::setText( ::String text){
{
		HX_STACK_PUSH("Clipboard::setText","systools/Clipboard.hx",31);
		HX_STACK_ARG(text,"text");
		HX_STACK_LINE(31)
		::systools::Clipboard_obj::_set_clipboard_data(text);
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC1(Clipboard_obj,setText,(void))

::String Clipboard_obj::getText( ){
	HX_STACK_PUSH("Clipboard::getText","systools/Clipboard.hx",35);
	HX_STACK_LINE(35)
	return ::String(::systools::Clipboard_obj::_get_clipboard_data());
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Clipboard_obj,getText,return )

Void Clipboard_obj::clear( ){
{
		HX_STACK_PUSH("Clipboard::clear","systools/Clipboard.hx",39);
		HX_STACK_LINE(39)
		::systools::Clipboard_obj::_clear_clipboard();
	}
return null();
}


STATIC_HX_DEFINE_DYNAMIC_FUNC0(Clipboard_obj,clear,(void))

Dynamic Clipboard_obj::_set_clipboard_data;

Dynamic Clipboard_obj::_get_clipboard_data;

Dynamic Clipboard_obj::_clear_clipboard;


Clipboard_obj::Clipboard_obj()
{
}

void Clipboard_obj::__Mark(HX_MARK_PARAMS)
{
	HX_MARK_BEGIN_CLASS(Clipboard);
	HX_MARK_END_CLASS();
}

void Clipboard_obj::__Visit(HX_VISIT_PARAMS)
{
}

Dynamic Clipboard_obj::__Field(const ::String &inName,bool inCallProp)
{
	switch(inName.length) {
	case 5:
		if (HX_FIELD_EQ(inName,"clear") ) { return clear_dyn(); }
		break;
	case 7:
		if (HX_FIELD_EQ(inName,"setText") ) { return setText_dyn(); }
		if (HX_FIELD_EQ(inName,"getText") ) { return getText_dyn(); }
		break;
	case 16:
		if (HX_FIELD_EQ(inName,"_clear_clipboard") ) { return _clear_clipboard; }
		break;
	case 19:
		if (HX_FIELD_EQ(inName,"_set_clipboard_data") ) { return _set_clipboard_data; }
		if (HX_FIELD_EQ(inName,"_get_clipboard_data") ) { return _get_clipboard_data; }
	}
	return super::__Field(inName,inCallProp);
}

Dynamic Clipboard_obj::__SetField(const ::String &inName,const Dynamic &inValue,bool inCallProp)
{
	switch(inName.length) {
	case 16:
		if (HX_FIELD_EQ(inName,"_clear_clipboard") ) { _clear_clipboard=inValue.Cast< Dynamic >(); return inValue; }
		break;
	case 19:
		if (HX_FIELD_EQ(inName,"_set_clipboard_data") ) { _set_clipboard_data=inValue.Cast< Dynamic >(); return inValue; }
		if (HX_FIELD_EQ(inName,"_get_clipboard_data") ) { _get_clipboard_data=inValue.Cast< Dynamic >(); return inValue; }
	}
	return super::__SetField(inName,inValue,inCallProp);
}

void Clipboard_obj::__GetFields(Array< ::String> &outFields)
{
	super::__GetFields(outFields);
};

static ::String sStaticFields[] = {
	HX_CSTRING("setText"),
	HX_CSTRING("getText"),
	HX_CSTRING("clear"),
	HX_CSTRING("_set_clipboard_data"),
	HX_CSTRING("_get_clipboard_data"),
	HX_CSTRING("_clear_clipboard"),
	String(null()) };

static ::String sMemberFields[] = {
	String(null()) };

static void sMarkStatics(HX_MARK_PARAMS) {
	HX_MARK_MEMBER_NAME(Clipboard_obj::__mClass,"__mClass");
	HX_MARK_MEMBER_NAME(Clipboard_obj::_set_clipboard_data,"_set_clipboard_data");
	HX_MARK_MEMBER_NAME(Clipboard_obj::_get_clipboard_data,"_get_clipboard_data");
	HX_MARK_MEMBER_NAME(Clipboard_obj::_clear_clipboard,"_clear_clipboard");
};

static void sVisitStatics(HX_VISIT_PARAMS) {
	HX_VISIT_MEMBER_NAME(Clipboard_obj::__mClass,"__mClass");
	HX_VISIT_MEMBER_NAME(Clipboard_obj::_set_clipboard_data,"_set_clipboard_data");
	HX_VISIT_MEMBER_NAME(Clipboard_obj::_get_clipboard_data,"_get_clipboard_data");
	HX_VISIT_MEMBER_NAME(Clipboard_obj::_clear_clipboard,"_clear_clipboard");
};

Class Clipboard_obj::__mClass;

void Clipboard_obj::__register()
{
	hx::Static(__mClass) = hx::RegisterClass(HX_CSTRING("systools.Clipboard"), hx::TCanCast< Clipboard_obj> ,sStaticFields,sMemberFields,
	&__CreateEmpty, &__Create,
	&super::__SGetClass(), 0, sMarkStatics, sVisitStatics);
}

void Clipboard_obj::__boot()
{
	_set_clipboard_data= ::cpp::Lib_obj::load(HX_CSTRING("systools"),HX_CSTRING("clipboard_set_text"),(int)1);
	_get_clipboard_data= ::cpp::Lib_obj::load(HX_CSTRING("systools"),HX_CSTRING("clipboard_get_text"),(int)0);
	_clear_clipboard= ::cpp::Lib_obj::load(HX_CSTRING("systools"),HX_CSTRING("clipboard_clear"),(int)0);
}

} // end namespace systools
