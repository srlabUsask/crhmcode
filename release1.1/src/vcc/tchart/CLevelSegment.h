// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CLevelSegment wrapper class

class CLevelSegment : public COleDispatchDriver
{
public:
	CLevelSegment() {} // Calls COleDispatchDriver default constructor
	CLevelSegment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLevelSegment(const CLevelSegment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ILevelSegment methods
public:
	long get_NumPoints()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Points(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// ILevelSegment properties
public:

};
