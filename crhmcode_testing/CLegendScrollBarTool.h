// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CLegendScrollBarTool wrapper class

class CLegendScrollBarTool : public COleDispatchDriver
{
public:
	CLegendScrollBarTool() {} // Calls COleDispatchDriver default constructor
	CLegendScrollBarTool(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CLegendScrollBarTool(const CLegendScrollBarTool& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ILegendScrollBarTool methods
public:
	BOOL get_Horizontal()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Horizontal(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Position()
	{
		long result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Position(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_ArrowBrush()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_AutoRepeat()
	{
		BOOL result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_AutoRepeat(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	unsigned long get_BackColor()
	{
		unsigned long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}
	void put_BackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Bevel()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Bevel(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Brush()
	{
		LPDISPATCH result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_InitialDelay()
	{
		long result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_InitialDelay(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Pen()
	{
		LPDISPATCH result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_Size()
	{
		long result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Size(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd3, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_ThumbBrush()
	{
		LPDISPATCH result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_DrawStyle()
	{
		long result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_DrawStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Gradient()
	{
		LPDISPATCH result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_MinThumbSize()
	{
		long result;
		InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MinThumbSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ThumbSize()
	{
		long result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ThumbSize(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd7, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Thumb()
	{
		LPDISPATCH result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// ILegendScrollBarTool properties
public:

};
