// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeBasePath wrapper class

class CTeeBasePath : public COleDispatchDriver
{
public:
	CTeeBasePath() {} // Calls COleDispatchDriver default constructor
	CTeeBasePath(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeBasePath(const CTeeBasePath& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeBasePath methods
public:
	void ArcTo(long X, long Y, long Width, long Height, long StartAngle, long SweepAngle)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y, Width, Height, StartAngle, SweepAngle);
	}
	void Close()
	{
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Curve(long ArraySize, VARIANT& XArray, VARIANT& YArray, long Tension, BOOL Closed)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_BOOL;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ArraySize, &XArray, &YArray, Tension, Closed);
	}
	void Draw()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void LineTo(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y);
	}
	void MoveTo(long X, long Y)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, X, Y);
	}

	// ITeeBasePath properties
public:

};
