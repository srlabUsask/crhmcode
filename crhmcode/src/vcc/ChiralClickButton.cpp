#include "ChiralClickButton.h"
BEGIN_MESSAGE_MAP(ChiralClickButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

UINT ChiralClickButton::getMessageCodeLeft()
{
	return this->messageCodeLeft;
}

void ChiralClickButton::setMessageCodeLeft(UINT code)
{
	this->messageCodeLeft = code;
}

UINT ChiralClickButton::getMessageCodeRight()
{
	return this->messageCodeRight;
}

void ChiralClickButton::setMessageCodeRight(UINT code)
{
	this->messageCodeRight = code;
}

void ChiralClickButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->SendMessage(this->messageCodeLeft, nFlags, 0);

	CButton::OnRButtonDown(nFlags, point);
}

void ChiralClickButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	GetParent()->SendMessage(this->messageCodeRight, nFlags, 0);

	CButton::OnRButtonDown(nFlags, point);
}
