#pragma once

#include <afxwin.h>
#include <string>

#include "../resource.h"
#include "../../src/core/ClassPar.h"
#include "ParamSetAllDlg.h"
#include "GridCell.h"
#include "FontsContainer.h"

/**
*  Displays the information for a parameter and allows it to be edited.
*/
class ParamDlgCard : public CDialog
{
private:
	/**
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = PARAMETERS_CARD };

	/**
	* Handles the set all button being clicked.
	* 
	* Opens a dialog to receive the value to set all of the cells to.
	*/
	afx_msg void OnSetAllButton();

	/**
	* Handles the Reset button being clicked.
	* 
	* Resets all of the cells in the grid to the values in the model.
	*/
	afx_msg void OnResetButton();

	/**
	* Handles the Save button being clicked. 
	* 
	* Saves all of the cells in the grid so that the model matches the cells.
	*/
	afx_msg void OnSaveButton();

public:
	/*
	* Standard constructor
	*/
	ParamDlgCard(ClassPar * param, FontsContainer * fonts, CWnd * pParent);

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
	virtual void InitalizeValues();

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

	/**
	* Displays the name of this parameter
	*/
	CEdit param_name;

	/**
	* Displays the help information for this parameter
	*/
	CEdit param_help;

	/**
	* Displays a label for the parameter units
	*/
	CEdit param_units_label;
	
	/**
	* Displays the units string for this parameter
	*/
	CEdit param_units;

	/**
	* Displays a label for max value
	*/
	CEdit param_max_label;

	/**
	* Displays the maximum value for this parameter
	*/
	CEdit param_max_value;

	/**
	* Displays a label for min value
	*/
	CEdit param_min_label;

	/**
	* Displays the minimum value for this parameter
	*/
	CEdit param_min_value;

	/**
	* Displays a label for parameter default value
	*/
	CEdit param_default_label;

	/**
	* Displays the default label for this parameter
	*/
	CEdit param_default_value;

	/**
	* The first column label for the value grid
	*/
	CEdit param_col;

	/**
	* The first row lable for the value grid
	*/
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
	* Reference to a 120 point font
	*/
	CFont* pointFont120;

	/**
	* Reference to a 100 point font
	*/
	CFont* pointFont100;

	/**
	* Reference to a 80 point font
	*/
	CFont* pointFont80;

	/**
	* Reference to a 60 point font
	*/
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