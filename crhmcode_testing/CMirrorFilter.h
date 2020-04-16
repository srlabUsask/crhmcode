// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CMirrorFilter wrapper class

class CMirrorFilter : public COleDispatchDriver
{
public:
	CMirrorFilter() {} // Calls COleDispatchDriver default constructor
	CMirrorFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMirrorFilter(const CMirrorFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMirrorFilter methods
public:
	long get_Direction()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Direction(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IMirrorFilter properties
public:

};
