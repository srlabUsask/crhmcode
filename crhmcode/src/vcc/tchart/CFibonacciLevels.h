// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CFibonacciLevels wrapper class

class CFibonacciLevels : public COleDispatchDriver
{
public:
	CFibonacciLevels() {} // Calls COleDispatchDriver default constructor
	CFibonacciLevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFibonacciLevels(const CFibonacciLevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IFibonacciLevels methods
public:
	LPDISPATCH get_Level(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IFibonacciLevels properties
public:

};

