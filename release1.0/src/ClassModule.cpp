
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
#include "Common.h"


//---------------------------------------------------------------------------

//#pragma package(smart_init)
//#pragma init_seg

using namespace std;

TStringList* ReadListN = new TStringList;

TStringList* FunctListN = new TStringList;

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
		AA[2] += log(thisModule->variation) / log(2) + 1;
		S += AA;
	}
	return S;
}

//---------------------------------------------------------------------------
void ClassModule::initbase(void) {



	Global::BuildFlag = CRHM::INIT;


	MapPar::iterator itPar;
	ClassPar* newPar;



	if (Var_NDEFN_cnt) {

		Var_loop_lay_table = new float** [Var_NDEFN_cnt]; // define [#Var][#layers]

		for (long jj = 0; jj < Var_NDEFN_cnt; ++jj) {
			Var_loop_lay_table[jj] = new float* [nlay];
		}

		Var_loop_lay_value = new float* [Var_NDEFN_cnt]; // define [#Var]
		for (long jj = 0; jj < Var_NDEFN_cnt; ++jj)
			Var_loop_lay_value[jj] = new float[nhru];
	}
	else {

		Var_loop_lay_table = NULL;
		Var_loop_lay_value = NULL;
	}



	if (Par_NDEFN_cnt) {
		Par_loop_lay_table = new float** [Par_NDEFN_cnt];
		for (long jj = 0; jj < Par_NDEFN_cnt; ++jj) {
			Par_loop_lay_table[jj] = new float* [nlay];
			for (long ll = 0; ll < nlay; ++ll)
				Par_loop_lay_table[ll] = new float* [nhru];
		}
		Par_loop_lay_value = new float* [Par_NDEFN_cnt];
		for (long jj = 0; jj < Par_NDEFN_cnt; ++jj) {
			Par_loop_lay_value[jj] = new float[nlay];
			for (long ll = 0; ll < nlay; ++ll)
				Par_loop_lay_value[ll] = new float[nhru];
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
	string units, float** value, float*** layvalue, bool PointPlot) {

	MapVar::iterator itVar;
	ClassVar* newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}
	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		PeerVar = queryvar.c_str();
		return 0;
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return 0;
		}

		if (layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
			return -1;
		}

		if (!Global::GroupCntTrk) {
			LogError(CRHMException("No groups defined " + Name + " " + variable, WARNING));
			return -1;
		}
		newVar = new ClassVar(Name, variable, CRHM::NREB, help, units, CRHM::Float, PointPlot, nhru);

		newVar->varType = CRHM::Float;

		newVar->variation_set = variation_set;

		newVar->InGroup = GroupCnt;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return 0;
	}

	case CRHM::INIT: {
		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;

			for (int ii = 0; ii < nhru; ++ii)
				newVar->layvalues[ii] = NULL;

			if (!Global::GroupCntTrk) // no groups in model!
				return 0;

			long querycnt = 0;
			for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
				ClassVar* foundVar = (*itVar).second;
				if (newVar != NULL) {
					if (foundVar->FileData)
						continue;
					string S = foundVar->name;
					string::size_type indx = S.find('@');
					if (indx != string::npos) {
						string N = S.substr(indx + 1);
						S = S.erase(indx);
						if (S == queryvar) {
							newVar->layvalues[querycnt] = foundVar->values;
							newVar->values[querycnt] = foundVar->dim;
							++querycnt;
						} // if - this queryvar
					} // if - found group
				} // if - not null, is it possible?
			} // for
			*layvalue = newVar->layvalues; // return address
			return querycnt;
		}
		else {
			CRHMException Except("variable not found: " + Name + ' ' + variable, TERMINATE);
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
void ClassModule::decldiag(string variable, CRHM::TDim dimen,
	string help, string units, float** value, float*** layvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, false, Local);
}
//---------------------------------------------------------------------------

void ClassModule::decldiag(string variable, CRHM::TDim dimen,
	string help, string units, long** value, long*** ilayvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, false, Local);

}
//---------------------------------------------------------------------------

