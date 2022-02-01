// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CToolList wrapper class

class CToolList : public COleDispatchDriver
{
public:
	CToolList() {} // Calls COleDispatchDriver default constructor
	CToolList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CToolList(const CToolList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IToolList methods
public:
	long Add(long ToolClass)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ToolClass);
		return result;
	}
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	VARIANT get_ControlDefault(long Index)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Index);
		return result;
	}
	void Clear()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Delete(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Active(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void Exchange(long Index1, long Index2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index1, Index2);
	}
	void ShowGallery()
	{
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	// IToolList properties
public:

};
