// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAxisScrollTool wrapper class

class CAxisScrollTool : public COleDispatchDriver
{
public:
	CAxisScrollTool() {} // Calls COleDispatchDriver default constructor
	CAxisScrollTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisScrollTool(const CAxisScrollTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAxisScrollTool methods
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
	BOOL get_ScrollInverted()
	{
		BOOL result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ScrollInverted(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IAxisScrollTool properties
public:

};

