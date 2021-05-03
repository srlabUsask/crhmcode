// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// COrgItem wrapper class

class COrgItem : public COleDispatchDriver
{
public:
	COrgItem() {} // Calls COleDispatchDriver default constructor
	COrgItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COrgItem(const COrgItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IOrgItem methods
public:
	long AddChild(LPCTSTR Text)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Text);
		return result;
	}
	long AddBrother(LPCTSTR Text)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Text);
		return result;
	}
	VARIANT get_Series()
	{
		VARIANT result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	long get_Superior()
	{
		long result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Superior(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Format()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IOrgItem properties
public:

};
