// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeePreviewPanel wrapper class

class CTeePreviewPanel : public COleDispatchDriver
{
public:
	CTeePreviewPanel() {} // Calls COleDispatchDriver default constructor
	CTeePreviewPanel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeePreviewPanel(const CTeePreviewPanel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeePreviewPanel methods
public:
	void put_Chart(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void put_ChartLink(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void put_ChartLinkx64(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	BOOL get_AllowResize()
	{
		BOOL result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllowResize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AllowMove()
	{
		BOOL result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllowMove(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AsBitmap()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AsBitmap(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_DragImage()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_DragImage(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Orientation()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Orientation(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_PaperColor()
	{
		unsigned long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_PaperColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_ShadowColor()
	{
		unsigned long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_ShadowColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ShadowSize()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ShadowSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowImage()
	{
		BOOL result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowImage(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Title()
	{
		CString result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Title(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void Repaint()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Panels()
	{
		LPDISPATCH result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void AddChart(LPDISPATCH Value)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Value);
	}
	LPDISPATCH get_Gradient()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Margins()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void PrintPage()
	{
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void AddChartLink(long Value)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Value);
	}
	LPDISPATCH get_Canvas()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_PaperRect()
	{
		LPDISPATCH result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void ShowEditor()
	{
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void AddChartLinkx64(VARIANT& Value)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &Value);
	}

	// ITeePreviewPanel properties
public:

};
