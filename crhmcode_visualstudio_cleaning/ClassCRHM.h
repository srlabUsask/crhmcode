#pragma once
// 11/15/17
//---------------------------------------------------------------------------
#ifndef ClassCRHMH
#define ClassCRHMH
//---------------------------------------------------------------------------

using namespace std;

#include "Common.h"
#include "GlobalCommon.h"
#include "TStringList.h"
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>

enum types { DELIMITER = 1, NUMBER };

class Classmacro;
class parser;
class ClassModule;
//TStringList *Strings;

typedef unsigned long Word;

class __declspec(dllexport) ClassData {
public:
 string DataFileName;
 string Description;
	float **Data;
	double *Times; // holds sparse times
	double Dt1;
	double Dt2;
	double Interval; // days
	long Lines;
	long Freq;
	long IndxMin;   // range of data available
	long IndxMax;   // range of data available
	long ModN;      // divisor for data less frequent than basic interval
	long HdrLen;    // length of file header
	long Position;  // current line in file
	long DataCnt;
	long FilterCnt;  // filter count

	Classmacro *myMacro;
	bool Simulation;
	long ForceInterval;
	bool GoodInterval;
	bool GoodDay;
	bool RunUsed;
	bool Success;
	long TimeIndx; // sparse file ??
	bool FirstFile;

	float TimeShiftFilter; // used by Time shift filter

	ClassData(string DataFileName) : DataFileName(DataFileName), Data(NULL), myMacro(NULL),
		DataCnt(0), FilterCnt(0), Simulation(false), FirstFile(false),
		ForceInterval(0), ModN(0), Times(NULL), TimeShiftFilter(0.0) {
		Success = DataReadFile();
	}

	ClassData() : DataFileName(""), Data(NULL), myMacro(NULL),
		DataCnt(0), FilterCnt(0), Simulation(false), FirstFile(false),
		ForceInterval(0), ModN(0), Times(NULL), TimeShiftFilter(0.0) {};

	ClassData(const ClassData & Cl);
	ClassData & operator=(const ClassData & Cl);

	bool DataReadFile(void); //{ return true; };
	long Veto_Freq(long Freq);
	virtual __fastcall ~ClassData(); //{ ; };
	double ClassData::Encode24(int D[]);
};

class __declspec(dllexport) ClassVar {

	typedef void (ClassVar:: *TSomeFunct) (void);
	typedef void (ClassVar:: *TSomeFunct_) (long dim_n);
	typedef void (ClassVar:: *TLoopFunct) (long dim_n);
	typedef void (ClassVar:: *TAccFunct) (ClassModule *);

public:

 string module;
 string root;
 string name;
 string help;
 string units;
 string DLLName; // use to differentiate DLLs and Macros from normal modules, i.e. CRHM

	CRHM::TVar varType;

	long dim;
	long dimMax; // used by observations
	long lay;
	long variation_set;
	CRHM::TDim dimen;

	CRHM::TVISIBLE visibility;
	bool optional;
	bool PointPlot;
	long TchrtOpt;
	long VarFunct;
	bool StatVar;
	long InGroup;
	bool nfreq;
	CRHM::TFun FunKind;
	bool Daily; // used by AddObsPlot to decide how to apply function to input obs/var

	float * values;
	long  * ivalues;

	float ** layvalues;
	long **ilayvalues;

	// backup storage

	float ** layvaluesBkup;
	long **ilayvaluesBkup;

	long offset; // observation offset in ClassData FileData/Data
	long cnt;    // observation dimension

	ClassData  *FileData;

	long HRU_OBS_indexed; // used to access the HRU_OBS[HRU_OBS_indexed][HRU] table
	ClassVar *FunctVar;
	TLoopFunct LoopFunct;  // typedef void (ClassVar:: *SomeFunct) (long dim_n) used in ClassCRHM
	TSomeFunct UserFunct;  // typedef void (ClassVar:: *SomeFunct) (void) used in ClassModule
	TSomeFunct_ UserFunct_;  // typedef void (ClassVar:: *SomeFunct) (long dim_n) used in ClassCRHM
	TAccFunct CustomFunct; // typedef void (ClassVar:: *AccFunct) (ClassModule *) used in ClassModule
 string CustomFunctName; // debug aid
	long No_ReadVar; // do not read observation again in a group but use CustomFunct

