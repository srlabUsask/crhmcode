// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTransposeSeriesTool wrapper class

class CTransposeSeriesTool : public COleDispatchDriver
{
public:
	CTransposeSeriesTool() {} // Calls COleDispatchDriver default constructor
	CTransposeSeriesTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTransposeSeriesTool(const CTransposeSeriesTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITransposeSeriesTool methods
public:
	void Transpose()
	{
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	// ITransposeSeriesTool properties
public:

};
