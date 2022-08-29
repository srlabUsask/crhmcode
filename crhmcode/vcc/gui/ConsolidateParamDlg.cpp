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
#include "ConsolidateParamDlg.h"


IMPLEMENT_DYNAMIC(ConsolidateParamDlg, CDialog)


ConsolidateParamDlg::ConsolidateParamDlg(std::map<std::string, std::list<ClassPar*>*>* candidates, CWnd* pParent)
	: CDialog(CONSOLIDATE_PARAM_DLG, pParent)
{
	this->candidates = *candidates;
}


ConsolidateParamDlg::~ConsolidateParamDlg()
{
	delete this->scrollPane;
}


BEGIN_MESSAGE_MAP(ConsolidateParamDlg, CDialog)
	ON_LBN_SELCHANGE(ID_CONSOLIDATABLE_LIST_BOX, &ConsolidateParamDlg::OnSelectCandidate)
	ON_MESSAGE(UWM_USE_FOR_ALL, &ConsolidateParamDlg::OnUseForAllMsg)
	ON_BN_CLICKED(ID_CONSOLIDATE_RETURN, &ConsolidateParamDlg::OnReturnClicked)
	ON_BN_CLICKED(ID_CONSOLIDATE_FINISH, &ConsolidateParamDlg::OnFinishClicked)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void ConsolidateParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_CONSOLIDATABLE_LIST_BOX, this->candidates_list_box);
}


BOOL ConsolidateParamDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->InitalizeCandidatesListBox();

	/**
	* Replace the placeholder pane with the parameters scroll pane.
	*/
	this->scrollPane = new CardScrollPane(this);
	CRect rectangle;
	GetDlgItem(ID_CONSOLIDATE_CARDS_PLACEHOLDER)->GetWindowRect(rectangle);
	ScreenToClient(&rectangle);
	this->scrollPane->MoveWindow(rectangle);

	return true;
}


void ConsolidateParamDlg::InitalizeCandidatesListBox()
{
	for (
		std::map<std::string, std::list<ClassPar*>*>::iterator it = this->candidates.begin();
		it != this->candidates.end();
		it++
		)
	{
		CString paramText(it->first.c_str());
		this->candidates_list_box.AddString(paramText);
	}
}


void ConsolidateParamDlg::OnSelectCandidate()
{
	CString paramText;
	this->candidates_list_box.GetText(this->candidates_list_box.GetCurSel(), paramText);

	// Convert the CString to std::string
	CT2CA pszConvertedAnsiString(paramText);
	std::string paramString(pszConvertedAnsiString);

	std::map<std::string, std::list<ClassPar*>*>::iterator selection = this->candidates.find(paramString);

	std::list<ClassPar*>* selectionList = selection->second;
	std::list<std::pair<std::string, ClassPar*>>* paramList = new std::list<std::pair<std::string, ClassPar*>>();

	for (
		std::list<ClassPar*>::iterator it = selectionList->begin();
		it != selectionList->end();
		it++
		)
	{
		paramList->push_back(std::pair<std::string, ClassPar*>("&" + (*it)->param, *it));
	}

	this->scrollPane->SetParameterCards(paramList);

	delete paramList;
}


LRESULT ConsolidateParamDlg::OnUseForAllMsg(WPARAM wParam, LPARAM lParam)
{
	ClassPar * selectedParameter = (ClassPar*)wParam;

	std::map<std::string, std::list<ClassPar*>*>::iterator candidatesIt = this->candidates.find(selectedParameter->param);

	std::list<ClassPar*>* parameterList = candidatesIt->second;

	for (
		std::list<ClassPar*>::iterator it = parameterList->begin();
		it != parameterList->end();
		it++
		)
	{
		for (int i = 0; i < (*it)->lay; i++)
		{
			for (int j = 0; j < (*it)->dim; j++)
			{
				
				if (selectedParameter->varType == TVar::Float)
				{
					(*it)->layvalues[i][j] = selectedParameter->layvalues[i][j];
				}
				else if (selectedParameter->varType == TVar::Int)
				{
					(*it)->ilayvalues[i][j] = selectedParameter->ilayvalues[i][j];
				}
				else if (selectedParameter->varType == TVar::Txt)
				{
					(*it)->Strings[i] = selectedParameter->Strings[i];
				}

			}
		}

	}

	int itemCount = this->candidates_list_box.GetCount();
	for (int i = 0; i < itemCount; i++)
	{
		CString paramText;
		this->candidates_list_box.GetText(i, paramText);

		// Convert the CString to std::string
		CT2CA pszConvertedAnsiString(paramText);
		std::string paramString(pszConvertedAnsiString);

		if (selectedParameter->param == paramString)
		{
			this->candidates_list_box.DeleteString(i);
			break;
		}
	}

	this->scrollPane->SetParameterCards(new std::list<std::pair<std::string, ClassPar*>>());

	return LRESULT();
}


void ConsolidateParamDlg::OnReturnClicked()
{
	this->OnOK();
}


void ConsolidateParamDlg::OnFinishClicked()
{
	this->OnCancel();
}


void ConsolidateParamDlg::OnSize(UINT nType, int cx, int cy)
{
	CWnd* wnd = GetDlgItem(ID_CONSOLIDATE_CARDS_PLACEHOLDER);

	if (wnd != NULL)
	{
		CRect rectangle;
		GetDlgItem(ID_CONSOLIDATE_CARDS_PLACEHOLDER)->GetWindowRect(rectangle);
		ScreenToClient(&rectangle);
		this->scrollPane->MoveWindow(rectangle);
	}
}