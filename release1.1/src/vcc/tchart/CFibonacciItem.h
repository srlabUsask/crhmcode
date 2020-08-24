// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CFibonacciItem wrapper class

class CFibonacciItem : public COleDispatchDriver
{
public:
	CFibonacciItem() {} // Calls COleDispatchDriver default constructor
	CFibonacciItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFibonacciItem(const CFibonacciItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IFibonacciItem methods
public:
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	double get_Value()
	{
		double result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Value(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IFibonacciItem properties
public:

};

