/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>

#include "ClassCRHM.h"
#include "Classfilter.h"
#include "../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"
#include "CRHMLogger.h"

using namespace std;

void setdim(string name, long dim) {
	string s = name;

	if (name == "nhru") {
		Update_Main_DIM(TDim::NHRU, dim);
	}
	else if (name == "nobs") {
		Update_Main_DIM(TDim::NOBS, dim);
	}
	else if (name == "nlay") {
		Update_Main_DIM(TDim::NLAY, dim);
	}
}

//---------------------------------------------------------------------------
ClassPar *ClassParFindShared(string name) { // where name is concatenation of MODULE and NAME
	MapPar::iterator itPar;

	if ((itPar = Global::SharedMapPars.find(name)) == Global::SharedMapPars.end()) {
		CRHMException Except("Could not find Parameter: " + name, TExcept::WARNING);
		LogError(Except);
		return NULL;
	}
	return ((*itPar).second);
}

//---------------------------------------------------------------------------
ClassPar *ClassParFind(string name) { // where name is concatenation of MODULE and NAME
	MapPar::iterator itPar;

	if ((itPar = Global::MapPars.find(name)) == Global::MapPars.end()) {
		CRHMException Except("Could not find Parameter: " + name, TExcept::WARNING);
		LogError(Except);
		return NULL;
	}
	return ((*itPar).second);
}

//---------------------------------------------------------------------------
ClassPar *ClassParFindPar(string name) { // where name is parameter
	MapPar::iterator itPar;
	ClassPar *thisPar;

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar) {
		thisPar = (*itPar).second;
		if (thisPar->param == name)
			return ((*itPar).second);
	}
	return (NULL);
}

//---------------------------------------------------------------------------
long ClassParFindParBld(ClassPar *thisPar) { // where parameter is BasinMapPars
	Mapstr::iterator itPar;                   // creates individual module parameters
	//ClassPar *newPar;
	string sparam, smodule;
	long Count = 0;

	for (itPar = Global::Mapdeclpar.begin(); itPar != Global::Mapdeclpar.end(); ++itPar) {
		sparam = (itPar->second.first).c_str();
		smodule = (itPar->first).c_str();
		if (sparam == thisPar->param) {
			MapPar::iterator itPar0 = Global::MapPars.find(smodule + ' ' + thisPar->param);
			if (itPar0 != Global::MapPars.end())
			{// already there?
				continue;
			}

			bool smoduleInOurModules = false;
			for (
				std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
				it != Global::OurModulesList->end();
				it++
				)
			{
				if (it->first == smodule.c_str())
				{
					smoduleInOurModules = true;
				}
			}

			if (smoduleInOurModules == false)
			{
				continue;
			}

			++Count;
			ClassPar *newPar = new ClassPar(*thisPar);
			newPar->module = smodule;
			PairPar Item = PairPar(newPar->module + ' ' + newPar->param, newPar);
			Global::MapPars.insert(Item);
		}
	}

	return (Count);
}

//---------------------------------------------------------------------------
void ClassParSet(ClassPar *p) {
	MapPar::iterator itPar;
	ClassPar *thisPar;

	// if new parameter is identical to 'Shared' version, delete it!

	if ((itPar = Global::MapPars.find("Shared " + p->param)) != Global::MapPars.end()) {
		thisPar = ((*itPar).second);
		if (thisPar->Same(*p)) {
			delete p;
			return;
		}
	}

	// if parameter already exists - change to new value and delete it!

	if ((itPar = Global::MapPars.find(p->module + ' ' + p->param)) != Global::MapPars.end()) {
		thisPar = ((*itPar).second);
		if (!thisPar->Same(*p) && thisPar->dim == p->dim)
			thisPar->Change(*p);
		delete p;
		return;
	}

	// create new parameter
	else {
		PairPar Item = PairPar(p->module + ' ' + p->param, p);
		Global::MapPars.insert(Item);
	}
}

//---------------------------------------------------------------------------
ClassPar *ClassParFind(string module, string param) { // routine concatenates MODULE and NAME
	MapPar::iterator itPar;

	if ((itPar = Global::MapPars.find(module + ' ' + param)) != Global::MapPars.end()) {
		return ((*itPar).second);
	}

	if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
		return ((*itPar).second);
	else {
		long jj = -1;
		if (Global::OldModuleName != NULL)
		{
			for (size_t i = 0; i < Global::OldModuleName->size(); i++)
			{
				if (module.c_str() == Global::OldModuleName->at(i))
				{
					jj = i;
				}
			}
		}
		if (jj > -1)
		{
			string s = Global::NewModuleName->at(jj) + ""; // two step to remove \0
			if ((itPar = Global::MapPars.find(s + ' ' + param)) != Global::MapPars.end()) {
				return ((*itPar).second);
			}
		}
		LogError(CRHMException("Parameter defined in module: " + param + ", " + module + " not found", TExcept::WARNING));
		return NULL;
	}
}

