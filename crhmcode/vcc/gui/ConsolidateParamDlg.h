#pragma once
#include <afxwin.h>
#include <afxdialogex.h>

#include <map>
#include <list>
#include <string>

#include "../resource.h"
#include "../../src/core/ClassPar.h"


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

	std::map<std::string, std::list<ClassPar*>*> candidates;

	/**
	* Declares handlers for messages dispached by the GUI
	*/
	DECLARE_MESSAGE_MAP()
};

