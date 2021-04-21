// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGridTransposeTool wrapper class

class CGridTransposeTool : public COleDispatchDriver
{
public:
	CGridTransposeTool() {} // Calls COleDispatchDriver default constructor
	CGridTransposeTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGridTransposeTool(const CGridTransposeTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGridTransposeTool methods
public:
	void Transpose()
	{
		InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	VARIANT get_Series()
	{
		VARIANT result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Series(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}

	// IGridTransposeTool properties
public:

};

