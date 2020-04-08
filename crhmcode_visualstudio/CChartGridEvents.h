// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartGridEvents wrapper class

class CChartGridEvents : public COleDispatchDriver
{
public:
	CChartGridEvents() {} // Calls COleDispatchDriver default constructor
	CChartGridEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartGridEvents(const CChartGridEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartGridEvents methods
public:
	STDMETHOD(OnClick)()
	{
		HRESULT result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_HRESULT, (void*)&result, nullptr);
		return result;
	}
	void OnChangeColor()
	{
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void OnEditingCell(long ACol, long ARow, BOOL * Allow)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ACol, ARow, Allow);
	}
	void OnSetEditText(long ACol, long ARow, LPCTSTR AValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ACol, ARow, AValue);
	}
	void OnTopLeftChanged()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	// IChartGridEvents properties
public:

};

