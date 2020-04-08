#include "stdafx.h"
#include "StandardConverterUtility.h"
#include "TStringList.h"
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
	COleDateTime dateTest;
	dateTest = COleDateTime::GetCurrentTime();
	double t = dateTest;
	return t;
}




double StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)
{
	if (hour == 24)
	{
		hour = 23;
		minute = 59;
		second = 59;
	}
	COleDateTime time = COleDateTime(year, month, day, hour, minute, second);
	double t = time;
	return t;
}




//This function takes a double date time as a parameter and returns date time in string format   'mm/dd/yyyy hh:mm'
std::string StandardConverterUtility::GetDateTimeInString(double datetime)
{
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }

	std::string stime = std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year) + " " + shour + ":" + sminute;

	return stime;
}

std::string StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)
{
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	//if (hour < 10) { shour = "0" + std::to_string(hour); }
	//if (minute < 10) { sminute = "0" + std::to_string(minute); }

	std::string stime = std::to_string(year) + " " + std::to_string(month) + " " + std::to_string(day) + " " + shour + " " + sminute;

	return stime;
}


std::string StandardConverterUtility::GetDateInString(double datetime)
{
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }

	std::string stime =  std::to_string(year) + " " + std::to_string(month) + " " + std::to_string(day);

	return stime;
}

void StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)
{
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }

	*y = year; *m = month, *d = day, *h = hour, *mi - minute;
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



