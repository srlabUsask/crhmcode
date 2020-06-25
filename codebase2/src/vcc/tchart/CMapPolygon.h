// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CMapPolygon wrapper class

class CMapPolygon : public COleDispatchDriver
{
public:
	CMapPolygon() {} // Calls COleDispatchDriver default constructor
	CMapPolygon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMapPolygon(const CMapPolygon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMapPolygon methods
public:
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_Color()
	{
		unsigned long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_Color(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Gradient()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ParentBrush()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ParentBrush(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ParentPen()
	{
		BOOL result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ParentPen(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Z()
	{
		double result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Z(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long AddXY(double X, double Y)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL Visible()
	{
		BOOL result;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Closed()
	{
		BOOL result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Closed(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_GetPoints()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Index()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Index(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Active()
	{
		BOOL result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Active(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Transparent()
	{
		BOOL result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Transparent(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Points()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	CString get_Code()
	{
		CString result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Code(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Size()
	{
		double result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Size(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xd2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Picture()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH Centroid()
	{
		LPDISPATCH result;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IMapPolygon properties
public:

};
