#include "ReportStream.h"
#include "InstrumentLogger.h"

ReportStream :: ReportStream (std :: string reportName)
{
InstrumentLogger::instance()->log_instrument_log("<ReportStream::ReportStream(std :: string reportName)@@@ReportStream.cpp>");
    this -> reportFileStream = new std :: basic_ofstream < char, std :: char_traits < char >> ();
    this -> reportFileStream -> open (reportName);
    if (! this -> reportFileStream -> is_open ())
    {
        CRHMException e = CRHMException ("Cannot open file " + reportName + " to save report.", TExcept :: ERR);
        CRHMLogger :: instance () -> log_run_error (e);
    }

InstrumentLogger::instance()->log_instrument_log("</ReportStream::ReportStream(std :: string reportName)@@@ReportStream.cpp>");
}
void ReportStream :: OutputHeaders (CRHMmain * instance)
{
InstrumentLogger::instance()->log_instrument_log("<ReportStream::OutputHeaders(CRHMmain * instance)@@@ReportStream.cpp>");
    std :: list < std :: string > * headerLines = new std :: list < std :: string > ();
    if (instance -> OutputFormat == OUTPUT_FORMAT :: STD)
    {
        headerLines = this -> RprtHeader (instance);
    }

    else
    if (instance -> OutputFormat == OUTPUT_FORMAT :: OBS)
    {
        headerLines = this -> RprtHeaderObs (instance);
    }

    else
    {
        CRHMException e = CRHMException ("No output format was specified defaulting to STD.", TExcept :: WARNING);
        CRHMLogger :: instance () -> log_run_error (e);
        headerLines = this -> RprtHeader (instance);
    }

    for (std :: list < std :: string > :: iterator it = headerLines -> begin (); it != headerLines -> end (); it ++) {
        * (this -> reportFileStream) << (it -> c_str ());
        * (this -> reportFileStream) << ("\n");
    }
    this -> reportFileStream -> flush ();
InstrumentLogger::instance()->log_instrument_log("</ReportStream::OutputHeaders(CRHMmain * instance)@@@ReportStream.cpp>");
}
void ReportStream :: SendTimeStepToReport (CRHMmain * instance)
{
InstrumentLogger::instance()->log_instrument_log("<ReportStream::SendTimeStepToReport(CRHMmain * instance)@@@ReportStream.cpp>");
    long index = Global :: DTindx - Global :: DTmin;
    std :: string Sx = FloatToStrF (instance -> cdSeries [0] -> XValue (index), TFloatFormat :: ffGeneral, 10, 0);
    Sx = StandardConverterUtility :: GetDateTimeInStringForOutput (instance -> cdSeries [0] -> XValue (index));
    switch (Global :: TimeFormat) {
    case TIMEFORMAT :: MS:
        Sx = FloatToStrF (instance -> cdSeries [0] -> XValue (index), TFloatFormat :: ffGeneral, 10, 0);
        break;
    case TIMEFORMAT :: YYYYMMDD:
        Sx = StandardConverterUtility :: FormatDateTime ("yyyy-mm-dd hh:mm ", instance -> cdSeries [0] -> XValue (index));
        break;
    case TIMEFORMAT :: ISO:
        Sx = StandardConverterUtility :: FormatDateTime ("ISO", instance -> cdSeries [0] -> XValue (index));
        break;
    default:
        break;
    }
    for (int vv = 0; vv < instance -> SeriesCnt; ++ vv) {
        if (instance -> cdSeries [0] -> Count () == instance -> cdSeries [vv] -> Count ())
        {
            ClassVar * thisVar = instance -> cdSeries [vv] -> Tag;
            int prec = 7;
            if (thisVar -> varType == TVar :: Int || thisVar -> varType == TVar :: ReadI)
            {
                prec = 7;
            }

            std :: string Sy = FloatToStrF (instance -> cdSeries [vv] -> YValue (index), TFloatFormat :: ffGeneral, prec, 10);
            Sx = Sx + instance -> Delimiter + Sy;
        }

    }
    * (this -> reportFileStream) << (Sx);
    * (this -> reportFileStream) << ("\n");
InstrumentLogger::instance()->log_instrument_log("</ReportStream::SendTimeStepToReport(CRHMmain * instance)@@@ReportStream.cpp>");
}
void ReportStream :: CloseStream ()
{
InstrumentLogger::instance()->log_instrument_log("<ReportStream::CloseStream()@@@ReportStream.cpp>");
    this -> reportFileStream -> flush ();
    this -> reportFileStream -> close ();
InstrumentLogger::instance()->log_instrument_log("</ReportStream::CloseStream()@@@ReportStream.cpp>");
}
std :: list < std :: string > * ReportStream :: RprtHeader (CRHMmain * instance)
{
InstrumentLogger::instance()->log_instrument_log("<ReportStream::RprtHeader(CRHMmain * instance)@@@ReportStream.cpp>");
    std :: string Sx;
    std :: string Sy;
    std :: list < std :: string > * headerLines = new std :: list < std :: string > ();
    Sx = "time";
    for (int vv = 0; vv < instance -> SeriesCnt; ++ vv) {
        std :: string S = instance -> cdSeries [vv] -> Title;
        Sx += instance -> Delimiter + S;
    }
    headerLines -> push_back (Sx);
    Sx = "units";
    for (int vv = 0; vv < instance -> SeriesCnt; ++ vv) {
        ClassVar * thisVar = instance -> cdSeries [vv] -> Tag;
        std :: string S = thisVar -> units;
        Sx += instance -> Delimiter + S;
    }
    headerLines -> push_back (Sx);

InstrumentLogger::instance()->log_instrument_log("</ReportStream::RprtHeader(CRHMmain * instance)@@@ReportStream.cpp>");
    return headerLines;
InstrumentLogger::instance()->log_instrument_log("</ReportStream::RprtHeader(CRHMmain * instance)@@@ReportStream.cpp>");
}
std :: list < std :: string > * ReportStream :: RprtHeaderObs (CRHMmain * instance)
{
InstrumentLogger::instance()->log_instrument_log("<ReportStream::RprtHeaderObs(CRHMmain * instance)@@@ReportStream.cpp>");
    std :: string Sx;
    std :: string Sy;
    std :: list < std :: string > * headerLines = new std :: list < std :: string > ();
    headerLines -> push_back ("Future File Description");
    for (int vv = 0; vv < instance -> SeriesCnt; ++ vv) {
        ClassVar * thisVar = instance -> cdSeries [vv] -> Tag;
        Sx = instance -> cdSeries [vv] -> Title;
        Sx += string (" 1 ");
        Sx += thisVar -> units;
        headerLines -> push_back (Sx);
    }
    Sx = "###### time";
    for (int vv = 0; vv < instance -> SeriesCnt; ++ vv) {
        string S = instance -> cdSeries [vv] -> Title;
        Sx += instance -> Delimiter + S;
    }
    headerLines -> push_back (Sx);

InstrumentLogger::instance()->log_instrument_log("</ReportStream::RprtHeaderObs(CRHMmain * instance)@@@ReportStream.cpp>");
    return headerLines;
InstrumentLogger::instance()->log_instrument_log("</ReportStream::RprtHeaderObs(CRHMmain * instance)@@@ReportStream.cpp>");
}