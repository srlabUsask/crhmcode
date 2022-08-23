#pragma once

// 02/20/18
//---------------------------------------------------------------------------

#ifndef ClassModuleH
#define ClassModuleH
//---------------------------------------------------------------------------
#include <cmath>
#include <string>
#include <time.h>

#include "GlobalCommon.h"
#include "GlobalDll.h"
#include "ClassCRHM.h"
#include "Administer.h"
#include "Myparser.h"
#include "ClassClark.h"
#include "ClassMuskingum.h"



using namespace std;

enum class OUTCOME { None, Implicit, Explicit, IgnoreObs, IgnoreVar, IgnoreObsFunct };

class Administer;

class   ClassModule {
private:
	std::list<std::pair<std::string, ClassPar*>> parameters_list;

	

public:

	std::list<std::pair<std::string, ClassPar*>>* getParametersList();

	string Name; // Module or Macro name
	string NameRoot; // When Macro gives Root
	string DLLName; // CRHM, Macro or DLL name
	string ID; // Class name. If macro is the macro name
	Administer* OurAdmin {NULL};
	string Version;
	long PeerRank;
	string PeerVar;
	LMODULE Lvl;  // module level - BASIC, MACRO, ADVANCE, SUPPORT, CUSTOM, PROTO, OBSOL
	string Description;

	long nhru; // # of HRU's. Can be different from Global::nhru for groups, structurs and comprising modules
	long nobs;
	long nlay;
	long hh;
	long nn;
	unsigned short variation;     // module operating variation
	unsigned short variation_set; // current variation call variation level
	unsigned short variation_max; // maximum - OR of all variation_set

	bool isGroup; // in declgroup macros
	bool isStruct; // in declstruct macros
	long GroupCnt; // in declgroup macros and comprising modules
	long StructCnt; // in declstruct macros and comprising modules
	long ModuleIndx; // in declstruct - module index starting at 1 to nhru

	const long *HRU_struct; // only defined for structure Macros and modules

	long Dummy;

	double** Var_loop_lay_value {NULL};
	double** Par_loop_lay_value {NULL};

	double*** Var_loop_lay_table {NULL};
	double*** Par_loop_lay_table {NULL};

	long Var_NDEFN_cnt = 0;
	long Par_NDEFN_cnt = 0;

	// long Using_RH_EA_obs;

	ClassModule(string Name, string Version, LMODULE Lvl = LMODULE::PROTO, long PeerRank = 1000, string PeerVar = "")
		: Name(Name), NameRoot(Name), Version(Version), Lvl(Lvl), PeerRank(PeerRank), PeerVar(PeerVar), HRU_struct(NULL), isGroup(false), isStruct(false),
		nhru(0), nobs(0), nlay(0), hh(0), nn(0), variation(0), variation_set(0), variation_max(0),
		DLLName(""), GroupCnt(0), StructCnt(0), ModuleIndx(0),
		ID(typeid(*this).name()) {
		Dummy = -9999;
	};

	virtual ~ClassModule() {};

	virtual void decl(void) {};
	void initbase(void);
	virtual void init(void) {};
	virtual void run(void) {};
	virtual void run2(double **) {}; //added by Manishankar to solve the address issue.
	virtual void pre_run(void) {};
	virtual void finish(bool good) {};
	ClassModule* link(string Module);
	double Now(void);
	virtual double Function1(double *I, long hh) { return 0.0; };
	virtual double Function2(double *X, long hh) { return 0.0; };
	virtual void reset(void) {

		nhru = 0;
		nobs = 0;
		nlay = 0;

		variation = 0;
		variation_set = 0;
		variation_max = 0;

		isGroup = false;
		isStruct = false;
		GroupCnt = 0;
		StructCnt = 0;
		HRU_struct = NULL;
	};

	bool chkStruct(void) {
		if (HRU_struct != NULL)
			while (hh < nhru && ModuleIndx != HRU_struct[hh])
			{
				++hh;
			}
		return hh < nhru;
	};

	bool chkStruct(long &hh) {
		if (HRU_struct != NULL)
			while (hh < nhru && ModuleIndx != HRU_struct[hh])
			{
				++hh;
			}
		return hh < nhru;
	};

	bool chkStruct(long &hh, long Nhru) {
		if (HRU_struct != NULL)
			while (hh < Nhru && ModuleIndx != HRU_struct[hh])
			{
				++hh;
			}
		return hh < Nhru;
	};

