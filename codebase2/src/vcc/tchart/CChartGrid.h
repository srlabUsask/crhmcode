// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CChartGrid wrapper class

class CChartGrid : public COleDispatchDriver
{
public:
	CChartGrid() {} // Calls COleDispatchDriver default constructor
	CChartGrid(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChartGrid(const CChartGrid& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IChartGrid methods
public:
	void put_Chart(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void put_ChartLink(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void put_ChartLinkx64(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	long get_Col()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Col(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ColCount()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Colwidths(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void put_Colwidths(long Index, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}
	BOOL get_EditorMode()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_EditorMode(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_GridHeight()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_GridWidth()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_LeftCol()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LeftCol(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_GridLink()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void RecalcDimensions()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL get_ShowLabels()
	{
		BOOL result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowLabels(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowColors()
	{
		BOOL result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowColors(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowFields()
	{
		BOOL result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowFields(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH Cols()
	{
		LPDISPATCH result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH Rows()
	{
		LPDISPATCH result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_DefaultColWidth()
	{
		long result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DefaultColWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Grid3DMode()
	{
		BOOL result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Grid3DMode(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_LabelHeader()
	{
		CString result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_LabelHeader(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AllowAppend()
	{
		BOOL result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllowAppend(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ReadOnly()
	{
		BOOL result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ReadOnly(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AllowInsertSeries()
	{
		BOOL result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AllowInsertSeries(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ColorsColumn()
	{
		long result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_FirstRowNum()
	{
		long result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_LabelsColumn()
	{
		long result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	BOOL get_SeriesSymbolClickable()
	{
		BOOL result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_SeriesSymbolClickable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ShowXValues()
	{
		long result;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ShowXValues(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TopRow()
	{
		long result;
		InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TopRow(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_RowHeights(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void put_RowHeights(long Index, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}
	LPDISPATCH get_GradientCell()
	{
		LPDISPATCH result;
		InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	VARIANT get_GridLinkx64()
	{
		VARIANT result;
		InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}

	// IChartGrid properties
public:

};

