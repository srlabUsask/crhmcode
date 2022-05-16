#pragma once
#include <afxwin.h>
#include <string>
#include "afxdialogex.h"
#include "../stdafx.h"
#include "../resource.h"

#include "ParamDlgCard.h"

// Forward declaration
class ParamDlgCard;

class ParamSetAllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParamSetAllDlg)

private:
	/**
	* The CEdit control for choosing the value to set. 
	*/
	CEdit set_all_value;

	/**
	* Reference to the parameter card that the value will be applied to.
	*/
	ParamDlgCard* card;

	/**
	* Overide of OnOK that will set the values in the parameter card before closing 
	*	when the set button is pressed.
	*/
	void ParamSetAllDlg::OnOK();

public:
	/**
	* Constructor 
	* 
	* @param paramCard - ParamDlgCard* pointer to the 
	*	parameter card associated with this dialog.
	*/
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