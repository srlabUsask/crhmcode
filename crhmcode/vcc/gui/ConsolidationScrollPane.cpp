#include "ConsolidationScrollPane.h"


BEGIN_MESSAGE_MAP(ConsolidationScrollPane, CDialog)
END_MESSAGE_MAP()


ConsolidationScrollPane::ConsolidationScrollPane(CWnd* pParent)
{
	Create(ConsolidationScrollPane::IDD, pParent);

}


ConsolidationScrollPane::~ConsolidationScrollPane()
{
}


void ConsolidationScrollPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL ConsolidationScrollPane::OnInitDialog()
{
	CDialog::OnInitDialog();

	return true;
}