#pragma once

#ifndef MACROCLASS
#define MACROCLASS

#include "ClassCRHM.h"

class MacroClass {
public:
	MacroClass(ClassData* File);
	~MacroClass();

	ClassData* File;
	TStringList* FilterList;
	long Interpolation;
	void addfilter(string Line);
	void fixup(void);
	void execute(long Line);
};

#endif // !MACROCLASS
