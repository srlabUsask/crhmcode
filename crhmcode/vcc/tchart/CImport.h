// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CImport wrapper class

class CImport : public COleDispatchDriver
{
public:
	CImport() {} // Calls COleDispatchDriver default constructor
	CImport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CImport(const CImport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IImport methods
public:
	void LoadFromFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void LoadFromURL(LPCTSTR URL)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, URL);
	}
	void LoadFromStream(VARIANT& AStream)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &AStream);
	}
	void LoadFromBase64Stream(VARIANT& AStream)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &AStream);
	}
	BOOL get_V5TeeCompatible()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_V5TeeCompatible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_CheckURL()
	{
		BOOL result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_CheckURL(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IImport properties
public:

};

