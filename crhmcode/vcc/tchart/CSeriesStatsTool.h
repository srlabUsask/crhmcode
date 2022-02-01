// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSeriesStatsTool wrapper class

class CSeriesStatsTool : public COleDispatchDriver
{
public:
	CSeriesStatsTool() {} // Calls COleDispatchDriver default constructor
	CSeriesStatsTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSeriesStatsTool(const CSeriesStatsTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISeriesStatsTool methods
public:
	VARIANT get_Series()
	{
		VARIANT result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Series(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	LPDISPATCH get_Statistics()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void FreeStatsSeries()
	{
		InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	double Kurtosis()
	{
		double result;
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}
	double Mean()
	{
		double result;
		InvokeHelper(0x130, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}
	double Skewness()
	{
		double result;
		InvokeHelper(0x131, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}
	double StdDeviation()
	{
		double result;
		InvokeHelper(0x132, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}

	// ISeriesStatsTool properties
public:

};
