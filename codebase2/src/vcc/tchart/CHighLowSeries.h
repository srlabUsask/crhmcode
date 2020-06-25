// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CHighLowSeries wrapper class

class CHighLowSeries : public COleDispatchDriver
{
public:
	CHighLowSeries() {} // Calls COleDispatchDriver default constructor
	CHighLowSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CHighLowSeries(const CHighLowSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IHighLowSeries methods
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
	LPDISPATCH get_HighBrush()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_HighPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_LowBrush()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_LowPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IHighLowSeries properties
public:

};

