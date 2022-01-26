#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>

#include "Classfilter.h"
#include "ClassCRHM.h"
#include "../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"

using namespace std;

Classfilter::Classfilter(ClassData* MyObs, string ToVar, string args, string argtypes) :
	MyObs(MyObs),
	ToVar(ToVar),
	args(args),
	argtypes(argtypes),
	Vs(0),
	Cs(0),
	Error(0),
	ObsCnt(0),
	TotalCnt(0),
	FirstTime(true)
{

	for (unsigned int ii = 0; ii < argtypes.length(); ++ii)
	{
		if (argtypes[ii] == 'V')
		{
			Vs++;
		}
		else if (argtypes[ii] == 'C')
		{
			Cs++;
		}
	}

	if (!ToVar.empty()) // 11/10/11
	{
		++Vs;
	}

	if (Vs)
	{
		Data = new double** [Vs];  // increment
		for (int ii = 0; ii < Vs; ++ii)
		{
			Data[ii] = NULL;
		}

		DataIndx = new long[Vs];
		DataObsCnt = new long[Vs];
	}

	if (Cs > 0)
	{
		Constants = new double[Cs];
	}
}

//---------------------------------------------------------------------------
void Classfilter::doFunctions(long Line)
{
	for (int jj = 0; jj < ObsCnt; ++jj)
	{
		doFunc(jj, Line);
	}
}

//---------------------------------------------------------------------------
Classfilter::~Classfilter() {

	if (Vs > 0) {
		if (!Error) // will not be assigned if error
			for (int jj = 0; jj < Vs; ++jj)
				delete[] Data[jj];
		delete[] Data;
		delete[] DataIndx;
		delete[] DataObsCnt;
	}
	if (Cs > 0) delete[] Constants;
}

//---------------------------------------------------------------------------
void Classfilter::error(string Mess) {

	string Mess2 = string(Mess);
	string F = string(string("\"") + typeid(*this).name());
	CRHMException Except(Mess2.c_str(), TExcept::ERR);
	////Application->MessageBox(Mess2.c_str(), string("Error in filter: " + F + "\" in observation file: \"" + MyObs->DataFileName.c_str() + "\"").c_str(), MB_OK);
	LogError(Except);
	Error = true;
}

//---------------------------------------------------------------------------
void Classfilter::fixup(void) { // must wait till memory allocated

	for (int ii = 0; ii < Vs; ++ii) {  // fixup Vs variables except destination
		if (!Data[ii])
			Data[ii] = new double* [ObsCnt];

		for (int jj = 0; jj < ObsCnt; ++jj) { // fixup all observations

			if (ii == Vs - 1 && DataIndx[ii] + jj < TotalCnt) { // array dimensioned ObsCnt
				if (MyObs->Data[TotalCnt + jj]) // was being deleted twice - should be fixed
					delete[] MyObs->Data[TotalCnt + jj];  // not used
				MyObs->Data[TotalCnt + jj] = NULL;    // indicate to destructor
			}

			int jjj = jj;
			if (jjj > DataObsCnt[ii] - 1) // source may not have dimension ObsCnt
				jjj = DataObsCnt[ii] - 1; // variable has too few observations
			double* X = MyObs->Data[DataIndx[ii] + jjj];
			Data[ii][jj] = X;
		}
	}
}

//---------------------------------------------------------------------------

void Classfilter::readargs()
{

	MapVar::iterator itVar;
	ClassVar* thisVar;
	istringstream instr;
	double C;
	string V;

	long ee = args.find(")");
	string Comment = args.substr(ee + 1, args.size());
	Common::trim(Comment);
	if (Comment.empty())
	{
		Comment = "filter";
	}
	else
	{
		long tt;
		while (tt = Comment.find("\\t"), tt != string::npos)
		{
			Comment.erase(tt, 1);
			Comment[tt] = ' ';
		}
	}

	args = args.substr(1, ee - 1);
	while (ee = args.find(','), ee > 0)
	{
		args[ee] = ' ';
	}

	instr.str(args);
	unsigned long Cnt;
	long IndexC = 0;
	long IndexV = 0;
	long pp, pp2;

	// allow for output location
	for (Cnt = 0; Cnt < argtypes.length(); ++Cnt)
	{
		instr >> V;
		if (instr.fail())
		{
			break;
		}

		pp = V.find_first_not_of("0123456789 //:.+-Ee_");
		if (pp == -1)
		{
			// constant
			if (argtypes[Cnt] != 'C')
			{
				error("expected constant");
				return;
			}

			pp = V.find_first_of("://_");
			if (pp != -1)
			{ // time
				pp2 = V.find_first_of("_");
				if (pp2 == -1)
				{
					if (V[pp] == '/')
					{
						C = StrToDate(V);
					}
					else
					{
						C = StrToTime(V);
					}
				}
				else
				{
					string z(V, 1, pp2 - 1);
					C = StrToDate(z);
					z.assign(V, pp2 + 1, V.size());
					C += double(StrToTime(z) - 1.0 / Global::Freq);
				}
			}
			else
			{
				C = Common::StrtoDt(V);
			}

			Constants[IndexC++] = C;
		}
		else
		{
			// variable
			if (argtypes[Cnt] != 'V')
			{
				error("expecting CONSTANT");
				return;
			}

			if ((itVar = Global::MapVars.find("obs " + V)) != Global::MapVars.end())
			{
				thisVar = (*itVar).second;
				if (thisVar->varType < TVar::Read)
				{
					error("not observation variable");
					return;
				}
			}
			else
			{
				error("unknown variable");
				return;
			}

			DataIndx[IndexV] = thisVar->offset;
			DataObsCnt[IndexV] = thisVar->dim;
			++IndexV;

			if (ObsCnt == 0 || thisVar->dim < ObsCnt)
			{
				ObsCnt = thisVar->dim;
			}
		}
	}

	if (Cnt != argtypes.length())
	{
		error("too few arguments");
		return;
	}

	if (Cnt > argtypes.length())
	{
		error("too many arguments");
		return;
	}

	if (!ToVar.empty())
	{

		TotalCnt = MyObs->DataCnt + MyObs->FilterCnt;
		if (ObsCnt == 0) ++ObsCnt; // handle case of constant

		MyObs->FilterCnt += ObsCnt;

		if ((itVar = Global::MapVars.find("obs " + ToVar)) != Global::MapVars.end())
		{
			thisVar = (*itVar).second;
			if (thisVar->varType >= TVar::Read)
			{
				DataIndx[Vs - 1] = thisVar->offset;
				DataObsCnt[Vs - 1] = ObsCnt;
				return;
			}
		}

		thisVar = declread("obs", ToVar, ObsCnt, TotalCnt, MyObs, Comment); // creates or re-uses
		DataIndx[Vs - 1] = TotalCnt;
		DataObsCnt[Vs - 1] = ObsCnt;
		thisVar->review_HRU_OBS();
	}
}

double estar(double t) /* Saturation vapour pressure */
{
	if (t > 0.0)
	{
		return 0.611 * exp(17.27 * t / (t + 237.3));
	}
	else
	{
		return 0.611 * exp(21.88 * t / (t + 265.5));
	}
}
