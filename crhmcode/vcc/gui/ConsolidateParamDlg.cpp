#include "ConsolidateParamDlg.h"


IMPLEMENT_DYNAMIC(ConsolidateParamDlg, CDialogEx)


ConsolidateParamDlg::ConsolidateParamDlg(std::map<std::string, std::list<ClassPar*>*>* candidates, CWnd* pParent)
	: CDialogEx(CONSOLIDATE_PARAM_DLG, pParent)
{
	this->candidates = *candidates;
}


ConsolidateParamDlg::~ConsolidateParamDlg()
{
}


void ConsolidateParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_CONSOLIDATABLE_LIST_BOX, this->candidates_list_box);
}


BOOL ConsolidateParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->InitalizeCandidatesListBox();

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


BEGIN_MESSAGE_MAP(ConsolidateParamDlg, CDialogEx)
END_MESSAGE_MAP()