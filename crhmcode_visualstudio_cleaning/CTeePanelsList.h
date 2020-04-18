// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeePanelsList wrapper class

class CTeePanelsList : public COleDispatchDriver
{
public:
	CTeePanelsList() {} // Calls COleDispatchDriver default constructor
	CTeePanelsList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeePanelsList(const CTeePanelsList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeePanelsList methods
public:
	void Delete(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}
	void Clear()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	// ITeePanelsList properties
public:

};
