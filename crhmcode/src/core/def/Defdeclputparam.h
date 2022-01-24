#pragma once

#ifndef DEFDECLPUTPARAM
#define DEFDECLPUTPARAM

#include "DefCRHM.h"

class Defdeclputparam : public DefCRHM {
public:
	Defdeclputparam(ClassMacro* Macro_);
	void CallDecl();
	void CallInit(long nhru, long nlay);

	string module;
	string name;
	string Units;
	bool Int;
};

#endif // !DEFDECLPUTPARAM
