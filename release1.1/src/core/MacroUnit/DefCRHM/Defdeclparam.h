#pragma once

#ifndef DEFDECLPARAM
#define DEFDECLPARAM

#include "DefCRHM.h"

using namespace std;

class Defdeclparam : public DefCRHM {
public:
	Defdeclparam(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	TDim Dim;
	string Default;
	string Min;
	string Max;
	string Description;
	string Units;
	bool Int;
	int nlay;
	TVISIBLE visibility;
};

#endif // !DEFDECPARAM
