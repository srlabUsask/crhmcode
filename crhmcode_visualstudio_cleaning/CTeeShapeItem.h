// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeShapeItem wrapper class

class CTeeShapeItem : public COleDispatchDriver
{
public:
	CTeeShapeItem() {} // Calls COleDispatchDriver default constructor
	CTeeShapeItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeShapeItem(const CTeeShapeItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeShapeItem methods
public:
	LPDISPATCH get_Shape()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// ITeeShapeItem properties
public:

};
