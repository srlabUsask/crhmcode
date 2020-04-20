

//#include "stdafx.h"
#include <stdio.h>
//#include <tchar.h>



#include "StandardConverterUtility.h"
#include "TStringList.h"
//#include "ATLComTime.h"
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
	//COleDateTime dateTest;
	//dateTest = COleDateTime::GetCurrentTime();
	//double t = dateTest;
	return Common::DateTimeDt();;
}




double StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)
{
	/*
	if (hour == 24)
	{
		hour = 23;
		minute = 59;
		second = 59;
	}
	COleDateTime time = COleDateTime(year, month, day, hour, minute, second);
	double t = time;*/
	double t = Common::EncodeDateTime(year, month, day, hour, minute);
	return t;
}




//This function takes a double date time as a parameter and returns date time in string format   'mm/dd/yyyy hh:mm'
std::string StandardConverterUtility::GetDateTimeInString(double datetime)
{
	int y, m, d, h, min, s;
	Common::DecodeDateTime(datetime, &y, &m, &d, &h, &min);

	/*
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }*/

	std::string stime = std::to_string(m) + "/" + std::to_string(d) + "/" + std::to_string(y) + " " + std::to_string(h) + ":" + std::to_string(min);

	return stime;
}

std::string StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)
{
	int y, m, d, h, min, s;
	Common::DecodeDateTime(datetime, &y, &m, &d, &h, &min);

	/*
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }*/

	//if (min == 59 && h != 23) { h = h+1; min = 0; } //added by Manishankar to round the minutes into the next hour.

	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d) + " " + std::to_string(h) + " " + std::to_string(min);

	return stime;
}


std::string StandardConverterUtility::GetDateInString(double datetime)
{
	int y, m, d, h, min, s;
	Common::DecodeDateTime(datetime, &y, &m, &d, &h, &min);

	/*
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }
	*/

	std::string stime =  std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d);

	return stime;
}

/*void StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)
{
	COleDateTime time = datetime;
	int year = time.GetYear(), month = time.GetMonth(), day = time.GetDay(), hour = time.GetHour(), minute = time.GetMinute();

	std::string shour = std::to_string(hour), sminute = std::to_string(minute);
	if (hour < 10) { shour = "0" + std::to_string(hour); }
	if (minute < 10) { sminute = "0" + std::to_string(minute); }

	*y = year; *m = month, *d = day, *h = hour, *mi - minute;
}*/

//CString StandardConverterUtility::GetCStringFromStandardString(string str)
//{
//	CString cstr(str.c_str());
//	return cstr;
//}




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



