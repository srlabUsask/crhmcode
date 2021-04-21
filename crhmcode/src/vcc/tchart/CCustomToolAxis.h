// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCustomToolAxis wrapper class

class CCustomToolAxis : public COleDispatchDriver
{
public:
	CCustomToolAxis() {} // Calls COleDispatchDriver default constructor
	CCustomToolAxis(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCustomToolAxis(const CCustomToolAxis& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICustomToolAxis methods
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

	// ICustomToolAxis properties
public:

};

