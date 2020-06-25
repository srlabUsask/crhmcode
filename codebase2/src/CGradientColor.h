// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGradientColor wrapper class

class CGradientColor : public COleDispatchDriver
{
public:
	CGradientColor() {} // Calls COleDispatchDriver default constructor
	CGradientColor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGradientColor(const CGradientColor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGradientColor methods
public:
	unsigned long get_Color()
	{
		unsigned long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_Color(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Offset()
	{
		double result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Offset(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IGradientColor properties
public:

};

