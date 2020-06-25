// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPrinterSettings wrapper class

class CPrinterSettings : public COleDispatchDriver
{
public:
	CPrinterSettings() {} // Calls COleDispatchDriver default constructor
	CPrinterSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPrinterSettings(const CPrinterSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPrinterSettings methods
public:
	short get_Orientation()
	{
		short result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Orientation(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_PaperSize()
	{
		short result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_PaperSize(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_PaperLength()
	{
		short result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_PaperLength(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_PaperWidth()
	{
		short result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_PaperWidth(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Copies()
	{
		short result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Copies(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_PrintQuality()
	{
		short result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_PrintQuality(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Color()
	{
		short result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Color(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Duplex()
	{
		short result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Duplex(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Scale()
	{
		short result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Scale(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_DefaultSource()
	{
		short result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_DefaultSource(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xd2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_TTOption()
	{
		short result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_TTOption(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xd3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Collate()
	{
		short result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Collate(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xd4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_SpecVersion()
	{
		long result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_SpecVersion(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DriverVersion()
	{
		long result;
		InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DriverVersion(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Size()
	{
		long result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Size(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DriverExtra()
	{
		long result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DriverExtra(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_LogPixels()
	{
		long result;
		InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LogPixels(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Fields()
	{
		long result;
		InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Fields(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xda, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BitsPerPel()
	{
		long result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BitsPerPel(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xdb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_PelsWidth()
	{
		long result;
		InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PelsWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xdc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_PelsHeight()
	{
		long result;
		InvokeHelper(0xdd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PelsHeight(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xdd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DisplayFlags()
	{
		long result;
		InvokeHelper(0xde, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DisplayFlags(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xde, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DisplayFrequency()
	{
		long result;
		InvokeHelper(0xdf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DisplayFrequency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xdf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ICMMethod()
	{
		long result;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ICMMethod(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ICMIntent()
	{
		long result;
		InvokeHelper(0xe1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ICMIntent(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_YResolution()
	{
		short result;
		InvokeHelper(0xe2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_YResolution(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xe2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_DeviceName()
	{
		CString result;
		InvokeHelper(0xe3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_DeviceName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xe3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_FormName()
	{
		CString result;
		InvokeHelper(0xe4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_FormName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xe4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void InitPrinterOrientation()
	{
		InvokeHelper(0xe5, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	// IPrinterSettings properties
public:

};
