/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
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
	ON_COMMAND(ID_CONTINUE_RUN, &RefreshRateDlg::OnContinueRun)
	ON_COMMAND(ID_END_RUN, &RefreshRateDlg::OnEndRun)
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


void RefreshRateDlg::OnContinueRun()
{
	this->EndDialog((int) this->rate);
}


void RefreshRateDlg::OnEndRun()
{
	this->EndDialog(-1);
}