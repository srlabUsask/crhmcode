#pragma once

#ifndef CLASSMACRO
#define CLASSMACRO

#include "MacroUnit.h"

class DefCRHM;

typedef std::shared_ptr<DefCRHM> DefCRHMPtr;

typedef std::shared_ptr<ClassModule> ModulePtr;

class ClassMacro : public ClassModule {

public:

	symtab_t::iterator FP;

	list<DefCRHMPtr> Calls;    // declaration list used for declarations
	list<ModulePtr> Modules;   // list used for modules
	list<Execbase> Operations; // shortened to 'oper' in CRHM_parse.h
	std::vector<std::pair<std::string, ClassModule*>> * GrpStringList;// list of modules in group or struct
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

	ClassModule* ObsModule;

	// declared parameters
	const double* HRU_group;

	ClassMacro(string NameX, int ThisBegin = 0, string Version = "undefined", string Desc = "not available");  // , string Desc = "not available"

	~ClassMacro();

	long declobs(string module, string name, TDim dimen, string help, string units, double** value);

	virtual void decl(void);

	virtual void init(void);

	virtual void run(void);

	virtual void finish(bool good);

	ClassMacro* klone(string name) const;

	/**
	* Retrives all of the parameters associated with a group macro. Appending them to
	* the provided list.
	* 
	* @param allParameters - std::list<std::pair<std::string, ClassPar*>>* pointer to a list to append all of the 
	*     parameter entries to.
	*/
	void RetrieveAllParameters(std::list<std::pair<std::string, ClassPar*>> * allParameters);
};

#endif // !CLASSMACRO
