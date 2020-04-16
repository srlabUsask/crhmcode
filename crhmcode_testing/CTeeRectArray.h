// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeRectArray wrapper class

class CTeeRectArray : public COleDispatchDriver
{
public:
	CTeeRectArray() {} // Calls COleDispatchDriver default constructor
	CTeeRectArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeRectArray(const CTeeRectArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeRectArray methods
public:
	long get_Count()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// ITeeRectArray properties
public:

};
