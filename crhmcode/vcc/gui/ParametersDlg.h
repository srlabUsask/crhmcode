#pragma once
#include "../../src/core/CRHMmain.h"

// ParametersDlg dialog

class ParametersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParametersDlg)

private:
	CListBox modules_list_box;
	
	void initalizeModulesListBox(CRHMmain * main);
public:
	ParametersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ParametersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = PARAMETERS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	/**
	* Initalizes the dialog elements after creating the dialog.
	*/
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
