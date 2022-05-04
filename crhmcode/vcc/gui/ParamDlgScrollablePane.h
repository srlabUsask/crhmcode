#pragma once
#include <afxwin.h>
#include "../resource.h"

class ParamDlgScrollablePane : public CDialog
{

public:
	ParamDlgScrollablePane(CWnd* pParent = NULL);   // standard constructor

	// dialog size as you see in the resource view (original size)
	CRect	m_rcOriginalRect;

	// actual scroll position
	int		m_nScrollPos;

	// actual dialog height
	int		m_nCurHeight;


	enum { IDD = PARAMETERS_DLG_SCROLL_PANE};
	



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:


	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	DECLARE_MESSAGE_MAP()
public:

};