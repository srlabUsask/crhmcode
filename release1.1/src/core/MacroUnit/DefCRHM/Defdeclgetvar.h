#pragma once

#ifndef DEFDECLGETVAR
#define DEFDECLGETVAR

#include "DefCRHM.h"

class Defdeclgetvar : public DefCRHM {
public:
	Defdeclgetvar(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string module;
	string name;
	string Units;
	bool Int;
};

#endif // !DEFDECLGETVAR
