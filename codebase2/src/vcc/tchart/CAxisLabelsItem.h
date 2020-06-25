// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CAxisLabelsItem wrapper class

class CAxisLabelsItem : public COleDispatchDriver
{
public:
	CAxisLabelsItem() {} // Calls COleDispatchDriver default constructor
	CAxisLabelsItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxisLabelsItem(const CAxisLabelsItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IAxisLabelsItem methods
public:
	double get_Value()
	{
		double result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_Value(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_LabelPos()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_LabelPos(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Format()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// IAxisLabelsItem properties
public:

};

