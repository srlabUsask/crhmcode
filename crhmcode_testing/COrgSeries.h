// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// COrgSeries wrapper class

class COrgSeries : public COleDispatchDriver
{
public:
	COrgSeries() {} // Calls COleDispatchDriver default constructor
	COrgSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COrgSeries(const COrgSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IOrgSeries methods
public:
	long Add(LPCTSTR Text, long Superior)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Text, Superior);
		return result;
	}
	long FirstChild(long ValueIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ValueIndex);
		return result;
	}
	TeeRect get_Bounds()
	{
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	LPDISPATCH get_Format()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Items()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_LineStyle()
	{
		long result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LineStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Spacing()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IOrgSeries properties
public:

};
