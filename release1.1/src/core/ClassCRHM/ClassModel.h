#pragma once
#include <string>

#ifndef CLASSMODEL
#define CLASSMODEL

using namespace std;

class ClassModel {
public:
	string ModelName;
	string ModelModules;

	ClassModel(string ModelName, string ModelModules) :
		ModelName(ModelName), ModelModules(ModelModules) {};
};

#endif // !CLASSMODEL
