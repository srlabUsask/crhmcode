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

#include "ParamDlgCardShared.h" 

/**
* Parameter card for displaying a prameter as an option for consolidation
*/
class ConsolidateParamCard : public ParamDlgCardShared
{
public:
	
	/**
	* Standard constructor
	*/
	ConsolidateParamCard(ClassPar* param, FontsContainer * fonts, CWnd* pParent);

	/**
	* Creates the dialog object and attaches it to this object.
	*
	* Must be called directly after the constructor.
	*
	* @return bool - true if successful false otherwise
	*/
	virtual bool call_create(CWnd* pParent) override;

	/**
	* Initalizes the help information for the parameter card
	*/
	virtual void InitalizeValues();

private:

	/**
	* The CEdit component that holds the name of the module this version of the parameter is from
	*/
	CEdit module_name;

	/**
	* Connect data layer to the view.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Handles the use for all button being clicked. Sends a message up to the CardScrollPane. 
	*/
	afx_msg void ConsolidateParamCard::OnUseForAll();

	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = CONSOLIDATE_PARAM_CARD };

	DECLARE_MESSAGE_MAP()

};

