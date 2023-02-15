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
#include "ConsolidateParamCard.h"


ConsolidateParamCard::ConsolidateParamCard(ClassPar* param, FontsContainer * fonts, CWnd* pParent)
	: ParamDlgCardShared(param, fonts, pParent)
{
}


BEGIN_MESSAGE_MAP(ConsolidateParamCard, ParamDlgCardShared)
	ON_BN_CLICKED(ID_PARAM_USE_FOR_ALL, &ConsolidateParamCard::OnUseForAll)
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


void ConsolidateParamCard::OnUseForAll()
{
	GetParent()->PostMessage(UWM_USE_FOR_ALL, (WPARAM)this->parameter, (LPARAM)this->parameter);
}