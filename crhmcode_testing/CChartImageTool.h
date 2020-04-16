// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartImageTool wrapper class

class CChartImageTool : public COleDispatchDriver
{
public:
	CChartImageTool() {} // Calls COleDispatchDriver default constructor
	CChartImageTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartImageTool(const CChartImageTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartImageTool methods
public:
	VARIANT get_Series()
	{
		VARIANT result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Series(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	void ImageLoad(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void ImageClear()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IChartImageTool properties
public:

};

