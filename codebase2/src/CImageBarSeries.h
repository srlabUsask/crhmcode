// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CImageBarSeries wrapper class

class CImageBarSeries : public COleDispatchDriver
{
public:
	CImageBarSeries() {} // Calls COleDispatchDriver default constructor
	CImageBarSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CImageBarSeries(const CImageBarSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IImageBarSeries methods
public:
	long get_MultiBar()
	{
		long result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MultiBar(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_AutoMarkPosition()
	{
		BOOL result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoMarkPosition(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_BarBrush()
	{
		LPDISPATCH result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_BarPen()
	{
		LPDISPATCH result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_BarStyle()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BarStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BarWidthPercent()
	{
		long result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BarWidthPercent(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Dark3D()
	{
		BOOL result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Dark3D(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_OffsetPercent()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_OffsetPercent(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_SideMargins()
	{
		BOOL result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_SideMargins(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_UseOrigin()
	{
		BOOL result;
		InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseOrigin(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_Origin()
	{
		double result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Origin(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long GetOriginPos(long SomeValueIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeValueIndex);
		return result;
	}
	BOOL get_AutoBarSize()
	{
		BOOL result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoBarSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void BarImageLoad(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, FileName);
	}
	void BarImageClear()
	{
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Gradient()
	{
		LPDISPATCH result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_StackGroup()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_StackGroup(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ConePercent()
	{
		long result;
		InvokeHelper(0x6f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ConePercent(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x6f, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_TickLines()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_DepthPercent()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DepthPercent(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Shadow()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Transparency()
	{
		long result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Transparency(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BevelSize()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BevelSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DarkPen()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DarkPen(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_RoundSize()
	{
		long result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_RoundSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_MarksOnBar()
	{
		BOOL result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_MarksOnBar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MarksLocation()
	{
		long result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MarksLocation(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BarRound()
	{
		long result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BarRound(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Emboss()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_GradientRelative()
	{
		BOOL result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_GradientRelative(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_BarWidth()
	{
		long result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BarWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH CalcBarBounds(long ValueIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ValueIndex);
		return result;
	}
	BOOL LoadImage(LPCTSTR FileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName);
		return result;
	}
	void ClearImage()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	BOOL get_ImageTiled()
	{
		BOOL result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ImageTiled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IImageBarSeries properties
public:

};

