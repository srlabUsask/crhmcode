// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCustomAxes wrapper class

class CCustomAxes : public COleDispatchDriver
{
public:
	CCustomAxes() {} // Calls COleDispatchDriver default constructor
	CCustomAxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCustomAxes(const CCustomAxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICustomAxes methods
public:
	long Add()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Items(long AIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, AIndex);
		return result;
	}
	void ResetScales(long AIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, AIndex);
	}

	// ICustomAxes properties
public:

};

