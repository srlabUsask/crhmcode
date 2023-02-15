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
#include "GridCell.h"


GridCell::GridCell(ClassPar* par, int row, int col)
	: CEdit()
{
	this->param = par;
	this->row = row;
	this->col = col;
	
	this->black = RGB(0, 0, 0);
	this->white = RGB(255, 255, 255);
	this->yellow = RGB(255, 255, 0);
	this->currentColour = this->white;
	this->background_brush_white.CreateSolidBrush(this->white);
	this->background_brush_yellow.CreateSolidBrush(this->yellow);
}


BEGIN_MESSAGE_MAP(GridCell, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


HBRUSH GridCell::CtlColor(CDC* pDC, UINT nCtlColor)
{
	if (this->calculateColour() == this->yellow)
	{
		pDC->SetTextColor(this->black);
		pDC->SetBkColor(this->yellow);
		this->currentColour = this->yellow;
		return this->background_brush_yellow;
	}
	else
	{
		pDC->SetTextColor(this->black);
		pDC->SetBkColor(this->white);
		this->currentColour = this->white;
		return this->background_brush_white;
	}
}


COLORREF GridCell::calculateColour()
{
	bool changed = false;

	int lineLength = this->LineLength(0);
	LPTSTR buffer = new TCHAR[lineLength+1];
	
	if (lineLength > 0)
	{
		int charsRead = this->GetLine(0, buffer);
		if (charsRead != lineLength)
		{
			delete[] buffer;
			return this->currentColour;
		}
	}
	buffer[lineLength] = L'\0';

	CT2CA pszConvertedAnsiString(buffer);
	std::string valueString(pszConvertedAnsiString);

	if (this->param->varType == TVar::Float)
	{
		double current{};
		try
		{
			current = std::stod(valueString);
		}
		catch (const std::invalid_argument&)
		{
			delete[] buffer;
			return this->yellow;	
		}

		double original = this->param->layvalues[this->row][this->col];

		if (std::abs(original - current) > DBL_EPSILON)
		{
			changed = true;
		}

	}
	else if (this->param->varType == TVar::Int)
	{
		long current{};
		try
		{
			current = std::stol(valueString);
		}
		catch (const std::invalid_argument&)
		{
			delete[] buffer;
			return this->yellow;
		}

		long original = this->param->ilayvalues[this->row][this->col];

		if (original != current)
		{
			changed = true;
		}
	}
	else if (this->param->varType == TVar::Txt)
	{
		std::string current = valueString;

		std::string original;
		try
		{
			original = this->param->Strings->at(this->col);
		}
		catch (const std::out_of_range&)
		{
			delete[] buffer;
			return this->white;
		}

		if (original != current)
		{
			changed = true;
		}
	}

	delete[] buffer;
	
	if (changed)
	{
		return this->yellow;
	}
	else
	{
		return this->white;
	}
	
}


void GridCell::setColourToYellow()
{
	this->currentColour = this->yellow;
}