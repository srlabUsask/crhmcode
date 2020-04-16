// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// COrgShape wrapper class

class COrgShape : public COleDispatchDriver
{
public:
	COrgShape() {} // Calls COleDispatchDriver default constructor
	COrgShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COrgShape(const COrgShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IOrgShape methods
public:
	unsigned long get_Color()
	{
		unsigned long result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_Color(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x6c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Gradient()
	{
		LPDISPATCH result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ShadowSize()
	{
		long result;
		InvokeHelper(0x3f4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ShadowSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3f4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_ShadowColor()
	{
		unsigned long result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_ShadowColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Transparent()
	{
		BOOL result;
		InvokeHelper(0x3f5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Transparent(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x3f5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ShapeStyle()
	{
		long result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ShapeStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_ShapeBounds()
	{
		LPDISPATCH result;
		InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Bevel()
	{
		long result;
		InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Bevel(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BevelWidth()
	{
		long result;
		InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BevelWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x13a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void ShowEditorShape(BOOL HideTexts, LPCTSTR Caption)
	{
		static BYTE parms[] = VTS_BOOL VTS_BSTR;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, HideTexts, Caption);
	}
	LPDISPATCH get_Shadow()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_RoundSize()
	{
		long result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_RoundSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Picture()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void Show()
	{
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Hide()
	{
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Emboss()
	{
		LPDISPATCH result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xdc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0xe6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Frame()
	{
		LPDISPATCH result;
		InvokeHelper(0x122, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_ShapeCallout()
	{
		LPDISPATCH result;
		InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Corners()
	{
		LPDISPATCH result;
		InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Children()
	{
		LPDISPATCH result;
		InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ChildLayout()
	{
		long result;
		InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ChildLayout(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x106, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Angle()
	{
		long result;
		InvokeHelper(0x107, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Angle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x107, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShapeVisible()
	{
		BOOL result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShapeVisible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TextFormat()
	{
		long result;
		InvokeHelper(0x353, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TextFormat(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x353, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_CustomPosition()
	{
		BOOL result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_CustomPosition(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xdb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Left(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Top(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoSize()
	{
		BOOL result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ClipText()
	{
		BOOL result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ClipText(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Cursor()
	{
		short result;
		InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Cursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TextAlignment()
	{
		long result;
		InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TextAlignment(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Margins()
	{
		LPDISPATCH result;
		InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IOrgShape properties
public:

};
