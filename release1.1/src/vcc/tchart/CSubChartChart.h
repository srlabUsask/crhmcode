// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSubChartChart wrapper class

class CSubChartChart : public COleDispatchDriver
{
public:
	CSubChartChart() {} // Calls COleDispatchDriver default constructor
	CSubChartChart(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSubChartChart(const CSubChartChart& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISubChartChart methods
public:
	LPDISPATCH get_Aspect()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Axis()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Canvas()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ClipPoints()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ClipPoints(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_Cursor()
	{
		short result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_Cursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_DragCursor()
	{
		short result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_DragCursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DragMode()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DragMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Export()
	{
		LPDISPATCH result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Footer()
	{
		LPDISPATCH result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Frame()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Header()
	{
		LPDISPATCH result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
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
	LPDISPATCH get_Import()
	{
		LPDISPATCH result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Left(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Legend()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Page()
	{
		LPDISPATCH result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Panel()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Printer()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Scroll()
	{
		LPDISPATCH result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_aSeries(long SeriesIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, SeriesIndex);
		return result;
	}
	long get_SeriesCount()
	{
		long result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Top(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Walls()
	{
		LPDISPATCH result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Zoom()
	{
		LPDISPATCH result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long AddSeries(long SeriesClass)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SeriesClass);
		return result;
	}
	void ChangeSeriesType(long SeriesIndex, long NewSeriesType)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex, NewSeriesType);
	}
	long CloneSeries(long SourceSeriesIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SourceSeriesIndex);
		return result;
	}
	void Draw(VARIANT& DC, long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &DC, Left, Top, Right, Bottom);
	}
	void ExchangeSeries(long Series1, long Series2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Series1, Series2);
	}
	double GetDateTimeStep(long DateTimeStep)
	{
		double result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_R8, (void*)&result, parms, DateTimeStep);
		return result;
	}
	unsigned long GetFreeSeriesColor(BOOL CheckBackgroundColor)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, CheckBackgroundColor);
		return result;
	}
	LPDISPATCH GetLabelsSeries(long DestAxis)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, DestAxis);
		return result;
	}
	BOOL IsFreeSeriesColor(unsigned long AColor, BOOL CheckBackgroundColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_UI4 VTS_BOOL;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, AColor, CheckBackgroundColor);
		return result;
	}
	void RemoveAllSeries()
	{
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void RemoveSeries(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	void Repaint()
	{
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	CString SeriesTitleLegend(long ASeriesIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ASeriesIndex);
		return result;
	}
	void ShowEditor(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	void StopMouse()
	{
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL get_TimerEnabled()
	{
		BOOL result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_TimerEnabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TimerInterval()
	{
		long result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TimerInterval(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoRepaint()
	{
		BOOL result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoRepaint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void EditOneSeries(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	LPDISPATCH get_Environment()
	{
		LPDISPATCH result;
		InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ChartLink()
	{
		long result;
		InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_MousePosition()
	{
		LPDISPATCH result;
		InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void ChartRect(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	LPDISPATCH get_Tools()
	{
		LPDISPATCH result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_SubHeader()
	{
		LPDISPATCH result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_SubFooter()
	{
		LPDISPATCH result;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void ClearChart()
	{
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void RefreshData()
	{
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH Series(long SeriesIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, SeriesIndex);
		return result;
	}
	BOOL ShowThemesEditor()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void SetTheme(long aTheme, long aPalette)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, aTheme, aPalette);
	}
	void ApplyPalette(long paletteIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, paletteIndex);
	}
	void ApplyCustomPalette(VARIANT& colorArray)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &colorArray);
	}
	LPDISPATCH get_SeriesList()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	CString get_Hint()
	{
		CString result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Hint(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowHint()
	{
		BOOL result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowHint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Version()
	{
		CString result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	BOOL get_CustomChartRect()
	{
		BOOL result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_CustomChartRect(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Monochrome()
	{
		BOOL result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Monochrome(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	short get_OriginalCursor()
	{
		short result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}
	void put_OriginalCursor(short newValue)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0xd3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Printing()
	{
		BOOL result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	long get_ChartHeight()
	{
		long result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_ChartWidth()
	{
		long result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_ChartBounds()
	{
		LPDISPATCH result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_BufferedDisplay()
	{
		BOOL result;
		InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_BufferedDisplay(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xdc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_CanClip()
	{
		BOOL result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_GetChartRect()
	{
		LPDISPATCH result;
		InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL EditStrings(BSTR * Strings, BOOL ReadOnly)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_BOOL;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Strings, ReadOnly);
		return result;
	}
	long get_Language()
	{
		long result;
		InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Language(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xda, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Languaged()
	{
		long result;
		InvokeHelper(0xdd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Languaged(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xdd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long MultiLineTextWidth(LPCTSTR AString, long NumLines, long TextFormat)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
		InvokeHelper(0xde, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AString, NumLines, TextFormat);
		return result;
	}
	long MultiLineTextHeight(LPCTSTR AString, long NumLines, long TextFormat)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AString, NumLines, TextFormat);
		return result;
	}
	LPDISPATCH get_Animations()
	{
		LPDISPATCH result;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH CreateNewSeriesGallery(long AGalleryWidth, long AGalleryHeight)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xe1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, AGalleryWidth, AGalleryHeight);
		return result;
	}
	LPDISPATCH get_Panning()
	{
		LPDISPATCH result;
		InvokeHelper(0xe2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long ActiveSeriesLegend(long ItemIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ItemIndex);
		return result;
	}
	void ShowSeriesEditor(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	long CloneSeriesFromChart(long ChartLink, long SeriesIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xe5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ChartLink, SeriesIndex);
		return result;
	}
	long CloneToolFromChart(long ChartLink, long ToolIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xe6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ChartLink, ToolIndex);
		return result;
	}
	LPDISPATCH CreateSeriesChangeGallery(long AGalleryWidth, long AGalleryHeight, long SeriesIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xe7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, AGalleryWidth, AGalleryHeight, SeriesIndex);
		return result;
	}
	LPDISPATCH get_Themes()
	{
		LPDISPATCH result;
		InvokeHelper(0xe8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ZoomWheel()
	{
		long result;
		InvokeHelper(0xe9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ZoomWheel(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void SetChartRect(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xea, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	LPDISPATCH get_Animate()
	{
		LPDISPATCH result;
		InvokeHelper(0xeb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	VARIANT get_ChartLinkx64()
	{
		VARIANT result;
		InvokeHelper(0xec, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	long CloneSeriesFromChartx64(VARIANT& ChartLinkx64, long SeriesIndex)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT VTS_I4;
		InvokeHelper(0xed, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &ChartLinkx64, SeriesIndex);
		return result;
	}
	long CloneToolFromChartx64(VARIANT& ChartLinkx64, long ToolIndex)
	{
		long result;
		static BYTE parms[] = VTS_VARIANT VTS_I4;
		InvokeHelper(0xee, DISPATCH_METHOD, VT_I4, (void*)&result, parms, &ChartLinkx64, ToolIndex);
		return result;
	}
	LPDISPATCH get_Hover()
	{
		LPDISPATCH result;
		InvokeHelper(0xef, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// ISubChartChart properties
public:

};
