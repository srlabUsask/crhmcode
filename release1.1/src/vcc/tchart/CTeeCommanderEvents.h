// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeCommanderEvents wrapper class

class CTeeCommanderEvents : public COleDispatchDriver
{
public:
	CTeeCommanderEvents() {} // Calls COleDispatchDriver default constructor
	CTeeCommanderEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeCommanderEvents(const CTeeCommanderEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeCommanderEvents methods
public:
	void OnEditedChart()
	{
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	// ITeeCommanderEvents properties
public:

};
