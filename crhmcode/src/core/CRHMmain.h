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

/**
* Detecting what platform is being compiled on and setting either the COMMAND_LINE or VS_GUI flag
**/
#if defined(__linux__) || defined(__APPLE__) || defined(__MINGW32__)
#define COMMAND_LINE
#endif
#if defined(_WIN32) && defined(_MSC_VER )
#define VS_GUI
#endif

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <list>
#include <iostream>

#include "Common.h"
#include "ClassCRHM.h"
#include "MMSData.h"
#include "TSeries.h"
#include "Classinfo.h"
#include "CRHMLogger.h"
#include "ReportStream.h"
#include "CRHMArguments.h"

//class ObsFileInfo {
//private:
//	list<string> obsNames;
//	char *filepath;
//
//public:
//
//	list<string> getObsName();
//	char *getFilePath();
//	void addObsName(string obsName);
//	void setFilePath(string filepath);
//};

//Forward Declarations
class ReportStream;
class CRHMArguments;
enum class OUTPUT_FORMAT;

enum class TimeBase { DAILY, WATER_YEAR, CALENDAR_YEAR, MONTHLY, ALL };

class CRHMmain
{
	static CRHMmain* instance;

private:
	/**
	* True if the AutoRun directive is set for the current project.
	* 
	* Saved in project file as Auto_Run
	*/
	bool AutoRun{ false };

	/**
	* True if the AutoExit directive is set for the current project. 
	* 
	* Saved in the project file as Auto_Exit
	*/
	bool AutoExit{ false };

	/**
	* True if all the variable outputs should be output to file.
	* False if only the values for the last time step should be output to file.
	* 
	* Saved in the project file as Log_All for true or Log_Last for false.
	*/
	bool ReportAll{ true };

	/**
	* True when a simulation run has been completed and is still saved in program memory.
	*/
	bool finishedRun{ false };

	/**
	* Tracks if a summary file has been requested for the loaded project.
	*/
	bool Summarize{ false };

	/**
	* Represents the summary period to be used for applying functions to observations or variables.
	*/
	TimeBase time_base;

	/**
	* Integer value of the month the water year ends.
	* 1 == January ... 12 == December.
	*/
	int water_year_month;

	/**
	* Ouputs the requested summary information to a .sum file with the same name as the output file.
	*/
	void OutputSummary();

public:
	
	/**
	* Retrives the value of the AutoRun field.
	* 
	* @return bool - true if AutoRun is enabled false otherwise.
	*/
	bool getAutoRun();

	/**
	* Sets the value of the AutoRun field.
	* 
	* @param set - bool value to set the field to.
	*/
	void setAutoRun(bool set);
	
	/**
	* Retrives the value of the AutoExit field.
	* 
	* @return bool - true if AutoExit is enabled false otherwise.
	*/
	bool getAutoExit();

	/**
	* Sets the value of the AutoExit field.
	* 
	* @param set - bool value to set the field to.
	*/
	void setAutoExit(bool set);
	
	/**
	* Retrives the value of the FinishedRun field
	* 
	* @return bool - true if a simulation run is finished and still in program memory false otherwise.
	*/
	bool getFinishedRun();
	
	/**
	* Retrives the value of the ReportAll field. 
	* 
	* @return bool - true if Log_All is enabled false if Log_Last is enabled.
	*/
	bool getReportAll();

	/**
	* Sets the value of the ReportAll field.
	* 
	* @param set - bool value to set the ReportAll field to.
	*/
	void setReportAll(bool set);

	/**
	* Retrives the value of the Summarize field.
	* 
	* @return bool - true if a summary is to be produced and false otherwise
	*/
	bool getSummarize();

	/**
	* Sets the value of the Summarize field.
	* 
	* @param set - bool value to set the Summarize field to.
	*/
	void setSummarize(bool set);

	/**
	* Retrives the value of the time_base field
	* 
	* @return TimeBase the value of the time_base field
	*/
	TimeBase getTimeBase();

	/**
	* Sets the value of the time_base field
	* 
	* @param base - TimeBase value to set the time_base field to.
	*/
	void setTimeBase(TimeBase base);

