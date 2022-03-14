#include <cmath>
#include "StandardConverterUtility.h"
#include "TStringList/TStringList.h"
#include "InstrumentLogger.h"

StandardConverterUtility :: StandardConverterUtility ()
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::StandardConverterUtility()@@@StandardConverterUtility.cpp>");
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::StandardConverterUtility()@@@StandardConverterUtility.cpp>");
}
StandardConverterUtility :: ~StandardConverterUtility ()
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::~StandardConverterUtility()@@@StandardConverterUtility.cpp>");
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::~StandardConverterUtility()@@@StandardConverterUtility.cpp>");
}
double StandardConverterUtility :: GetCurrentDateTime ()
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::GetCurrentDateTime()@@@StandardConverterUtility.cpp>");

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetCurrentDateTime()@@@StandardConverterUtility.cpp>");
    return DateTimeDt ();
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetCurrentDateTime()@@@StandardConverterUtility.cpp>");
}
double StandardConverterUtility :: GetDateTimeInDouble (int year, int month, int day, int hour, int minute, int second)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)@@@StandardConverterUtility.cpp>");
    double t = EncodeDateTime (year, month, day, hour, minute);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)@@@StandardConverterUtility.cpp>");
    return t;
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeInDouble(int year, int month, int day, int hour, int minute, int second)@@@StandardConverterUtility.cpp>");
}
std :: string StandardConverterUtility :: GetDateTimeInString (double datetime)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::GetDateTimeInString(double datetime)@@@StandardConverterUtility.cpp>");
    int y, m, d, h, min;
    DecodeDateTime (datetime, & y, & m, & d, & h, & min);
    std :: string stime = std :: to_string (m) + "/" + std :: to_string (d) + "/" + std :: to_string (y) + " " + std :: to_string (h) + ":" + std :: to_string (min);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeInString(double datetime)@@@StandardConverterUtility.cpp>");
    return stime;
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeInString(double datetime)@@@StandardConverterUtility.cpp>");
}
std :: string StandardConverterUtility :: GetDateTimeInStringForOutput (double datetime)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)@@@StandardConverterUtility.cpp>");
    int y, m, d, h, min;
    DecodeDateTime (datetime, & y, & m, & d, & h, & min);
    std :: string stime = std :: to_string (y) + " " + std :: to_string (m) + " " + std :: to_string (d) + " " + std :: to_string (h) + " " + std :: to_string (min);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)@@@StandardConverterUtility.cpp>");
    return stime;
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeInStringForOutput(double datetime)@@@StandardConverterUtility.cpp>");
}
std :: string StandardConverterUtility :: GetDateInString (double datetime)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::GetDateInString(double datetime)@@@StandardConverterUtility.cpp>");
    int y, m, d, h, min;
    DecodeDateTime (datetime, & y, & m, & d, & h, & min);
    std :: string stime = std :: to_string (y) + " " + std :: to_string (m) + " " + std :: to_string (d);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateInString(double datetime)@@@StandardConverterUtility.cpp>");
    return stime;
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateInString(double datetime)@@@StandardConverterUtility.cpp>");
}
void StandardConverterUtility :: GetDateTimeElements (double datetime, int * y, int * m, int * d, int * h, int * mi)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)@@@StandardConverterUtility.cpp>");
    int y1, m1, d1, h1, min1;
    DecodeDateTime (datetime, & y1, & m1, & d1, & h1, & min1);
    * y = y1;
    * m = m1, * d = d1, * h = h1, * mi = min1;
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::GetDateTimeElements(double datetime, int * y, int * m, int * d, int * h, int * mi)@@@StandardConverterUtility.cpp>");
}
double StandardConverterUtility :: Calculate_TdateTime_Offset (void)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::Calculate_TdateTime_Offset(void)@@@StandardConverterUtility.cpp>");
    tm timeinfo;
    timeinfo.tm_sec = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_hour = 0;
    timeinfo.tm_mday = 1;
    timeinfo.tm_mon = 0;
    timeinfo.tm_year = 70;
    timeinfo.tm_isdst = - 1;
    time_t Current = mktime (& timeinfo);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::Calculate_TdateTime_Offset(void)@@@StandardConverterUtility.cpp>");
    return double (Current) / 86400.0;
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::Calculate_TdateTime_Offset(void)@@@StandardConverterUtility.cpp>");
}
double StandardConverterUtility :: EncodeDateTime (int Year, int Month, int Day, int hour, int min)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::EncodeDateTime(int Year, int Month, int Day, int hour, int min)@@@StandardConverterUtility.cpp>");
    tm timeinfo;
    long indx = (Year - 1900) / 10;
    if (indx > 7)
    {
        indx = 7;
    }

    timeinfo.tm_sec = 0;
    timeinfo.tm_min = min;
    timeinfo.tm_hour = hour;
    timeinfo.tm_mday = Day;
    timeinfo.tm_mon = Month - 1;
    timeinfo.tm_isdst = 0;
    timeinfo.tm_year = Year + Decade_Offsets [indx] [0] - 1900;
    time_t Current = mktime (& timeinfo);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::EncodeDateTime(int Year, int Month, int Day, int hour, int min)@@@StandardConverterUtility.cpp>");
    return double (Current) / 86400.0 + Decade_Offsets [indx] [1] - Calculate_TdateTime_Offset ();
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::EncodeDateTime(int Year, int Month, int Day, int hour, int min)@@@StandardConverterUtility.cpp>");
}
void StandardConverterUtility :: DecodeDateTime (double Dttime, int * Year, int * Month, int * Day, int * Hour, int * Min)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::DecodeDateTime(double Dttime, int * Year, int * Month, int * Day, int * Hour, int * Min)@@@StandardConverterUtility.cpp>");
    long indx = 7;
    if (Dttime < 25569)
    {
        for (indx = 6; indx >= 0; -- indx) {
            if (! (Dttime < Decade_Offsets [indx] [3]))
            {
                break;
            }

        }
    }

    long Fix = (long) roundl ((Dttime - Decade_Offsets [indx] [1]) * 86400.0);
    time_t rawtime = (time_t) Fix;
    tm * timeinfo = gmtime (& rawtime);
    if (timeinfo != NULL)
    {
        * Year = timeinfo -> tm_year - Decade_Offsets [indx] [0] + 1900;
        * Month = timeinfo -> tm_mon + 1;
        * Day = timeinfo -> tm_mday;
        * Hour = timeinfo -> tm_hour;
        * Min = timeinfo -> tm_min;
    }

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::DecodeDateTime(double Dttime, int * Year, int * Month, int * Day, int * Hour, int * Min)@@@StandardConverterUtility.cpp>");
}
double StandardConverterUtility :: DateTimeDt (void)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::DateTimeDt(void)@@@StandardConverterUtility.cpp>");
    time_t Currently;
    time (& Currently);

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::DateTimeDt(void)@@@StandardConverterUtility.cpp>");
    return double (Currently) / 86400.0 + Decade_Offsets [7] [1] - Calculate_TdateTime_Offset ();
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::DateTimeDt(void)@@@StandardConverterUtility.cpp>");
}
std :: string StandardConverterUtility :: FormatDateTime (std :: string fmt, double datetime)
{
InstrumentLogger::instance()->log_instrument_log("<StandardConverterUtility::FormatDateTime(std :: string fmt, double datetime)@@@StandardConverterUtility.cpp>");
    int y, m, d, h, min;
    DecodeDateTime (datetime, & y, & m, & d, & h, & min);
    string m1 = to_string (m), d1 = to_string (d), h1 = to_string (h), min1 = to_string (min);
    if (m < 10)
    {
        m1 = "0" + m1;
    }

    if (d < 10)
    {
        d1 = "0" + d1;
    }

    if (h < 10)
    {
        h1 = "0" + h1;
    }

    if (min < 10)
    {
        min1 = "0" + min1;
    }

    if (fmt == "yyyy-mm-dd hh:mm ")
    {

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::FormatDateTime(std :: string fmt, double datetime)@@@StandardConverterUtility.cpp>");
        return to_string (y) + " " + m1 + " " + d1 + " " + h1 + " " + min1;
    }

    else
    if (fmt == "ISO")
    {

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::FormatDateTime(std :: string fmt, double datetime)@@@StandardConverterUtility.cpp>");
        return to_string (y) + "-" + m1 + "-" + d1 + "T" + h1 + ":" + min1;
    }

InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::FormatDateTime(std :: string fmt, double datetime)@@@StandardConverterUtility.cpp>");
    return "";
InstrumentLogger::instance()->log_instrument_log("</StandardConverterUtility::FormatDateTime(std :: string fmt, double datetime)@@@StandardConverterUtility.cpp>");
}