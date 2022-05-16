#pragma once
#include <afxwin.h>
#include <string>
#include "afxdialogex.h"
#include "../stdafx.h"
#include "../resource.h"

#include "ParamDlgCard.h"

class ParamDlgCard;

class ParamSetAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParamSetAllDlg)

private:
	CEdit set_all_value;

	void ParamSetAllDlg::OnOK();

	ParamDlgCard * card;

public:
	ParamSetAllDlg(ParamDlgCard* paramCard, CWnd* parent = nullptr);


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