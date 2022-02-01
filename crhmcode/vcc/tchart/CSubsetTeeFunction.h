// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSubsetTeeFunction wrapper class

class CSubsetTeeFunction : public COleDispatchDriver
{
public:
	CSubsetTeeFunction() {} // Calls COleDispatchDriver default constructor
	CSubsetTeeFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSubsetTeeFunction(const CSubsetTeeFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISubsetTeeFunction methods
public:
	double get_StartValue()
	{
		double result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_StartValue(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_EndValue()
	{
		double result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_EndValue(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ISubsetTeeFunction properties
public:

};
