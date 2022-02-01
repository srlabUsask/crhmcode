// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGradientColors wrapper class

class CGradientColors : public COleDispatchDriver
{
public:
	CGradientColors() {} // Calls COleDispatchDriver default constructor
	CGradientColors(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGradientColors(const CGradientColors& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGradientColors methods
public:
	void Clear()
	{
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long AddColor(double AOffset, unsigned long AColor, long ATransparency)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_UI4 VTS_I4;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AOffset, AColor, ATransparency);
		return result;
	}
	void Delete(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}

	// IGradientColors properties
public:

};

