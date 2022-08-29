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
#pragma once
#include <afxwin.h>
#include <string>

#include "../src/core/GlobalDll.h"
#include "../src/core/ClassMacro.h"
#include "resource.h"


class HierarchyDlg : public CDialog
{
	DECLARE_DYNAMIC(HierarchyDlg)

public:
	HierarchyDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~HierarchyDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_HIERARCHY_DLG};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CListBox hierarchyCheck;
	CListBox hierarchyList;

	BOOL OnInitDialog();

	void Hierarchy1Click();
	void HierarchyList();
	void Expand_Grp_to_OurModuleList(std::string moduleName, ClassModule* module);
	std::pair<std::string, ClassModule*> * findvar(std::string who, std::string what, bool& Self);
	std::pair<std::string, ClassModule*> * findstatvar(std::string who, std::string what, bool& Self);
};

