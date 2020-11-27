#pragma once

#ifndef CLASSMACRO
#define CLASSMACRO

#include "ClassCRHM.h"

class Classmacro {
public:
	Classmacro(ClassData* File);
	~Classmacro();

	ClassData* File;
	TStringList* FilterList;
	long Interpolation;
	void addfilter(string Line);
	void fixup(void);
	void execute(long Line);
};

#endif // !CLASSMACRO
