// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CMarks wrapper class

class CMarks : public COleDispatchDriver
{
public:
	CMarks() {} // Calls COleDispatchDriver default constructor
	CMarks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMarks(const CMarks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMarks methods
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
	LPDISPATCH get_Arrow()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ArrowLength()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ArrowLength(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_BackColor()
	{
		unsigned long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_BackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Clip()
	{
		BOOL result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Clip(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Style()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Style(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Positions()
	{
		LPDISPATCH result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long Clicked(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	long get_ZPosition()
	{
		long result;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ZPosition(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DrawEvery()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DrawEvery(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Multiline()
	{
		BOOL result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Multiline(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void ResetPositions()
	{
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Callout()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void ShowEditorMarks()
	{
		InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	void Clear()
	{
		InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Symbol()
	{
		LPDISPATCH result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_TextAlign()
	{
		long result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TextAlign(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Margins()
	{
		LPDISPATCH result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_FontSeriesColor()
	{
		BOOL result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_FontSeriesColor(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x134, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_OnTop()
	{
		BOOL result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_OnTop(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoPosition()
	{
		BOOL result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoPosition(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_SoftClip()
	{
		BOOL result;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_SoftClip(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_UseSeriesTransparency()
	{
		BOOL result;
		InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseSeriesTransparency(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Automatic()
	{
		LPDISPATCH result;
		InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Tail()
	{
		LPDISPATCH result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IMarks properties
public:

};
