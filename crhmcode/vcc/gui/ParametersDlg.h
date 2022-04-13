#pragma once


// ParametersDlg dialog

class ParametersDlg : public CDialog
{
	DECLARE_DYNAMIC(ParametersDlg)

public:
	ParametersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ParametersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = PARAMETERS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
