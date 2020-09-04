// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCustomSortedFunction wrapper class

class CCustomSortedFunction : public COleDispatchDriver
{
public:
	CCustomSortedFunction() {} // Calls COleDispatchDriver default constructor
	CCustomSortedFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCustomSortedFunction(const CCustomSortedFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICustomSortedFunction methods
public:
	BOOL get_IncludeNulls()
	{
		BOOL result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_IncludeNulls(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ICustomSortedFunction properties
public:

};

