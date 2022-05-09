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
	/**
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_DLG_SCROLL_PANE };

	/**
	* CRect object representing the original size of the inserted pane.
	*/
	CRect original_rectangle;

	/**
	* CRect object representing the current size of the pane.
	*/
	CRect current_rectangle;

	/**
	* Vector of ParamDlgCard references that holds the currently rendered parameter cards.
	*/
	std::vector<ParamDlgCard*> cards;

	/**
	* Tracks the scroll position of the pane.
	*/
	int	scroll_position;

	/**
	* Tracks the actual height of the pane
	*/
	int	pane_height;

	/**
	* Renders a parameter card. 
	* 
	* @param data - std::list<std::pair<std::string, ClassPar*>>::iterator the data for the parameter card to render.
	*/
	void AddCard(std::list<std::pair<std::string, ClassPar*>>::iterator data);

	/**
	* Removes all of the rendered parameter cards.
	*/
	void RemoveAllCards();

	/**
	* Calculate the location to place the next parameter card.
	* 
	* @param rectangle - CRect* a reference to the CRect object to set to the location where to place the card.
	*/
	void CalculateCardLocation(CRect* rectangle);

	void ResizeWindow();

public:
	/**
	* Standard constructor
	*/
	ParamDlgScrollablePane(CWnd* pParent = NULL);

	/**
	* Sets the rendered parameter cards to the passed in list of parameters.
	* 
	* @param parametersList - std::list<std::pair<std::string, ClassPar*>>* list of parameters to render.
	*/
	void SetParameterCards(std::list<std::pair<std::string, ClassPar*>>* parametersList);

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