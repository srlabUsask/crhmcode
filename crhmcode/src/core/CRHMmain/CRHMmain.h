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
//#include "CString"
#include "Common/Common.h"
#include "TStringList/TStringList.h"
//#include "boost/shared_ptr.hpp"
#include "ClassCRHM/ClassCRHM.h"
#include <map>
#include <iostream>
#include<list>
#include "MMSData.h"
#include "TSeries.h"
#include "Classinfo.h"
#include "CRHMLogger.h"
#include "../../gcc/CRHMArguments.h"

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

class CRHMmain
{
	static CRHMmain* instance;

public:

	CRHMLogger* Logger;

	static CRHMmain *  getInstance();
	CRHMmain(struct crhm_arguments * );

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

	TStringList *AllVariables; //manishankar used this meaningful variable name instead of ListBox1.
	TStringList *AllObservations; //manishankar used this meaningful variable name instead of ListBox2.
	TStringList *SelectedVariables; //manishankar used this meaningful variable name instead of ListBox3.
	TStringList *SelectedObservations; //manishankar used this meaningful variable name instead of ListBox4.
	TStringList *queryResult;


	double StartDatePicker; // replaces graphic controls. manishankar Picker1 was replaced by StartDatePicker
	double EndDatePicker; //manishankar Picker2 was replaced by EndDatePicker



	TStringList *ObsFilesList;
	TStringList *ProjectList;

	bool OpenStateFlag;

	//double ProjectFileDate;
	time_t Dt0; // used to ca


	string ProjectDir;// = ApplicationDir;
	string ProjectDirectory;

	string SaveDialogPrj;



	TStringList *OpenDLLs;
	TStringList *PrjObsHelp;
	TStringList *ListHruNames;

	TStringList *LoopList;  // used by ControlReadState
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

	void DoPrjOpen(string OpenNamePrj, string ProjectDirectory);

	void makeQuery(string statementtype, string statement, string fields, int fieldcount);
	string getQueryValue(int row, int column);

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

	void ObsFileClose(void);

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


	TStringList * getObservations();

	TStringList * getAllmodules();

	TStringList* getVariables();

	MMSData * RunClick2Start();
	void RunClick2Middle(MMSData * mmsdata, long startdate, long enddate);
	void RunClick2End(MMSData * mmsdata);
	void RunClick(void);
	void CheckBlankModule();
	void AllRprt();
	void  ControlReadState(bool MainLoop, ClassPar * VarPar);
	void  LastRprt(void);
	void  ControlSaveState(bool MainLoop, ClassPar * VarPar, BitSet &Bit);
	void DoObsStatus(bool &First);
	void calculateOutputFileName();
	void RprtHeader(TStringList *LogList, int LocalCnt);
	void RprtHeaderObs(TStringList *LogList, int LocalCnt);
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
	TStringList* getSelectedVariables();
	TStringList* getSelectedObservations();
	void setSelectedObservatoions(TStringList * t);
	void setSelectedVariables(TStringList * t);


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

	TObject * GetObjectOfVariable(string vname); //added this function from CRHMmainDlg.cpp file.
	TObject * GetObjectOfObservation(string vname); //added this function from CRHMmainDlg.cpp file.

	void SaveState();

	void print_progress_start();

	void print_progress(long current_step, long last_step, int print_frequency);

	void print_progress_end();

};

//class Classinfo; // used to process shared parameters