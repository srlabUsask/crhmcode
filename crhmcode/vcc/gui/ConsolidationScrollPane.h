#pragma once

#include <afxwin.h>

#include "../resource.h"

class ConsolidationScrollPane : public CDialog
{
public:

	ConsolidationScrollPane(CWnd* pParent = NULL);
	
	~ConsolidationScrollPane();

private:
	/**
	* Defines the resource assoicated with this class.
	*/
	enum { IDD = CONSOLIDATION_SCROLL_PANE };

	/**
	* Connect data layer to the view.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	* Initalize the dialog
	*/
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};

