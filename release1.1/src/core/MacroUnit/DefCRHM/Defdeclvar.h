#pragma once

#ifndef DEFDECLVAR
#define DEFDECLVAR

#include "DefCRHM.h"

class Defdeclvar : public DefCRHM {
public:
	Defdeclvar(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	TDim Dim;
	string Description;
	string Units;
	bool Int;
};

#endif // !DEFDECLVAR
