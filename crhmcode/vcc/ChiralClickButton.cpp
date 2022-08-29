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
#include "ChiralClickButton.h"
BEGIN_MESSAGE_MAP(ChiralClickButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

UINT ChiralClickButton::getMessageCodeLeft()
{
	return this->messageCodeLeft;
}

void ChiralClickButton::setMessageCodeLeft(UINT code)
{
	this->messageCodeLeft = code;
}

UINT ChiralClickButton::getMessageCodeRight()
{
	return this->messageCodeRight;
}

void ChiralClickButton::setMessageCodeRight(UINT code)
{
	this->messageCodeRight = code;
}

void ChiralClickButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->SendMessage(this->messageCodeLeft, nFlags, 0);

	CButton::OnRButtonDown(nFlags, point);
}

void ChiralClickButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->SendMessage(this->messageCodeRight, nFlags, 0);

	CButton::OnRButtonDown(nFlags, point);
}
