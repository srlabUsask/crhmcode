#include "RefreshRateDlg.h"

IMPLEMENT_DYNAMIC(RefreshRateDlg, CDialog)

RefreshRateDlg::RefreshRateDlg(RefreshRate rate, CWnd* pParent) 
	: CDialog(RefreshRateDlg::IDD, pParent)
{
	this->rate = rate;
}

BEGIN_MESSAGE_MAP(RefreshRateDlg, CDialog)
	ON_COMMAND(ID_REFRESH_DAILY, &RefreshRateDlg::OnRefreshRateDaily)
	ON_COMMAND(ID_REFRESH_BIWEEKLY, &RefreshRateDlg::OnRefreshRateBiWeekly)
	ON_COMMAND(ID_REFRESH_WEEKLY, &RefreshRateDlg::OnRefreshRateWeekly)
	ON_COMMAND(ID_REFRESH_MONTHLY, &RefreshRateDlg::OnRefreshRateMonthly)
	ON_COMMAND(ID_REFRESH_YEARLY, &RefreshRateDlg::OnRefreshRateYearly)
	ON_COMMAND(ID_REFRESH_ATEND, &RefreshRateDlg::OnRefreshRateAtEnd)
END_MESSAGE_MAP()

BOOL RefreshRateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->CheckRate(this->rate);
	return true;
}

void RefreshRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_REFRESH_DAILY, this->daily_button);
	DDX_Control(pDX, ID_REFRESH_BIWEEKLY, this->biweekly_button);
	DDX_Control(pDX, ID_REFRESH_WEEKLY, this->weekly_button);
	DDX_Control(pDX, ID_REFRESH_MONTHLY, this->monthly_button);
	DDX_Control(pDX, ID_REFRESH_YEARLY, this->yearly_button);
	DDX_Control(pDX, ID_REFRESH_ATEND, this->at_end_button);
}


void RefreshRateDlg::CheckRate(RefreshRate rate)
{
	switch (this->rate)
	{
	case RefreshRate::DAILY:
		this->daily_button.SetCheck(BST_CHECKED);
		this->biweekly_button.SetCheck(BST_UNCHECKED);
		this->weekly_button.SetCheck(BST_UNCHECKED);
		this->monthly_button.SetCheck(BST_UNCHECKED);
		this->yearly_button.SetCheck(BST_UNCHECKED);
		this->at_end_button.SetCheck(BST_UNCHECKED);
		break;
	case RefreshRate::BIWEEKLY:
		this->daily_button.SetCheck(BST_UNCHECKED);
		this->biweekly_button.SetCheck(BST_CHECKED);
		this->weekly_button.SetCheck(BST_UNCHECKED);
		this->monthly_button.SetCheck(BST_UNCHECKED);
		this->yearly_button.SetCheck(BST_UNCHECKED);
		this->at_end_button.SetCheck(BST_UNCHECKED);
		break;
	case RefreshRate::WEEKLY:
		this->daily_button.SetCheck(BST_UNCHECKED);
		this->biweekly_button.SetCheck(BST_UNCHECKED);
		this->weekly_button.SetCheck(BST_CHECKED);
		this->monthly_button.SetCheck(BST_UNCHECKED);
		this->yearly_button.SetCheck(BST_UNCHECKED);
		this->at_end_button.SetCheck(BST_UNCHECKED);
		break;
	case RefreshRate::MONTHLY:
		this->daily_button.SetCheck(BST_UNCHECKED);
		this->biweekly_button.SetCheck(BST_UNCHECKED);
		this->weekly_button.SetCheck(BST_UNCHECKED);
		this->monthly_button.SetCheck(BST_CHECKED);
		this->yearly_button.SetCheck(BST_UNCHECKED);
		this->at_end_button.SetCheck(BST_UNCHECKED);
		break;
	case RefreshRate::YEARLY:
		this->daily_button.SetCheck(BST_UNCHECKED);
		this->biweekly_button.SetCheck(BST_UNCHECKED);
		this->weekly_button.SetCheck(BST_UNCHECKED);
		this->monthly_button.SetCheck(BST_UNCHECKED);
		this->yearly_button.SetCheck(BST_CHECKED);
		this->at_end_button.SetCheck(BST_UNCHECKED);
		break;
	case RefreshRate::ATEND:
		this->daily_button.SetCheck(BST_UNCHECKED);
		this->biweekly_button.SetCheck(BST_UNCHECKED);
		this->weekly_button.SetCheck(BST_UNCHECKED);
		this->monthly_button.SetCheck(BST_UNCHECKED);
		this->yearly_button.SetCheck(BST_UNCHECKED);
		this->at_end_button.SetCheck(BST_CHECKED);
		break;
	default:
		break;
	}
}


void RefreshRateDlg::OnRefreshRateDaily()
{
	this->rate = RefreshRate::DAILY;
	this->CheckRate(this->rate);
}


void RefreshRateDlg::OnRefreshRateBiWeekly()
{
	this->rate = RefreshRate::BIWEEKLY;
	this->CheckRate(this->rate);
}


void RefreshRateDlg::OnRefreshRateWeekly()
{
	this->rate = RefreshRate::WEEKLY;
	this->CheckRate(this->rate);
}


void RefreshRateDlg::OnRefreshRateMonthly()
{
	this->rate = RefreshRate::MONTHLY;
	this->CheckRate(this->rate);
}


void RefreshRateDlg::OnRefreshRateYearly()
{
	this->rate = RefreshRate::YEARLY;
	this->CheckRate(this->rate);
}


void RefreshRateDlg::OnRefreshRateAtEnd()
{
	this->rate = RefreshRate::ATEND;
	this->CheckRate(this->rate);
}