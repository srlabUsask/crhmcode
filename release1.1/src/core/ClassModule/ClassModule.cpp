
#if defined(_WIN32)
#include "stdafx.h"
#endif

#include <stdio.h>
//#include <tchar.h>
#include "assert.h"

// 01/30/18
//---------------------------------------------------------------------------


//#pragma hdrstop



#include "ClassModule.h"
#include "Common/Common.h"


//---------------------------------------------------------------------------

//#pragma package(smart_init)
//#pragma init_seg

using namespace std;

TStringList *ReadListN = new TStringList;

TStringList *FunctListN = new TStringList;

string Fstrings[] = { "Observation", "VP_saturated", "W_to_MJ/Int", "MJ/Int_to_W", "Average", "Minimum", "Maximum", "Daily Sum", "Positive",
"Total", "First", "Last", "Peak", "Count", "Count0", "Intvl" };

string AKAstrings[] = { "VARG", "OBSR", "VARD", "OBSD", "PARD", "OBSF" };







//---------------------------------------------------------------------------
double ClassModule::Now(void) {

	//return std::stod(getTimeGG());
	return Global::DTnow;
}

//---------------------------------------------------------------------------
string ClassModule::Var_name(ClassModule* thisModule, string S) {
	if (thisModule->variation != 0) {
		string AA("#0");
		AA[2] += (char) (log(thisModule->variation) / log(2) + 1);
		S += AA;
	}
	return S;
}

//---------------------------------------------------------------------------
void ClassModule::initbase(void) {



	Global::BuildFlag = TBuild::INIT;


	MapPar::iterator itPar;
	//ClassPar *newPar; variable is unreferenced commenting out for now - jhs507



	if (Var_NDEFN_cnt) {
		
		Var_loop_lay_table = new double**[Var_NDEFN_cnt]; // define [#Var][#layers]
														 
		for (long jj = 0; jj < Var_NDEFN_cnt; ++jj) {
			Var_loop_lay_table[jj] = new double*[nlay];
		}
		
		Var_loop_lay_value = new double*[Var_NDEFN_cnt]; // define [#Var]
		for (long jj = 0; jj < Var_NDEFN_cnt; ++jj)
			Var_loop_lay_value[jj] = new double[nhru];
	}
	else {
		
		Var_loop_lay_table = NULL;
		Var_loop_lay_value = NULL;
	}

	

	if (Par_NDEFN_cnt) {
		Par_loop_lay_table = new double**[Par_NDEFN_cnt];
		for (long jj = 0; jj < Par_NDEFN_cnt; ++jj) {
			Par_loop_lay_table[jj] = new double*[nlay];
			for (long ll = 0; ll < nlay; ++ll)
				Par_loop_lay_table[ll] = new double*[nhru];
		}
		Par_loop_lay_value = new double*[Par_NDEFN_cnt];
		for (long jj = 0; jj < Par_NDEFN_cnt; ++jj) {
			Par_loop_lay_value[jj] = new double[nlay];
			for (long ll = 0; ll < nlay; ++ll)
				Par_loop_lay_value[ll] = new double[nhru];
		}
	}
	else {
		Par_loop_lay_table = NULL;
		Par_loop_lay_value = NULL;
	}

	

	Var_NDEFN_cnt = 0;
	Par_NDEFN_cnt = 0;


	

	decl();  // executes the INIT portion of the declvar/declparam etc. routines

	init();  // executes the module init() routine

			 

}

//---------------------------------------------------------------------------
int ClassModule::declgrpvar(string variable, string queryvar, string help,
	string units, double **value, double ***layvalue, bool PointPlot) {

	MapVar::iterator itVar;
	ClassVar *newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}
	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(TAKA::VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		PeerVar = queryvar.c_str();
		return 0;
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return 0;
		}

		if (layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return -1;
		}

		if (!Global::GroupCntTrk) {
			LogError(CRHMException("No groups defined " + Name + " " + variable, TExcept::WARNING));
			return -1;
		}
		newVar = new ClassVar(Name, variable, TDim::NREB, help, units, TVar::Float, PointPlot, nhru);

		newVar->varType = TVar::Float;

		newVar->variation_set = variation_set;

		newVar->InGroup = GroupCnt;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return 0;
	}

	case TBuild::INIT: {
		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) 
		{
			newVar = (*itVar).second;
			*value = newVar->values;

			for (int ii = 0; ii < nhru; ++ii)
				newVar->layvalues[ii] = NULL;

			if (!Global::GroupCntTrk) // no groups in model!
				return 0;

			long querycnt = 0;
			for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) 
			{
				ClassVar* foundVar = (*itVar).second;

				if (newVar != NULL) 
				{
					if (foundVar->FileData) 
					{
						continue;
					}
					
					string S = foundVar->name;
					string::size_type indx = S.find('@');
					
					if (indx != string::npos) 
					{
						string N = S.substr(indx + 1);
						S = S.erase(indx);
						if (S == queryvar) 
						{
							newVar->layvalues[querycnt] = foundVar->values;
							newVar->values[querycnt] = foundVar->dim;
							++querycnt;
						} // if - this queryvar
					} // if - found group
				} // if - not null, is it possible?
			} // for
			
			if (newVar != NULL) 
			{
				*layvalue = newVar->layvalues; // return address
			}
			else
			{
				CRHMException Except("variable was null found: " + Name + ' ' + variable, TExcept::TERMINATE);
				LogError(Except);
				throw Except;
			}
			
			return querycnt;
		}
		else 
		{
			CRHMException Except("variable not found: " + Name + ' ' + variable, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return -1;
}

//---------------------------------------------------------------------------
void ClassModule::decldiag(string variable, TDim dimen,
	string help, string units, double **value, double ***layvalue, const int dim, bool PointPlot, TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, false, Local);
}
//---------------------------------------------------------------------------

void ClassModule::decldiag(string variable, TDim dimen,
	string help, string units, long **value, long ***ilayvalue, const int dim, bool PointPlot, TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, false, Local);

}
//---------------------------------------------------------------------------

