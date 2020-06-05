// CWebBrowser.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWebBrowser

class CWebBrowser : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWebBrowser)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8856F961, 0x340A, 0x11D0, { 0xA9, 0x6B, 0x0, 0xC0, 0x4F, 0xD7, 0x5, 0xA2 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID,
						CCreateContext* pContext = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey);
	}

// Attributes
public:

// Operations
public:

	void GoBack()
	{
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void GoForward()
	{
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void GoHome()
	{
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void GoSearch()
	{
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Navigate(LPCTSTR URL, VARIANT * Flags, VARIANT * TargetFrameName, VARIANT * PostData, VARIANT * Headers)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, URL, Flags, TargetFrameName, PostData, Headers);
	}
	void Refresh()
	{
		InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	void Refresh2(VARIANT * Level)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Level);
	}
	void Stop()
	{
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Container()
	{
		LPDISPATCH result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	LPDISPATCH get_Document()
	{
		LPDISPATCH result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}
	BOOL get_TopLevelContainer()
	{
		BOOL result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}
	CString get_Type()
	{
		CString result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Left(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Top(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}
	CString get_LocationName()
	{
		CString result;
		InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString get_LocationURL()
	{
		CString result;
		InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	BOOL get_Busy()
	{
		BOOL result;
		InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}


};
