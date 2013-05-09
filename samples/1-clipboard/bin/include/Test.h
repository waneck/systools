#ifndef INCLUDED_Test
#define INCLUDED_Test

#ifndef HXCPP_H
#include <hxcpp.h>
#endif

HX_DECLARE_CLASS0(Test)


class HXCPP_CLASS_ATTRIBUTES  Test_obj : public hx::Object{
	public:
		typedef hx::Object super;
		typedef Test_obj OBJ_;
		Test_obj();
		Void __construct();

	public:
		static hx::ObjectPtr< Test_obj > __new();
		static Dynamic __CreateEmpty();
		static Dynamic __Create(hx::DynamicArray inArgs);
		~Test_obj();

		HX_DO_RTTI;
		static void __boot();
		static void __register();
		void __Mark(HX_MARK_PARAMS);
		void __Visit(HX_VISIT_PARAMS);
		::String __ToString() const { return HX_CSTRING("Test"); }

		static Void main( );
		static Dynamic main_dyn();

};


#endif /* INCLUDED_Test */ 
