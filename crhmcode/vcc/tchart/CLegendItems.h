// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CLegendItems wrapper class

class CLegendItems : public COleDispatchDriver
{
public:
	CLegendItems() {} // Calls COleDispatchDriver default constructor
	CLegendItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLegendItems(const CLegendItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ILegendItems methods
public:
	void Clear()
	{
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL get_Custom()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Custom(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// ILegendItems properties
public:

};
