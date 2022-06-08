#pragma once

#include "afxdialogex.h"
#include "../resource.h"

class RefreshRateDlg : public CDialog
{
public:
	RefreshRateDlg(CWnd* pParent = NULL);

	enum { IDD = REFRESH_RATE_DLG };


private:

	BOOL OnInitDialog();

	void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
};