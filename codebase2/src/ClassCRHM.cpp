
// 11/28/17
//---------------------------------------------------------------------------

#if defined(_WIN32)
#include "stdafx.h"
#endif

#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <cmath>
#include <cmath>


#include "ClassCRHM.h"
#include "NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"
#include "Common.h"
#include "StandardConverterUtility.h"

//---------------------------------------------------------------------------
//#pragma package(smart_init)

//---------------------------------------------------------------------------

//#define M_PI           3.14159265358979323846  /* pi */

using namespace std;

//---------------------------------------------------------------------------
/*
extern double xLimit;
extern long lLimit;
*/
//double xLimit;
//long lLimit;

long Index_; // used by functions
			 //---------------------------------------------------------------------------
void ClassVar::BackUp() {

	long Fix = lay;
	if (lay == 0) Fix = 1;

	if (varType == CRHM::Float) {
		layvaluesBkup = new float *[Fix];
		for (int ii = 0; ii < Fix; ii++)
			layvaluesBkup[ii] = new float[dim];

		for (int jj = 0; jj < Fix; jj++)
			for (int ii = 0; ii < dim; ii++)
				if (lay == 0 && jj == 0)
					layvaluesBkup[jj][ii] = values[ii];
				else
					layvaluesBkup[jj][ii] = layvalues[jj][ii];
	}
	else if (varType == CRHM::Int) {
		ilayvaluesBkup = new long *[Fix];
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

//---------------------------------------------------------------------------
void ClassVar::Restore() {

	long Fix = lay;
	if (lay == 0) Fix = 1;

	if (varType == CRHM::Float) {

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
	else if (varType == CRHM::Int) {

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

//---------------------------------------------------------------------------
void ClassVar::ReadVar(void) {

	if (FileData->Times == NULL) {
		if (varType == CRHM::ReadF || varType == CRHM::Read) {
			if (dimen == CRHM::NHRU)
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
						values[ii] = (float)xLimit;
					}
			}
		}
		else if (varType == CRHM::ReadI)
		{
			if (dimen == CRHM::NHRU)
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
		if (varType == CRHM::ReadF || varType == CRHM::Read)
		{
			if (dimen == CRHM::NHRU)
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
		else if (varType == CRHM::ReadI)
		{
			if (dimen == CRHM::NHRU)
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
		float doN = (float)dim;
		if (dimen == CRHM::NOBS)
			doN = (float)cnt;
		if (varType == CRHM::ReadF || varType == CRHM::Read)
			for (long ii = 0; ii < doN; ++ii)
				values[ii] = (float)xLimit;

		else if (varType == CRHM::ReadI)
			for (long ii = 0; ii < doN; ++ii)
				ivalues[ii] = lLimit;
	}
}

//---------------------------------------------------------------------------
void ClassVar::WriteVar(void) {

	if (FileData->Times == NULL) {
		if (varType == CRHM::ReadF || varType == CRHM::Read)
		{
			if (dimen == CRHM::NHRU)
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

		else if (varType == CRHM::ReadI)
		{
			for (long ii = 0; ii < dim; ++ii)
				FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] = (float)ivalues[ii];
		}
		else
		{
			for (long ii = 0; ii < cnt; ++ii)
				FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][Global::DTindx / FileData->ModN - FileData->IndxMin] = (float)ivalues[ii];
		}
	}
	else if (FileData->GoodInterval) { // sparse data
		if (varType == CRHM::ReadF || varType == CRHM::Read)
		{
			if (dimen == CRHM::NHRU)
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
		else if (varType == CRHM::ReadI)
		{
			if (dimen == CRHM::NHRU)
			{
				for (long ii = 0; ii < dim; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] = (float)ivalues[ii];
			}
			else
			{
				for (long ii = 0; ii < cnt; ++ii)
					FileData->Data[offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], cnt) - 1][FileData->TimeIndx] = (float)ivalues[ii];
			}
		}
	}
}

//---------------------------------------------------------------------------
void ClassVar::Intvl(void) {  // used for NFREQ observation reads - Tday, RHday and EAday
	float X;

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
	} while (++Index_%FunctVar->FileData->Freq != 0);
}

//---------------------------------------------------------------------------
void ClassVar::Tot_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] += X;

};

//---------------------------------------------------------------------------
void ClassVar::Pos_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt - 1)][Index_ - FunctVar->FileData->IndxMin];
	if (X > 0.0)
		values[dim_n] += X;

};

//---------------------------------------------------------------------------
void ClassVar::Max_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X > values[dim_n])
		values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::Min_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X < values[dim_n])
		values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::Last_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::First_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] = X;

};

//---------------------------------------------------------------------------
void ClassVar::Avg_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	values[dim_n] += X / this->FileData->Freq;

};

//---------------------------------------------------------------------------
void ClassVar::Count_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X > 0.0)
		values[dim_n] += (float)1.0 / this->FileData->Freq;

};

//---------------------------------------------------------------------------
void ClassVar::Count0_(long dim_n) {

	float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][dim_n], FunctVar->cnt) - 1][Index_ - FunctVar->FileData->IndxMin];
	if (X == 0.0)
		values[dim_n] += (float)1.0 / this->FileData->Freq;

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
			float X = FunctVar->FileData->Data[firstindex][secondindex];
			values[ii] += X;
		}
		Count++;
	} while (++Index%FunctVar->FileData->Freq != 0);

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
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X > values[ii]) values[ii] = X;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Min(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 100000.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X < values[ii]) values[ii] = X;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Dtot(void) { // day total

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 0.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			values[ii] += X;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Tot(void) { // running total from the beginning

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			values[ii] += X;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Last(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN + FunctVar->FileData->Freq - 1;

	for (long ii = 0; ii < this->dim; ++ii) {
		float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
		values[ii] = X;
	}
};

//---------------------------------------------------------------------------
void ClassVar::First(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) {
		float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
		values[ii] = X;
	}
};

//---------------------------------------------------------------------------
void ClassVar::Peak(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X > values[ii]) values[ii] = X;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Count(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;
	float Divisor = (float)FunctVar->FileData->ModN;

	if (this->root != "") // VarObsFunct - normalise to daily value
		Divisor = (float)this->FileData->Freq;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X > 0.0)
				values[ii] += (float)1.0 / Divisor;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Count0(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;
	float Divisor = (float)FunctVar->FileData->ModN;

	if (this->root != "") // VarObsFunct - normalise to daily value
		Divisor = (float)this->FileData->Freq;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt) - 1][Index - FunctVar->FileData->IndxMin];
			if (X == 0.0)
				values[ii] += (float)1.0 / Divisor;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::Pos(void) {

	long Index = Global::DTindx / FunctVar->FileData->ModN;

	for (long ii = 0; ii < this->dim; ++ii) values[ii] = 0.0;

	do {
		for (long ii = 0; ii < this->dim; ++ii) {
			float X = FunctVar->FileData->Data[FunctVar->offset + min<long>(Global::HRU_OBS[HRU_OBS_indexed][ii], FunctVar->cnt - 1)][Index - FunctVar->FileData->IndxMin];
			if (X > 0.0) values[ii] += X;
		}
	} while (++Index%FunctVar->FileData->Freq != 0);
};

//---------------------------------------------------------------------------
void ClassVar::do_t(ClassModule *thisModule) { // adjusts t_max and t_min observations for lapse rate and climate warming

	for (int ii = 0; ii < this->dim; ++ii) // does this step
		values[ii] -= Global::lapse_rate[ii] * (float)(Global::hru_elev[ii] - Global::OBS_ELEV[0][ii]) / (float)100.0;
	// should original t be saved for ea
};

//---------------------------------------------------------------------------
void ClassVar::do_t_Clim(ClassModule *thisModule) { // adjusts t_max and t_min observations for lapse rate and climate warming

	do_t(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) // does this step
		values[ii] += Global::Warming_t[ii];
	// should original t be saved for ea
};

