#pragma once

#ifndef TSTRINGS
#define TSTRINGS

using namespace std;

class TStringList;

/**
* TStrings is a class that defines a list of strings
*/
class TStrings {

public:
	TStringList* StringList; //!< A TStringList of strings

	/**
	* Overload of [] such that the operator [i] returns the ith element of the TStrings::StringList
	*
	* @return the ith string in TStrings::StringList
	*/
	string& operator[](int ii);
	
	/**
	* Initalizes this TStrings::StringList with the provided TStringList
	*/
	void Init(TStringList* StringList_) { StringList = StringList_; };
};

#endif // !TSTRINGS
