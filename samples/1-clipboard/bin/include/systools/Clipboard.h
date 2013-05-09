#ifndef INCLUDED_systools_Clipboard
#define INCLUDED_systools_Clipboard

#ifndef HXCPP_H
#include <hxcpp.h>
#endif

HX_DECLARE_CLASS1(systools,Clipboard)
namespace systools{


class HXCPP_CLASS_ATTRIBUTES  Clipboard_obj : public hx::Object{
	public:
		typedef hx::Object super;
		typedef Clipboard_obj OBJ_;
		Clipboard_obj();
		Void __construct();

	public:
		static hx::ObjectPtr< Clipboard_obj > __new();
		static Dynamic __CreateEmpty();
		static Dynamic __Create(hx::DynamicArray inArgs);
		~Clipboard_obj();

		HX_DO_RTTI;
		static void __boot();
		static void __register();
		void __Mark(HX_MARK_PARAMS);
		void __Visit(HX_VISIT_PARAMS);
		::String __ToString() const { return HX_CSTRING("Clipboard"); }

		static Void setText( ::String text);
		static Dynamic setText_dyn();

		static ::String getText( );
		static Dynamic getText_dyn();

		static Void clear( );
		static Dynamic clear_dyn();

		static Dynamic _set_clipboard_data;
		static Dynamic &_set_clipboard_data_dyn() { return _set_clipboard_data;}
		static Dynamic _get_clipboard_data;
		static Dynamic &_get_clipboard_data_dyn() { return _get_clipboard_data;}
		static Dynamic _clear_clipboard;
		static Dynamic &_clear_clipboard_dyn() { return _clear_clipboard;}
};

} // end namespace systools

#endif /* INCLUDED_systools_Clipboard */ 
