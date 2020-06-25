// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CATRFunction wrapper class

class CATRFunction : public COleDispatchDriver
{
public:
	CATRFunction() {} // Calls COleDispatchDriver default constructor
	CATRFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CATRFunction(const CATRFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IATRFunction methods
public:
	BOOL get_IncludeNulls()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_IncludeNulls(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IATRFunction properties
public:

};

