// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTrendFunction wrapper class

class CTrendFunction : public COleDispatchDriver
{
public:
	CTrendFunction() {} // Calls COleDispatchDriver default constructor
	CTrendFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTrendFunction(const CTrendFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITrendFunction methods
public:
	long CalculateTrend(double * m, double * b, long SourceSeriesIndex, long FirstIndex, long LastIndex)
	{
		long result;
		static BYTE parms[] = VTS_PR8 VTS_PR8 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, m, b, SourceSeriesIndex, FirstIndex, LastIndex);
		return result;
	}

	// ITrendFunction properties
public:

};
