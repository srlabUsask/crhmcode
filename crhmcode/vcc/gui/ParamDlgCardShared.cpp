#include "ParamDlgCardShared.h"

ParamDlgCardShared::ParamDlgCardShared(ClassPar* param, CWnd* pParent)
	: ParamDlgCard(param, pParent)
{
}


void ParamDlgCardShared::call_create(CWnd* pParent)
{
	Create(ParamDlgCardShared::IDD, pParent);
}


void ParamDlgCardShared::RenderGrid()
{

	CWaitCursor wait;

	// Place the first col guide CEdit in the vector
	this->colHearders.push_back((CEdit*)GetDlgItem(ID_PARAM_COL));

	// Place the first row guide CEdit in the vector
	this->rowLabels.push_back((CEdit*)GetDlgItem(ID_PARAM_ROW));

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
		GetDlgItem(ID_PARAM_COL + i - 1)->GetWindowRect(&columnRectangle);
		ScreenToClient(&columnRectangle);
		int width = columnRectangle.Width();
		columnRectangle.TopLeft().x = columnRectangle.TopLeft().x + width;
		columnRectangle.BottomRight().x = columnRectangle.BottomRight().x + width;

		// Create a CEdit for the cell
		CEdit* colHeader = new CEdit();
		DWORD dwStyle = ES_CENTER | ES_READONLY | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP;
		colHeader->Create(
			dwStyle,
			columnRectangle,
			this,
			ID_PARAM_COL + i
		);

		// Set the font and text for the cell
		GetDlgItem(ID_PARAM_COL + i)->SetFont(this->pointFont100);
		std::string colString = "HRU[" + std::to_string(i + 1) + "]";
		CString colText = CString(colString.c_str());
		SetDlgItemText(ID_PARAM_COL + i, colText);

		// Place the CEdit into the vector
		this->colHearders.push_back(colHeader);
	}

	// Create the row label cells
	int numRow = (int)this->parameter->lay;
	for (int i = 1; i < numRow; i++)
	{
		// Determine the location for the cell
		CRect rowRectangle;
		GetDlgItem(ID_PARAM_ROW + i - 1)->GetWindowRect(&rowRectangle);
		ScreenToClient(&rowRectangle);
		int height = rowRectangle.Height();
		rowRectangle.TopLeft().y = rowRectangle.TopLeft().y + height;
		rowRectangle.BottomRight().y = rowRectangle.BottomRight().y + height;

		// Create a CEdit for the cell
		CEdit* rowHeader = new CEdit();
		DWORD dwStyle = ES_READONLY | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP;
		rowHeader->Create(
			dwStyle,
			rowRectangle,
			this,
			ID_PARAM_ROW + i
		);

		// Set the font and text for the cell
		GetDlgItem(ID_PARAM_ROW + i)->SetFont(this->pointFont80);
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
		GetDlgItem(ID_PARAM_ROW + i)->GetWindowRect(&rowGuideRect);
		ScreenToClient(&rowGuideRect);
		int topY = rowGuideRect.TopLeft().y;
		int botY = rowGuideRect.BottomRight().y;

		for (int j = 0; j < numCol; j++)
		{
			// Find the X coordinates for the new cell
			CRect colGuideRect;
			GetDlgItem(ID_PARAM_COL + j)->GetWindowRect(&colGuideRect);
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
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_RIGHT | ES_READONLY;
			if (this->parameter->varType == TVar::Int)
			{
				// If it is a numberic cell add the ES_NUMBER style to prevent non numeric characters
				dwStyle = dwStyle | ES_NUMBER;
			}

			// Create a CEdit for the cell
			CEdit* newCell = new CEdit();
			newCell->Create(
				dwStyle,
				newCellRect,
				this,
				ID_PARAM_GRID + (i * 1000) + j
			);

			// Set the font for the cell
			GetDlgItem(ID_PARAM_GRID + (i * 1000) + j)->SetFont(this->pointFont80);

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

}