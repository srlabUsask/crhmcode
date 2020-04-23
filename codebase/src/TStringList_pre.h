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
#include <atltime.h>
#include<sstream>
#include<iomanip>
using namespace std;


typedef void TObject;

class TStringList;
class TStrings;
class TObjects;



class StringandObject {
public:

	string Name;
	TObject* Object;

	StringandObject() { Name = ""; Object = 0; };
	StringandObject(string Name_, TObject* Object_) { Name = Name_; Object = Object_; };
	string get_Name() { return Name; };
	TObject* get_Object() { return Object; };
};

class TStringList {
protected:


public:
	TStringList();

	vector<StringandObject> array;
	vector<StringandObject>::iterator pos;


	//TStrings S = TStrings();

	string Strings;
	TObjects *Objects;

	int Count;
	bool CaseSensitive;
	bool Sorted;

	string DelimitedText;
	string CommaText;

	int IndexOf(string s);
	void Add(string s);
	list<string> showall();
	void AddObject(string s, TObject* thing);
	void Clear();
	void Delete(int Index);
	string operator[](int ii);
	//  void SaveToFile(string FileName){};


	void Assign(TStringList * list) { Strings = list->Strings; };
};


class TStrings {
public:
	int Test;
	TStrings() {
		return;
	};
	TStrings(TStringList* StringList_) : StringList(StringList_) { Test = 987; };
	string operator[](int ii);

	TStringList* StringList;
};

class TObjects {
public:
	int Test;

	TObjects(TStringList* StringList_) : StringList(StringList_) { Test = 789; };
	TObject* operator[](int ii);

	TStringList* StringList;
};



#endif // !TSTRINGLIST_H