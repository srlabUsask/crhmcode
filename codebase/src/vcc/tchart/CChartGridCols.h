// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartGridCols wrapper class

class CChartGridCols : public COleDispatchDriver
{
public:
	CChartGridCols() {} // Calls COleDispatchDriver default constructor
	CChartGridCols(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartGridCols(const CChartGridCols& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartGridCols methods
public:
	long get_Col()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Col(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Widths(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void put_Widths(long Index, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}

	// IChartGridCols properties
public:

};

