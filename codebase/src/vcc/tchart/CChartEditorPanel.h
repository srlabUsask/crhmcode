// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartEditorPanel wrapper class

class CChartEditorPanel : public COleDispatchDriver
{
public:
	CChartEditorPanel() {} // Calls COleDispatchDriver default constructor
	CChartEditorPanel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartEditorPanel(const CChartEditorPanel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartEditorPanel methods
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
	void SelectUnderMouse()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_BevelOuter()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BevelOuter(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void put_Editor(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void put_EditorLink(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_MainPage()
	{
		LPDISPATCH result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_SubPage()
	{
		LPDISPATCH result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IChartEditorPanel properties
public:

};

