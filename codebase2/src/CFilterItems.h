// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CFilterItems wrapper class

class CFilterItems : public COleDispatchDriver
{
public:
	CFilterItems() {} // Calls COleDispatchDriver default constructor
	CFilterItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFilterItems(const CFilterItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IFilterItems methods
public:
	long Add(long FilterClass)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, FilterClass);
		return result;
	}
	void LoadImage(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	void AssignImage(long ImageHandle)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ImageHandle);
	}

	// IFilterItems properties
public:

};

