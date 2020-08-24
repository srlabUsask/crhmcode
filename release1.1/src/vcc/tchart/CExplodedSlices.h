// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CExplodedSlices wrapper class

class CExplodedSlices : public COleDispatchDriver
{
public:
	CExplodedSlices() {} // Calls COleDispatchDriver default constructor
	CExplodedSlices(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExplodedSlices(const CExplodedSlices& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IExplodedSlices methods
public:
	long get_Value(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void put_Value(long Index, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}

	// IExplodedSlices properties
public:

};

