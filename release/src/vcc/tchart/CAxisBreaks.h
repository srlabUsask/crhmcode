// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAxisBreaks wrapper class

class CAxisBreaks : public COleDispatchDriver
{
public:
	CAxisBreaks() {} // Calls COleDispatchDriver default constructor
	CAxisBreaks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisBreaks(const CAxisBreaks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAxisBreaks methods
public:
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long Add(double AStart, double AEnd)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AStart, AEnd);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void Clear()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Delete(long AIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, AIndex);
	}

	// IAxisBreaks properties
public:

};

