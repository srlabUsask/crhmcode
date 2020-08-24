// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCompressFunction wrapper class

class CCompressFunction : public COleDispatchDriver
{
public:
	CCompressFunction() {} // Calls COleDispatchDriver default constructor
	CCompressFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCompressFunction(const CCompressFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICompressFunction methods
public:
	long get_Compress()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Compress(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ICompressFunction properties
public:

};

