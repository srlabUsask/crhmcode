// Library includes
#include "../stdafx.h"
#include "afxdialogex.h"
#include "../tchart/CSeries.h"
#include "CTChart.h"
// Source includes
#include "../../src/core/CRHMmain.h"
#include "../../src/core/ClassCRHM.h"
#include "CRHM_GUI.h"
#include "CRHMAboutBox.h"
#include "MacroEntryDlg.h"
#include "FlowDiagramDlg.h"
#include "CReport.h"
#include "CConstruct.h"
#include "../RightClickListBox.h"
#include "../HierarchyDlg.h"
#include "CExport.h"
#include "../ChiralClickButton.h"

// Defines
#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

#pragma once
 
/**
* The main CRHM dialog window class
* CRHMmainDlg defines the main dialog window for the application. 
* This dialog handles the main menu and supports loading, saving, and running projects.
* It is a descendant of the CDialogEx class.  
*/
class CRHMmainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRHMmainDlg)	

public:

	CRHMmainDlg(CWnd* pParent = nullptr); /**< Standard constructor */
	virtual ~CRHMmainDlg(); /**< Standard destructor */


	/**
	* Constructor that takes in a project file name and runs that
	*	project after opening
	*
	* @param argumentfile std::string path to a project file.
	*/
	CRHMmainDlg(std::string argumentfile);

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CRHMmainDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	long Box1Disply{ 0 };
	long ObsFunct_Toggle = 0; /**< no display/Final/Trend values */
	long TBase{ 0 };
	long water_year_month = 10; /**< Specifies the month to signal end of water year. Default is October.*/

	std::string ProjectFileArgument = ""; /**< it takes the filename from the command line. */
	std::string defaultprojectname = "currentproject.prj";
	std::string defaultprojectpath = "currentproject.prj";
	std::string defaultobservationpath = "obs/Badlake73_76.obs";
	std::string TBases[5] = { "Daily", "Water_year", "Calendar_year", "Monthly_summary", "Summarize_all" };

	CMenu main_menu;

	/**
	* Drop down selector for observation functions
	* 
	* Options are:
	*	Observation
	*	Total
	*	Minimum
	*	Maximum
	*	Average
	* 
	* Control ID is ID_FUNCTION_DROP_DOWN
	*/
	CComboBox function_drop_down;

	/**
	* Drop down selector for timebase setting
	* 
	* Options are:
	*	Daily	
	*	Water Year
	*	Calendar Year
	*	Monthly
	*	All
	*	
	* 
	* Control ID is ID_TIMEBASE_DROP_DOWN
	*/
	CComboBox timebase_drop_down;

	/**
	* List box for all variables in the loaded project
	* List box that contains a string for each variable available
	*	for output in the currently loaded project.
	* 
	* The control ID is ID_ALL_VAR_LIST_BOX
	* The list box is defined in the resource file CRHMGUI.rc
	*/
	RightClickListBox listbox_all_variables;

	/**
	* List box for all variables that have been selected for output.
	* List box that contains a string for each variable to be output.
	*
	* The control ID is ID_SEL_VAR_LIST_BOX
	* The list box is defined in the resource file CRHMGUI.rc
	*/
	RightClickListBox listbox_sel_variables;

	/**
	* Listbox for all available observations.
	* List box that contains a string for each observation currently loaded.
	*
	* The control ID is ID_ALL_OBS_LIST_BOX
	* The list box is defined in the resource file "CRHMGUI.rc"
	*/
	RightClickListBox listbox_all_observations;

	/**
	* List box for selected observations.
	* List box that contains a string for each observation that is currently selected
	*	for output and display.
	*
	* The control ID is ID_SEL_OBS_LIST_BOX
	* The list box is defined in the resource file "CRHMGUI.rc"
	*/
	RightClickListBox listbox_sel_observations;

	/**
	* CTChart that controls the tchart plot.
	*/
	CTChart tchart;

	/**
	* Date picker for the start date of the simulation. 
	* 
	* Control ID is ID_START_DATE_PICKER
	* The control is defined in the resource file "CRhMGUI.rc"
	*/
	CDateTimeCtrl StartDatePicker;

	/**
	* Date picker for the end date of the simulation.
	*
	* Control ID is ID_END_DATE_PICKER
	* The control is defined in the resource file "CRhMGUI.rc"
	*/
	CDateTimeCtrl EndDatePicker;

	ChiralClickButton FlipTicks;


	/** 
	* The number of open observation files.
	*/
	int observationsFilesCount = 0; 

	/**
	* Vector that stores observation file names paired with a vector of strings of the names of the observations within.
	*/
	std::vector<std::pair<std::string, std::vector<std::string>*>>* observationsFiles{ NULL };

	/**
	* Map that assocates a control ID for a menu item with each open observation file.
	*/
	std::map<UINT, std::pair<std::string, std::string>>* openObsFiles; 

	/**
	* Initalizes the dialog elements after creating the dialog.
	*/
	virtual BOOL OnInitDialog();

	/**
	* Processes the command line arguments if the GUI version of CRHM is used as a command line program.
	* 
	* This feature is not reccomended as the gcc CLI is much more robust. 
	* Reccomend depricating this feature. 
	*/
	void ProcessCommandLineArgument();

	/**
	* Initalzies GUI components after loading a project. 
	* 
	* Also determines of auto run is enabled and runs the project if so.
	*/
	void loadGuiComponents();


	/**
	* Calls the declaration function on each selected module after a model is built.
	*/
	void InitModules();

	/**
	* Called at end of initModules. Purpose currently unknown. 
	*/
	void GetAllVariables();

	/**
	* Returns true if the variable and module use a variation.
	* 
	* @param Variation_set int value of variation_set member of a ClassVar
	* @param Variation long value of variation member of a ClassModule 
	*/
	bool Variation_Decide(int Variation_set, long Variation);

	/**
	* Returns name of the passed in variable with the group suffix appended. 
	* 
	* @param thisVar ClassVar* the variable to return the group suffix appened name of.
	*/
	std::string DeclObsName(ClassVar* thisVar);

	/**
	* Runs the simulation that has been set up.
	* The simulation is run in stages and after 
	*	each stage the GUI updates the plot as it runs
	*/
	void RunClickFunction();


	/**
	* Adds a series to the TChart plot.
	* 
	* @param series TSeries* a pointer to the series to add to the plot.
	*/
	void AddSeriesToTChart(TSeries* series);


	/**
	* 
	* @param thisVar ClassVar* pointer to the observation variable being added to the plot.
	* @param cdSeries TSeries* pointer to the series being added to the plot.
	* @param S 
	*/
	void AddObsPlot(ClassVar* thisVar, TSeries* cdSeries, std::string S, TFun Funct);

	/**
	* Sets the time on the date pickers.
	* 
	* @param startDate double windows OLE timestamp
	* @param endDate double windows OLE timestamp
	*/
	void SetTime(double startDate, double endDate);

	/**
	* Opens a project in the model.
	* 
	* @param filepath std::string path to the project file to open.
	* @param filename std::string name of the project file to open.
	*/
	void OpenProject(std::string filepath, std::string filename);

	/**
	* Saves, closes, and reopens the currently open project. 
	*/
	void ReopenProject();

	/**
	* Saves the currently open project.
	*/
	void SaveProject();

	/**
	* Closes the currently open project.
	*/
	void CloseProject();

	/**
	* Adds a plot point to a CSeries
	* 
	* @param series CSeries the seriese to add the plot point to.
	* @param xvalue double x value of the plot point to add.
	* @param yvalue double y value of the plot point to add. 
	*/
	void AddDataToSeries(CSeries series, double xvalue, double yvalue);

	/**
	* Opens an observation file.
	* 
	* @param obsfilepath std::string filepath to the observation file to open.
	*/
	void OpenObservation(std::string obsfilepath);


	/**
	* Adds an observation file to the list of open observation files and makes a menu item for it.
	* Creates a menu item for the given observation file and adds it to the menu. 
	*
	* @param filepath std::string path to the project file to open.
	* @param filename std::string name of the project file to open.
	*/
	void AddOpenObsFile(std::string filepath, std::string filename);

	// Start GUI update functions

	/**
	* Calls the updateOpenObsFileMenu and updateOpenStateFileMenu funcitons.
	*/
	void updateGuiMenuItems();

	/**
	* Updates the observation submenu based on the model.
	* Helper function that removes all submenu items from the OpenObsFileMenu and
	* resets it so that it contains the correct submenu items based on the state
	* in the model.
	*
	* Also resets the observations listbox and its selected items.
	*/
	void updateOpenObsFileMenu();

	/**
	* Updates the state file submenu items based on the model.
	*/
	void updateOpenStateFileMenu();

	/**
	* Updates the selected variables list box contents based on the state of the model.
	*/
	void updateSelectedVariablesListBox();

	/**
	* Updates the selected observation list box contents based on the state of the model.
	*/
	void updateSelectedObservationListBox();

	// End GUI update functions

	//Message handlers

	/**
	* Handler for clicking on project->Open
	* Uses a file open dialog to select a project file 
	*	and then opens the selected project file.
	*/
	afx_msg void OnFileOpen();

	/**
	* Handler for clicking on project->Save
	* 
	* Saves the currently loaded project. 
	*/
	afx_msg void OnFileSave();

	/**
	* Handler for clicking on project->Save As
	* 
	* Opens a file dialog allowing the user to choose a file location.
	*	Upon completion of the dialog saves the currently open project in that location.
	*/
	afx_msg void OnFileSaveAs();

	/**
	* Handler for clicking on project->Close
	* 
	* Closes the currently open project.
	*	This saves the project and closes the whole dialog and opens a new one.
	*/
	afx_msg void OnFileClose();

	/**
	* Handler for clicking on project->Extract Group
	* 
	* Opens the extract group modal window.
	*/
	afx_msg void OnExtractGroup();

	afx_msg void OnViewHierarchy();

	/**
	* Handler for clicking on project->Auto Run
	* 
	* Toggles the auto run status of the currently loaded project.
	*/
	afx_msg void OnAutoRun();

	/**
	* Handler for clicking on project->Auto Exit
	* 
	* Toggles the auto exit status of the currently loaded project. 
	*/
	afx_msg void OnAutoExit();

	/**
	* Handler for clicking on project->Exit
	*
	* this has been added by Manishankar for exiting the CRHM program.
	* All the functionalities while closing the project should be integrated
	*	(for example saving an unsaved project) and additionally the program 
	*	should exit at last.
	* 
	* Currently does not check if project needs to be saved.
	*/
	afx_msg void OnExit();

	afx_msg void OnLogAll();

	afx_msg void OnLogLast();

	/**
	* Handler for clicking on Observations->Open Observation
	* 
	* Opens a file selection dialog. 
	* Once complete the user selected observation file is opened. 
	* A menu item for the open file is also created. 
	*/
	afx_msg void OnOpenObservation();

	/**
	* Handler for clicking on an open observation file menu item.
	* 
	* Closes the clicked on observation file and removes the menu item.
	*/
	afx_msg void OnClickOnOpenFile(UINT nID);

	/**
	* Handler for clicking on Observations->Close All
	* 
	* Closes all of the open observation files. 
	*/
	afx_msg void OnCloseAllObservations();

	/**
	* Handler for clicking on Build->Construct
	* 
	* Opens the project construction dialog.
	*/
	afx_msg void OnBuildConstruct();

	/**
	* Handler for clicking on Build->Clear Modules
	* 
	* Removes all modules from the current projects and 
	*	removes both all variables and selected variables. 
	*/
	afx_msg void OnClearModules();

	/**
	* Handler for clicking on Build->Macro
	* 
	* Opens the macro construction dialog.
	*/
	afx_msg void OnBuildMacro();

	/**
	* Handler for clicking on State->Open Inital State
	* 
	* Opens a file dialog to select an inital state file.
	* Upon completion loads the inital state file and creates an menu item for it.
	*/
	afx_msg void OnClickOnOpenInitState();

	/**
	* Handler for clicking on an State->(open inital state file name).
	* 
	* Closes the inital state file.
	*/
	afx_msg void CloseOpenInitFile();

	/**
	* Handler for clicking on State->Save State.
	* 
	* Sets the flag to cause a final state file to be saved upon the completion of a simulation.
	* The file will be saved to the location listed in the Save To menu item.
	*/
	afx_msg void OnSaveState();

	/**
	* Handler for clicking on State->Save To.
	* 
	* Opens a file dialog that lets a user select a path that the 
	*	final state will be saved to upon the completion of a simulaiton. 
	*/
	afx_msg void OnSaveStateTo();

	/**
	* Handler for clicking on State->Save State As
	* 
	* Opens a file dialog that lets a user select a path to save the 
	*	final state file. Only available when a completed simulation is in memory.
	*/
	afx_msg void OnSaveStateAs();

	/**
	* Handler for clicking on Run->Run Model
	* 
	* Runs the simulation of the loaded project model.
	*/
	afx_msg void OnRunRunmodel();

	/**
	* Handler for clicking on Export menu item
	* 
	* Opens the export dialog
	*/
	afx_msg void OnExport();


	/**
	* Handler for clicking on Flow Diagram->Show Diagram
	* 
	* Shows the flow diagram associated with the loaded project. 
	*/
	afx_msg void OnFlowdiagramsShowdiagram();

	/**
	* Handler for clicking on Help->CRHMabout
	* 
	* Opens the help informaiton dialog.
	*/
	afx_msg void OnHelpAbout();

	/**
	* Handler for clicking on the "<" button for the HRU dimension selector.
	* 
	* Decreases the displayed HRU dimension by 1 with a mimimum value of 1.
	*/
	afx_msg void DecreaseHRUDimension();

	/**
	* Handles clicking on the ">" button for the HRU dimension selector.
	* 
	* Increases the displayed HRU dimension by 1 with a maximum value of Max HRU
	*/
	afx_msg void IncreaseHRUDimension();

	/**
	* Handler for clicking on the "<" button for the Obs dimension selector.
	*
	* Decreases the displayed Obs dimension by 1 with a mimimum value of 1.
	*/
	afx_msg void DecreaseObsDimension();

	/**
	* Handler for clicking on the ">" button for the Obs dimension selector.
	*
	* Increases the displayed Obs dimension by 1 with a maximum value of Max Obs
	*/
	afx_msg void IncreaseObsDimension();

	/**
	* Handler for double clicking on a variable in the all variables list box.
	*
	* Moves the next available variable dimension defined by the HRU dimension
	*	selector of the variable that was clicked on to the selected variables
	*	list box.
	*/
	afx_msg void OnDblClkAllVarListBox();

	/**
	* Handler for double clicking on a variable in the selected variables list box.
	*
	* Removes the variable from selected variable list box.
	*/
	afx_msg void OnDblClkSelVarListBox();

	/**
	* Handler for the selection in the all variables list box changing.
	* 
	* Updates the variables help text to be that for the last selected variable.
	*/
	afx_msg void OnVariableSelectChange();


	/**
	* Handler for double clicking on an observation in the all observations list box. 
	* 
	* Moves the next available observation dimension defined by the Obs dimension
	*	selector of the observation that was clicked on to the selected observation 
	*	list box. Also adds the series of the observation to the TChart area. 
	*/
	afx_msg void OnDblClkAllObsListBox();

	/**
	* Handler for double clicking on an observation in the selected observations list box.
	* 
	* Removes the observation series from the TChart plot and the selected observation 
	*	from the list box.
	*/
	afx_msg void OnDblClkSelObsListBox();

	/**
	* Handler for the selection in the observation list box changing. 
	* 
	* When the selection changes the help information on that variable is updated.
	*/
	afx_msg void OnObservationSelectChange();

	/**
	* Handler for the message UWM_OPEN_CTX_ALL_VAR
	* 
	* Opens the context menu when the variables list box is right clicked. 
	* Context menu has the following items:
	*	Add - Adds the selected variable items to the set of variables to be output.
	*	Add Array - Adds all HRUs of the selected variable items to the set of variables to be output.
	*/
	afx_msg LRESULT OpenAllVarCtxMenu(WPARAM, LPARAM);

	/**
	* Handler for the message UWM_OPEN_CTX_SEL_VAR
	*
	* Opens the context menu when the selected observations list box is right clicked.
	* Context menu has the following items:
	*	Remove - Removes the selected observations from the selected observations list box and plot.
	*/
	afx_msg LRESULT OpenSelVarCtxMenu(WPARAM, LPARAM);

	/**
	* Handler for the message UWM_OPEN_CTX_ALL_OBS
	* 
	* Opens the context menu when the all observations list box is right clicked.
	* Context menu has the following items:
	*	Add - Adds the selected observation items to the plot and selected box.
	*	Add Array - Adds all dimensions of the selected observation items to the plot and selected box.
	*/
	afx_msg LRESULT OpenAllObsCtxMenu(WPARAM, LPARAM);

	/**
	* Handler for the message UWM_OPEN_CTX_SEL_OBS
	* 
	* Opens the context menu when the selected observations list box is right clicked.
	* Context menu has the following items:
	*	Remove - Removes the selected observations from the selected observations list box and plot.
	*/
	afx_msg LRESULT OpenSelObsCtxMenu(WPARAM, LPARAM);

	/**
	* Checks what variables are selected in the all variables list box and adds the
	*	appropreate dimension to the model and updates the list boxes. 
	*/
	void addVariablesToSelected();

	/**
	* Checks what variables are selected in the all variables list box and adds all HRUs
	*	of those to the model to be displayed.
	*/
	void addVariablesArrayToSelected();

	/**
	* Checks what variables are selected in the all variables list box and adds all layers
	*	of the selected HRU of those to the model to be displayed.
	*/
	void addVariablesLayerArrayToSelected();

	/**
	* Checks what variables are selected in the all variables list box and adds all layers
	*	of all HRUs of those to the model to be displayed.
	*/
	void addVariablesHRULayerArrayToSelected();

	/**
	* Checks what observations are selected in the all observations list box and adds 
	*	the appropreate dimension to the model to be displayed. 
	*/
	void addObservationsToSelected();

	/**
	* Checks what observations are selected in the all observations list box and adds all dimensions
	*	of those to the model to be displayed. 
	*/
	void addObservationsArrayToSelected();
	
	/**
	* Checks what variables are selected in the selected variables list box and removes
	*	them from the model.
	*/
	void removeVariablesFromSelected();

	/**
	* Checks what observations are selected in the selected observations list box and removes
	*	them from the model.
	*/
	void removeObservationsFromSelected();
	
	/**
	* Returns true if the variable with the name passed in is selected
	*	in the model and false otherwise.
	*
	* @param seriesTitle std::string the name of the variable with dimension suffix to be checked.
	*/
	bool variableIsSelected(std::string seriesTitle);

	/**
	* Returns true if the observation with the name passed in is selected 
	*	in the model and false otherwise.
	* 
	* @param seriesTitle std::string the name of the observation with dimension suffix to be checked.
	*/
	bool observationIsSelected(std::string seriesTitle);

	/**
	* Sets the items in a list box to the values in the passed in string vector. 
	* 
	* @param listboxid int the control ID of the listbox to add 
	* @param list std::vector<std::string>* pointer to a vector of the items to add to the list box.
	*/
	void SetItemsToListBox(int listboxid, std::vector<std::string>* list);

	/**
	* Returns the variables present in the selected variables list box. 
	* 
	* @returns std::list<std::pair<std::string, ClassVar*>>* a pointer to a list of pairs of strings and
	*	ClassVar* that are paired to the string.
	*/
	std::list<std::pair<std::string, ClassVar*>> * GetSelectedVariables();

	/**
	* Returns the observations present in the selected observations list box.
	* 
	* @returns std::list<std::pair<std::string, TSeries*>>* a pointer to a list of pairs of observation names
	*	and their related TSeries.
	*/
	std::list<std::pair<std::string, TSeries*>> * GetSelectedObservations();
	
	/**
	* Handler for changing the date in the start date picker.
	* 
	* Ensures that the internal representation of the date is consistant with the GUI.
	*/
	afx_msg void OnStartDateChange(NMHDR* pNMHDR, LRESULT* pResult);
	
	/**
	* Handler for changing the date in the end date picker.
	*
	* Ensures that the internal representation of the date is consistant with the GUI.
	*/
	afx_msg void OnEndDateChange(NMHDR* pNMHDR, LRESULT* pResult);

	/**
	* Handler for clicking on the flip ticks button.
	*/
	afx_msg void OnClickFlipTicks();

	afx_msg LRESULT OnLeftClickFlipTicks(WPARAM, LPARAM);

	afx_msg LRESULT OnRightClickFlipTicks(WPARAM, LPARAM);
	

	afx_msg LRESULT OnAutoRunMessage(WPARAM, LPARAM);

	void setDimensionSelectorToObs();

	void setDimensionSelectorToLay();

	int getMaxLayofSelection();

};