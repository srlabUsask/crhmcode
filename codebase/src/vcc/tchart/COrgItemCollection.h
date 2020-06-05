// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// COrgItemCollection wrapper class

class COrgItemCollection : public COleDispatchDriver
{
public:
	COrgItemCollection() {} // Calls COleDispatchDriver default constructor
	COrgItemCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COrgItemCollection(const COrgItemCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IOrgItemCollection methods
public:
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	// IOrgItemCollection properties
public:

};
