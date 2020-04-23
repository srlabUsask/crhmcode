// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPieAngle wrapper class

class CPieAngle : public COleDispatchDriver
{
public:
	CPieAngle() {} // Calls COleDispatchDriver default constructor
	CPieAngle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPieAngle(const CPieAngle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPieAngle methods
public:
	double get_StartAngle()
	{
		double result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_StartAngle(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_MidAngle()
	{
		double result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_MidAngle(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_EndAngle()
	{
		double result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_EndAngle(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IPieAngle properties
public:

};
