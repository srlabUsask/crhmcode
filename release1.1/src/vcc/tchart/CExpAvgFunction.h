// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CExpAvgFunction wrapper class

class CExpAvgFunction : public COleDispatchDriver
{
public:
	CExpAvgFunction() {} // Calls COleDispatchDriver default constructor
	CExpAvgFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExpAvgFunction(const CExpAvgFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IExpAvgFunction methods
public:
	double get_Weight()
	{
		double result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Weight(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IExpAvgFunction properties
public:

};

