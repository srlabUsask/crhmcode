// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCustomToolSeries wrapper class

class CCustomToolSeries : public COleDispatchDriver
{
public:
	CCustomToolSeries() {} // Calls COleDispatchDriver default constructor
	CCustomToolSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCustomToolSeries(const CCustomToolSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICustomToolSeries methods
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

	// ICustomToolSeries properties
public:

};

