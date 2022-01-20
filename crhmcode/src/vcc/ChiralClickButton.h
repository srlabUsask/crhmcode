#pragma once
#include <afxwin.h>
#include "resource.h"
class ChiralClickButton :
    public CButton
{
public:
    UINT getMessageCodeLeft();
    void setMessageCodeLeft(UINT code);
    UINT getMessageCodeRight();
    void setMessageCodeRight(UINT code);

    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
    UINT messageCodeLeft{ 0 };
    UINT messageCodeRight{ 0 };
};