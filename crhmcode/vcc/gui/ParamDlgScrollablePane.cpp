#include "ParamDlgScrollablePane.h"


ParamDlgScrollablePane::ParamDlgScrollablePane(CWnd* pParent /*=NULL*/)
	: CDialog(ParamDlgScrollablePane::IDD, pParent)
{
	Create(ParamDlgScrollablePane::IDD,pParent);
	this->scroll_position = 0;
	this->pane_height = 0;
}


void ParamDlgScrollablePane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ParamDlgScrollablePane, CDialog)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL ParamDlgScrollablePane::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// save the original size
	GetWindowRect(original_rectangle);
	GetWindowRect(current_rectangle);

	// initial scroll position
	scroll_position = 0; 
	
	return TRUE;
}


void ParamDlgScrollablePane::UpdateParametersCards(std::list<std::pair<std::string, ClassPar*>>* parametersList)
{
	this->RemoveAllCards();

	for (
		std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList->begin();
		it != parametersList->end();
		it++
		)
	{
		this->AddCard(it);
	}

}


void ParamDlgScrollablePane::RemoveAllCards()
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
}


void ParamDlgScrollablePane::AddCard(std::list<std::pair<std::string, ClassPar*>>::iterator data)
{
	CRect cardRect;
	this->CalculateCardLocation(&cardRect);

	this->ResizeWindow();

	ParamDlgCard * newCard = new ParamDlgCard(data->second, this);
	newCard->MoveWindow(cardRect);
	newCard->InitalizeValues();

	this->cards.push_back(newCard);
	
}


void ParamDlgScrollablePane::CalculateCardLocation(CRect* rect)
{
	size_t offsetFactor = this->cards.size();

	int topX = 8;
	int topY = 8 + (offsetFactor * 250);
	int botX = this->current_rectangle.BottomRight().x - 50;
	int botY = topY + 240;

	rect->TopLeft().x = topX;
	rect->TopLeft().y = topY;
	rect->BottomRight().x = botX;
	rect->BottomRight().y = botY;

}


void ParamDlgScrollablePane::ResizeWindow()
{

	this->current_rectangle.InflateRect(0, 250);

	this->SetWindowPos(
		this->GetParent(),
		current_rectangle.TopLeft().x,
		current_rectangle.TopLeft().y,
		current_rectangle.Width(),
		current_rectangle.Height(),
		SWP_SHOWWINDOW
	);

	SCROLLINFO si{};
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = current_rectangle.Height();
	si.nPage = original_rectangle.Height();
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE);

}


void ParamDlgScrollablePane::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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


void ParamDlgScrollablePane::OnSize(UINT nType, int cx, int cy)
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

}


BOOL ParamDlgScrollablePane::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
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
