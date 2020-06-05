// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CVolumeSeries wrapper class

class CVolumeSeries : public COleDispatchDriver
{
public:
	CVolumeSeries() {} // Calls COleDispatchDriver default constructor
	CVolumeSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVolumeSeries(const CVolumeSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVolumeSeries methods
public:
	LPDISPATCH get_VolumeValues()
	{
		LPDISPATCH result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_LinePen()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_UseYOrigin()
	{
		BOOL result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_UseYOrigin(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	double get_YOrigin()
	{
		double result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, nullptr);
		return result;
	}
	void put_YOrigin(double newValue)
	{
		static BYTE parms[] = VTS_R8;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	// IVolumeSeries properties
public:

};
