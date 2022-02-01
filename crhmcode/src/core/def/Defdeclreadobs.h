#pragma once

#ifndef DEFDECLREADOBS
#define DEFDECLREADOBS

#include "DefCRHM.h"

class Defdeclreadobs : public DefCRHM {
public:
	Defdeclreadobs(ClassMacro* Macro_);
	void CallDecl();

	string name;
	TDim Dim;
	string Description;
	string Units;
	long HRU_OBS_indexed;
};

#endif // !DEFDECLREADOBS
