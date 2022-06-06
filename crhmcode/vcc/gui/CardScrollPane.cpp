#include "CardScrollPane.h"


CardScrollPane::CardScrollPane(CWnd* pParent /*=NULL*/)
	: CDialog(CardScrollPane::IDD, pParent)
{
	Create(CardScrollPane::IDD,pParent);
	this->scroll_position = 0;
	this->pane_height = 0;
	this->next_card = 8;
}


void CardScrollPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CardScrollPane, CDialog)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_MESSAGE(UWM_MAKE_LOCAL, &CardScrollPane::OnMakeLocalMsg)
END_MESSAGE_MAP()


BOOL CardScrollPane::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// save the original size
	GetWindowRect(original_rectangle);
	GetWindowRect(current_rectangle);

	// initial scroll position
	scroll_position = 0; 
	
	return TRUE;
}


void CardScrollPane::SetParameterCards(std::list<std::pair<std::string, ClassPar*>>* parametersList)
{
	bool success = true;

	// Remove all of the existing cards
	this->RemoveAllCards();

	std::list<std::pair<std::string, ClassPar*>>::iterator lastIt;

	// Render a card for each parameter in the passed in list
	for (
		std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList->begin();
		it != parametersList->end();
		it++
		)
	{
		success = this->AddCard(it);

		if (!success)
		{
			lastIt = it;
			break;
		}
	}

	// Handle not displaying all of the selected cards.
	if (!success)
	{	
		std::list<std::pair<std::string, ClassPar*>> * nonRenderedList = new std::list<std::pair<std::string, ClassPar*>>();
		nonRenderedList->assign(lastIt, parametersList->end());
		parametersList->erase(lastIt, parametersList->end());

		// Send message to parent to no longer select the nonRenderedList
		GetParent()->PostMessage(UWM_UNSELECT_PARAMS, (WPARAM)nonRenderedList, (LPARAM)nonRenderedList);

		// Display a message box with a list of the parameters that cannot be rendered and will be unselected
		std::string temp = std::string("Too many parameters were selected. Excess parameters will be unselected.");
		CString cstr(temp.c_str());
		MessageBox(cstr, MB_OK);

	}

	this->ResizeWindow();
	this->ResizeCards();
}

void CardScrollPane::ResetAllCards()
{
	for (
		size_t i = 0;
		i < this->cards.size();
		i++
		)
	{
		this->cards[i]->ResetGrid();
	}
}


void CardScrollPane::SaveAllCards()
{
	for (
		size_t i = 0;
		i < this->cards.size();
		i++
		)
	{
		this->cards[i]->SaveCard();
	}
}

void CardScrollPane::RemoveAllCards()
{
	for (
		std::vector<ParamDlgCard*>::iterator it = this->cards.begin();
		it != this->cards.end();
		it++
		)
	{
		delete (*it);
	}

	this->cards.clear();
	this->next_card = 8;
}


bool CardScrollPane::AddCard(std::list<std::pair<std::string, ClassPar*>>::iterator data)
{
	bool success = true;
	CRect cardRect;
	this->CalculateCardLocation(&cardRect, (int) data->second->lay, (int) data->second->dim);

	ParamDlgCard * newCard;
	if (data->first.find("*") != std::string::npos)
	{
		newCard = new ParamDlgCardShared(data->second, this);
		newCard->call_create(this);
	}
	else
	{
		newCard = new ParamDlgCard(data->second, this);
		success = newCard->call_create(this);
	}
	newCard->MoveWindow(cardRect);
	newCard->InitalizeValues();
	success = newCard->RenderGrid();

	if (success)
	{
		this->cards.push_back(newCard);
	}
	else
	{
		delete newCard;
	}

	return success;
}


void CardScrollPane::CalculateCardLocation(CRect* rectangle, int numRows, int numCols)
{
	CRect baseSize(0, 0, this->current_rectangle.Width(), 150);
	CRect sizeGuide(0,0,80,20);
	ScreenToClient(&sizeGuide);
	ScreenToClient(&baseSize);
	int guideHeight = sizeGuide.Height();
	int guideWidth = sizeGuide.Width();
	int baseHeight = baseSize.Height();
	int baseWidth = baseSize.Width();

	if (numCols < 11)
	{
		numCols = 11;
	}

	int topX = 8;
	int topY = this->next_card;
	int botX = topX + baseWidth + ((numCols - 11) * guideWidth);
	int botY = topY + baseHeight + (numRows * guideHeight);

	rectangle->TopLeft().x = topX;
	rectangle->TopLeft().y = topY;
	rectangle->BottomRight().x = botX;
	rectangle->BottomRight().y = botY;

	this->next_card = botY + 8;
}


void CardScrollPane::ResizeWindow()
{

	if (this->cards.size() == 0)
	{
		this->current_rectangle.CopyRect(original_rectangle);

		this->SetWindowPos(
			this->GetParent(),
			current_rectangle.TopLeft().x,
			current_rectangle.TopLeft().y,
			current_rectangle.Width(),
			current_rectangle.Height(),
			SWP_SHOWWINDOW
		);

	}
	else
	{
		size_t cardsFactor = this->cards.size();

		current_rectangle.BottomRight().y = original_rectangle.BottomRight().y + (cardsFactor * 250);

		this->SetWindowPos(
			this->GetParent(),
			current_rectangle.TopLeft().x,
			current_rectangle.TopLeft().y,
			current_rectangle.Width(),
			current_rectangle.Height(),
			SWP_SHOWWINDOW
		);

	}

	SCROLLINFO si{};
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = current_rectangle.Height();
	si.nPage = original_rectangle.Height();
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);
	this->scroll_position = 0;
	SetScrollPos(SB_VERT, this->scroll_position, TRUE);

}


void CardScrollPane::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	int nMaxPos = current_rectangle.Height() - pane_height;

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


void CardScrollPane::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	pane_height = cy;

	SCROLLINFO si{};
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = current_rectangle.Height();
	si.nPage = cy;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE); 	

	this->ResizeCards();
}


BOOL CardScrollPane::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nMaxPos = current_rectangle.Height() - pane_height;

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

LRESULT CardScrollPane::OnMakeLocalMsg(WPARAM wParam, LPARAM lParam)
{
	GetParent()->PostMessage(UWM_MAKE_LOCAL, wParam, lParam);
	return 0;
}


void CardScrollPane::ResizeCards()
{
	for (
		size_t i = 0;
		i < this->cards.size();
		i++
		)
	{
		CRect card;
		CRect window;
		this->cards[i]->GetWindowRect(&card);
		this->GetWindowRect(&window);

		if (window.BottomRight().x > card.BottomRight().x)
		{
			card.BottomRight().x = window.BottomRight().x - 20;
			ScreenToClient(&card);
			this->cards[i]->MoveWindow(card);
		}
		
	}

}