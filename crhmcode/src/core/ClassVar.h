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
#pragma once

#ifndef CLASSVAR
#define CLASSVAR

#include "ClassCRHM.h"

using namespace std;

class ClassModule;

class ClassVar {

	typedef void (ClassVar::* TSomeFunct) (void);
	typedef void (ClassVar::* TSomeFunct_) (long dim_n);
	typedef void (ClassVar::* TLoopFunct) (long dim_n);
	typedef void (ClassVar::* TAccFunct) (ClassModule*);

public:

	string module;
	string root;
	string name;
	string help;
	string units;
	string DLLName; // use to differentiate DLLs and Macros from normal modules, i.e. CRHM

	TVar varType;

	long dim;
	long dimMax; // used by observations
	long lay;
	long variation_set{ 0 };
	TDim dimen{ TDim::NREB };

	TVISIBLE visibility;
	bool optional;
	bool PointPlot;
	long TchrtOpt;
	long VarFunct{ 0 };
	bool StatVar;
	long InGroup;
	bool nfreq;
	TFun FunKind;
	bool Daily{ false }; // used by AddObsPlot to decide how to apply function to input obs/var

	double* values;
	long* ivalues;

	double** layvalues;
	long** ilayvalues;

	// backup storage

	double** layvaluesBkup{ NULL };
	long** ilayvaluesBkup{ NULL };

	long offset; // observation offset in ClassData FileData/Data
	long cnt;    // observation dimension

	ClassData* FileData;

	long HRU_OBS_indexed; // used to access the HRU_OBS[HRU_OBS_indexed][HRU] table
	ClassVar* FunctVar;
	TLoopFunct LoopFunct{ NULL };  // typedef void (ClassVar:: *SomeFunct) (long dim_n) used in ClassCRHM
	TSomeFunct UserFunct{ NULL };  // typedef void (ClassVar:: *SomeFunct) (void) used in ClassModule
	TSomeFunct_ UserFunct_{ NULL };  // typedef void (ClassVar:: *SomeFunct) (long dim_n) used in ClassCRHM
	TAccFunct CustomFunct; // typedef void (ClassVar:: *AccFunct) (ClassModule *) used in ClassModule
	string CustomFunctName; // debug aid
	long No_ReadVar; // do not read observation again in a group but use CustomFunct

	ClassVar(string module = "none", string name = "none"): 
		module(module), 
		name(name), 
		help(""), 
		DLLName(""), 
		root(""), 
		varType(TVar::none), 
		dim(0), 
		dimMax(0), 
		lay(0), 
		variation_set(0), 
		nfreq(false),
		optional(false), 
		StatVar(false), 
		InGroup(0), 
		visibility(TVISIBLE::USUAL), 
		FunKind(TFun::FOBS), 
		VarFunct(0),
		values(NULL), 
		ivalues(NULL), 
		layvalues(NULL), 
		ilayvalues(NULL), 
		Daily(false),
		offset(0), 
		cnt(0), 
		FileData(NULL), 
		HRU_OBS_indexed(0), 
		UserFunct(NULL), 
		FunctVar(NULL), 
		CustomFunct(NULL), 
		No_ReadVar(0), 
		PointPlot(false), 
		TchrtOpt(0) 
	{};

	ClassVar(
		string module, 
		string name, 
		TDim dimen, 
		string help, 
		string units, 
		TVar varType, 
		bool PointPlot = false,
		int Grpdim = 0, 
		int defdim = 0
	);

	ClassVar(
		string module,
		string name, 
		long dim,
		string help, 
		string units, 
		TVar varType, 
		bool PointPlot = false
	);

	ClassVar(string module, string name, long cnt, long offset, ClassData* FileData) : 
		module(module), 
		name(name), 
		help(""), 
		DLLName(""), 
		root(""), 
		varType(TVar::Read), 
		dim(cnt), 
		dimMax(0), 
		lay(0), 
		variation_set(0), 
		nfreq(false),
		optional(false), 
		StatVar(false), 
		InGroup(0), 
		visibility(TVISIBLE::USUAL), 
		FunKind(TFun::FOBS), 
		VarFunct(0),
		offset(offset), 
		cnt(cnt), 
		FileData(FileData), 
		HRU_OBS_indexed(0), 
		UserFunct(NULL), 
		FunctVar(NULL), 
		CustomFunct(NULL), 
		No_ReadVar(0), 
		dimen(TDim::NOBS),
		values(NULL), 
		ivalues(NULL), 
		layvalues(NULL), 
		ilayvalues(NULL), 
		Daily(false), 
		PointPlot(false), 
		TchrtOpt(0) 
	{};

	virtual   ~ClassVar() { ReleaseM(); } // releases everything

	void BackUp();
	void Restore();

	ClassVar(const ClassVar& Cl);
	ClassVar& operator=(const ClassVar& Cl);

	double& operator[](int ii) { return values[ii]; }

	virtual void ReleaseM(bool Keep = false);

	virtual void ReadVar();

	virtual void WriteVar();

	virtual string UserName(void) { return module + ' ' + name; };

	virtual void LoopFirst(long dim_n);

	virtual void LoopLast(long dim_n);

	virtual void LoopRange(long dim_n);

	virtual void Avg_(long dim_n);

	virtual void Min_(long dim_n);

	virtual void Max_(long dim_n);

	virtual void First_(long dim_n);

	virtual void Last_(long dim_n);

	virtual void Count_(long dim_n);

	virtual void Count0_(long dim_n);

	virtual void Pos_(long dim_n);

	virtual void Tot_(long dim_n);

	virtual void Avg(void);

	virtual void Min(void);

	virtual void Max(void);

	virtual void Dtot(void);

	virtual void Tot(void);

	virtual void First(void);

	virtual void Last(void);

	virtual void Peak(void);

	virtual void Count(void);

	virtual void Count0(void);

	virtual void Pos(void);

	virtual void Intvl(void);

	virtual void do_t(ClassModule* thisModule); // uses Global::lapse_rate, Global::hru_elev and Global::OBS_ELEV

	virtual void do_t_Clim(ClassModule* thisModule); // uses Global::Warming_t and do_t

	virtual void do_t_day(ClassModule* thisModule); // uses Global::lapse_rate, Global::hru_elev and Global::OBS_ELEV

	virtual void do_t_day_Clim(ClassModule* thisModule); // uses Global::Warming_t and do_t_day

	virtual void do_rh_day(ClassModule* thisModule); // uses Global::obs_ea and Global::obs_t and if Global::RH_VP_flag then Global::obs_t_obs

	virtual void do_rh_day_Clim(ClassModule* thisModule); // uses do_rh_day and if extra Global::RH_VP_flag2 then Global::obs_t_obs

	virtual void do_ea_day(ClassModule* thisModule); // uses Global::obs_rh, Global::obs_t_obs, Global::obs_t and Global::RH_VP_flag

	virtual void do_ppt(ClassModule* thisModule); // uses Global::hru_elev, Global::OBS_ELEV and Global::ppt_adj

	virtual void do_p(ClassModule* thisModule); // uses Global::hru_elev, Global::OBS_ELEV and Global::ppt_adj

	virtual void do_p_Clim(ClassModule* thisModule); // uses Global::Warming_p

	virtual void do_ppt_Clim(ClassModule* thisModule); // uses Global::Warming_p

	long GetUnit(void);

	virtual void review_HRU_OBS(void);
};

#endif // !CLASSVAR