	bool chkStructOff(long &hh, long Nhru) { // for macros
		if (HRU_struct != NULL)
			while (hh < Nhru && ModuleIndx != HRU_struct[hh - 1]) // note offset range
			{
				++hh;
			}
		return hh < Nhru;
	};

	virtual ClassModule* klone(string name) const {
		return NULL;
	};

	string Var_name(ClassModule* thisModule, string S);

	long getdim(TDim dimen);

	void AKAhook(TAKA type, string module, string OrgName, string & NewName);

	void AKAhook(TAKA type, string module, string OrgName, string & NewName, string & source, string base);

	int declgrpvar(string variable, string queryvar,
		string help, string units, double **value, double ***layvalue, bool PointPlot = false);

	void declvar(string variable, TDim dimen,
		string help, string units, double **value, double ***layvalue = NULL, const int dim = 1,
		bool PointPlot = false, bool StatVar = false, TVISIBLE Local = TVISIBLE::USUAL);

	void declvar(string variable, TDim dimen,
		string help, string units, long **value, long ***ilayvalue = NULL, const int dim = 1,
		bool PointPlot = false, bool StatVar = false, TVISIBLE Local = TVISIBLE::USUAL);

	void decldiag(string variable, TDim dimen,
		string help, string units, double **value, double ***layvalue = NULL, const int dim = 1,
		bool PointPlot = false, TVISIBLE Local = TVISIBLE::DIAGNOSTIC);

	void declstatdiag(string variable, TDim dimen,
		string help, string units, double **value, double ***layvalue = NULL, const int dim = 1,
		bool PointPlot = false, TVISIBLE Local = TVISIBLE::DIAGNOSTIC);

	void decldiag(string variable, TDim dimen,
		string help, string units, long **value, long ***ilayvalue = NULL, const int dim = 1,
		bool PointPlot = false, TVISIBLE Local = TVISIBLE::DIAGNOSTIC);

	void declstatdiag(string variable, TDim dimen,
		string help, string units, long **value, long ***ilayvalue = NULL, const int dim = 1,
		bool PointPlot = false, TVISIBLE Local = TVISIBLE::DIAGNOSTIC);

	void declstatvar(string variable, TDim dimen,
		string help, string units, double **value, double ***layvalue = NULL, const int dim = 1,
		bool PointPlot = false, TVISIBLE Local = TVISIBLE::USUAL);

	void declstatvar(string variable, TDim dimen,
		string help, string units, long **value, long ***ilayvalue = NULL, const int dim = 1,
		bool PointPlot = false, TVISIBLE Local = TVISIBLE::USUAL);

	void decllocal(string variable, TDim dimen,
		string help, string units, double **value, double ***layvalue = NULL, const int dim = 1);

	void decllocal(string variable, TDim dimen,
		string help, string units, long **value, long ***ilayvalue = NULL, const int dim = 1);

	

	/**
	* Declares a user defined floating point basic parameter for a module.
	* 
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param valstr - std::string string the defines the default value of the parameter.
	* @param minstr - std::string string that defines the minimum value of the parameter.
	* @param maxstr - std::string string that defines the maximum value of the parameter.
	* @param help - std::string help string for the parameter. 
	* @param units - std::string units the units string for the parameter.
	* @param value - double** Pointer to an array of doubles that holds the values for the parameter.
	* @param layvalue - double*** Pointer to a two dimenional array of doubles that holds the values for the parameter.
	* @param dim - int purpose unknown defaults to 1.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to USUAL which indicates a basic parameter.
	*/
	void declparam(
		std::string param, 
		TDim dimen,
		std::string valstr, 
		std::string minstr, 
		std::string maxstr,
		std::string help, 
		std::string units, 
		const double **value,
		const double ***layvalue = NULL, 
		const int dim = 1, 
		TVISIBLE Local = TVISIBLE::USUAL
	);

	/**
	* Declares a user defined integer basic parameter for a module.
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param valstr - std::string string the defines the default value of the parameter.
	* @param minstr - std::string string that defines the minimum value of the parameter.
	* @param maxstr - std::string string that defines the maximum value of the parameter.
	* @param help - std::string help string for the parameter.
	* @param units - std::string units the units string for the parameter.
	* @param value - long** Pointer to an array of longs that holds the values for the parameter.
	* @param ilayvalue - long*** Pointer to a two dimenional array of longs that holds the values for the parameter.
	* @param dim - int purpose unknown defaults to 1.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to USUAL which indicates a basic parameter.
	*/
	void declparam(
		std::string param, 
		TDim dimen,
		std::string valstr, 
		std::string minstr, 
		std::string maxstr,
		std::string help, 
		std::string units, 
		const long **value,
		const long ***ilayvalue = NULL, 
		const int dim = 1, 
		TVISIBLE Local = TVISIBLE::USUAL
	);

