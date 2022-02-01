// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CMapPolygonList wrapper class

class CMapPolygonList : public COleDispatchDriver
{
public:
	CMapPolygonList() {} // Calls COleDispatchDriver default constructor
	CMapPolygonList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapPolygonList(const CMapPolygonList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMapPolygonList methods
public:
	long Add()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Polygon(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_ByCode(LPCTSTR ACode)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, ACode);
		return result;
	}
	LPDISPATCH get_ByName(LPCTSTR AName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, AName);
		return result;
	}
	void Exchange(long a, long b)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, a, b);
	}

	// IMapPolygonList properties
public:

};
