// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CExpandAnimation wrapper class

class CExpandAnimation : public COleDispatchDriver
{
public:
	CExpandAnimation() {} // Calls COleDispatchDriver default constructor
	CExpandAnimation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExpandAnimation(const CExpandAnimation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IExpandAnimation methods
public:
	long get_Speed()
	{
		long result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Speed(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Animations()
	{
		LPDISPATCH result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Animate()
	{
		LPDISPATCH result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Loop()
	{
		BOOL result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Loop(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_SizeBy()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_SizeBy(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Target()
	{
		long result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Target(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x131, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Trigger()
	{
		long result;
		InvokeHelper(0x132, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Trigger(long newValue)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x132, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IExpandAnimation properties
public:

};

