// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CMovingAvgFunction wrapper class

class CMovingAvgFunction : public COleDispatchDriver
{
public:
	CMovingAvgFunction() {} // Calls COleDispatchDriver default constructor
	CMovingAvgFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMovingAvgFunction(const CMovingAvgFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMovingAvgFunction methods
public:
	BOOL get_Weighted()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Weighted(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IMovingAvgFunction properties
public:

};