	ClassVar(string module = "none",
		
		string name = "none")
		: module(module), name(name), help(""), DLLName(""), root(""), varType(CRHM::none), dim(0), dimMax(0), lay(0), variation_set(0), nfreq(false),
		optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS), VarFunct(0),
		values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Daily(false),
		offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0), UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(false), TchrtOpt(0) {};

	ClassVar(string module, string name, CRHM::TDim dimen,
	 string help, string units, CRHM::TVar varType, bool PointPlot = false, int Grpdim = 0, int defdim = 0);

	ClassVar(string module, string name, long dim,
	 string help, string units, CRHM::TVar varType, bool PointPlot = false);

	ClassVar(string module, string name, long cnt, long offset, ClassData * FileData)
		: module(module), name(name), help(""), DLLName(""), root(""), varType(CRHM::Read), dim(cnt), dimMax(0), lay(0), variation_set(0), nfreq(false),
		optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS), VarFunct(0),
		offset(offset), cnt(cnt), FileData(FileData), HRU_OBS_indexed(0), UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), dimen(CRHM::NOBS),
		values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Daily(false), PointPlot(false), TchrtOpt(0) {};

	virtual __fastcall ~ClassVar() { ReleaseM(); } // releases everything

	void BackUp();
	void Restore();

	ClassVar(const ClassVar & Cl);
	ClassVar & operator=(const ClassVar & Cl);

	float &operator[](int ii) { return values[ii]; }

	virtual void ReleaseM(bool Keep = false);

	virtual void ReadVar();

	virtual void WriteVar();

	virtual string UserName(void) { return module + ' ' + name; };

	virtual void LoopFirst(long dim_n);

	virtual void LoopLast(long dim_n);

	virtual void LoopRange(long dim_n);

	virtual void Avg_(long dim_n);

	virtual void Min_(long dim_n);

	virtual void Max_(long dim_n);

	virtual void First_(long dim_n);

	virtual void Last_(long dim_n);

	virtual void Count_(long dim_n);

	virtual void Count0_(long dim_n);

	virtual void Pos_(long dim_n);

	virtual void Tot_(long dim_n);

	virtual void Avg(void);

	virtual void Min(void);

	virtual void Max(void);

	virtual void Dtot(void);

	virtual void Tot(void);

	virtual void First(void);

	virtual void Last(void);

	virtual void Peak(void);

	virtual void Count(void);

	virtual void Count0(void);

	virtual void Pos(void);

	virtual void Intvl(void);

	virtual void do_t(ClassModule *thisModule); // uses Global::lapse_rate, Global::hru_elev and Global::OBS_ELEV

	virtual void do_t_Clim(ClassModule *thisModule); // uses Global::Warming_t and do_t

	virtual void do_t_day(ClassModule *thisModule); // uses Global::lapse_rate, Global::hru_elev and Global::OBS_ELEV

	virtual void do_t_day_Clim(ClassModule *thisModule); // uses Global::Warming_t and do_t_day

	virtual void do_rh_day(ClassModule *thisModule); // uses Global::obs_ea and Global::obs_t and if Global::RH_VP_flag then Global::obs_t_obs

	virtual void do_rh_day_Clim(ClassModule *thisModule); // uses do_rh_day and if extra Global::RH_VP_flag2 then Global::obs_t_obs

	virtual void do_ea_day(ClassModule *thisModule); // uses Global::obs_rh, Global::obs_t_obs, Global::obs_t and Global::RH_VP_flag

	virtual void do_ppt(ClassModule *thisModule); // uses Global::hru_elev, Global::OBS_ELEV and Global::ppt_adj

	virtual void do_p(ClassModule *thisModule); // uses Global::hru_elev, Global::OBS_ELEV and Global::ppt_adj

	virtual void do_p_Clim(ClassModule *thisModule); // uses Global::Warming_p

	virtual void do_ppt_Clim(ClassModule *thisModule); // uses Global::Warming_p

	long GetUnit(void);

	virtual void review_HRU_OBS(void);
};

