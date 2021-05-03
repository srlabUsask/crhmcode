#pragma once

#ifndef DEFDECLPUTVAR
#define DEFDECLPUTVAR

#include "DefCRHM.h"

class Defdeclputvar : public DefCRHM {
public:
	Defdeclputvar(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string module;
	string name;
	string Units;
	bool Int;
};

#endif // !DEFDECLPUTVAR