	/**
	* Declares a user defined string basic parameter 
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param Texts - std::string the default string to use in the parameter.
	* @param help - std::string the help string for the parameter.
	* @param stringsList - std::vector<std::string>* pointer to the vector where the parameter values are stored.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to USUAL which indicates a basic parameter.
	*/
	std::vector<std::string>* declparam(
		std::string param, 
		TDim dimen, 
		std::string Texts, 
		std::string help, 
		std::vector<std::string>* stringsList, 
		TVISIBLE Local = TVISIBLE::USUAL
	);

	/**
	* Declares a user defined floating point advance parameter for a module.
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param valstr - std::string string the defines the default value of the parameter.
	* @param minstr - std::string string that defines the minimum value of the parameter.
	* @param maxstr - std::string string that defines the maximum value of the parameter.
	* @param help - std::string help string for the parameter.
	* @param units - std::string units the units string for the parameter.
	* @param value - double** Pointer to an array of doubles that holds the values for the parameter.
	* @param layvalue - double*** Pointer to a two dimenional array of doubles that holds the values for the parameter.
	* @param dim - int purpose unknown defaults to 1.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to DIAGNOSTIC which indicates an advance parameter.
	*/
	void decldiagparam(
		std::string param, 
		TDim dimen,
		std::string valstr, 
		std::string minstr, 
		std::string maxstr,
		std::string help, 
		std::string units, 
		const double **value,
		const double ***layvalue = NULL, 
		const int dim = 1, 
		TVISIBLE Local = TVISIBLE::DIAGNOSTIC
	);

	/**
	* Declares a user defined integer advance parameter for a module.
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param valstr - std::string string the defines the default value of the parameter.
	* @param minstr - std::string string that defines the minimum value of the parameter.
	* @param maxstr - std::string string that defines the maximum value of the parameter.
	* @param help - std::string help string for the parameter.
	* @param units - std::string units the units string for the parameter.
	* @param value - long** Pointer to an array of longs that holds the values for the parameter.
	* @param ilayvalue - long*** Pointer to a two dimenional array of longs that holds the values for the parameter.
	* @param dim - int purpose unknown defaults to 1.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to DIAGNOSTIC which indicates an advance parameter.
	*/
	void decldiagparam(
		std::string param, 
		TDim dimen,
		std::string valstr, 
		std::string minstr, 
		std::string maxstr,
		std::string help, 
		std::string units, 
		const long **value,
		const long ***ilayvalue = NULL, 
		const int dim = 1, 
		TVISIBLE Local = TVISIBLE::DIAGNOSTIC
	);

	/**
	* Declares a user defined string advance parameter
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param Texts - std::string the default string to use in the parameter.
	* @param help - std::string the help string for the parameter.
	* @param stringsList - std::vector<std::string>* pointer to the vector where the parameter values are stored.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to DIAGNOSTIC which indicates an advance parameter.
	*/
	std::vector<std::string>* decldiagparam(
		std::string param,
		TDim dimen,
		std::string Texts,
		std::string help,
		std::vector<std::string>* stringsList,
		TVISIBLE Local = TVISIBLE::DIAGNOSTIC
	);

	/**
	* Declares a user defined floating point private parameter for a module.
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param valstr - std::string string the defines the default value of the parameter.
	* @param minstr - std::string string that defines the minimum value of the parameter.
	* @param maxstr - std::string string that defines the maximum value of the parameter.
	* @param help - std::string help string for the parameter.
	* @param units - std::string units the units string for the parameter.
	* @param value - double** Pointer to an array of doubles that holds the values for the parameter.
	* @param layvalue - double*** Pointer to a two dimenional array of doubles that holds the values for the parameter.
	* @param dim - int purpose unknown defaults to 1.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to PRIVATE which indicates a private parameter.
	*/
	void decllocalparam(
		std::string param, 
		TDim dimen,
		std::string valstr, 
		std::string minstr, 
		std::string maxstr,
		std::string help, 
		std::string units, 
		const double **value,
		const double ***layvalue = NULL, 
		const int dim = 1, 
		TVISIBLE Local = TVISIBLE::PRIVATE
	);

