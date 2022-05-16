#pragma once
#include <afxwin.h>
#include "../stdafx.h"
#include "afxdialogex.h"
#include "../resource.h"

class ParamSetAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParamSetAllDlg)

private:
	CEdit set_all_value;

public:
	ParamSetAllDlg(CWnd* parent = nullptr);


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = PARAMETERS_SET_ALL_DLG };
#endif

protected:
	/**
	* Performs data exchange to properly connect graphical elements to the model.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Initalizes the dialog elements after creating the dialog.
	*/
	virtual BOOL OnInitDialog();

	/**
	* Declares handlers for messages dispached by the GUI
	*/
	DECLARE_MESSAGE_MAP()
};