#pragma once

#ifndef TOBJECTS
#define TOBJECTS

#include "TStringList.h"

class TStringList;

class TObjects {
public:
	TObject*& operator[](int ii);
	void Init(TStringList* StringList_) { StringList = StringList_; };

	TStringList* StringList;
};

#endif // !TOBJECTS
