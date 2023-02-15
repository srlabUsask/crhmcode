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

#include "ClassVar.h"
#include "ClassCRHM.h"
#include "../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"

using namespace std;

long Index_;

ClassVar::ClassVar(string module, string name, TDim dimen,
	string help, string units, TVar varType, bool PointPlot, int Grpdim, int defdim)
	: module(module), name(name), DLLName(""), root(""), varType(varType), lay(0), nfreq(false),
	optional(false), StatVar(false), InGroup(0), visibility(TVISIBLE::USUAL), FunKind(TFun::FOBS),
	help(help), units(units), layvalues(NULL), ilayvalues(NULL), dim(0), dimMax(0),
	values(NULL), ivalues(NULL), offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0),
	UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(PointPlot), TchrtOpt(0),
	dimen(dimen) {

	if (Grpdim == 0)
		Grpdim = Global::nhru;

// Allow 'dim' to be overridden as necessary (PRL)
	if (dimen == TDim::NOBS)
		dim = Global::nobs;
	else
		dim = Grpdim;

	if (dimen == TDim::NLAY)
		lay = Global::nlay;
	else if (dimen == TDim::NFREQ) {
		lay = Global::Freq;
		nfreq = true;
	}
	else if (dimen == TDim::NDEF) {
		lay = defdim;
		dim = 1;
	}
	else if (dimen == TDim::NDEF2) {
		lay = 0;
		dim = defdim;
	}
	else if (dimen == TDim::NDEFN) {
		lay = defdim;
		dim = Grpdim;
	}
	else if (dimen == TDim::NREB)
		lay = Grpdim; // memory allocated by variables found
	else
		lay = 0;

	try {
		if (varType == TVar::Float) {
			if (lay > 0) {
				layvalues = new double* [lay];
				if (dimen != TDim::NREB) { // NREB does not own lay memory only HRU memory
					for (int ii = 0; ii < lay; ii++)
						layvalues[ii] = new double[dim];
					values = layvalues[0]; // sets to first layer

					for (int jj = 0; jj < lay; ++jj)
						for (int kk = 0; kk < dim; ++kk)
							layvalues[jj][kk] = 0.0;
				}
			}

			if (lay == 0 || dimen == TDim::NREB) {
				values = new double[dim];
				for (int kk = 0; kk < dim; ++kk)
					values[kk] = 0.0;
			}
		}
		else if (varType == TVar::Int) {
			if (lay > 0) {
				ilayvalues = new long* [lay];
				if (dimen != TDim::NREB) { // NREB does not own lay memory only HRU memory
					for (int ii = 0; ii < lay; ii++)
						ilayvalues[ii] = new long[dim];
					ivalues = ilayvalues[0];

					for (int jj = 0; jj < lay; ++jj)
						for (int kk = 0; kk < dim; ++kk)
							ilayvalues[jj][kk] = (int)0.0;
				}
			}

			if (lay == 0 || dimen == TDim::NREB) {
				ivalues = new long[dim];
				for (int kk = 0; kk < dim; ++kk)
					ivalues[kk] = 0;
			}
		}
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassVar.", TExcept::TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
}


ClassVar::ClassVar(string module, string name, long dim,
	string help, string units, TVar varType, bool PointPlot)
	: module(module), name(name), DLLName(""), root(""), varType(varType), dim(dim), dimMax(0), lay(0), nfreq(false),
	optional(false), StatVar(false), InGroup(0), visibility(TVISIBLE::USUAL), FunKind(TFun::FOBS),
	help(help), units(units), layvalues(NULL), ilayvalues(NULL),
	values(NULL), ivalues(NULL), offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0),
	UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(PointPlot), TchrtOpt(0),
	dimen(TDim::NHRU) {


	try {
		if (varType == TVar::Float)
			values = new double[dim];
		else if (varType == TVar::Int)
			ivalues = new long[dim];
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassVar.", TExcept::TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
}


//---------------------------------------------------------------------------
void ClassVar::BackUp() {

	long Fix = lay;
	if (lay == 0) Fix = 1;

	if (varType == TVar::Float) {
		layvaluesBkup = new double* [Fix];
		for (int ii = 0; ii < Fix; ii++)
			layvaluesBkup[ii] = new double[dim];

		for (int jj = 0; jj < Fix; jj++)
			for (int ii = 0; ii < dim; ii++)
				if (lay == 0 && jj == 0)
					layvaluesBkup[jj][ii] = values[ii];
				else
					layvaluesBkup[jj][ii] = layvalues[jj][ii];
	}
	else if (varType == TVar::Int) {
		ilayvaluesBkup = new long* [Fix];
		for (int ii = 0; ii < Fix; ii++)
			ilayvaluesBkup[ii] = new long[dim];

		for (int jj = 0; jj < Fix; jj++)
			for (int ii = 0; ii < dim; ii++)
				if (lay == 0 && jj == 0)
					ilayvaluesBkup[jj][ii] = ivalues[ii];
				else
					ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
	}
}


void ClassVar::Restore() {

	long Fix = lay;
	if (lay == 0) Fix = 1;

	if (varType == TVar::Float) {

		for (int jj = 0; jj < Fix; jj++)
			for (int ii = 0; ii < dim; ii++)
				if (lay == 0 && jj == 0)
					values[ii] = layvaluesBkup[jj][ii];
				else
					layvalues[jj][ii] = layvaluesBkup[jj][ii];


		for (int ii = 0; ii < Fix; ++ii)
			delete[] layvaluesBkup[ii];
		delete[] layvaluesBkup;  //Array [nhru] [lay]
		layvaluesBkup = NULL;
	}
	else if (varType == TVar::Int) {

		for (int jj = 0; jj < Fix; jj++)
			for (int ii = 0; ii < dim; ii++)
				if (lay == 0 && jj == 0)
					ivalues[ii] = ilayvaluesBkup[jj][ii];
				else
					ilayvalues[jj][ii] = ilayvaluesBkup[jj][ii];

		for (int ii = 0; ii < Fix; ++ii)
			delete[] ilayvaluesBkup[ii];
		delete[] ilayvaluesBkup; //Array [nhru] [lay]
		ilayvaluesBkup = NULL;
	}
}


ClassVar::ClassVar(const ClassVar& Cl) { // used for observation totals +

	module = Cl.module;
	root = Cl.root;
	name = Cl.name;
	help = Cl.help;
	units = Cl.units;
	dim = Cl.dim;
	dimMax = Cl.dimMax;
	variation_set = Cl.variation_set;
	dimen = Cl.dimen;
	lay = Cl.lay;

	varType = Cl.varType;
	visibility = Cl.visibility;
	optional = Cl.optional;
	PointPlot = Cl.PointPlot;
	TchrtOpt = Cl.TchrtOpt;
	VarFunct = Cl.VarFunct;
	StatVar = Cl.StatVar;
	InGroup = Cl.InGroup;
	nfreq = Cl.nfreq;
	FunKind = Cl.FunKind;

	ivalues = NULL;

	ilayvalues = NULL;
	layvalues = NULL;

	offset = Cl.offset;
	cnt = Cl.cnt;
	if (Cl.FileData)

		FileData = new ClassData(*Cl.FileData);
	else
		FileData = NULL;

	HRU_OBS_indexed = Cl.HRU_OBS_indexed;

	UserFunct = Cl.UserFunct;
	FunctVar = Cl.FunctVar;
	CustomFunct = Cl.CustomFunct;
	CustomFunctName = Cl.CustomFunctName;
	No_ReadVar = Cl.No_ReadVar;

	if (lay > 0) {
		layvalues = new double* [lay];
		if (dimen != TDim::NREB) { // NREB does not own lay memory only HRU memory
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new double[dim];
			values = layvalues[0];

			for (int jj = 0; jj < lay; ++jj)
				for (int kk = 0; kk < dim; ++kk)
					layvalues[jj][kk] = 0.0;
		}
	}

	if (lay == 0 || dimen == TDim::NREB) {
		varType = TVar::Float; // display always double. handles integer variables from VarObsFunct_Update
		values = new double[dim];
		ivalues = NULL;
		for (int kk = 0; kk < dim; ++kk)
			values[kk] = 0.0;
	}
}


ClassVar& ClassVar::operator=(const ClassVar& Cl) { // not used ever

	if (this == &Cl) return *this;

	module = Cl.module;
	root = Cl.root;
	name = Cl.name;
	help = Cl.help;
	units = Cl.units;
	dim = Cl.dim;
	dimMax = Cl.dimMax;
	variation_set = Cl.variation_set;
	dimen = Cl.dimen;
	lay = 0;

	varType = Cl.varType;
	visibility = Cl.visibility;
	optional = Cl.optional;
	PointPlot = Cl.PointPlot;
	TchrtOpt = Cl.TchrtOpt;
	VarFunct = Cl.VarFunct;
	StatVar = Cl.StatVar;
	InGroup = Cl.InGroup;
	nfreq = Cl.nfreq;
	FunKind = Cl.FunKind;

	ivalues = NULL;
	values = NULL;
	ilayvalues = NULL;
	layvalues = NULL;

	offset = Cl.offset;
	cnt = Cl.cnt;
	FileData = Cl.FileData;

	HRU_OBS_indexed = Cl.HRU_OBS_indexed;

	UserFunct = Cl.UserFunct;
	FunctVar = Cl.FunctVar;
	CustomFunct = Cl.CustomFunct;
	CustomFunctName = Cl.CustomFunctName;
	No_ReadVar = Cl.No_ReadVar;

	return *this;
}


void ClassVar::ReleaseM(bool Keep) {
	if (!values && !ivalues) return;

	if (varType == TVar::Float || varType == TVar::ReadF) {

		if (lay > 0) {
			if (dimen != TDim::NREB)
				values = NULL;    // values was set to layvalues[0] which will be deleted

			if (dimen != TDim::NREB) // NREB does not own lay memory only HRU memory
				for (int ii = 0; ii < lay; ++ii)
					delete[] layvalues[ii];

			delete[] layvalues;  //Array [nhru] [lay]
			layvalues = NULL;
		}

		if (!Keep && values != NULL) {
			delete[] values;
			values = NULL;
		}
	}
	else if (varType == TVar::Int || varType == TVar::ReadI) {

		if (lay > 0) {
			if (dimen != TDim::NREB)
				ivalues = NULL;

			if (dimen != TDim::NREB) // NREB does not own lay memory only HRU memory
				for (int ii = 0; ii < lay; ++ii)
					delete[] ilayvalues[ii];

			delete[] ilayvalues;  //Array [nhru] [lay]
			ilayvalues = NULL;
		}

		if (!Keep && ivalues != NULL) {
			delete[] ivalues;
			ivalues = NULL;
		}
	}
}


void ClassVar::ReadVar(void) {

	if (FileData->Times == NULL) {
		if (varType == TVar::ReadF || varType == TVar::Read) {
			if (dimen == TDim::NHRU)
				for (long ii = 0; ii < dim; ++ii)
					values[ii] = FileData->Data
					[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin];
			else {
				bool exists = (Global::DTindx / FileData->ModN >= FileData->IndxMin) && (Global::DTindx / FileData->ModN <= FileData->IndxMax);
				long cnt0 = min<long>(cnt, dim);
				for (long ii = 0; ii < cnt0; ++ii)
					if (exists)
					{
						long hruvalue = Global::HRU_OBS[HRU_OBS_indexed][ii];
						long index1 = offset + min<long>(hruvalue, cnt) - 1;
						long index2 = Global::DTindx / FileData->ModN - FileData->IndxMin;
						values[ii] = FileData->Data[index1][index2];
					}
					else
					{
						values[ii] = xLimit;
					}
			}
		}
		else if (varType == TVar::ReadI)
		{
			if (dimen == TDim::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
				{
					ivalues[ii] = int(FileData->Data
						[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] + 0.5);
				}
			}
			else {
				bool exists = (Global::DTindx / FileData->ModN >= FileData->IndxMin) && (Global::DTindx / FileData->ModN <= FileData->IndxMax);
				for (long ii = 0; ii < cnt; ++ii)
				{
					if (exists)
					{
						ivalues[ii] = int(FileData->Data
							[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] + 0.5);
					}
					else
					{
						ivalues[ii] = lLimit;
					}
				}
			}
		}
	}
	else if (FileData->GoodInterval) { // sparse data
		if (varType == TVar::ReadF || varType == TVar::Read)
		{
			if (dimen == TDim::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
					values[ii] = FileData->Data
					[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx];
			}
			else
			{
				for (long ii = 0; ii < cnt; ++ii)
				{
					values[ii] = FileData->Data
						[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx];
				}
			}
		}
		else if (varType == TVar::ReadI)
		{
			if (dimen == TDim::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
				{
					ivalues[ii] = int(FileData->Data
						[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] + 0.5);
				}
			}
			else
			{
				for (long ii = 0; ii < cnt; ++ii)
				{
					ivalues[ii] = int(FileData->Data
						[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] + 0.5);
				}
			}
		}
	}
	else {
		double doN = dim;
		if (dimen == TDim::NOBS)
			doN = cnt;
		if (varType == TVar::ReadF || varType == TVar::Read)
			for (long ii = 0; ii < doN; ++ii)
				values[ii] = xLimit;

		else if (varType == TVar::ReadI)
			for (long ii = 0; ii < doN; ++ii)
				ivalues[ii] = lLimit;
	}
}


void ClassVar::WriteVar(void) {

	if (FileData->Times == NULL) {
		if (varType == TVar::ReadF || varType == TVar::Read)
		{
			if (dimen == TDim::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] = values[ii];
			}
			else
			{
				for (long ii = 0; ii < cnt; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] = values[ii];
			}
		}

		else if (varType == TVar::ReadI)
		{
			for (long ii = 0; ii < dim; ++ii)
				FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] = ivalues[ii];
		}
		else
		{
			for (long ii = 0; ii < cnt; ++ii)
				FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] = ivalues[ii];
		}
	}
	else if (FileData->GoodInterval) { // sparse data
		if (varType == TVar::ReadF || varType == TVar::Read)
		{
			if (dimen == TDim::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] = values[ii];
			}
			else
			{
				for (long ii = 0; ii < cnt; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] = values[ii];
			}
		}
		else if (varType == TVar::ReadI)
		{
			if (dimen == TDim::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] = (double)ivalues[ii];
			}
			else
			{
				for (long ii = 0; ii < cnt; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] = (double)ivalues[ii];
			}
		}
	}
}


