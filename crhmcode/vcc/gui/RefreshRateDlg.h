#pragma once

#include "afxdialogex.h"
#include "../resource.h"

/**
* Defines the options for the plot refresh rate.
*
* Daily the plot updates once per simulation day
* Bi-Weekly the plot updates every 4 simulation days
* Weekly the plot updates every 7 simulation days
* Monthly the plot updates every 30 simulation days
* Yearly the plot updates every 365 simulation days
* At End the plot updates only when the simulation is complete
*/
enum class RefreshRate { DAILY, BIWEEKLY, WEEKLY, MONTHLY, YEARLY, ATEND };

class RefreshRateDlg : public CDialog
{
	DECLARE_DYNAMIC(RefreshRateDlg)

public:
	RefreshRateDlg(RefreshRate rate, CWnd* pParent = NULL);

	enum { IDD = REFRESH_RATE_DLG };

private:

	CButton daily_button;
	CButton biweekly_button;
	CButton weekly_button;
	CButton monthly_button;
	CButton yearly_button;
	CButton at_end_button;

	RefreshRate rate;

	BOOL OnInitDialog();

	void DoDataExchange(CDataExchange* pDX);

	void CheckRate(RefreshRate rate);

	void OnRefreshRateDaily();
	void OnRefreshRateBiWeekly();
	void OnRefreshRateWeekly();
	void OnRefreshRateMonthly();
	void OnRefreshRateYearly();
	void OnRefreshRateAtEnd();

	void OnContinueRun();

	void OnEndRun();

	DECLARE_MESSAGE_MAP()
};