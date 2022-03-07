#if defined (_WIN32) && ! defined (__MINGW32__)
    #include "../../vcc/stdafx.h"
#endif

#include "CRHMmain.h"

#if defined (VS_GUI)
    #include "../../vcc/gui/CRHMAboutBox.h"
#endif

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include "GlobalDll.h"
#include "ClassModule.h"
#include "../modules/newmodules/NewModules.h"
#include "MacroUnit.h"
#include "Common.h"
#include "StandardConverterUtility.h"
#include "CRHMLogger.h"
#include "InstrumentLogger.h"

Administer AdminMacro ("03/24/06", "Macro");
using namespace std; using namespace CRHM; extern string AKAstrings [];
typedef pair < string, string > PairDllModule;
typedef multimap < string, string > TDllModule;
typedef std :: shared_ptr < Classinfo > Pinfo;
typedef pair < string, Pinfo > Pairinfo;
typedef multimap < string, Pinfo > paras;
typedef pair < string, ClassPar * > PairPar;
typedef multimap < string, ClassPar * > GrpParas;
ClassVar * VarFind (string name);
ClassPar * ParFind (string name);
string Version = "Version: 4.7_16";
CRHMmain * CRHMmain :: instance = 0;

bool CRHMmain :: getAutoRun ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getAutoRun()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAutoRun()@@@CRHMmain.cpp>");
    return this -> AutoRun;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAutoRun()@@@CRHMmain.cpp>");
}
void CRHMmain :: setAutoRun (bool set)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setAutoRun(bool set)@@@CRHMmain.cpp>");
    this -> AutoRun = set;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setAutoRun(bool set)@@@CRHMmain.cpp>");
}
bool CRHMmain :: getAutoExit ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getAutoExit()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAutoExit()@@@CRHMmain.cpp>");
    return this -> AutoExit;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAutoExit()@@@CRHMmain.cpp>");
}
void CRHMmain :: setAutoExit (bool set)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setAutoExit(bool set)@@@CRHMmain.cpp>");
    this -> AutoExit = set;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setAutoExit(bool set)@@@CRHMmain.cpp>");
}
bool CRHMmain :: getFinishedRun ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getFinishedRun()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getFinishedRun()@@@CRHMmain.cpp>");
    return this -> finishedRun;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getFinishedRun()@@@CRHMmain.cpp>");
}
bool CRHMmain :: getReportAll ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getReportAll()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getReportAll()@@@CRHMmain.cpp>");
    return this -> ReportAll;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getReportAll()@@@CRHMmain.cpp>");
}
void CRHMmain :: setReportAll (bool set)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setReportAll(bool set)@@@CRHMmain.cpp>");
    this -> ReportAll = set;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setReportAll(bool set)@@@CRHMmain.cpp>");
}
CRHMmain * CRHMmain :: getInstance ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getInstance()@@@CRHMmain.cpp>");
    if (instance == 0)
    {
        instance = new CRHMmain (NULL);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getInstance()@@@CRHMmain.cpp>");
    return instance;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getInstance()@@@CRHMmain.cpp>");
}
CRHMmain :: CRHMmain (CRHMArguments * arguments)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::CRHMmain(CRHMArguments * arguments)@@@CRHMmain.cpp>");
    if (arguments == NULL)
    {
        Global :: TimeFormat = TIMEFORMAT :: ISO;

        #if defined (VS_GUI)
            this -> OutputFormat = OUTPUT_FORMAT :: OBS;
        #endif

        #if ! defined (VS_GUI)
            this -> OutputFormat = OUTPUT_FORMAT :: STD;
        #endif

        this -> OutputName = "";
        this -> Delimiter = '\t';
        this -> ObsFileDirectory = "";
        this -> ShowProgress = false;
        this -> UpdateProgress = 7;
    }

    else
    {
        Global :: TimeFormat = arguments -> get_time_format ();
        this -> OutputFormat = arguments -> get_output_format ();
        this -> OutputName = arguments -> get_output_name ();
        this -> Delimiter = arguments -> get_delimiter ();
        this -> ObsFileDirectory = arguments -> get_obs_file_directory ();
        this -> ShowProgress = arguments -> get_show_progress ();
        this -> UpdateProgress = arguments -> get_update_progress ();
    }

    FormCreate ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::CRHMmain(CRHMArguments * arguments)@@@CRHMmain.cpp>");
}
CRHMmain :: ~CRHMmain ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::~CRHMmain()@@@CRHMmain.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::~CRHMmain()@@@CRHMmain.cpp>");
}
double CRHMmain :: GetStartDate ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetStartDate()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetStartDate()@@@CRHMmain.cpp>");
    return StartDatePicker;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetStartDate()@@@CRHMmain.cpp>");
}
void CRHMmain :: setStartDate (double sdate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setStartDate(double sdate)@@@CRHMmain.cpp>");
    StartDatePicker = sdate;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setStartDate(double sdate)@@@CRHMmain.cpp>");
}
double CRHMmain :: GetEndDate ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetEndDate()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetEndDate()@@@CRHMmain.cpp>");
    return EndDatePicker;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetEndDate()@@@CRHMmain.cpp>");
}
void CRHMmain :: setEndDate (double edate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setEndDate(double edate)@@@CRHMmain.cpp>");
    EndDatePicker = edate;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setEndDate(double edate)@@@CRHMmain.cpp>");
}
std :: list < std :: pair < std :: string, ClassVar * >> * CRHMmain :: getSelectedVariables ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getSelectedVariables()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedVariables()@@@CRHMmain.cpp>");
    return SelectedVariables;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedVariables()@@@CRHMmain.cpp>");
}
void CRHMmain :: setSelectedVariables (std :: list < std :: pair < std :: string, ClassVar * >> * t)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setSelectedVariables(std :: list < std :: pair < std :: string, ClassVar * >> * t)@@@CRHMmain.cpp>");
    SelectedVariables = t;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setSelectedVariables(std :: list < std :: pair < std :: string, ClassVar * >> * t)@@@CRHMmain.cpp>");
}
std :: list < std :: pair < std :: string, TSeries * >> * CRHMmain :: getSelectedObservations ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getSelectedObservations()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedObservations()@@@CRHMmain.cpp>");
    return SelectedObservations;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedObservations()@@@CRHMmain.cpp>");
}
void CRHMmain :: setSelectedObservatoions (std :: list < std :: pair < std :: string, TSeries * >> * t)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setSelectedObservatoions(std :: list < std :: pair < std :: string, TSeries * >> * t)@@@CRHMmain.cpp>");
    SelectedObservations = t;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setSelectedObservatoions(std :: list < std :: pair < std :: string, TSeries * >> * t)@@@CRHMmain.cpp>");
}
ClassVar * CRHMmain :: GetObjectOfVariable (string vname)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObjectOfVariable(string vname)@@@CRHMmain.cpp>");
    int pos = vname.find_first_of ('(');
    std :: string name = vname.substr (0, pos);
    std :: map < std :: string, ClassVar * > :: iterator it = this -> AllVariables -> find (name);
    if (it != this -> AllVariables -> end ())
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObjectOfVariable(string vname)@@@CRHMmain.cpp>");
        return it -> second;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObjectOfVariable(string vname)@@@CRHMmain.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObjectOfVariable(string vname)@@@CRHMmain.cpp>");
}
ClassVar * CRHMmain :: GetObjectOfObservation (string vname)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObjectOfObservation(string vname)@@@CRHMmain.cpp>");
    int pos = vname.find_first_of ('(');
    std :: string name = vname.substr (0, pos);
    std :: map < std :: string, ClassVar * > :: iterator it = this -> AllObservations -> find (name);
    if (it != this -> AllObservations -> end ())
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObjectOfObservation(string vname)@@@CRHMmain.cpp>");
        return it -> second;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObjectOfObservation(string vname)@@@CRHMmain.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObjectOfObservation(string vname)@@@CRHMmain.cpp>");
}
void CRHMmain :: BldModelClick ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::BldModelClick()@@@CRHMmain.cpp>");
    ProjectOpen = true;
    InitModules ();
    SqueezeParams ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BldModelClick()@@@CRHMmain.cpp>");
}
bool CRHMmain :: DoPrjOpen (string OpenNamePrj, string PD)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
    this -> finishedRun = false;
    OpenProjectPath = OpenNamePrj;
    MapPar :: iterator itPar;
    ClassPar * thisPar = NULL;
    ClassVar * thisVar;
    ifstream DataFile;
    unsigned short Variation;
    std :: string module, param, Descrip, Line, name;
    std :: string S, s;
    std :: string SS;
    DataFile.open (OpenNamePrj.c_str ());
    if (! DataFile)
    {
        Common :: Message ("cannot open file", "File Error");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
        return false;
    }

    ProjectDirectory = GetCurrentDir ();
    Dt0 = time (NULL);
    bool Prj = Common :: lowercase (OpenNamePrj).find (".prj") != string :: npos;
    getline (DataFile, Descrip);
    DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
    getline (DataFile, Line);
    Global :: MacroModulesList -> clear ();
    this -> setAutoRun (false);
    this -> setAutoExit (false);
    try {
        do {
            DataFile >> S;
            if (DataFile.eof ())
            {
                break;
            }

            DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
            getline (DataFile, Line);
            if (S == "AKAs:")
            {
                string module, type, name, alias, source;
                while (! DataFile.eof ()) {
                    DataFile >> type;
                    if (type [1] == '#')
                    {
                        break;
                    }

                    DataFile >> module >> name >> alias;
                    TAKA Type = AKAtype (type);
                    if (Type == TAKA :: VARG || Type == TAKA :: OBSR || Type == TAKA :: OBSF)
                    {
                        DataFile >> source;
                        alias += ' ' + source;
                    }

                    if (Type != TAKA :: AKAERROR)
                    {
                        Pairstr2 Item = Pairstr2 (type + " " + module + " " + name, alias);
                        Global :: MapAKA.insert (Item);
                    }

                    if (DataFile.eof ())
                    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
                        return true;
                    }

                }
            }

            else
            if (S == "Macros:")
            {
                getline (DataFile, S);
                while (S [0] != '#') {
                    string sub = "";
                    size_t pos = 1;
                    while (pos < S.length () && S [pos] != '\'') sub.push_back (S [pos ++]);
                    Global :: MacroModulesList -> push_back (sub);
                    getline (DataFile, S);
                }
                MacroLoad ();
            }

            else
            if (S == "Observations:")
            {
                getline (DataFile, S);
                while (S [0] != '#') {
                    if (this -> ObsFileDirectory == "")
                    {
                        SS = S;
                    }

                    else
                    {
                        SS = this -> ObsFileDirectory + S;
                    }

                    int l = SS.length ();
                    if (SS [l - 1] == '\r')
                    {
                        SS [l - 1] = '\0';
                    }

                    if (FindFileName (SS))
                    {
                        OpenNameObs = SS;
                        bool test = OpenObsFile (SS);
                    }

                    else
                    {
                        Common :: Message (SS.c_str (), "Cannot find observation file. Exiting.");
                        CRHMException Except ("Cannot find observation file.", TExcept :: ERR);
                        LogError (Except);

                        #ifdef VS_GUI

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
                            return false;
                        #endif

                        exit (1);
                    }

                    getline (DataFile, S);
                }
            }

            else
            if (S == "Dates:")
            {

                int D [3]
                {
                }
                ;
                double DT;
                for (int ii = 0; ii < 3; ii ++)
                    DataFile >> D [ii];
                DT = StandardConverterUtility :: EncodeDateTime ((int) D [0], (int) D [1], (int) D [2], 0, 0);
                StartDatePicker = DT;
                int c;
                while ((c = DataFile.peek (), c == 32)) {
                    DataFile.get ();
                    c = DataFile.peek ();
                }
                if (iswdigit (c) && ObsFilesList -> size () == 0)
                {
                    DataFile >> Global :: Freq;
                    Global :: Interval = 1.0 / Global :: Freq;
                }

                else
                {
                    DataFile.ignore (256, '\n');
                }

                for (int ii = 0; ii < 3; ii ++)
                    DataFile >> D [ii];
                DT = StandardConverterUtility :: EncodeDateTime ((int) D [0], (int) D [1], (int) D [2], 0, 0);
                EndDatePicker = DT;
                DataFile >> S;
            }

            else
            if (S == "Modules:")
            {
                Global :: OurModulesList -> clear ();
                for (;;) {
                    getline (DataFile, S);
                    if (S [0] == '#')
                    {
                        break;
                    }

                    bool InGrp = false;
                    long idx = S.find ('+');
                    if (idx != - 1)
                    {
                        S = S.substr (idx + 1);
                        InGrp = true;
                    }

                    idx = S.find (' ');
                    s = S.substr (0, idx);
                    idx = S.find ('#');
                    if (idx != - 1)
                    {
                        Variation = (unsigned short) pow (2, S [idx + 1] - char ('1'));
                        s = S.substr (0, idx);
                    }

                    else
                    {
                        Variation = 0;
                    }

                    if (! InGrp)
                    {
                        Global :: OurModulesVariation -> push_back (std :: pair < std :: string, unsigned short > (s, Variation));
                    }

                    idx = S.find (' ');
                    S = S.substr (idx + 1);
                    idx = S.rfind (' ');
                    S = S.substr (0, idx);
                    transform (S.begin (), S.end (), S.begin (), :: toupper);
                    idx = S.rfind (".DLL");
                }
                for (std :: list < std :: pair < std :: string, unsigned short >> :: iterator it = Global :: OurModulesVariation -> begin (); it != Global :: OurModulesVariation -> end (); it ++) {
                    string Name = it -> first;
                    int jj = Global :: AllModulesList -> count (Name);
                    if (jj == 0)
                    {
                        CRHMException Except ("Unknown Module: " + string (Name.c_str ()), TExcept :: ERR);
                        Common :: Message (Except.Message.c_str (), "Unknown Module: incorrect CRHM version or DLL not loaded");
                        LogError (Except);
                        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                            if (it -> first == Name)
                            {
                                Global :: OurModulesList -> erase (it);
                                break;
                            }

                        }
                        Global :: OurModulesVariation -> erase (it);
                        DataFile.seekg (0, ios_base :: end);
                    }

                    else
                    {
                        Variation = it -> second;
                        Global :: AllModulesList -> find (Name) -> second -> variation = Variation;
                        Global :: OurModulesList -> push_back (std :: pair < std :: string, ClassModule * > (Name, Global :: AllModulesList -> find (Name) -> second));
                    }

                }
                InitModules ();
            }

            else
            if (S == "Dimensions:")
            {
                DataFile >> S;
                long dim;
                while (S [0] != '#') {
                    DataFile >> dim;
                    if (S == "nhru")
                    {
                        Global :: nhru = dim;
                        Global :: maxhru = dim;
                    }

                    else
                    if (S == "nobs")
                    {
                        Global :: nobs = dim;
                        Global :: maxobs = dim;
                    }

                    else
                    if (S == "nlay")
                    {
                        Global :: nlay = dim;
                        Global :: maxlay = dim;
                    }

                    DataFile >> S;
                }
            }

            else
            if (S == "Parameters:")
            {
                int c;
                long Cols, Rows;
                bool TooFewHRUs = false;
                string ss;
                while (! DataFile.eof ()) {
                    DataFile >> module;
                    if (module [1] == '#')
                    {
                        break;
                    }

                    DataFile >> param;
                    if (DataFile.eof ())
                    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
                        return true;
                    }

                    DataFile.ignore ((numeric_limits < streamsize > :: max) (), '\n');
                    S = "";
                    do {
                        getline (DataFile, ss);
                        S += ss + ' ';
                        while (c = DataFile.peek (), iscntrl (c) || isspace (c)) DataFile.get ();
                    }
                    while (c = DataFile.peek (), ! isalpha (c) && c != '#');
                    string Sc = S;
                    string :: iterator pos;
                    bool inField = false;
                    for (pos = Sc.begin (); pos != Sc.end (); ++ pos) {
                        if (* pos == '\'')
                        {
                            inField = ! inField;
                        }

                        if (inField && * pos == ' ')
                        {
                            * pos = '_';
                        }

                    }
                    istringstream instr;
                    instr.clear ();
                    instr.str (Sc);
                    Cols = 0;
                    for (;;) {
                        instr >> s;
                        if (instr.fail ())
                        {
                            break;
                        }

                        ++ Cols;
                    }
                    if (module == "Shared")
                    {
                        MapPar :: iterator itPar;
                        for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); ++ itPar) {
                            thisPar = (* itPar).second;
                            if (thisPar -> param == param)
                            {
                                if (thisPar -> dim == Cols / thisPar -> lay)
                                {
                                    break;
                                }

                                else
                                if (thisPar -> varType == TVar :: Txt && thisPar -> dimen < TDim :: NHRU)
                                {
                                    break;
                                }

                                else
                                if (thisPar -> param == "obs_elev" || thisPar -> param == "soil_withdrawal")
                                {
                                    break;
                                }

                                else
                                {
                                    if ((thisPar -> param == param) && (thisPar -> dim == Cols / thisPar -> dim))
                                    {
                                        break;
                                    }

                                    else
                                    {
                                        thisPar = NULL;
                                    }

                                }

                            }

                            else
                            {
                                thisPar = NULL;
                            }

                        }
                    }

                    else
                    {
                        thisPar = ClassParFind (module, param);
                        if (thisPar)
                        {
                            module = thisPar -> module.c_str ();
                        }

                    }

                    if (thisPar)
                    {
                        ClassPar * newPar = new ClassPar (* thisPar);
                        newPar -> module = module;
                        if (thisPar -> varType == TVar :: Txt)
                        {
                            Common :: tokenizeString (S.c_str (), newPar -> Strings);
                        }

                        else
                        {
                            Rows = 0;
                            istringstream instr;
                            instr.clear ();
                            instr.str (S);
                            for (int jj = 0; jj < thisPar -> lay; ++ jj) {
                                Cols = 0;
                                for (int ii = 0; ii < newPar -> dim; ++ ii) {
                                    if (newPar -> varType == TVar :: Float)
                                    {
                                        double x;
                                        instr >> x;
                                        if (instr.fail ())
                                        {
                                            break;
                                        }

                                        newPar -> layvalues [jj] [ii] = x;
                                    }

                                    else
                                    if (newPar -> varType == TVar :: Int)
                                    {
                                        long x;
                                        instr >> x;
                                        if (instr.fail ())
                                        {
                                            break;
                                        }

                                        newPar -> ilayvalues [jj] [ii] = x;
                                    }

                                    ++ Cols;
                                }
                                if (instr.fail ())
                                {
                                    if (! TooFewHRUs && newPar -> module != "Shared")
                                    {
                                        if (newPar -> lay > Global :: nlay)
                                        {
                                            Global :: nlay = newPar -> lay;
                                        }

                                        TooFewHRUs = true;
                                    }

                                    if (! (Cols == 0 && newPar -> lay > Rows))
                                    {
                                        for (int ii = Cols; ii < newPar -> dim; ++ ii) {
                                            if (newPar -> varType == TVar :: Float)
                                            {
                                                newPar -> layvalues [Rows] [ii] = newPar -> layvalues [Rows] [ii - 1];
                                            }

                                            else
                                            {
                                                newPar -> ilayvalues [Rows] [ii] = newPar -> ilayvalues [Rows] [ii - 1];
                                            }

                                        }
                                    }

                                    else
                                    {
                                        for (int jjj = Rows; jjj < thisPar -> lay; ++ jjj) {
                                            for (int ii = 0; ii < newPar -> dim; ++ ii) {
                                                if (newPar -> varType == TVar :: Float)
                                                {
                                                    newPar -> layvalues [jjj] [ii] = newPar -> layvalues [jjj - 1] [ii];
                                                }

                                                else
                                                {
                                                    newPar -> ilayvalues [jjj] [ii] = newPar -> ilayvalues [jjj - 1] [ii];
                                                }

                                            }
                                        }
                                    }

                                }

                                ++ Rows;
                            }
                        }

                        if (module == "Shared")
                        {
                            SetSharedParams (newPar);
                            delete newPar;
                        }

                        else
                        {
                            ClassParSet (newPar);
                        }

                    }

                    else
                    {
                        if (param != "Use_Observations_As_Supplied")
                        {
                            CRHMException Except ("Unknown Module Parameter: " + module + " -> " + param + " in " + OpenNamePrj, TExcept :: ERR);
                            LogError (Except);
                        }

                        while (c = DataFile.peek (), ! isalpha (c) && c != '#') DataFile.ignore (256, '\n');
                    }

                    long cnt = Global :: MapPars.size ();
                    DataFile.clear ();
                }
                SqueezeParams ();
            }

            else
            if (S == "Display_Variable:")
            {
                while (! DataFile.eof ()) {
                    DataFile >> module;
                    if (module [1] == '#')
                    {
                        break;
                    }

                    DataFile >> name;
                    if (DataFile.eof ())
                    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
                        return true;
                    }

                    S = string (module) + ' ' + string (name);
                    long Index;
                    string comma;
                    thisVar = ClassVarFind (S);
                    if (thisVar)
                    {
                        for (;;) {
                            DataFile >> Index;
                            if (DataFile.fail ())
                            {
                                break;
                            }

                            if (Index < 0)
                            {
                                Index = labs (Index);
                                thisVar -> TchrtOpt = 1;
                            }

                            if (DataFile.peek () != ',')
                            {
                                SS = thisVar -> name + "(" + Common :: longtoStr (Index) + ")";
                            }

                            else
                            {
                                DataFile >> comma;
                                SS = thisVar -> name + "(" + Common :: longtoStr (Index) + comma + ")";
                            }

                            bool listContainsSS = false;
                            for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator listIt = SelectedVariables -> begin (); listIt != SelectedVariables -> end (); listIt ++) {
                                if (listIt -> first == SS)
                                {
                                    listContainsSS = true;
                                }

                            }
                            if (listContainsSS == false && Index <= thisVar -> dim)
                            {
                                SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (SS, thisVar));
                            }

                        }
                    }

                    else
                    {
                        CRHMException Except ("Unknown Variable " + S + " in " + string (OpenNamePrj.c_str ()), TExcept :: ERR);
                        Common :: Message (Except.Message.c_str (), "Unknown Variable in project file");
                        LogError (Except);
                        DataFile.ignore (256, '\n');
                    }

                    DataFile.clear ();
                }
            }

            else
            if (S == "Display_Observation:")
            {
                while (! DataFile.eof ()) {
                    DataFile >> module;
                    if (module [1] == '#')
                    {
                        break;
                    }

                    DataFile >> name;
                    if (DataFile.eof ())
                    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
                        return true;
                    }

                    string Kind;
                    long Index;
                    S = string (module) + ' ' + string (name);
                    thisVar = ClassVarFind (S);
                    if (thisVar && thisVar -> FileData != NULL)
                    {
                        for (int ii = 0; ii < 100; ii ++) {
                            DataFile >> Index >> Kind;
                            if (DataFile.fail ())
                            {
                                break;
                            }

                            if (Kind == "_obs")
                            {
                                Kind = "";
                            }

                            SS = thisVar -> name + "(" + Common :: longtoStr (labs (Index)) + ")" + Kind;
                            bool selectedObservationsContainsSS = false;
                            for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = SelectedObservations -> begin (); it != SelectedObservations -> end (); it ++) {
                                if (it -> first == SS)
                                {
                                    selectedObservationsContainsSS = true;
                                }

                            }
                            if (selectedObservationsContainsSS != true)
                            {
                                TSeries * cdSeries = NULL;
                                if (thisVar -> FileData -> Times == NULL)
                                {
                                    double Dif = EndDatePicker - StartDatePicker;
                                    cdSeries = new TSeries ();
                                    cdSeries -> Tag = thisVar;
                                    cdSeries -> Title = SS;
                                }

                                SelectedObservations -> push_back (std :: pair < std :: string, TSeries * > (SS, cdSeries));
                            }

                        }
                    }

                    else
                    {
                        CRHMException Except ("Unknown Variable " + S + " in " + string (OpenNamePrj.c_str ()), TExcept :: ERR);
                        Common :: Message (Except.Message.c_str (), "Unknown Variable in project file");
                        LogError (Except);
                        DataFile.ignore (256, '\n');
                    }

                    DataFile.clear ();
                }
            }

            else
            if (S == "Initial_State")
            {
                getline (DataFile, S);
                if (S [0] != '#')
                {
                    SS = S;
                    int l = SS.length ();
                    if (SS [l - 1] == '\r')
                    {
                        SS [l - 1] = '\0';
                    }

                    if (FindFileName (SS))
                    {
                        OpenNameState = SS;
                        OpenStateFlag = true;
                    }

                    else
                    {
                        OpenNameState = "";
                    }

                    DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
                    DataFile >> S;
                }

            }

            else
            if (S == "Final_State")
            {
                getline (DataFile, S);
                if (S [1] != '#')
                {
                    SS = S;
                    int l = SS.length ();
                    if (SS [l - 1] == '\r')
                    {
                        SS [l - 1] = '\0';
                    }

                    SaveStateFileName = SS;
                    SaveStateFlag = true;
                    DataFile >> S;
                }

                else
                {
                    SaveStateFileName = "";
                }

            }

            else
            if (S == "Log_Last")
            {
                this -> setReportAll (false);
            }

            else
            if (S == "Log_All")
            {
                this -> setReportAll (true);
            }

            else
            if (S == "Auto_Run")
            {
                this -> setAutoRun (true);
            }

            else
            if (S == "Auto_Exit")
            {
                this -> setAutoExit (true);
            }

            else
            if (S == "TChart:")
            {
                while (! DataFile.eof ()) {
                    getline (DataFile, S);
                    if (DataFile.eof ())
                    {
                        break;
                    }

                    if (S [0] == '#')
                    {
                        break;
                    }

                }
            }

        }
        while (! DataFile.eof ());
    }
    catch (CRHMException Except) {
        Common :: Message (Except.Message.c_str (), "Loading project Error");
        DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
        return false;
    }
    DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain.cpp>");
}
void CRHMmain :: SetSharedParams (ClassPar * basinPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SetSharedParams(ClassPar * basinPar)@@@CRHMmain.cpp>");
    ClassPar * thisPar;
    MapPar :: iterator itPar;
    for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); ++ itPar) {
        thisPar = (* itPar).second;
        if (basinPar == thisPar)
        {
            continue;
        }

        if (thisPar -> param == basinPar -> param && thisPar -> dim == basinPar -> dim)
        {
            thisPar -> Change (* basinPar);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SetSharedParams(ClassPar * basinPar)@@@CRHMmain.cpp>");
}
void CRHMmain :: FormCreate ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FormCreate()@@@CRHMmain.cpp>");
    Global :: BuildFlag = TBuild :: BUILD;
    Global :: maxhru = 1;
    Global :: maxlay = 1;
    Global :: maxobs = 1;
    Global :: Freq = 48;
    Global :: Interval = 1.0 / Global :: Freq;
    cdSeries = NULL;
    time_t Dt = time (NULL);
    OpenStateFlag = false;
    Global :: nhru = Global :: maxhru;
    Global :: nobs = Global :: maxobs;
    Global :: nlay = Global :: maxlay;
    Global :: OBS_AS_IS = false;
    ObsFilesList = new std :: list < std :: pair < std :: string, ClassData * >> ();
    ProjectList = new std :: list < std :: string >;
    Global :: AllModulesList = new std :: map < std :: string, ClassModule * >;
    Global :: OurModulesList = new std :: list < std :: pair < std :: string, ClassModule * >>;
    Global :: OurModulesVariation = new std :: list < std :: pair < std :: string, unsigned short >>;
    Global :: ModuleBitSet = new std :: set < std :: string >;
    Global :: MacroModulesList = new std :: vector < std :: string >;
    Global :: AllModelsList = new std :: list < std :: pair < std :: string, int >> ();
    Global :: ModelModulesList = new std :: list < std :: pair < std :: string, Administer * >> ();
    Global :: OurHelpList = NULL;
    Global :: PendingDLLModuleList = new std :: list < std :: pair < std :: string, ClassModule * >> ();
    Global :: ReportList = NULL;
    Global :: DeclRootList = new std :: list < std :: string > ();
    AllVariables = new std :: map < std :: string, ClassVar * > ();
    AllObservations = new std :: map < std :: string, ClassVar * > ();
    SelectedVariables = new std :: list < std :: pair < std :: string, ClassVar * >> ();
    SelectedObservations = new std :: list < std :: pair < std :: string, TSeries * >> ();
    MoveModulesToGlobal ();
    Global :: PendingDLLModuleList -> begin () -> second -> OurAdmin -> Accept (mbYesToAll);
    ++ InitModCnt;
    Global :: OldModuleName = new std :: vector < std :: string >;
    Global :: NewModuleName = new std :: vector < std :: string >;
    std :: string oldModuleNames [] = {"long", "CanopyClearingGap2", "pbsm_WQ", "Soil_WQ", "Netrout_WQ", "Netroute_M_D_WQ"};
    Global :: OldModuleName -> insert (Global :: OldModuleName -> begin (), oldModuleNames, oldModuleNames + 6);
    std :: string newModuleNames [] = {"longVt", "CanopyClearingGap", "WQ_pbsm", "WQ_Soil", "WQ_Netroute", "WQ_Netroute_M_D"};
    Global :: NewModuleName -> insert (Global :: NewModuleName -> begin (), newModuleNames, newModuleNames + 6);

    #if ! defined NO_MODULES
        for (size_t ii = 0; ii < Global :: NewModuleName -> size (); ++ ii) {
            size_t jj = Global :: AllModulesList -> count (Global :: NewModuleName -> at (ii));
            assert (jj != 0);
        }
    #endif

    Global :: CRHMStatus = 0;
    Global :: CurrentModuleRun = - 1;
    Global :: CRHMControlSaveCnt = 0;
    Global :: HRU_OBS_DIRECT = new long * [5];
    for (int jj = 0; jj < 5; ++ jj) {
        Global :: HRU_OBS_DIRECT [jj] = new long [500];
        for (long ii = 0; ii < 500; ++ ii)
            Global :: HRU_OBS_DIRECT [jj] [ii] = ii + 1;
    }
    Global :: HRU_OBS = Global :: HRU_OBS_DIRECT;
    Global :: NaNcheck = false;
    Global :: LOGVARLOAD = false;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FormCreate()@@@CRHMmain.cpp>");
}
void CRHMmain :: InitModules (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::InitModules(void)@@@CRHMmain.cpp>");
    Global :: BuildFlag = TBuild :: DECL;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        it -> second -> nhru = Global :: nhru;
        it -> second -> decl ();
    }
    Label4Click ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::InitModules(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: Label4Click (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::Label4Click(void)@@@CRHMmain.cpp>");
    ClassVar * thisVar;
    MapVar :: iterator itVar;
    string Newname;
    AllVariables -> clear ();
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType < TVar :: Read && thisVar -> visibility == TVISIBLE :: USUAL && thisVar -> dimen != TDim :: NREB)
        {
            Newname = DeclObsName (thisVar);
            if (this -> AllVariables -> count (Newname) == 0)
            {
                this -> AllVariables -> insert (std :: pair < std :: string, ClassVar * > (Newname, thisVar));
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::Label4Click(void)@@@CRHMmain.cpp>");
}
TFun CRHMmain :: FindObservationType (string Kind)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FindObservationType(string Kind)@@@CRHMmain.cpp>");
    if (Kind == "_obs")
    {
        Kind = "";
    }

    for (int ii = (int) TFun :: FOBS; ii <= (int) TFun :: LAST; ii ++)
        if (Kind == Sstrings [ii])
        {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindObservationType(string Kind)@@@CRHMmain.cpp>");
            return (TFun) ii;
        }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindObservationType(string Kind)@@@CRHMmain.cpp>");
    return (TFun :: FOBS);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindObservationType(string Kind)@@@CRHMmain.cpp>");
}
void CRHMmain :: SqueezeParams (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SqueezeParams(void)@@@CRHMmain.cpp>");
    paras MapInfo;
    ClassPar * thisPar, * thisPar2;
    MapPar :: iterator itPar;
    itPar = Global :: MapPars.begin ();
    while (itPar != Global :: MapPars.end ()) {
        thisPar = (* itPar).second;
        string S = ((* itPar).second) -> param;
        Pairinfo Item = Pairinfo (S, Pinfo (new Classinfo (thisPar)));
        MapInfo.insert (Item);
        ++ itPar;
    }
    paras :: iterator itPar2, itPar3, itPar4;
    itPar2 = MapInfo.begin ();
    pair < paras :: iterator, paras :: iterator > range;
    GrpParas Matched;
    string Key;
    MapPar MapParsNew;
    while (itPar2 != MapInfo.end ()) {
        string S = (* itPar2).first;
        long thiscnt = MapInfo.count (S);
        if (thiscnt > 1)
        {
            range = MapInfo.equal_range (S);
            long greatestCnt = 0;
            bool first = true;
            ClassPar * SharedPar = NULL;
            for (itPar3 = range.first; itPar3 != range.second; itPar3 ++) {
                Classinfo * info3 = ((* itPar3).second).get ();
                if (info3 -> rootinfo == NULL)
                {
                    info3 -> rootinfo = info3;
                }

                thisPar = info3 -> thisPar;
                range.first ++;
                if (info3 -> matched)
                {
                    continue;
                }

                PairPar Item = PairPar (thisPar -> module, thisPar);
                Matched.insert (Item);
                for (itPar4 = range.first; itPar4 != range.second; itPar4 ++) {
                    Classinfo * info4 = ((* itPar4).second).get ();
                    if (info4 -> matched)
                    {
                        continue;
                    }

                    thisPar2 = info4 -> thisPar;
                    bool match = thisPar -> Same (* thisPar2);
                    if (match)
                    {
                        PairPar Item = PairPar (thisPar -> module, thisPar2);
                        Matched.insert (Item);
                        info4 -> matched = true;
                        if (++ info3 -> rootinfo -> cnt > greatestCnt)
                        {
                            greatestCnt = info3 -> rootinfo -> cnt;
                            Key = info3 -> rootinfo -> thisPar -> module;
                        }

                    }

                }
            }
            GrpParas :: iterator itPar5;
            if (Matched.count (Key) > 1)
            {
                pair < GrpParas :: iterator, GrpParas :: iterator > range2;
                range2 = Matched.equal_range (Key);
                bool first = true;
                for (itPar5 = range2.first; itPar5 != range2.second; itPar5 ++) {
                    thisPar = (* itPar5).second;
                    if (first)
                    {
                        thisPar -> module = "Shared";
                        PairPar Item = PairPar ("Shared " + thisPar -> param, thisPar);
                        MapParsNew.insert (Item);
                        Global :: SharedMapPars.insert (Item);
                        first = false;
                    }

                    else
                    {
                        delete thisPar;
                    }

                    (* itPar5).second = NULL;
                }
            }

            for (itPar5 = Matched.begin (); itPar5 != Matched.end (); itPar5 ++) {
                thisPar = (* itPar5).second;
                if (! thisPar)
                {
                    continue;
                }

                PairPar Item = PairPar (thisPar -> module + ' ' + thisPar -> param, thisPar);
                MapParsNew.insert (Item);
            }
            Matched.clear ();
        }

        else
        {
            Classinfo * info = ((* itPar2).second).get ();
            thisPar = info -> thisPar;
            PairPar Item = PairPar (thisPar -> module + ' ' + thisPar -> param, thisPar);
            MapParsNew.insert (Item);
        }

        MapInfo.erase (S);
        itPar2 = MapInfo.begin ();
    }
    Global :: MapPars.clear ();
    Global :: MapPars = MapParsNew;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SqueezeParams(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: SetBasinParams (ClassPar * basinPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SetBasinParams(ClassPar * basinPar)@@@CRHMmain.cpp>");
    ClassPar * thisPar;
    MapPar :: iterator itPar;
    for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); ++ itPar) {
        thisPar = (* itPar).second;
        if (basinPar == thisPar)
        {
            continue;
        }

        if (thisPar -> param == basinPar -> param && thisPar -> dim == basinPar -> dim)
        {
            thisPar -> Change (* basinPar);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SetBasinParams(ClassPar * basinPar)@@@CRHMmain.cpp>");
}
void CRHMmain :: MacroClick (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::MacroClick(void)@@@CRHMmain.cpp>");
    if (InitMacroCnt && InitModCnt)
    {
        -- InitModCnt;
        InitMacroCnt = 0;
    }

    ListBoxMacroClear ();
    AdminMacro.MacroClear ();
    MacroLoad ();
    AdminMacro.MacroUpdate ();
    InitModules ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::MacroClick(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: ListBoxMacroClear ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ListBoxMacroClear()@@@CRHMmain.cpp>");
    ClassVar * thisVar;
    if (SeriesCnt <= 0)
    {
        SelectedVariables -> clear ();
    }

    else
    {
        string serTitle;
        int jj;
        SeriesCnt = SelectedVariables -> size ();
        cdSeries = new TSeries * [SeriesCnt];
        int Cnt = Global :: DTmax - Global :: DTmin;
        for (int ii = 0; ii < SeriesCnt; ++ ii)
            cdSeries [ii] = new TSeries ();
        for (jj = 0; jj < SeriesCnt; jj ++) {
            serTitle = cdSeries [jj] -> Title;
        }
        bool listContainsSerTitle = false;
        std :: list < std :: pair < std :: string, ClassVar * >> :: iterator positionOfSerTitle;
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator listIt = SelectedVariables -> begin (); listIt != SelectedVariables -> end (); listIt ++) {
            if (listIt -> first == serTitle)
            {
                listContainsSerTitle = true;
                positionOfSerTitle = listIt;
            }

        }
        if (listContainsSerTitle == true)
        {
            thisVar = positionOfSerTitle -> second;
            if (thisVar -> DLLName == "Macro")
            {
                for (int kk = jj + 1; kk < SeriesCnt; ++ kk) {
                    cdSeries [kk - 1] = cdSeries [kk];
                }
                SelectedVariables -> erase (positionOfSerTitle);
                SeriesCnt --;
            }

        }

    }

    map < string, ClassVar * > :: iterator it;
    for (it = AllVariables -> begin (); it != AllVariables -> end (); it ++) {
        if (it -> second -> DLLName == "Macro")
        {
            AllVariables -> erase (it -> first);
            it = AllVariables -> begin ();
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ListBoxMacroClear()@@@CRHMmain.cpp>");
}
void CRHMmain :: MacroLoad (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::MacroLoad(void)@@@CRHMmain.cpp>");
    Global :: GroupCntTrk = 0;
    Global :: StructCntTrk = 0;
    ClearModules (false);
    if (Global :: MacroModulesList -> size () > 0)
    {
        size_t Macro = 0;
        while (Macro < Global :: MacroModulesList -> size ()) {
            string s = Global :: MacroModulesList -> at (Macro);
            string :: size_type ppp = s.find_last_not_of (' ');
            if (s.empty () || ppp == string :: npos || s [0] == '/')
            {
                ++ Macro;
                continue;
            }

            string Desc;
            string :: size_type pp = s.find_first_of (" /");
            if (pp != string :: npos)
            {
                Desc = s.substr (pp);
                s = s.substr (0, pp);
                pp = Desc.find_first_not_of (" /");
                Desc = Desc.substr (pp);
                Desc = '\'' + Desc + '\'';
            }

            else
            {
                Desc = "'no description given'";
            }

            ClassMacro * Custom = new ClassMacro (s, Macro, "04/20/06", Desc);
            AdminMacro.AddModule (Custom);
            string S, SS;
            S = Global :: MacroModulesList -> at (Macro).c_str ();
            S = Common :: trim (S);
            SS = S.substr (0, 3);
            while (! (SS == "end" && (S.length () == 3 || S.find_first_of (" /") != string :: npos)) && Global :: MacroModulesList -> size () > Macro) {
                Macro ++;
                S = Global :: MacroModulesList -> at (Macro).c_str ();
                S = Common :: trim (S);
                SS = S.substr (0, 3);
            }
            Macro ++;
        }
        AdminMacro.LoadCRHM ("Macro");
        AdminMacro.Accept (mbYesToAll);
        if (InitMacroCnt == 0)
        {
            InitMacroCnt = 1;
            ++ InitModCnt;
        }

        if (SeriesCnt > 0)
        {
            SeriesCnt = 0;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::MacroLoad(void)@@@CRHMmain.cpp>");
}
string CRHMmain :: DeclObsName (ClassVar * thisVar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DeclObsName(ClassVar * thisVar)@@@CRHMmain.cpp>");
    string Newname = thisVar -> name;
    std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos = Global :: OurModulesList -> end ();
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        if (it -> first == thisVar -> module)
        {
            pos = it;
        }

    }
    if (pos != Global :: OurModulesList -> end () && Newname.rfind ("#") != string :: npos)
    {
        ClassModule * thisModule = pos -> second;
        if (thisModule -> isGroup)
        {
            string AA ("@@");
            AA [1] += (char) thisModule -> GroupCnt;
            Newname += AA;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DeclObsName(ClassVar * thisVar)@@@CRHMmain.cpp>");
    return Newname;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DeclObsName(ClassVar * thisVar)@@@CRHMmain.cpp>");
}
bool CRHMmain :: OpenObsFile (string FileName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::OpenObsFile(string FileName)@@@CRHMmain.cpp>");
    ClassData * FileData;
    bool fileAlreadyOpen = false;
    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
        if (it -> first == FileName)
        {
            fileAlreadyOpen = true;
        }

    }
    if (fileAlreadyOpen == true)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain.cpp>");
        return false;
    }

    if (ObsFilesList -> size () == 0)
    {
        Global :: DTstart = 0;
        Global :: DTend = 0;
    }

    FileData = new ClassData (FileName);
    if (FileData -> Success)
    {
        if (ObsFilesList -> size () == 0)
        {
            if (FileData -> Times != NULL)
            {
                delete FileData;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain.cpp>");
                return false;
            }

            setStartDate (FileData -> Dt1);
            setEndDate (FileData -> Dt2);
            OpenNameObs = FileName;
            Global :: Interval = FileData -> Interval;
            Global :: Freq = FileData -> Freq;
            Global :: IndxMin = FileData -> IndxMin;
            Global :: IndxMax = FileData -> IndxMax;
        }

        FileData -> ModN = Global :: Freq / FileData -> Freq;
        ClassVar * thisVar;
        std :: map < std :: string, ClassVar * > :: iterator it;
        for (it = AllVariables -> begin (); it != AllVariables -> end (); it ++) {
            if (it -> second -> varType >= TVar :: Read)
            {
                AllVariables -> erase (it -> first);
                it = AllVariables -> begin ();
            }

        }
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator selectedVarIt = SelectedVariables -> begin (); selectedVarIt != SelectedVariables -> end (); selectedVarIt ++) {
            thisVar = selectedVarIt -> second;
            if (thisVar && thisVar -> varType >= TVar :: Read)
            {
                SelectedVariables -> erase (selectedVarIt);
            }

        }
        AllObservations -> clear ();
        MapVar :: iterator itVar;
        for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
            thisVar = (* itVar).second;
            if (thisVar && thisVar -> varType >= TVar :: Read)
            {
                if (AllObservations -> count (thisVar -> name) == 0)
                {
                    AllObservations -> insert (std :: pair < std :: string, ClassVar * > (thisVar -> name, thisVar));
                }

            }

        }
        ObsFilesList -> push_back (std :: pair < std :: string, ClassData * > (FileName, FileData));

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain.cpp>");
        return true;
    }

    else
    {
        if (ObsFilesList -> size () == 0)
        {
            Global :: DTstart = 0;
            Global :: DTend = 0;
        }

        delete FileData;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain.cpp>");
}
void CRHMmain :: ObsCloseClick (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ObsCloseClick(void)@@@CRHMmain.cpp>");
    AllObservations -> clear ();
    SelectedObservations -> clear ();
    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
        ClassData * FileData = it -> second;
        delete FileData;
    }
    ObsFilesList -> clear ();
    Global :: nobs = 1;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ObsCloseClick(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: ObsFileClose (std :: string filepath)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ObsFileClose(std :: string filepath)@@@CRHMmain.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    std :: list < std :: pair < std :: string, ClassData * >> :: iterator position;
    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
        if (it -> first == filepath)
        {
            position = it;
            break;
        }

    }
    if (position == ObsFilesList -> begin () && ObsFilesList -> size () == 1)
    {
        ObsCloseClick ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ObsFileClose(std :: string filepath)@@@CRHMmain.cpp>");
        return;
    }

    AllObservations -> clear ();
    ClassData * FileData = position -> second;
    delete FileData;
    ObsFilesList -> erase (position);
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType >= TVar :: Read)
        {
            if (AllObservations -> count (itVar -> second -> name) == 0)
            {
                AllObservations -> insert (std :: pair < std :: string, ClassVar * > (itVar -> second -> name, itVar -> second));
            }

        }

    }
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType < TVar :: Read && thisVar -> visibility == TVISIBLE :: USUAL)
        {
            if (AllVariables -> count ((* itVar).second -> name) == 0)
            {
                AllVariables -> insert (std :: pair < std :: string, ClassVar * > ((* itVar).second -> name, (* itVar).second));
            }

        }

    }
    delete cdSeries;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ObsFileClose(std :: string filepath)@@@CRHMmain.cpp>");
}
void CRHMmain :: FormDestroy (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FormDestroy(void)@@@CRHMmain.cpp>");
    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
        ClassData * FileData = it -> second;
        delete FileData;
    }
    delete ObsFilesList;
    ModVarRemove (Global :: MapVars);
    Global :: SharedMapPars.clear ();
    delete ProjectList;
    delete AllVariables;
    delete AllObservations;
    delete SelectedVariables;
    delete SelectedObservations;
    delete Global :: OurModulesList;
    delete Global :: ModelModulesList;
    delete Global :: DeclRootList;
    delete Global :: PendingDLLModuleList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FormDestroy(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: FreeChart1 (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FreeChart1(void)@@@CRHMmain.cpp>");
    if (SeriesCnt > 0)
    {
        for (int ii = 0; ii < SeriesCnt; ii ++) {
            ClassVar * thisVar = (ClassVar *) cdSeries [ii] -> Tag;
            if (thisVar -> FunKind > TFun :: FOBS && ! thisVar -> values && ! thisVar -> ivalues)
            {
                delete thisVar;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FreeChart1(void)@@@CRHMmain.cpp>");
}
bool CRHMmain :: FileExistsSp (string FileName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FileExistsSp(string FileName)@@@CRHMmain.cpp>");
    ifstream DataFile;
    DataFile.open (FileName.c_str ());
    if (DataFile)
    {
        DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FileExistsSp(string FileName)@@@CRHMmain.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FileExistsSp(string FileName)@@@CRHMmain.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FileExistsSp(string FileName)@@@CRHMmain.cpp>");
}
bool CRHMmain :: FindFileName (string & FileName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
    string FilePart;
    if (FileExistsSp (FileName))
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
        return true;
    }

    string :: size_type Pos = FileName.find_last_of ("\\/");
    if (Pos)
    {
        FilePart = FileName.substr (Pos + 1, FileName.length ());
        if (FileExistsSp (FilePart))
        {
            FileName = FilePart;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
            return true;
        }

    }

    else
    {
        FilePart = FileName;
    }

    string NewFileName = ProjectDirectory + FilePart;
    if (FileExistsSp (NewFileName))
    {
        FileName = NewFileName;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
        return true;
    }

    NewFileName = ApplicationDir + FilePart;
    if (FileExistsSp (NewFileName))
    {
        FileName = NewFileName;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
        return true;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
    return false;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain.cpp>");
}
string CRHMmain :: ExtractHruLay (string S, long & Hru, long & Lay)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ExtractHruLay(string S, long & Hru, long & Lay)@@@CRHMmain.cpp>");
    long jj = S.find ("(");
    long jj1 = S.find (",");
    long jj2 = S.find (")");
    Lay = 0;
    if (jj1 > - 1)
    {
        Lay = Strtolong (S.substr (jj1 + 1, jj2 - jj1 - 1));
    }

    else
    {
        jj1 = jj2;
    }

    Hru = Strtolong ((S.substr (jj + 1, jj1 - jj - 1)));

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLay(string S, long & Hru, long & Lay)@@@CRHMmain.cpp>");
    return S.substr (0, jj);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLay(string S, long & Hru, long & Lay)@@@CRHMmain.cpp>");
}
MMSData * CRHMmain :: RunClick2Start ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick2Start()@@@CRHMmain.cpp>");
    ClassVar * thisVar;
    double ** mmsData;
    long ** mmsDataL;
    bool GoodRun = true;
    MMSData * mmsdata = new MMSData ();
    this -> finishedRun = false;
    MapVar :: iterator itVar;
    Global :: ModuleBitSet -> clear ();
    Global :: HRU_OBS = Global :: HRU_OBS_DIRECT;
    Global :: OBS_AS_IS = false;
    Global :: WQ_prj = false;
    if (Global :: IndxMin != 0)
    {
        Global :: IndxMin = 0;
    }

    if (Global :: IndxMin != 0)
    {

        #if defined (VS_GUI)
            AfxMessageBox (_T ("First observation day - not an entire day"));
        #endif

        #if defined (COMMAND_LINE)
            string message = "First observation day - not an entire day";
            LogMessageX (message.c_str ());
        #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain.cpp>");
        return mmsdata;
    }

    if (SelectedVariables -> size () == 0)
    {

        #if defined (VS_GUI)
            AfxMessageBox (_T ("No model output selected"));
        #endif

        #if defined (COMMAND_LINE)
            string message = "No model output selected";
            LogMessageX (message.c_str ());
        #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain.cpp>");
        return mmsdata;
    }

    string Message = "Project file: " + OpenNamePrj;
    LogMessageX (Message.c_str ());
    LogMessageX (" ");
    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
        Message = "Observation file: " + it -> first;
        LogMessageX (Message.c_str ());
    }
    LogMessageX (" ");
    if (OpenStateFlag)
    {
        Message = "State file: " + OpenNameState;
        LogMessageX (Message.c_str ());
        LogMessageX (" ");
    }

    double Dt = StandardConverterUtility :: DateTimeDt ();
    Message = string ("Time of model run: ") + DttoStr (Dt) + " " + FormatString (Dt, "yy mm dd ") + ". Program " + Version;
    LogMessageX (Message.c_str ());
    string S = string ("Module List \"");
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        ClassModule * thisModule = it -> second;
        S += it -> first;
        if (thisModule -> variation != 0)
        {
            string AA ("#0");
            AA [1] += (char) (log (thisModule -> variation) / log (2) + 1);
            S += AA;
        }

        std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos = it;
        if (pos ++ == Global :: OurModulesList -> end ())
        {
            S += ".\"";
        }

        else
        {
            S += ", ";
        }

    }
    if (! Global :: MapAKA.empty ())
    {
        Mapstr2 :: iterator it;
        LogMessageX ("Linkage modifications (AKAs)");
        for (it = Global :: MapAKA.begin (); it != Global :: MapAKA.end (); ++ it) {
            Message = string ((* it).first.c_str ()) + " " + string ((* it).second.c_str ());
            LogMessageX (Message.c_str ());
        }
        LogMessageX (" ");
    }

    Global :: DeclRootList -> clear ();
    Global :: OurModulesList -> begin () -> second -> InitReadObs ();
    double DTstartR = StartDatePicker;
    double DTendR = EndDatePicker;
    ClassPar * thisPar;
    double P;
    thisPar = ParFind ("basin RUN_START");
    if (thisPar)
    {
        if (thisPar -> ivalues [0] > 0)
        {
            P = thisPar -> ivalues [0];
        }

    }

    else
    {
        MapPar :: iterator itPar;
        for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
            thisPar = (* itPar).second;
            if (thisPar -> param == "RUN_START" && thisPar -> ivalues [0] > 0)
            {
                P = thisPar -> ivalues [0];
                break;
            }

        }
    }

    thisPar = ParFind ("basin RUN_END");
    if (thisPar)
    {
        if (thisPar -> ivalues [0] > 0)
        {
            P = thisPar -> ivalues [0];
        }

    }

    else
    {
        MapPar :: iterator itPar;
        for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
            thisPar = (* itPar).second;
            if (thisPar -> param == "RUN_END" && thisPar -> ivalues [0] > 0)
            {
                P = thisPar -> ivalues [0];
                break;
            }

        }
    }

    Global :: DTmin = (int) ((DTstartR - Global :: DTstart) * Global :: Freq);
    Global :: DTindx = Global :: DTmin;
    Global :: DTnow = Global :: DTstart + Global :: Interval * ((long long) Global :: DTindx + 1ll);
    int Modii = 0;
    Global :: MapVarsGet.clear ();
    Global :: MapVarsPut.clear ();
    Global :: MapObsGet.clear ();
    try {
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator moduleIt = Global :: OurModulesList -> begin (); moduleIt != Global :: OurModulesList -> end (); moduleIt ++) {
            moduleIt -> second -> initbase ();
        }
    }
    catch (CRHMException Except) {
        LogMessageX (Except.Message.c_str ());
        GoodRun = false;
    }
    catch (exception & E) {
        LogMessageX (E.what ());
        GoodRun = false;
    }
    catch (...) {
        LogMessageX ("Unknown error");
        GoodRun = false;
    }
    if (DTstartR >= DTendR)
    {
        LogMessageX ("Start Time >= EndTime");
        GoodRun = false;
    }

    ClassData * FileData = NULL;
    if (ObsFilesList -> size () > 0)
    {
        FileData = ObsFilesList -> begin () -> second;
        if (DTstartR < FileData -> Dt1)
        {
            LogMessageX ("Start Time before first Observation");
            GoodRun = false;
        }

        if (DTendR > FileData -> Dt2)
        {
            LogMessageX ("End Time after last Observation");
            GoodRun = false;
        }

    }

    if (GoodRun)
    {
        if (! OpenStateFlag)
        {
            thisPar = ParFind ("basin INIT_STATE");
            if (thisPar && thisPar -> Strings -> size () && ! thisPar -> Strings -> at (0).empty ())
            {
                OpenNameState = thisPar -> Strings -> at (0);
                OpenStateFlag = true;
            }

            else
            {
                MapPar :: iterator itPar;
                for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
                    thisPar = (* itPar).second;
                    if (thisPar -> param == "INIT_STATE" && thisPar -> Strings -> size () && ! thisPar -> Strings -> at (0).empty ())
                    {
                        OpenNameState = thisPar -> Strings -> at (0);
                        OpenStateFlag = true;
                        break;
                    }

                }
            }

        }

    }

    if (OpenStateFlag)
    {
        ReadStateFile (GoodRun);
    }

    if (! GoodRun)
    {
        Global :: OurModulesList -> begin () -> second -> InitReadObs ();
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
            modIt -> second -> finish (false);
        }
        Global :: BuildFlag = TBuild :: DECL;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain.cpp>");
        return mmsdata;
    }

    Global :: BuildFlag = TBuild :: RUN;
    Global :: DTmax = (int) ((DTendR - Global :: DTstart) * Global :: Freq);
    SeriesCnt = SelectedVariables -> size ();
    int Cnt = Global :: DTmax - Global :: DTmin;
    cdSeries = new TSeries * [SeriesCnt];
    for (int ii = 0; ii < SeriesCnt; ++ ii) {
        cdSeries [ii] = new TSeries ();
    }
    mmsData = new double * [SeriesCnt];
    mmsDataL = new long * [SeriesCnt];
    std :: list < std :: pair < std :: string, ClassVar * >> :: iterator selectedVarIterator = SelectedVariables -> begin ();
    for (int ii = 0; ii < SeriesCnt; ii ++) {
        thisVar = selectedVarIterator -> second;
        cdSeries [ii] -> Tag = thisVar;
        string S = selectedVarIterator -> first;
        cdSeries [ii] -> Title = S;
        long lay, dim;
        S = ExtractHruLay (S, dim, lay);
        if (thisVar -> varType == TVar :: Float)
        {
            mmsDataL [ii] = NULL;
            if (thisVar -> lay == 0)
            {
                mmsData [ii] = thisVar -> values + (dim - 1);
            }

            else
            {
                mmsData [ii] = (thisVar -> layvalues [lay - 1]) + (dim - 1);
            }

        }

        else
        if (thisVar -> varType == TVar :: Int)
        {
            mmsData [ii] = NULL;
            if (thisVar -> lay == 0)
            {
                mmsDataL [ii] = thisVar -> ivalues + (dim - 1);
            }

            else
            {
                mmsDataL [ii] = (thisVar -> ilayvalues [lay - 1]) + (dim - 1);
            }

        }

        selectedVarIterator ++;
    }
    LogMessageX (" ");
    S = string ("timestep ") + DttoStr (Global :: Interval * 24) + " hr.";
    LogDebug (S.c_str ());
    LogDebugT ("\"start of run\".");
    LogMessageX (" ");
    Global :: CRHMControlSaveCnt = 0;
    Global :: CRHMStatus = 0;
    Global :: LoopCntDown = - 1;
    StatePar = NULL;
    Global :: ModuleBitSet -> clear ();
    ClassModule * Obs_preset;
    std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos = Global :: OurModulesList -> end ();
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        if (it -> first == "obs")
        {
            pos = it;
        }

    }
    if (pos == Global :: OurModulesList -> end ())
    {
        Obs_preset = NULL;
    }

    else
    {
        Obs_preset = pos -> second;
    }

    if (Global :: LoopCnt && ((double) Global :: RapidAdvanceTo == 0.0 || (double) Global :: RapidAdvanceTo <= DTstartR))
    {
        Global :: RapidAdvanceTo = DTstartR + 1;
    }

    mmsdata -> mmsData = mmsData;
    mmsdata -> mmsDataL = mmsDataL;
    mmsdata -> GoodRun = GoodRun;
    mmsdata -> obs_preset = Obs_preset;
    mmsdata -> S = S;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain.cpp>");
    return mmsdata;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain.cpp>");
}
void CRHMmain :: RunClick2Middle (MMSData * mmsdata, long startdate, long enddate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick2Middle(MMSData * mmsdata, long startdate, long enddate)@@@CRHMmain.cpp>");
    double ** mmsData = mmsdata -> mmsData;
    long ** mmsDataL = mmsdata -> mmsDataL;
    bool GoodRun = mmsdata -> GoodRun;
    string S = mmsdata -> S;
    ClassModule * Obs_preset = mmsdata -> obs_preset;
    bool First = true;
    try {
        if (this -> ShowProgress)
        {
            print_progress_start ();
        }

        if (Global :: DTindx == Global :: DTmin)
        {
            this -> calculateOutputFileName ();
            this -> reportStream = new ReportStream (this -> OpenNameReport);
            this -> reportStream -> OutputHeaders (this);
        }

        int iter = 0;
        for (Global :: DTindx = startdate; Global :: DTindx < enddate; Global :: DTindx ++) {
            if (this -> ShowProgress)
            {
                print_progress (Global :: DTindx, enddate, this -> UpdateProgress);
            }

            iter ++;
            if (Global :: Freq == 1)
            {
                Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx);
            }

            else
            {
                Global :: DTnow = Global :: DTstart + Global :: Interval * ((long long) Global :: DTindx + 1ll);
            }

            if ((double) Global :: RapidAdvanceTo > 0.0 && ! (Global :: CRHMStatus & 4))
            {
                if (Global :: DTnow < Global :: RapidAdvanceTo)
                {
                    Global :: CRHMStatus |= 2;
                }

                else
                if (Global :: DTnow == Global :: RapidAdvanceTo + Global :: Interval && ! Global :: LoopCnt)
                {
                    Global :: CRHMStatus &= 125;
                    LogMessage ("Terminate fast loop aheadMain", TExtra :: DD);
                }

                else
                if (Global :: DTnow == Global :: RapidAdvanceTo && Global :: LoopCnt)
                {
                    if (Global :: LoopCntDown == - 1)
                    {
                        Global :: LoopCntDown = Global :: LoopCnt;
                        StatePar = ParFind ("basin StateVars_to_Update");
                        ControlSaveState (true, StatePar);
                        LogMessage ("Initialise LoopTo Main", TExtra :: DD);
                    }

                }

                else
                if (Global :: DTnow == Global :: LoopTo && Global :: LoopCnt)
                {
                    ControlReadState (true, StatePar);
                    -- Global :: LoopCntDown;
                    LogMessage ("Reached loop Main", TExtra :: DD);
                    if (Global :: LoopCntDown <= 0)
                    {
                        ResetLoopList ();
                        Global :: CRHMStatus &= 125;
                        Global :: CRHMStatus |= 4;
                        Global :: LoopCntDown = - 1;
                        LogMessage ("Terminate LoopTo Main", TExtra :: DD);
                        continue;
                    }

                }

            }

            DoObsStatus (First);
            bool Reset = true;
            if (Obs_preset)
            {
                Obs_preset -> pre_run ();
            }

            for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
                Global :: CurrentModuleRun = modIt -> first;
                long Last = Global :: CRHMControlSaveCnt;
                ClassModule * p = modIt -> second;
                if (p -> GroupCnt && ((ClassMacro *) p) -> ObsModule)
                {
                    ((ClassMacro *) p) -> ObsModule -> pre_run ();
                }

                p -> ReadObs (Reset);
                Reset = false;
                CheckBlankModule ();
                if (! p -> isGroup || ! Global :: CRHMStatus || (Global :: CRHMStatus & 1 && Global :: ModuleBitSet -> count (Global :: CurrentModuleRun)))
                {
                    p -> run ();
                }

                CheckBlankModule ();
                if (Last != Global :: CRHMControlSaveCnt)
                {
                    Global :: ModuleBitSet -> insert (Global :: CurrentModuleRun);
                }

            }
            if (Global :: CRHMControlSaveCnt && ! (Global :: CRHMStatus & 1))
            {
                ControlSaveState (false, StatePar);
                Global :: CRHMStatus |= 1;
                LogMessage ("Start save Main", TExtra :: DD);
            }

            bool DoOutput = true;
            if ((Global :: CRHMStatus & 1) && (! Global :: CRHMControlSaveCnt || Global :: DTindx >= Global :: DTmax - 1))
            {
                ControlReadState (false, NULL);
                Global :: CRHMStatus &= 126;
                Global :: CRHMControlSaveCnt = 0;
                LogMessage ("End save Main", TExtra :: DD);
                LogDebug (" ");
                if (Global :: Freq == 1)
                {
                    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx);
                    Global :: DTindx -= 1;
                }

                else
                {
                    Global :: DTnow = Global :: DTstart + Global :: Interval * ((long long) Global :: DTindx + 1ll);
                    Global :: DTindx -= 1;
                }

                DoOutput = false;
            }

            if (! (Global :: CRHMStatus & 7) && ! (Global :: CRHMControlSaveCnt) && DoOutput)
            {
                double xx;
                for (int ii = 0; ii < SeriesCnt; ii ++) {
                    if (mmsData [ii] != NULL)
                    {
                        xx = * mmsData [ii];
                        if (xx < xLimit)
                        {
                            cdSeries [ii] -> AddXY (Global :: DTnow, xx);
                        }

                        else
                        {
                            cdSeries [ii] -> AddXY (Global :: DTnow, - 9999);
                        }

                    }

                    else
                    {
                        xx = (* mmsDataL [ii]);
                        if (xx < lLimit)
                        {
                            cdSeries [ii] -> AddXY (Global :: DTnow, xx);
                        }

                        else
                        {
                            cdSeries [ii] -> AddXY (Global :: DTnow, - 9999);
                        }

                    }

                }
            }

            if (this -> ReportAll)
            {
                this -> reportStream -> SendTimeStepToReport (this);
            }

            if (! this -> ReportAll && Global :: DTindx == Global :: DTmax - 1)
            {
                this -> reportStream -> SendTimeStepToReport (this);
            }

        }
        if (this -> ShowProgress)
        {
            print_progress_end ();
        }

        if (Global :: DTindx == Global :: DTmax)
        {
            this -> reportStream -> CloseStream ();
        }

        int d = iter;
        Global :: BuildFlag = TBuild :: DECL;
    }
    catch (exception & E) {
        string errorMessage = E.what ();
        LogError (errorMessage + " (" + FloatToStrF (Global :: DTnow, TFloatFormat :: ffGeneral, 10, 0) + ")", TExcept :: ERR);
        GoodRun = false;
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Middle(MMSData * mmsdata, long startdate, long enddate)@@@CRHMmain.cpp>");
}
void CRHMmain :: RunClick2End (MMSData * mmsdata)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick2End(MMSData * mmsdata)@@@CRHMmain.cpp>");
    double ** mmsData = mmsdata -> mmsData;
    long ** mmsDataL = mmsdata -> mmsDataL;
    bool GoodRun = mmsdata -> GoodRun;
    double Dt = StandardConverterUtility :: DateTimeDt ();
    string Message = string ("End of model run: ") + DttoStr (Dt) + " " + FormatString (Dt, "yy mm dd ") + ". Program " + Version;
    LogMessageX (Message.c_str ());
    delete [] mmsData;
    delete [] mmsDataL;
    Global :: OurModulesList -> begin () -> second -> InitReadObs ();
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        modIt -> second -> finish (true);
    }
    if (GoodRun)
    {
        if (SaveStateFlag)
        {
            SaveState ();
        }

        this -> finishedRun = true;
    }

    CRHMLogger :: instance () -> get_run_logger () -> flush ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2End(MMSData * mmsdata)@@@CRHMmain.cpp>");
}
void CRHMmain :: CheckBlankModule ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::CheckBlankModule()@@@CRHMmain.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        string s = thisVar -> name;
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::CheckBlankModule()@@@CRHMmain.cpp>");
}
void CRHMmain :: RunClick (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick(void)@@@CRHMmain.cpp>");
    MMSData * mmsdata = CRHMmain :: RunClick2Start ();
    CRHMmain :: RunClick2Middle (mmsdata, Global :: DTmin, Global :: DTmax);
    CRHMmain :: RunClick2End (mmsdata);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: ControlSaveState (bool MainLoop, ClassPar * VarPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ControlSaveState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain.cpp>");
    std :: list < std :: string > * StateList;
    StateList = new std :: list < std :: string > ();
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    string S;
    bool Needed;
    Global :: RunUpBitSet.reset ();
    bool Wild = false;
    if (VarPar && ! VarPar -> Strings -> at (0).empty ())
    {
        Wild = VarPar -> Strings -> at (0).find ("@") == string :: npos;
    }

    if (MainLoop)
    {
        StateList -> push_back ("Starting main run-up loop");
    }

    else
    {
        StateList -> push_back ("starting module run-ahead to determine future variables");
    }

    StateList -> push_back ("######");
    StateList -> push_back ("Time:");
    S = FormatString (Global :: DTnow, "yyyy m d");
    StateList -> push_back (S);
    StateList -> push_back ("######");
    StateList -> push_back ("DTindx:");
    StateList -> push_back (DttoStr (Global :: DTindx));
    StateList -> push_back ("######");
    StateList -> push_back ("CurrentModuleRun:");
    StateList -> push_back (Global :: CurrentModuleRun);
    StateList -> push_back ("######");
    StateList -> push_back ("Dimension:");
    StateList -> push_back (Common :: longtoStr (Global :: nhru) + " " + Common :: longtoStr (Global :: nlay));
    StateList -> push_back ("######");
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        Needed = false;
        if (thisVar -> varType < TVar :: Read && thisVar -> StatVar)
        {
            if (! thisVar -> InGroup || Global :: ModuleBitSet -> count (thisVar -> module))
            {
                Needed = true;
            }

            else
            if (MainLoop)
            {
                string namebasic = thisVar -> name;
                size_t indx_namebasic = - 1;
                if (VarPar)
                {
                    for (size_t it = 0; it < VarPar -> Strings -> size (); it ++) {
                        if (VarPar -> Strings -> at (it) == namebasic)
                        {
                            indx_namebasic = it;
                            break;
                        }

                    }
                }

                if (VarPar && (indx_namebasic > - 1))
                {
                    Needed = true;
                }

                else
                if (Wild)
                {
                    string :: size_type Idx = namebasic.find ("@");
                    if (Idx != string :: npos)
                    {
                        namebasic = namebasic.substr (1, Idx - 1);
                        indx_namebasic = - 1;
                        if (VarPar)
                        {
                            for (size_t it = 0; it < VarPar -> Strings -> size (); it ++) {
                                if (VarPar -> Strings -> at (it) == namebasic)
                                {
                                    indx_namebasic = it;
                                    break;
                                }

                            }
                        }

                        if (VarPar && (indx_namebasic > - 1))
                        {
                            Needed = true;
                        }

                    }

                }

                Global :: RunUpBitSet [thisVar -> InGroup - 1] = true;
            }

        }

        if (Needed)
        {
            S = thisVar -> module + " " + thisVar -> name;
            StateList -> push_back (S);
            S = "";
            if (thisVar -> lay == 0)
            for (int ii = 0; ii < thisVar -> dim; ii ++) {
                if (thisVar -> values != NULL)
                {
                    S = S + FloatToStrF (thisVar -> values [ii], TFloatFormat :: ffGeneral, 7, 0) + " ";
                }

                else
                if (thisVar -> ivalues != NULL)
                {
                    S = S + FloatToStrF (thisVar -> ivalues [ii], TFloatFormat :: ffGeneral, 7, 0) + " ";
                }

                else
                {
                    S = S + "-0 ";
                }

                if (ii % 10 == 9)
                {
                    StateList -> push_back (S);
                    S = "";
                }

            }

            else
            for (int ll = 0; ll < thisVar -> lay; ll ++) {
                for (int ii = 0; ii < thisVar -> dim; ii ++) {
                    if (thisVar -> layvalues != NULL)
                    {
                        S = S + FloatToStrF (thisVar -> layvalues [ll] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                    }

                    else
                    if (thisVar -> ivalues != NULL)
                    {
                        S = S + FloatToStrF (thisVar -> ilayvalues [ll] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                    }

                    else
                    {
                        S = S + "-0 ";
                    }

                    if (ii % 10 == 9)
                    {
                        StateList -> push_back (S);
                        S = "";
                    }

                }
                if (! S.empty ())
                {
                    StateList -> push_back (S);
                }

                S = "";
            }

            if (! S.empty ())
            {
                StateList -> push_back (S);
            }

            StateList -> push_back ("######");
        }

    }
    if (MainLoop)
    {
        ofstream file;
        file.open (ProjectDirectory + "\\" + "ControlStateFile.tmp1");
        if (file.is_open ())
        {
            for (std :: list < std :: string > :: iterator it = StateList -> begin (); it != StateList -> end (); it ++) {
                file << it -> c_str () << endl;
            }
            file.close ();
        }

        else
        {
            CRHMException e = CRHMException ("Cannot open file " + ProjectDirectory + "\\" + "ControlStateFile.tmp1 to save state file.", TExcept :: ERR);
            CRHMLogger :: instance () -> log_run_error (e);
        }

    }

    else
    {
        ofstream file;
        file.open (ProjectDirectory + "\\" + "ControlStateFile.tmp2");
        if (file.is_open ())
        {
            for (std :: list < std :: string > :: iterator it = StateList -> begin (); it != StateList -> end (); it ++) {
                file << it -> c_str () << endl;
            }
            file.close ();
        }

        else
        {
            CRHMException e = CRHMException ("Cannot open file " + ProjectDirectory + "\\" + "ControlStateFile.tmp2 to save state file.", TExcept :: ERR);
            CRHMLogger :: instance () -> log_run_error (e);
        }

    }

    delete StateList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ControlSaveState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain.cpp>");
}
void CRHMmain :: ReadStateFile (bool & GoodRun)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain.cpp>");
    MapPar :: iterator itVar;
    ClassVar * thisVar;
    std :: string module, name, Descrip, Line;
    string S;
    ifstream DataFile (OpenNameState.c_str ());
    if (! DataFile)
    {
        Common :: Message ("cannot open file", "File Error");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain.cpp>");
        return;
    }

    getline (DataFile, Descrip);
    DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
    getline (DataFile, Line);
    getline (DataFile, Line);

    int D [3]
    {
    }
    ;
    DataFile >> D [0] >> D [1] >> D [2];
    double DT = StandardConverterUtility :: EncodeDateTime (D [0], D [1], D [2], 0, 0);
    getline (DataFile, Descrip);
    DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
    getline (DataFile, Line);
    getline (DataFile, Line);
    long filehru, filelay;
    DataFile >> filehru >> filelay;
    if (filehru != Global :: nhru || filelay != Global :: nlay)
    {
        Common :: Message ("State File and Model #HRU's or #LAY's are not equal", "File Error");
        GoodRun = false;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain.cpp>");
        return;
    }

    DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
    getline (DataFile, Line);
    while (! DataFile.eof ()) {
        DataFile >> module >> name;
        if (DataFile.fail ())
        {
            break;
        }

        DataFile.ignore ();
        S = string (module) + ' ' + string (name);
        thisVar = ClassVarFind (S);
        if (! thisVar)
        {
            thisVar = ClassVarFind ("#" + S);
        }

        if (thisVar)
        {
            if (thisVar -> lay == 0)
            {
                for (int ii = 0; ii < thisVar -> dim; ii ++)
                    if (thisVar -> values != NULL)
                    {
                        DataFile >> thisVar -> values [ii];
                    }

                    else
                    if (thisVar -> ivalues != NULL)
                    {
                        DataFile >> thisVar -> ivalues [ii];
                    }

            }

            else
            {
                for (int ll = 0; ll < thisVar -> lay; ll ++)
                    for (int ii = 0; ii < thisVar -> dim; ii ++)
                        if (thisVar -> layvalues != NULL)
                        {
                            DataFile >> thisVar -> layvalues [ll] [ii];
                        }

                        else
                        if (thisVar -> ivalues != NULL)
                        {
                            DataFile >> thisVar -> ilayvalues [ll] [ii];
                        }

            }

            DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
            getline (DataFile, Line);
        }

        else
        {
            Common :: Message ((string ("State File variable ") + S.c_str ()).c_str (), "Unknown variable");
            DataFile.ignore ((numeric_limits < streamsize > :: max) (), '#');
            getline (DataFile, Line);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain.cpp>");
}
ClassVar * VarFind (string name)
{
InstrumentLogger::instance()->log_instrument_log("<VarFind(string name)@@@CRHMmain.cpp>");
    MapVar :: iterator itVar;
    if ((itVar = Global :: MapVars.find (name)) == Global :: MapVars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</VarFind(string name)@@@CRHMmain.cpp>");
        return NULL;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</VarFind(string name)@@@CRHMmain.cpp>");
        return ((* itVar).second);
    }

InstrumentLogger::instance()->log_instrument_log("</VarFind(string name)@@@CRHMmain.cpp>");
}
ClassPar * ParFind (string name)
{
InstrumentLogger::instance()->log_instrument_log("<ParFind(string name)@@@CRHMmain.cpp>");
    MapPar :: iterator itPar;
    if ((itPar = Global :: MapPars.find (name)) == Global :: MapPars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</ParFind(string name)@@@CRHMmain.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ParFind(string name)@@@CRHMmain.cpp>");
    return ((* itPar).second);
InstrumentLogger::instance()->log_instrument_log("</ParFind(string name)@@@CRHMmain.cpp>");
}
void CRHMmain :: DoObsStatus (bool & First)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DoObsStatus(bool & First)@@@CRHMmain.cpp>");
    if (First)
    {
        for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
            ClassData * FileData = it -> second;
            FileData -> TimeIndx = 0;
        }
        First = false;
    }

    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
        ClassData * FileData = it -> second;
        FileData -> GoodInterval = true;
        if (it == ObsFilesList -> begin ())
        {
            FileData -> GoodDay = true;
            continue;
        }

        FileData -> GoodInterval = true;
        if (FileData -> Times != NULL)
        {
            FileData -> GoodDay = false;
            while (FileData -> Times [FileData -> TimeIndx] < Global :: DTnow && FileData -> TimeIndx < FileData -> Lines - 1) ++ FileData -> TimeIndx;
            if (FileData -> Times [FileData -> TimeIndx] != Global :: DTnow)
            {
                FileData -> GoodInterval = false;
            }

        }

        else
        {
            if (FileData -> ModN == 0)
            {
                CRHMException e = CRHMException ("Observation files are in a incompatible order. "
                    "Make sure the first observation file has the shorter interval.", TExcept :: TERMINATE);
                LogError (e);
            }

            long Index = Global :: DTindx / FileData -> ModN;
            if (Index < FileData -> IndxMin || Index > FileData -> IndxMax)
            {
                FileData -> GoodInterval = false;
                FileData -> GoodDay = false;
                continue;
            }

            if (Index % FileData -> Freq == 0)
            {
                FileData -> GoodDay = true;
                if (FileData -> Freq <= 1)
                {
                    continue;
                }

                Index += FileData -> Freq / FileData -> ModN - 1;
                if (Index < FileData -> IndxMin || Index > FileData -> IndxMax)
                {
                    FileData -> GoodDay = false;
                    continue;
                }

                continue;
            }

            else
            {
                if (FileData -> GoodDay)
                {
                    FileData -> GoodInterval = true;
                }

                else
                if (Index < FileData -> IndxMin || Index > FileData -> IndxMax)
                {
                    FileData -> GoodInterval = false;
                }

            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoObsStatus(bool & First)@@@CRHMmain.cpp>");
}
void CRHMmain :: ResetLoopList (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ResetLoopList(void)@@@CRHMmain.cpp>");
    if (LoopList == NULL)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ResetLoopList(void)@@@CRHMmain.cpp>");
        return;
    }

    ClassPar * thisPar = ParFind ("basin RUN_ID");
    long ID = 0;
    if (! thisPar)
    {
        MapPar :: iterator itPar;
        for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
            thisPar = (* itPar).second;
            if (thisPar -> param == "RUN_ID" && thisPar -> ivalues [0] > 0)
            {
                ID = thisPar -> ivalues [0];
                break;
            }

        }
    }

    else
    {
        ID = thisPar -> ivalues [0];
    }

    string FileName = "CRHM_loop_output";
    if (ID > 0)
    {
        FileName += string ("_");
    }

    ofstream file (ProjectDirectory + "\\" + FileName + ".txt");
    if (file)
    {
        for (std :: list < std :: string > :: iterator it = LoopList -> begin (); it != LoopList -> end (); it ++) {
            file << it -> c_str () << endl;
        }
        file.close ();
    }

    else
    {
        CRHMException e = CRHMException ("Cannot open file to write out loop list." + ProjectDirectory + "\\" + FileName + ".txt", TExcept :: ERR);
        CRHMLogger :: instance () -> log_run_error (e);
    }

    delete LoopList;
    LoopList = NULL;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ResetLoopList(void)@@@CRHMmain.cpp>");
}
void CRHMmain :: ControlReadState (bool MainLoop, ClassPar * VarPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain.cpp>");
    MapPar :: iterator itVar;
    ClassVar * thisVar;
    string Sy;
    string Sx;
    bool first = true;
    bool Wild = false;
    if (VarPar && ! VarPar -> Strings -> at (0).empty ())
    {
        Wild = VarPar -> Strings -> at (0).find ("@") == string :: npos;
    }

    ifstream DataFile;
    char module [80], name [80];
    string S, Descrip, Line;
    if (MainLoop)
    {
        DataFile.open ((ProjectDirectory + "\\" + "ControlStateFile.tmp1").c_str ());
    }

    else
    {
        DataFile.open ((ProjectDirectory + "\\" + "ControlStateFile.tmp2").c_str ());
    }

    if (! DataFile)
    {
        Common :: Message ("cannot open file", "File Error");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain.cpp>");
        return;
    }

    getline (DataFile, Descrip);
    DataFile.ignore (180, '#');
    getline (DataFile, Line);
    getline (DataFile, Line);

    int D [3]
    {
    }
    ;
    DataFile >> D [0] >> D [1] >> D [2];
    DataFile.ignore (180, '#');
    getline (DataFile, Line);
    getline (DataFile, Line);
    DataFile >> Global :: DTindx;
    DataFile.ignore (180, '#');
    getline (DataFile, Line);
    getline (DataFile, Line);
    DataFile >> Global :: CurrentModuleRun;
    getline (DataFile, Descrip);
    DataFile.ignore (180, '#');
    getline (DataFile, Line);
    getline (DataFile, Line);
    long filehru, filelay;
    DataFile >> filehru >> filelay;
    DataFile.ignore (180, '#');
    getline (DataFile, Line);
    while (! DataFile.eof ()) {
        DataFile >> module >> name;
        if (DataFile.fail ())
        {
            break;
        }

        DataFile.ignore ();
        std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos;
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
            if (it -> first == module)
            {
                pos = it;
            }

        }
        ClassModule * mod;
        if (pos != Global :: OurModulesList -> end ())
        {
            mod = pos -> second;
        }

        else
        {
            Common :: Message ((string ("State File module ") + module), "Unknown module");
            DataFile.ignore (180, '#');
            getline (DataFile, Line);
            continue;
        }

        S = string (module) + ' ' + string (name);
        thisVar = ClassVarFind (S);
        if (! thisVar)
        {
            thisVar = ClassVarFind ("#" + S);
        }

        if (! thisVar && mod -> isGroup)
        {
            string :: size_type idx = S.find ('@');
            if (idx == string :: npos)
            {
                string A;
                Common :: GroupEnding (A, mod -> GroupCnt);
                S += A;
                thisVar = ClassVarFind (S);
            }

        }

        string namebasic = name;
        if (Wild)
        {
            string :: size_type Idx = namebasic.find ("@");
            if (Idx != string :: npos)
            {
                namebasic = namebasic.substr (1, Idx - 1);
            }

        }

        if (thisVar)
        {
            size_t indx_namebasic = - 1;
            if (VarPar)
            {
                for (size_t it = 0; it < VarPar -> Strings -> size (); it ++) {
                    if (VarPar -> Strings -> at (it) == namebasic)
                    {
                        indx_namebasic = it;
                        break;
                    }

                }
            }

            if (VarPar && indx_namebasic > - 1)
            {
                if (LoopList == NULL)
                {
                    LoopList = new std :: list < std :: string > ();
                    Sx = DttoStr (Global :: DTnow);
                    LoopList -> push_back (Sx);
                }

                if (first)
                {
                    Sx = "loop " + inttoStr (Global :: LoopCnt - Global :: LoopCntDown + 1) + "\t" + name;
                    first = false;
                }

                else
                {
                    Sx += ("\t" + string (name));
                }

                Sy = "";
                if (thisVar -> lay == 0)
                {
                    for (int ii = 0; ii < thisVar -> dim; ii ++)
                        if (thisVar -> values != NULL)
                        {
                            Sy += FloatToStrF (thisVar -> values [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                        }

                        else
                        if (thisVar -> ivalues != NULL)
                        {
                            Sy += FloatToStrF (thisVar -> ivalues [ii], TFloatFormat :: ffFixed, 0, 0) + " ";
                        }

                }

                else
                {
                    for (int ll = 0; ll < thisVar -> lay; ll ++)
                        for (int ii = 0; ii < thisVar -> dim; ii ++)
                            if (thisVar -> layvalues != NULL)
                            {
                                Sy += FloatToStrF (thisVar -> layvalues [ll] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                            }

                            else
                            if (thisVar -> ivalues != NULL)
                            {
                                Sy += FloatToStrF (thisVar -> ilayvalues [ll] [ii], TFloatFormat :: ffGeneral, 0, 0) + " ";
                            }

                }

                Sx = Sx + "\t" + Sy;
            }

            else
            {
                if (thisVar -> lay == 0)
                {
                    for (int ii = 0; ii < thisVar -> dim; ii ++)
                        if (thisVar -> values != NULL)
                        {
                            DataFile >> thisVar -> values [ii];
                        }

                        else
                        if (thisVar -> ivalues != NULL)
                        {
                            DataFile >> thisVar -> ivalues [ii];
                        }

                }

                else
                {
                    for (int ll = 0; ll < thisVar -> lay; ll ++)
                        for (int ii = 0; ii < thisVar -> dim; ii ++)
                            if (thisVar -> layvalues != NULL)
                            {
                                DataFile >> thisVar -> layvalues [ll] [ii];
                            }

                            else
                            if (thisVar -> ivalues != NULL)
                            {
                                DataFile >> thisVar -> ilayvalues [ll] [ii];
                            }

                }

            }

            DataFile.ignore (180, '#');
            getline (DataFile, Line);
        }

        else
        {
            Common :: Message ((string ("State File variable ") + S), "Unknown variable");
            DataFile.ignore (180, '#');
            getline (DataFile, Line);
        }

    }
    if (MainLoop)
    {
        bool Wild2 = false;
        ClassPar * TraceVarPar = ParFind ("basin TraceVars");
        if (TraceVarPar && ! TraceVarPar -> Strings -> at (0).empty ())
        {
            Wild2 = TraceVarPar -> Strings -> at (0).find ("@") == string :: npos;
        }

        for (size_t ii = 0; ii < TraceVarPar -> Strings -> size (); ++ ii) {
            string Trimmed = Common :: trim (TraceVarPar -> Strings -> at (ii));
            if (! Trimmed.empty ())
            {
                if (AllVariables -> count (Trimmed))
                {
                    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
                        ClassVar * thisVar = VarFind (string (modIt -> first) + ' ' + TraceVarPar -> Strings -> at (0));
                        if (thisVar)
                        {
                            break;
                        }

                    }
                    thisVar = AllVariables -> find (Trimmed) -> second;
                    if (thisVar)
                    {
                        Sx += ("\t" + string (Trimmed));
                        Sy = "";
                        if (thisVar -> lay == 0)
                        {
                            for (int ii = 0; ii < thisVar -> dim; ii ++)
                                if (thisVar -> values != NULL)
                                {
                                    Sy += FloatToStrF (thisVar -> values [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                                }

                                else
                                if (thisVar -> ivalues != NULL)
                                {
                                    Sy += FloatToStrF (thisVar -> ivalues [ii], TFloatFormat :: ffFixed, 0, 0) + " ";
                                }

                        }

                        else
                        {
                            for (int ll = 0; ll < thisVar -> lay; ll ++)
                                for (int ii = 0; ii < thisVar -> dim; ii ++)
                                    if (thisVar -> layvalues != NULL)
                                    {
                                        Sy += FloatToStrF (thisVar -> layvalues [ll] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                                    }

                                    else
                                    if (thisVar -> ivalues != NULL)
                                    {
                                        Sy += FloatToStrF (thisVar -> ilayvalues [ll] [ii], TFloatFormat :: ffGeneral, 0, 0) + " ";
                                    }

                        }

                        Sx = Sx + "\t" + Sy;
                    }

                }

            }

        }
    }

    if (! Sx.empty ())
    {
        LoopList -> push_back (Sx);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain.cpp>");
}
std :: map < std :: string, ClassVar * > * CRHMmain :: getObservations ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getObservations()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getObservations()@@@CRHMmain.cpp>");
    return AllObservations;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getObservations()@@@CRHMmain.cpp>");
}
std :: map < std :: string, ClassModule * > * CRHMmain :: getAllmodules ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getAllmodules()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAllmodules()@@@CRHMmain.cpp>");
    return Global :: AllModulesList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAllmodules()@@@CRHMmain.cpp>");
}
std :: map < std :: string, ClassVar * > * CRHMmain :: getVariables ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getVariables()@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getVariables()@@@CRHMmain.cpp>");
    return this -> AllVariables;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getVariables()@@@CRHMmain.cpp>");
}
void CRHMmain :: calculateOutputFileName ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::calculateOutputFileName()@@@CRHMmain.cpp>");
    if (this -> OutputName == "")
    {
        ClassPar * thisPar;
        thisPar = ParFind ("basin RUN_ID");
        long ID = 0;
        std :: string ext;
        if (this -> OutputFormat == OUTPUT_FORMAT :: STD)
        {
            ext = ".txt";
        }

        else
        {
            ext = ".obs";
        }

        if (! thisPar)
        {
            MapPar :: iterator itPar;
            for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
                thisPar = (* itPar).second;
                if (thisPar -> param == "RUN_ID")
                {
                    ID = thisPar -> ivalues [0];
                    break;
                }

            }
        }

        else
        {
            ID = thisPar -> ivalues [0];
        }

        OpenNameReport = ProjectDirectory + "/CRHM_output";
        if (ID >= 0)
        {
            if (ID > 0)
            {
                OpenNameReport += "_";
                OpenNameReport += inttoStr (ID);
            }

            OpenNameReport += ext;
        }

        else
        if (ID < 0)
        {
            ID = - ID;
            OpenNameReport = OpenNamePrj.substr (0, OpenNamePrj.length () - 4) + "_" + Common :: longtoStr (ID) + ext;
        }

    }

    else
    {
        OpenNameReport = this -> OutputName;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::calculateOutputFileName()@@@CRHMmain.cpp>");
}
string CRHMmain :: DttoStr (double D)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DttoStr(double D)@@@CRHMmain.cpp>");
    ostringstream temp;
    temp << D;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DttoStr(double D)@@@CRHMmain.cpp>");
    return temp.str ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DttoStr(double D)@@@CRHMmain.cpp>");
}
string CRHMmain :: inttoStr (int I)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::inttoStr(int I)@@@CRHMmain.cpp>");
    ostringstream temp;
    temp << I;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::inttoStr(int I)@@@CRHMmain.cpp>");
    return temp.str ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::inttoStr(int I)@@@CRHMmain.cpp>");
}
void CRHMmain :: LogMessageX (const char * S)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::LogMessageX(const char * S)@@@CRHMmain.cpp>");
    CRHMLogger :: instance () -> log_to_console (S);
    CRHMLogger :: instance () -> log_run_message (S);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::LogMessageX(const char * S)@@@CRHMmain.cpp>");
}
string CRHMmain :: GetCaptionFromAboutBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain.cpp>");

    #if defined (VS_GUI)
        CRHMAboutBox aboutbox;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain.cpp>");
        return aboutbox.versionstring;
    #endif

    #if defined (COMMAND_LINE)

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain.cpp>");
        return "";
    #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain.cpp>");
}
void CRHMmain :: SaveProject (string prj_description, string filepath)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SaveProject(string prj_description, string filepath)@@@CRHMmain.cpp>");
    MapPar :: iterator itPar;
    MapDim :: iterator itDim;
    ClassPar * thisPar;
    ClassVar * lastVar = NULL;
    string Output;
    int Y = 0, M = 0, D = 0, H = 0, Min = 0;
    ProjectList -> push_back (prj_description);
    double Dt = StandardConverterUtility :: GetCurrentDateTime ();
    string datetime = StandardConverterUtility :: GetDateTimeInString (Dt);
    string S ("  Creation: " + datetime);
    string caption = GetCaptionFromAboutBox ();
    ProjectList -> push_back ("###### " + caption + S);
    bool Prj = false;
    if (filepath.find (".prj") != std :: string :: npos)
    {
        Prj = true;
    }

    if (Prj)
    {
        ProjectList -> push_back ("Dimensions:");
        ProjectList -> push_back ("######");
        ProjectList -> push_back (string ("nhru " + to_string (Global :: maxhru)));
        ProjectList -> push_back (string ("nlay " + to_string (Global :: maxlay)));
        ProjectList -> push_back (string ("nobs " + to_string (Global :: maxobs)));
        ProjectList -> push_back ("######");
        ProjectList -> push_back ("Macros:");
        ProjectList -> push_back ("######");
        for (size_t ii = 0; ii < Global :: MacroModulesList -> size (); ++ ii) {
            ProjectList -> push_back ("'" + Global :: MacroModulesList -> at (ii) + "'");
        }
        ProjectList -> push_back ("######");
        if (! Global :: MapAKA.empty ())
        {
            Mapstr2 :: iterator it;
            ProjectList -> push_back ("AKAs:");
            ProjectList -> push_back ("######");
            for (it = Global :: MapAKA.begin (); it != Global :: MapAKA.end (); ++ it) {
                string Var = (* it).first + ' ' + (* it).second;
                ProjectList -> push_back (Var.c_str ());
            }
            ProjectList -> push_back ("######");
        }

        ProjectList -> push_back ("Observations:");
        ProjectList -> push_back ("######");
        for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = ObsFilesList -> begin (); it != ObsFilesList -> end (); it ++) {
            string S = it -> first;
            ProjectList -> push_back (S);
        }
        ProjectList -> push_back ("######");
        ProjectList -> push_back ("Dates:");
        ProjectList -> push_back ("######");
        string S;
        double date1 = GetStartDate ();
        S = StandardConverterUtility :: GetDateInString (date1);
        if (ObsFilesList -> size () == 0)
        {
            S = S + " " + FloatToStrF (Global :: Freq, TFloatFormat :: ffGeneral, 0, 0);
        }

        ProjectList -> push_back (S);
        double date2 = GetEndDate ();
        S = StandardConverterUtility :: GetDateInString (date2);
        ProjectList -> push_back (S);
        ProjectList -> push_back ("######");

        #ifdef CRHM_DLL
            if (OpenDLLs -> Count > 0)
            {
                ProjectList -> push_back ("DLLs:");
                ProjectList -> push_back ("######");
                CompactDlls ();
                for (int ii = 0; ii < OpenDLLs -> Count; ii ++) {
                    String S = OpenDLLs -> Strings [ii];
                    ProjectList -> push_back (S);
                }
                ProjectList -> push_back ("######");
            }

        #endif

        ProjectList -> push_back ("Modules:");
        ProjectList -> push_back ("######");
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
            ClassModule * thisModule = modIt -> second;
            string S = modIt -> first;
            if (thisModule -> variation > 0)
            {
                string AA ("#0 ");
                AA [1] += (char) (log (thisModule -> variation) / log (2) + 1);
                S = S + AA.c_str ();
            }

            else
            {
                S = S + " ";
            }

            S = S + thisModule -> DLLName + " ";
            S = S + thisModule -> Version;
            ProjectList -> push_back (S);
            if (thisModule -> isGroup || thisModule -> isStruct)
            {
                list < ModulePtr > :: iterator iterM;
                iterM = ((ClassMacro *) thisModule) -> Modules.begin ();
                while (iterM != ((ClassMacro *) thisModule) -> Modules.end ()) {
                    std :: weak_ptr < ClassModule > MP ((* iterM));
                    string S = string (" +") + (* iterM) -> NameRoot.c_str ();
                    if ((* iterM) -> variation > 0)
                    {
                        string AA ("#0 ");
                        AA [1] += (char) (log ((* iterM) -> variation) / log (2) + 1);
                        S = S + AA.c_str ();
                    }

                    else
                    {
                        S = S + " ";
                    }

                    S = S + (* iterM) -> DLLName + " ";
                    S = S + (* iterM) -> Version;
                    ProjectList -> push_back (S);
                    ++ iterM;
                }
            }

        }
        ProjectList -> push_back ("######");
        ProjectList -> push_back ("Parameters:");
        ProjectList -> push_back ("###### 'basin' parameters always first");
        for (int bb = 0; bb < 2; ++ bb) {
            for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
                thisPar = (* itPar).second;
                if (thisPar -> param == "HRU_group")
                {
                    continue;
                }

                if (bb == 0 && thisPar -> module != "shared")
                {
                    continue;
                }

                if (bb == 1 && thisPar -> module == "shared")
                {
                    continue;
                }

                string S = string (thisPar -> module.c_str ()) + " " + string (thisPar -> param.c_str ());
                if (thisPar -> varType != TVar :: Txt)
                {
                    S += " <" + FloatToStrF (thisPar -> minVal, TFloatFormat :: ffGeneral, 4, 0) + " to " + FloatToStrF (thisPar -> maxVal, TFloatFormat :: ffGeneral, 4, 0) + ">";
                }

                ProjectList -> push_back (S);
                for (long jj = 0; jj < thisPar -> lay; jj ++) {
                    S = "";
                    for (size_t ii = 0; ii < (size_t) thisPar -> dim; ii ++) {
                        if (thisPar -> varType == TVar :: Float)
                        {
                            S = S + FloatToStrF (thisPar -> layvalues [jj] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                        }

                        else
                        if (thisPar -> varType == TVar :: Int)
                        {
                            S = S + FloatToStrF (thisPar -> ilayvalues [jj] [ii], TFloatFormat :: ffFixed, 8, 0) + " ";
                        }

                        else
                        if (thisPar -> varType == TVar :: Txt)
                        {
                            if (thisPar -> Strings -> size () > ii)
                            {
                                S = S + "'" + thisPar -> Strings -> at (ii) + "' ";
                            }

                            else
                            {
                                S = "''";
                            }

                        }

                        if (ii % 16 == 15)
                        {
                            ProjectList -> push_back (S);
                            S = "";
                        }

                    }
                    if (S.length () != 0)
                    {
                        ProjectList -> push_back (S);
                        S = "";
                    }

                }
                if (S.length () != 0)
                {
                    ProjectList -> push_back (S);
                }

            }
        }
        ProjectList -> push_back ("######");
        ProjectList -> push_back ("Initial_State");
        ProjectList -> push_back ("######");
        ProjectList -> push_back ("######");
        ProjectList -> push_back ("Final_State");
        ProjectList -> push_back ("######");
        if (SaveStateFlag)
        {
            ProjectList -> push_back (SaveStateFileName);
        }

        ProjectList -> push_back ("######");
    }

    if (Global :: LOGVARLOAD)
    {
        ProjectList -> push_back ("LOGVARLOAD");
        ProjectList -> push_back ("######");
    }

    ProjectList -> push_back ("Display_Variable:");
    ProjectList -> push_back ("######");
    for (int ii = 0; ii < SeriesCnt; ii ++) {
    }
    lastVar = NULL;
    Output = "";
    for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator selectedVariablesIt = SelectedVariables -> begin (); selectedVariablesIt != SelectedVariables -> end (); selectedVariablesIt ++) {
        long lay, dim;
        ExtractHruLay (selectedVariablesIt -> first, dim, lay);
        ClassVar * thisVar = selectedVariablesIt -> second;
        if (thisVar != NULL)
        {
            if (thisVar -> TchrtOpt)
            {
                dim = - dim;
            }

            string SS = to_string (dim);
            if (thisVar -> lay > 0)
            {
                SS += "," + to_string (lay);
            }

            string Mod = thisVar -> module;
            if (lastVar == NULL)
            {
                Output = (Mod + " " + thisVar -> name + " ").c_str () + SS;
            }

            else
            if (lastVar != thisVar)
            {
                ProjectList -> push_back (Output);
                Output = (Mod + " " + thisVar -> name + " ").c_str () + SS;
            }

            else
            {
                Output += " " + SS;
            }

            lastVar = thisVar;
        }

    }
    if (Output.length () != 0)
    {
        ProjectList -> push_back (Output);
    }

    ProjectList -> push_back ("######");
    ProjectList -> push_back ("Display_Observation:");
    ProjectList -> push_back ("######");
    lastVar = NULL;
    string kind, lastkind;
    Output = "";
    for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = SelectedObservations -> begin (); it != SelectedObservations -> end (); it ++) {
        string S = it -> first;
        string FullName;
        long dim = 0, lay = 0;
        kind = "_obs";
        string Name = GetObservationName (it -> first);
        ExtractHruLay (it -> first, dim, lay);
        TSeries * cdSeries = it -> second;
        ClassVar * thisVar;
        thisVar = NULL;
        thisVar = (ClassVar *) cdSeries -> Tag;
        if (! thisVar || ! thisVar -> FileData)
        {
            if (! thisVar)
            {
                std :: list < std :: pair < std :: string, ClassVar * >> :: iterator pos;
                for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = SelectedVariables -> begin (); it != SelectedVariables -> end () || it -> first != FullName; it ++) {
                    pos = it;
                }
                if (pos != SelectedVariables -> end ())
                {
                    thisVar = pos -> second;
                }

                else
                {
                    thisVar = VarFind (string (string ("obs ") + Name.c_str ()));
                }

            }

        }

        string SS = to_string (dim);
        if (lay > 0)
        {
            SS += "," + to_string (lay);
        }

        if (Output != "" && (thisVar != lastVar || kind != lastkind))
        {
            ProjectList -> push_back (Output + " " + lastkind);
            if (thisVar)
            {
                Output = (thisVar -> module + " " + Name.c_str () + " " + SS.c_str ()).c_str ();
            }

            else
            {
                Output = (string ("obs ") + Name.c_str () + " " + SS.c_str ()).c_str ();
            }

        }

        else
        if (lastVar)
        {
            Output += " " + SS;
        }

        else
        {
            if (thisVar != NULL)
            {
                Output = (thisVar -> module + " " + Name.c_str () + " " + SS.c_str ()).c_str ();
            }

        }

        lastVar = thisVar;
        lastkind = kind;
    }
    if (Output.length () != 0)
    {
        ProjectList -> push_back (Output + " " + kind);
    }

    ProjectList -> push_back ("######");
    if (this -> getAutoRun ())
    {
        ProjectList -> push_back ("Auto_Run");
        ProjectList -> push_back ("######");
    }

    if (this -> getAutoExit ())
    {
        ProjectList -> push_back ("Auto_Exit");
        ProjectList -> push_back ("######");
    }

    if (this -> getReportAll ())
    {
        ProjectList -> push_back ("Log_All");
        ProjectList -> push_back ("######");
    }

    else
    {
        ProjectList -> push_back ("Log_Last");
        ProjectList -> push_back ("######");
    }

    ProjectList -> push_back ("TChart:");
    ProjectList -> push_back ("######");
    ProjectList -> push_back ("######");
    ofstream file (filepath.c_str ());
    if (file)
    {
        for (std :: list < std :: string > :: iterator it = ProjectList -> begin (); it != ProjectList -> end (); it ++) {
            file << it -> c_str () << endl;
        }
        file.close ();
    }

    else
    {
        CRHMException e = CRHMException ("Cannot open file at " + filepath + " to save project file.", TExcept :: ERR);
        CRHMLogger :: instance () -> log_run_error (e);
    }

    ProjectList -> clear ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SaveProject(string prj_description, string filepath)@@@CRHMmain.cpp>");
}
string CRHMmain :: GetObservationName (string vname)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObservationName(string vname)@@@CRHMmain.cpp>");
    int pos = vname.find_first_of ('(');
    std :: string name = vname.substr (0, pos);
    std :: map < std :: string, ClassVar * > :: iterator it = AllObservations -> find (name);
    if (it != AllObservations -> end ())
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationName(string vname)@@@CRHMmain.cpp>");
        return it -> first;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationName(string vname)@@@CRHMmain.cpp>");
        return "";
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationName(string vname)@@@CRHMmain.cpp>");
}
string CRHMmain :: ExtractHruLayFunct (string S, long & Hru, long & Lay, string & Funct, string & FullName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ExtractHruLayFunct(string S, long & Hru, long & Lay, string & Funct, string & FullName)@@@CRHMmain.cpp>");
    long jj = S.rfind ("(");
    long jj1 = S.find (",");
    long jj2 = S.rfind (")");
    long jj3 = S.rfind ("_");
    long jj4 = S.rfind (")");
    Lay = 0;
    if (jj1 != 0)
    {
        Lay = stoi (S.substr (jj1 + 1, jj2 - jj1 - 1));
    }

    else
    {
        jj1 = jj2;
    }

    if (! HruNames)
    {
        Hru = stoi (S.substr (jj + 1, jj1 - jj - 1));
        if (jj3 > jj2)
        {
            Funct = S.substr (jj4 + 1, S.length ());
        }

    }

    else
    {
        string sub = S.substr (jj + 1, jj1 - jj - 1);
        bool found = false;
        for (size_t i = 0; i < ListHruNames -> size (); i ++) {
            if (ListHruNames -> at (i) == sub)
            {
                Hru = i;
                found = true;
            }

        }
        if (found == false)
        {
            Hru = - 1;
        }

        if (Hru == - 1)
        {
            Hru = stoi (S.substr (jj + 1, jj1 - jj - 1));
        }

        else
        {
            if (Hru == 0)
            {
                ++ Hru;
            }

        }

    }

    FullName = S.substr (1, jj2);

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLayFunct(string S, long & Hru, long & Lay, string & Funct, string & FullName)@@@CRHMmain.cpp>");
    return S.substr (1, jj - 1);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLayFunct(string S, long & Hru, long & Lay, string & Funct, string & FullName)@@@CRHMmain.cpp>");
}
void CRHMmain :: ClearModules (bool All)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ClearModules(bool All)@@@CRHMmain.cpp>");
    ModVarRemove (Global :: MapVars);
    Global :: SharedMapPars.clear ();
    if (All)
    {
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
            modIt -> second -> reset ();
        }
    }

    Global :: OurModulesList -> clear ();
    if (All)
    {
        AdminMacro.MacroClear ();
        Global :: MacroModulesList -> clear ();
    }

    AllVariables -> clear ();
    SelectedVariables -> clear ();
    if (cdSeries)
    {
        cdSeries = NULL;
        SeriesCnt = 0;
    }

    Global :: BuildFlag = TBuild :: BUILD;
    Global :: MapAKA.clear ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ClearModules(bool All)@@@CRHMmain.cpp>");
}
void CRHMmain :: GetObservationNames (char * obsfilepath)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObservationNames(char * obsfilepath)@@@CRHMmain.cpp>");
    FILE * obfile = fopen (obsfilepath, "r");
    char line [128];

    char obsname [128]
    {
    }
    ;

    char obsnames [50] [128]
    {
    }
    ;
    int obsindex = 0;
    int j = 0;
    char * readErrorIndicator;
    readErrorIndicator = fgets (line, sizeof line, obfile);
    if (readErrorIndicator == NULL)
    {
        CRHMException e = CRHMException ("Error reading and discarding the first line of an obsfile.", TExcept :: TERMINATE);
        CRHMLogger :: instance () -> log_run_error (e);
    }

    while (fgets (line, sizeof line, obfile) != NULL) {
        obsname [0] = '\0';
        if (line [0] == '#')
        {
            break;
        }

        for (unsigned int i = 0; i < strlen (line); i ++) {
            obsname [i] = line [i];
            if (line [i] == ' ')
            {
                obsname [i] = '\0';
                strcpy (obsnames [j], obsname);
                break;
            }

        }
        for (int i = 0; i < j; i ++) {

            char test [128]
            {
            }
            ;
            test [0] = '$';
            test [1] = '\0';
            strcat (test, obsnames [i]);
            if (strcmp (obsname, test) == 0)
            {
                j --;
                break;
            }

        }
        j ++;
    }
    fclose (obfile);
    FILE * fp = fopen ("datatransfer.txt", "w");
    for (int i = 0; i < j; i ++) {
        fputs (strcat (obsnames [i], "\n"), fp);
    }
    fclose (fp);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationNames(char * obsfilepath)@@@CRHMmain.cpp>");
}
void CRHMmain :: GetObservationData (char * obsfilepath, char * observationname)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObservationData(char * obsfilepath, char * observationname)@@@CRHMmain.cpp>");
    int length = strlen (observationname);
    if (observationname [length - 1] == '\n')
    {
        observationname [length - 1] = '\0';
    }

    FILE * obfile = fopen (obsfilepath, "r");
    char line [128];

    char obsname [128]
    {
    }
    ;
    char * token, obsnames [50] [128] {};
    int obsindex = 0;
    int j = 0;
    char * readErrorIndicator;
    readErrorIndicator = fgets (line, sizeof line, obfile);
    if (readErrorIndicator == NULL)
    {
        CRHMException e = CRHMException ("Error reading and discarding the first line of an obsfile.", TExcept :: TERMINATE);
        CRHMLogger :: instance () -> log_run_error (e);
    }

    while (fgets (line, sizeof line, obfile) != NULL) {
        obsname [0] = '\0';
        if (line [0] == '#')
        {
            break;
        }

        for (unsigned int i = 0; i < strlen (line); i ++) {
            obsname [i] = line [i];
            if (line [i] == ' ')
            {
                obsname [i] = '\0';
                strcpy (obsnames [j], obsname);
                break;
            }

        }
        if (strcmp (obsname, observationname) == 0)
        {
            obsindex = j + 1;
        }

        for (int i = 0; i < j; i ++) {

            char test [128]
            {
            }
            ;
            test [0] = '$';
            test [1] = '\0';
            strcat (test, obsnames [i]);
            if (strcmp (obsname, test) == 0)
            {
                j --;
                break;
            }

        }
        j ++;
    }
    observationseries = new TSeries ();
    observationseries -> Title = observationname;
    int obscount = j;

    char tokens [50] [50]
    {
    }
    ;
    int tokencount = 0;
    double obsvalue = 0.0;
    int dateelements = 0, year, month, day, hour;
    double ddate;
    while (fgets (line, sizeof line, obfile) != NULL) {
        tokencount = 0;
        token = strtok (line, " \t");
        while (token != NULL) {
            strcpy (tokens [tokencount], token);
            tokencount ++;
            token = strtok (NULL, " \t");
        }
        if ((tokencount - obscount + obsindex - 1) > 0)
        {
            obsvalue = atof (tokens [tokencount - obscount + obsindex - 1]);
        }

        else
        {
            CRHMException Except ("Reading an obs file attempted to read before the begining of an array", TExcept :: TERMINATE);
        }

        dateelements = tokencount - obscount;
        if (dateelements == 1)
        {
            ddate = atof (tokens [0]);
        }

        else
        {
            year = atoi (tokens [0]);
            month = atoi (tokens [1]);
            day = atoi (tokens [2]);
            hour = atoi (tokens [3]);
            ddate = StandardConverterUtility :: GetDateTimeInDouble (year, month, day, hour, 0, 0);
        }

        observationseries -> AddXY (ddate, obsvalue);
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationData(char * obsfilepath, char * observationname)@@@CRHMmain.cpp>");
}
string CRHMmain :: BuildHru (string S, long Hru, TDim dimen)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::BuildHru(string S, long Hru, TDim dimen)@@@CRHMmain.cpp>");
    if (! HruNames)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildHru(string S, long Hru, TDim dimen)@@@CRHMmain.cpp>");
        return S + "(" + to_string (Hru) + ")";
    }

    else
    {
        string SS;
        if (dimen == TDim :: BASIN)
        {
            SS = "(" + ListHruNames -> front () + ")";
        }

        else
        {
            SS = "(" + ListHruNames -> at (Hru) + ")";
        }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildHru(string S, long Hru, TDim dimen)@@@CRHMmain.cpp>");
        return S + SS;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildHru(string S, long Hru, TDim dimen)@@@CRHMmain.cpp>");
}
string CRHMmain :: BuildLay (string S, long Lay)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::BuildLay(string S, long Lay)@@@CRHMmain.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildLay(string S, long Lay)@@@CRHMmain.cpp>");
    return S.substr (1, S.length () - 1) + "," + to_string (Lay) + ")";
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildLay(string S, long Lay)@@@CRHMmain.cpp>");
}
void CRHMmain :: SaveState ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SaveState()@@@CRHMmain.cpp>");
    std :: list < std :: string > * StateList;
    StateList = new std :: list < std :: string > ();
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    std :: string S;
    StateList -> push_back ("Description of State File - to be added");
    StateList -> push_back ("######");
    StateList -> push_back ("Time:");
    S = FormatString (Global :: DTnow, "YMD");
    StateList -> push_back (S);
    StateList -> push_back ("######");
    StateList -> push_back ("Dimension:");
    StateList -> push_back (std :: to_string (Global :: nhru) + " " + std :: to_string (Global :: nlay));
    StateList -> push_back ("######");
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType < TVar :: Read && thisVar -> StatVar)
        {
            S = std :: string (thisVar -> module.c_str ()) + " " + std :: string (thisVar -> name.c_str ());
            StateList -> push_back (S);
            S = "";
            if (thisVar -> lay == 0)
            for (int ii = 0; ii < thisVar -> dim; ii ++) {
                if (thisVar -> values != NULL)
                {
                    S = S + FloatToStrF (thisVar -> values [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                }

                else
                if (thisVar -> ivalues != NULL)
                {
                    S = S + FloatToStrF (thisVar -> ivalues [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                }

                else
                {
                    S = S + "-0 ";
                }

                if (ii % 10 == 9)
                {
                    StateList -> push_back (S);
                    S = "";
                }

            }

            else
            for (int ll = 0; ll < thisVar -> lay; ll ++) {
                for (int ii = 0; ii < thisVar -> dim; ii ++) {
                    if (thisVar -> layvalues != NULL)
                    {
                        S = S + FloatToStrF (thisVar -> layvalues [ll] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                    }

                    else
                    if (thisVar -> ivalues != NULL)
                    {
                        S = S + FloatToStrF (thisVar -> ilayvalues [ll] [ii], TFloatFormat :: ffGeneral, 4, 0) + " ";
                    }

                    else
                    {
                        S = S + "-0 ";
                    }

                    if (ii % 10 == 9)
                    {
                        StateList -> push_back (S);
                        S = "";
                    }

                }
                if (! S.empty ())
                {
                    StateList -> push_back (S);
                }

                S = "";
            }

            if (! S.empty ())
            {
                StateList -> push_back (S);
            }

            StateList -> push_back ("######");
        }

    }
    ofstream file;
    file.open (SaveStateFileName);
    if (file.is_open ())
    {
        for (std :: list < std :: string > :: iterator it = StateList -> begin (); it != StateList -> end (); it ++) {
            file << it -> c_str () << endl;
        }
        file.close ();
    }

    else
    {
        CRHMException e = CRHMException ("Cannot open file " + SaveStateFileName + " to save state file.", TExcept :: ERR);
        CRHMLogger :: instance () -> log_run_error (e);
    }

    delete StateList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SaveState()@@@CRHMmain.cpp>");
}
void CRHMmain :: print_progress_start ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::print_progress_start()@@@CRHMmain.cpp>");
    std :: cout << "Running simulation...\n";
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::print_progress_start()@@@CRHMmain.cpp>");
}
void CRHMmain :: print_progress (long current_step, long last_step, int print_frequency)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::print_progress(long current_step, long last_step, int print_frequency)@@@CRHMmain.cpp>");
    if (current_step % (Global :: Freq * print_frequency) == 0)
    {
        std :: cout << '\r' << setprecision (3) << setfill (' ') << setw (25) << (((float) current_step / (float) last_step) * 100.0f) << "% complete.";
        std :: cout.flush ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::print_progress(long current_step, long last_step, int print_frequency)@@@CRHMmain.cpp>");
}
void CRHMmain :: print_progress_end ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::print_progress_end()@@@CRHMmain.cpp>");
    std :: cout.flush ();
    std :: cout << '\r' << setfill (' ') << setw (25) << 100.0f << "% Complete!";
    std :: cout.flush ();
    std :: cout << "\n\n\n";
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::print_progress_end()@@@CRHMmain.cpp>");
}