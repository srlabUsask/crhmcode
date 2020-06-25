// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPyramidSeries wrapper class

class CPyramidSeries : public COleDispatchDriver
{
public:
	CPyramidSeries() {} // Calls COleDispatchDriver default constructor
	CPyramidSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPyramidSeries(const CPyramidSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPyramidSeries methods
public:
	long get_SizePercent()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_SizePercent(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IPyramidSeries properties
public:

};
