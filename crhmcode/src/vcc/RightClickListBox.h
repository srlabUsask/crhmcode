#pragma once
#include <afxwin.h>
#include "resource.h"
class RightClickListBox :
    public CListBox
{
public:
    UINT getMessageCode();
    void setMessageCode(UINT code);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
    UINT messageCode;
};

