// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeCorner wrapper class

class CTeeCorner : public COleDispatchDriver
{
public:
	CTeeCorner() {} // Calls COleDispatchDriver default constructor
	CTeeCorner(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeCorner(const CTeeCorner& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeCorner methods
public:
	long get_Style()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Style(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ITeeCorner properties
public:

};
