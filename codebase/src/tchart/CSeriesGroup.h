// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSeriesGroup wrapper class

class CSeriesGroup : public COleDispatchDriver
{
public:
	CSeriesGroup() {} // Calls COleDispatchDriver default constructor
	CSeriesGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSeriesGroup(const CSeriesGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISeriesGroup methods
public:
	void Add(long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, SeriesIndex);
	}
	void Hide()
	{
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Show()
	{
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	long get_Active()
	{
		long result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Active(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xcd, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	VARIANT get_SeriesCount()
	{
		VARIANT result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	long get_GroupLink()
	{
		long result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void Delete(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}
	void Insert(long IndexInGroup, long SeriesIndex)
	{
		static BYTE parms[] = VTS_I4 VTS_I4;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, IndexInGroup, SeriesIndex);
	}
	LPDISPATCH get_Series()
	{
		LPDISPATCH result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// ISeriesGroup properties
public:

};
