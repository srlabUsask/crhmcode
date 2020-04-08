// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeListBoxEvents wrapper class

class CTeeListBoxEvents : public COleDispatchDriver
{
public:
	CTeeListBoxEvents() {} // Calls COleDispatchDriver default constructor
	CTeeListBoxEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeListBoxEvents(const CTeeListBoxEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeListBoxEvents methods
public:
	void OnDblClickSeries(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	STDMETHOD(OnClick)()
	{
		HRESULT result;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_HRESULT, (void*)&result, nullptr);
		return result;
	}
	void OnChangeActive(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	void OnMouseUp(long Button, long Shift, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Button, Shift, X, Y);
	}
	void OnMouseDown(long Button, long Shift, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Button, Shift, X, Y);
	}
	void OnMouseMove(long Shift, long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Shift, X, Y);
	}
	void OnChangeColor(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	void OnChangeOrder(long SeriesIndex1, long SeriesIndex2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex1, SeriesIndex2);
	}
	STDMETHOD(OnOtherItemsChange)()
	{
		HRESULT result;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_HRESULT, (void*)&result, nullptr);
		return result;
	}
	STDMETHOD(OnRefresh)()
	{
		HRESULT result;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_HRESULT, (void*)&result, nullptr);
		return result;
	}
	void OnRemovedSeries(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}

	// ITeeListBoxEvents properties
public:

};
