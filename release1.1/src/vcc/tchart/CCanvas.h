// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCanvas wrapper class

class CCanvas : public COleDispatchDriver
{
public:
	CCanvas() {} // Calls COleDispatchDriver default constructor
	CCanvas(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCanvas(const CCanvas& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICanvas methods
public:
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void LineTo(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y);
	}
	void MoveTo(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y);
	}
	void Rectangle(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void Arc(long X1, long Y1, long X2, long Y2, long X3, long Y3, long X4, long Y4)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2, X3, Y3, X4, Y4);
	}
	void Ellipse(long X1, long Y1, long X2, long Y2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2);
	}
	void TextOut(long X, long Y, LPCTSTR Text)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Text);
	}
	long TextHeight(LPCTSTR SomeText)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeText);
		return result;
	}
	long TextWidth(LPCTSTR SomeText)
	{
		long result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, SomeText);
		return result;
	}
	void ClipRectangle(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	void UnClipRectangle()
	{
		InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void RotateLabel(long X, long Y, LPCTSTR St, long RotDegree)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_I4;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, St, RotDegree);
	}
	BOOL IsScreenHighColor()
	{
		BOOL result;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_BackMode()
	{
		long result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_BackMode(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_BackColor()
	{
		unsigned long result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_BackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_SupportsFullRotation()
	{
		BOOL result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	BOOL get_UseBuffer()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseBuffer(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void Pie3D(long XCenter, long YCenter, long XRadius, long YRadius, long Z0, long Z1, double StartAngle, double EndAngle, BOOL DarkSides, BOOL DrawSides)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_BOOL VTS_BOOL;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, XCenter, YCenter, XRadius, YRadius, Z0, Z1, StartAngle, EndAngle, DarkSides, DrawSides);
	}
	void LineWithZ(long X0, long Y0, long X1, long Y1, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X0, Y0, X1, Y1, Z);
	}
	void MoveTo3D(long X, long Y, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z);
	}
	void LineTo3D(long X, long Y, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z);
	}
	void Plane3D(long X0, long Y0, long X1, long Y1, long Z0, long Z1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X0, Y0, X1, Y1, Z0, Z1);
	}
	void ZLine3D(long X, long Y, long Z0, long Z1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z0, Z1);
	}
	void RotateLabel3D(long X, long Y, long Z, LPCTSTR St, long RotDegree)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z, St, RotDegree);
	}
	long get_TextAlign()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TextAlign(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void VertLine3D(long X, long Top, long Bottom, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Top, Bottom, Z);
	}
	void HorizLine3D(long Left, long Right, long Y, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Right, Y, Z);
	}
	void Cylinder(BOOL Vertical, long Left, long Top, long Right, long Bottom, long Z0, long Z1, BOOL DarkCover)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Vertical, Left, Top, Right, Bottom, Z0, Z1, DarkCover);
	}
	void Cube(long Left, long Right, long Top, long Bottom, long Z0, long Z1, BOOL DarkSides)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Right, Top, Bottom, Z0, Z1, DarkSides);
	}
	void EllipseWithZ(long X1, long Y1, long X2, long Y2, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2, Z);
	}
	void PlaneWithZ(long X1, long Y1, long X2, long Y2, long X3, long Y3, long X4, long Y4, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2, X3, Y3, X4, Y4, Z);
	}
	void PlaneFour3D(long X1, long Y1, long X2, long Y2, long X3, long Y3, long X4, long Y4, long Z0, long Z1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2, X3, Y3, X4, Y4, Z0, Z1);
	}
	void RectangleWithZ(long Left, long Top, long Right, long Bottom, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, Z);
	}
	void RectangleZ(long Left, long Top, long Bottom, long Z0, long Z1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Bottom, Z0, Z1);
	}
	void TextOut3D(long X, long Y, long Z, LPCTSTR Text)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z, Text);
	}
	void TriangleWithZ(long X1, long Y1, long X2, long Y2, long X3, long Y3, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2, X3, Y3, Z);
	}
	void Frame3D(long Left, long Top, long Right, long Bottom, unsigned long TopColor, unsigned long BottomColor, long Width)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_UI4 VTS_UI4 VTS_I4;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, TopColor, BottomColor, Width);
	}
	void EraseBackground(long Left, long Top, long Right, long Bottom)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom);
	}
	void GradientFill(long Left, long Top, long Right, long Bottom, unsigned long StartColor, unsigned long EndColor, long Direction)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_UI4 VTS_UI4 VTS_I4;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, StartColor, EndColor, Direction);
	}
	void Line(long X0, long Y0, long X1, long Y1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X0, Y0, X1, Y1);
	}
	void RectangleY(long Left, long Top, long Right, long Z0, long Z1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Z0, Z1);
	}
	void Pixels3D(long X, long Y, long Z, unsigned long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_UI4;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z, Value);
	}
	VARIANT get_HandleDC()
	{
		VARIANT result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void Cone(BOOL Vertical, long Left, long Top, long Right, long Bottom, long Z0, long Z1, BOOL Dark3D, long ConePercent)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Vertical, Left, Top, Right, Bottom, Z0, Z1, Dark3D, ConePercent);
	}
	void Sphere(long X, long Y, long Z, double Radius)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R8;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Z, Radius);
	}
	void Arrow(BOOL Filled, long X0, long Y0, long X1, long Y1, long HeadWidth, long HeadHeight, long Z)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Filled, X0, Y0, X1, Y1, HeadWidth, HeadHeight, Z);
	}
	void Draw(long X, long Y, LPUNKNOWN Image)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UNKNOWN;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Image);
	}
	LPDISPATCH get_RotationCenter()
	{
		LPDISPATCH result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_ChartXCenter()
	{
		long result;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	long get_ChartYCenter()
	{
		long result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void GrayScale(BOOL Inverted)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Inverted);
	}
	void Polyline(long ArraySize, VARIANT& XArray, VARIANT& YArray, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ArraySize, &XArray, &YArray, Z);
	}
	void RotatedEllipse(long Left, long Top, long Right, long Bottom, long Z, double Angle)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, Z, Angle);
	}
	void StretchDraw(long Left, long Top, long Right, long Bottom, LPUNKNOWN Image)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_UNKNOWN;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, Image);
	}
	void StretchDrawZ(long Left, long Top, long Right, long Bottom, LPUNKNOWN Image, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_UNKNOWN VTS_I4;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, Image, Z);
	}
	void Pie(long X1, long Y1, long X2, long Y2, long X3, long Y3, long X4, long Y4)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X1, Y1, X2, Y2, X3, Y3, X4, Y4);
	}
	void PolygonWithZ(long ArraySize, VARIANT& XArray, VARIANT& YArray, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ArraySize, &XArray, &YArray, Z);
	}
	BOOL get_UseAntiAlias()
	{
		BOOL result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseAntiAlias(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void Polygon(long NumPoints, VARIANT& Points)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, NumPoints, &Points);
	}
	void DrawBevel(long Value, long Left, long Top, long Right, long Bottom, long Size)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Value, Left, Top, Right, Bottom, Size);
	}
	unsigned long ApplyDark(unsigned long Color, long HowMuch)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 VTS_I4;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, Color, HowMuch);
		return result;
	}
	void DrawLine(long X0, long Y0, long X1, long Y1)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X0, Y0, X1, Y1);
	}
	BOOL get_TeeCheckPenWidth()
	{
		BOOL result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Metafiling()
	{
		BOOL result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Metafiling(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Monochrome()
	{
		BOOL result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Monochrome(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void AssignBrush(long ABrush)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ABrush);
	}
	long get_FontHeight()
	{
		long result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	unsigned long get_GetPixels3D(long X, long Y, long Z)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, X, Y, Z);
		return result;
	}
	void Pixels(long X, long Y, unsigned long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_UI4;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Value);
	}
	unsigned long get_GetPixels(long X, long Y)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, X, Y);
		return result;
	}
	BOOL get_Supports3DText()
	{
		BOOL result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void ClipRoundRectangle(long Left, long Top, long Right, long Bottom, long RoundSize)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, RoundSize);
	}
	void ClipEllipse(long Left, long Top, long Right, long Bottom, BOOL Inverted)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL;
		InvokeHelper(0xdd, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, Inverted);
	}
	void ClipPolygon(VARIANT * Points, long NumPoints)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_I4;
		InvokeHelper(0xde, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Points, NumPoints);
	}
	void PolygonGradient(long ArraySize, VARIANT * Points, unsigned long StartColor, unsigned long MiddleColor, unsigned long EndColor, long Direction)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_UI4 VTS_UI4 VTS_UI4 VTS_I4;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ArraySize, Points, StartColor, MiddleColor, EndColor, Direction);
	}
	LPDISPATCH get_CustomEditColors()
	{
		LPDISPATCH result;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long ColorAlpha(unsigned long AColor)
	{
		long result;
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0xe1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, AColor);
		return result;
	}
	unsigned long ColorFrom(unsigned long AColor, long Alpha)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 VTS_I4;
		InvokeHelper(0xe2, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, AColor, Alpha);
		return result;
	}
	void RoundRectWithZ(long Left, long Top, long Right, long Bottom, long X, long Y, long Z)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xe3, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, X, Y, Z);
	}
	ITeeBasePath CreatePath()
	{
		InvokeHelper(0xe4, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_StretchDrawQuality()
	{
		long result;
		InvokeHelper(0xe5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_StretchDrawQuality(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xe5, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	void ClipCube(long Left, long Top, long Right, long Bottom, long MinZ, long MaxZ)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xe6, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Left, Top, Right, Bottom, MinZ, MaxZ);
	}
	LPDISPATCH CubeHull(long Left, long Top, long Right, long Bottom, long MinZ, long MaxZ)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xe7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Left, Top, Right, Bottom, MinZ, MaxZ);
		return result;
	}
	BOOL get_IsAvailable()
	{
		BOOL result;
		InvokeHelper(0xe8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	// ICanvas properties
public:

};

