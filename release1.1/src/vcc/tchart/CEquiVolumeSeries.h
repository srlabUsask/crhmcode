// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CEquiVolumeSeries wrapper class

class CEquiVolumeSeries : public COleDispatchDriver
{
public:
	CEquiVolumeSeries() {} // Calls COleDispatchDriver default constructor
	CEquiVolumeSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CEquiVolumeSeries(const CEquiVolumeSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IEquiVolumeSeries methods
public:
	LPDISPATCH get_Pointer()
	{
		LPDISPATCH result;
		InvokeHelper(0x641, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Stairs()
	{
		BOOL result;
		InvokeHelper(0x642, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Stairs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x642, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_InvertedStairs()
	{
		BOOL result;
		InvokeHelper(0x643, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_InvertedStairs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x643, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_LinePen()
	{
		LPDISPATCH result;
		InvokeHelper(0x644, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_LineBrush()
	{
		long result;
		InvokeHelper(0x645, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LineBrush(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x645, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ClickableLine()
	{
		BOOL result;
		InvokeHelper(0x646, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ClickableLine(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x646, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_LineHeight()
	{
		long result;
		InvokeHelper(0x647, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LineHeight(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x647, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Dark3D()
	{
		BOOL result;
		InvokeHelper(0x648, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Dark3D(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x648, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0x649, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ColorEachLine()
	{
		BOOL result;
		InvokeHelper(0x64a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ColorEachLine(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x64a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Outline()
	{
		LPDISPATCH result;
		InvokeHelper(0x64b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0x64c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x64c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Shadow()
	{
		LPDISPATCH result;
		InvokeHelper(0x64d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_TreatNulls()
	{
		long result;
		InvokeHelper(0x64e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TreatNulls(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x64e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Smoothed()
	{
		BOOL result;
		InvokeHelper(0x64f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Smoothed(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x64f, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ClickTolerance()
	{
		long result;
		InvokeHelper(0x650, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ClickTolerance(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x650, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DrawStyle()
	{
		long result;
		InvokeHelper(0x651, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DrawStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x651, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_InflateMargins()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_InflateMargins(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_PointerBehind()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_PointerBehind(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_FastPoint()
	{
		BOOL result;
		InvokeHelper(0x6f9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_FastPoint(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6f9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_CandleStyle()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_CandleStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_CandleWidth()
	{
		long result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_CandleWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_CloseValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_DateValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_DownCloseColor()
	{
		unsigned long result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_DownCloseColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_HighValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_LowValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_OpenValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ShowCloseTick()
	{
		BOOL result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowCloseTick(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_ShowOpenTick()
	{
		BOOL result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ShowOpenTick(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_UpCloseColor()
	{
		unsigned long result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_UpCloseColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long AddCandle(double DateValue, double OpenValue, double HighValue, double LowValue, double CloseValue, LPCTSTR ALabel, unsigned long AColor)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BSTR VTS_UI4;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, DateValue, OpenValue, HighValue, LowValue, CloseValue, ALabel, AColor);
		return result;
	}
	LPDISPATCH get_HighLowPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ColorStyle()
	{
		long result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ColorStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_UpCloseGradient()
	{
		LPDISPATCH result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_DownCloseGradient()
	{
		LPDISPATCH result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_OpenTickColor()
	{
		unsigned long result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_OpenTickColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_CloseTickColor()
	{
		unsigned long result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_CloseTickColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoSize()
	{
		BOOL result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x133, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BorderColor()
	{
		long result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BorderColor(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x134, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Draw3D()
	{
		BOOL result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Draw3D(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x135, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_RemoveGaps()
	{
		BOOL result;
		InvokeHelper(0x136, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_RemoveGaps(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x136, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_HighLowColor()
	{
		long result;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_HighLowColor(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x137, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BoxFillStyle()
	{
		long result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BoxFillStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_VolumeValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_VolumePointer()
	{
		LPDISPATCH result;
		InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_PointGap()
	{
		long result;
		InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_PointGap(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IEquiVolumeSeries properties
public:

};

