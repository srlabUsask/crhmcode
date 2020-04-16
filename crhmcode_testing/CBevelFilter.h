// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CBevelFilter wrapper class

class CBevelFilter : public COleDispatchDriver
{
public:
	CBevelFilter() {} // Calls COleDispatchDriver default constructor
	CBevelFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CBevelFilter(const CBevelFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IBevelFilter methods
public:
	long get_Bright()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Bright(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Size()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Size(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IBevelFilter properties
public:

};

