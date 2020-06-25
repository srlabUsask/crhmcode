// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeEditor wrapper class

class CTeeEditor : public COleDispatchDriver
{
public:
	CTeeEditor() {} // Calls COleDispatchDriver default constructor
	CTeeEditor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeEditor(const CTeeEditor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeEditor methods
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
	CString get_EditorTitle()
	{
		CString result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_EditorTitle(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DefaultPage()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DefaultPage(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void ShowEditor()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL get_AutoRepaint()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoRepaint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_ShowPages()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_EditorLink()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Options()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_TreeView()
	{
		BOOL result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_TreeView(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_HighLightTabs()
	{
		BOOL result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_HighLightTabs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_PixelsPerInch()
	{
		long result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PixelsPerInch(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_RememberPosition()
	{
		BOOL result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_RememberPosition(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_GalleryHeight()
	{
		long result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_GalleryHeight(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_GalleryWidth()
	{
		long result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_GalleryWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x133, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x134, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	VARIANT get_EditorLinkx64()
	{
		VARIANT result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}

	// ITeeEditor properties
public:

};
