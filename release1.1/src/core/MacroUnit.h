#pragma once

// 10/04/12
//---------------------------------------------------------------------------

#include "CRHM_parse.h"
#include "ClassModule.h"
#include <string>
//#include "boost/spirit/core/basics.hpp"

#ifndef MacroUnitH
#define MacroUnitH
//---------------------------------------------------------------------------
using namespace std;

class DefCRHM;

typedef std::shared_ptr<DefCRHM> DefCRHMPtr;

typedef std::shared_ptr<ClassModule> ModulePtr;

string Add_Quote(string s);

class ClassMacro : public ClassModule {

public:

	symtab_t::iterator FP;

	TStringList *Declaration;

	list<DefCRHMPtr> Calls;    // declaration list used for declarations
	list<ModulePtr> Modules;   // list used for modules
	list<Execbase> Operations; // shortened to 'oper' in CRHM_parse.h
	TStringList *GrpStringList;// list of modules in group or struct
	long Grpnhru;              // group actual nhru
	stack<double> eval;         // execution stack for double values
	symtab_t vars;             // symbol table
	stack<VarCHRM*> LastVar;   // used to access variables in case they are nested
	stack<VarCHRM*> LastVas;   // used to access assigned variables in case they are nested
	list<Execbase> ::iterator PCiter; // execution program counter

	friend class DefCRHM;

	int MacroBegin; // index to MacroModulesList first line
	int Begin; // index to MacroModulesList 'command'
	int End;   // index to MacroModulesList 'end'

	ClassModule *ObsModule;

	// declared parameters
	const double *HRU_group;

	ClassMacro(string NameX, int ThisBegin = 0, string Version = "undefined", string Desc = "not available");  // , string Desc = "not available"

	~ClassMacro();

	long declobs(string module, string name, CRHM::TDim dimen, string help, string units, double **value);

	virtual void decl(void);

	virtual void init(void);

	virtual void run(void);

	virtual void finish(bool good);

	ClassMacro* klone(string name) const;
};

class DefCRHM {
public:
	DefCRHM(ClassMacro *Macro_) : Macro(Macro_), fix(NULL), fix2(NULL)
	{
		if (!DefStringList) DefStringList = new TStringList;
	};

	static TStringList *DefStringList;
	virtual void CallDecl() {};
	virtual void CallInit(long nhru, long nlay) {};

protected:
	CRHM::TDim getTDim(string D);
	TFun getTFunc(string D);
	ClassMacro *Macro;
	symtab_t::iterator FP;
	double *fix;
	long* fix_long {NULL};
	double** fix2 {NULL};
	const double* fix_const {NULL};
	const double** fix2_const {NULL};
	const long* fix_long_const {NULL};
	const long** fix2_long_const {NULL};
};

class Defcommand : public DefCRHM {
public:
	Defcommand(ClassMacro *Macro_) : DefCRHM(Macro_) {}
};

class Defdeclparam : public DefCRHM {
public:
	Defdeclparam(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	CRHM::TDim Dim;
	string Default;
	string Min;
	string Max;
	string Description;
	string Units;
	bool Int;
	int nlay;
	CRHM::TVISIBLE visibility;
};

class Defdeclvar : public DefCRHM {
public:
	Defdeclvar(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	CRHM::TDim Dim;
	string Description;
	string Units;
	bool Int;
};

class Defdecldiag : public DefCRHM {
public:
	Defdecldiag(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	CRHM::TDim Dim;
	string Description;
	string Units;
	bool Int;
};

class Defdeclstatvar : public DefCRHM {
public:
	Defdeclstatvar(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	CRHM::TDim Dim;
	string Description;
	string Units;
	bool Int;
};

class Defdecllocal : public DefCRHM {
public:
	Defdecllocal(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	CRHM::TDim Dim;
	string Description;
	string Units;
	bool Int;
};

class Defdeclobs : public DefCRHM {
public:
	Defdeclobs(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	CRHM::TDim Dim;
	string Description;
	string Units;
};

class Defdeclgetvar : public DefCRHM {
public:
	Defdeclgetvar(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string module;
	string name;
	string Units;
	bool Int;
};

class Defdeclputvar : public DefCRHM {
public:
	Defdeclputvar(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string module;
	string name;
	string Units;
	bool Int;
};

class Defdeclputparam : public DefCRHM {
public:
	Defdeclputparam(ClassMacro *Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string module;
	string name;
	string Units;
	bool Int;
};

class Defdeclreadobs : public DefCRHM {
public:
	Defdeclreadobs(ClassMacro *Macro_);
	void CallDecl();

	string name;
	CRHM::TDim Dim;
	string Description;
	string Units;
	long HRU_OBS_indexed;
};

class Defdeclobsfunc : public DefCRHM {
public:
	Defdeclobsfunc(ClassMacro *Macro_);
	void CallDecl();

	string obs;
	string name;
	TFun typeFun;
};

#endif
