#pragma once

#ifndef TOBJECTS
#define TOBJECTS

#include "TStringList.h"

class TStringList;

/**
* Tobjects is a class that defines a List of objects
*/
class TObjects {
public:
	TStringList* StringList; //!< A TStringList of objects

	/**
	* Overload of [] such that the operator [i] returns the ith element of the TObjects::StringList
	*
	* @return the ith string in TObjects::StringList
	*/
	TObject*& operator[](int ii);
	
	/**
	* Initalizes this TObjects::StringList with the provided TStringList
	*/
	void Init(TStringList* StringList_) { StringList = StringList_; };
};

#endif // !TOBJECTS
