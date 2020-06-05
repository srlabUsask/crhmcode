// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CStrings wrapper class

class CStrings : public COleDispatchDriver
{
public:
	CStrings() {} // Calls COleDispatchDriver default constructor
	CStrings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CStrings(const CStrings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IStrings methods
public:
	VARIANT get_ControlDefault(long Index)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Index);
		return result;
	}
	void put_ControlDefault(long Index, VARIANT& newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, &newValue);
	}
	long Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	VARIANT get_Item(long Index)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Index);
		return result;
	}
	void put_Item(long Index, VARIANT& newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, &newValue);
	}
	void Remove(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}
	void Clear()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long Add(VARIANT& AItem)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &AItem);
		return result;
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IStrings properties
public:

};
