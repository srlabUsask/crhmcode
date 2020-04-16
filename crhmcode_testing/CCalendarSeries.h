// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCalendarSeries wrapper class

class CCalendarSeries : public COleDispatchDriver
{
public:
	CCalendarSeries() {} // Calls COleDispatchDriver default constructor
	CCalendarSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCalendarSeries(const CCalendarSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICalendarSeries methods
public:
	double get_Date()
	{
		double result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Date(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Days()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Months()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Trailing()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Sunday()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Today()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Weekdays()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void NextMonth()
	{
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void PreviousMonth()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	TeeRect RectCell(long Column, long Row)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Column, Row);
	}
	long Rows()
	{
		long result;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	TeeRect SeriesRect()
	{
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL get_NextButtonVisible()
	{
		BOOL result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_NextButtonVisible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_PreviousButtonVisible()
	{
		BOOL result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_PreviousButtonVisible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL ClickedDate(long X, long Y, DATE * ADate)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PDATE;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, X, Y, ADate);
		return result;
	}

	// ICalendarSeries properties
public:

};

