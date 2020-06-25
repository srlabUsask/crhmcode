// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CTeeFilter wrapper class

class CTeeFilter : public COleDispatchDriver
{
public:
	CTeeFilter() {} // Calls COleDispatchDriver default constructor
	CTeeFilter(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeFilter(const CTeeFilter& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ITeeFilter methods
public:
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	LPDISPATCH get_Region()
	{
		LPDISPATCH result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asResize()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asCrop()
	{
		LPDISPATCH result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGrayScale()
	{
		LPDISPATCH result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asMosaic()
	{
		LPDISPATCH result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asColor()
	{
		LPDISPATCH result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asHueLumSat()
	{
		LPDISPATCH result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asRotate()
	{
		LPDISPATCH result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asMirror()
	{
		LPDISPATCH result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBlur()
	{
		LPDISPATCH result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBrightness()
	{
		LPDISPATCH result;
		InvokeHelper(0xd5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asContrast()
	{
		LPDISPATCH result;
		InvokeHelper(0xd6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asGammaCorrection()
	{
		LPDISPATCH result;
		InvokeHelper(0xd7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asAmount()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSharpen()
	{
		LPDISPATCH result;
		InvokeHelper(0xd8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asEmboss()
	{
		LPDISPATCH result;
		InvokeHelper(0xd9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSoften()
	{
		LPDISPATCH result;
		InvokeHelper(0xda, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asTile()
	{
		LPDISPATCH result;
		InvokeHelper(0xdb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asBevel()
	{
		LPDISPATCH result;
		InvokeHelper(0xdc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asZoom()
	{
		LPDISPATCH result;
		InvokeHelper(0xdd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asLight()
	{
		LPDISPATCH result;
		InvokeHelper(0xde, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSobel()
	{
		LPDISPATCH result;
		InvokeHelper(0xdf, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_asSepia()
	{
		LPDISPATCH result;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	// ITeeFilter properties
public:

};
