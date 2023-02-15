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
#include "ParamDlgCard.h"


ParamDlgCard::ParamDlgCard(ClassPar * param, FontsContainer * fonts, CWnd * pParent)
	: CDialog(ParamDlgCard::IDD, (CWnd*)pParent)
{
	this->scroll_position = 0;
	this->pane_width = 0;
	this->parameter = param;

	this->pointFont120 = fonts->pointFont120;
	this->pointFont100 = fonts->pointFont100;
	this->pointFont80 = fonts->pointFont80;
	this->pointFont60 = fonts->pointFont60;
}


bool ParamDlgCard::call_create(CWnd* pParent)
{
	return Create(ParamDlgCard::IDD, pParent);
}


ParamDlgCard::~ParamDlgCard()
{

	// Starts at 1 because the first item is not dynamicaly allocated
	for (size_t i = 1; i < this->rowLabels.size(); i++)
	{
		delete this->rowLabels[i];
	}

	// Starts at 1 beacuse the first item is not dynamcialy allocated
	for (size_t i = 1; i < this->colHeaders.size(); i++)
	{
		delete this->colHeaders[i];
	}

	for (size_t i = 0; i < this->valueGrid.size(); i++)
	{
		for (size_t j = 0; j < this->valueGrid[i].size(); j++)
		{
			delete this->valueGrid[i][j];
		}
	}
}


void ParamDlgCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PARAM_NAME, this->param_name);
	DDX_Control(pDX, ID_PARAM_UNITS_LABEL, this->param_units_label);
	DDX_Control(pDX, ID_PARAM_MAX_LABEL, this->param_max_label);
	DDX_Control(pDX, ID_PARAM_MIN_LABEL, this->param_min_label);
	DDX_Control(pDX, ID_PARAM_DEFAULT_LABEL, this->param_default_label);
	DDX_Control(pDX, ID_PARAM_UNITS, this->param_units);
	DDX_Control(pDX, ID_PARAM_MAX_VALUE, this->param_max_value);
	DDX_Control(pDX, ID_PARAM_MIN_VALUE, this->param_min_value);
	DDX_Control(pDX, ID_PARAM_DEFAULT_VALUE, this->param_default_value);
	DDX_Control(pDX, ID_PARAM_COL, this->param_col);
	DDX_Control(pDX, ID_PARAM_HELP, this->param_help);
	DDX_Control(pDX, ID_PARAM_ROW, this->param_row);
}


BEGIN_MESSAGE_MAP(ParamDlgCard, CDialog)
	ON_BN_CLICKED(ID_PARAM_SET_BTN, &ParamDlgCard::OnSetAllButton)
	ON_BN_CLICKED(ID_PARAM_RESET_BTN, &ParamDlgCard::OnResetButton)
	ON_BN_CLICKED(ID_PARAM_SAVE_BTN, &ParamDlgCard::OnSaveButton)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


void ParamDlgCard::OnOK()
{
	//Do nothing this prevents the enter key from closing the card
}


void ParamDlgCard::OnCancel()
{
	//Do nothing this prevents the escape key from closing the card
}


