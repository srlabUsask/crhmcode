/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#include "StandardConverterUtility.h"

StandardConverterUtility::StandardConverterUtility()
{
}


StandardConverterUtility::~StandardConverterUtility()
{
}



//This function returns current date and time in double format.
/*
double StandardConverterUtility::GetCurrentDateTime()
{
	return DateTimeDt();
}
*/



double StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)
{
	double t = EncodeDate(year, month, day) +
				EncodeTime(hour, minute, 0, 0);
	return t;
}




//This function takes a double date time as a parameter and returns date time in string format   'mm/dd/yyyy hh:mm'
std::string StandardConverterUtility::GetDateTimeInString(double datetime)
{
	int y, m, d, h, min, sec, milli; 
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDate(datetime, y, m, d);
	DecodeTime(datetime, h, min, sec, milli);
	std::string stime = std::to_string(m) + "/" + std::to_string(d) + "/" + std::to_string(y) + " " + std::to_string(h) + ":" + std::to_string(min);
	return stime;
}

std::string StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)
{
	int y, m, d, h, min, sec, milli;
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDate(datetime, y, m, d);
	DecodeTime(datetime, h, min, sec, milli);
	//if (min == 59 && h != 23) { h = h + 1; min = 0; } //added by Manishankar to round the minutes into the next hour.
	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d) + " " + std::to_string(h) + " " + std::to_string(min);
	return stime;
}


std::string StandardConverterUtility::GetDateInString(double datetime)
{
	int y, m, d, h, min, sec, milli;
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDate(datetime, y, m, d);
	DecodeTime(datetime, h, min, sec, milli);
	std::string stime = std::to_string(y) + " " + std::to_string(m) + " " + std::to_string(d);
	return stime;
}

void StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)
{
	int y1, m1, d1, h1, min1, sec1, milli1;
	//int s1; variable is unreferenced commenting out for now - jhs507
	DecodeDate(datetime, y1, m1, d1);
	DecodeTime(datetime, h1, min1, sec1, milli1);

	*y = y1; *m = m1, *d = d1, *h = h1, *mi = min1;
}

/*
double StandardConverterUtility::Calculate_TdateTime_Offset(void) {  //Manishankar: It is only being used here.

	tm timeinfo;

	timeinfo.tm_sec = 0;
	timeinfo.tm_min = 0;
	timeinfo.tm_hour = 0;
	timeinfo.tm_mday = 1;
	timeinfo.tm_mon = 0;
	timeinfo.tm_year = 70;
	timeinfo.tm_isdst = -1;

	time_t Current = timegm(&timeinfo); // determine ???

	return double(Current) / 86400.0;
}
*/

/*************************************
 * Date and Time routines mirroring Embarcadero / Borland functionality
 *
 * The following URLs describe the general API requirements of these routines:
 * https://docwiki.embarcadero.com/Libraries/Sydney/en/System.TDateTime
 * https://docwiki.embarcadero.com/Libraries/Sydney/en/System.SysUtils.EncodeDate
 *************************************/

// This offset defines the origin as Jan 1, 1970
#define UNIX_OFFSET 719468 
// This offset defines the origin as Dec 30, 1899
#define BORLAND_OFFSET 693899 

// This algorithm is from the following url:
// https://howardhinnant.github.io/date_algorithms.html#days_from_civil
// This accounts for varying days in the month,
// and leap-year 4yr, 100yr and 400yr rules.
 double StandardConverterUtility::EncodeDate(int y, int m, int d) noexcept {
	y -= m <= 2;
	const int era = (y >= 0 ? y : y-399) / 400;
	const int yoe = y - era * 400;      // [0, 399]
	const int doy = (153*(m > 2 ? m-3 : m+9) + 2)/5 + d-1;  // [0, 365]
	const int doe = yoe * 365 + yoe/4 - yoe/100 + doy;         // [0, 146096]
	return era * 146097 + doe - BORLAND_OFFSET;
}

// This code does not account for leap seconds
 double StandardConverterUtility::EncodeTime(int hour, int min, int sec, int milli) noexcept {
// Need to add a small amount to seconds to avoid underrepresentation in the 'double'	
	return ( ( ( (sec+0.1d)/60.0 + min)/60.0) + hour ) / 24.0;
}

 void StandardConverterUtility::DecodeDate(double Dttime, int &year, int &month, int &day) noexcept {
	long z = Dttime + BORLAND_OFFSET;
	const int era = (z >= 0 ? z : z - 146096) / 146097;
	const int doe = (z - era * 146097);          // [0, 146096]
	const int yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;  // [0, 399]
	const int y = yoe + era * 400;
	const int doy = doe - (365*yoe + yoe/4 - yoe/100);                // [0, 365]
	const int mp = (5*doy + 2)/153;                                   // [0, 11]
	const int d = doy - (153*mp+2)/5 + 1;                             // [1, 31]
	const int m = mp < 10 ? mp+3 : mp-9;                            // [1, 12]
	year = y + (m <= 2);
	month = m;
	day = d;
}

 void StandardConverterUtility::DecodeTime(double Dttime, int &hour, int &min, int &sec, int &milli) noexcept {
	Dttime += 0.99d/86400.0d;
	hour = (long)(Dttime*24) % 24;
	min = (long)(Dttime*24*60) % 60;
	sec = (long)(Dttime*24*60*60) % 60;
}


/*
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

	time_t Current = timegm(&timeinfo);

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
*/


//this function is being used CRHMmain.cpp. Added by Manishankar.
std::string StandardConverterUtility::FormatDateTime(std::string fmt, double datetime) 
{
	int y, m, d, h, min, sec, milli;
	//int s; variable is unreferenced commenting out for now - jhs507
	DecodeDate(datetime, y, m, d);
	DecodeTime(datetime, h, min, sec, milli);

	std::string m1 = std::to_string(m);
	std::string d1 = std::to_string(d);
	std::string h1 = std::to_string(h);
	std::string min1 = std::to_string(min);

	if (m < 10) { m1 = "0" + m1; }
	if (d < 10) { d1 = "0" + d1; }
	if (h < 10) { h1 = "0" + h1; }
	if (min < 10) { min1 = "0" + min1; }

	if (fmt == "yyyy-mm-dd hh:mm ")
	{
		return std::to_string(y) + " " + m1 + " " + d1 + " " + h1 + " " + min1;
	}
	else if (fmt == "ISO")
	{
		return std::to_string(y) + "-" + m1 + "-" + d1 + "T" + h1 + ":" + min1;
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
