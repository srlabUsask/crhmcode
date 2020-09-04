// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAnimations wrapper class

class CAnimations : public COleDispatchDriver
{
public:
	CAnimations() {} // Calls COleDispatchDriver default constructor
	CAnimations(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAnimations(const CAnimations& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAnimations methods
public:
	LPDISPATCH get_Animation(long AIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, AIndex);
		return result;
	}

	// IAnimations properties
public:

};