//---------------------------------------------------------------------------
ClassPar *ClassParFindRev(string module, string param) {
	MapPar::iterator itPar;

	if ((itPar = Global::MapPars.find("Shared " + param)) != Global::MapPars.end())
		return ((*itPar).second);

	if ((itPar = Global::MapPars.find(module + ' ' + param)) != Global::MapPars.end()) {
		return ((*itPar).second);
	}
	else {
		LogError(CRHMException("Parameter defined in module: " + param + ", " + module + " not found", TExcept::TERMINATE));
		return NULL;
	}
}


//---------------------------------------------------------------------------
ClassVar *ClassVarFind(string name) {
	MapVar::iterator itVar;

	if ((itVar = Global::MapVars.find(name)) == Global::MapVars.end())
		if ((itVar = Global::MapVars.find('#' + name)) == Global::MapVars.end()) { // could be local
			CRHMException Except("Could not find Variable: " + name, TExcept::WARNING);
			LogError(Except);
			return NULL;
		}
	return ((*itVar).second);
}


void ClassVar::review_HRU_OBS(void) {

	if (name == "t" || name == "t_max" || name == "t_min" || name == "rh" || name == "ea")
		HRU_OBS_indexed = 0;
	else if (name == "p" || name == "ppt")
		HRU_OBS_indexed = 1;
	else if (name == "u")
		HRU_OBS_indexed = 2;
	else if (name == "Qsi" || name == "SunAct" || name == "Qli")
		HRU_OBS_indexed = 3;
	else
		HRU_OBS_indexed = 4;
}

//Changed by Manishankar 2018/09/10
long julian(string when) {
	int Y, M, D, H, Min, Sec, Milli;
	double DtBegin;
	//CTime
	// calendar

	if (when == "start") {
//		StandardConverterUtility::DecodeDateTime(Global::DTstart, &Y, &M, &D, &H, &Min);
//		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);

		StandardConverterUtility::DecodeDate(Global::DTstart, Y, M, D);
		StandardConverterUtility::DecodeTime(Global::DTstart, H, Min, Sec, Milli);
		DtBegin = StandardConverterUtility::EncodeDate((Word)Y - 1, (Word)12, (Word)31);

		return  INT(Global::DTstart - DtBegin);  // -0.999/Global::Freq
	}
	else if (when == "end") {
//		StandardConverterUtility::DecodeDateTime(Global::DTend, &Y, &M, &D, &H, &Min);
//		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);

		StandardConverterUtility::DecodeDate(Global::DTend, Y, M, D);
		StandardConverterUtility::DecodeTime(Global::DTend, H, Min, Sec, Milli);
		DtBegin = StandardConverterUtility::EncodeDate((Word)Y - 1, (Word)12, (Word)31);

		return  INT(Global::DTend - DtBegin);
	}
	else { // now
//		StandardConverterUtility::DecodeDateTime(Global::DTnow, &Y, &M, &D, &H, &Min);
//		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);

		StandardConverterUtility::DecodeDate(Global::DTnow, Y, M, D);
		StandardConverterUtility::DecodeTime(Global::DTnow, H, Min, Sec, Milli);
		DtBegin = StandardConverterUtility::EncodeDate((Word)Y - 1, (Word)12, (Word)31);

		return  INT(Global::DTnow - DtBegin);
	}
}

//---------------------------------------------------------------------------
//Changed by Manishankar 2018/09/10

long julian(double DT) {
	int Y, M, D, H, Min, Sec, Milli;
	double DtBegin;

//	StandardConverterUtility::DecodeDateTime(DT, &Y, &M, &D, &H, &Min);
//	DtBegin = StandardConverterUtility::EncodeDateTime(Y - 1, 12, 31, 0, 0);

	StandardConverterUtility::DecodeDate(DT, Y, M, D);
	StandardConverterUtility::DecodeTime(DT, H, Min, Sec, Milli);
	DtBegin = StandardConverterUtility::EncodeDate(Y - 1, 12, 31);

	return  INT(DT - DtBegin);
}

