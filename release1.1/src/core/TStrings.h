#pragma once

#ifndef TSTRINGS
#define TSTRINGS

using namespace std;

class TStringList;

/**
* 
*/
class TStrings {

public:
	string& operator[](int ii);
	
	void Init(TStringList* StringList_) { StringList = StringList_; };
	
	TStringList* StringList;
};

#endif // !TSTRINGS
