// TStringList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TStringList.h"
#include <list>

TStringList::TStringList() {}

string TStringList::operator[](int ii) {
	return array[ii].Name;
}

void TStringList::AddObject(string s, TObject* thing) {
	array.push_back(StringandObject(s, thing));
}

int TStringList::IndexOf(string s) {

	for (int ii = 0; ii < array.size(); ++ii)
		if (array.at(ii).get_Name() == s)
			return ii;

	return -1;
}

void TStringList::Add(string s) {
	array.push_back(StringandObject(s, 0));
}

list<string> TStringList::showall() {

	std::list<std::string> sList;

	for (int ii = 0; ii < array.size(); ++ii) {
		sList.push_back(array.at(ii).get_Name());
	}

	return sList;
}

void TStringList::Clear() {
	array.clear();
}

void TStringList::Delete(int Index) {
	int cnt = 0;
	for (pos = array.begin(); pos < array.end(); ++pos)
		if (Index == cnt) {
			array.erase(pos);
			return;
		}
	;
}

string TStrings::operator[](int ii) {
	return StringList->array[ii].Name;
}

TObject* TObjects::operator[](int ii) {
	return StringList->array[ii].Object;
}

//void saveFiles(TStringList H)
//{
//	ofstream myfile;
//	myfile.open("example.txt");
//
//	for (unsigned int a = 0; a < sizeof(H.Count); a = a + 1)
//	{
//		myfile << "value of a: " << H.Sorted << endl;
//	}
//	myfile.close();
//
//}

//int main()
//{
//	TStringList Fred;
//
//	cout << "Hello world!" << endl;
//
//	for (int ii = 0; ii < 26; ++ii) {
//
//	 string Name("nameA");
//		Name[4] += ii;
//
//		//Fred.AddObject(Name, (TObject*)ii);
//		Fred.Add(Name);
//	}
//
//	/*saveFiles(Fred);*/
//	int I;
//	cin >> I;
//	for (int ii = 0; ii < 26; ++ii) {
//
//		cout << Fred[ii] << endl;
//		//      cout << (Fred.Strings).Test << endl;
//		//      cout << Fred.Strings[2] << endl;
//		//      cout << Fred.Strings[ii] << endl;
//	}
//
//	//cout << Fred.IndexOf("nameD") << endl;
//	//    cout << Fred.Strings << endl;
//
//	return 0;
//}