// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CContrastFilter wrapper class

class CContrastFilter : public COleDispatchDriver
{
public:
	CContrastFilter() {} // Calls COleDispatchDriver default constructor
	CContrastFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CContrastFilter(const CContrastFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IContrastFilter methods
public:
	BOOL get_Percent()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Percent(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Amount()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Amount(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IContrastFilter properties
public:

};

