// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CExtraLegendTool wrapper class

class CExtraLegendTool : public COleDispatchDriver
{
public:
	CExtraLegendTool() {} // Calls COleDispatchDriver default constructor
	CExtraLegendTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExtraLegendTool(const CExtraLegendTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IExtraLegendTool methods
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
	LPDISPATCH get_Legend()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IExtraLegendTool properties
public:

};

