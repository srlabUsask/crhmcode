#include "RefreshRateDlg.h"

IMPLEMENT_DYNAMIC(RefreshRateDlg, CDialog)

RefreshRateDlg::RefreshRateDlg(RefreshRate rate, CWnd* pParent) 
	: CDialog(RefreshRateDlg::IDD, pParent)
{
	this->rate = rate;
}

BEGIN_MESSAGE_MAP(RefreshRateDlg, CDialog)
END_MESSAGE_MAP()

BOOL RefreshRateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch (this->rate)
	{
	case RefreshRate::DAILY:
		this->daily_button.SetCheck(BST_CHECKED);
		break;
	case RefreshRate::BIWEEKLY:
		this->biweekly_button.SetCheck(BST_CHECKED);
		break;
	case RefreshRate::WEEKLY:
		this->weekly_button.SetCheck(BST_CHECKED);
		break;
	case RefreshRate::MONTHLY:
		this->monthly_button.SetCheck(BST_CHECKED);
		break;
	case RefreshRate::YEARLY:
		this->yearly_button.SetCheck(BST_CHECKED);
		break;
	case RefreshRate::ATEND:
		this->at_end_button.SetCheck(BST_CHECKED);
		break;
	default:
		break;
	}

	return true;
}

void RefreshRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PLOTREFRESHRATE_DAILY, this->daily_button);
	DDX_Control(pDX, ID_PLOTREFRESHRATE_BI, this->biweekly_button);
	DDX_Control(pDX, ID_PLOTREFRESHRATE_WEEKLY, this->weekly_button);
	DDX_Control(pDX, ID_PLOTREFRESHRATE_MONTHLY, this->monthly_button);
	DDX_Control(pDX, ID_PLOTREFRESHRATE_YEARLY, this->yearly_button);
	DDX_Control(pDX, ID_PLOTREFRESHRATE_ATEND, this->at_end_button);
}