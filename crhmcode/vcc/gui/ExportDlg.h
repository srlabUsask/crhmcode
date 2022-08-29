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

#include "../stdafx.h"

#include <string>
#include <list>

#include "CRHM_GUI.h"
#include "../../src/core/CRHMmain.h"
#include "../../src/core/ClassVar.h"

// CExport dialog

class ExportDlg : public CDialog
{
	DECLARE_DYNAMIC(ExportDlg)

	DECLARE_MESSAGE_MAP()

public:

	/**
	* Standard constructor 
	*/
	ExportDlg(CWnd* pParent = nullptr);

	/**
	* Standard deconstructor
	*/
	virtual ~ExportDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EXPORT_DLG };
#endif

protected:

	/**
	* Performs data exchange to connect dialog controls to member variables.
	*/
	virtual void DoDataExchange(CDataExchange* pDX);

private:

	/**
	* List box for all of the outputs from the model that could be selected for export.
	*/
	CListBox outputs_list_box;
	
	/**
	* List box for all of the selected outputs from the model that are to be exported.
	*/
	CListBox selected_list_box;
	
	/**
	* List box used to display the preview of the export output
	*/
	CListBox preview_list_box;

	/**
	* Button that when clicked will output a preview of the export to previewEditBox
	*/
	CButton preview_button;
	
	/**
	* Drop down list box that contains the vairous formats the output can be exported in.
	* 
	* Choices are:
	* Standard - Tab delimited columns with the first row detailing the output names 
	*     and the second row contains the units
	* OBS - Observation file .obs format. Creates an .obs file that can be used by CRHM.
	* STD w/ MS dates - Standard format but with dates in the Microsoft decimal format
	* STD w/ YYYYMMDD dates - Standard format but with dates in YYYY MM DD hh mm format
	*/
	CComboBox format_toggle;

	/**
	* Tracks what is the next line that should be sent to the preview box.
	* 1000 lines are sent at a time. 
	*/
	long next_line;

	/**
	* Initalizes the CExport dialog setting the control elements to their inital state.
	* 
	* @return BOOL - returns true which indicates that windows will handle which control recives control
	*/
	BOOL OnInitDialog();

	/**
	*  Handler for when the selection in the outputs list box changes.
	* 
	*  Adds the selected outputs to the selected list box.
	* 
	*  Also resets next_line to 0.
	*/
	afx_msg void OnOutputsSelectionChange();
	
	/**
	* Handler for when the selection in the selected list box changes.
	* 
	* Removes the selected outputs from the selected list box.
	* 
	* Also resets next_line to 0.
	*/
	afx_msg void OnSelectedSelectionChange();
	
	/**
	* Handler for when the preview button is pressed.
	* 
	* Causes a preview of the export to be output to the preview list box
	*/
	afx_msg void OnPreviewPressed();

	/**
	* Handler for when the file->save menu item clicked.
	* 
	* Saves the selected output to the default output file.
	*/
	afx_msg void OnSave();
	
	/**
	* Handler for when the file->save_as menu item is clicked.
	* 
	* Saves the selected output to a file specified by the user.
	*/
	afx_msg void OnSaveAs();
	
	/**
	* Handler for when the file->exit menu item is clicked.
	* 
	* Closes the Export Dialog
	*/
	afx_msg void OnExit();

	/**
	* Creates a vector of TSeries that contain the data that will be output. Creates a series for each 
	*     output in the selected list box and fills in data so they have all the same number of points.
	* 
	* @return std::vector<TSeries*>* pointer to a vector of TSeries that contain the data to be exported. 
	*     the vector and TSeries within are dynamicly allocated and need to be deleted after use.
	*/
	std::vector<TSeries*>* PrepareDataForExport();

	/**
	* Saves to the passed in file the export data found in the passed in data series.
	* 
	* @param filePath std::string - string path to the file to save the output in.
	* @param data std::vector<TSeries*>* pointer to a vector of TSeries* that contain the data to be output.
	*/
	void exportToFile(std::string filePath, std::vector<TSeries*>* data);

	bool IsValidSuffix(std::string suffix);
};
