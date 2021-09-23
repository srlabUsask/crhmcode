#include "RightClickListBox.h"
BEGIN_MESSAGE_MAP(RightClickListBox, CListBox)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

UINT RightClickListBox::getMessageCode()
{
	return this->messageCode;
}

void RightClickListBox::setMessageCode(UINT code)
{
	this->messageCode = code;
}

void RightClickListBox::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->SendMessage(this->messageCode, nFlags, 0);

	CListBox::OnRButtonDown(nFlags, point);
}
