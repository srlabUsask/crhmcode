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

/**
* Dialog that appears when a user clicks while a simulation is running. 
* 
* Allows the user to select a different refresh rate for the TChart plot.
* Also allows the user to end the simulation run prematurely.
*/
class RefreshRateDlg : public CDialog
{
	DECLARE_DYNAMIC(RefreshRateDlg)

public:

	/**
	* Constructor for the RefreshRateDlg. 
	* 
	* @param rate - RefreshRate enum for the currently set refresh rate.
	* @param pParent - CWnd* pointer to the parent window.
	*/
	RefreshRateDlg(RefreshRate rate, CWnd* pParent = NULL);

	/**
	* Defines the Resource ID for the dialog. 
	*/
	enum { IDD = REFRESH_RATE_DLG };

private:

	/**
	* Radial buttons for setting a daily refresh rate.
	*/
	CButton daily_button;

	/**
	* Radial button for setting a bi-weekly refresh rate.
	*/
	CButton biweekly_button;
	
	/**
	* Radial button for setting a weekly refresh rate.
	*/
	CButton weekly_button;

	/**
	* Radial button for setting a montly refresh rate.
	*/
	CButton monthly_button;

	/**
	* Radial button for setting a yearly refresh rate.
	*/
	CButton yearly_button;

	/**
	* Radial button for setting an at end refresh rate.
	*/
	CButton at_end_button;

	/**
	* Stores the currently set refresh rate.
	*/
	RefreshRate rate;

	/**
	* Initalized the dialog.
	*/
	BOOL OnInitDialog();

	/**
	* Connects GUI components to member variables.
	*/
	void DoDataExchange(CDataExchange* pDX);

	/**
	* Checks the corrisponding radio dial button for the passed in refresh rate.
	* Additionaly removes checks from all of the other radio dial buttons. 
	* 
	* @param rate - RefreshRate rate corrisponding for the button to check.
	*/
	void CheckRate(RefreshRate rate);

	/**
	* Handler for when the daily refresh rate dial is clicked. 
	* 
	* Selects the daily rate and unselects all others.
	* Sets the internal rate variable to daily.
	*/
	afx_msg void OnRefreshRateDaily();

	/**
	* Handler for when the bi weekly refresh rate dial is clicked.
	*
	* Selects the bi weekly rate and unselects all others.
	* Sets the internal rate variable to bi weekly.
	*/
	afx_msg void OnRefreshRateBiWeekly();

	/**
	* Handler for when the weekly refresh rate dial is clicked.
	*
	* Selects the weekly rate and unselects all others.
	* Sets the internal rate variable to weekly.
	*/
	afx_msg void OnRefreshRateWeekly();

	/**
	* Handler for when the monthly refresh rate dial is clicked.
	*
	* Selects the monthly rate and unselects all others.
	* Sets the internal rate variable to monthly.
	*/
	afx_msg void OnRefreshRateMonthly();

	/**
	* Handler for when the yearly refresh rate dial is clicked.
	*
	* Selects the yearly rate and unselects all others.
	* Sets the internal rate variable to yearly.
	*/
	afx_msg void OnRefreshRateYearly();

	/**
	* Handler for when the at end refresh rate dial is clicked.
	*
	* Selects the at end rate and unselects all others.
	* Sets the internal rate variable to at end.
	*/
	afx_msg void OnRefreshRateAtEnd();

	/**
	* Handler for when the continue button is clicked. 
	* 
	* Closes the modal window and sends a signal to continue with the set refresh rate.
	*/
	afx_msg void OnContinueRun();

	/**
	* Handler for when the end run button is clicked. 
	* 
	* Closes the modal window and sends a signal to stop the simulation.
	*/
	afx_msg void OnEndRun();

	DECLARE_MESSAGE_MAP()
};