//---------------------------------------------------------------------------
//Changed by Manishankar 2018/09/10

long MonthDaysCnt(double DT) {
	int Y, M, D; //, H, Min, Sec, Milli;
	double DTNext;

//	StandardConverterUtility::DecodeDateTime(DT, &Y, &M, &D, &H, &Min);
	StandardConverterUtility::DecodeDate(DT, Y, M, D);
	++M;

	if (M > 12) { // next year
		M = 1;
		++Y;
	}

//	DTNext = StandardConverterUtility::EncodeDateTime((Word)Y, (Word)M, (Word)D, 0, 0);
	DTNext = StandardConverterUtility::EncodeDate(Y, M, D);
	return  INT(DTNext - DT);
}


//---------------------------------------------------------------------------
//Changed by Manishankar 2018/09/10

double Julian(string when) {
	int Y, M, D; //, H, Min;
	double DtBegin;

	// calendar

	if (when == "start") {
		StandardConverterUtility::DecodeDate(Global::DTstart, Y, M, D);
		DtBegin = StandardConverterUtility::EncodeDate((Word)Y - 1, (Word)12, (Word)31);
		return  (double)(Global::DTstart - DtBegin);  // -0.999/Global::Freq
	}
	else if (when == "end") {
		StandardConverterUtility::DecodeDate(Global::DTend, Y, M, D);
		DtBegin = StandardConverterUtility::EncodeDate((Word)Y - 1, (Word)12, (Word)31);
		return  (double)(Global::DTend - DtBegin);
	}
	else { // now
		StandardConverterUtility::DecodeDate(Global::DTnow, Y, M, D);
		DtBegin = StandardConverterUtility::EncodeDate((Word)Y - 1, (Word)12, (Word)31);
		return  double((double)Global::DTnow - DtBegin);
	}
}


//---------------------------------------------------------------------------
bool last_timestep(void) {
	if (Global::DTindx == Global::DTmax - 1)
		return true;
	else
		return false;
}

//---------------------------------------------------------------------------
//Changed by Manishankar. 2018/09/11

void dattim(string type, long *itime) { // dimension itime[6]
	int Year, Month, Day, H, Min, Sec, Milli = 0;
	//int MSec; (unreferenced commented out jhs507)

	if (type == "start") {
		StandardConverterUtility::DecodeDate(Global::DTstart, Year, Month, Day);
		StandardConverterUtility::DecodeTime(Global::DTstart, H, Min, Sec, Milli);
	}
	else if (type == "end") {
		StandardConverterUtility::DecodeDate(Global::DTend, Year, Month, Day);
		StandardConverterUtility::DecodeTime(Global::DTend, H, Min, Sec, Milli);
	}
	else {
		StandardConverterUtility::DecodeDate(Global::DTnow, Year, Month, Day);
		StandardConverterUtility::DecodeTime(Global::DTnow, H, Min, Sec, Milli);
	}
	itime[0] = Year;
	itime[1] = Month;
	itime[2] = Day;
	itime[3] = H;
	itime[4] = Min;
	itime[5] = Sec;
}


//---------------------------------------------------------------------------
void dattim(double DT, long *itime) { // dimension itime[6]
	int Year, Month, Day, H, Min, Sec, Milli = 0;
	//int MSec; (unreferenced commented out jhs507)

	StandardConverterUtility::DecodeDate(DT, Year, Month, Day);
	StandardConverterUtility::DecodeTime(DT, H, Min, Sec, Milli);

	itime[0] = Year;
	itime[1] = Month;
	itime[2] = Day;
	itime[3] = H;
	itime[4] = Min;
	itime[5] = Sec;
}