class __declspec(dllexport) ClassPar {
public:
 string module;
 string param;
 string basemodule;
 string help;
 string units;

	CRHM::TVar varType;
	CRHM::TDim dimen;

	long dim;
	long lay;
	long variation_set;

	float *values;
	long *ivalues;

	float ** layvalues;
	long **ilayvalues;

	string valstr;
	float minVal;
	float maxVal;

	TStringList *Strings;

	CRHM::TVISIBLE visibility;

	long Inhibit_share; // 0 - shared, 1 - linked to declparam, 2 - declputparam unlinked

						// backup storage

	float ** layvaluesBkup;
	long **ilayvaluesBkup;

	ClassPar *Identical;

	TStringList * StringsBkup;

	ClassPar(string module = "none", string param = "none")
		: module(module), param(param), dim(0), visibility(CRHM::USUAL), variation_set(0), varType(CRHM::none),
		values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Identical(NULL), Inhibit_share(0) {};



		
	ClassPar(string module, string param, CRHM::TDim dimen,  // strings
	 string CommaText, string help, CRHM::TVar varType, int Grpdim);

	ClassPar(string module, string param, CRHM::TDim dimen,  // integer and float
	 string valstr, float minVal, float maxVal,
	 string help, string units, CRHM::TVar varType, int defdim = 0, int GrpN = 0);

	ClassPar(ClassPar &p);  // copy constructor

	float &operator[](int ii) { return values[ii]; }

	virtual __fastcall ~ClassPar();

	bool Same(ClassPar &p);  // compares parameter data

	void Change(ClassPar &p);  // changes this values to p

	virtual string UserName(void) { return module + ' ' + param; };

	friend class ::parser;

	void ExpandShrink(long new_dim);

	void BackUp(void);

	void Restore(void);

	long GetUnit(void);

};

class __declspec(dllexport) Classfilter {
public:
	Classfilter(ClassData *MyObs, string ToVar, string args, string argtypes);

	virtual ~Classfilter();

	ClassData *MyObs;

 string ToVar;
 string argtypes;
 string args;

	long Vs;
	long Cs;
	bool Error;
	long ObsCnt;
	long TotalCnt; // when created;
	bool FirstTime;

	long *DataIndx;    // Vs offsets
	long *DataObsCnt;  // maximum number of observations
	float ***Data;     // Data[Vs selection][Obs][line]
	double *Constants; // constant data

	ClassVar *thisVar; // last arg accessed
	ClassVar *outVar; // ToVar

	virtual void readargs();
	virtual void error(string Mess);
	void fixup(void);
	virtual void doFunc(long Obs, long Line) { Data[0][Obs][Line] = 0.0; }
	virtual void doFunctions(long Line);
};