	/**
	* Declares a user defined integer private parameter for a module.
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param valstr - std::string string the defines the default value of the parameter.
	* @param minstr - std::string string that defines the minimum value of the parameter.
	* @param maxstr - std::string string that defines the maximum value of the parameter.
	* @param help - std::string help string for the parameter.
	* @param units - std::string units the units string for the parameter.
	* @param value - long** Pointer to an array of longs that holds the values for the parameter.
	* @param ilayvalue - long*** Pointer to a two dimenional array of longs that holds the values for the parameter.
	* @param dim - int purpose unknown defaults to 1.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to PRIVATE which indicates a private parameter.
	*/
	void decllocalparam(
		std::string param, 
		TDim dimen,
		std::string valstr, 
		std::string minstr, 
		std::string maxstr,
		std::string help, 
		std::string units, 
		const long **value,
		const long ***ilayvalue = NULL, 
		const int dim = 1, 
		TVISIBLE Local = TVISIBLE::PRIVATE
	);

	/**
	* Declares a user defined string private parameter
	*
	* @param param - std::string the name of the parameter.
	* @param dimen - TDim defines the dimensonality of the parameter.
	* @param Texts - std::string the default string to use in the parameter.
	* @param help - std::string the help string for the parameter.
	* @param stringsList - std::vector<std::string>* pointer to the vector where the parameter values are stored.
	* @param Local - TVISABLE indicates the visability level of the parameter defaults to PRIVATE which indicates a private parameter.
	*/
	std::vector<std::string> * decllocalparam(
		string param, 
		TDim dimen, 
		string Texts, 
		string help, 
		std::vector<std::string> *stringsList, 
		TVISIBLE Local = TVISIBLE::PRIVATE
	);

	long declgetvar(string source, string name, string units, const double **value, const double ***layvalue = NULL);

	long declgetvar(string source, string name, string units, const long **value, const long ***layvalue = NULL);

	long declreadobs(string variable, TDim dimen, string help, string units,
		const double **value, long HRU_index = CRHM::HRU_OBS_t_rh_ea, bool optional = false, const double ***layvalue = NULL);

	long declreadobs(string variable, TDim dimen, string help, string units,
		const long **value, long HRU_index = 0, bool optional = false, const long ***layvalue = NULL);

	long declobs(string name, TDim dimen, string help, string units, double **value);

	long declobsfunc(string obs, string variable, double **value, TFun typeFun, double ***layvalue = NULL, bool optional = false);

	long declobsfunc(string obs, string variable, long **value, TFun typeFun, bool optional = false);

	long declputvar(string source, string name, string units, double **value, double ***layvalue = NULL);

	long declputvar(string source, string name, string units, long **value, long ***layvalue = NULL);

	long declputparam(string source, string name, string units, double **value, double ***layvalue = NULL);

	long declgetparam(string source, string name, string units, const double **value, const double ***layvalue = NULL);

	long declputparam(string source, string name, string units, long **value, long ***layvalue = NULL);

	void declgetparam(string source, string name, string units, const long **value, const long ***layvalue = NULL);

	void InitReadObs(void);  // used by RunClick to assign storage and reset Index

	void ReadObs(bool NotStart);  // reads current interval observations

	bool ReadAheadObs(long inc = 0); // reads inc interval observations ahead

	bool ReadAheadObsMacro(long inc = 0); // reads inc interval observations ahead

	bool WriteAheadObsMacro(long inc = 0); // writes interval observations ahead previously set by ReadAheadObs

	void DelReadObs(void);  // used by RunClick to delete storage

	void addtoreadlist(ClassVar *newVar);

	void addtofunctlist(ClassVar *newVar);

	long getdimObs(string variable);

	long FindWildVarFloat(string name, ClassVar* &newVar, bool OnceFlag = false);

	long FindWildParFloat(string name, ClassPar* &newPar, bool Org, bool Root);

	bool Variation_Skip(void);

	bool AnyOne(double *Data, int Cnt, double Val);

	bool UsingObservations(void);

	ClassModule* FindModule_from_parameter(string source, string param);
};


static string getTimeGG() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%A, %B %d, %Y", timeinfo);
	string strr = buffer;
	/*
	time_t t1 = GetCurrentTime();
	CTime t2 = t1 + CTimeSpan(0, 1, 0, 0);
	CString cs = t1.Format(_T("%A, %B %d, %Y"));

	CT2A ct(cs);
	string strr(ct);
	*/
	return (strr);
};

/*static string getTimeGG() {
CTime t1 = CTime::GetCurrentTime();
CTime t2 = t1 + CTimeSpan(0, 1, 0, 0);
CString cs = t1.Format(_T("%A, %B %d, %Y"));

CT2A ct(cs);
string strr(ct);
return (strr);
};*/


TAKA AKAtype(std::string type);

#endif