//---------------------------------------------------------------------------
void ClassVar::do_ppt(ClassModule *thisModule) { // adjusts observation for lapse rate

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] * ((float)1.0 + (Global::hru_elev[ii] - Global::OBS_ELEV[1][ii]) / (float)100.0 *Global::ppt_adj[ii]);
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_p(ClassModule *thisModule) { // adjusts observation for lapse rate

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = FunctVar->values[ii] * ((float)1.0 + (Global::hru_elev[ii] - Global::OBS_ELEV[1][ii]) / (float)100.0 *Global::ppt_adj[ii]);
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_p_Clim(ClassModule *thisModule) { // adjusts observation for lapse rate

	do_p(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] * Global::Warming_p[ii];
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_ppt_Clim(ClassModule *thisModule) { // adjusts observation for lapse rate

	do_ppt(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		values[ii] = values[ii] * Global::Warming_p[ii];
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_t_day(ClassModule *thisModule) { // FUNCTION - adjusts observation for lapse rate and handles climate warming
	for (int ii = 0; ii < this->dim; ++ii) {
		float Fix = (float)(Global::lapse_rate[ii] * (Global::hru_elev[ii] - Global::OBS_ELEV[0][ii]) / 100.0);
		for (int tt = 0; tt < Global::Freq; ++tt) {
			Global::obs_t_obs[tt][ii] = layvalues[tt][ii]; // save original values
			layvalues[tt][ii] -= Fix; // make lapse rate correction
			Global::obs_t[tt][ii] = layvalues[tt][ii];
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_t_day_Clim(ClassModule *thisModule) { // FUNCTION - adjusts observation for lapse rate and handles climate warming
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
void ClassVar::do_rh_day(ClassModule *thisModule) { // FUNCTION - RH available

	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			if (Global::RH_VP_flag[ii]) { // maintain ea if possible
				Global::obs_ea[tt][ii] = (float)(Common::estar(Global::obs_t[tt][ii])*layvalues[tt][ii] / 100.0); // use new t
				if (Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii]) { // new t lower, could be supersaturated
					float New_es = (float)Common::estar(Global::obs_t[tt][ii]); // maximum ea from new t
					if (Global::obs_ea[tt][ii] > New_es) {
						Global::obs_ea[tt][ii] = New_es;  // in saturation
						layvalues[tt][ii] = 100.0; // adjust RH
					}
					else
						layvalues[tt][ii] = (float)(Global::obs_ea[tt][ii] / New_es * 100.0); // adjust RH
				}
			}
			else // maintain RH
				Global::obs_ea[tt][ii] = (float)(Common::estar(Global::obs_t[tt][ii])*layvalues[tt][ii] / 100.0); // adjust ea
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_rh_day_Clim(ClassModule *thisModule) { // FUNCTION - RH available

	do_rh_day(thisModule);

	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			if (Global::RH_VP_flag2[ii]) { // maintain ea if possible
				Global::obs_ea[tt][ii] = (float)(Common::estar(Global::obs_t[tt][ii])*layvalues[tt][ii] / 100.0); // use new t
				if (Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii]) { // new t lower, could be supersaturated
					float New_es = (float)Common::estar(Global::obs_t[tt][ii]); // maximum ea from new t
					if (Global::obs_ea[tt][ii] > New_es) {
						Global::obs_ea[tt][ii] = New_es;  // in saturation
						layvalues[tt][ii] = 100.0; // adjust RH
					}
					else
						layvalues[tt][ii] = (float)(Global::obs_ea[tt][ii] / New_es * 100.0); // adjust RH
				}
			}
			else // maintain RH
				Global::obs_ea[tt][ii] = (float)(Common::estar(Global::obs_t[tt][ii])*layvalues[tt][ii] / 100.0); // adjust ea
		}
	}
};

//---------------------------------------------------------------------------
void ClassVar::do_ea_day(ClassModule *thisModule) { // FUNCTION - ea available

	float New_es;
	for (int ii = 0; ii < this->dim; ++ii) {
		for (int tt = 0; tt < Global::Freq; ++tt) {
			Global::obs_rh[tt][ii] = (float)(layvalues[tt][ii] / Common::estar(Global::obs_t_obs[tt][ii])*100.0); // use original t to calculate RH
			New_es = (float)Common::estar(Global::obs_t[tt][ii]); // maximum ea from new t

			if (Global::RH_VP_flag[ii]) { // maintain ea if possible
				if (Global::obs_t_obs[tt][ii] > Global::obs_t[tt][ii]) { // new t lower, could be supersaturated
					if (layvalues[tt][ii] > New_es) {
						layvalues[tt][ii] = New_es;  // in saturation
						Global::obs_rh[tt][ii] = 100.0; // adjust RH
					}
					else
						Global::obs_rh[tt][ii] = (float)(layvalues[tt][ii] / New_es * 100.0); // adjust RH
				}
			}
			else { // maintain RH
				layvalues[tt][ii] = New_es * Global::obs_rh[tt][ii] / (float)100.0; // adjust ea
				float X = layvalues[tt][ii];
			}
		}
	}
};

//---------------------------------------------------------------------------
void setdim(string name, long dim) {
	string s = name;

	if (name == "nhru") {
		Update_Main_DIM(CRHM::NHRU, dim);
	}
	else if (name == "nobs") {
		Update_Main_DIM(CRHM::NOBS, dim);
	}
	else if (name == "nlay") {
		Update_Main_DIM(CRHM::NLAY, dim);
	}
}

//---------------------------------------------------------------------------
//float sqr(float X) { return X * X; }


ClassPar::ClassPar(string module, string param, CRHM::TDim dimen,
	string CommaText, string help, CRHM::TVar varType, int Grpdim)
	: module(module), basemodule(""), param(param), varType(varType), dimen(dimen), help(help),
	units(""), valstr(""), minVal(0), maxVal(0), Inhibit_share(0),
	values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Identical(NULL),
	layvaluesBkup(NULL), ilayvaluesBkup(NULL), lay(1) {

	if (Grpdim == 0 && dimen >= CRHM::NHRU)
		Grpdim = Global::nhru;

	if (dimen < CRHM::NHRU)
		dim = getdim(dimen); // handle cases of 'ONE, TWO, ...
	else
		dim = Grpdim;

	Strings = new TStringList();
	//Strings->QuoteChar = '\'';
	Strings->DelimitedText(CommaText);
	if (Strings->Count == 0) // handle case of newly added string parameter. Only handles 'BASIN'
		Strings->Add("");

	if (dimen == CRHM::NHRU)
		for (int ii = Strings->Count; ii < dim; ++ii) {
			Strings->Add(Strings->Strings[0] + std::to_string(ii + 1));
		}
}

//---------------------------------------------------------------------------
void ClassPar::ExpandShrink(long new_dim) {

	// backup current string

	if (varType == CRHM::Txt) {
		StringsBkup = new TStringList;
		StringsBkup->Assign(Strings);
	}
	else if (varType == CRHM::Float) {
		layvaluesBkup = new float *[lay];
		for (int ii = 0; ii < lay; ii++)
			layvaluesBkup[ii] = new float[dim];

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				layvaluesBkup[jj][ii] = layvalues[jj][ii];
	}
	else if (varType == CRHM::Int) {
		ilayvaluesBkup = new long *[lay];
		for (int ii = 0; ii < lay; ii++)
			ilayvaluesBkup[ii] = new long[dim];

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
	}

	// delete current arrays

	if (varType == CRHM::Float) {
		for (int ii = 0; ii < lay; ++ii) delete[] layvalues[ii];

		delete[] layvalues;  //Array [nhru] [lay]
		values = NULL;
	}
	else if (varType == CRHM::Int) {
		for (int ii = 0; ii < lay; ++ii) delete[] ilayvalues[ii];

		delete[] ilayvalues; //Array [nhru] [lay]
		ivalues = NULL;
	}
	else if (varType == CRHM::Txt) {
		Strings->Clear();
	}

	// allocate new memory

	long lay0 = lay;
	long dim0 = dim;

	dim = new_dim;

	if (dimen == CRHM::NDEFN) // NDEFN stays the same
		lay = new_dim;

	if (varType == CRHM::Float) {
		if (lay > 0) {
			layvalues = new float *[lay];
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new float[dim];

			for (int jj = 0; jj < lay; ++jj)
				for (int kk = 0; kk < dim; ++kk)
					layvalues[jj][kk] = 0.0;
		}

		values = new float[dim];
		for (int kk = 0; kk < dim; ++kk)
			values[kk] = 0.0;
	}
	else if (varType == CRHM::Int) {
		if (lay > 0) {
			ilayvalues = new long *[lay];
			for (int ii = 0; ii < lay; ii++)
				ilayvalues[ii] = new long[dim];

			for (int jj = 0; jj < lay; ++jj)
				for (int kk = 0; kk < dim; ++kk)
					ilayvalues[jj][kk] = (int)0.0;
		}

		ivalues = new long[dim];
		for (int kk = 0; kk < dim; ++kk)
			ivalues[kk] = 0;
	}
	else if (varType == CRHM::Txt) {
		Strings->Clear();
	}

	// copy data into expanded/shrunk array

	if (varType == CRHM::Txt) {
		if (StringsBkup->Count > 0)
		{
			for (int kk = 0; kk < dim; ++kk)
				Strings->Add(StringsBkup->Strings[min<int>(kk, dim0 - 1)] + "");
			delete StringsBkup;
		}
		StringsBkup = NULL;
	}
	else if (varType == CRHM::Float) {

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				layvalues[jj][ii] = layvaluesBkup[min<int>(jj, lay0 - 1)][min<int>(ii, dim0 - 1)];

		for (int ii = 0; ii < lay0; ++ii)
			delete[] layvaluesBkup[ii];
		delete[] layvaluesBkup;  //Array [nhru] [lay]
		layvaluesBkup = NULL;
	}
	else if (varType == CRHM::Int) {

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				ilayvalues[jj][ii] = ilayvaluesBkup[min<int>(jj, lay0 - 1)][min<int>(ii, dim0 - 1)];

		for (int ii = 0; ii < lay0; ++ii)
			delete[] ilayvaluesBkup[ii];
		delete[] ilayvaluesBkup; //Array [nhru] [lay]
		ilayvaluesBkup = NULL;
	}
}

//---------------------------------------------------------------------------
void ClassPar::BackUp() {

	if (varType == CRHM::Txt) {
		StringsBkup = new TStringList;
		StringsBkup->Assign(Strings);
	}
	else if (varType == CRHM::Float) {
		layvaluesBkup = new float *[lay];
		for (int ii = 0; ii < lay; ii++)
			layvaluesBkup[ii] = new float[dim];

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				layvaluesBkup[jj][ii] = layvalues[jj][ii];
	}
	else if (varType == CRHM::Int) {
		ilayvaluesBkup = new long *[lay];
		for (int ii = 0; ii < lay; ii++)
			ilayvaluesBkup[ii] = new long[dim];

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
	}
}

//---------------------------------------------------------------------------
void ClassPar::Restore() {

	if (varType == CRHM::Txt) {
		Strings->Assign(StringsBkup);
		delete StringsBkup;
		StringsBkup = NULL;
	}
	else if (varType == CRHM::Float) {

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				layvalues[jj][ii] = layvaluesBkup[jj][ii];

		for (int ii = 0; ii < lay; ++ii)
			delete[] layvaluesBkup[ii];
		delete[] layvaluesBkup;  //Array [nhru] [lay]
		layvaluesBkup = NULL;
	}
	else if (varType == CRHM::Int) {

		for (int jj = 0; jj<lay; jj++)
			for (int ii = 0; ii<dim; ii++)
				ilayvalues[jj][ii] = ilayvaluesBkup[jj][ii];

		for (int ii = 0; ii < lay; ++ii)
			delete[] ilayvaluesBkup[ii];
		delete[] ilayvaluesBkup; //Array [nhru] [lay]
		ilayvaluesBkup = NULL;
	}
}

//---------------------------------------------------------------------------
ClassPar::ClassPar(string module, string param, CRHM::TDim dimen,
	string valstr, float minVal, float maxVal,
	string help, string units, CRHM::TVar varType, int defdim, int Grpdim)
	: module(module), basemodule(""), param(param), varType(varType), dimen(dimen),
	valstr(valstr), minVal(minVal), maxVal(maxVal), Inhibit_share(0),
	help(help), units(units),
	values(NULL), ivalues(NULL),
	layvalues(NULL), ilayvalues(NULL), Strings(NULL),
	layvaluesBkup(NULL), ilayvaluesBkup(NULL), Identical(NULL), StringsBkup(NULL), lay(1) {

	if (Grpdim == 0 && dimen >= CRHM::NHRU)
		Grpdim = Global::nhru;

	if (dimen == CRHM::NLAY) {
		lay = Global::nlay;
		dim = Grpdim;
	}
	else if (dimen == CRHM::NDEF) {
		lay = defdim;
		dim = 1; //
	}
	else if (dimen == CRHM::NDEFNZ) {
		lay = defdim;
		dim = 1; // array 1 * n;
	}
	else if (dimen == CRHM::NDEFN) {
		lay = defdim;
		dim = Grpdim; // Global::nhru;
	}
	else if (dimen < CRHM::NHRU) {
		dim = getdim(dimen); // handle cases of 'ONE, TWO, ...
		lay = 1;
	}
	else {
		dim = Grpdim;
		lay = 1;
	}

	try {
		if (varType == CRHM::Float) {
			layvalues = new float *[lay];
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new float[dim];
			values = layvalues[0];
		}
		else if (varType == CRHM::Int) {
			ilayvalues = new long *[lay];
			for (int ii = 0; ii < lay; ii++)
				ilayvalues[ii] = new long[dim];
			ivalues = ilayvalues[0];
		}
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassPar.", TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
}

//---------------------------------------------------------------------------
ClassPar::ClassPar(ClassPar &p) {  // copy constructor

	module = string(p.module);
	basemodule = string(p.basemodule);
	param = string(p.param);
	units = string(p.units);
	help = string(p.help);

	varType = p.varType;
	dimen = p.dimen;

	dim = p.dim;
	lay = p.lay;
	variation_set = p.variation_set;
	visibility = p.visibility;
	Inhibit_share = p.Inhibit_share;

	valstr = string(p.valstr);
	minVal = p.minVal;
	maxVal = p.maxVal;

	layvaluesBkup = NULL;
	ilayvaluesBkup = NULL;

	Strings = NULL;
	ivalues = NULL;
	values = NULL;
	ilayvalues = NULL;
	layvalues = NULL;
	Identical = NULL;

	try {
		if (varType == CRHM::Float) {
			layvalues = new float *[lay];
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new float[dim];
			values = layvalues[0];
		}
		else if (varType == CRHM::Int) {
			ilayvalues = new long *[lay];
			for (int ii = 0; ii < lay; ii++)
				ilayvalues[ii] = new long[dim];
			ivalues = ilayvalues[0];
		}
		else if (varType == CRHM::Txt) {
			Strings = new TStringList;
		}
	}

	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassPar.", TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}

	if (varType == CRHM::Float)
	{
		for (int jj = 0; jj < lay; jj++)
		{
			for (int ii = 0; ii < dim; ii++)
				layvalues[jj][ii] = p.layvalues[jj][ii];
		}
	}
	else if (varType == CRHM::Int)
	{
		for (int jj = 0; jj < lay; jj++)
		{
			for (int ii = 0; ii < dim; ii++)
				ilayvalues[jj][ii] = p.ilayvalues[jj][ii];
		}
	}
	else if (varType == CRHM::Txt)
	{
		Strings->Assign(p.Strings);
	}

}

//---------------------------------------------------------------------------
bool ClassPar::Same(ClassPar &p) {  // compares parameter data

	if (varType == p.varType && dim == p.dim && param == p.param) {
		if (Inhibit_share != 0 || p.Inhibit_share != 0) // declputparam
		{
			if (Global::GroupCntTrk)
			{
				return(false);  // never share group declputparam
			}
			else
			{
				return(true); // always share simple project declputparam parameters
			}
		}
		if (dim == p.dim) {
			if (varType == CRHM::Txt) {
				if (!Strings && !p.Strings) return true;
				if (Strings->Count != p.Strings->Count) return(false);
				for (int ii = 0; ii < Strings->Count; ++ii)
					if (Strings->Strings[ii] != p.Strings->Strings[ii]) return(false);
			}
			else
			{
				for (int jj = 0; jj<lay; ++jj)
					for (int ii = 0; ii<dim; ++ii)
						if (varType == CRHM::Float) {
							if (layvalues[jj][ii] != p.layvalues[jj][ii]) return(false);
						}
						else if (varType == CRHM::Int) {
							if (ilayvalues[jj][ii] != p.ilayvalues[jj][ii]) return(false);
						}
			}
			return(true);
		}
	}
	return(false);
}

//---------------------------------------------------------------------------
void ClassPar::Change(ClassPar &p) {  // changes parameter data to 'p'

	if (this == &p) return;

	if (varType == CRHM::Txt) {
		Strings->Assign(p.Strings);
		while (Strings->Count < dim && Strings->Count>0)  // duplicate last field when # of HRUs increased
														  //Strings->Append(Strings->Strings[Strings->Count - 1]);
			Strings->Add(Strings->Strings[Strings->Count - 1] + "");
	}
	else {
		bool Bang = valstr.find("!") != string::npos;
		for (int jj = 0; jj < lay; ++jj) {
			long jj0 = min<long>(jj, p.lay - 1);
			for (int ii = 0; ii < dim; ++ii) {
				long ii0 = min<long>(ii, p.dim - 1);
				if (Bang && ii0 < ii) {
					if (varType == CRHM::Float)
					{
						layvalues[jj][ii] = layvalues[jj][ii - 1] + 1;
					}
					else if (varType == CRHM::Int)
					{
						ilayvalues[jj][ii] = ilayvalues[jj][ii - 1] + 1;
					}
				}
				else {
					if (varType == CRHM::Float)
					{
						layvalues[jj][ii] = p.layvalues[jj0][ii0];
					}
					else if (varType == CRHM::Int)
					{
						ilayvalues[jj][ii] = p.ilayvalues[jj0][ii0];
					}
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
ClassPar *ClassParFindShared(string name) { // where name is concatenation of MODULE and NAME
	MapPar::iterator itPar;

	if ((itPar = Global::SharedMapPars.find(name)) == Global::SharedMapPars.end()) {
		CRHMException Except("Could not find Parameter: " + name, WARNING);
		LogError(Except);
		return NULL;
	}
	return ((*itPar).second);
}

//---------------------------------------------------------------------------
ClassPar *ClassParFind(string name) { // where name is concatenation of MODULE and NAME
	MapPar::iterator itPar;

	if ((itPar = Global::MapPars.find(name)) == Global::MapPars.end()) {
		CRHMException Except("Could not find Parameter: " + name, WARNING);
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
			if (itPar0 != Global::MapPars.end()) // already there?
				continue;
			if (Global::OurModulesList->IndexOf(smodule.c_str()) == -1) // in project?
				continue; // NO!
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
			jj = Global::OldModuleName->IndexOf(module.c_str()); // Check if renamed module. Find old name
		}
		if (jj > -1) {
			string s = Global::NewModuleName->Strings[jj] + ""; // two step to remove \0
			if ((itPar = Global::MapPars.find(s + ' ' + param)) != Global::MapPars.end()) {
				return ((*itPar).second);
			}
		}
		LogError(CRHMException("Parameter defined in module: " + param + ", " + module + " not found", WARNING));
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
		LogError(CRHMException("Parameter defined in module: " + param + ", " + module + " not found", TERMINATE));
		return NULL;
	}
}

//---------------------------------------------------------------------------
ClassPar::~ClassPar() {

	if (varType == CRHM::Float) {
		for (int ii = 0; ii < lay; ++ii) delete[] layvalues[ii];

		delete[] layvalues;  //Array [nhru] [lay]
		values = NULL;
	}
	else if (varType == CRHM::Int) {
		for (int ii = 0; ii < lay; ++ii) delete[] ilayvalues[ii];

		delete[] ilayvalues; //Array [nhru] [lay]
		ivalues = NULL;
	}
	else if (varType == CRHM::Txt) {
		delete Strings;
	}
	varType = CRHM::none;
}

//---------------------------------------------------------------------------
ClassVar *ClassVarFind(string name) {
	MapVar::iterator itVar;

	if ((itVar = Global::MapVars.find(name)) == Global::MapVars.end())
		if ((itVar = Global::MapVars.find('#' + name)) == Global::MapVars.end()) { // could be local
			CRHMException Except("Could not find Variable: " + name, WARNING);
			LogError(Except);
			return NULL;
		}
	return ((*itVar).second);
}

//---------------------------------------------------------------------------
ClassVar::ClassVar(string module, string name, CRHM::TDim dimen,
	string help, string units, CRHM::TVar varType, bool PointPlot, int Grpdim, int defdim)
	: module(module), name(name), DLLName(""), root(""), varType(varType), lay(0), nfreq(false),
	optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS),
	help(help), units(units), layvalues(NULL), ilayvalues(NULL), dim(0), dimMax(0),
	values(NULL), ivalues(NULL), offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0),
	UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(PointPlot), TchrtOpt(0),
	dimen(dimen) {

	if (Grpdim == 0)
		Grpdim = Global::nhru;

	if (dimen == CRHM::NLAY)
		lay = Global::nlay;
	else if (dimen == CRHM::NFREQ) {
		lay = Global::Freq;
		nfreq = true;
	}
	else if (dimen == CRHM::NDEF) {
		lay = defdim;
		dim = 1;
	}
	else if (dimen == CRHM::NDEFN) {
		lay = defdim;
		dim = Grpdim;
	}
	else if (dimen == CRHM::NREB)
		lay = Grpdim; // memory allocated by variables found
	else
		lay = 0;

	if (dimen == CRHM::NOBS)
		dim = Global::nobs;
	else
		dim = Grpdim;

	try {
		if (varType == CRHM::Float) {
			if (lay > 0) {
				layvalues = new float *[lay];
				if (!values)
					values = new float[dim];
				if (dimen != CRHM::NREB) { // NREB does not own lay memory only HRU memory
					for (int ii = 0; ii < lay; ii++)
						layvalues[ii] = new float[dim];
					values = layvalues[0]; // sets to first layer

					for (int jj = 0; jj < lay; ++jj)
						for (int kk = 0; kk < dim; ++kk)
							layvalues[jj][kk] = 0.0;
				}
			}

			if (lay == 0 || dimen == CRHM::NREB) {
				values = new float[dim];
				for (int kk = 0; kk < dim; ++kk)
					values[kk] = 0.0;
			}
		}
		else if (varType == CRHM::Int) {
			if (lay > 0) {
				ilayvalues = new long *[lay];
				if (dimen != CRHM::NREB) { // NREB does not own lay memory only HRU memory
					for (int ii = 0; ii < lay; ii++)
						ilayvalues[ii] = new long[dim];
					ivalues = ilayvalues[0];

					for (int jj = 0; jj < lay; ++jj)
						for (int kk = 0; kk < dim; ++kk)
							ilayvalues[jj][kk] = (int)0.0;
				}
			}

			if (lay == 0 || dimen == CRHM::NREB) {
				ivalues = new long[dim];
				for (int kk = 0; kk < dim; ++kk)
					ivalues[kk] = 0;
			}
		}
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassVar.", TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
}

//---------------------------------------------------------------------------
ClassVar::ClassVar(string module, string name, long dim,
	string help, string units, CRHM::TVar varType, bool PointPlot)
	: module(module), name(name), DLLName(""), root(""), varType(varType), dim(dim), dimMax(0), lay(0), nfreq(false),
	optional(false), StatVar(false), InGroup(0), visibility(CRHM::USUAL), FunKind(CRHM::FOBS),
	help(help), units(units), layvalues(NULL), ilayvalues(NULL),
	values(NULL), ivalues(NULL), offset(0), cnt(0), FileData(NULL), HRU_OBS_indexed(0),
	UserFunct(NULL), FunctVar(NULL), CustomFunct(NULL), No_ReadVar(0), PointPlot(PointPlot), TchrtOpt(0),
	dimen(CRHM::NHRU) {


	try {
		if (varType == CRHM::Float)
			values = new float[dim];
		else if (varType == CRHM::Int)
			ivalues = new long[dim];
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassVar.", TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
}

//---------------------------------------------------------------------------
void ClassVar::ReleaseM(bool Keep) {
	if (!values && !ivalues) return;

	if (varType == CRHM::Float || varType == CRHM::ReadF) {

		if (lay > 0) {
			if (dimen != CRHM::NREB)
				values = NULL;

			if (dimen != CRHM::NREB) // NREB does not own lay memory only HRU memory
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
	else if (varType == CRHM::Int || varType == CRHM::ReadI) {

		if (lay > 0) {
			if (dimen != CRHM::NREB)
				ivalues = NULL;

			if (dimen != CRHM::NREB) // NREB does not own lay memory only HRU memory
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

// not complete

//---------------------------------------------------------------------------
ClassVar::ClassVar(const ClassVar & Cl) { // used for observation totals +

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
		layvalues = new float *[lay];
		if (dimen != CRHM::NREB) { // NREB does not own lay memory only HRU memory
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new float[dim];
			values = layvalues[0];

			for (int jj = 0; jj < lay; ++jj)
				for (int kk = 0; kk < dim; ++kk)
					layvalues[jj][kk] = 0.0;
		}
	}

	if (lay == 0 || dimen == CRHM::NREB) {
		varType = CRHM::Float; // display always float. handles integer variables from VarObsFunct_Update
		values = new float[dim];
		ivalues = NULL;
		for (int kk = 0; kk < dim; ++kk)
			values[kk] = 0.0;
	}
}

// not complete

//---------------------------------------------------------------------------
ClassVar & ClassVar::operator=(const ClassVar & Cl) { // not used ever

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

//---------------------------------------------------------------------------
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


double ClassData::Encode24(int D[]) {

	try {
		if (D[3] == 24) // handle 24:00
			return  StandardConverterUtility::EncodeDateTime(D[0], D[1], D[2], 0, D[4]) + 1;
		else
			return  StandardConverterUtility::EncodeDateTime(D[0], D[1], D[2], D[3], D[4]);
	}
	catch (...)
	{
		//    string S;
		//    S.sprintf("Invalid Date: \"%5u %3u %3u %3u %3u\" at line: %u", D[0], D[1], D[2], D[3], D[4], Position+1);

		//    Message(S.c_str(), string("Observation File: " + DataFileName).c_str(), mbOK);
		//    throw;
		return 0.0;
	}
}


//---------------------------------------------------------------------------
long ClassData::Veto_Freq(long Freq) {
	const long OK_Values[14] = { 1, 2, 3, 4, 6, 8, 12, 24, 48, 72, 96, 144, 192, 288 };
	if (Freq <= 1)
		return 1;
	if (Freq >= OK_Values[13])
		return OK_Values[13];
	for (int ii = 1; ii < 14; ++ii) {
		if (Freq <= OK_Values[ii]) {
			if ((Freq - OK_Values[ii - 1]) < (OK_Values[ii] - Freq))
				return OK_Values[ii - 1];
			else
				return OK_Values[ii];
		}
	}
	return(-1);
}




//---------------------------------------------------------------------------
bool ClassData::DataReadFile(void) {

	ifstream DataFile;
	ifstream::pos_type Here, Here2;
	string Header, Var, Comment;
	istringstream instr;
	bool DecimalTime;
	FirstFile = !Global::DTstart;

	int D[5];
	long jj, MaxLines;
	bool SparseFlag = false;
	bool LineError = false;
	bool OneLine = false;

	ModN = 1;

	bitset <128> MyBitSet;

	DataFile.open(DataFileName, ios_base::in);
	if (!DataFile) {
		/*
		CRHMException Except("Missing observation " + DataFileName, ERR);
		Message(Except.Message.c_str(),
		"Project observation file", mbOK);
		LogError(Except);*/
		DataFile.close();
		return false;
	}

	getline(DataFile, Description);
	HdrLen = 1;
	myMacro = new Classmacro(this);
	while (!DataFile.eof()) {
		char c = DataFile.peek();

		if (DataFile.fail()) {
			/*       CRHMException Except("Errors in observation file header" + DataFileName, ERR);
			Message(Except.Message.c_str(),
			"Project observation file", mbOK);
			LogError(Except);*/
			DataFile.close();
			return false;
		}

		++HdrLen;

		if (c == '#') {
			getline(DataFile, Comment);
			break;
		}

		if (c == '/')
			getline(DataFile, Comment); // lose
		else if (c == '$') {
			getline(DataFile, Comment);
			myMacro->addfilter(Comment);
		}
		else { // observation
			if (FilterCnt != 0) {
				/*          CRHMException Except("Filters must follow observations in file header " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"Project observation file", mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}
			DataFile >> Var; // observation name
			DataFile >> jj; // number of columns

			getline(DataFile, Comment);
			bool negative = false; // defines integral/instantaneous data
			if (jj < 0) {
				jj = labs(jj);
				negative = true;
			}

			ClassVar *ThisVar = declread("obs", Var, jj, DataCnt, this, Comment);

			if (!ThisVar) { // NULL if already defined
				string S = string("Observation '") + Var + "' defined in earlier observation file";
				/*          CRHMException Except("Observation variable already defined " + DataFileName, ERR);
				Message(S.c_str(), Except.Message.c_str(), mbOK);*/
				DataFile.close();
				return false;
			}

			ThisVar->review_HRU_OBS();

			for (int ii = 0; ii < jj; ++ii)
				if (negative)
					MyBitSet.set(DataCnt + jj - 1);

			DataCnt = DataCnt + jj;
		}
	} // while

	if (!Simulation) {

		do {
			Here = DataFile.tellg();
			DataFile >> Dt1;
			if (Dt1 > 3000.0)
				DecimalTime = true;
			else {
				DecimalTime = false;
				D[0] = (int)Dt1;
				//DataFile.seekg(Here - 1);  // go back to beginning of data
				for (int ii = 1; ii < 5; ii++)
					DataFile >> D[ii];
				Position = HdrLen;
				Dt1 = Encode24(D);
			}

			Dt1 += TimeShiftFilter;

			if (DataFile.eof()) {
				/*          CRHMException Except("Error in observation file header " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"File observations end early!", mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}

			if (Global::DTstart != 0.0 && Dt1 >= Global::DTend) {
				/*         CRHMException Except("Error in observation file " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"File observations begin after period!", mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}

			getline(DataFile, Var);  // eat up remainder of line

			instr.clear(); // check for sufficient data
			instr.str(Var);
			float V;
			long Cols = 0;
			for (;;) {
				instr >> V;
				if (instr.fail()) break;
				++Cols;
			}

			if (Cols < DataCnt) {
				/*          CRHMException Except("Observation file header Error " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				string("Header of file defines more observations than data columns (" + string(Cols) + ")").c_str(), mbOK);
				LogError(Except);*/
				DataFile.close();
				return false;
			}
			else if (Cols > DataCnt) {
				/*          CRHMException Except("Observation file header Warning - Column count > Data count " + DataFileName, WARNING);
				Message(Except.Message.c_str(),
				string("Header of file defines fewer observations than data columns (" + string(Cols) + ")").c_str(), mbOK);
				LogError(Except);*/
			}

			char c = DataFile.peek();

			if (DataFile.eof()) { // one line file
				DataFile.clear();
				/*          CRHMException Except("Observation file warning " + DataFileName, ERR);
				Message(Except.Message.c_str(),
				"ONE line observation file!", mbOK);
				LogError(Except);*/
				OneLine = true;
				Dt2 = Dt1 + 1.0;
				Freq = 1;
				SparseFlag = true;
				Interval = 0.0;
				break;
			}
		} while (Global::DTstart != 0.0 && Global::DTstart > Dt1);

		if (Global::DTstart == 0.0) Global::DTstart = floor(Dt1);

		if (!OneLine) {
			if (DecimalTime)
				DataFile >> Dt2;
			else {
				for (int ii = 0; ii < 5; ii++)
					DataFile >> D[ii];
				Position = HdrLen + 1;
				Dt2 = Encode24(D);
			}

			Dt2 += TimeShiftFilter;

			Interval = Dt2 - Dt1;
			if (Interval > 1.0) {
				Interval = 1.0;
				SparseFlag = true;
			}

			Freq = (long)(1.0 / Interval + 0.8*Interval);
			Freq = Veto_Freq(Freq);

			Interval = (double) 1.0 / Freq;
			if (FirstFile)
				IndxMin = 0;
			else {
				IndxMin = (long)floor((Dt1 - Global::DTstart)*Freq + Interval / 2.0);
				if (Interval != 1) // Oct 30
					--IndxMin;
			}
			double mid = floor(Dt1) + Interval;
			float range = 0.00002;
			if (Dt1 > mid + range || (Dt1 < mid - range && Interval < 1.0)) { // ensure data starts at first interval  //warning resolved by Manishankar
																			/*          CRHMException Except("Observation file WARNING " + DataFileName, ERR);
																			Message(Except.Message.c_str(),
																			"First interval must start at midnight + interval! ", mbOK);
																			LogError(Except);*/

				if (IndxMin == 0)
					IndxMin = (long)((Dt1 - floor(Dt1)) / Interval - 1);
			}

			DataFile.seekg(0, ios_base::end);
			ifstream::pos_type Back = DataFile.tellg();// -3;
			char c;

			bool white = true;
			long Fix = -3;
			do {
				DataFile.seekg(Fix, ios::end);  // find last line in file
				--Fix;
				c = DataFile.get();
				if (white)
					white = isspace(c);
			} while (c != '\n' || white);

			if (DecimalTime)
				DataFile >> Dt2;
			else {
				for (int ii = 0; ii < 5; ii++)  // read last date and time
					DataFile >> D[ii];
				Position = 99998;
				Dt2 = Encode24(D);
			}
		} // not one line

		Dt2 += TimeShiftFilter;

		if (Global::DTend == 0.0) Global::DTend = Dt2;  // first data file

		if (Global::DTend != 0.0 && Global::DTend < Dt2) Dt2 = Global::DTend;

		Lines = (long)ceil((Dt2 - Dt1 + (float)1.0 / ((int)Freq * 2))* (int)Freq);

		if (SparseFlag && Lines < Global::Freq) // handle short interval with lots of sparse points
			Lines = Global::Freq;

		IndxMax = IndxMin + Lines - 1;

		DataFile.seekg(0, ios_base::beg);  // go back to beginning of data

		getline(DataFile, Comment);
		while (Comment[0] != '#') // space by header
			getline(DataFile, Comment);

	} // !Simulation

	try
	{
		//Data = new float*[DataCnt + FilterCnt];   // Data [Cnt] [Lines]
		//for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
		//	Data[jj] = new float[Lines];
		//Times = new double[Lines];

		Data = new float*[DataCnt + FilterCnt];   // Data [Cnt] [Lines]
		MaxLines = Lines;
		if (fmodl(Lines, Freq) > 0) // if missing data in last day - pad to midnight
			MaxLines = (Lines / Freq + 1)*Freq;
		for (int jj = 0; jj < DataCnt + FilterCnt; jj++)
		{
			Data[jj] = new float[MaxLines];
		}
		Times = new double[MaxLines];
	}

	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate for observations file: " +
			DataFileName, ERR);
		LogError(Except);
		Data = NULL;
	}





	//Mani look at this
	//trying to initialize data[][].
	for (int i = 0; i < Lines; i++)
	{
		for (int j = 0; j < DataCnt + FilterCnt; j++)
		{
			//Data[j][i] = 35.93;//-999999; //Changed by Manishankar to make it look like the original graph.
			Data[j][i] = -999999;
		}
	}



	myMacro->fixup(); // required by myMacro->execute(Position)

					  /*    TCursor OriginalCursor = Screen->Cursor;
					  Screen->Cursor = crHourGlass;*/
	Dt1 = floor(Dt1);

	//    try{
	//char c;
	double DeltaH = Interval * 1.5;


	for (Position = 0; Position < Lines; ++Position)
	{
		/*        if(Position%100 == 0) {
		if(!Simulation)
		Update_Main_Status("Observation Line " + string(Position+1));
		else
		Update_Main_Status("Simulation Line " + string(Position+1));

		Application->ProcessMessages();
		}*/



		if (!Simulation)
		{
			if (DecimalTime)
				DataFile >> Times[Position];
			else
			{
				for (int ii = 0; ii < 5; ++ii)
					DataFile >> D[ii];
				Times[Position] = Encode24(D);
			}

			if (DataFile.eof()) // handles sparse files
			{
				Lines = Position;
				break;
			}

			if (!DecimalTime) Times[Position] = Encode24(D);

			Times[Position] += TimeShiftFilter;

			Global::DTnow = Times[Position];

			if (Position != 0 && Times[Position] <= Times[Position - 1]) {
				string S;
				//S.sprintf("Earlier Date at line: %u+, %5u %3u %3u %3u %3u in observation file ", Position, D[0], D[1], D[2], D[3], D[4]);

				//CRHMException Except(S + DataFileName, ERR);
				//Message(S.c_str(), "Error in Observation File", mbOK);
				//LogError(Except);
				LineError = true;
				break;
			}

			for (int ii = 0; ii < DataCnt; ++ii) {
				char c;
				while (c = DataFile.peek(), c == ' ' || c == '\t') DataFile.get();

				if (DataFile.peek() == '\n') { // handles short line

											   //String S = String("Check line ") + String(HdrLen + Position + 1) + String(" for missing columns in ");
											   //CRHMException Except(S.c_str() + DataFileName, ERR);
					if (!SparseFlag) {
						//Application->MessageBox(Except.Message.c_str(),
						//"Project observation file - too few columns", MB_OK);
					}

					if (FirstFile) { // definitely error
									 //LogError(Except);
						LineError = true; // will break out of loop
					}
					else if (ii == 0) { // assume sparse in first column
						SparseFlag = true;
						--Position;
						continue;
					}
					else // any column but the first - assume missing
						Data[ii][Position] = 35.93;//Data[ii][Position] = -999999;

				}
				else
					DataFile >> Data[ii][Position];

				if (DataFile.fail()) { // handles faulty data
									   //String S = String("Faulty data at line ") + String(HdrLen + Position + 1)
									   //+ String(" in observation file ");
									   //CRHMException Except(S.c_str() + DataFileName, ERR);
									   //Application->MessageBox(Except.Message.c_str(),
									   //"Project observation file", MB_OK);
									   //LogError(Except);
					Lines = Position - 1;
					LineError = true;
					break;
				} // DataFile.fail
			} // for data loop


			if (LineError) break;

			if (DataFile.peek() != '\n') // gobbles up rest of line
				DataFile.ignore(256, '\n');


			//manishankar. The condition "Times[Position] >= Times[Position - 1] + DeltaH" was being true and thus the SparseFlag was being set.
			//However, I checked the data and saw that the date entries are not really sparse although this condition was being true.
			//I have thus commented this out.
			/*
			if (Position != 0 && Times[Position] >= Times[Position - 1] + DeltaH)
			{
				if (!SparseFlag)
				{
					SparseFlag = true;
					if (FirstFile)
					{
						//string S;
						//if(DecimalTime)
						//S.sprintf("Discontinuous Date: \"%5f\" at line: %u", Times[Position], Position + HdrLen + 1);
						//else
						//S.sprintf("Discontinuous Date: \"%5u %3u %3u %3u %3u\" at line: %u", D[0], D[1], D[2], D[3], D[4], HdrLen + Position + 1);

						//Message(S.c_str(), string("Warning Sparse Observation File: " + DataFileName).c_str(), mbOK);
					}
				}

			} // if !Simulation			
			}*/

			myMacro->execute(Position);
		} //end if

	} //end for

	  /*    __finally
	  {
	  Screen->Cursor = OriginalCursor;
	  }*/


	if (Dt2 > Times[Position - 1] + Interval / 2.0 && !SparseFlag && !Simulation) {
		/*     string S = string("Interval frequency increases ") + string(" in observation file ");
		CRHMException Except(S + DataFileName, ERR);
		Message(Except.Message.c_str(), "Project observation file", mbOK);
		LogError(Except);*/
		SparseFlag = true;
	}

	if (Freq > 1 && fmodl(Lines, Freq) > 0 && !SparseFlag) {

		CRHMException Except("Last day is incomplete and is padded with 0.0 " + DataFileName, WARNING);
		LogError(Except);

		IndxMax = IndxMin + MaxLines - 1;

		for (long ll = Position; ll <= MaxLines - 1; ++ll) {
			Times[ll] = Times[ll - 1] + 1.0 / Freq;
			Dt2 = Times[ll];

			for (long dd = 0; dd < DataCnt; ++dd)
				Data[dd][ll] = 0.0;
		}
	}


	if (LineError) { // clean up and flag error
		for (int ii = 0; ii < DataCnt + FilterCnt; ii++)
			if (Data[ii]) { // may already have been deleted if not used by the filter
				delete[] Data[ii];
				Data[ii] = NULL;
			}
		delete[] Data;
		Data = NULL;
		delete[] Times;
		Times = NULL;
	}
	else {
		if (Lines < Freq)  // Handle less than one day
			SparseFlag = true;

		if (!SparseFlag) {
			delete[] Times;
			Times = NULL;

			if ((ForceInterval == 96 && Freq == 144) || (ForceInterval == 144 && Freq == 96)) { // cannot convert 10 minute to 15 minute or vice versa  //warning resolved by Manishankar.
																							/*          string S = string("cannot convert 10 minute interval to 15 minute or vice versa") + string(" in observation file ");
																							CRHMException Except(S + DataFileName, ERR);
																							Message(Except.Message.c_str(), "Project observation file", mbOK);
																							LogError(Except);*/
				ForceInterval = 0;
			}

			if (ForceInterval != Freq && ForceInterval) {
				float Result = 0.0;

				for (int jj = 0; jj < DataCnt + FilterCnt; ++jj) { // convert all observations

					if (!Data[jj]) {
						continue;
					}

					float Divisor = 1.0;
					long NCnt;
					float Delta;

					if (ForceInterval > Freq) { // expand data
						NCnt = ForceInterval / Freq;
						float *NewData = new float[Lines*NCnt];
						if (!MyBitSet[jj]) {
							for (long ii = 0; ii < Lines*NCnt; ++ii) {
								long kk = ii % NCnt;
								if (kk == 0) {
									if (ii == 0) {
										Result = Data[jj][ii / NCnt] * Divisor;
										Delta = 0.0;
									}
									else if (ii + NCnt >= Lines * NCnt) {
										Result = Data[jj][ii / NCnt] * Divisor;
										Delta = 0.0;
									}
									else {
										Result = Data[jj][ii / NCnt - 1] * Divisor;
										Delta = (Data[jj][ii / NCnt] - Data[jj][ii / NCnt - 1])*Divisor;
									}
								}
								NewData[ii] = Result + Delta * (ii%NCnt + 1) / NCnt;
							}
						}
						else {
							Divisor = (float)1.0 / NCnt;
							for (long ii = 0; ii < Lines*NCnt; ++ii) {
								long kk = ii % NCnt;
								if (kk == 0)
									Result = Data[jj][ii / NCnt] * Divisor;
								NewData[ii] = Result;
							}
						}

						delete[] Data[jj];
						Data[jj] = NewData;

						if (jj + 1 == DataCnt + FilterCnt) {
							Lines = Lines * NCnt;
							Freq = Freq * NCnt;
							Interval = Interval / NCnt;
							IndxMin *= TimeShiftFilter;
							IndxMax = IndxMin + Lines - 1;
						}
					} // expand data
					else { // shrink data
						long NCnt = Freq / ForceInterval;
						float *NewData = new float[Lines / NCnt];
						if (!MyBitSet[jj])
							Divisor = (float)NCnt;
						Result = 0.0;
						for (long ii = 0; ii < Lines; ++ii) {
							Result += Data[jj][ii];
							long kk = ii % NCnt;
							if (kk == NCnt - 1) {
								NewData[ii / NCnt] = Result / Divisor;
								Result = 0.0;
							}
						}
						delete[] Data[jj];
						Data[jj] = NewData;
					} // shrink data
				} // convert all observations

				if (ForceInterval < Freq) { // shrink data
					long NCnt = Freq / ForceInterval;
					Lines = Lines / NCnt;
					Freq = Freq / NCnt;
					Interval = Interval * NCnt;
					IndxMax = IndxMin + Lines - 1;
				}
				myMacro->fixup(); // required by myMacro->execute(Position)
			}
		}
		else { //allocate space required
			double *Temp = new double[Lines];
			for (long ii = 0; ii < Lines; ++ii)
				Temp[ii] = Times[ii];
			delete[] Times;
			Times = Temp;
		}
	}

	delete myMacro;
	myMacro = NULL;
	DataFile.close();
	return true;
}

//---------------------------------------------------------------------------

ClassData::~ClassData() {

	if (Times != NULL) {
		delete[] Times;
		Times = NULL;
	}

	if (Data != NULL) {
		for (int ii = 0; ii < DataCnt + FilterCnt; ii++)
			if (Data[ii]) { // may already have been deleted if not used by the filter
				delete[] Data[ii];
				Data[ii] = NULL;
			}
		delete[] Data;
		Data = NULL;
	}
	if (HdrLen == 0)
		return; // not actual observation but Obs function

	if (myMacro) {
		delete myMacro;
		myMacro = NULL;
	}

	// Remove completely any observations never used by any module

	MapVar::iterator itVar;
	ClassVar *thisVar;


	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end();) {
		thisVar = (*itVar).second;
		if (thisVar->varType == CRHM::Read && thisVar->FileData == this) {
			delete thisVar;
			Global::MapVars.erase(itVar++);
		}
		else
			++itVar;
	}

	// Demote observations used by currently loaded modules

	for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++) {
		thisVar = (*itVar).second;
		if (thisVar->FileData == this && (thisVar->varType == CRHM::ReadF || thisVar->varType == CRHM::ReadI || thisVar->varType == CRHM::Float)) {
			thisVar->FileData = NULL;

			if (thisVar->varType == CRHM::Float) { // handles TDay, RHDay and EADay
				thisVar->FunctVar = NULL;
				thisVar->CustomFunct = NULL;
				thisVar->CustomFunctName = "";
				continue;
			}

			thisVar->ReleaseM();
			thisVar->dim = 1;
			thisVar->dimMax = 1;
			if (thisVar->DLLName.empty())
				thisVar->cnt = 0;
			thisVar->offset = 0;

			if (thisVar->varType == CRHM::ReadI) thisVar->varType = CRHM::Int;
			if (thisVar->varType == CRHM::ReadF) thisVar->varType = CRHM::Float;
		}
	}
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//Changed by Manishankar 2018/09/10

long julian(string when) {
	int Y, M, D, H, Min;
	double DtBegin;
	//CTime
	// calendar

	if (when == "start") {
		StandardConverterUtility::DecodeDateTime(Global::DTstart, &Y, &M, &D, &H, &Min);
		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);
		return  INT(Global::DTstart - DtBegin);  // -0.999/Global::Freq
	}
	else if (when == "end") {
		StandardConverterUtility::DecodeDateTime(Global::DTend, &Y, &M, &D, &H, &Min);
		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);
		return  INT(Global::DTend - DtBegin);
	}
	else { // now
		StandardConverterUtility::DecodeDateTime(Global::DTnow, &Y, &M, &D, &H, &Min);
		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);
		return  INT(Global::DTnow - DtBegin);
	}
}







//---------------------------------------------------------------------------
//Changed by Manishankar 2018/09/10

long julian(double DT) {
	int Y, M, D, H, Min;
	double DtBegin;

	StandardConverterUtility::DecodeDateTime(DT, &Y, &M, &D, &H, &Min);
	DtBegin = StandardConverterUtility::EncodeDateTime(Y - 1, 12, 31, 0, 0);
	return  INT(DT - DtBegin);
}


//---------------------------------------------------------------------------
//Changed by Manishankar 2018/09/10

long MonthDaysCnt(double DT) {
	int Y, M, D, H, Min;
	double DTNext;

	StandardConverterUtility::DecodeDateTime(DT, &Y, &M, &D, &H, &Min);
	++M;

	if (M > 12) { // next year
		M = 1;
		++Y;
	}

	DTNext = StandardConverterUtility::EncodeDateTime((Word)Y, (Word)M, (Word)D, 0, 0);
	return  INT(DTNext - DT);
}


//---------------------------------------------------------------------------
//Changed by Manishankar 2018/09/10

float Julian(string when) {
	int Y, M, D, H, Min;
	double DtBegin;

	// calendar

	if (when == "start") {
		StandardConverterUtility::DecodeDateTime(Global::DTstart, &Y, &M, &D, &H, &Min);
		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);
		return  (float)(Global::DTstart - DtBegin);  // -0.999/Global::Freq
	}
	else if (when == "end") {
		StandardConverterUtility::DecodeDateTime(Global::DTend, &Y, &M, &D, &H, &Min);
		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);
		return  (float)(Global::DTend - DtBegin);
	}
	else { // now
		StandardConverterUtility::DecodeDateTime(Global::DTnow, &Y, &M, &D, &H, &Min);
		DtBegin = StandardConverterUtility::EncodeDateTime((Word)Y - 1, (Word)12, (Word)31, 0, 0);
		return  float((double)Global::DTnow - DtBegin);
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
	int Year, Month, Day, H, Min, Sec = 0, MSec;

	if (type == "start") {
		StandardConverterUtility::DecodeDateTime(Global::DTstart, &Year, &Month, &Day, &H, &Min);
		//DecodeTime(Global::DTstart, &H, &Min, &Sec);
	}
	else if (type == "end") {
		StandardConverterUtility::DecodeDateTime(Global::DTend, &Year, &Month, &Day, &H, &Min);
		//DecodeTime(Global::DTend, &Hour, &Min, &Sec);
	}
	else {
		StandardConverterUtility::DecodeDateTime(Global::DTnow, &Year, &Month, &Day, &H, &Min);
		//DecodeTime(Global::DTnow, &Hour, &Min, &Sec);
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
	int Year, Month, Day, H, Min, Sec = 0, MSec;

	StandardConverterUtility::DecodeDateTime(DT, &Year, &Month, &Day, &H, &Min);
	//DecodeTime(DT, &Hour, &Min, &Sec);

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
			if (thisVar->varType < CRHM::Read) {
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
		case CRHM::ReadI:
			if (thisVar->lay > 0) { // handles NFREQ
				for (int ii = 0; ii < thisVar->lay; ++ii)
					delete[] thisVar->ilayvalues[ii];

				delete[] thisVar->ilayvalues;  //Array [nhru] [lay]
				thisVar->lay = 0;
				thisVar->ilayvalues = NULL;
			}

			delete[]thisVar->ivalues;
			thisVar->ivalues = NULL;
			thisVar->varType = CRHM::Read;
			thisVar->dim = thisVar->cnt;
			break;
		case CRHM::ReadF:

			if (thisVar->lay > 0) { // handles NFREQ
				for (int ii = 0; ii < thisVar->lay; ++ii)
					delete[] thisVar->layvalues[ii];

				delete[] thisVar->layvalues;  //Array [nhru] [lay]
				thisVar->lay = 0;
				thisVar->layvalues = NULL;
			}

			delete[]thisVar->values;
			thisVar->values = NULL;
			thisVar->varType = CRHM::Read;
			thisVar->dim = thisVar->cnt;
			break;
		case CRHM::Int:
		case CRHM::Float:
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
		if (thisVar->varType >= CRHM::Read) {
			LogError(CRHMException("Duplicate Observation variable: " + s1 + " " + s2, ERR));
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
		thisVar->layvalues = new float *[thisVar->lay];
		for(int ii = 0; ii < thisVar->lay; ii++)
		thisVar->layvalues[ii] = new float[thisVar->dim];
		}
		thisVar->values = new float[thisVar->dim];
		}
		*/
		if (thisVar->varType == CRHM::Int)
			thisVar->varType = CRHM::ReadI;
		if (thisVar->varType == CRHM::Float)
			thisVar->varType = CRHM::ReadF;

		return thisVar;
	}

	thisVar = new ClassVar(module, name, cnt, offset, FileData);


	if (thisVar->name == "p" || thisVar->name == "ppt") // must be NHRU for routine "ReadVar" when obs file loaded after modules.
		thisVar->dimen = CRHM::NHRU;

	thisVar->varType = CRHM::Read;
	thisVar->units = units;
	thisVar->help = Comment;

	PairVar Item = PairVar(s1 + ' ' + s2, thisVar);
	Global::MapVars.insert(Item);

	return thisVar;
}

//---------------------------------------------------------------------------
void Classfilter::fixup(void) { // must wait till memory allocated

	for (int ii = 0; ii < Vs; ++ii) {  // fixup Vs variables except destination
		if (!Data[ii])
			Data[ii] = new float *[ObsCnt];

		for (int jj = 0; jj < ObsCnt; ++jj) { // fixup all observations

			if (ii == Vs - 1 && DataIndx[ii] + jj < TotalCnt) { // array dimensioned ObsCnt
				if (MyObs->Data[TotalCnt + jj]) // was being deleted twice - should be fixed
					delete[] MyObs->Data[TotalCnt + jj];  // not used
				MyObs->Data[TotalCnt + jj] = NULL;    // indicate to destructor
			}

			int jjj = jj;
			if (jjj > DataObsCnt[ii] - 1) // source may not have dimension ObsCnt
				jjj = DataObsCnt[ii] - 1; // variable has too few observations
			float * X = MyObs->Data[DataIndx[ii] + jjj];
			Data[ii][jj] = X;
		}
	}
}

//---------------------------------------------------------------------------

void Classfilter::readargs() {

	MapVar::iterator itVar;
	ClassVar *thisVar;
	istringstream instr;
	double C;
	string V;

	long ee = args.find(")");
	string Comment = args.substr(ee + 1, args.size());
	Common::trim(Comment);
	if (Comment.empty())
		Comment = "filter";
	else {
		long tt;
		while (tt = Comment.find("\\t"), tt != string::npos) {
			Comment.erase(tt, 1);
			Comment[tt] = ' ';
		}
	}

	args = args.substr(1, ee - 1);
	while (ee = args.find(','), ee > 0) args[ee] = ' ';

	instr.str(args);
	long Cnt;
	long IndexC = 0;
	long IndexV = 0;
	long pp, pp2;

	for (Cnt = 0; Cnt < argtypes.length(); ++Cnt) { // allow for output location
		instr >> V;
		if (instr.fail()) break;
		pp = V.find_first_not_of("0123456789 //:.+-Ee_");
		if (pp == -1) { // constant
			if (argtypes[Cnt] != 'C') {
				error("expected constant");
				return;
			}

			pp = V.find_first_of("://_");
			if (pp != -1) { // time
				pp2 = V.find_first_of("_");
				if (pp2 == -1) {
					if (V[pp] == '/')
						C = StrToDate(V);
					else
						C = StrToTime(V);
				}
				else {
					string z(V, 1, pp2 - 1);
					C = StrToDate(z);
					z.assign(V, pp2 + 1, V.size());
					C += double(StrToTime(z) - 1.0 / Global::Freq);
				}
			}
			else
				C = Common::StrtoDt(V);

			Constants[IndexC++] = C;
		}
		else {               // variable
			if (argtypes[Cnt] != 'V') {
				error("expecting CONSTANT");
				return;
			}

			if ((itVar = Global::MapVars.find("obs " + V)) != Global::MapVars.end()) {
				thisVar = (*itVar).second;
				if (thisVar->varType < CRHM::Read) {
					error("not observation variable");
					return;
				}
			}
			else {
				error("unknown variable");
				return;
			}

			DataIndx[IndexV] = thisVar->offset;
			DataObsCnt[IndexV] = thisVar->dim;
			++IndexV;

			if (ObsCnt == 0 || thisVar->dim < ObsCnt)
				ObsCnt = thisVar->dim;
		}
	}

	if (Cnt != argtypes.length()) {
		error("too few arguments");
		return;
	}

	if (Cnt > argtypes.length()) {
		error("too many arguments");
		return;
	}

	if (!ToVar.empty()) {

		TotalCnt = MyObs->DataCnt + MyObs->FilterCnt;
		if (ObsCnt == 0) ++ObsCnt; // handle case of constant

		MyObs->FilterCnt += ObsCnt;

		if ((itVar = Global::MapVars.find("obs " + ToVar)) != Global::MapVars.end()) {
			thisVar = (*itVar).second;
			if (thisVar->varType >= CRHM::Read) {
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




//---------------------------------------------------------------------------
Classfilter::Classfilter(ClassData *MyObs, string ToVar, string args, string argtypes) :
	MyObs(MyObs), ToVar(ToVar), args(args), argtypes(argtypes),
	Vs(0), Cs(0), Error(0), ObsCnt(0), TotalCnt(0), FirstTime(true) {

	for (int ii = 1; ii < argtypes.length() + 1; ++ii) {
		if (argtypes[ii] == 'V') Vs++;
		else if (argtypes[ii] == 'C') Cs++;
	}

	if (!ToVar.empty()) // 11/10/11
		++Vs;

	if (Vs) {
		Data = new float **[Vs];  // increment
		for (int ii = 0; ii < Vs; ++ii)
			Data[ii] = NULL;

		DataIndx = new long[Vs];
		DataObsCnt = new long[Vs];
	}

	if (Cs > 0) Constants = new double[Cs];
}

//---------------------------------------------------------------------------
void Classfilter::doFunctions(long Line) {
	for (int jj = 0; jj < ObsCnt; ++jj)
		doFunc(jj, Line);
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
	CRHMException Except(Mess2.c_str(), ERR);
	////Application->MessageBox(Mess2.c_str(), string("Error in filter: " + F + "\" in observation file: \"" + MyObs->DataFileName.c_str() + "\"").c_str(), MB_OK);
	LogError(Except);
	Error = true;
}

//---------------------------------------------------------------------------


void Classmacro::addfilter(string Line) {

	Classfilter *NewFilter;

	string S = Line.substr(1, Common::trim(Line).length());

	if (Line.substr(1, 1) == "$") return; // handle comment

	long bb = S.find('(');

	long ee;
	//  for(ee = 1; ee < bb; ++ee)
	ee = S.find_first_of(" \t");

	string ToVar = "";
	if (bb > ee)    // filter returns value
		ToVar = S.substr(0, ee);
	else
		ee = 1;      // only "sim" ForceInterval and TimeShift at present

	S = S.substr(ee);
	S = Common::trim(S);

	ee = S.find('(');
	string Filter = S.substr(0, ee);
	string FilterStuff = S.substr(ee);
	FilterStuff = Common::trim(FilterStuff);

	if (ToVar.empty()) {
		if (Filter == "Sim") NewFilter = (Classfilter*) new ClassSim(File, ToVar, FilterStuff);
		else if (Filter == "ForceInterval") NewFilter = (Classfilter*) new ClassForce(File, ToVar, FilterStuff);
		else if (Filter == "TimeShift") NewFilter = (Classfilter*) new ClassTimeshift(File, ToVar, FilterStuff);
		else {
			string Mess = "Filter: '" + Filter + " has no 'to variable'";
			/*      CRHMException Except(Mess.c_str(), ERR);
			Message(Mess.c_str(), "Error in filter in observation file", mbOK);
			LogError(Except);*/
			return;
		}
	}
	else if (Filter == "missing") NewFilter = (Classfilter*) new ClassMissing(File, ToVar, FilterStuff);
	else if (Filter == "missing0") NewFilter = (Classfilter*) new ClassMissing0(File, ToVar, FilterStuff);
	else if (Filter == "missingC") NewFilter = (Classfilter*) new ClassMissingC(File, ToVar, FilterStuff);
	else if (Filter == "missingFlag") NewFilter = (Classfilter*) new ClassMissingFlag(File, ToVar, FilterStuff);
	else if (Filter == "missingFlagAfter") NewFilter = (Classfilter*) new ClassMissingFlagAfter(File, ToVar, FilterStuff);
	else if (Filter == "missingrepl") NewFilter = (Classfilter*) new ClassMissingrepl(File, ToVar, FilterStuff);
	else if (Filter == "missinginter") {
		NewFilter = (Classfilter*) new ClassMissingInter(File, ToVar, FilterStuff);
		++Interpolation;
	}
	else if (Filter == "ea") NewFilter = (Classfilter*) new Classea(File, ToVar, FilterStuff);
	else if (Filter == "rh") NewFilter = (Classfilter*) new Classrh(File, ToVar, FilterStuff);  //I have added this from the borland version.
	else if (Filter == "RH_WtoI") NewFilter = (Classfilter*) new ClassRH_WtoI(File, ToVar, FilterStuff);
	else if (Filter == "add") NewFilter = (Classfilter*) new Classadd(File, ToVar, FilterStuff);
	else if (Filter == "sub") NewFilter = (Classfilter*) new Classsub(File, ToVar, FilterStuff);
	else if (Filter == "mul") NewFilter = (Classfilter*) new Classmul(File, ToVar, FilterStuff);
	else if (Filter == "div") NewFilter = (Classfilter*) new Classdiv(File, ToVar, FilterStuff);
	else if (Filter == "addV") NewFilter = (Classfilter*) new ClassaddV(File, ToVar, FilterStuff);
	else if (Filter == "subV") NewFilter = (Classfilter*) new ClasssubV(File, ToVar, FilterStuff);
	else if (Filter == "mulV") NewFilter = (Classfilter*) new ClassmulV(File, ToVar, FilterStuff);
	else if (Filter == "divV") NewFilter = (Classfilter*) new ClassdivV(File, ToVar, FilterStuff);
	else if (Filter == "refwind") NewFilter = (Classfilter*) new Classrefwind(File, ToVar, FilterStuff);
	else if (Filter == "const") NewFilter = (Classfilter*) new Classconst(File, ToVar, FilterStuff);
	else if (Filter == "sine") NewFilter = (Classfilter*) new Classsin(File, ToVar, FilterStuff);
	else if (Filter == "sin") NewFilter = (Classfilter*) new Classsin(File, ToVar, FilterStuff); //I have added this from the borland version.
	else if (Filter == "cos") NewFilter = (Classfilter*) new Classcos(File, ToVar, FilterStuff); //I have added this from the borland version.
	else if (Filter == "abs") NewFilter = (Classfilter*) new Classabs(File, ToVar, FilterStuff); //I have added this from the borland version.
	else if (Filter == "square") NewFilter = (Classfilter*) new Classsquare(File, ToVar, FilterStuff);
	else if (Filter == "ramp") NewFilter = (Classfilter*) new Classramp(File, ToVar, FilterStuff);
	else if (Filter == "pulse") NewFilter = (Classfilter*) new Classpulse(File, ToVar, FilterStuff);
	else if (Filter == "exp") NewFilter = (Classfilter*) new Classexp(File, ToVar, FilterStuff);
	else if (Filter == "expV") NewFilter = (Classfilter*) new Classexpv(File, ToVar, FilterStuff);
	else if (Filter == "log") NewFilter = (Classfilter*) new Classlog(File, ToVar, FilterStuff);
	else if (Filter == "logV") NewFilter = (Classfilter*) new Classlogv(File, ToVar, FilterStuff);
	else if (Filter == "pow") NewFilter = (Classfilter*) new Classpow(File, ToVar, FilterStuff);
	else if (Filter == "powV") NewFilter = (Classfilter*) new Classpowv(File, ToVar, FilterStuff);
	else if (Filter == "time") NewFilter = (Classfilter*) new Classtime(File, ToVar, FilterStuff);
	else if (Filter == "julian") NewFilter = (Classfilter*) new Classjulian(File, ToVar, FilterStuff);
	else if (Filter == "random") NewFilter = (Classfilter*) new Classrandom(File, ToVar, FilterStuff);
	else if (Filter == "poly") NewFilter = (Classfilter*) new Classpoly(File, ToVar, FilterStuff);
	else if (Filter == "polyV") NewFilter = (Classfilter*) new Classpolyv(File, ToVar, FilterStuff);
	else if (Filter == "smear") NewFilter = (Classfilter*) new ClassSmear(File, ToVar, FilterStuff);
	else if (Filter == "FtoC") NewFilter = (Classfilter*) new ClassFtoC(File, ToVar, FilterStuff);
	else if (Filter == "KtoC") NewFilter = (Classfilter*) new ClassKtoC(File, ToVar, FilterStuff);
	else if (Filter == "CtoK") NewFilter = (Classfilter*) new ClassCtoK(File, ToVar, FilterStuff);
	else if (Filter == "replace") NewFilter = (Classfilter*) new ClassReplace(File, ToVar, FilterStuff); //I have added this from the borland version.
	else {
		string Mess = "Filter: '" + Filter + "' name not recognised";
		/*    CRHMException Except(Mess.c_str(), ERR);
		Message(Mess.c_str(), "Error in filter in observation file", mbOK);
		LogError(Except);*/
		return;
	}

	if (!NewFilter->Error) FilterList->AddObject(Filter, (TObject*)NewFilter);
	else delete NewFilter;
}




//---------------------------------------------------------------------------
void Classmacro::execute(long Line) {

	for (int ii = 0; ii < FilterList->Count; ii++)
		((Classfilter*)FilterList->Objects[ii])->doFunctions(Line);
}

//---------------------------------------------------------------------------
void Classmacro::fixup(void) {

	for (int ii = 0; ii < FilterList->Count; ii++)
		((Classfilter*)FilterList->Objects[ii])->fixup();
}

//---------------------------------------------------------------------------
Classmacro::Classmacro(ClassData *File) : File(File), Interpolation(0) {

	FilterList = new TStringList;
	FilterList->Sorted = false;
}

//---------------------------------------------------------------------------
Classmacro::~Classmacro() { // calls all filters to finalise data memory addresses

	if (Interpolation > 0 && FilterList->Count > Interpolation)
		LogError("Filter execution occurs before interpolation -> values may be incorrect." + File->DataFileName, WARNING);

	//for (int ii = 0; ii < FilterList->Count; ii++)
	//	delete (Classfilter*)FilterList->Objects[ii];
	delete FilterList;
}

//---------------------------------------------------------------------------
ClassFtoC::ClassFtoC(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassFtoC::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (float)((Data[0][Obs][Line] - 32.0)*5.0 / 9.0);
}

//---------------------------------------------------------------------------
ClassCtoK::ClassCtoK(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassCtoK::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (float)((Data[0][Obs][Line] + 273.15));
}

//---------------------------------------------------------------------------
ClassReplace::ClassReplace(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassReplace::doFunc(long Obs, long Line) {

	long shift = thisVar->FileData->IndxMin;
	for (int Obs = 0; Obs < ObsCnt; ++Obs)
		outVar->FileData->Data[Obs + DataIndx[Vs - 1]][Line + shift] = Data[0][Obs][Line];
	//    outVar->FileData->Data[Obs][Line  + shift] = thisVar->FileData->Data[Obs][Line];

}

//---------------------------------------------------------------------------
ClassKtoC::ClassKtoC(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {

	readargs();
}

void ClassKtoC::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (float)(Data[0][Obs][Line] - 273.15);
}

//---------------------------------------------------------------------------
ClassTimeshift::ClassTimeshift(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();

	MyObs->TimeShiftFilter = (float)Constants[0];
}

//---------------------------------------------------------------------------
ClassRH_WtoI::ClassRH_WtoI(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassRH_WtoI::doFunc(long Obs, long Line) {

	float T = Data[0][Obs][Line];
	float RH = Data[1][Obs][Line];

	if (T < 0.0)
		Data[Vs - 1][Obs][Line] = (float)(RH * 0.9995*exp(22.452*T / (272.55 + T)) / exp(17.502*T / (240.97 + T)));
	else
		Data[Vs - 1][Obs][Line] = RH;
}

//---------------------------------------------------------------------------
Classea::Classea(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

double estar(float t) /* Saturation vapour pressure */
{
	if (t > 0.0)
		return 0.611 * exp(17.27*t / (t + 237.3));
	else
		return 0.611 * exp(21.88*t / (t + 265.5));
}

void Classea::doFunc(long Obs, long Line) {

	if (Line == MyObs->IndxMax) // wait till last
		for (int Obs = 0; Obs < ObsCnt; ++Obs)
			for (long Line = MyObs->IndxMin; Line <= MyObs->IndxMax; ++Line)
				Data[Vs - 1][Obs][Line] = (float)(estar(Data[0][Obs][Line])* Data[1][Obs][Line] / 100.0);
}

//---------------------------------------------------------------------------
Classabs::Classabs(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classabs::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = abs(Data[0][Obs][Line]);
}

//---------------------------------------------------------------------------
Classrh::Classrh(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classrh::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (float)(Data[1][Obs][Line] / estar(Data[0][Obs][Line])*100.0);
}

//---------------------------------------------------------------------------
Classsin::Classsin(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classsin::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1)*MyObs->Freq);
			else
				delay = 0;

			if (Constants[3] > 0.0) {
				duration = (long)((Constants[3] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = (float)sin((float(Line) / period - float(phase) / period) * 2 * M_PI);
	}
}

//---------------------------------------------------------------------------
Classcos::Classcos(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classcos::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1)*MyObs->Freq);
			else
				delay = 0;

			if (Constants[3] > 0.0) {
				duration = (long)((Constants[3] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = (float)cos((float(Line) / period - float(phase) / period) * 2 * M_PI);
	}
}

//---------------------------------------------------------------------------
Classramp::Classramp(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classramp::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1)*MyObs->Freq);
			else
				delay = 0;

			if (Constants[3] > 0.0) {
				duration = (long)((Constants[3] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else {
			Data[Vs - 1][Obs][Line] = 0.0;
			float X = (float)fmod(float(Line - delay) / float(period)*2.0, 1.0);
			if (((Line + phase - delay) % period) >= period / 2)
				Data[Vs - 1][Obs][Line] = (float)1.0 - X;
			else
				Data[Vs - 1][Obs][Line] = X;
		}
	}
}

//---------------------------------------------------------------------------
Classsquare::Classsquare(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classsquare::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			period = (long)(Constants[0] * MyObs->Freq);
			phase = (long)(Constants[1] * MyObs->Freq);

			if (Constants[2] > MyObs->Dt1 && Constants[2] < MyObs->Dt2)
				delay = (long)((Constants[2] - MyObs->Dt1)*MyObs->Freq - 1);
			else
				delay = -1;

			if (Constants[3] > 0.0) {
				duration = (long)((Constants[3] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else {
			if (((Line + phase) % period) >= period / 2)
				Data[Vs - 1][Obs][Line] = 0.0;
			else
				Data[Vs - 1][Obs][Line] = 1.0;
		}
	}
}

//---------------------------------------------------------------------------
Classpulse::Classpulse(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classpulse::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			if (Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
				delay = (long)((Constants[0] - MyObs->Dt1)*MyObs->Freq - 1);
			else
				delay = -1;

			if (Constants[1] > 0.0) {
				duration = (long)((Constants[1] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = 1.0;
	}
}

//---------------------------------------------------------------------------
Classexp::Classexp(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classexp::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			if (Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
				delay = (long)((Constants[0] - MyObs->Dt1)*MyObs->Freq - 1);
			else
				delay = -1;

			if (Constants[1] > 0.0) {
				duration = (long)((Constants[1] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			A = (float)Constants[2];
			B = (float)(Constants[3] / MyObs->Freq);

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = A * exp(B*(Line - delay - 1));
	}
}

//---------------------------------------------------------------------------
Classexpv::Classexpv(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error) {
		A = (float)Constants[0];
		B = (float)Constants[0];
	}
}

void Classexpv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = A * exp(B*Data[0][Obs][Line]);
}

//---------------------------------------------------------------------------
Classpoly::Classpoly(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classpoly::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {

			if (Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
				delay = (long)((Constants[0] - MyObs->Dt1)*MyObs->Freq - 1);
			else
				delay = -1;

			if (Constants[1] > 0.0) {
				duration = (long)((Constants[1] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else {
			float x = (Line - delay - 1) / float(MyObs->Freq);
			Data[Vs - 1][Obs][Line] = (float)(Constants[2] + Constants[3] * x + Constants[4] * x*x
				+ Constants[5] * x*x*x + Constants[6] * x*x*x*x);
		}
	}
}

//---------------------------------------------------------------------------
Classpolyv::Classpolyv(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classpolyv::doFunc(long Obs, long Line) {

	float x = Data[0][Obs][Line];
	Data[Vs - 1][Obs][Line] = (float)(Constants[0] + Constants[1] * x +
		Constants[2] * x*x +
		Constants[3] * x*x*x +
		Constants[4] * x*x*x*x);
}

//---------------------------------------------------------------------------
Classlog::Classlog(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classlog::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {

			if (Constants[0] > MyObs->Dt1 && Constants[0] < MyObs->Dt2)
				delay = (long)((Constants[0] - MyObs->Dt1)*MyObs->Freq - 1);
			else
				delay = -1;

			if (Constants[1] > 0.0) {
				duration = (long)((Constants[1] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			A = (float)Constants[2];
			B = (float)fabs(Constants[3]);

			FirstTime = false;
		}

		if (Line <= delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = A * log(B*float(Line - delay) / MyObs->Freq);
	}
}

//---------------------------------------------------------------------------
Classlogv::Classlogv(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error) {
		A = (float)fabs(Constants[0]);
		B = (float)fabs(Constants[1]);
	}
}

void Classlogv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = A * log(B*Data[0][Obs][Line]);
}

//---------------------------------------------------------------------------
Classpow::Classpow(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classpow::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			if (Constants[0] >= MyObs->Dt1 && Constants[0] <= MyObs->Dt2)
				delay = (long)((Constants[0] - MyObs->Dt1)*MyObs->Freq);
			else
				delay = -1;

			if (Constants[1] > 0.0) {
				duration = (long)((Constants[1] - MyObs->Dt1)*MyObs->Freq - 1);
				if (duration <= 0) duration = MyObs->IndxMax;
			}
			else
				duration = MyObs->IndxMax;

			A = (float)Constants[2];
			B = (float)Constants[3];

			FirstTime = false;
		}

		if (Line < delay || Line > duration)
			Data[Vs - 1][Obs][Line] = 0.0;
		else
			Data[Vs - 1][Obs][Line] = A * pow((Line - delay + 1) / float(MyObs->Freq), B);
	}
}

//---------------------------------------------------------------------------
Classpowv::Classpowv(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error) {
		A = (float)Constants[0];
		B = (float)Constants[1];
	}
}

void Classpowv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = A * pow(Data[0][Obs][Line], B);
}

//---------------------------------------------------------------------------
Classtime::Classtime(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classtime::doFunc(long Obs, long Line) {

	if (!Error) {
		if (FirstTime) {
			option = (int)Constants[0];
			if (option)
				start = 0.0;
			else
				start = floor(Global::DTstart);

			FirstTime = false;
		}

		Data[Vs - 1][Obs][Line] = float(start + Line / float(MyObs->Freq));
	}
}

//---------------------------------------------------------------------------
Classjulian::Classjulian(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error)
		option = (int)Constants[0];
}

void Classjulian::doFunc(long Obs, long Line) {

	switch (option) {
	case 0: Data[Vs - 1][Obs][Line] = (float)julian("now"); break;
	case 1: Data[Vs - 1][Obs][Line] = (float)julian("start"); break;
	case 2: Data[Vs - 1][Obs][Line] = (float)julian("end"); break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------
Classrandom::Classrandom(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
	if (!Error)
		srand((unsigned)Constants[0]);
}

void Classrandom::doFunc(long Obs, long Line) {
	Data[Vs - 1][Obs][Line] = (float)rand() / RAND_MAX;
}

//---------------------------------------------------------------------------
Classrefwind::Classrefwind(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {

	readargs();
	if (!Error) {
		float d = (float)(Constants[2] * 2.0 / 3.0);  // zero plane
		float Z = (float)(Constants[2] * 0.123);    // roughness
		Const = (float)(log((Constants[1] - d) / Z) / log((Constants[0] - d) / Z));
	}
}

void Classrefwind::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] * Const;
}

//---------------------------------------------------------------------------
Classadd::Classadd(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classadd::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] + (float)Constants[0];
}

//---------------------------------------------------------------------------
Classsub::Classsub(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classsub::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] - (float)Constants[0];
}

//---------------------------------------------------------------------------
Classmul::Classmul(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classmul::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] * (float)Constants[0];
}

//---------------------------------------------------------------------------
Classdiv::Classdiv(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classdiv::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] / (float)Constants[0];
}

//---------------------------------------------------------------------------
ClassaddV::ClassaddV(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassaddV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] + Data[1][Obs][Line];
}

//---------------------------------------------------------------------------
ClasssubV::ClasssubV(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClasssubV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] - Data[1][Obs][Line];
}

//---------------------------------------------------------------------------
ClassmulV::ClassmulV(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassmulV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] * Data[1][Obs][Line];
}

//---------------------------------------------------------------------------
ClassdivV::ClassdivV(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void ClassdivV::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = Data[0][Obs][Line] / Data[1][Obs][Line];
}

//---------------------------------------------------------------------------
Classconst::Classconst(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();
}

void Classconst::doFunc(long Obs, long Line) {

	Data[Vs - 1][Obs][Line] = (float)Constants[0];
}

//---------------------------------------------------------------------------
ClassSim::ClassSim(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();

	MyObs->Simulation = true;
	MyObs->Dt1 = Constants[0];
	MyObs->Dt2 = Constants[1];
	MyObs->Interval = Constants[2] / 24.0;
	MyObs->Freq = (long)(1.0 / MyObs->Interval + 1.0 / 192.0);
	MyObs->Lines = (long)(ceil(MyObs->Dt2 - MyObs->Dt1)*MyObs->Freq);
	MyObs->IndxMin = 0;
	MyObs->IndxMax = (long)(floor((MyObs->Dt2 - MyObs->Dt1)*MyObs->Freq + MyObs->Interval / 2.0) - 1);

	// first data file?  Following necessary for use by filters
	if (Global::DTstart == 0.0) {
		Global::DTstart = floor(MyObs->Dt1);
		Global::DTend = floor(MyObs->Dt2);
		Global::DTnow = Global::DTstart;
		Global::Freq = MyObs->Freq;
		Global::Interval = MyObs->Interval;
	}

	if (Global::DTend == 0.0) Global::DTend = MyObs->Dt2;
	if (Global::DTend != 0.0 && Global::DTend < MyObs->Dt2) MyObs->Dt2 = Global::DTend;
}

void ClassSim::doFunc(long Obs, long Line) {
	// do nothing
}

//---------------------------------------------------------------------------
ClassForce::ClassForce(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes) {
	readargs();

	if (MyObs->FilterCnt > 0)
		error("ForceFilter filter must be the first filter.");

	if (Constants[0] > 288)
		error("ForceFilter filter interval cannot be less than 5 minutes ");

	if (Constants[0] < 1)
		error("ForceFilter filter interval cannot be greater than daily ");

	MyObs->ForceInterval = (long)Constants[0];
}

void ClassForce::doFunc(long Obs, long Line) {
	// do nothing
}

//---------------------------------------------------------------------------
ClassSmear::ClassSmear(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes), Minus(false) {
	readargs();
}

void ClassSmear::doFunc(long Obs, long Line) {

	if (FirstTime) {

		if (Constants[0] < 0.0)
			Minus = true;

		if (Constants[0] <= 0.0)
			Constants[0] = MyObs->Dt1;

		if (Constants[1] <= 0.0) Constants[1] = MyObs->Dt2;

		Constants[0] = MyObs->Dt1 - MyObs->Interval / 2.0;
		Constants[1] = MyObs->Dt2 + MyObs->Interval / 2.0;
		FirstTime = false;
	}

	double now = MyObs->Dt1 + Line * MyObs->Interval;
	double delta = MyObs->Interval / 2.0;


	double now0 = fmod(now, 1.0);

	if (now0 > -delta && now0 < delta) {  // end of day
		float value = Data[0][Obs][Line - MyObs->Freq + 1] / MyObs->Freq;

		if (now > Constants[0] && now < Constants[1] && ((Minus && value < 0.0) || !Minus)) {   //warning resolved by Manishankar.

			if (value < 0.0)
				value = -value;

			for (long ii = 0; ii < MyObs->Freq; ++ii) {
				if (Line - ii < 0) break; // incomplete first day
				Data[Vs - 1][Obs][Line - ii] = value;
			}
		}
		else {
			for (long ii = 0; ii < MyObs->Freq; ++ii) {
				if (Line - ii < 0) break; // incomplete first day
				Data[Vs - 1][Obs][Line - ii] = Data[0][Obs][Line - ii];
			}
		}
	}
}

//---------------------------------------------------------------------------
ClassMissing::ClassMissing(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes), GoodData(NULL) {
	readargs();
	GoodData = new float[ObsCnt];
}

void ClassMissing::doFunc(long Obs, long Line) {
	static bool Warned = false;

	if (FirstTime) {
		if ((Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1]) && !Warned) {
			////Application->MessageBox(MyObs->DataFileName.c_str(), "Missing data in first interval of filter 'missing'", MB_OK);
			LogError("Missing data in first interval of " + MyObs->DataFileName, WARNING);
			Warned = true;
		}

		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
		GoodData[Obs] = Data[0][Obs][Line];
		if (Obs + 1 >= ObsCnt)  FirstTime = false;
		return;
	}

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = GoodData[Obs];
	else {
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
		GoodData[Obs] = Data[0][Obs][Line];
	}
}

ClassMissing::~ClassMissing() {
	delete[] GoodData;
}

//---------------------------------------------------------------------------
ClassMissingInter::ClassMissingInter(ClassData *MyObs, string ToVar, string args, string argtypes) :
	Classfilter(MyObs, ToVar, args, argtypes), GoodData(NULL)
{
	readargs();
	GoodData = new float[ObsCnt];
	LastGoodData = new long[ObsCnt];
}

void ClassMissingInter::doFunc(long Obs, long Line) {
	static bool Warned = false;

	if (FirstTime) {
		if ((Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1]) && !Warned) {
			////Application->MessageBox(MyObs->DataFileName.c_str(), "Missing data in first interval of filter 'missinginter'", MB_OK);
			LogError("Missing data in first interval of " + MyObs->DataFileName, WARNING);
			Warned = true;
			LastGoodData[Obs] = -1;
			return;
		}

		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
		GoodData[Obs] = Data[0][Obs][Line];
		LastGoodData[Obs] = Line;

		if (Obs + 1 >= ObsCnt)  FirstTime = false;
		return;
	}

	if (Data[0][Obs][Line] > Constants[0] && Data[0][Obs][Line] < Constants[1]) {
		if (Line - 1 > LastGoodData[Obs] && LastGoodData[Obs] != -1) {
			float dif = (Data[0][Obs][Line] - GoodData[Obs]) / (Line - LastGoodData[Obs]);
			for (int ii = LastGoodData[Obs] + 1; ii < Line; ++ii)
				Data[Vs - 1][Obs][ii] = Data[Vs - 1][Obs][ii - 1] + dif;
		}

		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];

		GoodData[Obs] = Data[0][Obs][Line];
		LastGoodData[Obs] = Line;
	}
}

ClassMissingInter::~ClassMissingInter() {
	delete[] GoodData;
	delete[] LastGoodData;
}

//---------------------------------------------------------------------------
void ClassMissing0::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = 0.0;
	else
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
}

//---------------------------------------------------------------------------
void ClassMissingC::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = (float)Constants[2];
	else
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
}

//---------------------------------------------------------------------------
void ClassMissingFlagAfter::doFunc(long Obs, long Line) {

	if (FirstTime) {
		First = Line;
		FirstTime = false;
	}
	else
		Last = Line;
}

//---------------------------------------------------------------------------
void ClassMissingFlag::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = 1.0;
	else
		Data[Vs - 1][Obs][Line] = 0.0;
}

//---------------------------------------------------------------------------
ClassMissingFlagAfter::~ClassMissingFlagAfter() {

	for (int Obs = 0; Obs < ObsCnt; ++Obs)
		for (int Line = First; Line <= Last; ++Line) {
			if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
				Data[Vs - 1][Obs][Line] = 1.0;
			else
				Data[Vs - 1][Obs][Line] = 0.0;
		}
}

//---------------------------------------------------------------------------
void ClassMissingrepl::doFunc(long Obs, long Line) {

	if (Data[0][Obs][Line] <= Constants[0] || Data[0][Obs][Line] >= Constants[1])
		Data[Vs - 1][Obs][Line] = Data[1][Obs][Line];
	else
		Data[Vs - 1][Obs][Line] = Data[0][Obs][Line];
}

//---------------------------------------------------------------------------
void   Update_Main_DIM(CRHM::TDim Dim, long dim) {
	//SendMessage(Global::crhmMain, WM_CRHM_Main_DIM, (unsigned int)Dim, (unsigned int)dim);
}

//---------------------------------------------------------------------------
void   Update_Main_Dirty(void) {
	//SendMessage(Global::crhmMain, WM_CRHM_Main_DIRTY, (unsigned int)0, (unsigned int)0);
}

//---------------------------------------------------------------------------

long getdim(CRHM::TDim dimen) {
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
		return (Global::nhru);

	case CRHM::NOBS:
		return (Global::nobs);

	case CRHM::NLAY:
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
void setdim(CRHM::TDim dimen, long dim) {
	MapDim::iterator itDim;
	string s;

	switch (dimen) {

	case CRHM::NHRU: s = "nhru";
		Update_Main_DIM(CRHM::NHRU, dim);
		break;

	case CRHM::NOBS: s = "nobs";
		Update_Main_DIM(CRHM::NOBS, dim);
		break;

	case CRHM::NLAY: s = "nlay";
		Update_Main_DIM(CRHM::NLAY, dim);
		break;

	default:

		return;
	}
}

//---------------------------------------------------------------------------
void   LogError(CRHMException Except) {
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_EXCEPTION, (unsigned int)&Except, 0);
	if (Except.Kind == TERMINATE)
		throw (Except);
}

//---------------------------------------------------------------------------
void   LogError(string S, TExcept Kind) {
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_EXCEPTION1, (unsigned int)&S, (unsigned int)&Kind);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, float V, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V, "ffFixed", 10, 4) + " " + S2;

	LogMessage(SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, float V, TExtra Opt) {

	string D, SS;
	switch (Opt) {
	case BLANK:
		break;
	case DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	if (Opt == BLANK)
		SS = S + FloatToStrF(V, "ffFixed", 10, 4);
	else
		SS = D + S + FloatToStrF(V, "ffFixed", 10, 4);

	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, long V, TExtra Opt) {

	string D, SS;
	switch (Opt) {
	case BLANK:
		break;
	case DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	if (Opt == BLANK)
		SS = S + to_string(V);
	else
		SS = D + S + to_string(V);

	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(const char *S, TExtra Opt) {

	string D, SS;
	switch (Opt) {
	case BLANK:
		break;
	case DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	if (Opt == BLANK)
		SS = S;
	else
		SS = D + S;

	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, float V, TExtra Opt) {

	string A = string("HRU " + to_string(hh + 1) + ": ");
	string D;
	switch (Opt) {
	case BLANK:
		break;
	case DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	string SS = A + D + S + FloatToStrF(V, "ffFixed", 10, 4);
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, long V, TExtra Opt) {

	string A = string("HRU " + to_string(hh + 1) + ": ");
	string D;
	switch (Opt) {
	case BLANK:
		break;
	case DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	string SS = A + D + S + to_string(V);
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, TExtra Opt) {

	string A = string("HRU " + to_string(hh + 1) + ": ");
	string D;
	switch (Opt) {
	case BLANK:
		break;
	case DD:
		D = FormatString(Global::DTnow, "yy mm dd ");
		break;
	case DT:
		D = FormatString(Global::DTnow, "yy mm dd hh nn ");
		break;
	case TT:
		D = FormatString(Global::DTnow, "hh nn ");
	default:
		break;
	}

	string SS = A + D + S;
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebug(char *S) {

	string SS = S;
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebug(long h, char *Text, float v) {

	string S = to_string(h) + to_string(1);
	S += Text + to_string(v);

	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&S, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebugD(char *S) {

	string D = FormatString(Global::DTnow, "yy mm dd ");

	string SS = D + S;
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogDebugT(string S) {

	string D = FormatString(Global::DTnow, "yy mm dd hh nn ");

	string SS = "yy mm dd hh mm - ";
	SS += D + " - " + S;
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   Update_Main_Status(string S) {

	//SendMessage(Global::crhmMain, WM_CRHM_Main_STATUS, (unsigned int)&S, (unsigned int)0);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, float V1, float V2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 4) + ' ' + FloatToStrF(V2, "ffFixed", 10, 4);
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessage(long hh, const char *S, float V1, float V2, float V3, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 4) + " " + FloatToStrF(V2, "ffFixed", 10, 4) + " " + FloatToStrF(V3, "ffFixed", 10, 4);
	LogMessage(hh, SS.c_str(), Opt);
}
//---------------------------------------------------------------------------

void   LogMessageA(long hh, const char *S, float V1, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2);
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessageA(long hh, const char *S, float V1, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " + S2;
	LogMessage(hh, SS.c_str(), Opt);
}

void   LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area / Basin_area, "ffFixed", 10, 3);
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessageA(long hh, const char *S, float V1, const float HRU_area, const float Basin_area, const char *S2, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1*HRU_area / Basin_area, "ffFixed", 10, 3) + " " + S2;
	LogMessage(hh, SS.c_str(), Opt);
}

//---------------------------------------------------------------------------
void   LogMessageA(long hh, const char *S, float V1, const float Basin_area, TExtra Opt) {

	string SS = S + FloatToStrF(V1, "ffFixed", 10, 2) + " " +
		FloatToStrF(V1 / Basin_area, "ffFixed", 10, 3);
	LogMessage(hh, SS.c_str(), Opt);
}
//---------------------------------------------------------------------------

void   LogMessageA(long hh, const char *S, float V1, const float Basin_area, const char *S2, TExtra Opt) {

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

long ClassVar::GetUnit(void) {
	return GetSharedUnit(units);
}
//---------------------------------------------------------------------------

long ClassPar::GetUnit(void) {
	return GetSharedUnit(units);
}
//---------------------------------------------------------------------------

Convert::Convert() {
	NumUnits = 0;
	NumBasicUnits = 0;
	NumMultipliers = 0;

	while (!(Infos[NumUnits].Abbr).empty()) {
		if ((Infos[NumUnits].Expr).empty()) {
			Infos[NumUnits].k = NumBasicUnits;
			++NumBasicUnits;
		}

		++NumUnits;
	}

	while (Multipliers[NumMultipliers].Abbr) {
		++NumMultipliers;
	}
}

Unit_Info Convert::Infos[] = {
	Unit_Info("1", "1", 1, "") ,
	Unit_Info("A", "Ampere" , 1, "") ,
	Unit_Info("Bq", "becquerel", 1, "l/s") ,
	Unit_Info("Btu", "InternationalTableBtu", 1055.05585262, "Kg*m^2/s^2") ,
	Unit_Info("C", "Coulomb", 1, "A*s") ,
	Unit_Info("Ci", "Curie", 3.7 * 1010, "l/s") ,
	Unit_Info("F", "Farad", 1, "A^2*s^4/Kg*m^2") ,
	Unit_Info("Fdy", "Faraday", 96487, "A*s") ,
	Unit_Info("Gy", "Gray", 1, "m^2/s^2") ,
	Unit_Info("H", "Henry", 1, "Kg*m^2/A^2*s^2") ,
	Unit_Info("Hz", "Hertz", 1, "s^-1") ,
	Unit_Info("J", "Joule", 1, "Kg*m^2/s^2") ,
	Unit_Info("K", "Kelvin" , 1, ""),
	Unit_Info("Knot", "NauticalMilesPerHour", 463.0 / 900.0, "m/s") ,
	Unit_Info("N", "Newton", 1, "Kg*m/s^2") ,
	Unit_Info("Ohm", "Ohm", 1, "Kg*m^2/A^2*s^3") ,
	Unit_Info("OzUK", "UKFluidOunce", 2.8413075e-5, "m^3") ,
	Unit_Info("P", "Poise", 0.1, "Kg/m*s") ,
	Unit_Info("Pa", "Pascal", 1, "Kg/m*s") ,
	Unit_Info("Pdl", "Poundal", 0.13825495376, "Kg*m/s^2") ,
	Unit_Info("Pica", "Pica", 1.0 / 72.0, "in") ,
	Unit_Info("R", "Roentgen", 0.000258, "A*s/Kg") ,
	Unit_Info("S", "Siemens", 1, "A^2*s^3/Kg*m^2") ,
	Unit_Info("St", "Stokes", 0.0001, "m^2/s") ,
	Unit_Info("Sv", "Sievert", 1, "m^2/s^2") ,
	Unit_Info("T", "Tesla", 1, "Kg/A*s^2") ,
	Unit_Info("U", "UnifiedAtomicMass", 1.6605402e-27, "Kg") ,
	Unit_Info("V", "Volt", 1, "Kg*m^2/A*s^2") ,
	Unit_Info("W", "Watt", 1, "Kg*m^2/s^3") ,
	Unit_Info("Wb", "Weber", 1, "Kg*m^2/A*s^2") ,
	Unit_Info("acre", "Acre", 4046.87260987, "m^2") ,
	Unit_Info("arcmin", "ArcMinute", 2.9088820866e-4, "r") ,
	Unit_Info("arcs", "ArcSecond", 4.848136111e-6, "r") ,
	Unit_Info("atm", "Attmosphere", 101325, "Kg/m*s^2") ,
	Unit_Info("au", "AstronomicalUnit", 1.495979 * 1011, "m") ,
	Unit_Info("b", "Barn", 1e-28, "m^2") ,
	Unit_Info("bar", "Bar", 100000, "Kg/m*s^2") ,
	Unit_Info("bbl", "Barrel", 0.158987294928, "m^3") ,
	Unit_Info("bu", "Bushel", 0.03523907, "m^3") ,
	Unit_Info("c", "LightSpeed", 299792458, "m/s") ,
	Unit_Info("cal", "Calorie", 4.1868, "Kg*m^2/s^2") ,
	Unit_Info("cd", "Candela" , 1, "") ,
	Unit_Info("chain", "Chain", 20.1168402337, "m") ,
	Unit_Info("ct", "Carat", 0.0002, "Kg") ,
	Unit_Info("cu", "USCup", 2.365882365e-4, "m^3") ,
	Unit_Info("d", "day", 86400, "s") ,
	Unit_Info("dyn", "Dyne", 0.00001, "Kg*m/s^2") ,
	Unit_Info("eV", "ElectronVolt", 1.60217733e-19, "Kg*m^2/s^2") ,
	Unit_Info("erg", "Erg", 0.0000001, "Kg*m^2/s^2") ,
	Unit_Info("fath", "Fathom", 1.82880365761, "m") ,
	Unit_Info("fbm", "BoardFoot", 0.002359737216, "m^3") ,
	Unit_Info("fc", "Footcandle", 10.7639104167, "cd*sr/m^2") ,
	Unit_Info("fermi", "Fermi", 1e-15, "m") ,
	Unit_Info("flam", "Footlambert", 3.42625909964, "cd/m^2") ,
	Unit_Info("ft", "InternationalFoot", 0.3048, "m") ,
	Unit_Info("ftUS", "SurveyFoot", 0.304800609601, "m") ,
	Unit_Info("g", "Gram" , 1, "") ,
	Unit_Info("ga", "StandardFreefall", 9.80665, "m/s^2") ,
	Unit_Info("gal", "USGallon", 0.003785411784, "m^3") ,
	Unit_Info("galC", "CanadianGallon", 0.00454609, "m^3") ,
	Unit_Info("galUK", "UKGallon", 0.004546092, "m^3") ,
	Unit_Info("gf", "GramForce", 0.00980665, "Kg*m/s^2") ,
	Unit_Info("grad", "Grade", 1.57079632679e-2, "r") ,
	Unit_Info("grain", "Grain", 0.00006479891, "Kg") ,
	Unit_Info("h", "Hour", 3600, "s") ,
	Unit_Info("ha", "Hectare", 10000, "m^2") ,
	Unit_Info("hp", "horsepower", 745.699871582, "Kg*m^2/s^2") ,
	Unit_Info("in", "Inch", 0.0254, "m") ,
	Unit_Info("inH2O", "InchesOfWater", 248.84, "Kg/m*s^2") ,
	Unit_Info("inHg", "InchesOfMercury", 3386.38815789, "Kg/m*s^2") ,
	Unit_Info("int", "CRHM time step", 3600, "s") ,
	Unit_Info("kip", "KilopoundForce", 4448.22161526, "Kg*m/s^2") ,
	Unit_Info("kph", "KilometersPerHour", 5.0 / 18.0, "m/s") ,
	Unit_Info("l", "Liter", 0.001, "m^3") ,
	Unit_Info("lam", "Lambert", 3183.09886184, "cd/m^2") ,
	Unit_Info("lb", "AvoirdupoisPound", 0.45359267, "Kg") ,
	Unit_Info("lbf", "PoundForce", 4.44822161526, "Kg*m/s^2") ,
	Unit_Info("lbt", "TroyPound", 0.3732417216, "Kg") ,
	Unit_Info("lm", "Lumen", 1, "cd*sr") ,
	Unit_Info("lx", "Lux", 1, "cd*sr/m^2") ,
	Unit_Info("lyr", "LightYear", 9.46052840488 * 1015, "m") ,
	Unit_Info("m", "Meter" , 1, "") ,
	Unit_Info("mho", "Mho", 1, "A^2*s^2/Kg*m^2") ,
	Unit_Info("mi", "InternationalMile", 1609.344, "m") ,
	Unit_Info("miUS", "USStatuteMile", 1609.34721869, "m") ,
	Unit_Info("mil", "Mil", 0.0000254, "m") ,
	Unit_Info("min", "Minute", 60, "s") ,
	Unit_Info("mmHg", "MilimeterOfMercury", 133.322368421, "Kg/m*s^2") ,
	Unit_Info("mol", "Mole" , 1, "") ,
	Unit_Info("mph", "MilesPerHour", 0.44704, "m/s") ,
	Unit_Info("nmi", "NauticalMile", 1852, "m") ,
	Unit_Info("oz", "Ounce", 0.028349523125, "Kg") ,
	Unit_Info("ozfl", "USFluidOunce", 2.95735295625e-5, "m^3") ,
	Unit_Info("ozt", "TroyOunce", 0.0311034768, "Kg") ,
	Unit_Info("pc", "Parsec", 3.08567818585106, "m") ,
	Unit_Info("ph", "Phot", 10000, "cd*sr/m^2") ,
	Unit_Info("pk", "Peck", 0.0088097675, "m^3") ,
	Unit_Info("psi", "PoundsPerSquareInch", 6894.75729317, "Kg/m*s^2") ,
	Unit_Info("pt", "Pint", 0.000473176473, "m^3") ,
	Unit_Info("qt", "Quart", 0.000946352946, "m^3") ,
	Unit_Info("r", "Radian" , 1, "") ,
	Unit_Info("rad", "Rad", 0.01, "m^2/s^2") ,
	Unit_Info("rd", "Rod", 5.02921005842, "m") ,
	Unit_Info("rem", "Rem", 0.01, "m^2/s^2") ,
	Unit_Info("s", "Second" , 1, "") ,
	Unit_Info("sb", "Stilb", 10000, "cd/m^2") ,
	Unit_Info("slug", "Slug", 14.5939029372, "Kg") ,
	Unit_Info("sr", "Steradian" , 1, "") ,
	Unit_Info("st", "Stere", 1, "m^3") ,
	Unit_Info("t", "MetricTon", 1000, "Kg") ,
	Unit_Info("tbsp", "Tablespoon", 1.47867647813e-5, "m^3") ,
	Unit_Info("therm", "EECTherm", 105506000, "Kg*m^2/s^2") ,
	Unit_Info("ton", "ShortTon", 907.18474, "Kg") ,
	Unit_Info("tonUK", "UKLongTon", 1016.0469088, "Kg") ,
	Unit_Info("torr", "Torr", 133.322368421, "Kg/m^2") ,
	Unit_Info("tsp", "Teaspoon", 4.92892159375e-6, "m^3") ,
	Unit_Info("yd", "InternationalYard", 0.9144, "m") ,
	Unit_Info("yr", "Year", 31556925.9747, "s") ,
	//Unit_Info("\B0", "Degree", 1.74532925199e-2, "r") ,
	//Unit_Info("\B0C", "DegreeCelsius", 1.0, "K"),
	//Unit_Info("\B0F", "DegreesFahrenheit", 1.0 / 1.8, "K"),
	//Unit_Info("\B0R", "DegreesRankine", 1.0 / 1.8, "K"),
	//Unit_Info("\B5", "Micron", 1e-6, "m"),
	//Unit_Info("\C5", "Angstrom", 1e-10, "m"),
	Unit_Info("\0xB", "Degree", 1.74532925199e-2, "r"),
	Unit_Info("\0xB0C", "DegreeCelsius", 1.0, "K") ,
	Unit_Info("\0xB0F", "DegreesFahrenheit", 1.0 / 1.8, "K") ,
	Unit_Info("\0xB0R", "DegreesRankine", 1.0 / 1.8, "K") ,
	Unit_Info("\0xB5", "Micron", 1e-6, "m") ,
	Unit_Info("\0xC5", "Angstrom", 1e-10, "m") ,
	Unit_Info("", "", 0, "") };


Multiplier_Info Convert::Multipliers[] = {
	Multiplier_Info('Y',	"Yotta",   1e+24) ,
	Multiplier_Info('Z',	"Zetta",   1e+21) ,
	Multiplier_Info('E',	"Exa",     1e+18) ,
	Multiplier_Info('P',	"Peta",    1e+15) ,
	Multiplier_Info('T',	"Tera",    1e+12) ,
	Multiplier_Info('G',	"Giga",    1e+9) ,
	Multiplier_Info('M',	"Mega",    1e+6) ,
	Multiplier_Info('k',        "kilo",    1e+3) ,
	Multiplier_Info('K',        "Kilo",    1e+3) ,
	Multiplier_Info('h',        "hecto",   1e+2) ,
	Multiplier_Info('H',        "Hecto",   1e+2) ,
	Multiplier_Info('D',	"Deka",    1e+1) ,
	Multiplier_Info('d',	"deci",    1e-1) ,
	Multiplier_Info('c',	"cent",    1e-2) ,
	Multiplier_Info('m',	"mili",    1e-3) ,
	Multiplier_Info('u',	"micro",   1e-6) ,
	//Multiplier_Info('\B5',        "micro",   1e-6) ,
	Multiplier_Info('n',	"nano",    1e-9) ,
	Multiplier_Info('p',	"pico",    1e-12) ,
	Multiplier_Info('f',	"femto",   1e-15) ,
	Multiplier_Info('a',	"atto",    1e-18) ,
	Multiplier_Info('z',	"zepto",   1e-21) ,
	Multiplier_Info('y',	"yocto",   1e-24) ,
	Multiplier_Info('\0',	"",          0.0) };

string tcsinc(string pszIn) {

	return pszIn.substr(1);
}

string tcsSkipSpaces(string pszIn) {
	while (pszIn[0] == ' ')
		pszIn = pszIn.substr(1);
	return pszIn;
}

string tcsSqueeze(string pszIn) {
	string::iterator pos;

	string::size_type Idx;
	//  char const Misc[] = {"( )%\BA\B0\t"};
	//char const Misc[] = { "( )%\BA\t" };
	char const Misc[] = { "( )%\0xBA\t" };

	Idx = pszIn.find_first_of(Misc);
	while (Idx != string::npos) {
		pszIn = pszIn.erase(Idx, 1);
		Idx = pszIn.find_first_of(Misc);
	}

	return pszIn;
}

// Main Functions

// Converts the <dValue> from the <pszSrcUnit> to the <pszDstUnit>

bool Convert::ConvertUnit(
	double& dValue,     // [in] value to convert, [out] converted value
	string pszSrcUnit,  // [in] source unit
	string pszDstUnit   // [in] destination unit
) {

	pszSrcUnit = tcsSkipSpaces(pszSrcUnit);
	pszDstUnit = tcsSkipSpaces(pszDstUnit);

	dValue = 1.0;

	if (pszSrcUnit.compare(pszDstUnit) == 0)
		return true;

	Tresult uSrcUnit(NumBasicUnits);
	try {
		pszSrcUnit = ParseDivUnitExpr(pszSrcUnit, uSrcUnit);
	}
	catch (int i) {
		return false;
	}

	Tresult uDstUnit(NumBasicUnits);
	try {
		pszDstUnit = ParseDivUnitExpr(pszDstUnit, uDstUnit);
	}
	catch (int i) {
		return false;
	}

	for (int i = 0; i < NumBasicUnits; ++i)
		if (uSrcUnit.aExp[i] != uDstUnit.aExp[i]) {
			dValue = -999;
			return false;
		}

	dValue *= uSrcUnit.k;
	dValue /= uDstUnit.k;

	return true;
}

double Convert::quickPow(double k, int nPow)
{
	bool bNegative = (nPow < 0);
	if (bNegative)
		nPow = -nPow;

	double r = 1.0;

	while (nPow != 0)
	{
		if (nPow & 1)
			r *= k;

		k *= k;
		nPow >>= 1;
	}

	if (bNegative)
		r = 1.0 / r;

	return r;
}

int Convert::LookupUnit(string pszIn)
{
	int iFirst = 0;
	int iLast = NumUnits;
	int i;

	string::size_type Idx;

	Idx = pszIn.find_first_of("*/^");
	if (Idx == string::npos)
		Idx = pszIn.size();

	while (iLast >= iFirst)
	{
		i = (iLast + iFirst) / 2;

		int nCmp = pszIn.compare(0, Idx, Infos[i].Abbr);

		if (nCmp == 0)
			return i;  // match

		if (nCmp < 0)
			iLast = i - 1;
		else
			iFirst = i + 1;
	}

	return -1;  // no match
}

void Convert::DivUnit(Tresult& u1, const Tresult& u2)
{
	u1.k /= u2.k;

	for (int i = 0; i < NumBasicUnits; ++i)
		u1.aExp[i] -= u2.aExp[i];
};

void Convert::MulUnit(Tresult& u1, const Tresult& u2)
{
	u1.k *= u2.k;

	for (int i = 0; i < NumBasicUnits; ++i)
		u1.aExp[i] += u2.aExp[i];
};

void Convert::MulUnitK(Tresult& u, double k)
{
	u.k *= k;
};

void Convert::PowUnit(Tresult& u, char nPow)
{
	for (int i = 0; i < NumBasicUnits; ++i)
		u.aExp[i] *= nPow;

	u.k = quickPow(u.k, nPow);
};

void Convert::SetBasicUnit(Tresult& u, double k, int iUnit)
{
	u.k = k;

	int iBasicUnit = (int)(Infos[iUnit].k);
	if (0 <= iBasicUnit)
		u.aExp[iBasicUnit] = 1;
}

void Convert::ExpandUnitExpr(Tresult& u, double k, string pszExpr)
{
	pszExpr = ParseDivUnitExpr(pszExpr, u);

	u.k *= k;
}

// Unit interpretation: template declarations

string Convert::ParseDivUnitExpr(string pszIn, Tresult& u)
{
	pszIn = ParseMulUnitExpr(pszIn, u);

	if (pszIn.empty())
		return pszIn;

	string pszMark = pszIn;
	pszIn = tcsSkipSpaces(pszIn);
	if (pszIn[0] != '/')
		throw 3;

	pszIn = tcsinc(pszIn);
	pszIn = tcsSkipSpaces(pszIn);

	Tresult uAux(NumBasicUnits);
	pszIn = ParseMulUnitExpr(pszIn, uAux);

	DivUnit(u, uAux);

	pszMark = pszIn;
	return pszMark;
}

string Convert::ParseMulUnitExpr(string pszIn, Tresult& u)
{
	pszIn = ParsePowUnitExpr(pszIn, u);

	if (pszIn.empty())
		return pszIn;

	string pszMark = pszIn;

	while (pszIn = tcsSkipSpaces(pszIn), pszIn[0] == '*')
	{
		pszIn = tcsinc(pszIn);

		Tresult uAux(NumBasicUnits);
		pszIn = ParsePowUnitExpr(pszIn, uAux);
		if (pszIn == "error")
			return pszMark;

		MulUnit(u, uAux);

		pszMark = pszIn;
	}

	return pszIn;
}

string Convert::ParsePowUnitExpr(string pszIn, Tresult& u)
{
	pszIn = ParseUnitPhase1(pszIn, u);

	if (pszIn.empty())
		return pszIn;

	string pszMark = pszIn;

	pszIn = tcsSkipSpaces(pszIn);
	if (pszIn[0] != '^')
		return pszMark;

	pszIn = tcsinc(pszIn);
	pszIn = tcsSkipSpaces(pszIn);

	bool bNegative = (pszIn[0] == '-');

	if (pszIn[0] == '+' || pszIn[0] == '-')
		pszIn = tcsinc(pszIn);

	//if (!_istdigit(pszIn[0]))
	if (isdigit(pszIn[0]))
		return pszMark;

	char nPow = 0;

	//while (_istdigit(pszIn[0]))
	while (isdigit(pszIn[0]))
	{
		char nPow2 = nPow * 10 + (pszIn[0] - '0');
		if (nPow2 < nPow)
			break;

		nPow = nPow2;
		pszIn = tcsinc(pszIn);
	}

	if (bNegative)
		nPow = -nPow;

	PowUnit(u, nPow);

	return pszIn;
}

string Convert::ParseUnitPhase1(string pszIn, Tresult& u)
{
	string pszMark = pszIn;

	pszIn = ParseUnitPhase2(pszIn, u);
	if (pszIn != "????")
		return pszIn;

	pszIn = pszMark;

	double k;
	int ii;

	for (ii = 0; ii < NumMultipliers; ++ii)
		if (pszIn[0] == Multipliers[ii].Abbr) {
			k = Multipliers[ii].k;
			break;
		}

	if (ii >= NumMultipliers) {

		bool bNegative = (pszIn[0] == '-');

		if (pszIn[0] == '+' || pszIn[0] == '-')
			pszIn = tcsinc(pszIn);

		//if (!_istdigit(pszIn[0]))
		if (!isdigit(pszIn[0]))

			throw 1; // cause fault
		else {

			k = 0;

			//while (_istdigit(pszIn[0]))
			while (isdigit(pszIn[0]))
			{
				char nPow2 = k * 10 + (pszIn[0] - '0');
				if (nPow2 < k)
					break;

				k = nPow2;
				pszIn = tcsinc(pszIn);
			}

			if (bNegative)
				k = -k;

			if (pszIn[0] == '*') // allow '*'
				pszIn = tcsinc(pszIn);
		}
	}
	else
		pszIn = tcsinc(pszIn);

	pszIn = ParseUnitPhase2(pszIn, u);

	MulUnitK(u, k);

	return pszIn;
}

string Convert::ParseUnitPhase2(string pszIn, Tresult& u)
{
	int iUnit = LookupUnit(pszIn);

	if (iUnit < 0)
		return "????";

	if (Infos[iUnit].Expr.empty())
		SetBasicUnit(u, 1.0, iUnit);
	else
		ExpandUnitExpr(u, Infos[iUnit].k, Infos[iUnit].Expr);

	pszIn = pszIn.substr(Infos[iUnit].Abbr.size());

	return pszIn;
}

bool Convert::CheckUnitsTable()
{
	bool bSuccess = true;

	for (int i = 0; i < NumUnits - 1; ++i)
	{
		const Unit_Info info1 = Infos[i];
		const Unit_Info info2 = Infos[i + 1];

		if (info1.Abbr.compare(info2.Abbr) >= 0)
		{
			bSuccess = false;
		}
	}
	return bSuccess;
}

void Convert::CheckUnitsString(string Name, string variable, string units)
{
	//string::size_type Idx;
	string temp(units);

	units = tcsSqueeze(units);

	if (units.empty()) return;

	Tresult uSrcUnit(NumBasicUnits);

	try {
		units = ParseDivUnitExpr(units, uSrcUnit);
		if (!units.empty()) {
			units = temp;
			throw 2;
		}
	}
	catch (int i) {
		CRHMException Except("Units error: '" + units + "' in " + Name + ' ' + variable, WARNING);
		LogError(Except);
	}
}

void Convert::CheckUnitsObs(string Vunits, string Munits, string declaration) { // check original observation units
	//string::size_type Idx;
	double d;

	if (!Vunits.empty()) {
		if (!ConvertUnit(d, tcsSqueeze(Vunits), tcsSqueeze(Munits)) || d != 1.0) {
			CRHMException Except("Units error: '" + Vunits + " instead of " + Munits + "' in " + declaration, WARNING);
			LogError(Except);
		}
	}
}

//---------------------------------------------------------------------------
long julian_month(long Year, long julian) {
	int Y, Month, Day, H, Min;
	double DT = StandardConverterUtility::EncodeDateTime((Word)Year - 1, (Word)12, (Word)31, 0, 0);

	DT += (double)julian;
	StandardConverterUtility::DecodeDateTime(DT, &Y, &Month, &Day, &H, &Min);
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

//---------------------------------------------------------------------------
ClassData::ClassData(const ClassData & Cl) { //

	DataFileName = Cl.DataFileName;
	Description = Cl.Description;
	Dt1 = Cl.Dt1;
	Dt2 = Cl.Dt2;
	Interval = Cl.Interval;
	Lines = Cl.Lines;
	Freq = Cl.Freq;
	IndxMin = Cl.IndxMin;
	IndxMax = Cl.IndxMax;
	ModN = Cl.ModN;
	HdrLen = Cl.HdrLen;
	Position = Cl.Position;
	DataCnt = Cl.DataCnt;
	FilterCnt = Cl.FilterCnt;

	myMacro = Cl.myMacro;

	Simulation = Cl.Simulation;
	ForceInterval = Cl.ForceInterval;
	GoodInterval = Cl.GoodInterval;
	GoodDay = Cl.GoodDay;
	RunUsed = Cl.RunUsed;
	Success = Cl.Success;
	TimeIndx = Cl.TimeIndx;
	FirstFile = Cl.FirstFile;

	Data = new float*[DataCnt + FilterCnt];   // Data [Cnt] [Lines]

	for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
		Data[jj] = new float[Lines];

	//for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)  //warning resolved by Manishankar
	//	for (int kk = 0; kk < Lines; ++kk)
	//		Data[jj][kk];

	if (Cl.Times) {
		Times = new double[Lines];
		for (long ii = 0; ii < Lines; ++ii)
			Times[ii] = Cl.Times[ii];
	}
	else
		Times = NULL;
}

//---------------------------------------------------------------------------
ClassData & ClassData::operator=(const ClassData & Cl) { //

	if (this == &Cl) return *this;
	DataFileName = Cl.DataFileName;
	Description = Cl.Description;
	Dt1 = Cl.Dt1;
	Dt2 = Cl.Dt2;
	Interval = Cl.Interval;
	Lines = Cl.Lines;
	Freq = Cl.Freq;
	IndxMin = Cl.IndxMin;
	IndxMax = Cl.IndxMax;
	ModN = Cl.ModN;
	HdrLen = Cl.HdrLen;
	Position = Cl.Position;
	DataCnt = Cl.DataCnt;
	FilterCnt = Cl.FilterCnt;

	myMacro = Cl.myMacro;

	Simulation = Cl.Simulation;
	ForceInterval = Cl.ForceInterval;
	GoodInterval = Cl.GoodInterval;
	GoodDay = Cl.GoodDay;
	RunUsed = Cl.RunUsed;
	Success = Cl.Success;
	TimeIndx = Cl.TimeIndx;
	FirstFile = Cl.FirstFile;

	Data = new float*[DataCnt + FilterCnt];   // Data [Cnt] [Lines]

	for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)
		Data[jj] = new float[Lines];

	//for (int jj = 0; jj < DataCnt + FilterCnt; ++jj)  //warning resolved by Manishankar
	//	for (int kk = 0; kk < Lines; ++kk)
	//		Data[jj][kk];

	if (Cl.Times) {
		Times = new double[Lines];
		for (long ii = 0; ii < Lines; ++ii)
			Times[ii] = Cl.Times[ii];
	}
	else
		Times = NULL;

	return *this;
}

void   LogDebug(const char* S) {

	string SS = S;
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}
void   LogDebug(const string S) {

	string SS = S;
	//SendMessage(Global::crhmLog, WM_CRHM_LOG_DEBUG, (unsigned int)&SS, (unsigned int)0);
}
