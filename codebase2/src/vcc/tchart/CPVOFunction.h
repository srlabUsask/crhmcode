// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPVOFunction wrapper class

class CPVOFunction : public COleDispatchDriver
{
public:
	CPVOFunction() {} // Calls COleDispatchDriver default constructor
	CPVOFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPVOFunction(const CPVOFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPVOFunction methods
public:
	BOOL get_Percentage()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Percentage(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Period2()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Period2(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IPVOFunction properties
public:

};
