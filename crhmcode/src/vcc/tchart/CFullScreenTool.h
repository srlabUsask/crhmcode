// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CFullScreenTool wrapper class

class CFullScreenTool : public COleDispatchDriver
{
public:
	CFullScreenTool() {} // Calls COleDispatchDriver default constructor
	CFullScreenTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFullScreenTool(const CFullScreenTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IFullScreenTool methods
public:
	long get_ReleaseKey()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ReleaseKey(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IFullScreenTool properties
public:

};

