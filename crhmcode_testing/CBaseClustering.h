// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CBaseClustering wrapper class

class CBaseClustering : public COleDispatchDriver
{
public:
	CBaseClustering() {} // Calls COleDispatchDriver default constructor
	CBaseClustering(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CBaseClustering(const CBaseClustering& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IBaseClustering methods
public:
	long get_Linkage()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Linkage(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IBaseClustering properties
public:

};

