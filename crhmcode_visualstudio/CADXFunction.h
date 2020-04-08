// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CADXFunction wrapper class

class CADXFunction : public COleDispatchDriver
{
public:
	CADXFunction() {} // Calls COleDispatchDriver default constructor
	CADXFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CADXFunction(const CADXFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IADXFunction methods
public:
	LPDISPATCH get_DMDown()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_DMUp()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IADXFunction properties
public:

};

