// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CZoomPanning wrapper class

class CZoomPanning : public COleDispatchDriver
{
public:
	CZoomPanning() {} // Calls COleDispatchDriver default constructor
	CZoomPanning(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CZoomPanning(const CZoomPanning& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IZoomPanning methods
public:
	BOOL get_Active()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Active(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IZoomPanning properties
public:

};