//---------------------------------------------------------------------------
void ClassVar::Intvl(void) {  // used for NFREQ observation reads - Tday, RHday and EAday
	double X;

	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {

			//modified by Manishankar
			long t1 = min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt);

			//long t1 = 0;
			long t2 = this->offset;

			long t3 = (Global::DTindx + tt) / FileData->ModN;
			long t4 = FileData->IndxMin;
			long firstindex = t2 + t1 - 1;

			if (firstindex < 0) { firstindex = 0; }

			X = FileData->Data[firstindex][t3 - t4];

			if (layvalues != NULL)
				layvalues[tt][ii] = X;
			else
				ilayvalues[tt][ii] = int(X);
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::LoopFirst(long dim_n) { // only first interval of day

	Index_ = Global::DTindx / FunctVar->FileData->ModN;

	(this->*(this->UserFunct_))(dim_n);

}

//---------------------------------------------------------------------------
void ClassVar::LoopLast(long dim_n) { // only last interval of day


	Index_ = Global::DTindx / FunctVar->FileData->ModN + FunctVar->FileData->Freq - 1;

	(this->*(this->UserFunct_))(dim_n);

}

//---------------------------------------------------------------------------
void ClassVar::LoopRange(long dim_n) { // all intervals of day

	Index_ = Global::DTindx / FunctVar->FileData->ModN;

	do {
		(this->*(this->UserFunct_))(dim_n);
	} while (++Index_ % FunctVar->FileData->Freq != 0);
}

//---------------------------------------------------------------------------
void ClassVar::Tot_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] += X;

};

