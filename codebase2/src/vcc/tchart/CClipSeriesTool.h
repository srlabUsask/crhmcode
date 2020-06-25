// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CClipSeriesTool wrapper class

class CClipSeriesTool : public COleDispatchDriver
{
public:
	CClipSeriesTool() {} // Calls COleDispatchDriver default constructor
	CClipSeriesTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CClipSeriesTool(const CClipSeriesTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IClipSeriesTool methods
public:
	VARIANT get_Series()
	{
		VARIANT result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Series(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}

	// IClipSeriesTool properties
public:

};

