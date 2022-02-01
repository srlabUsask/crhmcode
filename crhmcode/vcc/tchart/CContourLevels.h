// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CContourLevels wrapper class

class CContourLevels : public COleDispatchDriver
{
public:
	CContourLevels() {} // Calls COleDispatchDriver default constructor
	CContourLevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CContourLevels(const CContourLevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IContourLevels methods
public:
	LPDISPATCH get_Items(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long Clicked(long XCoord, long YCoord, long * SegmentIndex, long * PointIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, XCoord, YCoord, SegmentIndex, PointIndex);
		return result;
	}
	long AddLevel(double LevelValue, unsigned long Color)
	{
		long result;
		static BYTE parms[] = VTS_R8 VTS_UI4;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms, LevelValue, Color);
		return result;
	}

	// IContourLevels properties
public:

};

