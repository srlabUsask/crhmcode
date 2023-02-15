/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
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