// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CDrawLine wrapper class

class CDrawLine : public COleDispatchDriver
{
public:
	CDrawLine() {} // Calls COleDispatchDriver default constructor
	CDrawLine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDrawLine(const CDrawLine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IDrawLine methods
public:
	LPDISPATCH get_EndPos()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_StartPos()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	void DrawHandles()
	{
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	TeeRect EndHandle()
	{
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	TeeRect StartHandle()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_Style()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Style(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IDrawLine properties
public:

};

