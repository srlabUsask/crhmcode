// TStringList.cpp : Defines the entry point for the console application.
//

#if defined(_WIN32)
#include "stdafx.h"
#include <Windows.h>
#include <direct.h>
#endif

#if defined(__linux__)|| defined(__APPLE__)
#include <unistd.h>
#endif

#include "TStringList/TStringList.h"
#include <time.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <limits>
#include "ClassCRHM/ClassCRHM.h"
#include "Common.h"

string TStringList::CommaText(void) 
{
	ostringstream temp;

	for (unsigned int ii = 0; ii < array.size(); ++ii) 
	{
		if (ii)
		{
			temp << ", ";
		}
		temp << array.at(ii).get_Name();
	}
	temp << endl;
	return temp.str();
}


void TStringList::DelimitedText(string s) 
{

	string in_quote;
	bool quoted = false;
	long pos;
	long here; 
	long last_quote; 
	long done_to = 0;

	Clear();
	Common::trim(s);
	
	if (s.size() == 0)
	{
		return;
	}
		
	s.append(",");

	for (pos = 0; pos < (long)s.size(); ++pos) 
	{
		here = s.find_first_of("' ,", pos);
		pos = here;
		switch (s[here]) 
		{
			case '\'':
				quoted = true;
				last_quote = s.find('\'', ++pos);
				if (last_quote > here + 1) // not empty
				{
					in_quote = s.substr(here + 1, last_quote - here - 1);
				}
				else
				{
					return;
				}
				pos = last_quote;
				break;
			
			case ',':
			
			case ' ':
				if (quoted) 
				{
					Add(in_quote);
				}	
				else 
				{
					if (pos > done_to)
					{
						Add(s.substr(done_to, pos - done_to));
					}
					else
					{
						return;
					}
				}

				done_to = s.find_first_not_of(" ", here + 1);

				if (done_to > -1)
				{
					pos = done_to - 1;
				}
				else
				{
					pos = here;
				}
				in_quote = "";
				quoted = false;

			default:
				break;
		} // switch
	} // for
}

void TStringList::CommaText(string s) 
{ 
	string in_quote;
	string::size_type pos;
	string::size_type here;
	string::size_type last_quote;
	string::size_type done_to = 0;

	array.clear();
	Common::trim(s);
	s.append(",");
	
	for (pos = 0; pos < s.size(); ++pos) 
	{
		here = s.find_first_of("' ,", pos);
		switch (s[here]) 
		{
			case '\'':
				last_quote = s.find("'", pos);
				in_quote = s.substr(here + 1, last_quote - 1);
				pos = last_quote + 1;
				break;

			case ',':

			case ' ':
				in_quote.append(s.substr(done_to, here - done_to));
				Add(in_quote);
				done_to = s.find_first_not_of(" ", here + 1);

				if (done_to == string::npos)
				{
					pos = s.size();
				}
				else 
				{
					pos = done_to;
					in_quote = "";
				}
			default:
				break;
		} // switch
	} // for
}


void TStringList::SaveToFile(string FileName) 
{	
	ofstream file;
	file.open(FileName.c_str());

	for (unsigned int ii = 0; ii < array.size(); ++ii) 
	{
		file << array.at(ii).get_Name() << endl;
	}

	file.close();
}


string &TStringList::operator[](int ii) 
{
	return array[ii].Name;
}


void TStringList::AddObject(string s, TObject* thing) 
{

	array.push_back(StringandObject(s, thing));
	Count = array.size();
}


void TStringList::InsertObject(int ii, string name, TObject * object)
{
	array.push_back(StringandObject(name, object));
	Count = array.size();
}


int TStringList::IndexOf(string s) 
{

	
	if (Count <= 0) 
	{ 
		return -1; 
	}
	else 
	{
		for (unsigned int ii = 0; ii < array.size(); ++ii)
		{
			if (array.at(ii).get_Name() == s)
			{
				return ii;
			}
				
		}
			
	}
	
	return -1;
}


void TStringList::Add(string s) 
{
	array.push_back(StringandObject(s, 0));
	Count = array.size();
}


void TStringList::Clear() 
{
	array.clear();
	Count = 0;
}


void TStringList::Assign(TStringList *Src) 
{
	Clear();
	for (unsigned int ii = 0; ii < Src->array.size(); ++ii) 
	{
		AddObject(Src->array.at(ii).get_Name(), Src->array[ii].Object);
	}
}


void TStringList::Delete(int Index) 
{
	vector<StringandObject>::iterator pos;
	int cnt = -1;
	for (pos = array.begin(); pos < array.end(); ++pos) 
	{
		if (Index == ++cnt) 
		{
			array.erase(pos);
			Count = array.size();
			return;
		}
	}		
}

string &TStrings::operator[](int ii) {
	//string result = "";
	if (ii < 0 || ii >= StringList->Count)
	{ 
		//added by Manishankar.
		CRHMException Except("Array index out of bounds.", TExcept::TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
	//if (ii >= StringList->Count) { return result; }
	return StringList->array[ii].Name;
}

TObject* &TObjects::operator[](int ii) {
	//TObject * to ;
	if (ii < 0 || ii >= StringList->Count)
	{ 
		//added by Manishankar.
		CRHMException Except("Array index out of bounds.", TExcept::TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
	return StringList->array[ii].Object;
}

TStringList::TStringList(const TStringList &p) { // copy constructor

	Sorted = p.Sorted;
	CaseSensitive = p.CaseSensitive;

	array.reserve(64);
	Strings.Init(this);
	Objects.Init(this);
	Count = 0;
}

//TStringList & TStringList::operator=(const TStringList & p) {
//
//	if (this == &p) return *this;
//
//}


void TStringList::LoadFromFile(string filename)
{
	ifstream infile(filename.c_str());
	string line;
	while (std::getline(infile, line))
	{
		AddObject(line, NULL);
	}
}
