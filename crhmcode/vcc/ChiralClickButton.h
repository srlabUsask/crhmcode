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
#include <afxwin.h>
#include "resource.h"
class ChiralClickButton :
    public CButton
{
public:
    UINT getMessageCodeLeft();
    void setMessageCodeLeft(UINT code);
    UINT getMessageCodeRight();
    void setMessageCodeRight(UINT code);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
    UINT messageCodeLeft{ 0 };
    UINT messageCodeRight{ 0 };
};