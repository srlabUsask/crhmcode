// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeRect wrapper class

class CTeeRect : public COleDispatchDriver
{
public:
	CTeeRect() {} // Calls COleDispatchDriver default constructor
	CTeeRect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeRect(const CTeeRect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeRect methods
public:
	long get_Left()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Right()
	{
		long result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Bottom()
	{
		long result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	// ITeeRect properties
public:

};