void ClassModule::declstatdiag(string variable, CRHM::TDim dimen,
	string help, string units, float** value, float*** layvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == CRHM::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------
void ClassModule::declstatdiag(string variable, CRHM::TDim dimen,
	string help, string units, long** value, long*** ilayvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == CRHM::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------
void ClassModule::declstatvar(string variable, CRHM::TDim dimen,
	string help, string units, float** value, float*** layvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == CRHM::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------
void ClassModule::declstatvar(string variable, CRHM::TDim dimen,
	string help, string units, long** value, long*** ilayvalue, const int dim, bool PointPlot, CRHM::TVISIBLE Local) {

	declvar(variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);

	if (Global::BuildFlag == CRHM::BUILD) {
		string s = string(Name.c_str()) + " " + variable.c_str();

		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(s, VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclstat.insert(Item);
	}
};

//---------------------------------------------------------------------------

void ClassModule::declvar(string variable, CRHM::TDim dimen, string help,
	string units, float** value, float*** layvalue, const int dim, bool PointPlot, bool StatVar, CRHM::TVISIBLE Local) {
	MapVar::iterator itVar;
	ClassVar* newVar;
	string Orgvariable = variable;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(variable.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);

		Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

		return;
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return;
		}

		if (dimen == CRHM::NLAY && layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
			return;
		}

		if (dimen == CRHM::NDEFN) // save for lay loop
			++Var_NDEFN_cnt;

		newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Float, PointPlot, nhru, dim);

		newVar->varType = CRHM::Float;

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

	case CRHM::INIT: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if (newVar->layvalues != NULL) {
				if (dimen == CRHM::NFREQ && newVar->lay != Global::Freq) {
					newVar->nfreq = true;
					newVar->lay = Global::Freq;
					newVar->ReleaseM(true);
					newVar->layvalues = new float* [newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->layvalues[ii] = new float[newVar->dim];
				}
				if ((dimen == CRHM::NLAY || dimen == CRHM::NDEFN) && newVar->lay != dim) {
					long JJ = newVar->lay;
				}

			}

			if (layvalue) // TB 10/30/10
				*layvalue = newVar->layvalues;

			*value = newVar->values; // TB 10/07/10

			if (dimen == CRHM::NDEF) { // save for lay loop
				Var_loop_lay_table[Var_NDEFN_cnt] = newVar->layvalues;
				Var_loop_lay_value[Var_NDEFN_cnt++] = newVar->values;
			}

			Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

			return;
		}
		else {
			CRHMException Except("variable not found: " + Name + ' ' + variable, TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void ClassModule::declvar(string variable, CRHM::TDim dimen, string help,
	string units, long** ivalue, long*** ilayvalue, const int dim, bool PointPlot, bool StatVar, CRHM::TVISIBLE Local) {

	MapVar::iterator itVar;
	ClassVar* newVar;
	string Orgvariable = variable;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	AKAhook(VARD, Name, variable, variable);

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(variable.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);

		Global::DeclRootList->Add(string(ID.c_str()) + " " + Orgvariable.c_str()); // to prevent input/output looping

		return;
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return;
		}

		if (dimen == CRHM::NLAY && ilayvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
			return;
		}

		newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Int, PointPlot, nhru, dim);

		newVar->varType = CRHM::Int;

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

	case CRHM::INIT: {

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if ((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && ilayvalue != NULL) {
				if (newVar->nfreq && newVar->lay != Global::Freq) {
					newVar->ReleaseM(true);
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->ilayvalues = new long* [newVar->lay];
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
			CRHMException Except("Variable not found: " + Name + ' ' + variable, TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void ClassModule::decllocal(string variable, CRHM::TDim dimen, string help,
	string units, float** value, float*** layvalue, const int dim) {

	MapVar::iterator itVar;
	ClassVar* newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(VARD, Name, variable, variable); // new 04/23/13

	switch (Global::BuildFlag) {

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find("#" + Name + " " + variable)) != Global::MapVars.end())
			return;

		if ((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
			return;
		}

		newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Float, false, nhru, dim);

		newVar->varType = CRHM::Float;

		newVar->InGroup = GroupCnt;

		newVar->visibility = CRHM::PRIVATE;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar("#" + Name + " " + variable, newVar);

		Global::MapVars.insert(Item);
		return;
	}

	case CRHM::INIT: {

		string S = "#" + Name + " " + variable;

		if ((itVar = Global::MapVars.find(S)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if ((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && layvalue != NULL) {
				if (newVar->nfreq && newVar->lay != Global::Freq) {
					newVar->ReleaseM(true);
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->layvalues = new float* [newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->layvalues[ii] = new float[newVar->dim];
				}
				*layvalue = newVar->layvalues;
			}

			*value = newVar->values;

			return;
		}
		else {
			CRHMException Except("variable not found: " + S, TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
void ClassModule::decllocal(string variable, CRHM::TDim dimen, string help,
	string units, long** value, long*** layvalue, const int dim) {

	MapVar::iterator itVar;
	ClassVar* newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, variable, units);

	AKAhook(VARD, Name, variable, variable); // new 04/23/13

	switch (Global::BuildFlag) {

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find("#" + Name + " " + variable)) != Global::MapVars.end())
			return;

		if (dimen == CRHM::NLAY && layvalue == NULL) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + variable, WARNING));
			return;
		}

		newVar = new ClassVar(Name, variable, dimen, help, units, CRHM::Int, false, nhru, dim);

		newVar->varType = CRHM::Int;

		newVar->InGroup = GroupCnt;

		newVar->visibility = CRHM::PRIVATE;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();

		newVar->root = ID.c_str();

		PairVar Item = PairVar("#" + Name + " " + variable, newVar);

		Global::MapVars.insert(Item);
		return;
	}

	case CRHM::INIT: {

		string S = "#" + Name + " " + variable;

		if ((itVar = Global::MapVars.find(S)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if ((dimen == CRHM::NLAY || dimen == CRHM::NFREQ) && layvalue != NULL) {
				if (newVar->nfreq && newVar->lay != Global::Freq) {
					newVar->ReleaseM(true);
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->ilayvalues = new long* [newVar->lay];
					for (int ii = 0; ii < newVar->lay; ii++)
						newVar->ilayvalues[ii] = new long[newVar->dim];
				}
				*layvalue = newVar->ilayvalues;
			}

			*value = newVar->ivalues;

			return;
		}
		else {
			CRHMException Except("variable not found: " + S, TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
}

//---------------------------------------------------------------------------
TStringList* ClassModule::decldiagparam(string param, CRHM::TDim dimen,
	string Texts, string help, TStringList* stringsList, CRHM::TVISIBLE Local) {

	TStringList* fix = declparam(param, dimen, Texts, help, stringsList, Local);
	return fix;
}

//---------------------------------------------------------------------------
TStringList* ClassModule::decllocalparam(string param, CRHM::TDim dimen,
	string Texts, string help, TStringList* stringsList, CRHM::TVISIBLE Local) {

	TStringList* fix = declparam(param, dimen, Texts, help, stringsList, Local);
	return fix;
}

//---------------------------------------------------------------------------
TStringList* ClassModule::declparam(string param, CRHM::TDim dimen,
	string Texts, string help, TStringList* stringsList, CRHM::TVISIBLE Local) {
	MapPar::iterator itPar;
	ClassPar* newPar;

	if (Variation_Skip()) {
		return (TStringList*)NULL;
	}

	variation_max = variation_max | variation_set;

	AKAhook(PARD, Name, param, param);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(param.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return (TStringList*)NULL;
	}

	case CRHM::DECL: {

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN) {
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

		newPar = new ClassPar(string(Name.c_str()), string(param), dimen, Texts, help, CRHM::Txt, nhru);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = Local;

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return newPar->Strings;
	}

	case CRHM::INIT: {
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
			CRHMException Except("Parameter not found: " + Name + param, TERMINATE);
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
void ClassModule::decldiagparam(string param, CRHM::TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const float** value, const float*** layvalue, const int dim, CRHM::TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::decllocalparam(string param, CRHM::TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const float** value, const float*** layvalue, const int dim, CRHM::TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::declparam(string param, CRHM::TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const float** value, const float*** layvalue, const int dim, CRHM::TVISIBLE Local) {
	MapPar::iterator itPar;
	ClassPar* newPar;

	if (Variation_Skip()) {
		*value = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(PARD, Name, param, param);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(param.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return;
	}

	case CRHM::DECL: {

		if (dim <= 0) { // find existing parameter
			return;
		}

		if (dimen == CRHM::NDEFN)// save for lay loop
			++Par_NDEFN_cnt;

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->basemodule = this->NameRoot;
					newPar->variation_set = variation_set;
					newPar->visibility = Local;
					newPar->Inhibit_share = 1;
					newPar->valstr = valstr;
					newPar->minVal = (float) atof(minstr.c_str());
					newPar->maxVal = (float) atof(maxstr.c_str());
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
			if ((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->Inhibit_share = 1;
					//            assert(0);
				}
				return;
			}
		}

		if ((dimen == CRHM::NLAY && layvalue == NULL) || (dimen == CRHM::NDEF && layvalue == NULL) || (dimen == CRHM::NDEFN && layvalue == NULL)) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + param, WARNING));
			return;
		}

		float minval = atof(minstr.c_str());
		float maxval = atof(maxstr.c_str());

		newPar = new ClassPar(string(Name.c_str()), string(param), dimen,
			valstr, minval, maxval, help, units, CRHM::Float, dim, nhru);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = Local;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return;
	}

	case CRHM::INIT: {
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
			CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
			LogError(Except);
			throw Except;
		}

		if ((dimen == CRHM::NLAY && layvalue != NULL) || (dimen == CRHM::NDEF && layvalue != NULL) || (dimen == CRHM::NDEFN && layvalue != NULL))
			*layvalue = (const float**)newPar->layvalues;

		if (dimen == CRHM::NDEF) {
			Par_loop_lay_table[Par_NDEFN_cnt] = newPar->layvalues; // save for lay loop
			Par_loop_lay_value[Par_NDEFN_cnt++] = newPar->values; // save for lay loop
		}
	} // case
	default:
		break;
	} // switch
}

//---------------------------------------------------------------------------
void ClassModule::decldiagparam(string param, CRHM::TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const long** value, const long*** layvalue, const int dim, CRHM::TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::decllocalparam(string param, CRHM::TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const long** value, const long*** layvalue, const int dim, CRHM::TVISIBLE Local) {

	declparam(param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
}

//---------------------------------------------------------------------------
void ClassModule::declparam(string param, CRHM::TDim dimen,
	string valstr, string minstr, string maxstr,
	string help, string units, const long** ivalue, const long*** ilayvalue, const int dim, CRHM::TVISIBLE Local) {

	MapPar::iterator itPar;
	ClassPar* newPar;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(PARD, Name, param, param);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		VandP VP; VP.PutV(variation_set); VP.PutP(Local);
		PairstrV Item2 = PairstrV(param.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return;
	}

	case CRHM::DECL: {

		if (dim <= 0) { // find existing parameter
			return;
		}

		*ivalue = &Dummy;

		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			if ((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					newPar->basemodule = this->NameRoot;
					newPar->variation_set = variation_set;
					newPar->visibility = Local;
					newPar->Inhibit_share = 1;
					newPar->valstr = valstr;
					newPar->minVal = (float) atof(minstr.c_str());
					newPar->maxVal = (float) atof(maxstr.c_str());
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
			if ((*itPar).second->dim == this->nhru || dimen == CRHM::BASIN) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share == 2) {
					assert(0);
				}
				return;
			}
		}

		if ((dimen == CRHM::NLAY && ilayvalue == NULL) || (dimen == CRHM::NDEF && ilayvalue == NULL) || (dimen == CRHM::NDEFN && ilayvalue == NULL)) {
			LogError(CRHMException("Layer Array not defined for " + Name + " " + param, WARNING));
			return;
		}

		float minval = atof(minstr.c_str());
		float maxval = atof(maxstr.c_str());

		newPar = new ClassPar(string(Name.c_str()), string(param), dimen,
			valstr, minval, maxval, help, units, CRHM::Int, dim, nhru);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = Local;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return;
	}

	case CRHM::INIT: {
		if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			*ivalue = newPar->ivalues;
			if ((dimen == CRHM::NLAY && ilayvalue != NULL) || (dimen == CRHM::NDEF && ilayvalue != NULL) || (dimen == CRHM::NDEFN && ilayvalue != NULL))
				*ilayvalue = (const long**)newPar->ilayvalues;
			return;
		}
		else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
			newPar = (*itPar).second;
			*ivalue = newPar->ivalues;
			if ((dimen == CRHM::NLAY && ilayvalue != NULL) || (dimen == CRHM::NDEF && ilayvalue != NULL) || (dimen == CRHM::NDEFN && ilayvalue != NULL))
				*ilayvalue = (const long**)newPar->ilayvalues;
			return;
		}
		else if ((newPar = ClassParFindPar(param))) {
			*ivalue = newPar->ivalues;
			if ((dimen == CRHM::NLAY && ilayvalue != NULL) || (dimen == CRHM::NDEF && ilayvalue != NULL) || (dimen == CRHM::NDEFN && ilayvalue != NULL))
				*ilayvalue = (const long**)newPar->ilayvalues;
			return;
		}
		else {
			CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
			LogError(Except);
			throw Except;
		}
	} // case
	default:
		break;
	} // switch
}

//---------------------------------------------------------------------------
long ClassModule::FindWildVarFloat(string name, ClassVar*& newVar, bool OnceFlag) {

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
long ClassModule::FindWildParFloat(string name, ClassPar*& newPar, bool Trunc = false, bool Root = true) {

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
long ClassModule::declgetvar(string source, string name, string units, const float** value, const float*** layvalue) {

	MapVar::iterator itVar;
	ClassVar* newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(VARG, Name, name, name, source, ID);

	MapPar::iterator itPar;
	ClassPar* newPar;
	long GetUnit;

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapgetvar.insert(Item);
		return 0;
	}

	case CRHM::DECL: {
		return 0;
	}

	case CRHM::INIT: {
		string::size_type indx2 = name.find('@');
		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;
			if (layvalue != NULL) *layvalue = (const float**)newVar->layvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (indx2 != string::npos &&  // look for group variable in fundamental module
			(itVar = Global::MapVars.find(source + " " + name.substr(0, indx2))) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;
			if (layvalue != NULL) *layvalue = (const float**)newVar->layvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->values;
				if (layvalue != NULL) *layvalue = (const float**)newVar->layvalues;

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
long ClassModule::declgetvar(string source, string name, string units, const long** value, const long*** layvalue) {

	MapVar::iterator itVar;
	ClassVar* newVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(VARG, Name, name, name, source, ID);

	MapPar::iterator itPar;
	ClassPar* newPar;
	long GetUnit;

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapgetvar.insert(Item);
		return 0;
	}

	case CRHM::DECL: {
		return 0;
	}

	case CRHM::INIT: {
		if (name == "Not_Used") // AKA does not handle int/float
			name = "Not_Used_int";

		string::size_type indx2 = name.find('@');
		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->ivalues;
			if (layvalue != NULL) *layvalue = (const long**)newVar->ilayvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (indx2 != string::npos &&  // look for group variable in fundamental module
			(itVar = Global::MapVars.find(source + " " + name.substr(0, indx2))) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->ivalues;
			if (layvalue != NULL) *layvalue = (const long**)newVar->ilayvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsGet.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->ivalues;
				if (layvalue != NULL) *layvalue = (const long**)newVar->ilayvalues;

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
long ClassModule::declobs(string name, CRHM::TDim dimen, string help, string units, float** value) {

	MapVar::iterator itVar;
	ClassVar* newVar;
	ClassVar* thisVar;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, name, units);

	AKAhook(OBSD, Name, name, name);

	int cnt = getdim(dimen);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {

		VandP VP; VP.PutV(variation_set); VP.PutP(CRHM::USUAL);
		PairstrV Item2 = PairstrV((name + "#").c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		Global::Mapdeclobs.insert(Item);

		Global::DeclRootList->Add(string(ID.c_str()) + " " + (name + "#").c_str()); // to prevent input/output looping

		return(-1);
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + name + "#")) != Global::MapVars.end()) {

			thisVar = (*itVar).second;
			if (thisVar->dim < cnt) {
				thisVar->ReleaseM(); // releases everything
				thisVar->dim = cnt;
				if (thisVar->lay > 0) {
					thisVar->layvalues = new float* [thisVar->lay];
					for (int ii = 0; ii < thisVar->lay; ii++) thisVar->layvalues[ii] = new float[cnt];
				}
				thisVar->values = new float[cnt];     // CHECK ???
			}
			thisVar->dimen = dimen;  //warning resolved by Manishankar

			thisVar->DLLName = DLLName.c_str();
			thisVar->root = ID.c_str();

			return(-1);
		}

		newVar = new ClassVar(Name, name + "#", cnt, 0, NULL);

		newVar->varType = CRHM::Float;
		newVar->help = help;
		newVar->units = units;
		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		newVar->values = new float[cnt];

		newVar->variation_set = variation_set;

		PairVar Item = PairVar(Name + " " + name + "#", newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case CRHM::INIT: {
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
			CRHMException Except("Observation not found: " + Name + " " + name + "#", TERMINATE);
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
	ClassVar* newVar;

	if ((itVar = Global::MapVars.find("obs " + variable)) != Global::MapVars.end()) {
		newVar = (*itVar).second;
		return(newVar->cnt);
	}
	else
		return(-1);
}

//---------------------------------------------------------------------------
long ClassModule::declreadobs(string variable, CRHM::TDim dimen,
	string help, string units, const float** value, long HRU_index, bool optional, const float*** layvalue) {

	MapVar::iterator itVar;
	ClassVar* newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(OBSR, Name, variable, variable, declModule, ID);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		return(-1);
	}

	case CRHM::DECL: {

		if (dimen == CRHM::NFREQ && layvalue == NULL) {
			LogError(CRHMException("NFREQ Array not defined for " + Name + " " + variable, WARNING));
			return(-1);
		}

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;

			if (newVar->varType == CRHM::Read) { // used only once. Changes Read to ReadF
				Convert convert;
				convert.CheckUnitsObs(newVar->units, units, variable); // check original observation units

				newVar->values = NULL; // memory assigned in CRHM::INIT

				newVar->varType = CRHM::ReadF;

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

		newVar = new ClassVar("obs", variable, dimen, help, units, CRHM::Float);

		newVar->varType = CRHM::Float;

		Item = PairVar(declModule + variable, newVar);
		Global::MapVars.insert(Item);

		Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case CRHM::INIT: {

		newVar = NULL; // unchanged if nothing found

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) { // look for in declModule
			newVar = (*itVar).second;

			if ((newVar->varType == CRHM::ReadF | newVar->varType == CRHM::Read) && newVar->values == NULL) {
				Convert convert; convert.CheckUnitsObs(newVar->units, units, variable); // check original observation units

				newVar->varType = CRHM::ReadF;

				newVar->dimMax = Global::maxhru;
				newVar->values = new float[newVar->dimMax];

				newVar->help = help;
				newVar->units = units;

				Item = PairVar(Name + " " + variable, newVar);
				Global::MapVars.insert(Item);
			}
		}

		string::size_type indx; // indicates if declared obs
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
			CRHMException Except("Observation not found " + declModule + ": " + variable, TERMINATE);
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
				CRHMException Except("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
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
			if (dimen == CRHM::NHRU)
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
long ClassModule::declreadobs(string variable, CRHM::TDim dimen,  // needs updating. Is it ever used.
	string help, string units, const long** value, long HRU_index, bool optional, const long*** layvalue) {

	MapVar::iterator itVar;
	ClassVar* newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(OBSR, Name, variable, variable, declModule, ID);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(variable.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		return(-1);
	}

	case CRHM::DECL: {

		if (dimen == CRHM::NFREQ && layvalue == NULL) {
			LogError(CRHMException("NFREQ Array not defined for " + Name + " " + variable, WARNING));
			return(-1);
		}

		if ((itVar = Global::MapVars.find(declModule + variable)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if (newVar->varType == CRHM::Read || newVar->varType == CRHM::ReadI) {
				if (dimen == CRHM::NFREQ && (newVar->lay == 0 || nhru > newVar->dim)) {
					newVar->ReleaseM(true);
					newVar->dim = nhru;
					newVar->dimMax = newVar->dim;
					newVar->lay = Global::Freq;
					newVar->nfreq = true;
					newVar->ilayvalues = new long* [newVar->lay];
					for (int ii = 0; ii < newVar->lay; ++ii)
						newVar->ilayvalues[ii] = new long[newVar->dimMax];
				}

				if (newVar->varType == CRHM::Read || (newVar->varType == CRHM::ReadF && nhru > newVar->dimMax)) {  //warning resolved by Manishankar
					if (newVar->ivalues != NULL)
						delete[] newVar->ivalues;
					else {
						Convert convert;
						convert.CheckUnitsObs(newVar->units, units, variable); // check original observation units
					}

					newVar->dimMax = max<long>(nhru, newVar->cnt);

					newVar->ivalues = new long[newVar->dimMax];

					newVar->varType = CRHM::ReadI;

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
			else if (newVar->dimen != dimen && dimen == CRHM::NFREQ) { // upgrade t to t-freq
				newVar->ReleaseM(true);
				newVar->lay = Global::Freq;
				newVar->nfreq = true;
				newVar->ilayvalues = new long* [newVar->lay];
				for (int ii = 0; ii < newVar->lay; ii++)
					newVar->ilayvalues[ii] = new long[newVar->dim];
			}
			return(-1);
		}

		newVar = new ClassVar(declModule, variable, dimen, help, units, CRHM::Int);

		newVar->varType = CRHM::Int;

		Item = PairVar(declModule + variable, newVar);
		Global::MapVars.insert(Item);

		Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case CRHM::INIT: {

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
			CRHMException Except("Observation not found " + declModule + ": " + variable, TERMINATE);
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
				CRHMException Except("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
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
				newVar->ilayvalues = new long* [newVar->lay];
				for (int ii = 0; ii < newVar->lay; ii++)
					newVar->ilayvalues[ii] = new long[newVar->dim];
			}

			*layvalue = (const long**)newVar->ilayvalues;
			newVar->UserFunct = &ClassVar::Intvl;
			newVar->FunKind = CRHM::INTVL;
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

long ClassModule::declobsfunc(string obs, string variable, float** value, CRHM::TFun typeFun, float*** layvalue, bool optional) {

	MapVar::iterator itVar;
	ClassVar* obsVar, * newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(OBSF, Name, obs, obs, declModule, ID);
	AKAhook(VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(Name.c_str());
		string units;

		for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap) {
			if (itMap->second.first == obs.c_str()) {
				units = itMap->second.second;
				break;
			}
		}

		VandP VP; VP.PutV(variation_set); VP.PutP(CRHM::DIAGNOSTIC);
		PairstrV Item2 = PairstrV(obs.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		Item2 = PairstrV(variable.c_str(), VP.both);
		Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		return(-1);
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(declModule + obs)) == Global::MapVars.end()) {
			LogError(CRHMException("function obs variable not declared: " + Name + " " + obs, WARNING));
			return(-1);
		}

		obsVar = (*itVar).second;

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return(-1);
		}

		//Manishankar. Fstrings[typeFun] was getting out of index.
		//string help = obsVar->help + " <" + Fstrings[typeFun] + "> ";
		string help = obsVar->help + " <" + "> ";

		newVar = new ClassVar(Name, variable, nhru, help, obsVar->units, CRHM::Float);

		newVar->dimMax = nhru; // added 04/16/13 (replacing t obs faulty)

		newVar->varType = CRHM::Float;

		newVar->visibility = CRHM::DIAGNOSTIC;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(0);
	}

	case CRHM::INIT: {
		itVar = Global::MapVars.find(Name + " " + variable);

		try
		{
			if ((itVar = Global::MapVars.find(declModule + obs)) != Global::MapVars.end()) {
				newVar = (*itVar).second;
				obsVar = (*itVar).second;

				if (!newVar) { // Applies to ppt, p etc. when building a new project with NO observations defined

					newVar = new ClassVar(Name, variable, nhru,
						obsVar->help + " <" + Fstrings[typeFun] + "> ",
						obsVar->units, CRHM::Float);

					newVar->dimMax = nhru;

					newVar->varType = CRHM::Float;

					newVar->visibility = CRHM::DIAGNOSTIC;

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
						CRHMException Except("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str() + "'. Requested by '" + Name.c_str() + "'", TERMINATE);
						LogError(Except);
						throw Except;
					}
				}

				if (obsVar->FileData->Times != NULL) {
					CRHMException Except("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
					LogError(Except);
					throw Except;
				}

				if (typeFun == CRHM::INTVL) {

					newVar->ReleaseM(false); // needs to release current values
					newVar->dim = max<long>(nhru, newVar->dim);
					newVar->dimMax = max<long>(newVar->dim, newVar->dimMax);
					newVar->lay = Global::Freq;

					newVar->layvalues = new float* [newVar->lay];
					*layvalue = newVar->layvalues;

					for (int ii = 0; ii < newVar->lay; ++ii)
						newVar->layvalues[ii] = new float[newVar->dimMax];

					newVar->values = newVar->layvalues[0]; // set non-zero - ReleaseM requires - NOP

					newVar->FileData = obsVar->FileData;
				}
				else if (nhru > newVar->dim) { // change of observation array size
					delete[] newVar->values;
					newVar->dimMax = nhru;
					newVar->values = new float[newVar->dimMax];
					newVar->dim = newVar->dimMax;
				}
				if (GroupCnt)
					newVar->CustomFunct = NULL; // Set by 'declobsfunc' for Groups. If simple set by 'addtoreadlist'

				switch (typeFun) {
				case CRHM::FOBS:
					newVar->FunctVar = obsVar;
					newVar->FunKind = CRHM::FOBS;
					newVar->FileData = obsVar->FileData;
					if (GroupCnt)
						newVar->No_ReadVar = 1;  // do not read observation
					break;
				case CRHM::AVG:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Avg;
					newVar->FunKind = CRHM::AVG;
					break;
				case CRHM::MIN:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Min;
					newVar->FunKind = CRHM::MIN;
					break;
				case CRHM::MAX:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Max;
					newVar->FunKind = CRHM::MAX;
					break;
				case CRHM::DTOT:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Dtot;
					newVar->FunKind = CRHM::DTOT;
					break;
				case CRHM::TOT:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Tot;
					newVar->FunKind = CRHM::TOT;
					break;
				case CRHM::FIRST:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::First;
					newVar->FunKind = CRHM::FIRST;
					break;
				case CRHM::LAST:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Last;
					newVar->FunKind = CRHM::LAST;
					break;
				case CRHM::POS:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Pos;
					newVar->FunKind = CRHM::POS;
					break;
				case CRHM::INTVL:
					newVar->FunctVar = obsVar;
					newVar->UserFunct = &ClassVar::Intvl;
					newVar->FunKind = CRHM::INTVL;
					newVar->offset = newVar->FunctVar->offset;

					*layvalue = newVar->layvalues;
					break;
				default:
					break;
				}

				*value = newVar->values;

				newVar->HRU_OBS_indexed = obsVar->HRU_OBS_indexed;
				if (newVar->FunKind == CRHM::FOBS)
					addtoreadlist(newVar);
				else if ((Global::RH_EA_obs == -1 && obs == "rh") || (Global::RH_EA_obs == -1 && obs == "ea") || Global::OBS_AS_IS || !(obs == "ea" || obs == "rh"))  //warning resolved by Manishankar
					addtofunctlist(newVar);
				return(obsVar->cnt - 1);
			}
			else {
				if (!optional) {
					CRHMException Except("Observation not found obs: " + obs, TERMINATE);
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
long ClassModule::declobsfunc(string obs, string variable, long** value, CRHM::TFun typeFun, bool optional) {

	MapVar::iterator itVar;
	ClassVar* obsVar, * newVar;
	PairVar Item;
	string declModule = "obs ";

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(OBSF, Name, obs, obs, declModule, ID);
	AKAhook(VARD, Name, variable, variable);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(Name.c_str());
		string units;

		for (Mapstr::iterator itMap = range.first; itMap != range.second; ++itMap) {
			if (itMap->second.first == obs.c_str()) {
				units = itMap->second.second;
				break;
			}
		}

		VandP VP; VP.PutV(variation_set); VP.PutP(CRHM::DIAGNOSTIC);
		PairstrV Item2 = PairstrV(obs.c_str(), VP.both);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapreadvar.insert(Item);
		Global::Mapdeclvar.insert(Item);

		Item2 = PairstrV(variable.c_str(), VP.both);
		Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclvar.insert(Item);
		return(-1);
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(declModule + obs)) == Global::MapVars.end()) {
			LogError(CRHMException("function obs variable not declared: " + Name + " " + obs, WARNING));
			return(-1);
		}

		obsVar = (*itVar).second;

		if ((itVar = Global::MapVars.find(Name + " " + variable)) != Global::MapVars.end()) {
			return(-1);
		}

		if (!obsVar->ivalues) {
			obsVar->ivalues = new long[obsVar->dim]; // TB 10/08/10
			obsVar->varType = CRHM::ReadI;
		}

		newVar = new ClassVar(Name, variable, obsVar->dim,
			obsVar->help + " <" + Fstrings[typeFun] + "> ",
			obsVar->units, CRHM::Float);

		newVar->varType = CRHM::Float;

		newVar->visibility = CRHM::DIAGNOSTIC;

		newVar->variation_set = variation_set;

		newVar->DLLName = DLLName.c_str();
		newVar->root = ID.c_str();

		PairVar Item = PairVar(Name + " " + variable, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case CRHM::INIT: {
		itVar = Global::MapVars.find(Name + " " + variable);
		newVar = (*itVar).second;

		if ((itVar = Global::MapVars.find(declModule + obs)) != Global::MapVars.end()) {
			obsVar = (*itVar).second;

			if (obsVar->FileData == NULL) {
				if (optional) {
					LogError(CRHMException("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str() + "'. Requested by '" + Name.c_str() + "' (optional).", WARNING));
					*value = NULL;
					return(-1);
				}
				else {
					CRHMException Except("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str() + "'. Requested by '" + Name.c_str() + "'", TERMINATE);
					LogError(Except);
					throw Except;
				}
			}

			if (obsVar->FileData->Times != NULL) {
				CRHMException Except("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str() + "'", TERMINATE);
				LogError(Except);
				throw Except;
			}

			if (obsVar->dim != newVar->dim) { // change of observation array size
				delete[] newVar->ivalues;
				newVar->ivalues = new long[obsVar->dim];
				newVar->dim = obsVar->dim;
			}

			switch (typeFun) {
			case CRHM::AVG:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Avg;
				newVar->FunKind = CRHM::AVG;
				break;
			case CRHM::MIN:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Min;
				newVar->FunKind = CRHM::MIN;
				break;
			case CRHM::MAX:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Max;
				newVar->FunKind = CRHM::MAX;
				break;
			case CRHM::DTOT:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Dtot;
				newVar->FunKind = CRHM::DTOT;
				break;
			case CRHM::TOT:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Tot;
				newVar->FunKind = CRHM::TOT;
				break;
			case CRHM::FIRST:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::First;
				newVar->FunKind = CRHM::FIRST;
				break;
			case CRHM::LAST:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Last;
				newVar->FunKind = CRHM::LAST;
				break;
			case CRHM::POS:
				newVar->FunctVar = obsVar;
				newVar->UserFunct = &ClassVar::Pos;
				newVar->FunKind = CRHM::POS;
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
			CRHMException Except("Variable not found obs: " + obs, TERMINATE);
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


long ClassModule::declputvar(string source, string name, string units, float** value, float*** layvalue) {

	MapVar::iterator itVar;
	ClassVar* newVar;
	long GetUnit;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(VARG, Name, name, name, source, ID);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapputvar.insert(Item);
		return 0;
	}

	case CRHM::DECL: {
		return 0;
	}

	case CRHM::INIT: {
		if ((itVar = Global::MapVars.find(source + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			*value = newVar->values;
			if (layvalue != NULL) (*layvalue) = newVar->layvalues; //const_cast<float **> (*layvalue) = newVar->layvalues;

			PairVar Item = PairVar(Name + " " + name, newVar);
			Global::MapVarsPut.insert(Item);
			return newVar->GetUnit();
		}
		else if (source[0] == '*') {
			GetUnit = FindWildVarFloat(name, newVar); // name
			if (GetUnit > -1) {
				*value = newVar->values;
				if (layvalue != NULL) (*layvalue) = newVar->layvalues;  //const_cast<float **> (*layvalue) = newVar->layvalues;

				PairVar Item = PairVar(Name + " " + name, newVar);
				Global::MapVarsPut.insert(Item);
				return GetUnit;
			}

			CRHMException Except("Wild variable not found: " + source + ' ' + name, TERMINATE);
			LogError(Except);
			throw Except;
		}
		else {
			CRHMException Except("Variable not found: " + source + ' ' + name, TERMINATE);
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
long ClassModule::declputvar(string source, string name, string units, long** value, long*** layvalue) {

	MapVar::iterator itVar;
	ClassVar* newVar;
	long GetUnit;

	if (Variation_Skip()) {
		*value = NULL;
		return(-1);
	}

	variation_max = variation_max | variation_set;

	AKAhook(VARG, Name, name, name, source, ID);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {

		string s = string(source.c_str()) + " " + name.c_str();

		PairstrV Item2 = PairstrV(s, variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapputvar.insert(Item);
		return 0;
	}

	case CRHM::DECL: {
		return 0;
	}

	case CRHM::INIT: {
		if (name == "Not_Used") // AKA does not handle int/float
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

			CRHMException Except("Wild variable not found: " + source + ' ' + name, TERMINATE);
			LogError(Except);
			throw Except;
		}
		else {
			CRHMException Except("Variable not found: " + source + ' ' + name, TERMINATE);
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
void ClassModule::AKAhook(TAKA type, string module, string OrgName, string& NewName) { // OBSD, PARD, VARD

	Mapstr2::iterator it; // holds NewName
	string ID = AKAstrings[type] + ' ' + module + ' ' + OrgName;
	bool Added = false;
	bool Explicit = false;

	if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
		NewName = (*it).second;
		NewName = NewName.substr(0, NewName.find(' '));
		Explicit = true;
	}
	else {
		if (type == OBSD) {
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
		else if (GroupCnt && type == VARD) {
			string A;
			Common::GroupEnding(A, GroupCnt);
			NewName.append(A);
			ID = AKAstrings[type] + ' ' + module + ' ' + NewName;
			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
				NewName = (*it).second;
				NewName = NewName.substr(0, NewName.find(' '));
				Explicit = true;
			}
		}
		else if (StructCnt && type == VARD) {
			string A("@`");
			A[1] += StructCnt;
			NewName.append(A);
		}
	}

	if (Global::ReportList && Explicit) {
		string ID = AKAstrings[type] + ' ' + module + ' ' + OrgName;
		if (Added)
			NewName.insert(NewName.size(), "#");
		if (Explicit)
			NewName.insert(NewName.size(), " **** explicit");
		Global::ReportList->Add((ID + " ---> " + NewName).c_str());
	}
}

//---------------------------------------------------------------------------
void ClassModule::AKAhook(TAKA type, string module, string OrgName, string& NewName, string& source, string base) { // OBSR, OBSF, VARG

	Mapstr2::iterator it; // holds NewName AND source

	enum { None, Implicit, Explicit, IgnoreObs, IgnoreVar, IgnoreObsFunct } Outcome;
	Outcome = None;

	TAKA typeL = type; // fudge until AKA screen fixed
	if (type == OBSF)
		type = OBSR;

	string Try;
	string ID = AKAstrings[type] + ' ' + module + ' ' + OrgName;

	if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) { // search AKA list
		Try = (*it).second;
		Try = Try.substr(0, Try.find(' '));
		if (Global::DeclRootList->IndexOf(string(base.c_str()) + " " + Try.c_str()) > -1) { // looping redirection
			if (typeL == OBSF)
				Outcome = IgnoreObsFunct;
			else
				Outcome = IgnoreObs;
		}
		else if (GroupCnt && type == VARG) {
			string A;
			Common::GroupEnding(A, GroupCnt);
			NewName.append(A);
			ID = AKAstrings[type] + ' ' + module + ' ' + NewName;
			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) { // search AKA list for GROUP name
				Try = (*it).second;
				Try = Try.substr(0, Try.find(' '));
				NewName = (*it).second;
				NewName = NewName.substr(0, NewName.find(' '));
				Outcome = Implicit;
			}
		}
		else if (typeL == OBSF && Try[Try.size() - 1] == '#') { // declared observation and daily function
			Outcome = IgnoreObsFunct;
		}
		else if (type == OBSR) { //  observation   !!! was typeL 08/20/10
			if (Try[Try.size() - 1] == '#') {
				if (Global::DeclRootList->IndexOf(string(base.c_str()) + " " + Try.c_str()) > -1) {
					Outcome = IgnoreObs;
				}
			}

			NewName = (*it).second;
			NewName = NewName.substr(0, NewName.find(' '));
			source = (*it).second;
			source = source.substr(source.find(' ') + 1) + ' ';
			Outcome = Explicit;
		}
		else if (type == VARG) { // handle read operation
			NewName = (*it).second;
			NewName = NewName.substr(0, NewName.find(' '));
			source = (*it).second;
			source = source.substr(source.find(' ') + 1);
			Outcome = Explicit;
		}
	} // Above found in AKA table
	else {
		if (GroupCnt && typeL == OBSR) { // use declared observation in same group

			if ((Global::MapVars.find("obs " + OrgName)) != Global::MapVars.end()) { // look for as observation
				NewName = OrgName;
				source = "obs ";
				Try = NewName;
				Outcome = Implicit;
			}
			else {
				string mod_var = ID.substr(ID.find(' ') + 1) + '#';

				if ((Global::MapVars.find(mod_var)) != Global::MapVars.end()) {
					NewName = OrgName + '#';
					source = module + ' ';
					Try = NewName;
					Outcome = Implicit;
				}
			}
		}
		else if ((GroupCnt || StructCnt) && type == VARG) {
			string A;
			if (GroupCnt) {
				Common::GroupEnding(A, GroupCnt);
			}
			if (StructCnt) {
				Common::GroupEnding(A, StructCnt);
			}
			NewName.append(A);
			ID = AKAstrings[type] + ' ' + module + ' ' + NewName;
			if ((it = Global::MapAKA.find(ID)) != Global::MapAKA.end()) {
				Try = (*it).second;
				Try = Try.substr(0, Try.find('@'));
				if (Global::DeclRootList->IndexOf(string(base.c_str()) + " " + Try.c_str()) > -1) {
					Outcome = IgnoreVar;
				}
				else {
					NewName = (*it).second;
					NewName = NewName.substr(0, NewName.find(' '));
					Outcome = Implicit;
				}
			}
		}
	}

	ID = AKAstrings[typeL] + " (" + base + ") " + module + " -> " + OrgName + ' ';
	switch (Outcome) {
	case IgnoreObs:
		LogMessage(string(ID + " *** AKA warning, not changed to *** " + source + "->" + Try).c_str());
		break;
	case IgnoreObsFunct:
		LogMessage(string(ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str());
		break;
	case IgnoreVar: // VARG
		LogMessage(string(ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str());
		break;
	default:
		break;
	} // switch

	if (Global::ReportList && Outcome != None) {
		string reason = "";
		switch (Outcome) {
		case Explicit:
			source = (ID + " changed to " + source + "-> " + Try).c_str();
			reason = " *** Explicit *** ";
			break;
		case Implicit:
			source = (ID + " changed to " + source + "-> " + Try).c_str();
			reason = " *** Implicit *** ";
			break;
		case IgnoreObs:
			source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
			reason = " *** source module AKA observation redirection would loop output to input";
			break;
		case IgnoreObsFunct:
			source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str();
			reason = " *** daily function cannot be a declared observation";
			break;
		case IgnoreVar: // VARG
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

	if (Global::DTindx % Global::Freq == 0) { // only at start of day
		while (pN != FunctListN->Count && FunctListN->Strings[pN] == Name.c_str()) {

			/*TStringList test1 = FunctListN->Objects[pN];
			auto *test2 = &test1;
			ClassVar *P = (ClassVar*)test2;*/

			ClassVar* P = (ClassVar*)FunctListN->array[pN].Object;

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
		ClassVar* P = (ClassVar*)ReadListN->array[p].Object;
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
	Global::DTnow = Global::DTstart + Global::Interval * (Global::DTindx + 1);

	long p = 0;

	while (p < ReadListN->Count) {
		ClassVar* P = (ClassVar*)ReadListN->array[p].Object;
		if (P->FileData->GoodInterval)
			P->ReadVar();
		++p;
	}

	if (Global::DTindx % Global::Freq == 0) {
		p = 0;
		while (p < FunctListN->Count && FunctListN->Strings[p] == Name.c_str()) {
			ClassVar* P = (ClassVar*)FunctListN->array[p].Object;
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
	long** Save_HRU_obs = Global::HRU_OBS;

	Global::DTindx += inc;
	Global::DTnow = Global::DTstart + Global::Interval * (Global::DTindx + 1);

	long p = 0;

	while (p < ReadListN->Count) {
		ClassVar* P = (ClassVar*)ReadListN->array[p].Object;
		if (P->FileData->GoodInterval)
			P->ReadVar();
		++p;
	}

	if (Global::DTindx % Global::Freq == 0) {
		p = 0;
		while (p < FunctListN->Count) {
			ClassVar* P = (ClassVar*)FunctListN->array[p].Object;
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
		ClassVar* P = (ClassVar*)ReadListN->array[p].Object;
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
bool ClassModule::AnyOne(float* Data, int Cnt, float Val) {

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
void ClassModule::addtoreadlist(ClassVar* newVar) { // BuildFlag = crhm::init

													// called by ClassModule::declreadobs INIT to add observation

	long p = 0;
	ClassVar* P;
	string::size_type indx;

	while (p < ReadListN->Count && GroupCnt == 0) { // duplicates possible in simple projects
		P = (ClassVar*)ReadListN->array[p].Object;
		if (newVar == P) {
			if (this->Name == this->NameRoot) // simple project
				return;
		}
		p++;
	}

	if (((Global::DTmax - Global::DTmin) / Global::Freq + newVar->FileData->Dt1 > newVar->FileData->Dt2) && !newVar->FileData->Times) {
		CRHMException TExcept((string("Observation file '") + string(newVar->FileData->DataFileName.c_str()) + "' shorter than model run!").c_str(), WARNING);
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
			if (AnyOne(Global::Warming_t, nhru, 0.0f)) {
				newVar->CustomFunct = &ClassVar::do_t_Clim;
				newVar->CustomFunctName = "do_t_Clim";
			}
			else {
				newVar->CustomFunct = &ClassVar::do_t;
				newVar->CustomFunctName = "do_t";
			}
		}
		else if ((!GroupCnt && newVar->name == "p") || (GroupCnt && root_var == "p")) {  //warning resolved by Manishankar
			if (AnyOne(Global::Warming_p, nhru, 1.0f)) {
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
void ClassModule::addtofunctlist(ClassVar* newVar) {

	// called by ClassModule::declobsfunc INIT to add observation function

	long p = 0;
	ClassVar* P;
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
				if (AnyOne(Global::Warming_t, nhru, 0.0f)) {
					newVar->CustomFunct = &ClassVar::do_t_day_Clim;
					newVar->CustomFunctName = "do_t_day_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_t_day;
					newVar->CustomFunctName = "do_t_day";
				}
			}
			else if (RootName == "RHday") {
				if (AnyOne(Global::Warming_t, nhru, 0.0f)) {
					newVar->CustomFunct = &ClassVar::do_rh_day_Clim;
					newVar->CustomFunctName = "do_rh_day_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_rh_day;
					newVar->CustomFunctName = "do_rh_day";
				}
			}
			else if (RootName == "EAday") {
				if (!AnyOne(Global::Warming_t, nhru, 0.0f)) {
					newVar->CustomFunct = &ClassVar::do_ea_day;
					newVar->CustomFunctName = "do_ea_day";
				}
			}
			else if (RootName == "t_min" || newVar->name == "t_max") {
				if (AnyOne(Global::Warming_t, nhru, 0.0f)) {
					newVar->CustomFunct = &ClassVar::do_t_Clim;
					newVar->CustomFunctName = "do_t_Clim";
				}
				else {
					newVar->CustomFunct = &ClassVar::do_t;
					newVar->CustomFunctName = "do_t";
				}
			}
			else if (RootName.substr(0, 4) == "pptD") {
				if (AnyOne(Global::Warming_p, nhru, 1.0f)) {
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

//---------------------------------------------------------------------------
Administer::Administer(string Version, string _HelpFile) : Version(Version), HelpFile(_HelpFile) {

	DLLModuleList = new TStringList;
	DLLModelList = new TStringList;
	DLLModelModuleList = new TStringList;

	if (Global::PendingDLLModuleList != NULL)
		Global::PendingDLLModuleList->Clear(); // clear
}

//---------------------------------------------------------------------------
Administer::~Administer() {

	for (int ii = 0; ii < DLLModuleList->Count; ++ii)
		delete ((ClassModule*)DLLModuleList->array[ii].Object); // delete modules

	delete DLLModuleList;
	delete DLLModelList;
	delete DLLModelModuleList;
}

//---------------------------------------------------------------------------
void Administer::MacroClear() {

	for (int ii = 0; ii < DLLModuleList->Count; ++ii) {

		/*int jj = Global::AllModulesList->IndexOf(DLLModuleList->strings[ii]);
		if (jj > -1)
		Global::AllModulesList->Delete(jj);*/

		ClassModule* thisModule = (ClassModule*)DLLModuleList->array[ii].Object;
		delete thisModule;
	}

	if (Global::OurHelpList) {
		int indx = Global::OurHelpList->IndexOf(HelpFile);
		if (indx > -1) // delete Macro help file.
			Global::OurHelpList->Delete(indx);
	}

	DLLModuleList->Clear();
	DLLModelList->Clear();
	DLLModelModuleList->Clear();
}

//---------------------------------------------------------------------------
void Administer::MacroUpdate() {
	for (int ii = 0; ii < DLLModuleList->Count; ++ii) {
		int jj = Global::OurModulesList->IndexOf(DLLModuleList->Strings[ii]);

		if (jj > -1) // Update Macro Module address
			Global::OurModulesList->Objects[jj] = DLLModuleList->Objects[ii];
	}
}

//---------------------------------------------------------------------------
void Administer::AddModule(ClassModule* Module) {

	Module->OurAdmin = this;
	DLLModuleList->AddObject((Module)->Name.c_str(), (TObject*)Module);
	Global::PendingDLLModuleList->AddObject((Module)->Name.c_str(), (TObject*)Module);
}

//---------------------------------------------------------------------------
void Administer::AddModel(string ModelName, string ModelModules) {

	DLLModelModuleList->Add(ModelModules);
	//DLLModelList->AddObject(ModelName, (TObject*)(DLLModelModuleList->Count - 1)); // removed this line and added the following two for resolving a warning.
	long _object = DLLModelModuleList->Count - 1;
	DLLModelList->AddObject(ModelName, (TObject*)_object);
}

//---------------------------------------------------------------------------
void Administer::LoadCRHM(string DllName) {

	DLLName = DllName;
}

//---------------------------------------------------------------------------
void Administer::Accept(int Result) {

	string Exists;
	//  TMsgDlgType MsgDlgType;
	ClassModule* thisModule;

	for (int ii = 0; ii < DLLModuleList->Count; ++ii) { // All modules in DLL

		if (Global::PendingDLLModuleList->Count > 0  // Do not load unless requested.  Count == 0 means all!
			&& Global::PendingDLLModuleList->IndexOf(DLLModuleList->Strings[ii]) == -1)
			continue;

		int jj = Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]);
		if (jj != -1) {
			Exists = "Over-write existing module \"";
			//      MsgDlgType = mtWarning;
		}
		else {
			Exists = "Load Module \"";
			//      MsgDlgType = mtInformation;
		}

		if (Global::AllModulesList->IndexOf(DLLModuleList->Strings[ii]) == -1 // Needed to be put back!
			&& Global::OurModulesList->IndexOf(DLLModuleList->Strings[ii]) != -1)
			Result = mbYes;
		//    else if(Result != mbYesToAll && Result != mbNoToAll){ // optional
		//      Result = MessageDlg(Exists + DLLModuleList->Strings[ii] + "\" ?",
		//      MsgDlgType,
		//      TMsgDlgButtons() << mbYes << mbNo << mbYesToAll << mbNoToAll, 0);
		//      }

		switch (Result) {
		case mbYes:
		case mbYesToAll:
			if (jj != -1) {
				LogError(CRHMException((DLLModuleList->Strings[ii] + " module being replaced").c_str(), WARNING));
				Global::AllModulesList->Delete(jj);
			}

			thisModule = (ClassModule*)DLLModuleList->Objects[ii];
			thisModule->DLLName = DLLName;
			if (thisModule->DLLName != "Macro")
				thisModule->ID = typeid(*thisModule).name();

			Global::AllModulesList->AddObject(DLLModuleList->Strings[ii],
				(TObject*)DLLModuleList->Objects[ii]);
			break;

		case mbNo:
		case mbNoToAll:
			continue;
		default:
			break;
		}
	}

	for (int ii = 0; ii < DLLModelList->Count; ++ii) {

		// when sorted index used to access ModelModulesList
		long _object = ii;
		Global::AllModelsList->AddObject(DLLModelList->Strings[ii], (TObject*)_object);

		// Administer object used to find which DLL loaded model
		Global::ModelModulesList->AddObject(DLLModelModuleList->Strings[ii], (TObject*)this);
	}

	if (Global::OurHelpList)
	{
		if (Global::OurHelpList->IndexOf(HelpFile) < 0)  // No duplicates
		{
			Global::OurHelpList->AddObject(HelpFile, (TObject*)1);
		}
		else
		{
			Global::OurHelpList->AddObject(HelpFile, (TObject*)0);
		}
	}

	Global::PendingDLLModuleList->Clear(); // clear
}

//---------------------------------------------------------------------------
Myparser::Myparser() // parser constructor
{
	exp_ptr = NULL;
}

// Parser entry point.
void Myparser::eval_exp(ClassPar* Par)
{
	LocalPar = Par;
	float result, Last;
	int stop;
	bool OpenBrkt;

	//"points to the expression"
	exp_ptr = Par->valstr.c_str();

	row = 0; col = 0;
	rowrepeat = 1;
	Bang = 0;

next:
	repeat = 1;
	repeatset = false;
	OpenBrkt = false;

	//determine if the current token is a number, delimeter or variable
	get_token();

	if (*token == '[')
		result = 0.0f;
	else if (*token) {
		eval_exp2(result);
		if (result > Par->maxVal) result = Par->maxVal;
		if (result < Par->minVal) result = Par->minVal;
		Last = result;
	}
	else
		result = 0.0f;

	bool end = !*exp_ptr;

	switch (*token) {
	case '\0':
		if (col >= Par->dim) break;

		if (Par->varType == CRHM::Float)
			Par->layvalues[row][col++] = result;
		else if (Par->varType == CRHM::Int)
			Par->ilayvalues[row][col++] = result;

		for (int ll = row; ll < Par->lay; ++ll) {
			if (Bang) { // N.B. loop start
				for (int ii = col - 1; ii < Par->dim; ++ii) {
					if (Par->varType == CRHM::Float)
						Par->layvalues[ll][ii] = Last;
					else if (Par->varType == CRHM::Int)
						Par->ilayvalues[ll][ii] = Last;

					Last += 1;
				}
			}
			else {
				for (int ii = col; ii < Par->dim; ++ii)
					if (Par->varType == CRHM::Float)
						Par->layvalues[ll][ii] = 0.0f;
					else if (Par->varType == CRHM::Int)
						Par->ilayvalues[ll][ii] = 0.0f;
			}

			col = 0;;
		}
		break;
	case '[':
		rowrepeat = repeat;
		repeat = 1;
		repeatset = false;
		OpenBrkt = true;
		goto next;
	case ']':
		OpenBrkt = false;
		while (isspace(*exp_ptr)) ++exp_ptr; // skip over white space
		if (*exp_ptr == ',') ++exp_ptr; // skip over comma

		stop = col + repeat;
		if (stop > Par->dim) stop = Par->dim;
		for (int ii = col; ii < stop; ++ii)
			if (Par->varType == CRHM::Float)
				Par->layvalues[row][col++] = result;
			else if (Par->varType == CRHM::Int)
				Par->ilayvalues[row][col++] = result;

		for (int ii = col; ii < Par->dim; ++ii) {
			Last += Bang;
			if (Par->varType == CRHM::Float)
				Par->layvalues[row][ii] = Last;
			else if (Par->varType == CRHM::Int)
				Par->ilayvalues[row][ii] = Last;
		}

		Bang = 0;
		row++; col = 0;
		if (rowrepeat > 1 || end) {
			stop = row + rowrepeat - 1;
			if (stop > Par->lay || end) stop = Par->lay;

			for (int ll = row; ll < stop; ++ll) {
				for (int ii = col; ii < Par->dim; ++ii)
					if (Par->varType == CRHM::Float)
						Par->layvalues[ll][ii] = Par->layvalues[ll - 1][ii];
					else if (Par->varType == CRHM::Int)
						Par->ilayvalues[ll][ii] = Par->ilayvalues[ll - 1][ii];
			}
			row = stop;
			rowrepeat = 1;
		}
		if (row >= Par->lay) break;

		goto next;
	case ',':
		stop = col + repeat;
		if (stop > Par->dim) stop = Par->dim;
		for (int ii = col; ii < stop; ++ii)
			if (Par->varType == CRHM::Float)
				Par->layvalues[row][col++] = result;
			else if (Par->varType == CRHM::Int)
				Par->ilayvalues[row][col++] = result;
		if (col >= Par->dim)
			if (!OpenBrkt && (row + 1 < Par->lay)) {
				col = 0;
				++row;
			}

		goto next;
	default:
		serror(0); // last token must be null
		break;
	} // switch
}

// Add or subtract two terms.
void Myparser::eval_exp2(float& result)
{
	char op; //removed register keyword to fix warning. Manishankar
	float temp;

	eval_exp3(result);
	while ((op = *token) == '+' || op == '-') {
		get_token();
		eval_exp3(temp);
		switch (op) {
		case '-':
			result = result - temp;
			break;
		case '+':
			result = result + temp;
			break;
		default:
			break;
		}
	}
}

// Multiply or divide two factors.
void Myparser::eval_exp3(float& result)
{
	char op; //removed register keyword to fix warning. Manishankar
	float temp;

	eval_exp4(result);
	while ((op = *token) == '*' || op == '/' || op == '%') {
		get_token();
		if (op == '*' && !repeatset) {
			repeat = result;
			repeatset = true;
			if (*token == '[') return;
			eval_exp4(result);
			return;
		}
		eval_exp4(temp);
		switch (op) {
		case '*':
			result = result * temp;
			break;
		case '/':
			result = result / temp;
			break;
		case '%':
			result = (int)result % (int)temp;
			break;
		default:
			break;
		}
	}
}

// Process an exponent
void Myparser::eval_exp4(float& result)
{
	float temp, ex;
	int t; //removed register keyword to fix warning. Manishankar

	eval_exp5(result);
	if (*token == '^') {
		get_token();
		eval_exp4(temp);
		if (temp == 0.0f) {
			result = 1.0f;
			return;
		}
		result = pow(result, temp);
	}
}

// Evaluate a unary + or -.
void Myparser::eval_exp5(float& result)
{
	char  op; //removed register keyword to fix warning. Manishankar

	op = 0;
	if (((tok_type == DELIMITER) && *token == '+') || *token == '-') {  //warning resolved by Manishankar
		op = *token;
		get_token();
	}
	eval_exp6(result);
	if (op == '-') result = -result;
}

// Process a parenthesized expression.
void Myparser::eval_exp6(float& result)
{
	if (*token == '(') {  //warning resolved by Manishankar
		repeatset = true;
		get_token();
		eval_exp2(result);
		if (*token != ')')
			serror(1);
		get_token();
	}
	else atom(result);
}

// Get the value of a number.
void Myparser::atom(float& result)
{
	switch (tok_type) {
	case NUMBER:
		result = (float) atof(token);
		get_token();
		return;
	default:
		serror(0);
	}
}

// Display a syntax error.
void Myparser::serror(int error)
{
	static string e[] = {
		"Syntax Error",
		"Unbalanced Parentheses",
		"No expression Present"
	};
	LogError(CRHMException(string(e[error]) + " in module '" +
		LocalPar->module + "' parameter '" + LocalPar->param + "'", WARNING));

	for (int ll = row; ll < LocalPar->lay; ++ll) { // reset remainder of parameter values to 0
		for (int ii = col; ii < LocalPar->dim; ++ii)
			if (LocalPar->varType == CRHM::Float)
				LocalPar->layvalues[ll][ii] = 0.0f;
			else if (LocalPar->varType == CRHM::Int)
				LocalPar->ilayvalues[ll][ii] = 0;
	}
}

// Obtain the next token.
void Myparser::get_token()
{
	char* temp;  //removed register keyword to fix warning. Manishankar

	tok_type = 0;
	temp = token;
	*temp = '\0';

	if (!*exp_ptr) return; // at end of expression

	while (isspace(*exp_ptr)) ++exp_ptr; // skip over white space

	if (*exp_ptr == '!') { // make series
		Bang = 1;
		++exp_ptr;
	}

	//check if exp_ptr is pointing to a valid character, that is, one of +-*/%^=(),[]!
	if ((*exp_ptr) && strchr("+-*/%^=(),[]!", *exp_ptr)) {  // added ','
		tok_type = DELIMITER;
		// advance to next char
		*temp++ = *exp_ptr++;
	}
	else if (isalpha(*exp_ptr)) {
		while (!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
		tok_type = CRHM::VARIABLE;
	}
	else if (isdigit(*exp_ptr)) {
		while ((*exp_ptr) && strchr("0123456789.", *exp_ptr)) *temp++ = *exp_ptr++;
		if ((*exp_ptr) && strchr("eE", *exp_ptr)) {
			*temp++ = *exp_ptr++;
			while ((*exp_ptr) && strchr("+- ", *exp_ptr))  *temp++ = *exp_ptr++;
			while (!isdelim(*exp_ptr)) *temp++ = *exp_ptr++;
		}
		tok_type = NUMBER;
	}

	*temp = '\0';
}

// Return true if c is a delimiter.
int Myparser::isdelim(char c)
{
	if (((*exp_ptr) && strchr(" +-/*%^=(),[]", c)) || c == 9 || c == '\r' || c == 0)  // added ','  //warning resolved by Manishankar
		return 1;
	return 0;
}

ClassClark::ClassClark(const float* inVar, float* outVar, const float* kstorage, const float* lag, const long nhru, const float setlag)
	: inVar(inVar), outVar(outVar), kstorage(kstorage), nhru(nhru) {

	// kstorage (days)
	// lag (hours)

	LastIn = new float[nhru];
	LastOut = new float[nhru];

	c01 = new float[nhru];
	c2 = new float[nhru];
	NO_lag_release = new float[nhru];

	ilag = new long[nhru];
	maxlag = new long[nhru];
	ulag = new long[nhru];

	for (long hh = 0; hh < nhru; hh++) {

		c01[hh] = Global::Interval * 0.5f / (kstorage[hh] + Global::Interval * 0.5f);  // units of Global::Interval (days)
		c2[hh] = (kstorage[hh] - Global::Interval * 0.5f) / (kstorage[hh] + Global::Interval * 0.5f); // units of kstorage (days)

		ilag[hh] = max<float>(lag[hh], 0.0f) / 24.0f * Global::Freq + 1.1f; // =1 for lag of zero

		if (setlag == -1 || ilag[hh] > setlag)
			maxlag[hh] = ilag[hh] + 1; // Quick fix
		else
			maxlag[hh] = setlag + 1; // Quick fix

		ulag[hh] = 0;

		LastIn[hh] = 0.0f; // zero initial conditions
		LastOut[hh] = 0.0f; // zero initial conditions
		NO_lag_release[hh] = 0.0f; // released from storage
	}

	LagArray = new float* [nhru];   // create lag array

	for (long hh = 0; hh < nhru; hh++) {
		LagArray[hh] = new float[maxlag[hh]];
		for (long jj = 0; jj < maxlag[hh]; jj++)
			LagArray[hh][jj] = 0.0f;
	}
}

ClassClark::~ClassClark() {
	delete[] LastIn;
	delete[] LastOut;
	delete[] c01;
	delete[] c2;
	delete[] NO_lag_release;
	delete[] ilag;
	delete[] maxlag;
	delete[] ulag;

	for (long hh = 0; hh < nhru; hh++)
		delete[] LagArray[hh];
	delete[] LagArray;
}

float ClassClark::ChangeStorage(const float* kstorage, const long hh)
{
	float Last_c01 = c01[hh];
	float Last_c2 = c2[hh];

	if (c2[hh] >= 1.0f) // handles case of NO delay
		return 0.0f;

	float Sstorage = (1.0f / (1.0f - c2[hh])) * (c01[hh] * LastIn[hh] + c2[hh] * outVar[hh]);

	c01[hh] = Global::Interval * 0.5f / (kstorage[hh] + Global::Interval * 0.5f);  // units of Global::Interval (days)
	c2[hh] = (kstorage[hh] - Global::Interval * 0.5f) / (kstorage[hh] + Global::Interval * 0.5f); // units of kstorage (days)

	if (Sstorage <= 0.0f || Last_c01 == c01[hh]) return 0.0f;

	LastOut[hh] = (Sstorage * (1.0f - c2[hh]) - c01[hh] * LastIn[hh]) / c2[hh];

	//    Sstorage = (1.0f/(1.0f - c2[hh]))*(c01[hh]*LastIn[hh] + c2[hh]*LastOut[hh]); // debug line

	return Sstorage;
}

float ClassClark::ChangeLag(const float* newlag, const long hh) {

	float LastValue;
	float Lag_storage = 0.0f;

	long newilag = max<float>(newlag[hh], 0.0f) / 24.0f * Global::Freq + 1.1f; // =1 for lag of zero

	for (int ii = 1; ii < ilag[hh]; ++ii)
		Lag_storage += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];

	if (newilag == ilag[hh]) {
		return Lag_storage;
	}

	float* AccArray = new float[ilag[hh]]; // work area for ChangeLag
	AccArray[0] = 0.0f;
	for (int ii = 1; ii < ilag[hh]; ++ii)
		AccArray[ii] = AccArray[ii - 1] + LagArray[hh][(ulag[hh] + ii) % ilag[hh]]; // accumulate storage

	NO_lag_release[hh] = 0.0f;

	delete[] LagArray[hh]; // delete previous length

	LagArray[hh] = new float[newilag]; // create new length

	ulag[hh] = 0; // next input value save here.
	LagArray[hh][ulag[hh]] = 0; //

	for (int ii = 1; ii < newilag; ++ii) // clear remainder
		LagArray[hh][ii] = 0.0f;

	if (newilag == 1) { // all storage is released
		NO_lag_release[hh] = AccArray[ilag[hh] - 1];
	}
	else if (ilag[hh] > 1 && AccArray[ilag[hh] - 1] > 0.0f) {
		LastValue = 0.0f;

		for (int mm = 1; mm < newilag - 1; ++mm) {
			float Y = float(mm) / (newilag - 1) * (ilag[hh] - 1);
			int Yint = Y + 0.0001f;
			float Ydif = Y - Yint;
			float NewValue = AccArray[Yint] + Ydif * (AccArray[Yint + 1] - AccArray[Yint]);

			LagArray[hh][(ulag[hh] + mm) % newilag] = NewValue - LastValue;

			LastValue = NewValue;
		}

		LagArray[hh][(ulag[hh] + newilag - 1) % newilag] = AccArray[ilag[hh] - 1] - LastValue; // final values
	}
	// ilag == 1 and newilag > 1
	// if ilag == 1 or nothing in storage -> nothing to be done

	delete[] AccArray; // work area for ChangeLag

	ilag[hh] = newilag; // assign new lag

	return Lag_storage;
}

void ClassClark::DoClark() {

	for (long hh = 0; hh < nhru; hh++) {

		LagArray[hh][ulag[hh]] = inVar[hh] + NO_lag_release[hh];
		NO_lag_release[hh] = 0.0f;

		ulag[hh] = ++ulag[hh] % ilag[hh];

		outVar[hh] = c01[hh] * (LagArray[hh][ulag[hh]] + LastIn[hh]) + c2[hh] * LastOut[hh];

		LastIn[hh] = LagArray[hh][ulag[hh]];

		LastOut[hh] = outVar[hh];
	}
}

void ClassClark::DoClark(const long hh) {

	LagArray[hh][ulag[hh]] = inVar[hh] + NO_lag_release[hh];
	NO_lag_release[hh] = 0.0f;

	ulag[hh] = ++ulag[hh] % ilag[hh];  // now points to fully delayed value

	outVar[hh] = c01[hh] * (LagArray[hh][ulag[hh]] + LastIn[hh]) + c2[hh] * LastOut[hh];

	LastIn[hh] = LagArray[hh][ulag[hh]];

	LastOut[hh] = outVar[hh];
}

float ClassClark::Left(int hh) {

	float Slag = 0;

	for (int ii = 1; ii < ilag[hh]; ++ii)
		Slag += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];

	if (c2[hh] >= 1.0f) return 0.0f; // handles case of NO delay

	float Sstorage = (1.0f / (1.0f - c2[hh])) * (c01[hh] * LastIn[hh] + c2[hh] * outVar[hh]);

	return Slag + Sstorage;
}

//---------------------------------------------------------------------------
ClassMuskingum::ClassMuskingum(const float* inVar, float* outVar, const float* k, const float* X_M, const float* lag, const long nhru, const float setlag)
	: inVar(inVar), outVar(outVar), nhru(nhru) {

	// !!! UNITS !!!

	// kstorage (days)
	// lag (hours)

	LastIn = new float[nhru];
	LastOut = new float[nhru];

	c0 = new float[nhru];
	c1 = new float[nhru];
	c2 = new float[nhru];

	ilag = new long[nhru];
	maxlag = new long[nhru];
	ulag = new long[nhru];
	long Biggest = 0;

	for (long hh = 0; hh < nhru; hh++) {

		c0[hh] = (Global::Interval - 2.0f * k[hh] * X_M[hh]) /
			(2.0f * k[hh] * (1.0f - X_M[hh]) + Global::Interval);  // units of Global::Interval (days)

		c1[hh] = (Global::Interval + 2.0f * k[hh] * X_M[hh]) /
			(2.0f * k[hh] * (1.0f - X_M[hh]) + Global::Interval); // units of kstorage (days)

		c2[hh] = (2.0f * k[hh] * (1.0f - X_M[hh]) - Global::Interval) /
			(2.0f * k[hh] * (1.0f - X_M[hh]) + Global::Interval); // units of kstorage (days)

		ilag[hh] = max<float>(lag[hh], 0.0f) / 24.0f * Global::Freq + 1.1f; // =1 for lag of zero

		if (setlag == -1 || ilag[hh] > setlag)
			maxlag[hh] = ilag[hh];
		else
			maxlag[hh] = setlag;

		ulag[hh] = 0;

		LastIn[hh] = 0.0f; // zero initial conditions

		LastOut[hh] = 0.0f; // zero initial conditions

		if (maxlag[hh] > Biggest) Biggest = maxlag[hh];
	}

	LagArray = new float* [nhru];   // create lag array

	for (long hh = 0; hh < nhru; hh++) {
		LagArray[hh] = new float[maxlag[hh]];
		for (long jj = 0; jj < maxlag[hh]; jj++)
			LagArray[hh][jj] = 0.0f;
	}
}

ClassMuskingum::~ClassMuskingum() {
	delete[] LastIn;
	delete[] LastOut;
	delete[] c0;
	delete[] c1;
	delete[] c2;
	delete[] ilag;
	delete[] maxlag;
	delete[] ulag;

	for (long hh = 0; hh < nhru; hh++)
		delete[] LagArray[hh];
	delete[] LagArray;
}

void ClassMuskingum::ChangeLag(const float* newlag, const long hh)
{

	long newilag = max<float>(newlag[hh], 0.0f) / 24.0f * Global::Freq + 1.1f; // =1 for lag of zero

	if (newilag == ilag[hh]) return;

	float* AccArray = new float[ilag[hh]]; // work area for ChangeLag

	AccArray[0] = 0.0f;

	for (int ii = 1; ii < ilag[hh]; ++ii)
		AccArray[ii] = AccArray[ii - 1] + LagArray[hh][(ulag[hh] + ii) % ilag[hh]]; // accumulate storage

	delete[] LagArray[hh]; // delete previous length

	LagArray[hh] = new float[newilag]; // create new length

	ulag[hh] = 0; // next input value save here.
	LagArray[hh][0] = 0.0f; // looks better

	float LastValue = 0.0f;

	for (int mm = 1; mm < newilag - 1; ++mm) {
		float Y = float(mm) / (newilag - 1) * (ilag[hh] - 1);
		int Yint = Y + 0.0001f;
		float Ydif = Y - Yint;
		float NewValue = AccArray[Yint] + Ydif * (AccArray[Yint + 1] - AccArray[Yint]);

		LagArray[hh][(ulag[hh] + mm) % newilag] = NewValue - LastValue;

		LastValue = NewValue;
	}

	LagArray[hh][(ulag[hh] + newilag - 1) % newilag] = AccArray[ilag[hh] - 1] - LastValue; // final values

	delete[] AccArray; // work area for ChangeLag

	ilag[hh] = newilag; // assign new lag
}

void ClassMuskingum::DoMuskingum() {

	for (long hh = 0; hh < nhru; hh++) {

		LagArray[hh][ulag[hh]] = inVar[hh];

		ulag[hh] = ++ulag[hh] % ilag[hh];

		outVar[hh] = c0[hh] * LagArray[hh][ulag[hh]] + c1[hh] * LastIn[hh] + c2[hh] * LastOut[hh];

		LastIn[hh] = LagArray[hh][ulag[hh]];

		LastOut[hh] = outVar[hh];
	}
}

void ClassMuskingum::DoMuskingum(const long hh) {

	LagArray[hh][ulag[hh]] = inVar[hh];

	ulag[hh] = ++ulag[hh] % ilag[hh];  // now points to fully delayed value

	outVar[hh] = c0[hh] * LagArray[hh][ulag[hh]] + c1[hh] * LastIn[hh] + c2[hh] * LastOut[hh];

	LastIn[hh] = LagArray[hh][ulag[hh]];

	LastOut[hh] = outVar[hh];
}

float ClassMuskingum::Left(int hh) {

	float Slag = 0;

	for (int ii = 1; ii < ilag[hh]; ++ii)
		Slag += LagArray[hh][(ulag[hh] + ii) % ilag[hh]];

	float Sstorage = (1.0f / (1.0f - c2[hh])) * (c1[hh] * LastIn[hh] + c2[hh] * outVar[hh]);

	return Slag + Sstorage;
}

//---------------------------------------------------------------------------

long ClassModule::getdim(CRHM::TDim dimen) {
	MapDim::iterator itDim;
	string s;

	switch (dimen) {

	case CRHM::BASIN:
		return ((int)CRHM::ONE);

	case CRHM::ONE:
	case CRHM::TWO:
	case CRHM::THREE:
	case CRHM::FOUR:
	case CRHM::FIVE:
	case CRHM::SIX:
	case CRHM::SEVEN:
	case CRHM::EIGHT:
	case CRHM::NINE:
	case CRHM::TEN:
	case CRHM::ELEVEN:
	case CRHM::TWELVE:
		return ((int)dimen);

	case CRHM::NHRU:
		if (nhru)
			return (nhru);
		else
			return (Global::nhru);

	case CRHM::NOBS:
		return (Global::nhru);

	case CRHM::NLAY:
		return (Global::nlay);

	default:
		return (-1);
	}
}

//---------------------------------------------------------------------------
TAKA AKAtype(string type) {

	TAKA Type = AKAERROR;

	for (int ii = VARG; ii < AKAEND; ++ii)
		if (type == AKAstrings[ii]) {
			Type = (TAKA)ii;
			break;
		}
	return Type;
}

//---------------------------------------------------------------------------
bool ClassModule::Variation_Skip(void) {

	if ((Global::BuildFlag == CRHM::BUILD && variation == 0) ||                    // for Build screen   //warning resolved by Manishankar
		((variation_set & 2048) != 0 && variation == 0) ||                        // handles VARIATION_0
		(variation_set & 4096) != 0 ||                        // handles VARIATION_0
		(variation_set == 0) ||                                                // handles VARIATION_ORG
		(variation_set & variation) != 0)                                       // handles #1, #2, #4 etc.
		return false; // add
	else
		return true; // skip
}

//---------------------------------------------------------------------------
long ClassModule::declputparam(string source, string param, string units, float** value, float*** layvalue) {

	MapPar::iterator itPar;
	ClassPar* newPar = NULL;

	if (Variation_Skip()) {
		*value = NULL;
		return -1;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return -1;
	}

	case CRHM::DECL: { // only finds groups

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

		newPar = new ClassPar(string(Name.c_str()), string(param), CRHM::NHRU, "", 0, 0, "", units, CRHM::Float);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = CRHM::USUAL;

		if (this->GroupCnt)
			newPar->Inhibit_share = 2;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return -1;
	}

	case CRHM::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*value = newPar->values;
					if (layvalue != NULL)
						(*layvalue) = newPar->layvalues;  //const_cast<float **> (*layvalue) = newPar->layvalues;
				}
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				//          if(newPar->Inhibit_share != 2){ // 2 means no declare, ie not used.
				*value = newPar->values;
				if (layvalue != NULL)
					(*layvalue) = newPar->layvalues;  //const_cast<float **> (*layvalue) = newPar->layvalues;
													  //          }
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*value = newPar->values;
					if (layvalue != NULL)
						(*layvalue) = newPar->layvalues;  //const_cast<float **> (*layvalue) = newPar->layvalues;
				}
			}
			else if ((newPar = ClassParFindPar(param))) {
				if (newPar->Inhibit_share != 2) { // 2 means no declare, ie not used.
					*value = newPar->values;
					if (layvalue != NULL)
						(*layvalue) = newPar->layvalues;  //const_cast<float **> (*layvalue) = newPar->layvalues;
				}
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
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
long ClassModule::declgetparam(string source, string param, string units, const float** value, const float*** layvalue) {

	MapPar::iterator itPar;
	ClassPar* newPar;

	if (Variation_Skip()) {
		*value = NULL;
		return -1;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return -1;
	}

	case CRHM::DECL: {
		return -1;
	}

	case CRHM::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*value = newPar->values;
				if (layvalue != NULL)
					*layvalue = (const float**)newPar->layvalues;
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*value = (const float*)newPar->values;
				if (layvalue != NULL)
					*layvalue = (const float**)newPar->layvalues;
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*value = (const float*)newPar->values;
				if (layvalue != NULL)
					*layvalue = (const float**)newPar->layvalues;
			}
			else if ((newPar = ClassParFindPar(param))) {
				*value = newPar->values;
				if (layvalue != NULL)
					*layvalue = (const float**)newPar->layvalues;
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
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
	ClassPar* newPar = NULL;

	variation_max = variation_max | variation_set;

	AKAhook(PARD, Name, param, param); // handles explicit rename - redundant now ?

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
			CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
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

	CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
	LogError(Except);
	throw Except; // does not return
}
//---------------------------------------------------------------------------
long ClassModule::declputparam(string source, string param, string units, long** ivalue, long*** ilayvalue) {

	MapPar::iterator itPar;
	ClassPar* newPar = NULL;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return -1;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return -1;
	}

	case CRHM::DECL: {
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

		newPar = new ClassPar(string(Name.c_str()), string(param), CRHM::NHRU, "", 0, 0, "", units, CRHM::Int);

		newPar->basemodule = this->NameRoot;

		newPar->variation_set = variation_set;

		newPar->visibility = CRHM::USUAL;

		newPar->Inhibit_share = 2;

		Myparser ob;

		ob.eval_exp(newPar);

		PairPar Item = PairPar(Name + " " + param, newPar);
		Global::MapPars.insert(Item);
		return -1;
	}

	case CRHM::INIT: {
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
				CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
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
void ClassModule::declgetparam(string source, string param, string units, const long** ivalue, const long*** ilayvalue) {

	MapPar::iterator itPar;
	ClassPar* newPar;

	if (Variation_Skip()) {
		*ivalue = NULL;
		return;
	}

	variation_max = variation_max | variation_set;

	Convert convert; convert.CheckUnitsString(Name, param, units);

	AKAhook(PARD, Name, param, param); // handles explicit rename - redundant now ?

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {
		PairstrV Item2 = PairstrV(param.c_str(), variation_set);
		PairstrI Item = PairstrI(Name.c_str(), Item2);

		Global::Mapdeclpar.insert(Item);
		return;
	}

	case CRHM::DECL: {
		return;
	}

	case CRHM::INIT: {
		if (source[0] != '*') {
			if ((itPar = Global::MapPars.find(source + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long**)newPar->ilayvalues;
				return;
			}
		}
		else {
			if ((itPar = Global::MapPars.find(Name + " " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = (const long*)newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long**)newPar->ilayvalues;
				return;
			}
			else if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end()) {
				newPar = (*itPar).second;
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long**)newPar->ilayvalues;
				return;
			}
			else if ((newPar = ClassParFindPar(param))) { // handles other module
				*ivalue = newPar->ivalues;
				if (ilayvalue != NULL)
					*ilayvalue = (const long**)newPar->ilayvalues;
				return;
			}
			else {
				CRHMException Except("Parameter not found: " + Name + " " + param, TERMINATE);
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
