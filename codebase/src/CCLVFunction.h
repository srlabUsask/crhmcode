// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CCLVFunction wrapper class

class CCLVFunction : public COleDispatchDriver
{
public:
	CCLVFunction() {} // Calls COleDispatchDriver default constructor
	CCLVFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCLVFunction(const CCLVFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ICLVFunction methods
public:
	BOOL get_Accumulate()
	{
		BOOL result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	void put_Accumulate(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	VARIANT get_Volume()
	{
		VARIANT result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}
	void put_Volume(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xca, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, &newValue);
	}

	// ICLVFunction properties
public:

};

