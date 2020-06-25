// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CGIFExport wrapper class

class CGIFExport : public COleDispatchDriver
{
public:
	CGIFExport() {} // Calls COleDispatchDriver default constructor
	CGIFExport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGIFExport(const CGIFExport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IGIFExport methods
public:
	long get_Width()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void SaveToFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	VARIANT SaveToStream()
	{
		VARIANT result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	long get_Compression()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Compression(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DitherMode()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DitherMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ColorReduction()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ColorReduction(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IGIFExport properties
public:

};

