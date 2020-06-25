// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartCollection wrapper class

class CChartCollection : public COleDispatchDriver
{
public:
	CChartCollection() {} // Calls COleDispatchDriver default constructor
	CChartCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartCollection(const CChartCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartCollection methods
public:
	LPDISPATCH AddChart(LPCTSTR AName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, AName);
		return result;
	}
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	void Clear()
	{
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Delete(long AIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, AIndex);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	// IChartCollection properties
public:

};

