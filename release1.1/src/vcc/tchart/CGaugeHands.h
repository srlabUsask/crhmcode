// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGaugeHands wrapper class

class CGaugeHands : public COleDispatchDriver
{
public:
	CGaugeHands() {} // Calls COleDispatchDriver default constructor
	CGaugeHands(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGaugeHands(const CGaugeHands& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGaugeHands methods
public:
	LPDISPATCH get_Items(long AIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, AIndex);
		return result;
	}
	long Add(double AValue)
	{
		long result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AValue);
		return result;
	}

	// IGaugeHands properties
public:

};

