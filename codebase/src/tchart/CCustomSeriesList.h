// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCustomSeriesList wrapper class

class CCustomSeriesList : public COleDispatchDriver
{
public:
	CCustomSeriesList() {} // Calls COleDispatchDriver default constructor
	CCustomSeriesList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCustomSeriesList(const CCustomSeriesList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICustomSeriesList methods
public:
	void ClearValues()
	{
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long First()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long Last()
	{
		long result;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// ICustomSeriesList properties
public:

};

