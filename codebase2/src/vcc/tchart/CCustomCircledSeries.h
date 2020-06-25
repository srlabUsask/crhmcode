// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCustomCircledSeries wrapper class

class CCustomCircledSeries : public COleDispatchDriver
{
public:
	CCustomCircledSeries() {} // Calls COleDispatchDriver default constructor
	CCustomCircledSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCustomCircledSeries(const CCustomCircledSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICustomCircledSeries methods
public:
	long get_XRadius()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_XRadius(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_YRadius()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_YRadius(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_XCenter()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_YCenter()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_CircleWidth()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_CircleHeight()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_CircleBackColor()
	{
		unsigned long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_CircleBackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Circled()
	{
		BOOL result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Circled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_RotationAngle()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_RotationAngle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH AngleToPoint(double Angle, double AXRadius, double AYRadius)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Angle, AXRadius, AYRadius);
		return result;
	}
	double PointToAngle(long XCoord, long YCoord)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_R8, (void*)&result, parms, XCoord, YCoord);
		return result;
	}
	double PointToRadius(long XCoord, long YCoord)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x191, DISPATCH_METHOD, VT_R8, (void*)&result, parms, XCoord, YCoord);
		return result;
	}
	double get_CustomXRadius()
	{
		double result;
		InvokeHelper(0x1f5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_CustomXRadius(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x1f5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_CustomYRadius()
	{
		double result;
		InvokeHelper(0x259, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_CustomYRadius(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x259, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Shadow()
	{
		LPDISPATCH result;
		InvokeHelper(0x2bd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_CircleBrush()
	{
		LPDISPATCH result;
		InvokeHelper(0x321, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_CirclePen()
	{
		LPDISPATCH result;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_ColorEachLine()
	{
		BOOL result;
		InvokeHelper(0x25a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_ColorEachLine(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x25a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Pointer()
	{
		LPDISPATCH result;
		InvokeHelper(0x25b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_PointerBehind()
	{
		BOOL result;
		InvokeHelper(0x25c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_PointerBehind(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x25c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_DrawStyle()
	{
		long result;
		InvokeHelper(0x25d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DrawStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x25d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TreatNulls()
	{
		long result;
		InvokeHelper(0x25e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TreatNulls(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x25e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ICustomCircledSeries properties
public:

};

