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
//#include "CString"
#include "Common/Common.h"
//#include "boost/shared_ptr.hpp"
#include "ClassCRHM/ClassCRHM.h"
#include <map>
#include <iostream>
#include<list>
#include "MMSData.h"
#include "TSeries.h"
#include "Classinfo.h"
#include "CRHMLogger.h"
#include "ReportStream.h"
#include "../ClassCRHM/CRHMArguments.h"

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

class CRHMmain
{
	static CRHMmain* instance;

private: 
	bool AutoRun{ false };
	bool AutoExit{ false };
	bool ReportAll{ true };
	bool finishedRun{ false };

public:

	bool getAutoRun();
	void setAutoRun(bool set);
	bool getAutoExit();
	void setAutoExit(bool set);
	bool getFinishedRun();
	bool getReportAll();
	void setReportAll(bool set);

	CRHMLogger* Logger;
	ReportStream * reportStream{NULL};

	static CRHMmain *  getInstance();
	CRHMmain(CRHMArguments * arguments);

	//virtual void DoPrjOpen(string OpenNamePrj, string ProjectDirectory);
	string Sstrings[12] = { "", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Sum", "_Pos", "_Tot", "_Tot/Freq", "_First", "_Last" };

	string OpenNamePrj;
	string OpenNameState;
	//string OpenNamePar;
	string OpenNameObs;
	string OpenNameReport;
	string OpenProjectPath;

	string SaveStateFileName;

	//	string ProjectDirectory;
	string ApplicationDir;

	//manishankar used this meaningful variable name instead of ListBox1.
	std::map<std::string, ClassVar*> * AllVariables; //!< Map keying variable names in model to their ClassVar objects.
	//manishankar used this meaningful variable name instead of ListBox2.
	std::map<std::string, ClassVar*> * AllObservations; //!< Map keying observation names in model to their ClassVar objects.
	//manishankar used this meaningful variable name instead of ListBox3.
	std::list<std::pair<std::string, ClassVar*>> * SelectedVariables; //!< List of selected paired variables names and variable objects.
	//manishankar used this meaningful variable name instead of ListBox4.
	std::list<std::pair<std::string, TSeries *>> * SelectedObservations; //!< List of selected paired observation names and TSeries objects.
	
	double StartDatePicker; // replaces graphic controls. manishankar Picker1 was replaced by StartDatePicker
	double EndDatePicker; //manishankar Picker2 was replaced by EndDatePicker



	std::list<std::pair<std::string, ClassData*>> * ObsFilesList;
	std::list<std::string> * ProjectList;

	bool OpenStateFlag;

	//double ProjectFileDate;
	time_t Dt0; // used to ca


	string ProjectDir;// = ApplicationDir;
	string ProjectDirectory;

	string SaveDialogPrj;

	std::vector<std::string> * ListHruNames;
	std::list<std::string> * LoopList;  // used by ControlReadState
	MapstrSS    *MapGrpNames;

	bool SaveStateFlag;
	bool ProjectOpen;
	bool ShiftDown; // Linked to ListBox1 and ListBox2
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
	long SeriesCnt;

	TSeries *observationseries;

	~CRHMmain();

	bool DoPrjOpen(string OpenNamePrj, string ProjectDirectory);

	void FormCreate(void);

	void InitModules(void);

	void Label4Click(void);

	TFun FindObservationType(string Kind);

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
	string GetObservationName(string vname);
	void ClearModules(bool All);
	void GetObservationData(char * obsfilepath, char * observationname);
	void GetObservationNames(char * obsfilepath);
	string ExtractHruLay(string S, long &Hru, long &Lay);
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

};

//class Classinfo; // used to process shared parameters