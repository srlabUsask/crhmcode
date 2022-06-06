#pragma once

#include <afxwin.h>

#include "../resource.h"

class ConsolidationScrollPane : public CDialog
{
public:

	ConsolidationScrollPane(CWnd* pParent = NULL);
	
	~ConsolidationScrollPane();

private:

	/**
	* Object describing the dimensions of the scroll pane.
	*/
	CRect current_rectangle;

	/**
	* Tracks the actual height of the pane
	*/
	int	pane_height;

	/**
	* Tracks the scroll position of the pane.
	*/
	int	scroll_position;

	/**
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = CONSOLIDATION_SCROLL_PANE };

	/**
	* Connect data layer to the view.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Initalize the dialog
	*/
	virtual BOOL OnInitDialog();

	/**
	* Handles vertical scrolling by use of the scroll bar.
	*/
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	/**
	* Handles vertical scrolling by use of the scroll wheel.
	*/
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	/**
	* Handles resizing of the pane.
	*/
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