//---------------------------------------------------------------------------
void ClassVar::Pos_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt - 1)][Index_ - FunctVar->FileData->IndxMin];
	if (X > 0.0)
		values[dim_n] += X;

};

//---------------------------------------------------------------------------
void ClassVar::Max_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X > values[dim_n])
		values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::Min_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X < values[dim_n])
		values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::Last_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::First_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::Avg_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] += X / this->FileData->Freq;

};

//---------------------------------------------------------------------------
void ClassVar::Count_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X > 0.0)
		values[dim_n] += (double)1.0 / this->FileData->Freq;

};

//---------------------------------------------------------------------------
void ClassVar::Count0_(long dim_n) {

	double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X == 0.0)
		values[dim_n] += (double)1.0 / this->FileData->Freq;

};

//---------------------------------------------------------------------------
void ClassVar::Avg(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;
	long Count = 0;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 0.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {


			//modified by Manishankar
			long firstindex = FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1;
			//long firstindex = 0;
			long secondindex = Index - FunctVar->FileData->IndxMin;
			if (firstindex < 0) { firstindex = 0; }
			double X = FunctVar->FileData->Data[firstindex][secondindex];
			values[ii] += X;
		}
		Count++;
	} while (++Index % FunctVar->FileData->Freq != 0);

	for (long ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] / Count;
	}
};

