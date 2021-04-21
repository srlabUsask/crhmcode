// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartAnimations wrapper class

class CChartAnimations : public COleDispatchDriver
{
public:
	CChartAnimations() {} // Calls COleDispatchDriver default constructor
	CChartAnimations(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartAnimations(const CChartAnimations& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartAnimations methods
public:
	LPDISPATCH get_asExpand()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTransformation()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IChartAnimations properties
public:

};

