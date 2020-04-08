// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGrayScaleFilter wrapper class

class CGrayScaleFilter : public COleDispatchDriver
{
public:
	CGrayScaleFilter() {} // Calls COleDispatchDriver default constructor
	CGrayScaleFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGrayScaleFilter(const CGrayScaleFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGrayScaleFilter methods
public:
	long get_Method()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Method(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IGrayScaleFilter properties
public:

};

