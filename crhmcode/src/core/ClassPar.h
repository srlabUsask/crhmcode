#pragma once

#ifndef CLASSPAR
#define CLASSPAR

#include "ClassCRHM.h"

using namespace std;

class parser;

class ClassPar {
public:
	string module;
	string param;
	string basemodule;
	string help;
	string units;

	TVar varType;
	TDim dimen{ TDim::NDEFNZ };

	long dim;
	long lay{ 0 };
	long variation_set{ 0 };

	double* values;
	long* ivalues;

	double** layvalues;
	long** ilayvalues;

	string valstr;
	double minVal{ 0.0 };
	double maxVal{ 0.0 };

	std::vector<std::string> * Strings{ NULL };
	std::vector<std::string> * StringsBkup{ NULL };

	TVISIBLE visibility{ TVISIBLE::USUAL };

	long Inhibit_share; // 0 - shared, 1 - linked to declparam, 2 - declputparam unlinked

						// backup storage

	double** layvaluesBkup{ NULL };
	long** ilayvaluesBkup{ NULL };

	ClassPar* Identical;

	

	ClassPar(string module = "none", string param = "none") : 
		module(module), 
		param(param), 
		dim(0), 
		visibility(TVISIBLE::USUAL), 
		variation_set(0), 
		varType(TVar::none),
		values(NULL), 
		ivalues(NULL), 
		layvalues(NULL), 
		ilayvalues(NULL), 
		Identical(NULL), 
		Inhibit_share(0) 
	{};

	ClassPar(string module, string param, TDim dimen, string CommaText, string help, TVar varType, int Grpdim);

	ClassPar(
		string module, 
		string param, 
		TDim dimen, 
		string valstr, 
		double minVal, 
		double maxVal,
		string help, 
		string units, 
		TVar varType, 
		int defdim = 0, 
		int GrpN = 0
	);

	ClassPar(ClassPar& p);  // copy constructor

	double& operator[](int ii) { return values[ii]; }

	virtual  ~ClassPar();

	bool Same(ClassPar& p);  // compares parameter data

	void Change(ClassPar& p);  // changes this values to p

	virtual string UserName(void) { return module + ' ' + param; };

	friend class ::parser;

	void ExpandShrink(long new_dim);

	void BackUp(void);

	void Restore(void);

	long GetUnit(void);

};

#endif // !CLASSPAR
