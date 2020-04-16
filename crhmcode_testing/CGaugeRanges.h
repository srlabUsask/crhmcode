// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGaugeRanges wrapper class

class CGaugeRanges : public COleDispatchDriver
{
public:
	CGaugeRanges() {} // Calls COleDispatchDriver default constructor
	CGaugeRanges(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGaugeRanges(const CGaugeRanges& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGaugeRanges methods
public:
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long Add(double StartValue, double EndValue, unsigned long Color)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_UI4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms, StartValue, EndValue, Color);
		return result;
	}

	// IGaugeRanges properties
public:

};

