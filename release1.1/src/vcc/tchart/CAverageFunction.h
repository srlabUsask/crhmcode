// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAverageFunction wrapper class

class CAverageFunction : public COleDispatchDriver
{
public:
	CAverageFunction() {} // Calls COleDispatchDriver default constructor
	CAverageFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAverageFunction(const CAverageFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAverageFunction methods
public:
	BOOL get_IncludeNulls()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_IncludeNulls(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IAverageFunction properties
public:

};

