// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeePicture wrapper class

class CTeePicture : public COleDispatchDriver
{
public:
	CTeePicture() {} // Calls COleDispatchDriver default constructor
	CTeePicture(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeePicture(const CTeePicture& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeePicture methods
public:
	LPDISPATCH get_Filters()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void LoadImage(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void AssignImage(long ImageHandle)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ImageHandle);
	}
	void ClearImage()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL ShowFiltersEditor()
	{
		BOOL result;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	long get_Handle()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void SaveToFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}

	// ITeePicture properties
public:

};
