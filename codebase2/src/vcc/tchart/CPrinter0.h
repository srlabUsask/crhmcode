// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPrinter0 wrapper class

class CPrinter0 : public COleDispatchDriver
{
public:
	CPrinter0() {} // Calls COleDispatchDriver default constructor
	CPrinter0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPrinter0(const CPrinter0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPrinter methods
public:
	long get_Detail()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Detail(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MarginBottom()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MarginBottom(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MarginLeft()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MarginLeft(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MarginTop()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MarginTop(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MarginRight()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MarginRight(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Orientation()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Orientation(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void Print()
	{
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void PrintLandscape()
	{
		InvokeHelper(0x41, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void PrintPortrait()
	{
		InvokeHelper(0x43, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void ShowPreview()
	{
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void PrintPartial(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	void BeginDoc()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void EndDoc()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_PrinterIndex()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PrinterIndex(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_PrinterCount()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	CString get_PrinterDescription(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	void PrintChart()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_PageHeight()
	{
		long result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_PageWidth()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	CString get_JobTitle()
	{
		CString result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_JobTitle(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_PrintProportional()
	{
		BOOL result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_PrintProportional(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void PrintPartialHandle(VARIANT& DC, long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &DC, Left, Top, Right, Bottom);
	}
	void PrintPages(long FromPage, long ToPage)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FromPage, ToPage);
	}
	BOOL ShowSetupDlg()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_PrinterSettings()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IPrinter properties
public:

};
