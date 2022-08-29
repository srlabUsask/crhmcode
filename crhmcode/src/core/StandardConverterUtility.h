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
#pragma once

#include <cstring>
#include <string>
#include <cmath>
#include <ctime>

class StandardConverterUtility
{
public:
	static double GetCurrentDateTime();
	static std::string GetDateTimeInString(double datetime);
	static std::string GetDateTimeInStringForOutput(double datetime);
	static std::string GetDateInString(double datetime);
	static void GetDateTimeElements(double datetime, int * year, int * month, int * day, int * hour, int * minute);
	static double GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second);
	double static Calculate_TdateTime_Offset(void);
	double static EncodeDateTime(int Year, int Month, int Day, int hour, int min);
	void static DecodeDateTime(double Dttime, int *Year, int *Month, int *Day, int *Hour, int *Min);
	double static DateTimeDt(void);
	std::string static FormatDateTime(std::string fmt, double datetime);


	StandardConverterUtility();
	~StandardConverterUtility();
};

long static Decade_Offsets[][4] = { // Year, abs(value), calc wrt to this year, offset.
	{ 80, -3652,  29219,     2 }, // 1900 moved to 1980
{ 60,  3654,  21915,  3654 }, // 1910 moved to 1970
{ 60,  3654,  21915,  7306 }, // 1920 moved to 1980
{ 40,  10959, 14610, 10959 }, // 1930 moved to 1970
{ 40,  10959, 14610, 14611 }, // 1940 moved to 1980
{ 20,  18264,  7305, 18264 }, // 1950 moved to 1970
{ 20,  18264,  7305, 21916 }, // 1960 moved to 1980
{ 0,  25569,     0, 25569 }, // 1970 not moved
{ 0,  29221,     0 }, // 1980 (not used)
};

