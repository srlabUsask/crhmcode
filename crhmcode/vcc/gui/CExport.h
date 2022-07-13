#pragma once

#include "../stdafx.h"
#include "afxdialogex.h"
#include <string>
#include <list>

#include "CRHM_GUI.h"
#include "../../src/core/CRHMmain.h"
#include "../../src/core/ClassVar.h"

// CExport dialog

class CExport : public CDialog
{
	DECLARE_DYNAMIC(CExport)

public:
	CExport(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CExport();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EXPORT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	long nextLine{ 0 };

	CListBox choicesListBox;
	CListBox selectedListBox;
	CButton previewMoreButton;
	CComboBox formatToggle;
	CListBox previewEditBox;

	BOOL OnInitDialog();

	afx_msg void OnChoicesSelectionChange();
	afx_msg void OnSelectedSelectionChange();
	afx_msg void OnPreviewMorePressed();

	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	afx_msg void OnExit();


	std::vector<int> * getExportIndex();
	void exportToFile(std::string filePath, std::vector<TSeries*>* data);

	std::vector<TSeries*>* PrepareDataForExport();

};
