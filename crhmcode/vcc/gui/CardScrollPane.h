#pragma once

#include <list>

#include "../resource.h"
#include "../../src/core/ClassPar.h"
#include "ParamDlgCard.h"
#include "ParamDlgCardShared.h"
#include "ConsolidateParamCard.h"
#include "FontsContainer.h"

class ParamDlgCard;

/**
* Resizable pane that holds parameter cards
*/
class CardScrollPane : public CDialog
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
	* Tracks where to place the top of the next card to be rendered
	*/
	int next_card;

	/**
	* Renders a parameter card. 
	* 
	* @param data - std::list<std::pair<std::string, ClassPar*>>::iterator the data for the parameter card to render.
	* @return bool - true if the card is created correctly false otherwise.
	*/
	bool AddCard(std::list<std::pair<std::string, ClassPar*>>::iterator data);

	/**
	* Removes all of the rendered parameter cards.
	*/
	void RemoveAllCards();

	/**
	* Calculate the location to place the next parameter card.
	* 
	* @param rectangle - CRect* a reference to the CRect object to set to the location where to place the card.
	* @param numRows - int the number of rows the incoming card needs to display all of its values.
	* @param numCols - int the number of columns the incoing card needs to display all of its values
	*/
	void CalculateCardLocation(CRect* rectangle, int numRows, int numCols);

	/**
	* Method called when the window is resized. Updates scroll info
	*/
	void ResizeWindow();

	/**
	* Resizes the cards in the scroll pane to fit horizontaly when the size of the window changes.
	*/
	void ResizeCards();

	/**
	* Handles the receiving of a UWM_MAKE_LOCAL message
	*
	* Passes the message up to the ParametersDlg
	* @param wParam - WPARAM pointer to the shared parameter to be made local
	* @param lParam - LPARAM pointer to the shared parameter to be made local
	*/
	afx_msg LRESULT OnMakeLocalMsg(WPARAM wParam, LPARAM lParam);

	/**
	* Handles the receiving of a UWM_USE_FOR_ALL message
	*
	* Passes the message up to the ConsolidateParamDlg
	* @param wParam - WPARAM pointer to the shared parameter to be used for all parameters with that name
	* @param lParam - LPARAM pointer to the shared parameter to be used for all parameters with that name
	*/
	afx_msg	LRESULT OnUseForAllMsg(WPARAM wParam, LPARAM lParam);

public:

	/**
	* Standard constructor
	*/
	CardScrollPane(CWnd* pParent = NULL);

	/**
	* deconstructor
	*/
	~CardScrollPane();

	/**
	* Sets the rendered parameter cards to the passed in list of parameters.
	* 
	* @param parametersList - std::list<std::pair<std::string, ClassPar*>>* list of parameters to render.
	*/
	void SetParameterCards(std::list<std::pair<std::string, ClassPar*>>* parametersList);

	/**
	* Calls the ResetGrid method on all of the parameter cards.
	*/
	void ResetAllCards();

	/*
	* Calls the SaveCard method on all of the parameter cards.
	*/
	void SaveAllCards();

	

	/**
	* Reference to the structure that contains the font pointers to be used in parameter cards
	*/
	FontsContainer* fonts;

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