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