void ClassModule::declstatdiag(string variable, TDim dimen,
	string help, string units, double **value, double ***layvalue, const int dim, bool PointPlot, TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == TBuild::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------
void ClassModule::declstatdiag(string variable, TDim dimen,
	string help, string units, long **value, long ***ilayvalue, const int dim, bool PointPlot, TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == TBuild::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------
void ClassModule::declstatvar(string variable, TDim dimen,
	string help, string units, double **value, double ***layvalue, const int dim, bool PointPlot, TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == TBuild::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------
void ClassModule::declstatvar(string variable, TDim dimen,
	string help, string units, long **value, long ***ilayvalue, const int dim, bool PointPlot, TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == TBuild::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------

void ClassModule::declvar(string variable, TDim dimen, string help,
	string units, double **value, double ***layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local) {
	MapVar::iterator itVar;
	ClassVar *newVar;
	string Orgvariable = variable;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(TAKA::VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(variable.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);

		Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

		return;
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return;
		}

		if (dimen == TDim::NLAY && layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return;
		}

		if (dimen == TDim::NDEFN) // save for lay loop
			++Var_NDEFN_cnt;

		newVar = new ClassVar(Name, variable, dimen, help, units, TVar::Float, PointPlot, nhru, dim);

		newVar->varType = TVar::Float;

		newVar->StatVar = StatVar;

		newVar->InGroup = GroupCnt;

		newVar->visibility = Local;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);
		return;
	}

	case TBuild::INIT: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if (newVar->layvalues != NULL) {
				if (dimen == TDim::NFREQ && newVar->lay != Global::Freq) {
					newVar->nfreq = true;
					newVar->lay = Global::Freq;
					newVar->ReleaseM(true);
					newVar->layvalues = new double *[newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->layvalues[ii] = new double[newVar->dim];
				}
				if ((dimen == TDim::NLAY || dimen == TDim::NDEFN) && newVar->lay != dim) {
					long JJ = newVar->lay;
				}

			}

			if (layvalue) // TB 10/30/10
				*layvalue = newVar->layvalues;

			*value = newVar->values; // TB 10/07/10

			if (dimen == TDim::NDEF) { // save for lay loop
				Var_loop_lay_table[Var_NDEFN_cnt] = newVar->layvalues;
				Var_loop_lay_value[Var_NDEFN_cnt++] = newVar->values;
			}

			Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

			return;
		}
		else {
			CRHMException Except("variable not found: " + Name + ' ' + variable, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void ClassModule::declvar(string variable, TDim dimen, string help,
	string units, long **ivalue, long ***ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local) {

	MapVar::iterator itVar;
	ClassVar *newVar;
	string Orgvariable = variable;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::VARD, Name, variable, variable);

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(variable.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);

		Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

		return;
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return;
		}

		if (dimen == TDim::NLAY && ilayvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return;
		}

		newVar = new ClassVar(Name, variable, dimen, help, units, TVar::Int, PointPlot, nhru, dim);

		newVar->varType = TVar::Int;

		newVar->StatVar = StatVar;

		newVar->InGroup = GroupCnt;

		newVar->visibility = Local;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);
		return;
	}

	case TBuild::INIT: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if ((dimen == TDim::NLAY || dimen == TDim::NFREQ) && ilayvalue != NULL) {
				if (newVar->nfreq && newVar->lay != Global::Freq) {
					newVar->ReleaseM(true);
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->ilayvalues = new long *[newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->ilayvalues[ii] = new long[newVar->dim];
				}
			}

			if (ilayvalue) // TB 10/30/10
				*ilayvalue = newVar->ilayvalues;

			*ivalue = newVar->ivalues; // TB move 10/07/10

			Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

			return;
		}
		else {
			CRHMException Except("Variable not found: " + Name + ' ' + variable, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void ClassModule::decllocal(string variable, TDim dimen, string help,
	string units, double **value, double ***layvalue, const int dim) {

	MapVar::iterator itVar;
	ClassVar *newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(TAKA::VARD, Name, variable, variable); // new 04/23/13

	switch (Global::BuildFlag) {

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find("#" + Name + " " + variable)) != Global::MapVars.end())
			return;

		if ((dimen == TDim::NLAY || dimen == TDim::NFREQ) && layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return;
		}

		newVar = new ClassVar(Name, variable, dimen, help, units, TVar::Float, false, nhru, dim);

		newVar->varType = TVar::Float;

		newVar->InGroup = GroupCnt;

		newVar->visibility = TVISIBLE::PRIVATE;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar("#" + Name + " " + variable, newVar);

		Global::MapVars.insert(Item);
		return;
	}

	case TBuild::INIT: {

		string S = "#" + Name + " " + variable;

		if ((itVar = Global::MapVars.find(S)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if ((dimen == TDim::NLAY || dimen == TDim::NFREQ) && layvalue != NULL) {
				if (newVar->nfreq && newVar->lay != Global::Freq) {
					newVar->ReleaseM(true);
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->layvalues = new double *[newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->layvalues[ii] = new double[newVar->dim];
				}
				*layvalue = newVar->layvalues;
			}

			*value = newVar->values;

			return;
		}
		else {
			CRHMException Except("variable not found: " + S, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void ClassModule::decllocal(string variable, TDim dimen, string help,
	string units, long **value, long ***layvalue, const int dim) {

	MapVar::iterator itVar;
	ClassVar *newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(TAKA::VARD, Name, variable, variable); // new 04/23/13

	switch (Global::BuildFlag) {

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find("#" + Name + " " + variable)) != Global::MapVars.end())
			return;

		if (dimen == TDim::NLAY && layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return;
		}

		newVar = new ClassVar(Name, variable, dimen, help, units, TVar::Int, false, nhru, dim);

		newVar->varType = TVar::Int;

		newVar->InGroup = GroupCnt;

		newVar->visibility = TVISIBLE::PRIVATE;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar("#" + Name + " " + variable, newVar);

		Global::MapVars.insert(Item);
		return;
	}

	case TBuild::INIT: {

		string S = "#" + Name + " " + variable;

		if ((itVar = Global::MapVars.find(S)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if ((dimen == TDim::NLAY || dimen == TDim::NFREQ) && layvalue != NULL) {
				if (newVar->nfreq && newVar->lay != Global::Freq) {
					newVar->ReleaseM(true);
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->ilayvalues = new long *[newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->ilayvalues[ii] = new long[newVar->dim];
				}
				*layvalue = newVar->ilayvalues;
			}

			*value = newVar->ivalues;

			return;
		}
		else {
			CRHMException Except("variable not found: " + S, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
TStringList* ClassModule::decldiagparam(string param, TDim dimen,
	string Texts, string help, TStringList *stringsList, TVISIBLE Local) {

	TStringList* fix = declparam(param, dimen, Texts, help, stringsList, Local);
	return fix;
}

//---------------------------------------------------------------------------
TStringList* ClassModule::decllocalparam(string param, TDim dimen,
	string Texts, string help, TStringList *stringsList, TVISIBLE Local) {

	TStringList* fix = declparam(param, dimen, Texts, help, stringsList, Local);
	return fix;
}

//---------------------------------------------------------------------------
TStringList* ClassModule::declparam(string param, TDim dimen,
	string Texts, string help, TStringList *stringsList, TVISIBLE Local) {
	MapPar::iterator itPar;
	ClassPar *newPar;

	if (Variation_Skip()) {
		return (TStringList*)NULL;
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::PARD, Name, param, param);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(param.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return (TStringList*)NULL;
	}

	case TBuild::DECL: {

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == TDim::BASIN) {
				newPar = (*itPar).second;
				return newPar->Strings;
			}
			else {
				(*itPar).second->ExpandShrink(this->nhru);
				newPar = (*itPar).second;
				return newPar->Strings;
			}
		}

		if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			return newPar->Strings;
		}

		newPar = new ClassPar(string(Name.c_str()), string(param), dimen, Texts, help, TVar::Txt, nhru);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = Local;

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return newPar->Strings;
	}

	case TBuild::INIT: {
		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			stringsList = newPar->Strings;
			return stringsList;
		}
		else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			stringsList = newPar->Strings;
			return stringsList;
		}
		else {
			CRHMException Except("Parameter not found: " + Name + param, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return (TStringList*)NULL;
}

//---------------------------------------------------------------------------
void ClassModule::decldiagparam(string param, TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const double **value, const double ***layvalue, const int dim, TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::decllocalparam(string param, TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const double **value, const double ***layvalue, const int dim, TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::declparam(string param, TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const double **value, const double ***layvalue, const int dim, TVISIBLE Local) {
	MapPar::iterator itPar;
	ClassPar *newPar;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(TAKA::PARD, Name, param, param);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(param.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return;
	}

	case TBuild::DECL: {

		if (dim <= 0) { // find existing parameter
			return;
		}

		if (dimen == TDim::NDEFN)// save for lay loop
			++Par_NDEFN_cnt;

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == TDim::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->basemodule = this->NameRoot;
					newPar->variation_set = variation_set;
					newPar->visibility = Local;
					newPar->Inhibit_share = 1;
					newPar->valstr = valstr;
					newPar->minVal = atof(minstr.c_str());
					newPar->maxVal = atof(maxstr.c_str());
					newPar->help = help;
				}
				return;
			}
			else {
				(*itPar).second->ExpandShrink(this->nhru);
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->Inhibit_share = 1;
				}
				return;
			}
		}

		if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == TDim::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->Inhibit_share = 1;
					//            assert(0);
				}
				return;
			}
		}

		if ((dimen == TDim::NLAY && layvalue == NULL) || (dimen == TDim::NDEF && layvalue == NULL) || (dimen == TDim::NDEFN && layvalue == NULL)) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + param, TExcept::WARNING));
			return;
		}

		double minval = atof(minstr.c_str());
		double maxval = atof(maxstr.c_str());

		newPar = new ClassPar(string(Name.c_str()), string(param), dimen,
			valstr, minval, maxval, help, units, TVar::Float, dim, nhru);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = Local;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return;
	}

	case TBuild::INIT: {
		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			*value = newPar->values;
		}
		else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			*value = newPar->values;
		}
		else if ((newPar = ClassParFindPar(param))) {
			*value = newPar->values;
		}
		else {
			CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}

		if ((dimen == TDim::NLAY && layvalue != NULL) || (dimen == TDim::NDEF && layvalue != NULL) || (dimen == TDim::NDEFN && layvalue != NULL))
			*layvalue = (const double**)newPar->layvalues;

		if (dimen == TDim::NDEF) {
			Par_loop_lay_table[Par_NDEFN_cnt] = newPar->layvalues; // save for lay loop
			Par_loop_lay_value[Par_NDEFN_cnt++] = newPar->values; // save for lay loop
		}
	} // case
	default:
		break;
	} // switch
}

//---------------------------------------------------------------------------
void ClassModule::decldiagparam(string param, TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const long **value, const long ***layvalue, const int dim, TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::decllocalparam(string param, TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const long **value, const long ***layvalue, const int dim, TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::declparam(string param, TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const long **ivalue, const long ***ilayvalue, const int dim, TVISIBLE Local) {

	MapPar::iterator itPar;
	ClassPar *newPar;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(TAKA::PARD, Name, param, param);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP((int)Local);
		PairstrV Item2 = PairstrV(param.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return;
	}

	case TBuild::DECL: {

		if (dim <= 0) { // find existing parameter
			return;
		}

		*ivalue = &Dummy;

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == TDim::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->basemodule = this->NameRoot;
					newPar->variation_set = variation_set;
					newPar->visibility = Local;
					newPar->Inhibit_share = 1;
					newPar->valstr = valstr;
					newPar->minVal = atof(minstr.c_str());
					newPar->maxVal = atof(maxstr.c_str());
					newPar->help = help;
				}
				return;
			}
			else {
				(*itPar).second->ExpandShrink(this->nhru);
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					assert(0);
				}
				return;
			}
		}

		if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == TDim::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					assert(0);
				}
				return;
			}
		}

		if ((dimen == TDim::NLAY && ilayvalue == NULL) || (dimen == TDim::NDEF && ilayvalue == NULL) || (dimen == TDim::NDEFN && ilayvalue == NULL)) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + param, TExcept::WARNING));
			return;
		}

		double minval = atof(minstr.c_str());
		double maxval = atof(maxstr.c_str());

		newPar = new ClassPar(string(Name.c_str()), string(param), dimen,
			valstr, minval, maxval, help, units, TVar::Int, dim, nhru);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = Local;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return;
	}

	case TBuild::INIT: {
		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			*ivalue = newPar->ivalues;
			if ((dimen == TDim::NLAY && ilayvalue != NULL) || (dimen == TDim::NDEF && ilayvalue != NULL) || (dimen == TDim::NDEFN && ilayvalue != NULL))
				*ilayvalue = (const long **)newPar->ilayvalues;
			return;
		}
		else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			*ivalue = newPar->ivalues;
			if ((dimen == TDim::NLAY && ilayvalue != NULL) || (dimen == TDim::NDEF && ilayvalue != NULL) || (dimen == TDim::NDEFN && ilayvalue != NULL))
				*ilayvalue = (const long **)newPar->ilayvalues;
			return;
		}
		else if ((newPar = ClassParFindPar(param))) {
			*ivalue = newPar->ivalues;
			if ((dimen == TDim::NLAY && ilayvalue != NULL) || (dimen == TDim::NDEF && ilayvalue != NULL) || (dimen == TDim::NDEFN && ilayvalue != NULL))
				*ilayvalue = (const long **)newPar->ilayvalues;
			return;
		}
		else {
			CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	} // case
	default:
		break;
	} // switch
}

