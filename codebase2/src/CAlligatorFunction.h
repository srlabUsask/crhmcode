// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAlligatorFunction wrapper class

class CAlligatorFunction : public COleDispatchDriver
{
public:
	CAlligatorFunction() {} // Calls COleDispatchDriver default constructor
	CAlligatorFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAlligatorFunction(const CAlligatorFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAlligatorFunction methods
public:
	LPDISPATCH get_TeethPen()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_LipsPen()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IAlligatorFunction properties
public:

};

