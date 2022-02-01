#pragma once

#ifndef DEFDECLOBS
#define DEFDECLOBS

#include "DefCRHM.h"

class Defdeclobs : public DefCRHM {
public:
	Defdeclobs(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	TDim Dim;
	string Description;
	string Units;
};

#endif // !DEFDECLOBS