//---------------------------------------------------------------------------
long ClassModule::FindWildVarFloat(string name, ClassVar* &newVar, bool OnceFlag) {

	string spacename = " " + name;;
	string Var;

	MapVar::iterator itVar;
	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		Var = (*itVar).first;

		if (Var[0] == '#') // local variable
			continue;

		string::size_type indx = Var.rfind(spacename); // can find name inside longer name
		if (indx == string::npos) {
			continue; // nothing found
		}

		newVar = (*itVar).second;
		if (newVar->cnt > 0)  // only observations set "cnt"
			continue;

		if (spacename.substr(1) != newVar->name) // exact match - previous match contained name
			continue;

		Global::thisVar = (TObject*)newVar;
		return newVar->GetUnit();
	} // for

	if (OnceFlag == false) {
		OnceFlag = true;
		string::size_type indx = name.find('@');
		if (indx != string::npos) {
			spacename = name.substr(0, indx); // truncate name */
			return FindWildVarFloat(spacename, newVar, true);
		}
	}

	Global::thisVar = NULL;
	return -1;
}
//---------------------------------------------------------------------------
long ClassModule::FindWildParFloat(string name, ClassPar* &newPar, bool Trunc = false, bool Root = true) {

	string spacename;
	if (!Trunc)
		spacename = " " + name;
	else {
		string::size_type indx2 = name.find('@');
		if (indx2 == string::npos)
			return -1;
		else
			spacename = " " + name.substr(0, indx2); // truncate name
	}

	MapPar::iterator itPar;
	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
		string Var = (*itPar).first;
		if (Var[0] == '#') continue;
		string::size_type indx = Var.rfind(spacename);
		newPar = (*itPar).second;
		if (indx == string::npos) continue; // will also find name inside longer name
		string::size_type indx2 = newPar->param.find('@');
		if (!Root || indx2 == string::npos) {
			if (spacename.substr(1) != newPar->param) // non group or mismatch
				continue;
		}
		else
			if (spacename.substr(1) != newPar->param.substr(0, indx2)) continue; // group

		return newPar->GetUnit();
	}
	return -1;
}
//---------------------------------------------------------------------------
long ClassModule::declgetvar(string source, string name, string units, const double **value, const double ***layvalue) {

	MapVar::iterator itVar;
	ClassVar *newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::VARG, Name, name, name, source, ID);

	MapPar::iterator itPar;
	//ClassPar *newPar; variable is unreferenced commenting out for now - jhs507
	long GetUnit;

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapgetvar.insert(Item);
		return 0;
	}

	case TBuild::DECL: {
		return 0;
	}

	case TBuild::INIT: {
		string::size_type indx2 = name.find('@');
		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;
			if (layvalue != NULL) *layvalue = (const double **)newVar->layvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (indx2 != string::npos &&  // look for group variable in fundamental module
			(itVar = Global::MapVars.find(source + " " + name.substr(0, indx2))) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;
			if (layvalue != NULL) *layvalue = (const double **)newVar->layvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->values;
				if (layvalue != NULL) *layvalue = (const double **)newVar->layvalues;

				PairVar Item = PairVar(Name + " " + name, newVar);
				Global::MapVarsGet.insert(Item);
				return GetUnit;
			}
		}
	} // case
	default:
		break;
	} // switch
	return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declgetvar(string source, string name, string units, const long **value, const long ***layvalue) {

	MapVar::iterator itVar;
	ClassVar *newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::VARG, Name, name, name, source, ID);

	MapPar::iterator itPar;
	//ClassPar *newPar; variable is unreferenced commenting out for now - jhs507
	long GetUnit;

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapgetvar.insert(Item);
		return 0;
	}

	case TBuild::DECL: {
		return 0;
	}

	case TBuild::INIT: {
		if (name == "Not_Used") // AKA does not handle int/double
			name = "Not_Used_int";

		string::size_type indx2 = name.find('@');
		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->ivalues;
			if (layvalue != NULL) *layvalue = (const long **)newVar->ilayvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (indx2 != string::npos &&  // look for group variable in fundamental module
			(itVar = Global::MapVars.find(source + " " + name.substr(0, indx2))) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->ivalues;
			if (layvalue != NULL) *layvalue = (const long **)newVar->ilayvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->ivalues;
				if (layvalue != NULL) *layvalue = (const long **)newVar->ilayvalues;

				PairVar Item = PairVar(Name + " " + name, newVar);
				Global::MapVarsGet.insert(Item);
				return GetUnit;
			}
		}
	} // case
	default:
		break;
	} // switch
	return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declobs(string name, TDim dimen, string help, string units, double **value) {

	MapVar::iterator itVar;
	ClassVar *newVar;
	ClassVar *thisVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, name, units);

	AKAhook(TAKA::OBSD, Name, name, name);

	int cnt = getdim(dimen);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {

		VandP VP; VP.PutV(variation_set); VP.PutP((int)TVISIBLE::USUAL);
		PairstrV Item2 = PairstrV((name + "#").c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		Global::Mapdeclobs.insert(Item);

		Global::DeclRootList->Add(string(ID.c_str()) + " " + (name + "#").c_str()); // to prevent input/output looping

		return(-1);
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + name + "#")) != Global::MapVars.end()) {

			thisVar = (*itVar).second;
			if (thisVar->dim < cnt) {
				thisVar->ReleaseM(); // releases everything
				thisVar->dim = cnt;
				if (thisVar->lay > 0) {
					thisVar->layvalues = new double *[thisVar->lay];
					for (int ii = 0; ii < thisVar->lay; ii++) thisVar->layvalues[ii] = new double[cnt];
				}
				thisVar->values = new double[cnt];     // CHECK ???
			}
			thisVar->dimen = dimen;  //warning resolved by Manishankar

			thisVar->DLLName = DLLName.c_str();
			thisVar->root = ID.c_str();

			return(-1);
		}

		newVar = new ClassVar(Name, name + "#", cnt, 0, NULL);

		newVar->varType = TVar::Float;
		newVar->help = help;
		newVar->units = units;
		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		newVar->values = new double[cnt];

		newVar->variation_set = variation_set;

		PairVar Item = PairVar(Name + " " + name + "#", newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case TBuild::INIT: {
		if ((itVar = Global::MapVars.find(Name + " " + name + "#")) != Global::MapVars.end()) {
			Global::DeclRootList->Add(string(ID.c_str()) + " " + (name + "#").c_str()); // to prevent input/output looping

			newVar = (*itVar).second;
			if (newVar->FileData) {
				*value = NULL;
				return(-(newVar->cnt - 1));
			}
			else {
				*value = newVar->values;
				newVar->cnt = cnt; // required if previously an observation file
				return(newVar->cnt - 1);
			}
		}
		else {
			CRHMException Except("Observation not found: " + Name + " " + name + "#", TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::getdimObs(string variable) {

	MapVar::iterator itVar;
	ClassVar *newVar;

	if ((itVar = Global::MapVars.find("obs " + variable)) != Global::MapVars.end()) {
		newVar = (*itVar).second;
		return(newVar->cnt);
	}
	else
		return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declreadobs(string variable, TDim dimen,
	string help, string units, const double **value, long HRU_index, bool optional, const double ***layvalue) {

	MapVar::iterator itVar;
	ClassVar *newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::OBSR, Name, variable, variable, declModule, ID);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		return(-1);
	}

	case TBuild::DECL: {

		if (dimen == TDim::NFREQ && layvalue == NULL) {
			LogError(CRHMException("NFREQ Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return(-1);
		}

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;

			if (newVar->varType == TVar::Read) { // used only once. Changes Read to ReadF
				Convert convert;
				convert.CheckUnitsObs(newVar->units, units, variable); // check original observation units

				newVar->values = NULL; // memory assigned in CRHM::INIT

				newVar->varType = TVar::ReadF;

				newVar->dimen = dimen;

				newVar->help = help;
				newVar->units = units;

				Item = PairVar(Name + " " + variable, newVar);
				Global::MapVars.insert(Item);
			}
			return(0);
		}

		if (optional)
			return(-1);

		newVar = new ClassVar("obs", variable, dimen, help, units, TVar::Float);

		newVar->varType = TVar::Float;

		Item = PairVar(declModule + variable, newVar);
		Global::MapVars.insert(Item);

		Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case TBuild::INIT: {

		newVar = NULL; // unchanged if nothing found

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) { // look for in declModule
			newVar = (*itVar).second;

			if ((newVar->varType == TVar::ReadF || newVar->varType == TVar::Read) && newVar->values == NULL) {
 				Convert convert; convert.CheckUnitsObs(newVar->units, units, variable); // check original observation units

				newVar->varType = TVar::ReadF;

				newVar->dimMax = Global::maxhru;
				newVar->values = new double[newVar->dimMax];

				newVar->help = help;
				newVar->units = units;

				Item = PairVar(Name + " " + variable, newVar);
				Global::MapVars.insert(Item);
			}
		}

		string::size_type indx = 0; // indicates if declared obs initalized to zero to prevent accidental declaration to npos - jhs507
 		if (itVar == Global::MapVars.end() || (!newVar->cnt && newVar->DLLName.empty())) { // look for with/without #  //warning resolved by Manishankar
			string variable2;

			indx = variable.find('#');
			if (indx == string::npos)
				variable2 = variable + '#';
			else
				variable2 = variable.erase(indx);

			if (GroupCnt) { // look for in Group
				if ((itVar = Global::MapVars.find(Name + ' ' + variable2)) != Global::MapVars.end())
					newVar = (*itVar).second;
			}
			else {  // look for in declModule
				if ((itVar = Global::MapVars.find(declModule + variable2)) != Global::MapVars.end())
					newVar = (*itVar).second;
			}
		}

		if (newVar == NULL) {
			if (optional) {
				*value = NULL;
				return(-1);
			}
			CRHMException Except("Observation not found " + declModule + ": " + variable, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}

		if (!newVar->cnt && newVar->DLLName.empty() && indx == string::npos) { //  && not declared module
			if (optional) {
				*value = NULL;

				PairVar Item = PairVar(Name + " " + variable, newVar);
				Global::MapObsGet.insert(Item);
				return(-1);
			}
			else {
				CRHMException Except("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'", TExcept::TERMINATE);
				LogError(Except);


				//added by Manishankar
				///////////////////////////////////
				string msgstring = "Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'";
				//CString cmsgstring(msgstring.c_str());
				//AfxMessageBox(cmsgstring);
				///////////////////////////////////

				throw Except;
			}
		}

		if (newVar->FileData) {
			if (dimen == TDim::NHRU)
				newVar->dim = nhru;
			else
				newVar->dim = newVar->cnt;
			addtoreadlist(newVar);  //insert in Obs read list
		}
		*value = newVar->values;

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapObsGet.insert(Item);

		if (HRU_index > 0)
			newVar->HRU_OBS_indexed = HRU_index - 1; // set up HRU_OBS index

		if (newVar->cnt > 0)
			return(newVar->cnt - 1); // simple obs
		else
			return(newVar->dim - 1);  // declared obs
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declreadobs(string variable, TDim dimen,  // needs updating. Is it ever used.
	string help, string units, const long **value, long HRU_index, bool optional, const long ***layvalue) {

	MapVar::iterator itVar;
	ClassVar *newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::OBSR, Name, variable, variable, declModule, ID);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		return(-1);
	}

	case TBuild::DECL: {

		if (dimen == TDim::NFREQ && layvalue == NULL) {
			LogError(CRHMException("NFREQ Array not defined for " + Name + " " + variable, TExcept::WARNING));
			return(-1);
		}

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if (newVar->varType == TVar::Read || newVar->varType == TVar::ReadI) {
				if (dimen == TDim::NFREQ && (newVar->lay == 0 || nhru > newVar->dim)) {
					newVar->ReleaseM(true);
					newVar->dim = nhru;
					newVar->dimMax = newVar->dim;
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->ilayvalues = new long *[newVar->lay];
					for (int ii = 0; ii < newVar->lay; ++ii)
						newVar->ilayvalues[ii] = new long[newVar->dimMax];
				}

				if (newVar->varType == TVar::Read || (newVar->varType == TVar::ReadF && nhru > newVar->dimMax)) {  //warning resolved by Manishankar
					if (newVar->ivalues != NULL)
						delete[] newVar->ivalues;
					else {
						Convert convert;
						convert.CheckUnitsObs(newVar->units, units, variable); // check original observation units
					}

					newVar->dimMax = max<long>(nhru, newVar->cnt);

					newVar->ivalues = new long[newVar->dimMax];

					newVar->varType = TVar::ReadI;

					newVar->help = help;
					newVar->units = units;

					Item = PairVar(Name + " " + variable, newVar);
					Global::MapVars.insert(Item);
				}
				else {
					Item = PairVar(Name + " " + variable, newVar);
					Global::MapVars.insert(Item);
				}
			}
			else if (newVar->dimen != dimen && dimen == TDim::NFREQ) { // upgrade t to t-freq
				newVar->ReleaseM(true);
				newVar->lay = Global::Freq;
				newVar->nfreq = true;
				newVar->ilayvalues = new long *[newVar->lay];
				for (int ii = 0; ii < newVar->lay; ii++)
					newVar->ilayvalues[ii] = new long[newVar->dim];
			}
			return(-1);
		}

		newVar = new ClassVar(declModule, variable, dimen, help, units, TVar::Int);

		newVar->varType = TVar::Int;

		Item = PairVar(declModule + variable, newVar);
		Global::MapVars.insert(Item);

		Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case TBuild::INIT: {

		newVar = NULL; // unchanged if nothing found

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) { // look for in declModule
			newVar = (*itVar).second;

			if (itVar == Global::MapVars.end() || (!newVar->cnt && newVar->DLLName.empty())) { // look for iwith/without #   //warning resolved by Manishankar
				string variable2;

				string::size_type indx = variable.find('#');
				if (indx == string::npos)
					variable2 = variable + '#';
				else
					variable2 = variable.erase(indx);

				if (GroupCnt) { // look for in Group
					if ((itVar = Global::MapVars.find(Name + ' ' + variable2)) != Global::MapVars.end())
						newVar = (*itVar).second;
				}
				else {  // look for in declModule
					if ((itVar = Global::MapVars.find(declModule + variable2)) != Global::MapVars.end())
						newVar = (*itVar).second;
				}
			}
		}

		if (newVar == NULL) {
			CRHMException Except("Observation not found " + declModule + ": " + variable, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}

		if (!newVar->cnt && newVar->DLLName.empty()) {
			if (optional) {
				*value = NULL;

				PairVar Item = PairVar(Name + " " + variable, newVar);
				Global::MapObsGet.insert(Item);
				return(-1);
			}
			else {
				CRHMException Except("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'", TExcept::TERMINATE);
				LogError(Except);

				//added by Manishankar
				///////////////////////////////////
				string msgstring = "Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'";
				//CString cmsgstring(msgstring.c_str());
				//AfxMessageBox(cmsgstring);
				///////////////////////////////////

				throw Except;
			}
		}

		newVar->No_ReadVar = 0;

		if (layvalue != NULL) {
			if (newVar->nfreq && newVar->lay != Global::Freq) {
				newVar->ReleaseM(true);
				newVar->lay = Global::Freq;
				newVar->nfreq = true;
				newVar->ilayvalues = new long *[newVar->lay];
				for (int ii = 0; ii < newVar->lay; ii++)
					newVar->ilayvalues[ii] = new long[newVar->dim];
			}

			*layvalue = (const long **)newVar->ilayvalues;
			newVar->UserFunct = &ClassVar::Intvl;
			newVar->FunKind = TFun::INTVL;
			newVar->FunctVar = newVar;
			addtofunctlist(newVar);  //insert in Obs read list
		}

		if (newVar->FileData) {
			newVar->dim = nhru;
			addtoreadlist(newVar);  //insert in Obs read list
		}

		*value = newVar->ivalues;

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapObsGet.insert(Item);

		if (HRU_index > 0)
			newVar->HRU_OBS_indexed = HRU_index - 1; // set up HRU_OBS index

		if (newVar->cnt > 0)
			return(newVar->cnt - 1); // simple obs
		else
			return(newVar->dim - 1);  // declared obs
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------

long ClassModule::declobsfunc(string obs, string variable, double **value, TFun typeFun, double ***layvalue, bool optional) {

	MapVar::iterator itVar;
	ClassVar *obsVar, *newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::OBSF, Name, obs, obs, declModule, ID);
	AKAhook(TAKA::VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(Name.c_str());
		//string units; local variable is not used - jhs507
		 
		for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap) {
			if (itMap->second.first == obs.c_str()) {
				//units = itMap->second.second; units is set here with a long value to a string but never used - jhs507
				break;
			}
		}

      		VandP VP; VP.PutV(variation_set); VP.PutP((int)TVISIBLE::DIAGNOSTIC);
		PairstrV Item2 = PairstrV(obs.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		Item2 = PairstrV(variable.c_str(), VP.both);
		Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		return(-1);
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(declModule + obs)) == Global::MapVars.end()) {
			LogError(CRHMException("function obs variable not declared: " + Name + " " + obs, TExcept::WARNING));
			return(-1);
		}

		obsVar = (*itVar).second;

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return(-1);
		}

		//Manishankar. Fstrings[typeFun] was getting out of index.
		//string help = obsVar->help + " <" + Fstrings[typeFun] + "> ";
		string help = obsVar->help + " <" + "> ";

		newVar = new ClassVar(Name, variable, nhru, help, obsVar->units, TVar::Float);

		newVar->dimMax = nhru; // added 04/16/13 (replacing t obs faulty)

		newVar->varType = TVar::Float;

		newVar->visibility = TVISIBLE::DIAGNOSTIC;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(0);
	}

	case TBuild::INIT: {
		itVar = Global::MapVars.find(Name + " " + variable);

		try
		{
			if ((itVar = Global::MapVars.find(declModule + obs)) != Global::MapVars.end()) {
				newVar = (*itVar).second;
				obsVar = (*itVar).second;

				if (!newVar) { // Applies to ppt, p etc. when building a new project with NO observations defined

					newVar = new ClassVar(Name, variable, nhru,
						obsVar->help + " <" + Fstrings[(int)typeFun] + "> ",
						obsVar->units, TVar::Float);

					newVar->dimMax = nhru;

					newVar->varType = TVar::Float;

					newVar->visibility = TVISIBLE::DIAGNOSTIC;

					newVar->variation_set = variation_set;

					newVar->DLLName = DLLName.c_str();
					newVar->root = ID.c_str();

					PairVar Item = PairVar(Name + " " + variable, newVar);
					Global::MapVars.insert(Item);
				}

				if (obsVar->FileData == NULL) {
					if (optional) {
						*value = NULL;
						return(-1);
					}
					else {
						CRHMException Except("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str() + "'. Requested by '" + Name.c_str() + "'", TExcept::TERMINATE);
						LogError(Except);
						throw Except;
					}
				}

				if (obsVar->FileData->Times != NULL) {
					CRHMException Except("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str() + "'", TExcept::TERMINATE);
					LogError(Except);
					throw Except;
				}

				if (typeFun == TFun::INTVL) {

					newVar->ReleaseM(false); // needs to release current values
					newVar->dim = max<long>(nhru, newVar->dim);
					newVar->dimMax = max<long>(newVar->dim, newVar->dimMax);
					newVar->lay = Global::Freq;

					newVar->layvalues = new double *[newVar->lay];
					*layvalue = newVar->layvalues;

					for (int ii = 0; ii < newVar->lay; ++ii)
						newVar->layvalues[ii] = new double[newVar->dimMax];

					newVar->values = newVar->layvalues[0]; // set non-zero - ReleaseM requires - NOP

					newVar->FileData = obsVar->FileData;
				}
				else if (nhru > newVar->dim) { // change of observation array size
					delete[] newVar->values;
					newVar->dimMax = nhru;
					newVar->values = new double[newVar->dimMax];
					newVar->dim = newVar->dimMax;
				}
				if (GroupCnt)
					newVar->CustomFunct = NULL; // Set by 'declobsfunc' for Groups. If simple set by 'addtoreadlist'

				switch (typeFun) {
				case TFun::FOBS:
					newVar->FunctVar = obsVar;
					newVar->FunKind = TFun::FOBS;
					newVar->FileData = obsVar->FileData;
					if (GroupCnt)
						newVar->No_ReadVar = 1;  // do not read observation
					break;
				case TFun::AVG:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Avg;
					newVar->FunKind = TFun::AVG;
					break;
				case TFun::MIN:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Min;
					newVar->FunKind = TFun::MIN;
					break;
				case TFun::MAX:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Max;
					newVar->FunKind = TFun::MAX;
					break;
				case TFun::DTOT:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Dtot;
					newVar->FunKind = TFun::DTOT;
					break;
				case TFun::TOT:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Tot;
					newVar->FunKind = TFun::TOT;
					break;
				case TFun::FIRST:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::First;
					newVar->FunKind = TFun::FIRST;
					break;
				case TFun::LAST:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Last;
					newVar->FunKind = TFun::LAST;
					break;
				case TFun::POS:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Pos;
					newVar->FunKind = TFun::POS;
					break;
				case TFun::INTVL:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Intvl;
					newVar->FunKind = TFun::INTVL;
					newVar->offset = newVar->FunctVar->offset;

					*layvalue = newVar->layvalues;
					break;
				default:
					break;
				}

				*value = newVar->values;

				newVar->HRU_OBS_indexed = obsVar->HRU_OBS_indexed;
				if (newVar->FunKind == TFun::FOBS)
					addtoreadlist(newVar);
				else if ((Global::RH_EA_obs == -1 && obs == "rh") || (Global::RH_EA_obs == -1 && obs == "ea") || Global::OBS_AS_IS || !(obs == "ea" || obs == "rh"))  //warning resolved by Manishankar
					addtofunctlist(newVar);
				return(obsVar->cnt - 1);
			}
			else {
				if (!optional) {
					CRHMException Except("Observation not found obs: " + obs, TExcept::TERMINATE);
					LogError(Except);
					throw Except;
				}
				else
					*value = NULL;
			}
		}
		catch (...) {
			//do nothing.
		}
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declobsfunc(string obs, string variable, long **value, TFun typeFun, bool optional) {

	MapVar::iterator itVar;
	ClassVar *obsVar, *newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::OBSF, Name, obs, obs, declModule, ID);
	AKAhook(TAKA::VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(Name.c_str());
		//string units; Units is set below with a long value into a string but never used - jhs507

		for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap) {
			if (itMap->second.first == obs.c_str()) {
				//units = itMap->second.second; //The value of units is never used - jhs507
				break;
			}
		}

		VandP VP; VP.PutV(variation_set); VP.PutP((int)TVISIBLE::DIAGNOSTIC);
		PairstrV Item2 = PairstrV(obs.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		Item2 = PairstrV(variable.c_str(), VP.both);
		Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		return(-1);
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(declModule + obs)) == Global::MapVars.end()) {
			LogError(CRHMException("function obs variable not declared: " + Name + " " + obs, TExcept::WARNING));
			return(-1);
		}

		obsVar = (*itVar).second;

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return(-1);
		}

		if (!obsVar->ivalues) {
			obsVar->ivalues = new long[obsVar->dim]; // TB 10/08/10
			obsVar->varType = TVar::ReadI;
		}

		newVar = new ClassVar(Name, variable, obsVar->dim,
			obsVar->help + " <" + Fstrings[(int)typeFun] + "> ",
			obsVar->units, TVar::Float);

		newVar->varType = TVar::Float;

		newVar->visibility = TVISIBLE::DIAGNOSTIC;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case TBuild::INIT: {
		itVar = Global::MapVars.find(Name + " " + variable);
		newVar = (*itVar).second;

		if ((itVar = Global::MapVars.find(declModule + obs)) != Global::MapVars.end()) {
			obsVar = (*itVar).second;

			if (obsVar->FileData == NULL) {
				if (optional) {
					LogError(CRHMException("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str() + "'. Requested by '" + Name.c_str() + "' (optional).", TExcept::WARNING));
					*value = NULL;
					return(-1);
				}
				else {
					CRHMException Except("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str() + "'. Requested by '" + Name.c_str() + "'", TExcept::TERMINATE);
					LogError(Except);
					throw Except;
				}
			}

			if (obsVar->FileData->Times != NULL) {
				CRHMException Except("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str() + "'", TExcept::TERMINATE);
				LogError(Except);
				throw Except;
			}

			if (obsVar->dim != newVar->dim) { // change of observation array size
				delete[] newVar->ivalues;
				newVar->ivalues = new long[obsVar->dim];
				newVar->dim = obsVar->dim;
			}

			switch (typeFun) {
			case TFun::AVG:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Avg;
				newVar->FunKind = TFun::AVG;
				break;
			case TFun::MIN:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Min;
				newVar->FunKind = TFun::MIN;
				break;
			case TFun::MAX:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Max;
				newVar->FunKind = TFun::MAX;
				break;
			case TFun::DTOT:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Dtot;
				newVar->FunKind = TFun::DTOT;
				break;
			case TFun::TOT:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Tot;
				newVar->FunKind = TFun::TOT;
				break;
			case TFun::FIRST:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::First;
				newVar->FunKind = TFun::FIRST;
				break;
			case TFun::LAST:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Last;
				newVar->FunKind = TFun::LAST;
				break;
			case TFun::POS:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Pos;
				newVar->FunKind = TFun::POS;
				break;
			default:
				break;
			}

			*value = newVar->ivalues;
			newVar->No_ReadVar = 0;
			newVar->HRU_OBS_indexed = obsVar->HRU_OBS_indexed;
			addtofunctlist(newVar);
			return (obsVar->cnt - 1);
		}
		else {
			CRHMException Except("Variable not found obs: " + obs, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------


long ClassModule::declputvar(string source, string name, string units, double **value, double ***layvalue) {

	MapVar::iterator itVar;
	ClassVar *newVar;
	long GetUnit;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::VARG, Name, name, name, source, ID);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapputvar.insert(Item);
		return 0;
	}

	case TBuild::DECL: {
		return 0;
	}

	case TBuild::INIT: {
		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;
			if (layvalue != NULL) (*layvalue) = newVar->layvalues; //const_cast<double **> (*layvalue) = newVar->layvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsPut.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->values;
				if (layvalue != NULL) (*layvalue) = newVar->layvalues;  //const_cast<double **> (*layvalue) = newVar->layvalues;

				PairVar Item = PairVar(Name + " " + name, newVar);
				Global::MapVarsPut.insert(Item);
				return GetUnit;
			}

			CRHMException Except("Wild variable not found: " + source + ' ' + name, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
		else {
			CRHMException Except("Variable not found: " + source + ' ' + name, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declputvar(string source, string name, string units, long **value, long ***layvalue) {

	MapVar::iterator itVar;
	ClassVar *newVar;
	long GetUnit;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::VARG, Name, name, name, source, ID);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapputvar.insert(Item);
		return 0;
	}

	case TBuild::DECL: {
		return 0;
	}

	case TBuild::INIT: {
		if (name == "Not_Used") // AKA does not handle int/double
			name = "Not_Used_int";

		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->ivalues;
			if (layvalue != NULL) (*layvalue) = newVar->ilayvalues;  //const_cast<long **> (*layvalue) = newVar->ilayvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsPut.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->ivalues;
				if (layvalue != NULL) (*layvalue) = newVar->ilayvalues;  //const_cast<long **> (*layvalue) = newVar->ilayvalues;

				PairVar Item = PairVar(Name + " " + name, newVar);
				Global::MapVarsPut.insert(Item);
				return GetUnit;
			}

			CRHMException Except("Wild variable not found: " + source + ' ' + name, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
		else {
			CRHMException Except("Variable not found: " + source + ' ' + name, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return(-1);
}

//---------------------------------------------------------------------------
void ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName) { // OBSD, PARD, VARD

	Mapstr2::iterator it; // holds NewName
	string ID = AKAstrings[(int)type] + ' ' + module + ' ' + OrgName;
	bool Added = false;
	bool Explicit = false;

	if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
		NewName = (*it).second;
		NewName = NewName.substr(0, NewName.find(' '));
		Explicit = true;
	}
	else {
		if (type == TAKA::OBSD) {
			string::size_type idx = ID.size();

			if (ID[idx - 1] == '#')
				ID.erase(idx, 1);
			else {
				ID.insert(idx, "#");
				Added = true;
			}

			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
				NewName = (*it).second;
				NewName = NewName.substr(0, NewName.find(' '));
				if (Added)
					NewName = NewName.substr(0, NewName.size() - 1);
				Explicit = true;
			}
			else
				Added = false;
		}
		else if (GroupCnt && type == TAKA::VARD) {
			string A;
			Common::GroupEnding(A, GroupCnt);
			NewName.append(A);
			ID = AKAstrings[(int)type] + ' ' + module + ' ' + NewName;
			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
				NewName = (*it).second;
				NewName = NewName.substr(0, NewName.find(' '));
				Explicit = true;
			}
		}
		else if (StructCnt && type == TAKA::VARD) {
			string A("@`");
			A[1] += (char) StructCnt;
			NewName.append(A);
		}
	}

	if (Global::ReportList && Explicit) {
		string ID = AKAstrings[(int)type] + ' ' + module + ' ' + OrgName;
		if (Added)
			NewName.insert(NewName.size(), "#");
		if (Explicit)
			NewName.insert(NewName.size(), " **** explicit");
		Global::ReportList->Add((ID + " ---> " + NewName).c_str());
	}
}

//---------------------------------------------------------------------------
void ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName, string & source, string base) { // OBSR, OBSF, VARG

	Mapstr2::iterator it; // holds NewName AND source

	
	OUTCOME Outcome = OUTCOME::None;

	TAKA typeL = type; // fudge until AKA screen fixed
	if (type == TAKA::OBSF)
		type = TAKA::OBSR;

	string Try;
	string ID = AKAstrings[(int)type] + ' ' + module + ' ' + OrgName;

	if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) { // search AKA list
		Try = (*it).second;
		Try = Try.substr(0, Try.find(' '));
		if (Global::DeclRootList->IndexOf(string(base.c_str()) + " " + Try.c_str()) > -1) { // looping redirection
			if (typeL == TAKA::OBSF)
				Outcome = OUTCOME::IgnoreObsFunct;
			else
				Outcome = OUTCOME::IgnoreObs;
		}
		else if (GroupCnt && type == TAKA::VARG) {
			string A;
			Common::GroupEnding(A, GroupCnt);
			NewName.append(A);
			ID = AKAstrings[(int)type] + ' ' + module + ' ' + NewName;
			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) { // search AKA list for GROUP name
				Try = (*it).second;
				Try = Try.substr(0, Try.find(' '));
				NewName = (*it).second;
				NewName = NewName.substr(0, NewName.find(' '));
				Outcome = OUTCOME::Implicit;
			}
		}
		else if (typeL == TAKA::OBSF && Try[Try.size() - 1] == '#') { // declared observation and daily function
			Outcome = OUTCOME::IgnoreObsFunct;
		}
		else if (type == TAKA::OBSR) { //  observation   !!! was typeL 08/20/10
			if (Try[Try.size() - 1] == '#') {
				if (Global::DeclRootList->IndexOf(string(base.c_str()) + " " + Try.c_str()) > -1) {
					Outcome = OUTCOME::IgnoreObs;
				}
			}

			NewName = (*it).second;
			NewName = NewName.substr(0, NewName.find(' '));
			source = (*it).second;
			source = source.substr(source.find(' ') + 1) + ' ';
			Outcome = OUTCOME::Explicit;
		}
		else if (type == TAKA::VARG) { // handle read operation
			NewName = (*it).second;
			NewName = NewName.substr(0, NewName.find(' '));
			source = (*it).second;
			source = source.substr(source.find(' ') + 1);
			Outcome = OUTCOME::Explicit;
		}
	} // Above found in AKA table
	else {
		if (GroupCnt && typeL == TAKA::OBSR) { // use declared observation in same group

			if ((Global::MapVars.find("obs " + OrgName)) != Global::MapVars.end()) { // look for as observation
				NewName = OrgName;
				source = "obs ";
				Try = NewName;
				Outcome = OUTCOME::Implicit;
			}
			else {
				string mod_var = ID.substr(ID.find(' ') + 1) + '#';

				if ((Global::MapVars.find(mod_var)) != Global::MapVars.end()) {
					NewName = OrgName + '#';
					source = module + ' ';
					Try = NewName;
					Outcome = OUTCOME::Implicit;
				}
			}
		}
		else if ((GroupCnt || StructCnt) && type == TAKA::VARG) {
			string A;
			if (GroupCnt) {
				Common::GroupEnding(A, GroupCnt);
			}
			if (StructCnt) {
				Common::GroupEnding(A, StructCnt);
			}
			NewName.append(A);
			ID = AKAstrings[(int)type] + ' ' + module + ' ' + NewName;
			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
				Try = (*it).second;
				Try = Try.substr(0, Try.find('@'));
				if (Global::DeclRootList->IndexOf(string(base.c_str()) + " " + Try.c_str()) > -1) {
					Outcome = OUTCOME::IgnoreVar;
				}
				else {
					NewName = (*it).second;
					NewName = NewName.substr(0, NewName.find(' '));
					Outcome = OUTCOME::Implicit;
				}
			}
		}
	}

	ID = AKAstrings[(int)typeL] + " (" + base + ") " + module + " -> " + OrgName + ' ';
	switch (Outcome) {
	case OUTCOME::IgnoreObs:
		LogMessage(string(ID + " *** AKA warning, not changed to *** " + source + "->" + Try).c_str());
		break;
	case OUTCOME::IgnoreObsFunct:
		LogMessage(string(ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str());
		break;
	case OUTCOME::IgnoreVar: // VARG
		LogMessage(string(ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str());
		break;
	default:
		break;
	} // switch

	if (Global::ReportList && Outcome != OUTCOME::None) {
		string reason = "";
		switch (Outcome) {
		case OUTCOME::Explicit:
			source = (ID + " changed to " + source + "-> " + Try).c_str();
			reason = " *** Explicit *** ";
			break;
		case OUTCOME::Implicit:
			source = (ID + " changed to " + source + "-> " + Try).c_str();
			reason = " *** Implicit *** ";
			break;
		case OUTCOME::IgnoreObs:
			source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
			reason = " *** source module AKA observation redirection would loop output to input";
			break;
		case OUTCOME::IgnoreObsFunct:
			source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
			reason = " *** daily function cannot be a declared observation";
			break;
		case OUTCOME::IgnoreVar: // VARG
			source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
			reason = " *** source module AKA variable redirection would loop output to input";
			break;
		default:
			break;
		} // switch

		Global::ReportList->Add((source + reason).c_str());
	}
}

//---------------------------------------------------------------------------
void ClassModule::InitReadObs(void) {

	// called by TMain::RunClick to clear storage

	ReadListN->Clear();
	FunctListN->Clear();
}

//---------------------------------------------------------------------------
void ClassModule::ReadObs(bool Reset) {

	// called by TMain::RunClick from within 'run loop'
	// Order in read lists same as in OurModuleList.
	// module can be in FunctListN without being in ReadListN.

	static long p;
	static long pN;
	static long LastGroup; // limits calls to pre_run

	if (Reset) {
		p = 0;
		pN = 0;
		LastGroup = -1;
	}

	if (Global::DTindx%Global::Freq == 0) { // only at start of day
		while (pN != FunctListN->Count && FunctListN->Strings[pN] == Name.c_str()) {

			/*TStringList test1 = FunctListN->Objects[pN];
			auto *test2 = &test1;
			ClassVar *P = (ClassVar*)test2;*/

			ClassVar *P = (ClassVar*)FunctListN->array[pN].Object;

			P->dim = nhru; // check if necessary. Group?

			if (P->FunctVar->FileData->GoodDay)
			{
				(P->*(P->UserFunct))();

				//manishankar. this is used for resolving the address related issue.
				if (P->name == "t")
				{
					this->t_layvalues = P->layvalues;
				}
				else if (P->name == "rh")
				{
					this->rh_layvalues = P->layvalues;
				}
			}

			if (P->CustomFunct) // execute any extra features except for nfreq observations   && !P->nfreq
				(P->*(P->CustomFunct))(this); // do_t_day, do_rh_day, do_ea_day, do_t, do_p,  do_ppt or Nothing

			++pN;
		}
	}

	while (p < ReadListN->Count && ((ReadListN->Strings[p] == Name.c_str()) || GroupCnt == 0)) { //  && ReadListN->strings[p] == "obs"
		ClassVar *P = (ClassVar*)ReadListN->array[p].Object;
		P->dim = nhru; // check if necessary. Group?

		if (P->module == "obs" || (GroupCnt && !P->No_ReadVar))
			P->ReadVar();

		if (P->CustomFunct) // execute any extra features for t etc
			(P->*(P->CustomFunct))(this); // do_t, do_p or Nothing

		++p;
	}
}
//---------------------------------------------------------------------------

bool ClassModule::ReadAheadObs(long inc) {

	// called by a module::run from within 'run loop'

	if (Global::DTindx + inc >= Global::DTmax || Global::DTindx + inc < Global::DTmin)
		return false;

	long CurrentDTindx = Global::DTindx;
	TDateTime CurrentDTnow = Global::DTnow;

	Global::DTindx += inc;
	Global::DTnow = Global::DTstart + Global::Interval*((long long)Global::DTindx + 1ll);

	long p = 0;

	while (p < ReadListN->Count) {
		ClassVar *P = (ClassVar*)ReadListN->array[p].Object;
		if (P->FileData->GoodInterval)
			P->ReadVar();
		++p;
	}

	if (Global::DTindx%Global::Freq == 0) {
		p = 0;
		while (p < FunctListN->Count && FunctListN->Strings[p] == Name.c_str()) {
			ClassVar *P = (ClassVar*)FunctListN->array[p].Object;
			if (P->FunctVar->FileData->GoodDay)
				(P->*(P->UserFunct))();
			++p;
		}
	}

	Global::DTindx = CurrentDTindx;
	Global::DTnow = CurrentDTnow;

	return true;
}

//---------------------------------------------------------------------------
bool ClassModule::ReadAheadObsMacro(long inc) {

	// called by 'macros'. ReadAheadObsMacro(0) must be called at end to reset Global::DTnow

	if (Global::DTindx + inc >= Global::DTmax || Global::DTindx + inc < Global::DTmin)
		return false;

	long CurrentDTindx = Global::DTindx;
	long **Save_HRU_obs = Global::HRU_OBS;

	Global::DTindx += inc;
	Global::DTnow = Global::DTstart + Global::Interval*((long long)Global::DTindx + 1ll);

	long p = 0;

	while (p < ReadListN->Count) {
		ClassVar *P = (ClassVar*)ReadListN->array[p].Object;
		if (P->FileData->GoodInterval)
			P->ReadVar();
		++p;
	}

	if (Global::DTindx%Global::Freq == 0) {
		p = 0;
		while (p < FunctListN->Count) {
			ClassVar *P = (ClassVar*)FunctListN->array[p].Object;
			if (P->FunctVar->FileData->GoodDay)
				(P->*(P->UserFunct))();
			++p;
		}
	}

	Global::DTindx = CurrentDTindx; // has to be restored for INC
	Global::HRU_OBS = Save_HRU_obs; // needs restore

	return true;
}

//---------------------------------------------------------------------------

bool ClassModule::WriteAheadObsMacro(long inc) {

	// called by 'macros'

	if (Global::DTindx + inc >= Global::DTmax || Global::DTindx + inc < Global::DTmin)
		return false;

	long CurrentDTindx = Global::DTindx;

	Global::DTindx += inc;

	long p = 0;

	while (p < ReadListN->Count) {
		ClassVar *P = (ClassVar*)ReadListN->array[p].Object;
		if (P->FileData->GoodInterval)
			P->WriteVar();
		++p;
	}

	Global::DTindx = CurrentDTindx; // has to be restored for INC

	return true;
}

//---------------------------------------------------------------------------
void ClassModule::DelReadObs(void) {

	// called by TMain::RunClick to clear storage

	ReadListN->Clear();
	FunctListN->Clear();
}

//---------------------------------------------------------------------------
bool ClassModule::AnyOne(double *Data, int Cnt, double Val) {

	if (Data == NULL) // remove later!
		return false;
	for (int ii = 0; ii < Cnt; ++ii)
		if (Data[ii] != Val) return true;
	return false;
}

//---------------------------------------------------------------------------
bool ClassModule::UsingObservations(void) {

	if (ReadListN->Count || FunctListN->Count)
		return true;
	else
		return false;
}

//---------------------------------------------------------------------------
void ClassModule::addtoreadlist(ClassVar *newVar) { // BuildFlag = crhm::init

													// called by ClassModule::declreadobs INIT to add observation

	long p = 0;
	ClassVar *P;
	//string::size_type indx; variable is unreferenced commenting out for now - jhs507

	while (p < ReadListN->Count && GroupCnt == 0) { // duplicates possible in simple projects
		P = (ClassVar*)ReadListN->array[p].Object;
		if (newVar == P) {
			if (this->Name == this->NameRoot) // simple project
				return;
		}
		p++;
	}

	if (((Global::DTmax - Global::DTmin) / Global::Freq + newVar->FileData->Dt1 > newVar->FileData->Dt2) && !newVar->FileData->Times) {
		CRHMException TExcept((string("Observation file '") + string(newVar->FileData->DataFileName.c_str()) + "' shorter than model run!").c_str(), TExcept::WARNING);
		LogError(TExcept);
	}

	if (GroupCnt) // Group
		ReadListN->AddObject(Name.c_str(), (TObject*)newVar); // add call to ReadVar
	else
		ReadListN->AddObject(newVar->module.c_str(), (TObject*)newVar); // add call to ReadVar

	newVar->CustomFunct = NULL; // Set by 'declobsfunc' for Groups. If simple set by 'addtoreadlist'

	if (!Global::OBS_AS_IS) {
		string::size_type idx = newVar->name.find('@');
		string root_var;
		if (idx != string::npos)
			root_var = newVar->name.substr(0, idx);

		if (newVar->name == "t_max" || newVar->name == "t_min") {
			if (AnyOne(Global::Warming_t, nhru, 0.0)) {
				newVar->CustomFunct = &ClassVar::do_t_Clim;
				newVar->CustomFunctName = "do_t_Clim";
			}
			else {
				newVar->CustomFunct = &ClassVar::do_t;
				newVar->CustomFunctName = "do_t";
			}
		}
		else if ((!GroupCnt && newVar->name == "p") || (GroupCnt && root_var == "p")) {  //warning resolved by Manishankar
			if (AnyOne(Global::Warming_p, nhru, 1.0)) {
				newVar->CustomFunct = &ClassVar::do_p_Clim;
				newVar->CustomFunctName = "do_p_Clim";
			}
			else {
				newVar->CustomFunct = &ClassVar::do_p;
				newVar->CustomFunctName = "do_p";
			}
		}
	} // !Global::OBS_AS_IS
}

//---------------------------------------------------------------------------
void ClassModule::addtofunctlist(ClassVar *newVar) {

	// called by ClassModule::declobsfunc INIT to add observation function

	long p = 0;
	ClassVar *P;
	string::size_type indx;

	while (p < FunctListN->Count) {
		P = (ClassVar*)FunctListN->array[p].Object;

		if (newVar == P) {
			if (this->Name == this->NameRoot && GroupCnt == 0) // duplicates possible in simple projects
				return;
		}

		p++;
	}

	FunctListN->AddObject(Name.c_str(), (TObject*)newVar);

	if (NameRoot == "obs" || Name == "obs") { // handle vapour pressure

		string RootName = newVar->name;
		if (indx = RootName.find("@"), indx != std::string::npos)
			RootName = newVar->name.substr(0, indx);

		if (!Global::OBS_AS_IS) {
			if (RootName == "Tday") {
				if (AnyOne(Global::Warming_t, nhru, 0.0)) {
					newVar->CustomFunct = &ClassVar::do_t_day_Clim;
					newVar->CustomFunctName = "do_t_day_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_t_day;
					newVar->CustomFunctName = "do_t_day";
				}
			}
			else if (RootName == "RHday") {
				if (AnyOne(Global::Warming_t, nhru, 0.0)) {
					newVar->CustomFunct = &ClassVar::do_rh_day_Clim;
					newVar->CustomFunctName = "do_rh_day_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_rh_day;
					newVar->CustomFunctName = "do_rh_day";
				}
			}
			else if (RootName == "EAday") {
				if (!AnyOne(Global::Warming_t, nhru, 0.0)) {
					newVar->CustomFunct = &ClassVar::do_ea_day;
					newVar->CustomFunctName = "do_ea_day";
				}
			}
			else if (RootName == "t_min" || newVar->name == "t_max") {
				if (AnyOne(Global::Warming_t, nhru, 0.0)) {
					newVar->CustomFunct = &ClassVar::do_t_Clim;
					newVar->CustomFunctName = "do_t_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_t;
					newVar->CustomFunctName = "do_t";
				}
			}
			else if (RootName.substr(0, 4) == "pptD") {
				if (AnyOne(Global::Warming_p, nhru, 1.0)) {
					newVar->CustomFunct = &ClassVar::do_ppt_Clim;
					newVar->CustomFunctName = "do_ppt_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_ppt;
					newVar->CustomFunctName = "do_ppt";
				}
			}
		} // !Global::OBS_AS_IS
		else
			newVar->CustomFunct = NULL;
	} // NameRoot == "obs" || Name == "obs"
}




long ClassModule::getdim(TDim dimen) {
	MapDim::iterator itDim;
	string s;

	switch (dimen) {

	case TDim::BASIN:
		return ((int)TDim::ONE);

	case TDim::ONE:
	case TDim::TWO:
	case TDim::THREE:
	case TDim::FOUR:
	case TDim::FIVE:
	case TDim::SIX:
	case TDim::SEVEN:
	case TDim::EIGHT:
	case TDim::NINE:
	case TDim::TEN:
	case TDim::ELEVEN:
	case TDim::TWELVE:
		return ((int)dimen);

	case TDim::NHRU:
		if (nhru)
			return (nhru);
		else
			return (Global::nhru);

	case TDim::NOBS:
		return (Global::nhru);

	case TDim::NLAY:
		return (Global::nlay);

	default:
		return (-1);
	}
}

//---------------------------------------------------------------------------
TAKA AKAtype(string type) {

	TAKA Type = TAKA::AKAERROR;

	for (int ii = (int) TAKA::VARG; ii < (int) TAKA::AKAEND; ++ii)
		if (type == AKAstrings[ii]) {
			Type = (TAKA)ii;
			break;
		}
	return Type;
}

//---------------------------------------------------------------------------
bool ClassModule::Variation_Skip(void) {

	if ((Global::BuildFlag == TBuild::BUILD && variation == 0) ||                    // for Build screen   //warning resolved by Manishankar
		((variation_set & 2048) != 0 && variation == 0) ||                        // handles VARIATION_0
		(variation_set & 4096) != 0 ||                        // handles VARIATION_0
		(variation_set == 0) ||                                                // handles VARIATION_ORG
		(variation_set & variation) != 0)                                       // handles #1, #2, #4 etc.
		return false; // add
	else
		return true; // skip
}

//---------------------------------------------------------------------------
long ClassModule::declputparam(string source, string param, string units, double **value, double ***layvalue) {

	MapPar::iterator itPar;
	ClassPar *newPar = NULL;

	if (Variation_Skip()) {
		*value = NULL;
		return -1;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(TAKA::PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return -1;
	}

	case TBuild::DECL: { // only finds groups

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			newPar->Inhibit_share = 1;
			return 0;
		}

		if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru)
				newPar = (*itPar).second;
			newPar->Inhibit_share = 1;
			return 0;
		}

		newPar = new ClassPar(string(Name.c_str()), string(param), TDim::NHRU, "", 0, 0, "", units, TVar::Float);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = TVISIBLE::USUAL;

		if (this->GroupCnt)
			newPar->Inhibit_share = 2;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return -1;
	}

	case TBuild::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*value = newPar->values;
					if (layvalue != NULL)
						(*layvalue) = newPar->layvalues;  //const_cast<double **> (*layvalue) = newPar->layvalues;
				}
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				//          if(newPar->Inhibit_share != 2){ // 2 means no declare, ie not used.
				*value = newPar->values;
				if (layvalue != NULL)
					(*layvalue) = newPar->layvalues;  //const_cast<double **> (*layvalue) = newPar->layvalues;
													  //          }
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*value = newPar->values;
					if (layvalue != NULL)
						(*layvalue) = newPar->layvalues;  //const_cast<double **> (*layvalue) = newPar->layvalues;
				}
			}
			else if ((newPar = ClassParFindPar(param))) {
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*value = newPar->values;
					if (layvalue != NULL)
						(*layvalue) = newPar->layvalues;  //const_cast<double **> (*layvalue) = newPar->layvalues;
				}
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
				LogError(Except);
				throw Except; // does not return
			}
			return 0;
		}
	} // case
	default:
		break;
	} // switch

	return 0;  //warning resolved by Manishankar
}

