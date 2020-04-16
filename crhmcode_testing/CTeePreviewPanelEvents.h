// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeePreviewPanelEvents wrapper class

class CTeePreviewPanelEvents : public COleDispatchDriver
{
public:
	CTeePreviewPanelEvents() {} // Calls COleDispatchDriver default constructor
	CTeePreviewPanelEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeePreviewPanelEvents(const CTeePreviewPanelEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeePreviewPanelEvents methods
public:
	STDMETHOD(OnChangeMargins)(BOOL DisableProportional, long Left, long Top, long Right, long Bottom)
	{
		HRESULT result;
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, DisableProportional, Left, Top, Right, Bottom);
		return result;
	}
	STDMETHOD(OnAfterDraw)()
	{
		HRESULT result;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_HRESULT, (void*)&result, nullptr);
		return result;
	}

	// ITeePreviewPanelEvents properties
public:

};