	/**
	* Retrives the value of the water_year_month field
	* 
	* @return int the value of the water_year_month field
	*/
	int getWaterYearMonth();

	/**
	* Sets the value of the water_year_month field
	* 
	* @param month - int the value to set the water_year_month to must be between 1-12
	*/
	void setWaterYearMonth(int month);

	/**
	* Reference to the reportStream object.
	*/
	ReportStream * reportStream{NULL};

	/**
	* Retrives the singleton instance of the main CRHM class.
	* 
	* @return CRHMmain* - Reference to the one and only CRHMmain object.
	*/
	static CRHMmain *  getInstance();

	/**
	* Constructs a CRHMmain object from a set of command line arguments.
	*/
	CRHMmain(CRHMArguments * arguments);
	
	/**
	* Name of the open project file.
	*/
	std::string OpenNamePrj;

	/**
	* Name of the open state file
	*/
	std::string OpenNameState;

	/**
	* Tracks if there is a open inital state file
	* true if there is false otherwise.
	*/
	bool OpenStateFlag;
	
	/**
	* Name to save the produced report to
	*/
	std::string OpenNameReport;
	
	/**
	* Name of the open project file.
	*/
	std::string OpenProjectPath;

	/**
	* Name of the file to save the final state to.
	*/
	std::string SaveStateFileName;

	/**
	* Tracks if a final state file is requested to be produced.
	*/
	bool SaveStateFlag;

	/**
	* Map keying variable names in the model to their ClassVar objects.
	* 
	* Used to be "ListBox1"
	*/
	std::map<std::string, ClassVar*> * AllVariables; 

	/**
	* Map keying observation names in model to their ClassVar objects.
	* 
	* Used to be "ListBox2"
	*/
	std::map<std::string, ClassVar*> * AllObservations;

	/**
	* List of the selected variables stored as a pair of variable name and ClassVar object.
	* 
	* Used to be "ListBox3"
	*/
	std::list<std::pair<std::string, ClassVar*>> * SelectedVariables; 

	/**
	* List of the selected observations stored as a pair of variable name and TSeries plots
	* 
	* Used to be "ListBox4"
	*/
	std::list<std::pair<std::string, TSeries *>> * SelectedObservations; 

	/**
	* Stores in double MS date format the start date of the simulation.
	*/
	double StartDate;
	
	/**
	* Stores in double MS date format the end date of the simulation.
	*/
	double EndDate;

	/**
	* List of open observation files stored as a pair of the file name and the ClassData object
	*/
	std::list<std::pair<std::string, ClassData*>> * ObsFilesList;
	
	/**
	* Used to store as a series of lines a project file to be written.
	*/
	std::list<std::string> * ProjectList;

	/**
	* The file path to the open project directory
	*/
	std::string ProjectDirectory;

	/**
	* Ordered list of names for HRU units. Can be used in place of HRU numbers.
	*/
	std::vector<std::string> * ListHruNames;

	/**
	* List of strings used in function ControlReadState
	*/
	std::list<std::string> * LoopList;
	
	MapstrSS* MapGrpNames;

	/**
	* Tracks if a project is currently open.
	* True if a project is open, false otherwise
	*/
	bool ProjectOpen;

	/**
	* Tracks if HRU names are being used over numbers
	* True if they are false otherwise.
	*/
	bool HruNames;


	OUTPUT_FORMAT OutputFormat;
	std::string OutputName;
	std::string ObsFileDirectory;
	bool ShowProgress;
	int UpdateProgress;
	char Delimiter;

	typedef  void LoadModuleType(string DllName);

	//	TDateTime ProjectFileDate;

	TSeries **cdSeries;

	TSeries *observationseries;

	~CRHMmain();

	bool DoPrjOpen(string OpenNamePrj, string ProjectDirectory);

	void FormCreate(void);

	void InitModules(void);

	void Label4Click(void);

	void SqueezeParams(void);

	void SetBasinParams(ClassPar * basinPar);

	void MacroLoad(void);

	string DeclObsName(ClassVar * thisVar);

	bool OpenObsFile(string FileName);

	void ObsCloseClick(void);

	void ObsFileClose(std::string filepath);

	void FormDestroy(void);

	void FreeChart1(void);

	bool FileExistsSp(string FileName);

