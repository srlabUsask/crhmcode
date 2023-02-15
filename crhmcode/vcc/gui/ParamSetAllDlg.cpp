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
#include "ParamSetAllDlg.h"


IMPLEMENT_DYNAMIC(ParamSetAllDlg, CDialog)


ParamSetAllDlg::ParamSetAllDlg(ParamDlgCard* paramCard, CWnd* pParent) 
	: CDialog(PARAMETERS_SET_ALL_DLG, pParent)
{
	this->card = paramCard;
	this->set_all_value = new CEdit();
}


ParamSetAllDlg::~ParamSetAllDlg()
{
	delete this->set_all_value;
}


BEGIN_MESSAGE_MAP(ParamSetAllDlg, CDialog)
END_MESSAGE_MAP()


BOOL ParamSetAllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetDlgItem(ID_PARAM_SET_PLACEHOLDER)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	// Set the styles for the new cell
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_RIGHT;
	if (this->card->GetParamType() == TVar::Int)
	{
		// If it is a numberic cell add the ES_NUMBER style to prevent non numeric characters
		dwStyle = dwStyle | ES_NUMBER;
	}

	this->set_all_value->Create(
		dwStyle,
		rect,
		this,
		ID_PARAM_SET_VALUE
	);

	return TRUE;
}


void ParamSetAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


void ParamSetAllDlg::OnOK()
{
	CString valueText;
	GetDlgItemText(ID_PARAM_SET_VALUE, valueText);

	CT2CA pszConvertedAnsiString(valueText);
	std::string valueString(pszConvertedAnsiString);

	// Call method in parent to set the values
	this->card->SetAll(valueString);

	// Call the default OnOK to close the dialog
	CDialog::OnOK();
}

