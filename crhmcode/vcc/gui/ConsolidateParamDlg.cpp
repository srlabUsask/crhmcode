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

	//this->scrollPane->SetCards(selectionList);
}


