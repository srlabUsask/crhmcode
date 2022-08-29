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
#include "RightClickListBox.h"
BEGIN_MESSAGE_MAP(RightClickListBox, CListBox)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

UINT RightClickListBox::getMessageCode()
{
	return this->messageCode;
}

void RightClickListBox::setMessageCode(UINT code)
{
	this->messageCode = code;
}

void RightClickListBox::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->SendMessage(this->messageCode, nFlags, 0);

	CListBox::OnRButtonDown(nFlags, point);
}
