// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CNativeExport wrapper class

class CNativeExport : public COleDispatchDriver
{
public:
	CNativeExport() {} // Calls COleDispatchDriver default constructor
	CNativeExport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CNativeExport(const CNativeExport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// INativeExport methods
public:
	void SaveToFile(LPCTSTR FileName, BOOL IncludeData)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName, IncludeData);
	}
	VARIANT SaveToStream(BOOL IncludeData)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, IncludeData);
		return result;
	}
	VARIANT SaveToBase64Stream(BOOL IncludeData)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, IncludeData);
		return result;
	}

	// INativeExport properties
public:

};