//---------------------------------------------------------------------------
void ModVarRemove(MapVar & MapVars) {

	ClassVar *thisVar;
	ClassVar *thisVar2;
	ClassPar *thisPar;

	MapVar::iterator itVar;
	MapVar::iterator itVar2, itVar3;
	MapPar::iterator itPar;

	string S, S2;

	// No observation(ie < Read) - Removes all variable (obs and module).  Done indirectly,
	//   so that variable is deleted only once
	// Observation(ie > Read) - removes only module variables
	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		if (thisVar != NULL) {
			S = (*itVar).first;
			if (thisVar->varType < TVar::Read) {
				for (itVar2 = Global::MapVars.begin(); itVar2 != Global::MapVars.end(); itVar2++) {
					thisVar2 = (*itVar2).second;
					if (thisVar2 != NULL) {
						S2 = (*itVar2).first;
						if (thisVar == thisVar2)
							(*itVar2).second = NULL;
					}
				}
				if (thisVar->module != "")
					delete thisVar; // releases everything
				else
					S = "Fault";
			}
			else {
				// Observation - removes duplicate map entries to ClassVar leaving the 'obs' entries.

				if (S != ("obs " + thisVar->name))
					(*itVar).second = NULL;
			}
		} // if
	}  // for

	   // Removes entries from map.  Do it like this as iteration pointer cannot point to erased item
	   // Removes entries flagged above.

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end();) {
		thisVar = (*itVar).second;
		//    S = (*itVar).first;
		if (thisVar == NULL)
			Global::MapVars.erase(itVar++);
		else
			++itVar;
	}

	// Observation - demotes variables to simple observation type from ReadI and ReadF
	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		switch (thisVar->varType) {
		case TVar::ReadI:
			if (thisVar->lay > 0) { // handles NFREQ
				for (int ii = 0; ii < thisVar->lay; ++ii)
					delete[] thisVar->ilayvalues[ii];

				delete[] thisVar->ilayvalues;  //Array [nhru] [lay]
				thisVar->lay = 0;
				thisVar->ilayvalues = NULL;
			}

			delete[]thisVar->ivalues;
			thisVar->ivalues = NULL;
			thisVar->varType = TVar::Read;
			thisVar->dim = thisVar->cnt;
			break;
		case TVar::ReadF:

			if (thisVar->lay > 0) { // handles NFREQ
				for (int ii = 0; ii < thisVar->lay; ++ii)
					delete[] thisVar->layvalues[ii];

				delete[] thisVar->layvalues;  //Array [nhru] [lay]
				thisVar->lay = 0;
				thisVar->layvalues = NULL;
			}

			delete[]thisVar->values;
			thisVar->values = NULL;
			thisVar->varType = TVar::Read;
			thisVar->dim = thisVar->cnt;
			break;
		case TVar::Int:
		case TVar::Float:
			exit(1); // should never happen
		default:
			break;
		}
	}
	// No modules - No parameters !

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
		thisPar = (*itPar).second;
		delete thisPar;
	}
	Global::MapPars.clear();
	Global::SharedMapPars.clear();
}

//---------------------------------------------------------------------------
ClassVar *declread(string module, string name, long cnt, long offset,
	ClassData * FileData, string Comment) {
	MapVar::iterator itVar;
	ClassVar *thisVar;
	string s1(module);
	string s2(name);
	string units;

	if (Comment.empty())
		Comment = "No information in observation file";
	else {
		units = extract_units(Comment);
	}

	if (cnt > Global::nobs) {
		Global::nobs = cnt; // allow it to display
		Global::maxobs = cnt;
	}

	// executes following code only if observation file replaced
	if ((itVar = Global::MapVars.find(s1 + " " + s2)) != Global::MapVars.end()) {
		thisVar = (*itVar).second;
		if (thisVar->varType >= TVar::Read) {
			LogError(CRHMException("Duplicate Observation variable: " + s1 + " " + s2, TExcept::ERR));
			return NULL;
		}
		//    Convert convert; convert.CheckUnitsObs(units, thisVar->units, name); // check original observation units
		//    if(thisVar->FileData == NULL)
		//      return thisVar;

		thisVar->FileData = FileData;
		thisVar->cnt = cnt;
		thisVar->offset = offset;
		/*
		if(thisVar->cnt && thisVar->dim != thisVar->cnt) {
		thisVar->ReleaseM(); // releases everything

		if(thisVar->lay > 0) {
		thisVar->layvalues = new double *[thisVar->lay];
		for(int ii = 0; ii < thisVar->lay; ii++)
		thisVar->layvalues[ii] = new double[thisVar->dim];
		}
		thisVar->values = new double[thisVar->dim];
		}
		*/
		if (thisVar->varType == TVar::Int)
			thisVar->varType = TVar::ReadI;
		if (thisVar->varType == TVar::Float)
			thisVar->varType = TVar::ReadF;

		return thisVar;
	}

	thisVar = new ClassVar(module, name, cnt, offset, FileData);

	if (thisVar->name == "p" || thisVar->name == "ppt") // must be NHRU for routine "ReadVar" when obs file loaded after modules.
		thisVar->dimen = TDim::NHRU;

	thisVar->varType = TVar::Read;
	thisVar->units = units;
	thisVar->help = Comment;

	PairVar Item = PairVar(s1 + ' ' + s2, thisVar);
	Global::MapVars.insert(Item);

	return thisVar;
}

