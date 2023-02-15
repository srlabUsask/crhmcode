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

#include "ParamDlgCard.h"

/**
* Displays the information for a shared parameter and allows it to be made local
*/
class ParamDlgCardShared : public ParamDlgCard
{
private:

	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_CARD_SHARED };

	/**
	* Handles the pressing of the "Manage Parameter Localy" button
	* 
	* Passes a message up to the ParamDlgScrollablePane
	*/
	afx_msg void OnMakeLocal();

public:

	/**
	* Standard constructor
	*/
	ParamDlgCardShared(ClassPar* param, FontsContainer* fonts, CWnd* pParent);

	/**
	* Creates the dialog object and attaches it to this object.
	* 
	* Must be called directly after the constructor.
	* 
	* @return bool - true if successful false otherwise
	*/
	virtual bool call_create(CWnd* pParent) override;
	
	/**
	* Renders the value grid for the parameter
	* 
	* @return bool - true if successful false otherwise
	*/
	virtual bool RenderGrid() override;

	DECLARE_MESSAGE_MAP()
};

