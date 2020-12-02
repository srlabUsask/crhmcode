#pragma once

#ifndef DEFDECLLOCAL
#define DEFDECLLOCAL

#include "DefCRHM.h"

class Defdecllocal : public DefCRHM {
public:
	Defdecllocal(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	TDim Dim;
	string Description;
	string Units;
	bool Int;
};

#endif // !DEFDECLLOCAL