//---------------------------------------------------------------------------
void   Update_Main_DIM(TDim Dim, long dim) {
	//SendMessage(Global::crhmMain, WM_CRHM_Main_DIM, (unsigned int)Dim, (unsigned int)dim);
}

//---------------------------------------------------------------------------
void   Update_Main_Dirty(void) {
	//SendMessage(Global::crhmMain, WM_CRHM_Main_DIRTY, (unsigned int)0, (unsigned int)0);
}

//---------------------------------------------------------------------------

long getdim(TDim dimen) {
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
		return (Global::nhru);

	case TDim::NOBS:
		return (Global::nobs);

	case TDim::NLAY:
		return (Global::nlay);

	default:

		return(-1);
	}
}

//---------------------------------------------------------------------------
long getstep(void) { return Global::DTindx - Global::DTmin + 1; }

//---------------------------------------------------------------------------
bool laststep(void) { return (Global::DTindx == Global::DTmax - 1); }

//---------------------------------------------------------------------------
void setdim(TDim dimen, long dim) {
	MapDim::iterator itDim;
	string s;

	switch (dimen) {

	case TDim::NHRU: s = "nhru";
		Update_Main_DIM(TDim::NHRU, dim);
		break;

	case TDim::NOBS: s = "nobs";
		Update_Main_DIM(TDim::NOBS, dim);
		break;

	case TDim::NLAY: s = "nlay";
		Update_Main_DIM(TDim::NLAY, dim);
		break;

	default:

		return;
	}
}

//---------------------------------------------------------------------------
void   LogError(CRHMException Except)
{
	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_EXCEPTION, (unsigned int)&Except, 0);

	CRHMLogger::instance()->log_run_error(Except);


	if (Except.Kind == TExcept::TERMINATE)
	{
		CRHMLogger::instance()->log_to_console(Except.Message);
		CRHMLogger::instance()->get_run_logger()->flush();
		throw (Except);
	}
}

