// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPointArray wrapper class

class CPointArray : public COleDispatchDriver
{
public:
	CPointArray() {} // Calls COleDispatchDriver default constructor
	CPointArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPointArray(const CPointArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPointArray methods
public:
	long get_Count()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IPointArray properties
public:

};
