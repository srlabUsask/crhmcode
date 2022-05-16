#include "ParamSetAllDlg.h"
#include "ParamDlgCard.h"

IMPLEMENT_DYNAMIC(ParamSetAllDlg, CDialogEx)

ParamSetAllDlg::ParamSetAllDlg(ParamDlgCard* paramCard, CWnd* pParent) 
	: CDialogEx(PARAMETERS_SET_ALL_DLG, pParent)
{
	this->card = paramCard;
}

BEGIN_MESSAGE_MAP(ParamSetAllDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL ParamSetAllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void ParamSetAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PARAM_SET_VALUE, this->set_all_value);
}

void ParamSetAllDlg::OnOK()
{
	// Retrive the value in the edit control
	int controlID = this->set_all_value.GetDlgCtrlID();
	CString valueText;
	GetDlgItemText(controlID, valueText);

	CT2CA pszConvertedAnsiString(valueText);
	std::string valueString(pszConvertedAnsiString);

	// Call method in parent to set the values
	this->card->SetAll(valueString);

	// Call the default OnOK to close the dialog
	CDialogEx::OnOK();
}

