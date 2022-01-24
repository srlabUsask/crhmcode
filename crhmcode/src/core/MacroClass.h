#pragma once

#ifndef MACROCLASS
#define MACROCLASS

#include "ClassCRHM.h"
#include "Classfilter.h"

class Classfilter;

class MacroClass 
{
public:
	MacroClass(ClassData* File);
	~MacroClass();

	ClassData* File;
	std::vector<std::pair<std::string, Classfilter *>> * FilterList;
	long Interpolation;
	void addfilter(string Line);
	void fixup(void);
	void execute(long Line);
};

#endif // !MACROCLASS
