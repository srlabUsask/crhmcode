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

//Visual studio includes
#include "../stdafx.h"
#include "afxdialogex.h"
//Standard library includes
#include <vector>
#include <string>
//Source includes
#include "CRHM_GUI.h"
#include "../../src/core/GlobalDll.h"
#include "Module.h"
#include "FileDialog.h"


class MacroEntryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MacroEntryDlg)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	MacroEntryDlg(CWnd* pParent = nullptr);
	
	virtual ~MacroEntryDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = MacroEntry_DLG };
#endif

private:

	CEdit macroEditBox; /**< Edit control for the macro section. */

	/**
	* Holds the modules in the group being created. 
	*/
	std::vector<std::string>* ModuleList{ NULL };

	std::vector<std::pair<std::string, Module*>>* MacroList{ NULL };   // macros in project file
	std::vector<std::pair<std::string, Module*>>* DefinedList{ NULL }; // macros already defined	
	std::vector<std::string>* ParaList{ NULL };    // defined parameters
	std::vector<std::string>* AKAList{ NULL };     // AKA defines

	Module GlobalModule;

	FileDialog* macrofile{ NULL };
	
	virtual BOOL OnInitDialog();

	//Buttons
	afx_msg void OnMacroSaveChanges();

	afx_msg void OnMacroCancelChanges();

	//Menu Items
	afx_msg void OnMacroFileOpen();

	afx_msg void OnMacroFileSave();

	afx_msg void OnMacroFileSaveAs();

	afx_msg void OnMacroFileCreateGroup();

	afx_msg void OnMacroFileClear();

	afx_msg void OnMacroFileExit();
	
	void DoSave();

	void SaveAsClick();

	void AddStringsToEditBox(std::vector<std::string>* tstr);

	void AddStringsToEditBox(std::string tstr);
	
	std::vector<std::string>* GetLinesFromEditBox();
	
	std::vector<std::string>* GetSelectedLinesFromEditBox();

	void CreateGroupClick();

	void AddGroup(int ii);

	void AddSupport(Module* ThisModule);

};