void ParamDlgCard::OnSaveButton()
{
	CWaitCursor wait;

	int numLayers = this->valueGrid.size();
	for (int i = 0; i < numLayers; i++)
	{
		int numHru = this->valueGrid[i].size();
		for (int j = 0; j < numHru; j++)
		{
			int controlID = valueGrid[i][j]->GetDlgCtrlID();
			CString valueText;
			GetDlgItemText(controlID, valueText);

			CT2CA pszConvertedAnsiString(valueText);
			std::string valueString(pszConvertedAnsiString);

			if (this->parameter->varType == TVar::Float)
			{
				double proposedValue;
				try
				{
					proposedValue = std::stod(valueString);
				}
				catch (const std::invalid_argument& e)
				{
					std::string position = "cell " + to_string(i+1) + ", " + to_string(j+1);
					std::string exceptMsg = e.what();
					std::string errorMsg = "A non decimal value was entered in "+position+". \n\nError Message: "+exceptMsg;
					CString text(errorMsg.c_str());
					MessageBox(text, MB_OK);
					return;
				}
				catch (const std::out_of_range& e)
				{
					std::string position = "cell " + to_string(i + 1) + "," + to_string(j + 1);
					std::string exceptMsg = e.what();
					std::string errorMsg = "The value in "+position + " cannot fit in a double type. \n\nError Message: " + exceptMsg;
					CString text(errorMsg.c_str());
					MessageBox(text, MB_OK);
					return;
				}

				double min = this->parameter->minVal;
				double max = this->parameter->maxVal;

				if (proposedValue >= min && proposedValue <= max)
				{
					this->parameter->layvalues[i][j] = proposedValue;
				}
				else
				{
					std::string position = "cell " + to_string(i + 1) + "," + to_string(j + 1);
					std::string errorMsg = "The value entered in " +position+" is not within the parameter's range";
					CString text(errorMsg.c_str());
					MessageBox(text, MB_OK);
					return;
				}
				
			}
			else if (this->parameter->varType == TVar::Int)
			{
				long proposedValue;
				try
				{
					proposedValue = std::stol(valueString);
				}
				catch (const std::invalid_argument& e)
				{
					std::string position = "cell " + to_string(i + 1) + ", " + to_string(j + 1);
					std::string exceptMsg = e.what();
					std::string errorMsg = "A non integer value was entered in " + position + ". \n\nError Message: " + exceptMsg;
					CString text(errorMsg.c_str());
					MessageBox(text, MB_OK);
					return;
				}
				catch (const std::out_of_range& e)
				{
					std::string position = "cell " + to_string(i + 1) + "," + to_string(j + 1);
					std::string exceptMsg = e.what();
					std::string errorMsg = "The value in " + position + " cannot fit in a long type. \n\nError Message: " + exceptMsg;
					CString text(errorMsg.c_str());
					MessageBox(text, MB_OK);
					return;
				}

				long min = (long) this->parameter->minVal;
				long max = (long) this->parameter->maxVal;

				if (proposedValue >= min && proposedValue <= max)
				{
					this->parameter->ilayvalues[i][j] = proposedValue;
				}
				else
				{
					std::string position = "cell " + to_string(i + 1) + "," + to_string(j + 1);
					std::string errorMsg = "The value entered in " + position + " is not within the parameter's range";
					CString text(errorMsg.c_str());
					MessageBox(text, MB_OK);
					return;
				}

			}
			else if (this->parameter->varType == TVar::Txt)
			{
				this->parameter->Strings->at(j) = valueString;
			}

		}

	}

	this->RemoveGrid();
	this->RenderGrid();
}


void ParamDlgCard::OnResetButton()
{
	this->RemoveGrid();
	this->RenderGrid();
}


void ParamDlgCard::OnSetAllButton()
{
	ParamSetAllDlg* setAllDlg;
	setAllDlg = new ParamSetAllDlg(this, (CWnd*)this);
	setAllDlg->DoModal();
	delete setAllDlg;
}


void ParamDlgCard::SetAll(std::string valueString)
{

	int numLayers = this->valueGrid.size();
	for (int i = 0; i < numLayers; i++)
	{
		int numHru = this->valueGrid[i].size();
		for (int j = 0; j < numHru; j++)
		{
			((GridCell *)valueGrid[i][j])->setColourToYellow();

			int controlID = valueGrid[i][j]->GetDlgCtrlID();

			CString valueText(valueString.c_str());

			SetDlgItemText(controlID, valueText);

		}
	}

}


void ParamDlgCard::ResetGrid()
{
	this->OnResetButton();
}


void ParamDlgCard::SaveCard()
{
	this->OnSaveButton();
}


BOOL ParamDlgCard::OnInitDialog()
{
	CDialog::OnInitDialog();

	// save the original size
	GetWindowRect(this->original_rectangle);

	// initial scroll position
	scroll_position = 0; 

	return TRUE;
}


void ParamDlgCard::InitalizeValues()
{
	CWaitCursor wait;

	/*
	* Setting fonts for CEdit boxes
	*/
	this->param_name.SetFont(this->pointFont120);
	this->param_units_label.SetFont(this->pointFont120);
	this->param_max_label.SetFont(this->pointFont120);
	this->param_min_label.SetFont(this->pointFont120);
	this->param_default_label.SetFont(this->pointFont120);
	
	this->param_units.SetFont(this->pointFont100);
	this->param_min_value.SetFont(this->pointFont100);
	this->param_max_value.SetFont(this->pointFont100);
	this->param_default_value.SetFont(this->pointFont100);
	this->param_col.SetFont(this->pointFont100);

	this->param_help.SetFont(this->pointFont80);
	this->param_row.SetFont(this->pointFont80);

	/*
	* Set text for CEdit Boxes
	*/
	std::string nameString = this->parameter->param;
	CString nameText = CString(nameString.c_str());
	SetDlgItemText(ID_PARAM_NAME, nameText);

	std::string helpString = this->parameter->help;
	CString helpText = CString(helpString.c_str());
	SetDlgItemText(ID_PARAM_HELP, helpText);

	std::string unitString = this->parameter->units;
	CString unitText = CString(unitString.c_str());
	SetDlgItemText(ID_PARAM_UNITS, unitText);

	std::stringstream minStream;
	minStream << this->parameter->minVal;
	std::string minString;
	minStream >> minString;
	CString minText = CString(minString.c_str());
	SetDlgItemText(ID_PARAM_MIN_VALUE, minText);

	std::stringstream maxStream;
	maxStream << this->parameter->maxVal;
	std::string maxString;
	maxStream >> maxString;
	CString maxText = CString(maxString.c_str());
	SetDlgItemText(ID_PARAM_MAX_VALUE, maxText);

	std::string defalultString = this->parameter->valstr;
	CString defaultText = CString(defalultString.c_str());
	SetDlgItemText(ID_PARAM_DEFAULT_VALUE, defaultText);

	SetDlgItemText(ID_PARAM_UNITS_LABEL, L"Units:");
	SetDlgItemText(ID_PARAM_MIN_LABEL, L"Min:");
	SetDlgItemText(ID_PARAM_MAX_LABEL, L"Max:");
	SetDlgItemText(ID_PARAM_DEFAULT_LABEL, L"Default:");
}


