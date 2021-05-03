// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

#import "C:\\Program Files (x86)\\Steema Software\\TeeChart Pro v2018 ActiveX Evaluation\\TeeChart2018.ocx" no_namespace
// CSeriesMarksPositions wrapper class

class CSeriesMarksPositions : public COleDispatchDriver
{
public:
	CSeriesMarksPositions() {} // Calls COleDispatchDriver default constructor
	CSeriesMarksPositions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSeriesMarksPositions(const CSeriesMarksPositions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// ISeriesMarksPositions methods
public:
	LPDISPATCH get_Position(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	void Automatic(long Index)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Index);
	}

	// ISeriesMarksPositions properties
public:

};
