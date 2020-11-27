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
#include "Classfilter.h"
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
