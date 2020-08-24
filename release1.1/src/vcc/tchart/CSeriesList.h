// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSeriesList wrapper class

class CSeriesList : public COleDispatchDriver
{
public:
	CSeriesList() {} // Calls COleDispatchDriver default constructor
	CSeriesList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSeriesList(const CSeriesList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISeriesList methods
public:
	void AddGroup(LPCTSTR Name)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Name);
	}
	BOOL get_AllActive()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllActive(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Groups()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void ClearValues()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long First()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long Last()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long Clicked(long X, long Y, long ValueIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y, ValueIndex);
		return result;
	}

	// ISeriesList properties
public:

};
