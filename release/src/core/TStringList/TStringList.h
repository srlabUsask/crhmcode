#pragma once

#ifndef TSTRINGLIST_H
#define TSTRINGLIST_H

// 08/23/12
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <list>
#include<sstream>
#include<iomanip>
#include "StringandObject.h"
#include "TStrings.h"
#include "TObjects.h"
//#include <atltime.h>

using namespace std;

#ifndef TOBJECT
#define TOBJECT
typedef void TObject;
#endif // !TOBJECT

/**
* TStringList stores a vector of StringandObject and provides helpful methods for manipulating this array.
* 
* 
*/
class TStringList {
public:

	int Count; //!< The number of items in the TStringList
	char QuoteChar = '\"'; //!< The character use for quotes for incoming values to this TStringList
	bool CaseSensitive; //!< Not impemented
	bool Sorted; //!< Not impemented
	
	string FilePath; //!< Used to store file path for a loaded observation file

	vector<StringandObject> array; //!< vector of StringandObject which stores the names and objects stored in this TStringList
	TStrings Strings;
	TObjects Objects;

	/**
	* Default constructor allocates memory for the TStringList reserving 64 positons for the TStringList::array
	* 
	* By default TStringList::CaseSensitive and TStringList::Sorted are false.
	*/
	TStringList() { array.reserve(64); Strings.Init(this); Objects.Init(this); Count = 0; CaseSensitive = false; Sorted = false; };

	/**
	* Constructor that copies an exisitng TStringList 
	* 
	* @param p	A reference to the TStringList to be copied
	*/
	TStringList(const TStringList &p);


	TStringList & operator=(const TStringList & p) = delete;//updated by Manishankar for resolving a warning.
	
	/**
	* Overload of [] such that the operator [i] returns the name of the ith element of TStringList::array
	*
	* @return the name of the ith element in TStringList::array
	*/
	string& operator[](int ii);

	/**
	* Returns the index of the provided string if it exists in the TStringList
	*
	* If the string does not exist -1 is returned.
	*
	* @param s	The string to look for the index of.
	* @return	The index of s or -1 if s is not found.
	*/
	int IndexOf(string s);

	/**
	* Add a StringandObject to TStringList::array with a specified string and Null TObject.
	*
	* The StringandObject is added to the back of TStringList::array.
	*
	* @param s The value of the string to add to TStringList::array.
	*/
	void Add(string s);

	/**
	* Creates a StringandObject with the specified string and object and pushes it to the back of TStringList::array.
	*
	* @param s:			The string portion of the StringandObject.
	* @param thing:		A pointer to the TObject portion of the StringandObject.
	*/
	void AddObject(string s, TObject* thing);

	/**
	* Removes all items from TStringList::array and resets Count to zero.
	*/
	void Clear();

	/**
	* Removes the element at index Index from TStringList::array.
	*
	* @param Index The index of the element to remove from TStringList::array.
	*/
	void Delete(int Index);

	/**
	* Replaces TStringList::array with the values contained within the specified TStringList.
	*
	* First clears TStringList::array by calling Clear() then calls AddObject() for each item in src.
	*
	* @param src A pointer to the TStringList whose TStringList::array should replace this TStringList::array.
	*/
	void Assign(TStringList *Src);
	
	/**
	* Parses input string of comma seperated values and adds each value to TStringList::array.
	*
	*	Before adding the values to TStringList::array this function calls Clear()
	*	Also removes quotes around incoming values.
	*
	*	For example an input of "'red',blue,'yellow'" will add "red" "blue" and "yellow" to TStringList::array
	*
	* @param s	Input string of comma seperated values
	*/
	void DelimitedText(string s);

	/**
	* Parses input string of comma seperated values and adds each value to TStringList::array.
	*
	*	Before adding the values to array this function calls Clear()
	*	Also removes quotes around incoming values.
	*	Used to read "AnnandaleX, calcsunX, calcsun_QsiD, ...
	*
	*	For example an input of "'red',blue,'yellow'" will add "red" "blue" and "yellow" to TStringList::array
	*
	* @param s	Input string of comma seperated values
	*/
	void CommaText(string s);

	/**
	* Returns all the strings in TStringList::array as a comma seperated values string.
	*
	* @return	string a comma seperated values string of all the strings in TStringList::array
	*/
	string CommaText(void);

	//this functions are already implemented in Common.h and Common.cpp. Manishankar
	//string trim(string & str);
	//string trimright(string & str);
	//string trimleft(string & str);

	/**
	* Writes the name values in TStringList::array to a file with the specified filename.
	*
	* @param FileName	The name of the file to save the values to.
	*/
	void SaveToFile(string FileName);

	/**
	* Adds the provided string and TObject reference to TStringList::array as a StringandObject
	*
	* @param ii			An int value which is unused.
	* @param name		The string portion of the StringandObject to be added to TStringList::array.
	* @param object		A reference to the object portion to be added to TStringList::array.
	*/
	void InsertObject(int ii, string name, TObject * object);

	/**
	* Adds each line in a specified file to the string portion of TStringList::array.
	*
	* @param filename	The file name of the file to load from.
	*/
	void LoadFromFile(string filename);
};



//typedef void TObject;
//
//class TStringList;
//class TStrings;
//class TObjects;
//
//
//
//class StringandObject {
//public:
//
//	string Name;
//	TObject* Object;
//
//	StringandObject() { Name = ""; Object = 0; };
//	StringandObject(string Name_, TObject* Object_) { Name = Name_; Object = Object_; };
//	string get_Name() { return Name; };
//	TObject* get_Object() { return Object; };
//};
//
//class TStringList {
//protected:
//
//
//public:
//	TStringList();
//
//	vector<StringandObject> array;
//	vector<StringandObject>::iterator pos;
//
//
//	//TStrings S = TStrings();
//
//	string Strings;
//	TObjects *Objects;
//
//	int Count;
//	bool CaseSensitive;
//	bool Sorted;
//
//	string DelimitedText;
//	string CommaText;
//
//	int IndexOf(string s);
//	void Add(string s);
//	list<string> showall();
//	void AddObject(string s, TObject* thing);
//	void Clear();
//	void Delete(int Index);
//	string operator[](int ii);
//	//  void SaveToFile(string FileName){};
//
//
//	void Assign(TStringList * list) { Strings = list->Strings; };
//};
//
//
//class TStrings {
//public:
//	int Test;
//	TStrings() {
//		return;
//	};
//	TStrings(TStringList* StringList_) : StringList(StringList_) { Test = 987; };
//	string operator[](int ii);
//
//	TStringList* StringList;
//};
//
//class TObjects {
//public:
//	int Test;
//
//	TObjects(TStringList* StringList_) : StringList(StringList_) { Test = 789; };
//	TObject* operator[](int ii);
//
//	TStringList* StringList;
//};

#endif // !TSTRINGLIST_H

