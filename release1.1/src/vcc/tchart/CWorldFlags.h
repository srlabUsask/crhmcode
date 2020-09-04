// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CWorldFlags wrapper class

class CWorldFlags : public COleDispatchDriver
{
public:
	CWorldFlags() {} // Calls COleDispatchDriver default constructor
	CWorldFlags(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWorldFlags(const CWorldFlags& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IWorldFlags methods
public:
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IWorldFlags properties
public:

};
