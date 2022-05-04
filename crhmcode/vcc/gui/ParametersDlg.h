#pragma once
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

	ParamDlgScrollablePane* prameters_scroll_pane;

	/**
	* Handler for when the selection in the modules_list_box changes.
	*
	* Sets the parameters_list_box to contain all the parameters in the selected module.
	*/
	afx_msg void OnSelectModule();

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
