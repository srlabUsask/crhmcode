// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTransformAnimation wrapper class

class CTransformAnimation : public COleDispatchDriver
{
public:
	CTransformAnimation() {} // Calls COleDispatchDriver default constructor
	CTransformAnimation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTransformAnimation(const CTransformAnimation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITransformAnimation methods
public:
	long get_Duration()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Duration(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Inverted()
	{
		BOOL result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Inverted(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_Loop()
	{
		BOOL result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Loop(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	long get_StartTime()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_StartTime(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Timing()
	{
		long result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Timing(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TimingStyle()
	{
		long result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TimingStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_Title()
	{
		CString result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	void put_Title(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_TwoWay()
	{
		BOOL result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_TwoWay(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xd2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Series()
	{
		long result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Series(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Axis()
	{
		LPDISPATCH result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Clip()
	{
		BOOL result;
		InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Clip(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Fade()
	{
		long result;
		InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Fade(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_MaxZoom()
	{
		long result;
		InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_MaxZoom(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_RotateMin()
	{
		long result;
		InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_RotateMin(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_RotateMax()
	{
		long result;
		InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_RotateMax(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Scale()
	{
		long result;
		InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Scale(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_TranslateStyle()
	{
		long result;
		InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_TranslateStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Target()
	{
		long result;
		InvokeHelper(0x199, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Target(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x199, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	BOOL get_UseBounds()
	{
		BOOL result;
		InvokeHelper(0x19a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseBounds(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x19a, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_ZoomStyle()
	{
		long result;
		InvokeHelper(0x19b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_ZoomStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x19b, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// ITransformAnimation properties
public:

};