//---------------------------------------------------------------------------
long ClassModule::declgetparam(string source, string param, string units, const double **value, const double ***layvalue) {

	MapPar::iterator itPar;
	ClassPar *newPar;

	if (Variation_Skip()) {
		*value = NULL;
		return -1;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(TAKA::PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return -1;
	}

	case TBuild::DECL: {
		return -1;
	}

	case TBuild::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*value = newPar->values;
				if (layvalue != NULL)
					*layvalue = (const double **)newPar->layvalues;
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*value = (const double *)newPar->values;
				if (layvalue != NULL)
					*layvalue = (const double **)newPar->layvalues;
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*value = (const double *)newPar->values;
				if (layvalue != NULL)
					*layvalue = (const double **)newPar->layvalues;
			}
			else if ((newPar = ClassParFindPar(param))) {
				*value = newPar->values;
				if (layvalue != NULL)
					*layvalue = (const double **)newPar->layvalues;
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
				LogError(Except);
				throw Except; // does not return
			}
			return 0;
		}
	} // case
	default:
		break;
	} // switch
	return 0;  //warning resolved by Manishankar
}
//---------------------------------------------------------------------------
long ClassModule::FindModule_from_parameter(string source, string param) {

	MapPar::iterator itPar;
	ClassPar *newPar = NULL;

	variation_max = variation_max | variation_set;

	AKAhook(TAKA::PARD, Name, param, param); // handles explicit rename - redundant now ?

	if (source[0] != '*') {
		if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
		}
	}
	else {
		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
		}
		else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
		}
		else if ((newPar = ClassParFindPar(param))) {
		}
		else {
			CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
			LogError(Except);
			throw Except; // does not return
		}
	}

	if (GroupCnt) {
		long ii = Global::OurModulesList->IndexOf(Name.c_str()); // find group macro
																 //ClassMacro* macro = (ClassMacro*)Global::OurModulesList->Objects[ii]; // access it
																 //long jj = macro->GrpstringList->IndexOf(newPar->basemodule.c_str()); // find module in list
																 //return    (long)macro->GrpstringList->Objects[jj]; // return object
	}
	else {
		long ii = Global::OurModulesList->IndexOf(newPar->basemodule.c_str());
		return    (long)Global::OurModulesList->array[ii].Object;
	}

	CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
	LogError(Except);
	throw Except; // does not return
}
//---------------------------------------------------------------------------
long ClassModule::declputparam(string source, string param, string units, long **ivalue, long ***ilayvalue) {

	MapPar::iterator itPar;
	ClassPar *newPar = NULL;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return -1;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(TAKA::PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return -1;
	}

	case TBuild::DECL: {
		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			newPar->Inhibit_share = 1;
			return 0;
		}

		if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru)
				newPar = (*itPar).second;
			newPar->Inhibit_share = 1;
			return 0;
		}

		newPar = new ClassPar(string(Name.c_str()), string(param), TDim::NHRU, "", 0, 0, "", units, TVar::Int);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = TVISIBLE::USUAL;

		newPar->Inhibit_share = 2;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return -1;
	}

	case TBuild::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*ivalue = newPar->ivalues;
					if (ilayvalue != NULL)
						(*ilayvalue) = newPar->ilayvalues;  //const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
				}
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					(*ilayvalue) = newPar->ilayvalues;  //const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*ivalue = newPar->ivalues;
					if (ilayvalue != NULL)
						(*ilayvalue) = newPar->ilayvalues;  //const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
				}
			}
			else if ((newPar = ClassParFindPar(param))) { // handles other module
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*ivalue = newPar->ivalues;
					if (ilayvalue != NULL)
						(*ilayvalue) = newPar->ilayvalues;  //const_cast<long **> (*ilayvalue) = newPar->ilayvalues;
				}
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
				LogError(Except);
				throw Except;
			}
			return 0;
		}
	} // case
	default:
		break;
	} // switch
	return 0; //warning resolved by Manishankar
}

//---------------------------------------------------------------------------
void ClassModule::declgetparam(string source, string param, string units, const long **ivalue, const long ***ilayvalue) {

	MapPar::iterator itPar;
	ClassPar *newPar;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(TAKA::PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return;
	}

	case TBuild::DECL: {
		return;
	}

	case TBuild::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long **)newPar->ilayvalues;
				return;
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = (const long *)newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long **)newPar->ilayvalues;
				return;
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long **)newPar->ilayvalues;
				return;
			}
			else if ((newPar = ClassParFindPar(param))) { // handles other module
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long **)newPar->ilayvalues;
				return;
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TExcept::TERMINATE);
				LogError(Except);
				throw Except;
			}
		}
	} // case
	default:
		break;
	} // switch
}

//---------------------------------------------------------------------------
ClassModule* ClassModule::link(string Module) {

	if (Name == Module.c_str())
		return NULL; // self

	int jj = Global::OurModulesList->IndexOf(Module.c_str());

	if (jj == -1)
		return NULL;
	else
		return (ClassModule*)Global::OurModulesList->array[jj].Object;
}
