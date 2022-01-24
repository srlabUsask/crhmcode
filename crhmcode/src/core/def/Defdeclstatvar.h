#pragma once

#ifndef DEFDECLSTAVAR
#define DEFDECLSTAVAR

#include "DefCRHM.h"

class Defdeclstatvar : public DefCRHM {
public:
	Defdeclstatvar(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	TDim Dim;
	string Description;
	string Units;
	bool Int;
};

#endif // !DEFDECLSTAVAR
