/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#include "CRHM_GUI.h"
#include "afxdialogex.h"
#include "../../src/core/CRHMmain.h"
#include "../../src/core/ClassModule.h"
#include "../../src/core/MacroUnit.h"

#pragma once


// CReport dialog

class CReport : public CDialog
{
	DECLARE_DYNAMIC(CReport)

public:
	CReport(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CReport();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = REPORT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:

	CListBox groupsListBox;
	CEdit extractedGroupText;
	CStatic staticText;

	virtual BOOL OnInitDialog();

	afx_msg void OnSave();
	afx_msg void OnExit();
	afx_msg void SelectGroup();



	//CStatic reportlabel;
	void ExtractGroupFile(ClassModule *thisModule);
	long Add_NHRU(string S, std::vector<std::string>* MacroModulesList);
	void AddMacroCode(string S, std::vector<std::string>* MacroModulesList, std::vector<std::string> * Memo1, long& MacroPos);
	

	string defaultprojectpath;
};
