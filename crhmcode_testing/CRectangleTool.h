// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CRectangleTool wrapper class

class CRectangleTool : public COleDispatchDriver
{
public:
	CRectangleTool() {} // Calls COleDispatchDriver default constructor
	CRectangleTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRectangleTool(const CRectangleTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IRectangleTool methods
public:
	long get_Position()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Position(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Shape()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Callout()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_TextAlignment()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TextAlignment(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL Clicked(long X, long Y)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, X, Y);
		return result;
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Cursor()
	{
		short result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Cursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Left(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Top(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoSize()
	{
		BOOL result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	TeeRect get_Bounds()
	{
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_EMPTY, nullptr, nullptr);
	}
	void SetBounds(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	long get_PositionUnits()
	{
		long result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PositionUnits(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Selected()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Dragging()
	{
		BOOL result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Resizing()
	{
		BOOL result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	long ClickedEdge(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	BOOL get_AllowDrag()
	{
		BOOL result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllowDrag(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AllowResize()
	{
		BOOL result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllowResize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IRectangleTool properties
public:

};
