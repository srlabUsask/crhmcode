// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CZoomFilter wrapper class

class CZoomFilter : public COleDispatchDriver
{
public:
	CZoomFilter() {} // Calls COleDispatchDriver default constructor
	CZoomFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CZoomFilter(const CZoomFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IZoomFilter methods
public:
	double get_Percent()
	{
		double result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Percent(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Smooth()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Smooth(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IZoomFilter properties
public:

};
