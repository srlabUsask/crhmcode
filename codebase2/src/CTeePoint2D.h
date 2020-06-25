// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeePoint2D wrapper class

class CTeePoint2D : public COleDispatchDriver
{
public:
	CTeePoint2D() {} // Calls COleDispatchDriver default constructor
	CTeePoint2D(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeePoint2D(const CTeePoint2D& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeePoint2D methods
public:
	double get_X()
	{
		double result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_X(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Y()
	{
		double result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Y(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ITeePoint2D properties
public:

};
