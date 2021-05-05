#include <cmath>
#include "StandardConverterUtility.h"
#include "TStringList/TStringList.h"

StandardConverterUtility::StandardConverterUtility()
{
}


StandardConverterUtility::~StandardConverterUtility()
{
}



//This function returns current date and time in double format.
double StandardConverterUtility::GetCurrentDateTime()
{
	return DateTimeDt();
}




double StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)
{
	double t = EncodeDateTime(year, month, day, hour, minute);
	return t;
}




//This function takes a double date time as a parameter and returns date time in string format   'mm/dd/yyyy hh:mm'
std::string StandardConverterUtility::GetDateTimeInString(double datetime)
{
	int y, m, d, h, min; 
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDateTime(datetime, &y, &m, &d, &h, &min);
	std::string stime = std::to_string(m) + "/" + std::to_string(d) + "/" + std::to_string(y) + " " + std::to_string(h) + ":" + std::to_string(min);
	return stime;
}

std::string StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)
{
	int y, m, d, h, min;
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDateTime(datetime, &y, &m, &d, &h, &min);
	//if (min == 59 && h != 23) { h = h + 1; min = 0; } //added by Manishankar to round the minutes into the next hour.
	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d) + " " + std::to_string(h) + " " + std::to_string(min);
	return stime;
}


std::string StandardConverterUtility::GetDateInString(double datetime)
{
	int y, m, d, h, min;
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDateTime(datetime, &y, &m, &d, &h, &min);
	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d);
	return stime;
}

void StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)
{
	int y1, m1, d1, h1, min1;
	//int s1; variable is unreferenced commenting out for now - jhs507
	DecodeDateTime(datetime, &y1, &m1, &d1, &h1, &min1);

	*y = y1; *m = m1, *d = d1, *h = h1, *mi = min1;
}

double StandardConverterUtility::Calculate_TdateTime_Offset(void) {  //Manishankar: It is only being used here.

	tm timeinfo;

	timeinfo.tm_sec = 0;
	timeinfo.tm_min = 0;
	timeinfo.tm_hour = 0;
	timeinfo.tm_mday = 1;
	timeinfo.tm_mon = 0;
	timeinfo.tm_year = 70;
	timeinfo.tm_isdst = -1;

	time_t Current = mktime(&timeinfo); // determine ???

	return double(Current) / 86400.0;
}

double StandardConverterUtility::EncodeDateTime(int Year, int Month, int Day, int hour, int min) {  //Manishankar: in ClassCRHM.cpp, GlobalDll.h, CRHMmain.cpp

	tm timeinfo;

	long indx = (Year - 1900) / 10;
	if (indx > 7)indx = 7;

	timeinfo.tm_sec = 0;
	timeinfo.tm_min = min;
	timeinfo.tm_hour = hour;
	timeinfo.tm_mday = Day;
	timeinfo.tm_mon = Month - 1;

	timeinfo.tm_isdst = 0;

	timeinfo.tm_year = Year + Decade_Offsets[indx][0] - 1900;

	time_t Current = mktime(&timeinfo);

	return double(Current) / 86400.0 + Decade_Offsets[indx][1] - Calculate_TdateTime_Offset(); //Global::TdateTime_Offset; // correction from
}

void StandardConverterUtility::DecodeDateTime(double Dttime, int *Year, int *Month, int *Day, int *Hour, int *Min) { //Manishankar: in ClassCRHM.cpp, GlobalDll.h, Hype_routines.cpp, MacroUnit.cpp

	long indx = 7;
	if (Dttime < 25569)
		for (indx = 6; indx >= 0; --indx) {
			if (!(Dttime < Decade_Offsets[indx][3]))
				break;
		}

	long Fix = (long) roundl((Dttime - Decade_Offsets[indx][1])*86400.0);
	//long Fix = (Dttime - Decade_Offsets[indx][1])*86400.0;
	time_t rawtime = (time_t)Fix;

	tm *timeinfo = gmtime(&rawtime);

	//Manishankar added this if condition
	if (timeinfo != NULL)
	{
		*Year = timeinfo->tm_year - Decade_Offsets[indx][0] + 1900;
		*Month = timeinfo->tm_mon + 1;
		*Day = timeinfo->tm_mday;
		*Hour = timeinfo->tm_hour;
		*Min = timeinfo->tm_min;
	}
}

double StandardConverterUtility::DateTimeDt(void) {  //Manishankar: in CRHMmain.cpp and NewModules.cpp.
	time_t Currently;

	time(&Currently);

	return double(Currently) / 86400.0 + Decade_Offsets[7][1] - Calculate_TdateTime_Offset(); //Global::TdateTime_Offset; //  TdateTime_Offset less local time offset
}



//this function is being used CRHMmain.cpp. Added by Manishankar.
std::string StandardConverterUtility::FormatDateTime(std::string fmt, double datetime) {
	int y, m, d, h, min;
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDateTime(datetime, &y, &m, &d, &h, &min);

	string m1 = to_string(m), d1 = to_string(d), h1 = to_string(h), min1 = to_string(min);
	if (m < 10) { m1 = "0" + m1; }
	if (d < 10) { d1 = "0" + d1; }
	if (h < 10) { h1 = "0" + h1; }
	if (min < 10) { min1 = "0" + min1; }

	if (fmt == "mm/dd/yyyy hh:mm ")
	{
		return m1 + "/" + d1 + "/" + to_string(y) + " " + h1 + ":" + min1+" ";
	}
	else if (fmt == "yyyy-mm-dd hh:mm ")
	{
		return to_string(y) + " " + m1 + " " + d1 + " " + h1 + " " + min1;
	}
	else if (fmt == "ISO")
	{
		return to_string(y) + "-" + m1 + "-" + d1 + "T" + h1 + ":" + min1;
	}

	return "";
}




//CString StandardConverterUtility::GetCStringFromStandardString(string str)
//{
//	CString cstr(str.c_str());
//	return cstr;
//}


////This function returns all items from a listbox.
//TStringList * GetItemsFromListBox(CListBox * listbox)
//{
//	TStringList * list = new TStringList();
//	//CListBox * listbox = (CListBox*)GetDlgItem(listboxid);
//
//	int itemcount = listbox->GetCount();
//	for (int i = 0; i < itemcount; i++)
//	{
//		CString str;
//		listbox->GetText(i, str);
//		CT2A s(str);
//		string st = s;
//		list->Add(st);
//	}
//	return list;
//}
//
////This function sets the items to a listbox.
//void SetItemsToListBox(CListBox * listbox, TStringList * list)
//{
//	int count = list->Count;
//
//	for (int i = 0; i < count; i++)
//	{
//		string str = list->array[i].get_Name();
//		CString cstr(str.c_str());
//		listbox->AddString(cstr);
//	}
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