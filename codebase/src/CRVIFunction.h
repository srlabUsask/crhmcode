// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CRVIFunction wrapper class

class CRVIFunction : public COleDispatchDriver
{
public:
	CRVIFunction() {} // Calls COleDispatchDriver default constructor
	CRVIFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRVIFunction(const CRVIFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IRVIFunction methods
public:
	LPDISPATCH get_SignalPen()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Signal()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IRVIFunction properties
public:

};
