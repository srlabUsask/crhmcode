#include "ConsolidateParamCard.h"


ConsolidateParamCard::ConsolidateParamCard(ClassPar* param, CWnd* pParent)
	: ParamDlgCardShared(param, pParent)
{
}

BEGIN_MESSAGE_MAP(ConsolidateParamCard, ParamDlgCardShared)
END_MESSAGE_MAP()


bool ConsolidateParamCard::call_create(CWnd* pParent)
{
	return Create(ConsolidateParamCard::IDD, pParent);
}

void ConsolidateParamCard::InitalizeValues()
{
	ParamDlgCardShared::InitalizeValues();

	this->module_name.SetFont(this->pointFont120);

	CString moduleText(this->parameter->module.c_str());
	SetDlgItemText(ID_MODULE_NAME, moduleText);

}


void ConsolidateParamCard::DoDataExchange(CDataExchange* pDX)
{
	ParamDlgCardShared::DoDataExchange(pDX);
	DDX_Control(pDX, ID_MODULE_NAME, this->module_name);
}