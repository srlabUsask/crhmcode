// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CFloatXYZ wrapper class

class CFloatXYZ : public COleDispatchDriver
{
public:
	CFloatXYZ() {} // Calls COleDispatchDriver default constructor
	CFloatXYZ(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFloatXYZ(const CFloatXYZ& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IFloatXYZ methods
public:
	double get_X()
	{
		double result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_X(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Y()
	{
		double result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Y(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Z()
	{
		double result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Z(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IFloatXYZ properties
public:

};

