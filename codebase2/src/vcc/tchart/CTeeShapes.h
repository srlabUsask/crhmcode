// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeShapes wrapper class

class CTeeShapes : public COleDispatchDriver
{
public:
	CTeeShapes() {} // Calls COleDispatchDriver default constructor
	CTeeShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeShapes(const CTeeShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeShapes methods
public:
	long Add()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Item(long AIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, AIndex);
		return result;
	}

	// ITeeShapes properties
public:

};
