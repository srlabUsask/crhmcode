// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CLegendItem wrapper class

class CLegendItem : public COleDispatchDriver
{
public:
	CLegendItem() {} // Calls COleDispatchDriver default constructor
	CLegendItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLegendItem(const CLegendItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ILegendItem methods
public:
	TeeRect get_SymbolRect()
	{
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_EMPTY, nullptr, nullptr);
	}
	void put_SymbolRect(TeeRect newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Align()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// ILegendItem properties
public:

};