bool ParamDlgCard::RenderGrid()
{
	CWaitCursor wait;

	// Place the first col guide CEdit in the vector
	this->colHeaders.push_back(&this->param_col);

	// Place the first row guide CEdit in the vector
	this->rowLabels.push_back(&this->param_row);

	/*
	* Set the text for the grid guide items.
	*/
	std::string gridRowLabel = this->parameter->param + "[1]";
	CString gridRowLabelText = CString(gridRowLabel.c_str());
	SetDlgItemText(ID_PARAM_ROW, gridRowLabelText);

	std::string gridColLabel = "HRU[1]";
	CString gridColLabelText = CString(gridColLabel.c_str());
	SetDlgItemText(ID_PARAM_COL, gridColLabelText);

	// Create the column header cells
	int numCol = (int)this->parameter->dim;
	for (int i = 1; i < numCol; i++)
	{
		// Determine the location for the cell
		CRect columnRectangle;
		this->colHeaders[i - 1]->GetWindowRect(&columnRectangle);
		ScreenToClient(&columnRectangle);
		int width = columnRectangle.Width();
		columnRectangle.TopLeft().x = columnRectangle.TopLeft().x + width;
		columnRectangle.BottomRight().x = columnRectangle.BottomRight().x + width;

		// Create a CEdit for the cell
		CEdit* colHeader = new CEdit();
		DWORD dwStyle = ES_CENTER | ES_READONLY | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP;
		bool creationSuccess = colHeader->Create(
			dwStyle,
			columnRectangle,
			this,
			ID_PARAM_COL + i
		);

		// Return false if creation failed.
		if (!creationSuccess)
		{
			delete colHeader;
			return false;
		}

		// Set the font and text for the cell
		colHeader->SetFont(this->pointFont100);
		std::string colString = "HRU[" + std::to_string(i+1) + "]";
		CString colText = CString(colString.c_str());
		SetDlgItemText(ID_PARAM_COL + i, colText);

		// Place the CEdit into the vector
		this->colHeaders.push_back(colHeader);
	}

	// Create the row label cells
	int numRow = (int) this->parameter->lay;
	for (int i = 1; i < numRow; i++)
	{
		// Determine the location for the cell
		CRect rowRectangle;
		this->rowLabels[i - 1]->GetWindowRect(&rowRectangle);
		ScreenToClient(&rowRectangle);
		int height = rowRectangle.Height();
		rowRectangle.TopLeft().y = rowRectangle.TopLeft().y + height;
		rowRectangle.BottomRight().y = rowRectangle.BottomRight().y + height;

		// Create a CEdit for the cell
		CEdit* rowHeader = new CEdit();
		DWORD dwStyle = ES_READONLY | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP;
		bool creationSuccess = rowHeader->Create(
			dwStyle,
			rowRectangle,
			this,
			ID_PARAM_ROW + i
		);

		if (!creationSuccess)
		{
			delete rowHeader;
			return false;
		}

		// Set the font and text for the cell
		rowHeader->SetFont(this->pointFont80);
		std::string rowString = this->parameter->param + "[" + std::to_string(i + 1) + "]";
		CString rowText = CString(rowString.c_str());
		SetDlgItemText(ID_PARAM_ROW + i, rowText);

		// Place the CEdit into the vector
		this->rowLabels.push_back(rowHeader);
	}

	// Initalize space for the valueGrid of CEdit cells
	this->valueGrid.resize(numRow);

	// Create the value grid
	for (int i = 0; i < numRow; i++)
	{
		// Find the Y coordinates for the new cell
		CRect rowGuideRect;
		this->rowLabels[i]->GetWindowRect(&rowGuideRect);
		ScreenToClient(&rowGuideRect);
		int topY = rowGuideRect.TopLeft().y;
		int botY = rowGuideRect.BottomRight().y;

		for (int j = 0; j < numCol; j++)
		{
			// Find the X coordinates for the new cell
			CRect colGuideRect;
			this->colHeaders[j]->GetWindowRect(&colGuideRect);
			ScreenToClient(&colGuideRect);
			int topX = colGuideRect.TopLeft().x;
			int botX = colGuideRect.BottomRight().x;

			// Set the positon of the rectangle for the new cell
			CRect newCellRect;
			newCellRect.TopLeft().x = topX;
			newCellRect.TopLeft().y = topY;
			newCellRect.BottomRight().x = botX;
			newCellRect.BottomRight().y = botY;

			// Set the styles for the new cell
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_RIGHT;
			if (this->parameter->varType == TVar::Int)
			{
				// If it is a numberic cell add the ES_NUMBER style to prevent non numeric characters
				dwStyle = dwStyle | ES_NUMBER;
			}

			// Create a CEdit for the cell
			GridCell* newCell = new GridCell(this->parameter, i, j);
			bool creationSuccess = newCell->Create(
				dwStyle,
				newCellRect,
				this,
				ID_PARAM_GRID + (i *1000) + j
			);

			if (!creationSuccess)
			{
				delete newCell;
				return false;
			}

			// Set the font for the cell
			newCell->SetFont(this->pointFont80);
			
			// Set the inital value in the cell
			std::stringstream valueStream;
			std::string valueString;
			if (this->parameter->varType == TVar::Float)
			{
				valueStream << this->parameter->layvalues[i][j];
				valueStream >> valueString;
			}
			else if (this->parameter->varType == TVar::Int)
			{
				valueStream << this->parameter->ilayvalues[i][j];
				valueStream >> valueString;
			}
			else if (this->parameter->varType == TVar::Txt)
			{
				if ((int)this->parameter->Strings->size() > j)
				{
					valueStream << this->parameter->Strings->at(j);
					valueStream >> valueString;
				}
				else
				{
					valueString = "";
				}
			}

			CString valueText = CString(valueString.c_str());
			SetDlgItemText(ID_PARAM_GRID + (i * 1000) + j, valueText);

			// Place the CEdit into the value grid to be tracked
			this->valueGrid[i].push_back(newCell);
		}

	}

	return true;

}


