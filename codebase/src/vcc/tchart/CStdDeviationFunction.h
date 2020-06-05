// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CStdDeviationFunction wrapper class

class CStdDeviationFunction : public COleDispatchDriver
{
public:
	CStdDeviationFunction() {} // Calls COleDispatchDriver default constructor
	CStdDeviationFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CStdDeviationFunction(const CStdDeviationFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IStdDeviationFunction methods
public:
	BOOL get_Complete()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Complete(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IStdDeviationFunction properties
public:

};
