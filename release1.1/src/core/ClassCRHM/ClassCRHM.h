#pragma once
// 11/15/17
//---------------------------------------------------------------------------
#ifndef ClassCRHMH
#define ClassCRHMH
//---------------------------------------------------------------------------

using namespace std;

#include "Common.h"
#include "GlobalCommon.h"
#include "TStringList/TStringList.h"
#include "ClassData.h"
#include "ClassVar.h"
#include "ClassPar.h"
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
typedef int INT;



class Classfilter {
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

	long* DataIndx{ NULL };    // Vs offsets
	long* DataObsCnt {NULL};  // maximum number of observations
	double*** Data {NULL};     // Data[Vs selection][Obs][line]
	double* Constants {NULL}; // constant data

	ClassVar* thisVar {NULL}; // last arg accessed
	ClassVar* outVar {NULL}; // ToVar

	virtual void readargs();
	virtual void error(string Mess);
	void fixup(void);
	virtual void doFunc(long Obs, long Line) { Data[0][Obs][Line] = 0.0; }
	virtual void doFunctions(long Line);
};

class ClassFtoC : Classfilter {
public:
	ClassFtoC(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class ClassCtoK : Classfilter {
public:
	ClassCtoK(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class ClassReplace : Classfilter {
public:
	ClassReplace(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class ClassKtoC : Classfilter {
public:
	ClassKtoC(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class ClassTimeshift : Classfilter {
public:
	ClassTimeshift(ClassData *MyObs, string ToVar, string args, string argtypes = "C");
};

class ClassRH_WtoI : Classfilter {
public:
	ClassRH_WtoI(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class Classea : Classfilter {
public:
	Classea(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class Classrh : Classfilter {
public:
	Classrh(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class Classsin : Classfilter {
public:
	long period {0};
	long phase {0};
	long delay {0};
	long duration {0};
	Classsin(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classcos : Classfilter {
public:
	long period {0};
	long phase {0};
	long delay {0};
	long duration {0};
	Classcos(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classabs : Classfilter {
public:
	Classabs(ClassData *MyObs, string ToVar, string args, string argtypes = "V");

	virtual void doFunc(long Obs, long Line);
};

class Classpulse : Classfilter {
public:
	long delay {0};
	long duration {0};
	Classpulse(ClassData *MyObs, string ToVar, string args, string argtypes = "CC");

	virtual void doFunc(long Obs, long Line);
};

class Classexp : Classfilter {
public:
	long delay {0};
	long duration {0};
	double A {0.0};
	double B {0.0};
	Classexp(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classexpv : Classfilter {
public:
	double A {0.0};
	double B {0.0};
	Classexpv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

class Classpoly : Classfilter {
public:
	long delay {0};
	long duration {0};
	Classpoly(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCCCCC");

	virtual void doFunc(long Obs, long Line);
	virtual string GetFilterName(void) { return typeid(*this).name(); }
};

class Classpolyv : Classfilter {
public:
	Classpolyv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classlog : Classfilter {
public:
	long delay {0};
	long duration {0};
	double A {0.0};
	double B {0.0};
	Classlog(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classlogv : Classfilter {
public:
	double A {0.0};
	double B {0.0};
	Classlogv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

class Classpow : Classfilter {
public:
	long delay {0};
	long duration {0};
	double A {0.0};
	double B {0.0};
	Classpow(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classpowv : Classfilter {
public:
	double A {0.0};
	double B {0.0};
	Classpowv(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	virtual void doFunc(long Obs, long Line);
};

class Classtime : Classfilter {
public:
	double start {0.0};
	int option {0};
	Classtime(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class Classjulian : Classfilter {
public:
	int option {0};
	Classjulian(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class Classrandom : Classfilter {
public:
	Classrandom(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class Classsquare : Classfilter {
public:
	long period {0};
	long phase {0};
	long delay {0};
	long duration {0};
	Classsquare(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classramp : Classfilter {
public:
	long period {0};
	long phase {0};
	long delay {0};
	long duration {0};
	Classramp(ClassData *MyObs, string ToVar, string args, string argtypes = "CCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classrefwind : Classfilter {
public:
	double Const {0.0}; // result log((Z2 - d)/Z)/log((Zm - d)/Z)

	Classrefwind(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCC");

	virtual void doFunc(long Obs, long Line);
};

class Classadd : Classfilter {
public:

	Classadd(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class Classsub : Classfilter {
public:

	Classsub(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class Classmul : Classfilter {
public:

	Classmul(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class Classdiv : Classfilter {
public:

	Classdiv(ClassData *MyObs, string ToVar, string args, string argtypes = "VC");

	virtual void doFunc(long Obs, long Line);
};

class ClassaddV : Classfilter {
public:

	ClassaddV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class ClasssubV : Classfilter {
public:

	ClasssubV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class ClassmulV : Classfilter {
public:

	ClassmulV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class ClassdivV : Classfilter {
public:

	ClassdivV(ClassData *MyObs, string ToVar, string args, string argtypes = "VV");

	virtual void doFunc(long Obs, long Line);
};

class Classconst : Classfilter {
public:

	Classconst(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class ClassSim : Classfilter {
public:

	ClassSim(ClassData *MyObs, string ToVar, string args, string argtypes = "CCC");

	virtual void doFunc(long Obs, long Line);
};

class  ClassSmear : Classfilter {
public:

	ClassSmear(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");

	bool Minus;

	virtual void doFunc(long Obs, long Line);
};

class ClassMissing : Classfilter {
public:

	ClassMissing(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");
	~ClassMissing();

	double *GoodData;

	virtual void doFunc(long Obs, long Line);
};

class ClassMissingInter : Classfilter {
public:

	ClassMissingInter(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC");
	~ClassMissingInter();

	bool FirstTime {true};
	double *GoodData;
	long *LastGoodData;

	virtual void doFunc(long Obs, long Line);
};

class ClassMissing0 : Classfilter {
public:

	ClassMissing0(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class ClassMissingC : Classfilter {
public:

	ClassMissingC(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class ClassMissingFlag : Classfilter {
public:

	ClassMissingFlag(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class ClassMissingFlagAfter : Classfilter {
public:

	ClassMissingFlagAfter(ClassData *MyObs, string ToVar, string args, string argtypes = "VCC") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};
	~ClassMissingFlagAfter();

	long First {0};
	long Last {0};

	virtual void doFunc(long Obs, long Line);
};

class ClassMissingrepl : Classfilter {
public:

	ClassMissingrepl(ClassData *MyObs, string ToVar, string args, string argtypes = "VCCV") :
		Classfilter(MyObs, ToVar, args, argtypes) {
		readargs();
	};

	virtual void doFunc(long Obs, long Line);
};

class ClassForce : Classfilter {
public:

	ClassForce(ClassData *MyObs, string ToVar, string args, string argtypes = "C");

	virtual void doFunc(long Obs, long Line);
};

class Classmacro {
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

class ClassModel {
public:
	string ModelName;
	string ModelModules;

	ClassModel(string ModelName, string ModelModules) :
		ModelName(ModelName), ModelModules(ModelModules) {};
};

void   LogError(CRHMException Except);
void   LogError(string S, TExcept Kind);

void   LogMessage(const char *S, double V, TExtra Opt = TExtra::BLANK);
void   LogMessage(const char *S, double V, const char *S2, TExtra Opt = TExtra::BLANK);
void   LogMessage(const char *S, long V, TExtra Opt = TExtra::BLANK);
void   LogMessage(const char *S, TExtra Opt = TExtra::BLANK);

void   LogMessage(long hh, const char *S, double V, TExtra Opt = TExtra::BLANK);
void   LogMessage(long hh, const char *S, long V, TExtra Opt = TExtra::BLANK);
void   LogMessage(long hh, const char *S, TExtra Opt = TExtra::BLANK);

void   LogMessage(long hh, const char *S, double V1, double V2, TExtra Opt = TExtra::BLANK);
void   LogMessage(long hh, const char *S, double V1, double V2, double V3, TExtra Opt = TExtra::BLANK);

void   LogMessageA(long hh, const char *S, double V1, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const char *S2, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double HRU_area, const double Basin_area, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double HRU_area, const double Basin_area, const char *S2, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double Basin_area, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double Basin_area, const char *S2, TExtra Opt = TExtra::BLANK);

void   LogDebug(long h, char *Text, double v);
void   LogDebug(char *S);
void   LogDebugD(char *S);
void   LogDebugT(string S);

void   Update_Main_Status(string S);

void   Update_Main_DIM(TDim Dim, long dim);

void   Update_Main_Dirty(void);

long getdim(TDim dimen);

long getstep(void);

bool laststep(void);

void setdim(TDim dimen, long dim);

void setdim(string name, long dim);

void ModVarRemove(MapVar & MapVars);

long julian(string when);

//  long julian(TDateTime DT);
//
//  long julian(TDateTime DT);
//
//  long MonthDaysCnt(TDateTime DT);

double Julian(string when);

bool last_timestep(void);

void dattim(string type, long *itime);

void dattim(double DT, long *itime);

ClassVar *declread(string module, string name, long cnt, long offset,
	ClassData * FileData, string Comment);

long ClassParFindParBld(ClassPar *thisPar);

ClassVar *ClassVarFind(string name);

ClassPar *ClassParFindShared(string name); // where name is concatenation of MODULE and NAME

ClassPar *ClassParFind(string name); // where name is concatenation of MODULE and NAME

ClassPar *ClassParFindPar(string name); // where name is parameter

ClassPar *ClassParFind(string module, string param); // routine concatenates MODULE and NAME

ClassPar *ClassParFindRev(string module, string param);

void ClassParSet(ClassPar *p);

//double sqr(double x);

class Tresult {
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

class Convert {
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

void   LogDebug(const char *S);
void   LogDebug(const string S);

#endif
