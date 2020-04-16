// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPieTool wrapper class

class CPieTool : public COleDispatchDriver
{
public:
	CPieTool() {} // Calls COleDispatchDriver default constructor
	CPieTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPieTool(const CPieTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPieTool methods
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
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Style()
	{
		long result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Style(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Slice()
	{
		long result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	// IPieTool properties
public:

};
