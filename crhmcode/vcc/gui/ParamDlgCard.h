#pragma once

#include <afxwin.h>
#include <string>

#include "../resource.h"
#include "../../src/core/ClassPar.h"
#include "ParamSetAllDlg.h"
#include "GridCell.h"



class ParamDlgScrollablePane;

class ParamDlgCard : public CDialog
{
private:
	/*
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_CARD };

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
	ParamDlgCard(ClassPar * param, CWnd * pParent);

	/**
	* Creates the dialog object and attaches it to this object.
	*
	* Must be called directly after the constructor.
	* @return bool - true if successful false otherwise
	*/
	virtual bool call_create(CWnd* pParent);

	/*
	* Deconstructor
	*/
	~ParamDlgCard();

	/**
	* Initalizes the help information for the parameter card
	*/
	void InitalizeValues();

	/**
	* Renders the value grid for the parameter.
	* 
	* @return bool - true on success false when an element fails to be created
	*/
	virtual bool RenderGrid();

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

	/**
	* Get the type of the parameter associated with this card.
	* 
	* @return TVar the type of the parameter this card is associated with.
	*/
	TVar GetParamType();

protected:

	CEdit param_name;
	CEdit param_units_label;
	CEdit param_max_label;
	CEdit param_min_label;
	CEdit param_default_label;
	CEdit param_units;
	CEdit param_min_value;
	CEdit param_max_value;
	CEdit param_default_value;
	CEdit param_col;
	CEdit param_help;
	CEdit param_row;

	/*
	* CRect object representing the original size of the card.
	*/
	CRect original_rectangle;

	/**
	* Tracks the scroll position of the pane.
	*/
	int	scroll_position;

	/**
	* Tracks the actual width of the pane
	*/
	int pane_width;

	/**
	* Holds the parameter associated with this card
	*/
	ClassPar* parameter;

	/**
	* Holders for fonts used on the card
	*/
	CFont* pointFont120;
	CFont* pointFont100;
	CFont* pointFont80;
	CFont* pointFont60;

	/**
	* Vector that holds the CEdit references for the row label items
	*/
	std::vector<CEdit*> rowLabels;

	/**
	* Vector that holds the CEdit references for the column header items
	*/
	std::vector<CEdit*> colHeaders;

	/**
	* Holds the representation of the valueGrid that is displayed
	*/
	std::vector<std::vector<CEdit*>> valueGrid;

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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

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