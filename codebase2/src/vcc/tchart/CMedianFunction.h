// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CMedianFunction wrapper class

class CMedianFunction : public COleDispatchDriver
{
public:
	CMedianFunction() {} // Calls COleDispatchDriver default constructor
	CMedianFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMedianFunction(const CMedianFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IMedianFunction methods
public:
	BOOL get_IncludeNulls()
	{
		BOOL result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_IncludeNulls(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IMedianFunction properties
public:

};
