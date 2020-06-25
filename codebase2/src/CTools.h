// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTools wrapper class

class CTools : public COleDispatchDriver
{
public:
	CTools() {} // Calls COleDispatchDriver default constructor
	CTools(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTools(const CTools& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITools methods
public:
	LPDISPATCH get_asTeeCursor()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asDragMarks()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAxisArrow()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asDrawLine()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asNearest()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asColorband()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asColorLine()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRotate()
	{
		LPDISPATCH result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asMarksTip()
	{
		LPDISPATCH result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asChartImage()
	{
		LPDISPATCH result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAnnotation()
	{
		LPDISPATCH result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPageNum()
	{
		LPDISPATCH result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Active()
	{
		BOOL result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Active(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Description()
	{
		CString result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	long get_ToolType()
	{
		long result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void ShowEditor()
	{
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_asGridTranspose()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asExtraLegend()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSeriesAnimation()
	{
		LPDISPATCH result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGantt()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGridBand()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asPie()
	{
		LPDISPATCH result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asDragPoint()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLegendScrollBar()
	{
		LPDISPATCH result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLight()
	{
		LPDISPATCH result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSurfaceNearest()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAxisScroll()
	{
		LPDISPATCH result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSeriesBand()
	{
		LPDISPATCH result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSelector()
	{
		LPDISPATCH result;
		InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRectangle()
	{
		LPDISPATCH result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ShowInEditor()
	{
		BOOL result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowInEditor(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_asDataTable()
	{
		LPDISPATCH result;
		InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asVideo()
	{
		LPDISPATCH result;
		InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asVideoPlayer()
	{
		LPDISPATCH result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTransposeSeries()
	{
		LPDISPATCH result;
		InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSeriesRegion()
	{
		LPDISPATCH result;
		InvokeHelper(0xdd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAntiAlias()
	{
		LPDISPATCH result;
		InvokeHelper(0xde, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asClipSeries()
	{
		LPDISPATCH result;
		InvokeHelper(0xdf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asFader()
	{
		LPDISPATCH result;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asFrame()
	{
		LPDISPATCH result;
		InvokeHelper(0xe1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asMagnify()
	{
		LPDISPATCH result;
		InvokeHelper(0xe2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLegendPalette()
	{
		LPDISPATCH result;
		InvokeHelper(0xe3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBanner()
	{
		LPDISPATCH result;
		InvokeHelper(0xe4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asText3D()
	{
		LPDISPATCH result;
		InvokeHelper(0xe5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSeriesStats()
	{
		LPDISPATCH result;
		InvokeHelper(0xe6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLink()
	{
		LPDISPATCH result;
		InvokeHelper(0xe7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asFibonacci()
	{
		LPDISPATCH result;
		InvokeHelper(0xe8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asFullScreen()
	{
		LPDISPATCH result;
		InvokeHelper(0xe9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAxisBreaks()
	{
		LPDISPATCH result;
		InvokeHelper(0xea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSubChart()
	{
		LPDISPATCH result;
		InvokeHelper(0xeb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asClustering()
	{
		LPDISPATCH result;
		InvokeHelper(0xec, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRepaintMonitor()
	{
		LPDISPATCH result;
		InvokeHelper(0xed, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asArrow()
	{
		LPDISPATCH result;
		InvokeHelper(0xee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asScrollPager()
	{
		LPDISPATCH result;
		InvokeHelper(0xef, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAxisScrollBar()
	{
		LPDISPATCH result;
		InvokeHelper(0xf0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Tag()
	{
		long result;
		InvokeHelper(0xf1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Tag(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xf1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ITools properties
public:

};
