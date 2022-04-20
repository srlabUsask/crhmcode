#pragma once
#include "../../src/core/CRHMmain.h"

// ParametersDlg dialog

class ParametersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParametersDlg)

public:
	ParametersDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ParametersDlg();

private:
	CListBox modules_list_box;
	CListBox parameters_list_box;

	/**
	* Handler for when the selection in the modules_list_box changes.
	*
	* Sets the parameters_list_box to contain all the parameters in the selected module.
	*/
	afx_msg void OnSelectModule();

	void initalizeModulesListBox(CRHMmain * main);


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
