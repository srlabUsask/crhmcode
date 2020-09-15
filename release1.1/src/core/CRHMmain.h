#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
//#include "CString"
#include "Common.h"
#include "TStringList.h"
//#include "boost/shared_ptr.hpp"
#include "ClassCRHM.h"
#include <map>
#include <iostream>
#include<list>


class MMSData
{
public:
	double ** mmsData;
	long ** mmsDataL;
	bool GoodRun;
	ClassModule *obs_preset;
	string S;
};



class TSeries {
public:
	double *XValues;
	double *YValues;
	ClassVar *Tag;
	int MaxCnt;
	int Used;
	string Title;
	TSeries(int Cnt) { MaxCnt = Cnt; XValues = new double[MaxCnt]; YValues = new double[MaxCnt]; Used = 0; };
	~TSeries() { delete[] XValues; delete[] YValues; };
	void AddXY(double X, double Y) { XValues[Used] = X; YValues[Used++] = Y; };
	int Count(void) { return Used; };
	double XValue(int nn) { return XValues[nn]; };
	double YValue(int nn) { return YValues[nn]; };
};



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

class Classinfo {
public:
	Classinfo() : thisPar(NULL), rootinfo(NULL), matched(false), cnt(0) {};
	Classinfo(ClassPar *thisPar) : thisPar(thisPar), rootinfo(NULL), matched(false), cnt(0) {};
	ClassPar *thisPar;
	Classinfo *rootinfo;
	long cnt;
	bool matched;
};


class CRHMmain
{


	static CRHMmain* instance;

public:
	static CRHMmain *  getInstance();
	CRHMmain();

	//virtual void DoPrjOpen(string OpenNamePrj, string ProjectDirectory);
	string Sstrings[12] = { "", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Sum", "_Pos", "_Tot", "_Tot/Freq", "_First", "_Last" };

	string OpenNamePrj;
	string OpenNameState;
	//string OpenNamePar;
	string OpenNameObs;
	string OpenNameReport;
	string OpenProjectPath;

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
	double Dt0; // used to ca


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

	void GetAllVariables(void);

	CRHM::TFun FindObservationType(string Kind);

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



	CRHM::TFun Funct = CRHM::FOBS;

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
	void RprtHeader(TStringList *LogList, int LocalCnt);
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
	string BuildHru(string S, long Hru, CRHM::TDim dimen);
	string BuildLay(string S, long Lay);
	void BldModelClick();
	void MacroClick(void);
	void ListBoxMacroClear();

	TObject * GetObjectOfVariable(string vname); //added this function from CRHMmainDlg.cpp file.
	TObject * GetObjectOfObservation(string vname); //added this function from CRHMmainDlg.cpp file.

};



//class Classinfo; // used to process shared parameters




