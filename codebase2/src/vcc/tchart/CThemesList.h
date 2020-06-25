// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CThemesList wrapper class

class CThemesList : public COleDispatchDriver
{
public:
	CThemesList() {} // Calls COleDispatchDriver default constructor
	CThemesList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CThemesList(const CThemesList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IThemesList methods
public:
	void ApplyFromChartLink(long Chart)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Chart);
	}
	void ApplyFromTee(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void ApplyFromChartLinkx64(VARIANT& Chartx64)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &Chartx64);
	}

	// IThemesList properties
public:

};
