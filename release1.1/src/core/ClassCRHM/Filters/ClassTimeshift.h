#pragma once

#ifndef CLASSTIMESHIFT
#define CLASSTIMESHIFT

#include "../Classfilter.h"

class ClassTimeshift : Classfilter {
public:
	ClassTimeshift(ClassData* MyObs, string ToVar, string args, string argtypes = "C");
};

#endif // !CLASSTIMESHIFT
