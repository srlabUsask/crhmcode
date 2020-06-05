// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAxisGridPen wrapper class

class CAxisGridPen : public COleDispatchDriver
{
public:
	CAxisGridPen() {} // Calls COleDispatchDriver default constructor
	CAxisGridPen(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisGridPen(const CAxisGridPen& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAxisGridPen methods
public:
	long get_DrawEvery()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DrawEvery(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_ZPosition()
	{
		double result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_ZPosition(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IAxisGridPen properties
public:

};