void ParamDlgCard::RemoveGrid()
{
	// Starts at 1 because the first item is not dynamicaly allocated
	for (size_t i = 1; i < this->rowLabels.size(); i++)
	{
		delete this->rowLabels[i];
	}

	this->rowLabels.clear();

	// Starts at 1 beacuse the first item is not dynamcialy allocated
	for (size_t i = 1; i < this->colHeaders.size(); i++)
	{
		delete this->colHeaders[i];
	}

	this->colHeaders.clear();

	for (size_t i = 0; i < this->valueGrid.size(); i++)
	{
		for (size_t j = 0; j < this->valueGrid[i].size(); j++)
		{
			delete this->valueGrid[i][j];
		}
		this->valueGrid[i].clear();
	}

	this->valueGrid.clear();
}


void ParamDlgCard::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	int nMaxPos = original_rectangle.Width() - pane_width;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (scroll_position >= nMaxPos)
			return;

		nDelta = min(max(nMaxPos/20,5),nMaxPos-scroll_position);
		break;

	case SB_LINEUP:
		if (scroll_position <= 0)
			return;
		nDelta = -min(max(nMaxPos/20,5),scroll_position);
		break;
	case SB_PAGEDOWN:
		if (scroll_position >= nMaxPos)
			return;
		nDelta = min(max(nMaxPos/10,5),nMaxPos-scroll_position);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - scroll_position;
		break;

	case SB_PAGEUP:
		if (scroll_position <= 0)
			return;
		nDelta = -min(max(nMaxPos/10,5),scroll_position);
		break;
	
		 default:
		return;
	}
	scroll_position += nDelta;
	SetScrollPos(SB_HORZ,scroll_position,TRUE);
	ScrollWindow(-nDelta,0);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void ParamDlgCard::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	pane_width = cx;

	SCROLLINFO sih{};
	sih.cbSize = sizeof(SCROLLINFO);
	sih.fMask = SIF_ALL;
	sih.nMin = 0;
	sih.nMax = cx;
	sih.nPage = original_rectangle.Width();
	sih.nPos = 0;
	SetScrollInfo(SB_HORZ, &sih, TRUE);

}


TVar ParamDlgCard::GetParamType()
{
	TVar varType;

	varType = this->parameter->varType;

	return varType;
}