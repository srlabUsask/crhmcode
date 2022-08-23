#pragma once

#include "ParamDlgCard.h"

class ParamDlgCard;

/**
* Dialog window that takes in a value to set all values in a parameter to a single value.
*/
class ParamSetAllDlg : public CDialog
{
	DECLARE_DYNAMIC(ParamSetAllDlg)

private:

	/**
	* The CEdit control for choosing the value to set. 
	*/
	CEdit * set_all_value;

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

	/**
	* Deconstructor
	* 
	* Deletes the CEdit declared on the heap.
	*/
	~ParamSetAllDlg();

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