	bool FindFileName(string & FileName);
	void SetSharedParams(ClassPar *basinPar);



	//Global global;



	TFun Funct = TFun::FOBS;

	int InitModCnt = 0;
	int InitMacroCnt = 0;

	ClassPar *StatePar = NULL; // used to handle basin StateVars_to_Handle


	std::map<std::string, ClassVar*> * getObservations();

	std::map<std::string, ClassModule *> * getAllmodules();

	/*
	* Return a reference to the list of modules declared in the current model.
	*/
	std::list<std::pair<std::string, ClassModule*>>* getOurModules();

	std::map<std::string, ClassVar*>* getVariables();

	MMSData * RunClick2Start();
	void RunClick2Middle(MMSData * mmsdata, long startdate, long enddate);
	void RunClick2End(MMSData * mmsdata);
	void RunClick(void);
	void CheckBlankModule();
	void ControlReadState(bool MainLoop, ClassPar * VarPar);
	void ControlSaveState(bool MainLoop, ClassPar * VarPar);
	void DoObsStatus(bool &First);
	void calculateOutputFileName();
	void ResetLoopList(void);
	void ReadStateFile(bool & GoodRun);
	string DttoStr(double D);
	string inttoStr(int I);
	void LogMessageX(const char *S);

	void SaveProject(string prj_description, string filepath);



	double GetStartDate();
	void setStartDate(double sdate);
	double GetEndDate();
	void setEndDate(double edate);
	std::list<std::pair<std::string, ClassVar *>> * getSelectedVariables();
	std::list<std::pair<std::string, TSeries *>> * getSelectedObservations();
	void setSelectedObservatoions(std::list<std::pair<std::string, TSeries*>> * t);
	void setSelectedVariables(std::list<std::pair<std::string, ClassVar*>> * t);


	string GetCaptionFromAboutBox();
	string  ExtractHruLayFunct(string S, long &Hru, long &Lay, string &Funct, string &FullName);
	
	/**
	* Extracts the name of an observation from an observation label string 
	*	that is in the format [name]([HRU],[LAY])
	* 
	* @return std::string - the name associated with an observation object found by looking for 
	*	an empty string is returned if the name portion of the label cannot be used to find an 
	*	observation object in the AllObservations field.
	*/
	std::string GetObservationName(std::string observationLabel);
	void ClearModules(bool All);
	void GetObservationData(char * obsfilepath, char * observationname);
	void GetObservationNames(char * obsfilepath);

	/**
	* Extracts the HRU and LAY value from a variable/observation label string
	*	that is in the format [name]([HRU],[LAY])
	* 
	* @param label - std::string the lable for values to be extracted from.
	* @param Hru - int& An integer where the value of [HRU] will be placed in.
	* @param Lay - int& An integer where the value of [LAY] will be placed in.
	* @return std::string - The name of the variable or observation without HRU or LAY label.
	*/
	std::string ExtractHruLay(std::string label, int &Hru, int &Lay);
	
	string BuildHru(string S, long Hru, TDim dimen);
	string BuildLay(string S, long Lay);
	void BldModelClick();
	void MacroClick(void);
	void ListBoxMacroClear();

	ClassVar * GetObjectOfVariable(string vname); //added this function from CRHMmainDlg.cpp file.
	ClassVar * GetObjectOfObservation(string vname); //added this function from CRHMmainDlg.cpp file.

	void SaveState();

	void print_progress_start();

	void print_progress(long current_step, long last_step, int print_frequency);

	void print_progress_end();

	/**
	* Calculates the series of values that make up a TSeries representing an Observation plot
	* 
	* @param thisVar - ClassVar* pointer to the ClassVar object associated with the observation
	* @param cdSeries - TSeries* pointer to the TSeries object where the series representing the observation plot will be stored
	* @param seriesTitle - std::string the name of the series to be represented.
	* @param TFun - Funct the function to be applied to the observation being ploted
	*/
	void calculateObservationTseries(ClassVar* thisVar, TSeries* cdSeries, string seriesTitle, TFun Funct);

	void calculateVariableFunctionOutput(std::string varName, TSeries* varPlot, TFun function);

};

//class Classinfo; // used to process shared parameters
