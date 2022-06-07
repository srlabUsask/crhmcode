#include "ConsolidateParamDlg.h"


IMPLEMENT_DYNAMIC(ConsolidateParamDlg, CDialogEx)


ConsolidateParamDlg::ConsolidateParamDlg(std::map<std::string, std::list<ClassPar*>*>* candidates, CWnd* pParent)
	: CDialogEx(CONSOLIDATE_PARAM_DLG, pParent)
{
	this->candidates = *candidates;
}


ConsolidateParamDlg::~ConsolidateParamDlg()
{
	delete this->scrollPane;
}


BEGIN_MESSAGE_MAP(ConsolidateParamDlg, CDialogEx)
	ON_LBN_SELCHANGE(ID_CONSOLIDATABLE_LIST_BOX, &ConsolidateParamDlg::OnSelectCandidate)
	ON_MESSAGE(UWM_USE_FOR_ALL, &ConsolidateParamDlg::OnUseForAllMsg)
	ON_BN_CLICKED(ID_CONSOLIDATE_RETURN, &ConsolidateParamDlg::OnReturnClicked)
	ON_BN_CLICKED(ID_CONSOLIDATE_FINISH, &ConsolidateParamDlg::OnFinishClicked)
END_MESSAGE_MAP()


void ConsolidateParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_CONSOLIDATABLE_LIST_BOX, this->candidates_list_box);
}


BOOL ConsolidateParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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