//---------------------------------------------------------------------------
void   LogError(string S, TExcept Kind)
{
	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_EXCEPTION1, (unsigned int)&S, (unsigned int)&Kind);

	CRHMException Except = CRHMException(S, Kind);

	CRHMLogger::instance()->log_run_error(Except);

	if (Except.Kind == TExcept::TERMINATE)
	{
		CRHMLogger::instance()->get_run_logger()->flush();
		throw (Except);
	}

}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, double V, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V, "ffFixed", 10, 4) + " " + S2;

	LogMessage(SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, double V, TExtra Opt) {

	string D, SS;
	switch (Opt) {
	case TExtra::BLANK:
		break;
	case TExtra::DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case TExtra::DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TExtra::TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	if (Opt == TExtra::BLANK)
		SS = S + FloatToStrF(V, "ffFixed", 10, 4);
	else
		SS = D + S + FloatToStrF(V, "ffFixed", 10, 4);


	CRHMLogger::instance()->log_run_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, long V, TExtra Opt) {

	string D, SS;
	switch (Opt) {
	case TExtra::BLANK:
		break;
	case TExtra::DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case TExtra::DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TExtra::TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	if (Opt == TExtra::BLANK)
		SS = S + to_string(V);
	else
		SS = D + S + to_string(V);

	CRHMLogger::instance()->log_run_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, TExtra Opt) {

	string D, SS;
	switch (Opt) {
	case TExtra::BLANK:
		break;
	case TExtra::DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case TExtra::DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TExtra::TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	if (Opt == TExtra::BLANK)
		SS = S;
	else
		SS = D + S;

	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, double V, TExtra Opt) {

	string A = string("HRU " + to_string(hh + 1) + ": ");
	string D;
	switch (Opt) {
	case TExtra::BLANK:
		break;
	case TExtra::DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case TExtra::DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TExtra::TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	string SS = A + D + S + FloatToStrF(V, "ffFixed", 10, 4);


	CRHMLogger::instance()->log_run_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, long V, TExtra Opt) {

	string A = string("HRU " + to_string(hh + 1) + ": ");
	string D;
	switch (Opt) {
	case TExtra::BLANK:
		break;
	case TExtra::DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case TExtra::DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TExtra::TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	string SS = A + D + S + to_string(V);

	CRHMLogger::instance()->log_run_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, TExtra Opt) {

	string A = string("HRU " + to_string(hh + 1) + ": ");
	string D;
	switch (Opt) {
	case TExtra::BLANK:
		break;
	case TExtra::DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case TExtra::DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TExtra::TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	string SS = A + D + S;

	CRHMLogger::instance()->log_run_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebug(char *S) {

	string SS = S;

	CRHMLogger::instance()->log_run_debug_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebug(long h, char *Text, double v) {

	string S = to_string(h) + to_string(1);
	S += Text + to_string(v);


	CRHMLogger::instance()->log_run_debug_message(S);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&S, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebugD(char *S) {

	string D = FormatString(Global::DTnow, "yy mm dd ");

	string SS = D + S;

	CRHMLogger::instance()->log_run_debug_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebugT(string S) {

	string D = FormatString(Global::DTnow, "yy mm dd hh nn ");

	string SS = "yy mm dd hh mm - ";
	SS += D + " - " + S;

	CRHMLogger::instance()->log_run_debug_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   Update_Main_Status(string S) {

	//SendMessage(Global::crhmMain, WM_CRHM_Main_STATUS, (unsigned int)&S, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, double V1, double V2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 4) + ' ' + FloatToStrF(V2, "ffFixed", 10, 4);
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, double V1, double V2, double V3, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 4) + " " + FloatToStrF(V2, "ffFixed", 10, 4) + " " + FloatToStrF(V3, "ffFixed", 10, 4);
	LogMessage(hh, SS.c_str(), Opt);
}
//---------------------------------------------------------------------------

void   LogMessageA(long hh, const char *S, double V1, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2);
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessageA(long hh, const char *S, double V1, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " + S2;
	LogMessage(hh, SS.c_str(), Opt);
}

void   LogMessageA(long hh, const char *S, double V1, const double HRU_area, const double Basin_area, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area / Basin_area, "ffFixed", 10, 3);
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessageA(long hh, const char *S, double V1, const double HRU_area, const double Basin_area, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area / Basin_area, "ffFixed", 10, 3) + " " + S2;
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessageA(long hh, const char *S, double V1, const double Basin_area, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1 / Basin_area, "ffFixed", 10, 3);
	LogMessage(hh, SS.c_str(), Opt);
}
//---------------------------------------------------------------------------

void   LogMessageA(long hh, const char *S, double V1, const double Basin_area, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1 / Basin_area, "ffFixed", 10, 3) + " " + S2;
	LogMessage(hh, SS.c_str(), Opt);
}
//---------------------------------------------------------------------------

long GetSharedUnit(string units) {
	const string delims("()/* \t,.-_");
	string::size_type begIdx, endIdx;
	begIdx = units.find_first_not_of(delims);

	while (begIdx != string::npos) {
		endIdx = units.find_first_of(delims, begIdx);
		if (endIdx == string::npos)
			endIdx = units.length();

		string name(units.substr(begIdx, endIdx - begIdx));

		if (name == "d")
			return Global::Freq;
		else if (name == "int")
			return 1;

		begIdx = units.find_first_not_of(delims, endIdx);
	}
	return 0; // was -1!!!!!!
}

//---------------------------------------------------------------------------
long julian_month(long Year, long julian) {
	int Y, Month, Day; //, H, Min;
	double DT = StandardConverterUtility::EncodeDate(Year - 1, 12, 31);

	DT += (double)julian;
	StandardConverterUtility::DecodeDate(DT, Y, Month, Day);
	return Month;
}

//---------------------------------------------------------------------------
string extract_units(string& Comment)
{
	string Lunits;
	string::size_type Idx, Idx2;

	Idx = Comment.find_first_of("(");
	if (Idx != string::npos) {
		Idx2 = Comment.find_first_of(")");
		if (Idx != string::npos) {
			Lunits = Comment.substr(Idx, Idx2 - Idx + 1);
			Comment = Comment.substr(Idx2 + 1);
			Idx = Comment.find_first_not_of(" \t");
			if (Idx != string::npos)
				Comment = Comment.substr(Idx);
			else
				Comment = "";
		}
	}
	return Lunits;
}


void   LogDebug(const char* S) {

	string SS = S;

	CRHMLogger::instance()->log_run_debug_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}
void   LogDebug(const string S) {

	string SS = S;

	CRHMLogger::instance()->log_run_debug_message(SS);

	//Old handler for Visual Studio Messages
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}
