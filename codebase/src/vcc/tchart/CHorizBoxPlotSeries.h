// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CHorizBoxPlotSeries wrapper class

class CHorizBoxPlotSeries : public COleDispatchDriver
{
public:
	CHorizBoxPlotSeries() {} // Calls COleDispatchDriver default constructor
	CHorizBoxPlotSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CHorizBoxPlotSeries(const CHorizBoxPlotSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IHorizBoxPlotSeries methods
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
	LPDISPATCH get_ExtrOut()
	{
		LPDISPATCH result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_MedianPen()
	{
		LPDISPATCH result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_MildOut()
	{
		LPDISPATCH result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	double get_Position()
	{
		double result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Position(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_WhiskerLength()
	{
		double result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_WhiskerLength(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_WhiskerPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Box()
	{
		LPDISPATCH result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	double get_Median()
	{
		double result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Median(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Quartile1()
	{
		double result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Quartile1(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Quartile3()
	{
		double result;
		InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Quartile3(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_InnerFence1()
	{
		double result;
		InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_InnerFence1(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_InnerFence3()
	{
		double result;
		InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_InnerFence3(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_OuterFence1()
	{
		double result;
		InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_OuterFence1(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_OuterFence3()
	{
		double result;
		InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_OuterFence3(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_AdjacentPoint1()
	{
		double result;
		InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_AdjacentPoint1(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_AdjacentPoint3()
	{
		double result;
		InvokeHelper(0x199, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_AdjacentPoint3(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x199, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_UseCustomValues()
	{
		BOOL result;
		InvokeHelper(0x19a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseCustomValues(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x19a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double MaxYValue()
	{
		double result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}
	double MinYValue()
	{
		double result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_R8, (void*)&result, nullptr);
		return result;
	}

	// IHorizBoxPlotSeries properties
public:

};

