#include "ParamSetAllDlg.h"

IMPLEMENT_DYNAMIC(ParamSetAllDlg, CDialogEx)

ParamSetAllDlg::ParamSetAllDlg(CWnd* pParent) 
	: CDialogEx(PARAMETERS_SET_ALL_DLG, pParent)
{

}

BEGIN_MESSAGE_MAP(ParamSetAllDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL ParamSetAllDlg::OnInitDialog()
{
	return TRUE;
}

void ParamSetAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