//---------------------------------------------------------------------------
void ClassVar::Max(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = -100000.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X > values[ii]) values[ii] = X;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Min(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 100000.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X < values[ii]) values[ii] = X;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Dtot(void) { // day total

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 0.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			values[ii] += X;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Tot(void) { // running total from the beginning

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			values[ii] += X;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Last(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN + FunctVar->FileData->Freq - 1;

	for (long ii = 0; ii < this->dim; ++ii) {
		double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
		values[ii] = X;
	}
};

//---------------------------------------------------------------------------
void ClassVar::First(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) {
		double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
		values[ii] = X;
	}
};

//---------------------------------------------------------------------------
void ClassVar::Peak(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X > values[ii]) values[ii] = X;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Count(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;
	double Divisor = (double)FunctVar->FileData->ModN;

	if (this->root != "") // VarObsFunct - normalise to daily value
		Divisor = (double)this->FileData->Freq;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X > 0.0)
				values[ii] += (double)1.0 / Divisor;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Count0(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;
	double Divisor = (double)FunctVar->FileData->ModN;

	if (this->root != "") // VarObsFunct - normalise to daily value
		Divisor = (double)this->FileData->Freq;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X == 0.0)
				values[ii] += (double)1.0 / Divisor;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Pos(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 0.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			double X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt - 1)][Index - FunctVar->FileData->IndxMin];
			if (X > 0.0) values[ii] += X;
		}
	} while (++Index % FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::do_t(ClassModule* thisModule) { // adjusts t_max and t_min observations for lapse rate and climate warming

	for (int ii = 0; ii < this->dim; ++ii) // does this step
		values[ii] -= Global::lapse_rate[ii] * (double)(Global::hru_elev[ii] - Global::OBS_ELEV[0][ii]) / (double)100.0;
	// should original t be saved for ea
};

//---------------------------------------------------------------------------
void ClassVar::do_t_Clim(ClassModule* thisModule) { // adjusts t_max and t_min observations for lapse rate and climate warming

	do_t(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) // does this step
		values[ii] += Global::Warming_t[ii];
	// should original t be saved for ea
};

//---------------------------------------------------------------------------
void ClassVar::do_ppt(ClassModule* thisModule) { // adjusts observation for lapse rate

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] * ((double)1.0 + (Global::hru_elev[ii] - Global::OBS_ELEV[1][ii]) / (double)100.0 * Global::ppt_adj[ii]);
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_p(ClassModule* thisModule) { // adjusts observation for lapse rate

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = FunctVar->values[ii] * ((double)1.0 + (Global::hru_elev[ii] - Global::OBS_ELEV[1][ii]) / (double)100.0 * Global::ppt_adj[ii]);
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_p_Clim(ClassModule* thisModule) { // adjusts observation for lapse rate

	do_p(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] * Global::Warming_p[ii];
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_ppt_Clim(ClassModule* thisModule) { // adjusts observation for lapse rate

	do_ppt(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] * Global::Warming_p[ii];
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_t_day(ClassModule* thisModule) { // FUNCTION - adjusts observation for lapse rate and handles climate warming
	for (int ii = 0; ii < this->dim; ++ii) {
		double Fix = (double)(Global::lapse_rate[ii] * (Global::hru_elev[ii] - Global::OBS_ELEV[0][ii]) / 100.0);
		for (int tt = 0; tt < Global::Freq; ++tt) {
			Global::obs_t_obs[tt][ii] = layvalues[tt][ii]; // save original values
			layvalues[tt][ii] -= Fix; // make lapse rate correction
			Global::obs_t[tt][ii] = layvalues[tt][ii];
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_t_day_Clim(ClassModule* thisModule) { // FUNCTION - adjusts observation for lapse rate and handles climate warming
	do_t_day(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			Global::obs_t_obs[tt][ii] = layvalues[tt][ii]; // save original values
			layvalues[tt][ii] += Global::Warming_t[ii]; // make temperature offset
			Global::obs_t[tt][ii] = layvalues[tt][ii];
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_rh_day(ClassModule* thisModule) { // FUNCTION - RH available

	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			if (Global::RH_VP_flag[ii]) { // maintain ea if possible
				Global::obs_ea[tt][ii] = (double)(Common::estar(Global::obs_t[tt][ii]) * layvalues[tt][ii] / 100.0); // use new t
				if (Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii]) { // new t lower, could be supersaturated
					double New_es = (double)Common::estar(Global::obs_t[tt][ii]); // maximum ea from new t
					if (Global::obs_ea[tt][ii] > New_es) {
						Global::obs_ea[tt][ii] = New_es;  // in saturation
						layvalues[tt][ii] = 100.0; // adjust RH
					}
					else
						layvalues[tt][ii] = (double)(Global::obs_ea[tt][ii] / New_es * 100.0); // adjust RH
				}
			}
			else // maintain RH
				Global::obs_ea[tt][ii] = (double)(Common::estar(Global::obs_t[tt][ii]) * layvalues[tt][ii] / 100.0); // adjust ea
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_rh_day_Clim(ClassModule* thisModule) { // FUNCTION - RH available

	do_rh_day(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			if (Global::RH_VP_flag2[ii]) { // maintain ea if possible
				Global::obs_ea[tt][ii] = (double)(Common::estar(Global::obs_t[tt][ii]) * layvalues[tt][ii] / 100.0); // use new t
				if (Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii]) { // new t lower, could be supersaturated
					double New_es = (double)Common::estar(Global::obs_t[tt][ii]); // maximum ea from new t
					if (Global::obs_ea[tt][ii] > New_es) {
						Global::obs_ea[tt][ii] = New_es;  // in saturation
						layvalues[tt][ii] = 100.0; // adjust RH
					}
					else
						layvalues[tt][ii] = (double)(Global::obs_ea[tt][ii] / New_es * 100.0); // adjust RH
				}
			}
			else // maintain RH
				Global::obs_ea[tt][ii] = (double)(Common::estar(Global::obs_t[tt][ii]) * layvalues[tt][ii] / 100.0); // adjust ea
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_ea_day(ClassModule* thisModule) { // FUNCTION - ea available

	double New_es;
	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			Global::obs_rh[tt][ii] = (double)(layvalues[tt][ii] / Common::estar(Global::obs_t_obs[tt][ii]) * 100.0); // use original t to calculate RH
			New_es = (double)Common::estar(Global::obs_t[tt][ii]); // maximum ea from new t

			if (Global::RH_VP_flag[ii]) { // maintain ea if possible
				if (Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii]) { // new t lower, could be supersaturated
					if (layvalues[tt][ii] > New_es) {
						layvalues[tt][ii] = New_es;  // in saturation
						Global::obs_rh[tt][ii] = 100.0; // adjust RH
					}
					else
						Global::obs_rh[tt][ii] = (double)(layvalues[tt][ii] / New_es * 100.0); // adjust RH
				}
			}
			else { // maintain RH
				layvalues[tt][ii] = New_es * Global::obs_rh[tt][ii] / (double)100.0; // adjust ea
				double X = layvalues[tt][ii];
			}
		}
	}
};

long GetSharedUnitVar(string units) {
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

long ClassVar::GetUnit(void) {
	return GetSharedUnitVar(units);
}
