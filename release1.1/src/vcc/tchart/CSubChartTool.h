// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSubChartTool wrapper class

class CSubChartTool : public COleDispatchDriver
{
public:
	CSubChartTool() {} // Calls COleDispatchDriver default constructor
	CSubChartTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSubChartTool(const CSubChartTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISubChartTool methods
public:
	LPDISPATCH get_Charts()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	short get_Cursor()
	{
		short result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Cursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ISubChartTool properties
public:

};
