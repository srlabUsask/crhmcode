#pragma once

#include <afxwin.h>
#include <string>

#include "../resource.h"
#include "../../src/core/ClassPar.h"


class ParamDlgCard : public CDialog
{
private:
	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_CARD };

	/*
	* CRect object representing the original size of the inserted pane.
	*/
	CRect original_rectangle;

	/**
	* Tracks the scroll position of the pane.
	*/
	int	scroll_position;

	/**
	* Tracks the actual height of the pane
	*/
	int	pane_height;

	ClassPar * parameter;

public:
	/*
	* Standard constructor
	*/
	ParamDlgCard(ClassPar * param, CWnd* pParent = NULL );

	CEdit param_label;

	void InitalizeValues();

protected:

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