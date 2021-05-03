// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSkewnessFunction wrapper class

class CSkewnessFunction : public COleDispatchDriver
{
public:
	CSkewnessFunction() {} // Calls COleDispatchDriver default constructor
	CSkewnessFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSkewnessFunction(const CSkewnessFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISkewnessFunction methods
public:
	BOOL get_Complete()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Complete(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ISkewnessFunction properties
public:

};
