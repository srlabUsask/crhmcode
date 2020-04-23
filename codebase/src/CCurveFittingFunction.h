// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCurveFittingFunction wrapper class

class CCurveFittingFunction : public COleDispatchDriver
{
public:
	CCurveFittingFunction() {} // Calls COleDispatchDriver default constructor
	CCurveFittingFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCurveFittingFunction(const CCurveFittingFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICurveFittingFunction methods
public:
	long get_PolyDegree()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PolyDegree(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TypeFitting()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TypeFitting(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_FirstPoint()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_FirstPoint(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_LastPoint()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LastPoint(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_FirstCalcPoint()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_FirstCalcPoint(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_LastCalcPoint()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LastCalcPoint(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_AnswerVector(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	double GetCurveYValue(double X)
	{
		double result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_R8, (void*)&result, parms, X);
		return result;
	}

	// ICurveFittingFunction properties
public:

};

