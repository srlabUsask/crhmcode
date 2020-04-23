// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CPolygonSeries wrapper class

class CPolygonSeries : public COleDispatchDriver
{
public:
	CPolygonSeries() {} // Calls COleDispatchDriver default constructor
	CPolygonSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPolygonSeries(const CPolygonSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IPolygonSeries methods
public:
	BOOL get_Active()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Active(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asArea()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asArrow()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBar()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBubble()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asCandle()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asErrorBar()
	{
		LPDISPATCH result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asFastLine()
	{
		LPDISPATCH result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGantt()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHorizBar()
	{
		LPDISPATCH result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLine()
	{
		LPDISPATCH result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPie()
	{
		LPDISPATCH result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPoint()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPolar()
	{
		LPDISPATCH result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asShape()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSurface()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asVolume()
	{
		LPDISPATCH result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_Color()
	{
		unsigned long result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_Color(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ColorEachPoint()
	{
		BOOL result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ColorEachPoint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	short get_Cursor()
	{
		short result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Cursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	VARIANT get_DataSource()
	{
		VARIANT result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_DataSource(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	long get_FirstValueIndex()
	{
		long result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_FunctionType()
	{
		LPDISPATCH result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_HorizontalAxis()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_HorizontalAxis(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_LabelsSource()
	{
		CString result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_LabelsSource(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_LastValueIndex()
	{
		long result;
		InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Marks()
	{
		LPDISPATCH result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_PercentFormat()
	{
		CString result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_PercentFormat(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_PointColor(long Index)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, Index);
		return result;
	}
	void put_PointColor(long Index, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}
	CString get_PointLabel(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	void put_PointLabel(long Index, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}
	double get_PointValue(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	void put_PointValue(long Index, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R8;
		InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, Index, newValue);
	}
	long get_SeriesType()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ShowInLegend()
	{
		BOOL result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowInLegend(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Title()
	{
		CString result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Title(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_ValueFormat()
	{
		CString result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_ValueFormat(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_ValueMarkText(long ValueIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ValueIndex);
		return result;
	}
	long get_VerticalAxis()
	{
		long result;
		InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_VerticalAxis(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_XValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_YValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long Add(double AValue, LPCTSTR ALabel, unsigned long Value)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_BSTR VTS_UI4;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AValue, ALabel, Value);
		return result;
	}
	long AddNull(LPCTSTR SomeLabel)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeLabel);
		return result;
	}
	long AddXY(double AX, double AY, LPCTSTR ALabel, unsigned long Value)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_BSTR VTS_UI4;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AX, AY, ALabel, Value);
		return result;
	}
	long CalcXPos(long SomeValueIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValueIndex);
		return result;
	}
	long CalcXPosValue(double SomeValue)
	{
		long result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValue);
		return result;
	}
	long CalcXSizeValue(double SomeValue)
	{
		long result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValue);
		return result;
	}
	long CalcYPos(long SomeValueIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValueIndex);
		return result;
	}
	long CalcYPosValue(double SomeValue)
	{
		long result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValue);
		return result;
	}
	long CalcYSizeValue(double SomeValue)
	{
		long result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValue);
		return result;
	}
	void CheckDataSource()
	{
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Clear()
	{
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long Clicked(long XCoord, long YCoord)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, parms, XCoord, YCoord);
		return result;
	}
	void Delete(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}
	void FillSampleValues(long NumValues)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, NumValues);
	}
	long GetMousePoint()
	{
		long result;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	BOOL IsNull(long ValueIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ValueIndex);
		return result;
	}
	void RefreshSeries()
	{
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void SetFunction(long AFunction)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, AFunction);
	}
	void SwapValues(long a, long b)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, a, b);
	}
	double XScreenToValue(long ScreenCoord)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_R8, (void*)&result, parms, ScreenCoord);
		return result;
	}
	CString XValueToText(double SomeValue)
	{
		CString result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, SomeValue);
		return result;
	}
	double YScreenToValue(long ScreenCoord)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_R8, (void*)&result, parms, ScreenCoord);
		return result;
	}
	CString YValueToText(double SomeValue)
	{
		CString result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, SomeValue);
		return result;
	}
	LPDISPATCH get_asBezier()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asContour()
	{
		LPDISPATCH result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asError()
	{
		LPDISPATCH result;
		InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPoint3D()
	{
		LPDISPATCH result;
		InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRadar()
	{
		LPDISPATCH result;
		InvokeHelper(0x47, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long AddNullXY(double X, double Y, LPCTSTR ALabel)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_BSTR;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y, ALabel);
		return result;
	}
	CString LegendString(long LegendIndex, long LegendTextStyle)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, LegendIndex, LegendTextStyle);
		return result;
	}
	unsigned long LegendItemColor(long LegendIndex)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, LegendIndex);
		return result;
	}
	long CountLegendItems()
	{
		long result;
		InvokeHelper(0x4b, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long LegendToValueIndex(long LegendIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LegendIndex);
		return result;
	}
	long VisibleCount()
	{
		long result;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void AssignValues(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	long get_HorizontalAxisCustom()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_HorizontalAxisCustom(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_VerticalAxisCustom()
	{
		long result;
		InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_VerticalAxisCustom(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asClock()
	{
		LPDISPATCH result;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asWindRose()
	{
		LPDISPATCH result;
		InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBar3D()
	{
		LPDISPATCH result;
		InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asImageBar()
	{
		LPDISPATCH result;
		InvokeHelper(0x53, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void DisconnectAxisCustom(BOOL IsHorizontal)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x54, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, IsHorizontal);
	}
	LPDISPATCH get_MouseValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void AddArray(long ArraySize, VARIANT& YArray, VARIANT& XArray)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ArraySize, &YArray, &XArray);
	}
	long get_Depth()
	{
		long result;
		InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Depth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x57, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asDonut()
	{
		LPDISPATCH result;
		InvokeHelper(0x59, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTriSurface()
	{
		LPDISPATCH result;
		InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBoxPlot()
	{
		LPDISPATCH result;
		InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHorizBoxPlot()
	{
		LPDISPATCH result;
		InvokeHelper(0x5c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHistogram()
	{
		LPDISPATCH result;
		InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asColorGrid()
	{
		LPDISPATCH result;
		InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHorizLine()
	{
		LPDISPATCH result;
		InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBarJoin()
	{
		LPDISPATCH result;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHighLow()
	{
		LPDISPATCH result;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asWaterfall()
	{
		LPDISPATCH result;
		InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSmith()
	{
		LPDISPATCH result;
		InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPyramid()
	{
		LPDISPATCH result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asMap()
	{
		LPDISPATCH result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asFunnel()
	{
		LPDISPATCH result;
		InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asCalendar()
	{
		LPDISPATCH result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void FreeDatasource(BOOL SurePrompt)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SurePrompt);
	}
	long get_SeriesLink()
	{
		long result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_DatasourceType()
	{
		long result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DatasourceType(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_ValueLists()
	{
		LPDISPATCH result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL IsNan(double Value)
	{
		BOOL result;
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Value);
		return result;
	}
	void DeleteRange(long start, long Quantity)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, start, Quantity);
	}
	void SortByLabels(long Order)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Order);
	}
	void SetNull(long ValueIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ValueIndex);
	}
	LPDISPATCH get_asHorizArea()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPointFigure()
	{
		LPDISPATCH result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGauge()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asVector3D()
	{
		LPDISPATCH result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTower()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	double MaxVisibleValue(long valueList)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_R8, (void*)&result, parms, valueList);
		return result;
	}
	double MinVisibleValue(long valueList)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_R8, (void*)&result, parms, valueList);
		return result;
	}
	LPDISPATCH get_asPolarBar()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBubble3D()
	{
		LPDISPATCH result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHorizHistogram()
	{
		LPDISPATCH result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ShowInEditor()
	{
		BOOL result;
		InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowInEditor(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asVolumePipe()
	{
		LPDISPATCH result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asIsoSurface()
	{
		LPDISPATCH result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asDarvas()
	{
		LPDISPATCH result;
		InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHighLowLine()
	{
		LPDISPATCH result;
		InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPolarGrid()
	{
		LPDISPATCH result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_YMandatory()
	{
		BOOL result;
		InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void BeginUpdate()
	{
		InvokeHelper(0xdd, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void EndUpdate()
	{
		InvokeHelper(0xde, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0xdf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_MandatoryValueList()
	{
		LPDISPATCH result;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_NotMandatoryValueList()
	{
		LPDISPATCH result;
		InvokeHelper(0xe1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asDeltaPoint()
	{
		LPDISPATCH result;
		InvokeHelper(0xe2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asImagePoint()
	{
		LPDISPATCH result;
		InvokeHelper(0xe3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asOrganizational()
	{
		LPDISPATCH result;
		InvokeHelper(0xe4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asWorld()
	{
		LPDISPATCH result;
		InvokeHelper(0xe5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTagCloud()
	{
		LPDISPATCH result;
		InvokeHelper(0xe6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asKagi()
	{
		LPDISPATCH result;
		InvokeHelper(0xe7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRenko()
	{
		LPDISPATCH result;
		InvokeHelper(0xe8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL IsValidSourceOf(long SeriesIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, SeriesIndex);
		return result;
	}
	BOOL IsValidSeriesSource(long SeriesIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xea, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, SeriesIndex);
		return result;
	}
	BOOL UseAxis()
	{
		BOOL result;
		InvokeHelper(0xeb, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	CString get_ColorSource()
	{
		CString result;
		InvokeHelper(0xec, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_ColorSource(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xec, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asNumericGauge()
	{
		LPDISPATCH result;
		InvokeHelper(0xed, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLinearGauge()
	{
		LPDISPATCH result;
		InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asCircularGauge()
	{
		LPDISPATCH result;
		InvokeHelper(0xef, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ZOrder()
	{
		long result;
		InvokeHelper(0xf0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ZOrder(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xf0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asKnobGauge()
	{
		LPDISPATCH result;
		InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRose()
	{
		LPDISPATCH result;
		InvokeHelper(0xf2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTernary()
	{
		LPDISPATCH result;
		InvokeHelper(0xf3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTreeMap()
	{
		LPDISPATCH result;
		InvokeHelper(0xf4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLinePoint()
	{
		LPDISPATCH result;
		InvokeHelper(0xf5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	double get_DefaultNullValue()
	{
		double result;
		InvokeHelper(0xf6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_DefaultNullValue(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0xf6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_LegendTitle()
	{
		CString result;
		InvokeHelper(0xf7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_LegendTitle(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xf7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asErrorPoint()
	{
		LPDISPATCH result;
		InvokeHelper(0xf8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asErrorPoint3D()
	{
		LPDISPATCH result;
		InvokeHelper(0xf9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	VARIANT get_Tag()
	{
		VARIANT result;
		InvokeHelper(0xfa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Tag(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xfa, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}
	LPDISPATCH get_asEquiVolume()
	{
		LPDISPATCH result;
		InvokeHelper(0xfb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0xfc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xfc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asDoubleHorizBar()
	{
		LPDISPATCH result;
		InvokeHelper(0xfd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Legend()
	{
		LPDISPATCH result;
		InvokeHelper(0xfe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPolarContour()
	{
		LPDISPATCH result;
		InvokeHelper(0xff, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	VARIANT get_SeriesLinkx64()
	{
		VARIANT result;
		InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Selected()
	{
		LPDISPATCH result;
		InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void AppendArray(long ArraySize, VARIANT& YArray, VARIANT& XArray)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT;
		InvokeHelper(0x102, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ArraySize, &YArray, &XArray);
	}
	LPDISPATCH get_asActivityGauge()
	{
		LPDISPATCH result;
		InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asEqualizerSeries()
	{
		LPDISPATCH result;
		InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_CalcVisiblePoints()
	{
		BOOL result;
		InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_CalcVisiblePoints(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Polygon()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IPolygonSeries properties
public:

};
