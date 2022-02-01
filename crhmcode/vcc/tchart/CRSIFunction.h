// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CRSIFunction wrapper class

class CRSIFunction : public COleDispatchDriver
{
public:
	CRSIFunction() {} // Calls COleDispatchDriver default constructor
	CRSIFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRSIFunction(const CRSIFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IRSIFunction methods
public:
	long get_Style()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Style(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IRSIFunction properties
public:

};
