#include "stdafx.h"
#include "StandardConverterUtility.h"
#include "TStringList.h"
#include "Common.h"
//#include <atlstr.h>


StandardConverterUtility::StandardConverterUtility()
{
}


StandardConverterUtility::~StandardConverterUtility()
{
}



//This function returns current date and time in double format.
double StandardConverterUtility::GetCurrentDateTime()
{
	return Common::DateTimeDt();;
}




double StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)
{
	double t = Common::EncodeDateTime(year, month, day, hour, minute);
	return t;
}




//This function takes a double date time as a parameter and returns date time in string format   'mm/dd/yyyy hh:mm'
std::string StandardConverterUtility::GetDateTimeInString(double datetime)
{
	int y, m, d, h, min, s;
	Common::DecodeDateTime(datetime, &y, &m, &d, &h, &min);
	std::string stime = std::to_string(m) + "/" + std::to_string(d) + "/" + std::to_string(y) + " " + std::to_string(h) + ":" + std::to_string(min);
	return stime;
}

std::string StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)
{
	int y, m, d, h, min, s;
	Common::DecodeDateTime(datetime, &y, &m, &d, &h, &min);
	//if (min == 59 && h != 23) { h = h + 1; min = 0; } //added by Manishankar to round the minutes into the next hour.
	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d) + " " + std::to_string(h) + " " + std::to_string(min);
	return stime;
}


std::string StandardConverterUtility::GetDateInString(double datetime)
{
	int y, m, d, h, min, s;
	Common::DecodeDateTime(datetime, &y, &m, &d, &h, &min);
	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d);
	return stime;
}

void StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)
{
	int y1, m1, d1, h1, min1, s1;
	Common::DecodeDateTime(datetime, &y1, &m1, &d1, &h1, &min1);

	*y = y1; *m = m1, *d = d1, *h = h1, *mi = min1;
}

//CString StandardConverterUtility::GetCStringFromStandardString(string str)
//{
//	CString cstr(str.c_str());
//	return cstr;
//}


//This function returns all items from a listbox.
TStringList * GetItemsFromListBox(CListBox * listbox)
{
	TStringList * list = new TStringList();
	//CListBox * listbox = (CListBox*)GetDlgItem(listboxid);

	int itemcount = listbox->GetCount();
	for (int i = 0; i < itemcount; i++)
	{
		CString str;
		listbox->GetText(i, str);
		CT2A s(str);
		string st = s;
		list->Add(st);
	}
	return list;
}

//This function sets the items to a listbox.
void SetItemsToListBox(CListBox * listbox, TStringList * list)
{
	int count = list->Count;

	for (int i = 0; i < count; i++)
	{
		string str = list->array[i].get_Name();
		CString cstr(str.c_str());
		listbox->AddString(cstr);
	}
}





//TStringList * StandardConverterUtility::GetItemsFromListBox(int listboxid)
//{
//	TStringList * list = new TStringList();
//	CListBox * listbox = (CListBox*)GetDlgItem(listboxid);
//
//	int itemcount = listbox->GetCount();
//	for (int i = 0; i < itemcount; i++)
//	{
//		CString str;
//		listbox->GetText(i, str);
//		CT2A s(str);
//		string st = s;
//
//		list->Add(st);
//	}
//	return list;
//}



