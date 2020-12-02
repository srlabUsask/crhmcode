#pragma once

#ifndef DEFDECLDIAG
#define DEFDECLDIAG

#include "DefCRHM.h"

class Defdecldiag : public DefCRHM {
public:
	Defdecldiag(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string name;
	TDim Dim;
	string Description;
	string Units;
	bool Int;
};

#endif // !DEFDECLDIAG
