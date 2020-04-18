#include <string>

#pragma once
class StandardConverterUtility
{
public:
	static double GetCurrentDateTime();
	static std::string GetDateTimeInString(double datetime);
	static std::string GetDateTimeInStringForOutput(double datetime);
	static std::string GetDateInString(double datetime);
	static void GetDateTimeElements(double datetime, int * year, int * month, int * day, int * hour, int * minute);
	static double GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second);

	StandardConverterUtility();
	~StandardConverterUtility();
};

