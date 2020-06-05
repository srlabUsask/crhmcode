// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CExport0 wrapper class

class CExport0 : public COleDispatchDriver
{
public:
	CExport0() {} // Calls COleDispatchDriver default constructor
	CExport0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExport0(const CExport0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IExport methods
public:
	void CopyToClipboardBitmap()
	{
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void CopyToClipboardMetafile(BOOL Enhanced)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Enhanced);
	}
	void SaveToBitmapFile(LPCTSTR FileName, long DPI)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName, DPI);
	}
	void SaveToFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void SaveToJPEGFile(LPCTSTR FileName, BOOL Gray, long Performance, long Quality, long Width, long Height, long DPI)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName, Gray, Performance, Quality, Width, Height, DPI);
	}
	void SaveToMetafile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void SaveToMetafileEnh(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void ShowExport()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	CString SaveChartDialog()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void ConvertTeeFileToText(LPCTSTR InputFile, LPCTSTR OutputFile)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, InputFile, OutputFile);
	}
	VARIANT Stream(long StreamType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, StreamType);
		return result;
	}
	LPDISPATCH get_asJPEG()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPNG()
	{
		LPDISPATCH result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGIF()
	{
		LPDISPATCH result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBMP()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPCX()
	{
		LPDISPATCH result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asMetafile()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asNative()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asXML()
	{
		LPDISPATCH result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asXLS()
	{
		LPDISPATCH result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHTML()
	{
		LPDISPATCH result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asText()
	{
		LPDISPATCH result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void EmailFile(LPCTSTR FileName, LPCTSTR Subject)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName, Subject);
	}
	LPDISPATCH get_asPDF()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asEPS()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSVG()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	CString get_LabelHeader()
	{
		CString result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_LabelHeader(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asXAML()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void SaveToXMLFile(LPCTSTR FileName, BOOL IncludeData, BOOL XMLHeader)
	{
		static BYTE parms[] = VTS_BSTR VTS_BOOL VTS_BOOL;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName, IncludeData, XMLHeader);
	}
	VARIANT SaveToXMLStream(BOOL IncludeData, BOOL XMLHeader)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BOOL VTS_BOOL;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, IncludeData, XMLHeader);
		return result;
	}
	LPDISPATCH get_asFlex()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asJavaScript()
	{
		LPDISPATCH result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asJSON()
	{
		LPDISPATCH result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asOpenDocument()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IExport properties
public:

};

