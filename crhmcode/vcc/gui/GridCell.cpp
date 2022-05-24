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
	this->background_brush_white.CreateSolidBrush(this->white);
	this->background_brush_yellow.CreateSolidBrush(this->yellow);
}

BEGIN_MESSAGE_MAP(GridCell, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

HBRUSH GridCell::CtlColor(CDC* pDC, UINT nCtlColor)
{
	if (this->valueChanged())
	{
		pDC->SetTextColor(this->black);
		pDC->SetBkColor(this->yellow);
		return this->background_brush_yellow;
	}
	else
	{
		pDC->SetTextColor(this->black);
		pDC->SetBkColor(this->white);
		return this->background_brush_white;
	}
}

bool GridCell::valueChanged()
{
	bool changed = false;

	int lineLength = this->LineLength(0);
	LPTSTR buffer = new TCHAR[lineLength+1];
	
	if (lineLength != 0)
	{
		this->GetLine(0, buffer);
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
			return true;
		}

		double original = this->param->layvalues[this->row][this->col];

		if (original != current) 
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
			return true;
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
			return false;
		}

		if (original != current)
		{
			changed = true;
		}
	}

	return changed;
}