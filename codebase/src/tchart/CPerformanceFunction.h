// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPerformanceFunction wrapper class

class CPerformanceFunction : public COleDispatchDriver
{
public:
	CPerformanceFunction() {} // Calls COleDispatchDriver default constructor
	CPerformanceFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPerformanceFunction(const CPerformanceFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPerformanceFunction methods
public:
	double Calculate(long SourceSeriesIndex, long FirstIndex, long LastIndex)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_R8, (void*)&result, parms, SourceSeriesIndex, FirstIndex, LastIndex);
		return result;
	}

	// IPerformanceFunction properties
public:

};
