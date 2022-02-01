// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSurfaceNearestTool wrapper class

class CSurfaceNearestTool : public COleDispatchDriver
{
public:
	CSurfaceNearestTool() {} // Calls COleDispatchDriver default constructor
	CSurfaceNearestTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSurfaceNearestTool(const CSurfaceNearestTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISurfaceNearestTool methods
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
	unsigned long get_CellColor()
	{
		unsigned long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_CellColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_ColumnColor()
	{
		unsigned long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_ColumnColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_RowColor()
	{
		unsigned long result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_RowColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_SelectedCell()
	{
		long result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_SelectedCell(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long GetRow()
	{
		long result;
		InvokeHelper(0x12e, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long GetCol()
	{
		long result;
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}

	// ISurfaceNearestTool properties
public:

};
