#pragma once
#include <afxwin.h>
#include <afxdialogex.h>

#include "../resource.h"

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
	ConsolidateParamDlg(CWnd* pParent = nullptr);
	
	/**
	* Deconstructor 
	*/
	~ConsolidateParamDlg();

private:


	/**
	* Declares handlers for messages dispached by the GUI
	*/
	DECLARE_MESSAGE_MAP()
};

