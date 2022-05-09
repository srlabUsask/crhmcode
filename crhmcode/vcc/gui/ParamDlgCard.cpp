#include "ParamDlgCard.h"


ParamDlgCard::ParamDlgCard(ClassPar * param, CWnd* pParent /*=NULL*/ )
	: CDialog(ParamDlgCard::IDD, pParent)
{
	Create(ParamDlgCard::IDD,pParent);
	this->scroll_position = 0;
	this->pane_height = 0;
	this->parameter = param;
}


void ParamDlgCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PARAM_HELP, this->param_label);
}


BEGIN_MESSAGE_MAP(ParamDlgCard, CDialog)
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


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
