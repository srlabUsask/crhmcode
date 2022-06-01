#pragma once
#include <afxwin.h>

#include "ParamDlgScrollablePane.h"

#include "../../src/core/CRHMmain.h"
#include "../../src/core/ClassMacro.h"


class ParametersDlg : public CDialogEx
{

	DECLARE_DYNAMIC(ParametersDlg)

public:
	/**
	* Standard constructor 
	*/
	ParametersDlg(CWnd* pParent = nullptr);
	
	/**
	* Standard deconstructor
	*/
	virtual ~ParametersDlg();

private:
	/**
	* List box that contains a list of the modules used in the loaded model.
	*/
	CListBox modules_list_box;

	/**
	* List box that contains a list of parameters. 
	*
	* The list changes based on the selection in the modules_list_box 
	*/
	CListBox parameters_list_box;

	/**
	* Scrollable pane that contains the individual parameter cards.
	*/
	ParamDlgScrollablePane* prameters_scroll_pane;

	/**
	* Handler for when the selection in the modules_list_box changes.
	*
	* Sets the parameters_list_box to contain all the parameters in the selected module.
	*/
	afx_msg void OnSelectModule();

	/**
	* Handler for when the selection in the parameters_list_box changes.
	* 
	* Dispaches a call to create the appropreate parameter cards.
	*/
	afx_msg void OnSelectParam();

	/**
	* Handler for when the Toggle Basic button is pressed.
	*
	* Will switch the selected/unselected state of all basic parameters in the Parameters List Box.
	*/
	afx_msg void OnToggleBasic();

	/**
	* Handler for when the Toggle Advance button is pressed.
	*
	* Will switch the selected/unselected state of all advance Parameters in the Parameters List Box.
	*/
	afx_msg void OnToggleAdvance();

	/**
	* Handler for when the Toggle Private button is pressed.
	*
	* Will switch the selected/unselected state of all private Parameters in the Parameters List Box.
	*/
	afx_msg void OnTogglePrivate();

	/**
	* Handler for when the Toggle All button is pressed.
	*
	* Will switch the selected/unselected state of all Parameters in the Parameters List Box.
	*/
	afx_msg void OnToggleAll();

	/**
	* Handler for when the Reset All button is pressed. 
	* 
	* Calls the reset method on all active parameter cards.
	*/
	afx_msg void OnResetAll();

	/**
	* Handler for when the Save All button is pressed.
	* 
	* Calls the save method on all active parameter cards.
	*/
	afx_msg void OnSaveAll();

	/**
	* Method that triggers when the window is resized
	*/
	afx_msg void OnSize(UINT nType, int cx, int cy);

	/**
	* Helper method used to initalize the values in the modules list box during dialog initalization.
	*
	* @param main CRHMmain* reference to the main CRHM model object. 
	*/
	void initalizeModulesListBox(CRHMmain * main);

	/**
	* Comparison function for sorting a list of modules indexed by string alphabeticaly ignoring case.
	*
	* Used as an argument to std::list.sort()
	*
	* @param item_a std::pair<std::string, ClassModule*> item to make up the left side of the comparison.
	* @param item_b std::pair<std::string, ClassModule*> item to make up the right side of the comparison.
	* @returns true if item_a is before item_b and false otherwise. 
	*/
	static BOOL compareModulesAlphabeticalyNoCase(std::pair<std::string, ClassModule*> item_a, std::pair<std::string, ClassModule*> item_b);

	/**
	* Comparison function for sorting a list of parameters indexed by string alphabeticaly ignoring case.
	*
	* Used as an argument to std::list.sort()
	*
	* @param item_a std::pair<std::string, ClassPar*> item to make up the left side of the comparison.
	* @param item_b std::pair<std::string, ClassPar*> item to make up the right side of the comparison.
	* @returns true if item_a is before item_b and false otherwise.
	*/
	static BOOL compareParametersAlphabeticalyNoCase(std::pair<std::string, ClassPar*> item_a, std::pair<std::string, ClassPar*> item_b);

	/**
	* Handles the receiving of a UWM_MAKE_LOCAL message 
	* 
	* Will alter the passed parameter to make it local instead of shared.
	* @param wParam - WPARAM pointer to the shared parameter to be made local
	* @param lParam - LPARAM pointer to the shared parameter to be made local
	*/
	afx_msg LRESULT OnMakeLocalMsg(WPARAM wParam, LPARAM lParam);

	/**
	* Handles the receiving of a UWM_UNSELECT_PARAMS message
	* 
	* Will remove the list of parameters passed in from being selected in the parameters list box
	* @param wParam - WPARAM pointer to a list of parameters to unselect
	* @param lParam - LPARAM pointer to a list of parameters to unselect (unused)
	*/
	afx_msg LRESULT ParametersDlg::OnUnselectParamsMsg(WPARAM wParam, LPARAM lParam);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = PARAMETERS_DLG };
#endif

protected:
	/**
	* Performs data exchange to properly connect graphical elements to the model.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Initalizes the dialog elements after creating the dialog.
	*/
	virtual BOOL OnInitDialog();

	/**
	* Declares handlers for messages dispached by the GUI
	*/
	DECLARE_MESSAGE_MAP()
};
