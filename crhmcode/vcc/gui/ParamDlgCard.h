#pragma once

#include <afxwin.h>
#include <string>

#include "../resource.h"
#include "../../src/core/ClassPar.h"
#include "ParamSetAllDlg.h"


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

	/**
	* Holds the parameter associated with this card 
	*/
	ClassPar * parameter;

	/**
	* Holders for fonts used on the card
	*/
	CFont * pointFont120;
	CFont * pointFont100;
	CFont * pointFont80;
	CFont * pointFont60;

	/**
	* Vector that holds the CEdit references for the row label items
	*/
	std::vector<CEdit*> rowLabels;

	/**
	* Vector that holds the CEdit references for the column header items
	*/
	std::vector<CEdit*> colHearders;

	/**
	* Holds the representation of the valueGrid that is displayed
	*/
	std::vector<std::vector<CEdit*>> valueGrid;

	/**
	* Handles the set all button being clicked.
	* 
	* Opens a dialog to receive the value to set all of the cells to.
	*/
	void OnSetAllButton();

	/**
	* Handles the Reset button being clicked.
	* 
	* Resets all of the cells in the grid to the values in the model.
	*/
	void OnResetButton();

	/**
	* Handles the Save button being clicked. 
	* 
	* Saves all of the cells in the grid so that the model matches the cells.
	*/
	void OnSaveButton();


public:
	/*
	* Standard constructor
	*/
	ParamDlgCard(ClassPar * param, CWnd* pParent = NULL );

	/*
	* Deconstructor
	*/
	~ParamDlgCard();

	/**
	* Initalizes the help information for the parameter card
	*/
	void InitalizeValues();

	/**
	* Renders the value grid for the parameter
	*/
	void RenderGrid();

	/**
	* Removes all of the items created to render the grid.
	*/
	void RemoveGrid();

	/*
	* Sets all of the cells in the grid to the value specifed.
	* 
	* @param valueString - std::string the value to set all of the cells to.
	*/
	void SetAll(std::string valueString);

	/**
	* Calls the OnResetButton method reseting the grid to the values in the model.
	*/
	void ResetGrid();

	/**
	* Calls the OnSaveButton method saving the state in the grid to the model
	*/
	void SaveCard();

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

	/**
	* Overrides OnOK to prevent Enter Key press from closing the card
	*/
	void OnOK();

	/**
	* Overrides OnCancel to prevent esc key press from closing the card
	*/
	void OnCancel();
	
	DECLARE_MESSAGE_MAP()

};