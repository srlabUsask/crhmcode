#pragma once

#ifndef DEFDECLOBSFUNC
#define DEFDECLOBSFUNC

#include "DefCRHM.h"

class Defdeclobsfunc : public DefCRHM {
public:
	Defdeclobsfunc(ClassMacro* Macro_);
	void CallDecl();

	string obs;
	string name;
	TFun typeFun;
};


#endif // !DEFDECLOBSFUNC
