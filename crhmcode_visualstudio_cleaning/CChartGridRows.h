// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartGridRows wrapper class

class CChartGridRows : public COleDispatchDriver
{
public:
	CChartGridRows() {} // Calls COleDispatchDriver default constructor
	CChartGridRows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartGridRows(const CChartGridRows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartGridRows methods
public:
	long get_Row()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Row(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Heights(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void put_Heights(long Index, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}

	// IChartGridRows properties
public:

};

