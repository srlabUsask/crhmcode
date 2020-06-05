// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CBaseHighLowSeries wrapper class

class CBaseHighLowSeries : public COleDispatchDriver
{
public:
	CBaseHighLowSeries() {} // Calls COleDispatchDriver default constructor
	CBaseHighLowSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CBaseHighLowSeries(const CBaseHighLowSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IBaseHighLowSeries methods
public:
	long AddHighLow(double AX, double AHigh, double ALow, LPCTSTR AXLabel, unsigned long AColor)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_BSTR VTS_UI4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AX, AHigh, ALow, AXLabel, AColor);
		return result;
	}
	LPDISPATCH get_HighValues()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_LowValues()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	double MaxYValue()
	{
		double result;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}
	double MinYValue()
	{
		double result;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}

	// IBaseHighLowSeries properties
public:

};

