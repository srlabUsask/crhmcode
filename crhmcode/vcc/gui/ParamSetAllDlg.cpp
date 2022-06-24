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

