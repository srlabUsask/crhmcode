// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPage wrapper class

class CPage : public COleDispatchDriver
{
public:
	CPage() {} // Calls COleDispatchDriver default constructor
	CPage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPage(const CPage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPage methods
public:
	void Next()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Previous()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_MaxPointsPerPage()
	{
		long result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MaxPointsPerPage(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Current()
	{
		long result;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Current(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ScaleLastPage()
	{
		BOOL result;
		InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ScaleLastPage(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_FirstValueIndex()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	BOOL get_AutoScale()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoScale(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IPage properties
public:

};