class __declspec(dllexport) ClassFtoC : Classfilter {
public:
	ClassFtoC(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassCtoK : Classfilter {
public:
	ClassCtoK(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassReplace : Classfilter {
public:
	ClassReplace(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassKtoC : Classfilter {
public:
	ClassKtoC(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassTimeshift : Classfilter {
public:
	ClassTimeshift(ClassData *MyObs, string ToVar, string args, string argtypes = "C");
};

class __declspec(dllexport) ClassRH_WtoI : Classfilter {
public:
	ClassRH_WtoI(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classea : Classfilter {
public:
	Classea(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classrh : Classfilter {
public:
	Classrh(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classsin : Classfilter {
public:
	long period;
	long phase;
	long delay;
	long duration;
	Classsin(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classcos : Classfilter {
public:
	long period;
	long phase;
	long delay;
	long duration;
	Classcos(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classabs : Classfilter {
public:
	Classabs(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpulse : Classfilter {
public:
	long delay;
	long duration;
	Classpulse(ClassData *MyObs, string ToVar, string args, string argtypes = "CC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classexp : Classfilter {
public:
	long delay;
	long duration;
	float A;
	float B;
	Classexp(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classexpv : Classfilter {
public:
	float A;
	float B;
	Classexpv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpoly : Classfilter {
public:
	long delay;
	long duration;
	Classpoly(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCCCCC");

	virtual void doFunc(long Obs, long Line);
	virtual string GetFilterName(void) { return typeid(*this).name(); }
};

class __declspec(dllexport) Classpolyv : Classfilter {
public:
	Classpolyv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classlog : Classfilter {
public:
	long delay;
	long duration;
	float A;
	float B;
	Classlog(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classlogv : Classfilter {
public:
	float A;
	float B;
	Classlogv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpow : Classfilter {
public:
	long delay;
	long duration;
	float A;
	float B;
	Classpow(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classpowv : Classfilter {
public:
	float A;
	float B;
	Classpowv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classtime : Classfilter {
public:
	double start;
	int option;
	Classtime(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classjulian : Classfilter {
public:
	int option;
	Classjulian(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classrandom : Classfilter {
public:
	Classrandom(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classsquare : Classfilter {
public:
	long period;
	long phase;
	long delay;
	long duration;
	Classsquare(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classramp : Classfilter {
public:
	long period;
	long phase;
	long delay;
	long duration;
	Classramp(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classrefwind : Classfilter {
public:
	float Const; // result log((Z2 - d)/Z)/log((Zm - d)/Z)

	Classrefwind(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classadd : Classfilter {
public:

	Classadd(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classsub : Classfilter {
public:

	Classsub(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classmul : Classfilter {
public:

	Classmul(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classdiv : Classfilter {
public:

	Classdiv(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassaddV : Classfilter {
public:

	ClassaddV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClasssubV : Classfilter {
public:

	ClasssubV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassmulV : Classfilter {
public:

	ClassmulV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassdivV : Classfilter {
public:

	ClassdivV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classconst : Classfilter {
public:

	Classconst(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassSim : Classfilter {
public:

	ClassSim(ClassData *MyObs, string ToVar, string args, string argtypes = "CCC");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassSmear : Classfilter {
public:

	ClassSmear(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	bool Minus;

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissing : Classfilter {
public:

	ClassMissing(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");
	~ClassMissing();

	float *GoodData;

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingInter : Classfilter {
public:

	ClassMissingInter(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");
	~ClassMissingInter();

	bool FirstTime;
	float *GoodData;
	long *LastGoodData;

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissing0 : Classfilter {
public:

	ClassMissing0(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingC : Classfilter {
public:

	ClassMissingC(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingFlag : Classfilter {
public:

	ClassMissingFlag(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingFlagAfter : Classfilter {
public:

	ClassMissingFlagAfter(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};
	~ClassMissingFlagAfter();

	long First;
	long Last;

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassMissingrepl : Classfilter {
public:

	ClassMissingrepl(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCV") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) ClassForce : Classfilter {
public:

	ClassForce(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class __declspec(dllexport) Classmacro {
public:
	Classmacro(ClassData *File);
	~Classmacro();

	ClassData *File;
	TStringList *FilterList;
	long Interpolation;
	void addfilter(string Line);
	void fixup(void);
	void execute(long Line);
};

class __declspec(dllexport) ClassModel {
public:
 string ModelName;
 string ModelModules;

	ClassModel(string ModelName, string ModelModules) :
		ModelName(ModelName), ModelModules(ModelModules) {};
};

__declspec(dllexport) void __fastcall LogError(CRHMException Except);
__declspec(dllexport) void __fastcall LogError(string S, TExcept Kind);

__declspec(dllexport) void __fastcall LogMessage(const char *S, float V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(const char *S, float V, const char *S2, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(const char *S, long V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(const char *S, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, float V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, long V, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, float V1, float V2, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessage(long hh, const char *S, float V1, float V2, float V3, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const char *S2, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, const char *S2, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const float Basin_area, TExtra Opt = BLANK);
__declspec(dllexport) void __fastcall LogMessageA(long hh, const char *S, float V1, const float Basin_area, const char *S2, TExtra Opt = BLANK);

__declspec(dllexport) void __fastcall LogDebug(long h, char *Text, float v);
__declspec(dllexport) void __fastcall LogDebug(char *S);
__declspec(dllexport) void __fastcall LogDebugD(char *S);
__declspec(dllexport) void __fastcall LogDebugT(char *S);

__declspec(dllexport) void __fastcall Update_Main_Status(string S);

__declspec(dllexport) void __fastcall Update_Main_DIM(CRHM::TDim Dim, long dim);

__declspec(dllexport) void __fastcall Update_Main_Dirty(void);

__declspec(dllexport) long getdim(CRHM::TDim dimen);

__declspec(dllexport) long getstep(void);

__declspec(dllexport) bool laststep(void);

__declspec(dllexport) void setdim(CRHM::TDim dimen, long dim);

__declspec(dllexport) void setdim(string name, long dim);

__declspec(dllexport) void ModVarRemove(MapVar & MapVars);

__declspec(dllexport) long julian(char *when);

//__declspec(dllexport) long julian(TDateTime DT);
//
//__declspec(dllexport) long julian(TDateTime DT);
//
//__declspec(dllexport) long MonthDaysCnt(TDateTime DT);

__declspec(dllexport) float Julian(char *when);

__declspec(dllexport) bool last_timestep(void);

__declspec(dllexport) void dattim(char *type, long *itime);

__declspec(dllexport) void dattim(double DT, long *itime);

__declspec(dllexport) ClassVar *declread(string module, string name, long cnt, long offset,
	ClassData * FileData, string Comment);

__declspec(dllexport) long ClassParFindParBld(ClassPar *thisPar);

__declspec(dllexport) ClassVar *ClassVarFind(string name);

__declspec(dllexport) ClassPar *ClassParFindShared(string name); // where name is concatenation of MODULE and NAME

__declspec(dllexport) ClassPar *ClassParFind(string name); // where name is concatenation of MODULE and NAME

__declspec(dllexport) ClassPar *ClassParFindPar(string name); // where name is parameter

__declspec(dllexport) ClassPar *ClassParFind(string module, string param); // routine concatenates MODULE and NAME

__declspec(dllexport) ClassPar *ClassParFindRev(string module, string param);

__declspec(dllexport) void ClassParSet(ClassPar *p);

//float sqr(float x);

class __declspec(dllexport) Tresult {
public:
	double k;
	char *aExp;

	Tresult(int size) : k(1.0) {
		aExp = new char[size];
		::memset(aExp, 0, sizeof(char)*size);
	}
	~Tresult() { delete[] aExp; }
};

class Unit_Info {
public:
 string Abbr;
 string Name;
	double k;
 string Expr;

	Unit_Info() :
		Abbr(""), Name(""), k(0.0), Expr("") {};

	Unit_Info(string Abbr_, string Name_, double k_, string Expr_) :
		Abbr(Abbr_), Name(Name_), k(k_), Expr(Expr_) {};
};

class Multiplier_Info {
public:
	char Abbr;
 string Name;
	double k;
	Multiplier_Info(char Abbr_, string Name_, double k_) :
		Abbr(Abbr_), Name(Name_), k(k_) {};
};

class __declspec(dllexport) Convert {
	static Unit_Info Infos[];
	static Multiplier_Info Multipliers[];

	int NumBasicUnits;
	int NumUnits;
	int NumMultipliers;

public:
	Convert();

	bool ConvertUnit(double& dValue, string pszSrcUnit, string pszDstUnit);

	double quickPow(double k, int nPow);
	int LookupUnit(string pszIn);
	void DivUnit(Tresult& u1, const Tresult& u2);
	void MulUnit(Tresult& u1, const Tresult& u2);
	void MulUnitK(Tresult& u, double k);
	void PowUnit(Tresult& u, char nPow);
	void SetBasicUnit(Tresult& u, double k, int iBasicUnit);
	void ExpandUnitExpr(Tresult& u, double k, string pszExpr);

 string ParseDivUnitExpr(string pszIn, Tresult& u);
 string ParseMulUnitExpr(string pszIn, Tresult& u);
 string ParsePowUnitExpr(string pszIn, Tresult& u);
 string ParseUnitPhase1(string pszIn, Tresult& u);
 string ParseUnitPhase2(string pszIn, Tresult& u);

	void CheckUnitsString(string Name, string variable, string units);
	void CheckUnitsObs(string Vunits, string Munits, string declaration); // check original observation units

	bool CheckUnitsTable();

};
string extract_units(string& Comment);
#endif