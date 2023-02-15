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
#include "../stdafx.h"

#include "CRHM_GUI.h"
#include "../../src/core/CRHMmain.h"
#include "../../src/core/MacroUnit.h"
#include "../RightClickListBox.h"

#pragma once

class StringGrid;

// CConstruct dialog

class ConstructDlg : public CDialog
{
	DECLARE_DYNAMIC(ConstructDlg)

public:
	ConstructDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConstructDlg();
	
	void AKAselectiveDelete();
	bool ModifyBuild = false;
	void SetSuffix(long Row);

	/**
	* Displays the infromation about a module in the two build panels.
	* 
	* @param moduleName std::string - Name of the module to be displayed.
	* @param module ClassModule* - pointer to the module to be displayed.
	* @param LBox1 bool - Set to true if called from the available 
	*	modules and false if called from the selected modules
	*/
	void DisplayModule(std::string moduleName, ClassModule* module, bool LBox1);

	bool Variation_Decide(int Variation_set, long Variation);
	bool Visible_Decide(long Variation);
	bool Not_Obs(string Mod, string Var);

	/**
	* Places the string in the Construct Console
	* 
	* @param str std::string text to place on the console.
	*/
	void AddLineToConstructConsole(std::string str);
	




// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CONSTRUCT_DLG };
#endif
private:

	RightClickListBox listbox_available_modules;
	RightClickListBox listbox_selected_modules;

	CButton module_filter_basic;
	CButton module_filter_macro;
	CButton module_filter_advanced;
	CButton module_filter_support;
	CButton module_filter_custom;
	CButton module_filter_prototype;
	CButton module_filter_obsolete;

	CSpinButtonCtrl max_HRU_spin;
	CSpinButtonCtrl max_layer_spin;

	afx_msg void OnClkModuleFilterBasic();
	afx_msg void OnClkModuleFilterMacro();
	afx_msg void OnClkModuleFilterAdvanced();
	afx_msg void OnClkModuleFilterSupport();
	afx_msg void OnClkModuleFilterCustom();
	afx_msg void OnClkModuleFilterPrototype();
	afx_msg void OnClkModuleFilterObsolete();

	afx_msg void OnSelChangeAllModsListBox();
	afx_msg LRESULT OpenAvailableModsCtxMenu(WPARAM, LPARAM);
	afx_msg void OnSelChangeSelModsListBox();
	afx_msg LRESULT OpenSelectedModsCtxMenu(WPARAM, LPARAM);

	afx_msg void OnClkBuildButton();
	afx_msg void OnClkCancelButton();
	afx_msg void OnClkCheckButton();


	/**
	* Sets the contents for the available modules list box based on the state of the filter checkboxes.
	* Checks the state of the filter checkboxes and adds each module that fits both to the
	*    AvailableModules vector and to the list box display.
	*/
	void UpdateAvailableModules();

	/**
	* Checks if a module represented by a given string is in the selected modules list box.
	*
	* @param cstr CString - the string of the module to look for in the selected modules.
	* @returns bool - true if the passed in module name is already selected false otherwise.
	*/
	bool ModuleIsSelected(CString cstr);

	/**
	* Adds the string Class Module pair passed in to the vector of available modules.
	*
	* @param str std::string name of the module to add.
	* @param obj ClassModule* pointer to the module to add.
	*/
	void AddToAvailableModules(std::string str, ClassModule* obj);

	void AddAvailableModsToSelected();

	void RemoveModulesFromSelected();

	/**
	* Adds and removes items from the selected modules list box such that it 
	* becomes synced with the SelectedModules vector. 
	*/
	void UpdateSelectedModulesListBox();

	/**
	* Changes the 
	*/
	void SetNextVariation();
	void SetPrevVariation();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedButton8();
	void FormActivate();
	void SetSuffix(std::list<std::pair<std::string, ClassModule*>>::iterator pos);
	
	std::vector<std::pair<std::string, ClassModule *>> * AvailableModules = new std::vector<std::pair<std::string, ClassModule*>>(); //manishankar ListBox1 has been renamed as AllModules.
	std::vector<std::pair<std::string, ClassModule *>> * SelectedModules = new std::vector<std::pair<std::string, ClassModule*>>(); //manishankar ListBox2 has been renamed as SelectedModules.
	bool Execute{ FALSE };
	std::vector<std::pair<std::string, int>> * List{ NULL };
	std::vector<std::string> * ListAll{ NULL };
	std::vector<std::pair<std::string, int>> * ListUsed{ NULL };
	std::vector<std::pair<std::string, int>> * ListPuts{ NULL };
	std::vector<std::string> * ListStats{ NULL };
	std::vector<std::pair<std::string, ClassPar *>> * ParaList{ NULL };
	Mapstr2 MapAKACopy;
	Mapstr2 MapAKAVar;

	CEdit Memo1;

	StringGrid * StringGrid1{ NULL };
	
	CListCtrl listcontrol;
	long CheckModel();
	long Best_Match(string Var, std::vector<std::pair<std::string, int>>* List);
	long Best_Match(string Var, std::vector<std::string>* List);
	string StringOfChar(char c, int n);
	long BuildClick();
	void SaveBuildParameters();
	void RemoveSharedParams();
	void RemoveParameter();
	long FormatMax(long M);
	void ReadBuildParameters();
	void LoadAllModules();
	void RemoveSelectedModule();
	void AddToSelectedModules(string str, ClassModule * obj);
	afx_msg void OnBnClickedButton1();
};

class StringGrid
{
public:
	string Cells[500][500];
	int ColCount = 0;
	int RowCount = 0;
	int FixedRows = 0;
	string Cols[500];
};