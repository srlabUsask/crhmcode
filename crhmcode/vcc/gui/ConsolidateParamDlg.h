#pragma once
#include <afxwin.h>
#include <afxdialogex.h>

#include <map>
#include <list>
#include <string>

#include "../resource.h"
#include "../../src/core/ClassPar.h"
#include "CardScrollPane.h"


class ConsolidateParamDlg : public CDialogEx
{

	DECLARE_DYNAMIC(ConsolidateParamDlg)

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CONSOLIDATE_PARAM_DLG };
#endif

public:

	/**
	* Constructor
	* 
	* @param pParent - CWnd* pointer to parent window. Optional.
	*/
	ConsolidateParamDlg(std::map<std::string, std::list<ClassPar*>*>* candidates, CWnd* pParent = nullptr);
	
	/**
	* Deconstructor 
	*/
	~ConsolidateParamDlg();

private:

	/**
	* Map of parameter names to a list of parameter objects that have differing values.
	*/
	std::map<std::string, std::list<ClassPar*>*> candidates;

	/**
	* List box containing the candidate parameters for consolidation
	*/
	CListBox candidates_list_box;

	/**
	* Scroll pane that holds the parameter cards
	*/
	CardScrollPane * scrollPane;

	/**
	* Performs data exchange to properly connect graphical elements to the model.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Initalizes the dialog elements after creating the dialog.
	*/
	virtual BOOL OnInitDialog();

	/**
	* Sets the inital contents of the candidates list box based on the passed in map.
	*/
	void InitalizeCandidatesListBox();

	/*
	* Handler when selecting a candidate parameter to consolidate.
	* 
	* When a parameter is selected the parameter version cards are created in the scroll pane.
	*/
	afx_msg void OnSelectCandidate();

	/**
	* Handles the receiving of a UWM_USE_FOR_ALL message
	*
	* Processes the passed parameter and sets all parameters with that name to have the same values.
	* 
	* @param wParam - WPARAM pointer to the shared parameter to be used for all parameters with that name
	* @param lParam - LPARAM pointer to the shared parameter to be used for all parameters with that name
	*/
	afx_msg LRESULT OnUseForAllMsg(WPARAM wParam, LPARAM lParam);

	/**
	* Declares handlers for messages dispached by the GUI
	*/
	DECLARE_MESSAGE_MAP()
};

