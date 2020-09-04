// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGridBandTool wrapper class

class CGridBandTool : public COleDispatchDriver
{
public:
	CGridBandTool() {} // Calls COleDispatchDriver default constructor
	CGridBandTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGridBandTool(const CGridBandTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGridBandTool methods
public:
	VARIANT get_Axis()
	{
		VARIANT result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Axis(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	LPDISPATCH get_Band1()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Band2()
	{
		LPDISPATCH result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_BandBackColor(long ABand)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, ABand);
		return result;
	}

	// IGridBandTool properties
public:

};

