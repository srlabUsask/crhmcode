#include "ConsolidationScrollPane.h"


BEGIN_MESSAGE_MAP(ConsolidationScrollPane, CDialog)
END_MESSAGE_MAP()


ConsolidationScrollPane::ConsolidationScrollPane(CWnd* pParent)
{
	Create(ConsolidationScrollPane::IDD, pParent);
	this->pane_height = 0;
	this->scroll_position = 0;
}


ConsolidationScrollPane::~ConsolidationScrollPane()
{
}


void ConsolidationScrollPane::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BOOL ConsolidationScrollPane::OnInitDialog()
{
	CDialog::OnInitDialog();

	return true;
}


void ConsolidationScrollPane::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	int nMaxPos = current_rectangle.Height() - pane_height;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (scroll_position >= nMaxPos)
			return;

		nDelta = min(max(nMaxPos / 20, 5), nMaxPos - scroll_position);
		break;

	case SB_LINEUP:
		if (scroll_position <= 0)
			return;
		nDelta = -min(max(nMaxPos / 20, 5), scroll_position);
		break;
	case SB_PAGEDOWN:
		if (scroll_position >= nMaxPos)
			return;
		nDelta = min(max(nMaxPos / 10, 5), nMaxPos - scroll_position);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nDelta = (int)nPos - scroll_position;
		break;

	case SB_PAGEUP:
		if (scroll_position <= 0)
			return;
		nDelta = -min(max(nMaxPos / 10, 5), scroll_position);
		break;

	default:
		return;
	}
	scroll_position += nDelta;
	SetScrollPos(SB_VERT, scroll_position, TRUE);
	ScrollWindow(0, -nDelta);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL ConsolidationScrollPane::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nMaxPos = current_rectangle.Height() - pane_height;

	if (zDelta < 0)
	{
		if (scroll_position < nMaxPos)
		{
			zDelta = min(max(nMaxPos / 20, 5), nMaxPos - scroll_position);

			scroll_position += zDelta;
			SetScrollPos(SB_VERT, scroll_position, TRUE);
			ScrollWindow(0, -zDelta);
		}
	}
	else
	{
		if (scroll_position > 0)
		{
			zDelta = -min(max(nMaxPos / 20, 5), scroll_position);

			scroll_position += zDelta;
			SetScrollPos(SB_VERT, scroll_position, TRUE);
			ScrollWindow(0, -zDelta);
		}
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


void ConsolidationScrollPane::OnSize(UINT nType, int cx, int cy)
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