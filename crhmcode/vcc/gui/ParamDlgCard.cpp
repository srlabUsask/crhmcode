#include "ParamDlgCard.h"


ParamDlgCard::ParamDlgCard(ClassPar * param, CWnd* pParent /*=NULL*/ )
	: CDialog(ParamDlgCard::IDD, pParent)
{
	Create(ParamDlgCard::IDD,pParent);
	this->scroll_position = 0;
	this->pane_height = 0;
	this->parameter = param;

	this->pointFont120 = new CFont();
	this->pointFont120->CreatePointFont(120, _T("Ariel"));

	this->pointFont100 = new CFont();
	this->pointFont100->CreatePointFont(100, _T("Ariel"));

	this->pointFont80 = new CFont();
	this->pointFont80->CreatePointFont(80, _T("Ariel"));

	this->pointFont60 = new CFont();
	this->pointFont60->CreatePointFont(60, _T("Ariel"));
}

ParamDlgCard::~ParamDlgCard()
{
	delete this->pointFont120;
	delete this->pointFont100;
	delete this->pointFont80;
	delete this->pointFont60;

	// Starts at 1 because the first item is not dynamicaly allocated
	for (int i = 1; i < this->rowLabels.size(); i++)
	{
		delete this->rowLabels[i];
	}

	// Starts at 1 beacuse the first item is not dynamcialy allocated
	for (int i = 1; i < this->colHearders.size(); i++)
	{
		delete this->colHearders[i];
	}

	for (int i = 0; i < this->valueGrid.size(); i++)
	{
		for (int j = 0; j < this->valueGrid[i].size(); j++)
		{
			delete this->valueGrid[i][j];
		}
	}
}


void ParamDlgCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ParamDlgCard, CDialog)
	ON_BN_CLICKED(ID_PARAM_SET_BTN, &ParamDlgCard::OnSetAllButton)
	ON_BN_CLICKED(ID_PARAM_RESET_BTN, &ParamDlgCard::OnResetButton)
	ON_BN_CLICKED(ID_PARAM_SAVE_BTN, &ParamDlgCard::OnSaveButton)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
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
				this->parameter->layvalues[i][j] = std::stod(valueString);
			}
			else if (this->parameter->varType == TVar::Int)
			{
				this->parameter->ilayvalues[i][j] = std::stol(valueString);
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
	setAllDlg = new ParamSetAllDlg();

	setAllDlg->DoModal();
}

BOOL ParamDlgCard::OnInitDialog()
{
	CDialog::OnInitDialog();

	// save the original size
	GetWindowRect(original_rectangle);

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
	GetDlgItem(ID_PARAM_NAME)->SetFont(this->pointFont120);
	GetDlgItem(ID_PARAM_UNITS_LABEL)->SetFont(this->pointFont120);
	GetDlgItem(ID_PARAM_MAX_LABEL)->SetFont(this->pointFont120);
	GetDlgItem(ID_PARAM_MIN_LABEL)->SetFont(this->pointFont120);
	GetDlgItem(ID_PARAM_DEFAULT_LABEL)->SetFont(this->pointFont120);

	GetDlgItem(ID_PARAM_UNITS)->SetFont(this->pointFont100);
	GetDlgItem(ID_PARAM_MIN_VALUE)->SetFont(this->pointFont100);
	GetDlgItem(ID_PARAM_MAX_VALUE)->SetFont(this->pointFont100);
	GetDlgItem(ID_PARAM_DEFAULT_VALUE)->SetFont(this->pointFont100);
	GetDlgItem(ID_PARAM_COL)->SetFont(this->pointFont100);

	GetDlgItem(ID_PARAM_HELP)->SetFont(this->pointFont80);
	GetDlgItem(ID_PARAM_ROW)->SetFont(this->pointFont80);

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


void ParamDlgCard::RenderGrid()
{
	CWaitCursor wait;

	// Place the first col guide CEdit in the vector
	this->colHearders.push_back((CEdit*)GetDlgItem(ID_PARAM_COL));

	// Place the first row guide CEdit in the vector
	this->rowLabels.push_back((CEdit *)GetDlgItem(ID_PARAM_ROW));

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
		std::string colString = "HRU[" + std::to_string(i+1) + "]";
		CString colText = CString(colString.c_str());
		SetDlgItemText(ID_PARAM_COL + i, colText);

		// Place the CEdit into the vector
		this->colHearders.push_back(colHeader);
	}

	// Create the row label cells
	int numRow = (int) this->parameter->lay;
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
			DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_RIGHT;
			if (this->parameter->varType == TVar::Int)
			{
				// If it is a numberic cell add the ES_NUMBER style to prevent non numeric characters
				dwStyle =dwStyle | ES_NUMBER;
			}

			// Create a CEdit for the cell
			CEdit* newCell = new CEdit();
			newCell->Create(
				dwStyle,
				newCellRect,
				this,
				ID_PARAM_GRID + (i *1000) + j
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
				if (this->parameter->Strings->size() > j)
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

void ParamDlgCard::RemoveGrid()
{
	// Starts at 1 because the first item is not dynamicaly allocated
	for (int i = 1; i < this->rowLabels.size(); i++)
	{
		delete this->rowLabels[i];
	}

	this->rowLabels.clear();

	// Starts at 1 beacuse the first item is not dynamcialy allocated
	for (int i = 1; i < this->colHearders.size(); i++)
	{
		delete this->colHearders[i];
	}

	this->colHearders.clear();

	for (int i = 0; i < this->valueGrid.size(); i++)
	{
		for (int j = 0; j < this->valueGrid[i].size(); j++)
		{
			delete this->valueGrid[i][j];
		}
		this->valueGrid[i].clear();
	}

	this->valueGrid.clear();
}

void ParamDlgCard::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	int nMaxPos = original_rectangle.Height() - pane_height;

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
	SetScrollPos(SB_VERT,scroll_position,TRUE);
	ScrollWindow(0,-nDelta);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void ParamDlgCard::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	pane_height = cy;

	SCROLLINFO si{};
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = original_rectangle.Height();
	si.nPage = cy;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE); 	

}


BOOL ParamDlgCard::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nMaxPos = original_rectangle.Height() - pane_height;

	if (zDelta<0)
	{
		if (scroll_position < nMaxPos)
		{
			zDelta = min(max(nMaxPos/20,5),nMaxPos-scroll_position);

			scroll_position += zDelta;
			SetScrollPos(SB_VERT,scroll_position,TRUE);
			ScrollWindow(0,-zDelta);
		}
	}
	else
	{
		if (scroll_position > 0)
		{
			zDelta = -min(max(nMaxPos/20,5),scroll_position);

			scroll_position += zDelta;
			SetScrollPos(SB_VERT,scroll_position,TRUE);
			ScrollWindow(0,-zDelta);
		}
	}
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
