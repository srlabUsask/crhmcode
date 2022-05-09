#pragma once

#include <afxwin.h>
#include <list>
#include <string>


#include "../resource.h"
#include "../../src/core/ClassPar.h"
#include "ParamDlgCard.h"

class ParamDlgScrollablePane : public CDialog
{
private:
	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_DLG_SCROLL_PANE };

	/*
	* CRect object representing the original size of the inserted pane.
	*/
	CRect original_rectangle;

	CRect current_rectangle;

	/**
	* Tracks the scroll position of the pane.
	*/
	int	scroll_position;

	/**
	* Tracks the actual height of the pane
	*/
	int	pane_height;

	std::vector<ParamDlgCard*> cards;

	void CalculateCardLocation(CRect*);

	void ResizeWindow();

public:
	/*
	* Standard constructor
	*/
	ParamDlgScrollablePane(CWnd* pParent = NULL);

	void UpdateParametersCards(std::list<std::pair<std::string, ClassPar*>>* parametersList);

protected:

	/**
	* Connect data layer to the view.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Initalize the dialog
	*/
	virtual BOOL OnInitDialog();

	void RemoveAllCards();

	void AddCard(std::list<std::pair<std::string, ClassPar*>>::iterator data);


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