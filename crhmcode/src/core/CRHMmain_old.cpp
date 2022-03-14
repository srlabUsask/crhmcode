#if defined (_WIN32)
    #include "../stdafx.h"
    #include "CRHMAboutBox.h"
#endif

#include "CRHMmain.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include "GlobalDll.h"
#include "ClassModule/ClassModule.h"
#include "NewModules.h"
#include "MacroUnit.h"
#include "Common.h"
#include "StandardConverterUtility.h"
#include <time.h>
Administer AdminMacro ("03/24/06", "Macro");
using namespace std; using namespace CRHM; bool ReportAll = true;
extern string AKAstrings [];
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

CRHMmain * CRHMmain :: getInstance ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getInstance()@@@CRHMmain_old.cpp>");
    if (instance == 0)
    {
        instance = new CRHMmain ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getInstance()@@@CRHMmain_old.cpp>");
    return instance;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getInstance()@@@CRHMmain_old.cpp>");
}
CRHMmain :: CRHMmain ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::CRHMmain()@@@CRHMmain_old.cpp>");
    FormCreate ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::CRHMmain()@@@CRHMmain_old.cpp>");
}
CRHMmain :: ~CRHMmain ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::~CRHMmain()@@@CRHMmain_old.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::~CRHMmain()@@@CRHMmain_old.cpp>");
}
double CRHMmain :: GetStartDate ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetStartDate()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetStartDate()@@@CRHMmain_old.cpp>");
    return Picker1;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetStartDate()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: setStartDate (double sdate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setStartDate(double sdate)@@@CRHMmain_old.cpp>");
    Picker1 = sdate;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setStartDate(double sdate)@@@CRHMmain_old.cpp>");
}
double CRHMmain :: GetEndDate ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetEndDate()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetEndDate()@@@CRHMmain_old.cpp>");
    return Picker2;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetEndDate()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: setEndDate (double edate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setEndDate(double edate)@@@CRHMmain_old.cpp>");
    Picker2 = edate;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setEndDate(double edate)@@@CRHMmain_old.cpp>");
}
TStringList * CRHMmain :: getSelectedVariables ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getSelectedVariables()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedVariables()@@@CRHMmain_old.cpp>");
    return ListBox3;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedVariables()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: setSelectedVariables (TStringList * t)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setSelectedVariables(TStringList * t)@@@CRHMmain_old.cpp>");
    ListBox3 = t;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setSelectedVariables(TStringList * t)@@@CRHMmain_old.cpp>");
}
TStringList * CRHMmain :: getSelectedObservations ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getSelectedObservations()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedObservations()@@@CRHMmain_old.cpp>");
    return ListBox4;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getSelectedObservations()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: setSelectedObservatoions (TStringList * t)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::setSelectedObservatoions(TStringList * t)@@@CRHMmain_old.cpp>");
    ListBox4 = t;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::setSelectedObservatoions(TStringList * t)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: BldModelClick ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::BldModelClick()@@@CRHMmain_old.cpp>");
    ProjectOpen = true;
    InitModules ();
    SqueezeParams ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BldModelClick()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: makeQuery (string statementtype, string statement, string fields, int fieldcount)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::makeQuery(string statementtype, string statement, string fields, int fieldcount)@@@CRHMmain_old.cpp>");
    ofstream queryfile;
    queryfile.open ("d:/test/query.txt");
    queryfile << "database name = " << "watersecurity" << endl;
    queryfile << "userid = " << "root" << endl;
    queryfile << "password = " << "none" << endl;
    queryfile << "statement type = " << statementtype << endl;
    queryfile << "statement = " << statement << endl;
    queryfile << "field count = " << fieldcount << endl;
    queryfile << "fields = " << fields << endl;
    queryfile.close ();
    system ("java -jar -min d:/javadatabaseaccess/DatabaseAccess.jar");
    ifstream resultfile;
    string line = "";
    resultfile.open ("d:/test/result.txt");
    queryResult -> Clear ();
    while (! resultfile.eof ()) {
        if (getline (resultfile, line))
        {
            queryResult -> Add (line);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::makeQuery(string statementtype, string statement, string fields, int fieldcount)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: getQueryValue (int row, int column)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getQueryValue(int row, int column)@@@CRHMmain_old.cpp>");
    string res = queryResult -> Strings [row];
    int l = res.length ();
    int cc = 0;
    for (int i = 0; i < l; i ++) {
        if (cc == column - 1)
        {
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getQueryValue(int row, int column)@@@CRHMmain_old.cpp>");
    return "";
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getQueryValue(int row, int column)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: DoPrjOpen (string OpenNamePrj, string PD)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
    OpenProjectPath = OpenNamePrj;
    MapPar :: iterator itPar;
    ClassPar * thisPar = NULL;
    ClassVar * thisVar;
    ifstream DataFile;
    long Variation;
    char module [80], param [80], Descrip [80], Line [80], name [80];
    string S, s;
    string SS;
    DataFile.open (OpenNamePrj.c_str ());
    if (! DataFile)
    {
        Common :: Message ("cannot open file", "File Error");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
        return;
    }

    ProjectDirectory = GetCurrentDir ();
    Dt0 = time (NULL);
    bool Prj = Common :: lowercase (OpenNamePrj).find (".prj") != string :: npos;
    DataFile.getline (Descrip, 80);
    DataFile.ignore (80, '#');
    DataFile.getline (Line, 80);
    Global :: MacroModulesList -> Clear ();
    try {
        do {
            DataFile >> S;
            if (DataFile.eof ())
            {
                break;
            }

            DataFile.ignore (80, '#');
            DataFile.getline (Line, 80);
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
                    if (Type == VARG || Type == OBSR || Type == OBSF)
                    {
                        DataFile >> source;
                        alias += ' ' + source;
                    }

                    if (Type != AKAERROR)
                    {
                        Pairstr2 Item = Pairstr2 (type + " " + module + " " + name, alias);
                        Global :: MapAKA.insert (Item);
                    }

                    if (DataFile.eof ())
                    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
                        return;
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
                    Global :: MacroModulesList -> Add (sub);
                    getline (DataFile, S);
                }
                MacroLoad ();
            }

            else
            if (S == "Observations:")
            {
                getline (DataFile, S);
                while (S [0] != '#') {
                    SS = S;
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
                        Common :: Message (SS.c_str (), "Cannot find observation file");
                    }

                    getline (DataFile, S);
                }
            }

            else
            if (S == "Dates:")
            {
                int D [3];
                double DT;
                for (int ii = 0; ii < 3; ii ++)
                    DataFile >> D [ii];
                DT = StandardConverterUtility :: EncodeDateTime ((int) D [0], (int) D [1], (int) D [2], 0, 0);
                Picker1 = DT;
                int c;
                while ((c = DataFile.peek (), c == 32)) {
                    DataFile.get ();
                    c = DataFile.peek ();
                }
                if (isdigit (c) && ObsFilesList -> Count == 0)
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
                Picker2 = DT;
                DataFile >> S;
            }

            else
            if (S == "Modules:")
            {
                Global :: OurModulesList -> Clear ();
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
                        Variation = pow (2, S [idx + 1] - char ('1'));
                        s = S.substr (0, idx);
                    }

                    else
                    {
                        Variation = 0;
                    }

                    if (! InGrp)
                    {
                        Global :: OurModulesList -> AddObject (s, (TObject *) Variation);
                    }

                    idx = S.find (' ');
                    S = S.substr (idx + 1);
                    idx = S.rfind (' ');
                    S = S.substr (0, idx);
                    transform (S.begin (), S.end (), S.begin (), :: toupper);
                    idx = S.rfind (".DLL");
                }
                for (int ii = Global :: OurModulesList -> Count - 1; ii >= 0; -- ii) {
                    string Name = Global :: OurModulesList -> Strings [ii];
                    int jj = Global :: AllModulesList -> IndexOf (Name);
                    if (jj < 0)
                    {
                        CRHMException Except ("Unknown Module: " + string (Name.c_str ()), ERR);
                        Common :: Message (Except.Message.c_str (), "Unknown Module: incorrect CRHM version or DLL not loaded");
                        LogError (Except);
                        Global :: OurModulesList -> Delete (ii);
                        DataFile.seekg (0, ios_base :: end);
                    }

                    else
                    {
                        Variation = ((long) Global :: OurModulesList -> Objects [ii]);
                        ((ClassModule *) Global :: AllModulesList -> Objects [jj]) -> variation = Variation;
                        Global :: OurModulesList -> Objects [ii] = Global :: AllModulesList -> Objects [jj];
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
                        return;
                    }

                    DataFile.ignore (80, '\n');
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
                    if (string (module, strlen (module)) == "Shared")
                    {
                        MapPar :: iterator itPar;
                        for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); ++ itPar) {
                            thisPar = (* itPar).second;
                            if (thisPar -> param == string (param, strlen (param)))
                            {
                                if (thisPar -> dim == Cols / thisPar -> lay)
                                {
                                    break;
                                }

                                else
                                if (thisPar -> varType == CRHM :: Txt && thisPar -> dimen < CRHM :: NHRU)
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
                                    if (thisPar -> param == string (param, strlen (param)) && (thisPar -> dim == Cols / thisPar -> dim))
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
                            strcpy (module, thisPar -> module.c_str ());
                        }

                    }

                    if (thisPar)
                    {
                        ClassPar * newPar = new ClassPar (* thisPar);
                        newPar -> module = module;
                        if (thisPar -> varType == CRHM :: Txt)
                        {
                            newPar -> Strings -> DelimitedText (S.c_str ());
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
                                    if (newPar -> varType == CRHM :: Float)
                                    {
                                        float x;
                                        instr >> x;
                                        if (instr.fail ())
                                        {
                                            break;
                                        }

                                        newPar -> layvalues [jj] [ii] = x;
                                    }

                                    else
                                    if (newPar -> varType == CRHM :: Int)
                                    {
                                        float x;
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
                                            if (newPar -> varType == CRHM :: Float)
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
                                                if (newPar -> varType == CRHM :: Float)
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

                        if (string (module) == "Shared")
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
                        if (string (param) != "Use_Observations_As_Supplied")
                        {
                            CRHMException Except ("Unknown Module Parameter: " + string (module) + " -> " + string (param) + " in " + OpenNamePrj, ERR);
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
                        return;
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

                            if (Common :: IndexOf (ListBox3, SS) == - 1 && Index <= thisVar -> dim)
                            {
                                ListBox3 -> AddObject (SS, (TObject *) thisVar);
                            }

                        }
                    }

                    else
                    {
                        CRHMException Except ("Unknown Variable " + S + " in " + string (OpenNamePrj.c_str ()), ERR);
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
                        return;
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
                            if (Common :: IndexOf (ListBox4, SS) == - 1)
                            {
                                TSeries * cdSeries = NULL;
                                if (thisVar -> FileData -> Times == NULL)
                                {
                                    double Dif = Picker2 - Picker1;
                                    TSeries * cdSeries = new TSeries (((int) (Dif * thisVar -> FileData -> Freq)) * thisVar -> FileData -> ModN);
                                    cdSeries -> Tag = thisVar;
                                    cdSeries -> Title = SS;
                                }

                                ListBox4 -> AddObject (SS, (TObject *) cdSeries);
                            }

                        }
                    }

                    else
                    {
                        CRHMException Except ("Unknown Variable " + S + " in " + string (OpenNamePrj.c_str ()), ERR);
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
                    if (FindFileName (SS))
                    {
                        OpenNameState = SS;
                        OpenStateFlag = true;
                    }

                    else
                    {
                        OpenNameState = "";
                    }

                    DataFile.ignore (80, '#');
                    DataFile >> S;
                }

            }

            else
            if (S == "Final_State")
            {
                getline (DataFile, S);
                if (S [0] != '#')
                {
                    DataFile >> S;
                }

            }

            else
            if (S == "Log_Last")
            {
                ReportAll = false;
            }

            else
            if (S == "Log_All")
            {
                ReportAll = true;
            }

            else
            if (S == "Auto_Run")
            {
                ;
            }

            else
            if (S == "Auto_Exit")
            {
                ;
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
        return;
    }
    DataFile.close ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoPrjOpen(string OpenNamePrj, string PD)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: SetSharedParams (ClassPar * basinPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SetSharedParams(ClassPar * basinPar)@@@CRHMmain_old.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SetSharedParams(ClassPar * basinPar)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: FormCreate (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FormCreate(void)@@@CRHMmain_old.cpp>");
    Global :: BuildFlag = CRHM :: BUILD;
    Global :: maxhru = 1;
    Global :: maxlay = 1;
    Global :: maxobs = 1;
    Global :: Freq = 48;
    Global :: Interval = 1.0 / Global :: Freq;
    cdSeries = NULL;
    double Dt = time (NULL);
    OpenStateFlag = false;
    Global :: nhru = Global :: maxhru;
    Global :: nobs = Global :: maxobs;
    Global :: nlay = Global :: maxlay;
    Global :: OBS_AS_IS = false;
    ObsFilesList = new TStringList;
    ProjectList = new TStringList;
    PrjObsHelp = new TStringList;
    PrjObsHelp -> AddObject ("", (TObject *) 1);
    Global :: AllModulesList = new TStringList;
    Global :: AllModulesList -> CaseSensitive = true;
    Global :: OurModulesList = new TStringList;
    Global :: OurModulesList -> Sorted = false;
    Global :: MacroModulesList = new TStringList;
    Global :: MacroModulesList -> Sorted = false;
    Global :: AllModelsList = new TStringList;
    Global :: AllModelsList -> Sorted = true;
    Global :: ModelModulesList = new TStringList;
    Global :: ModelModulesList -> Sorted = false;
    Global :: OurHelpList = NULL;
    Global :: PendingDLLModuleList = new TStringList;
    Global :: ReportList = NULL;
    Global :: DeclRootList = new TStringList;
    ListBox1 = new TStringList;
    ListBox2 = new TStringList;
    ListBox3 = new TStringList;
    ListBox4 = new TStringList;
    MoveModulesToGlobal ();
    ((ClassModule *) Global :: PendingDLLModuleList -> Objects [0]) -> OurAdmin -> Accept (mbYesToAll);
    ++ InitModCnt;
    Global :: OldModuleName = new TStringList;
    Global :: NewModuleName = new TStringList;
    Global :: OldModuleName -> CommaText ("long, CanopyClearingGap2, pbsm_WQ, Soil_WQ, Netroute_WQ, Netroute_M_D_WQ");
    Global :: NewModuleName -> CommaText ("longVt, CanopyClearingGap, WQ_pbsm, WQ_Soil, WQ_Netroute, WQ_Netroute_M_D");

    #if ! defined NO_MODULES
        for (long ii = 0; ii < Global :: NewModuleName -> Count; ++ ii) {
            long jj = Global :: AllModulesList -> IndexOf (Global :: NewModuleName -> Strings [ii]);
            assert (jj != - 1);
            Global :: OldModuleName -> Objects [ii] = (TObject *) jj;
        }
    #endif

    Global :: CRHMStatus = 0;
    Global :: CurrentModuleRun = - 1;
    Global :: CRHMControlSaveCnt = 0;
    Global :: HRU_OBS_DIRECT = new long * [5];
    for (long jj = 0; jj < 5; ++ jj) {
        Global :: HRU_OBS_DIRECT [jj] = new long [500];
        for (long ii = 0; ii < 500; ++ ii)
            Global :: HRU_OBS_DIRECT [jj] [ii] = ii + 1;
    }
    Global :: HRU_OBS = Global :: HRU_OBS_DIRECT;
    Global :: NaNcheck = false;
    Global :: LOGVARLOAD = false;
    Global :: TimeFormat = MS;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FormCreate(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: InitModules (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::InitModules(void)@@@CRHMmain_old.cpp>");
    ClassVar * thisVar;
    Global :: BuildFlag = CRHM :: DECL;
    for (int ii = 0; ii < Global :: OurModulesList -> Count; ii ++) {
        ((ClassModule *) Global :: OurModulesList -> Objects [ii]) -> nhru = Global :: nhru;
        ((ClassModule *) Global :: OurModulesList -> Objects [ii]) -> decl ();
    }
    Label4Click ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::InitModules(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: Label4Click (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::Label4Click(void)@@@CRHMmain_old.cpp>");
    ClassVar * thisVar;
    MapVar :: iterator itVar;
    string Newname;
    ListBox1 -> Clear ();
    ListBox1 -> Sorted = true;
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType < CRHM :: Read && thisVar -> visibility == CRHM :: USUAL && thisVar -> dimen != CRHM :: NREB)
        {
            Newname = DeclObsName (thisVar);
            if (Common :: IndexOf (ListBox1, Newname) == - 1)
            {
                ListBox1 -> AddObject (Newname, (TObject *) thisVar);
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::Label4Click(void)@@@CRHMmain_old.cpp>");
}
CRHM :: TFun CRHMmain :: FindObservationType (string Kind)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FindObservationType(string Kind)@@@CRHMmain_old.cpp>");
    if (Kind == "_obs")
    {
        Kind = "";
    }

    for (int ii = CRHM :: FOBS; ii <= CRHM :: LAST; ii ++)
        if (Kind == Sstrings [ii])
        {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindObservationType(string Kind)@@@CRHMmain_old.cpp>");
            return (CRHM :: TFun) ii;
        }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindObservationType(string Kind)@@@CRHMmain_old.cpp>");
    return (CRHM :: TFun) 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindObservationType(string Kind)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: SqueezeParams (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SqueezeParams(void)@@@CRHMmain_old.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SqueezeParams(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: SetBasinParams (ClassPar * basinPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SetBasinParams(ClassPar * basinPar)@@@CRHMmain_old.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SetBasinParams(ClassPar * basinPar)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: MacroClick (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::MacroClick(void)@@@CRHMmain_old.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::MacroClick(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ListBoxMacroClear ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ListBoxMacroClear()@@@CRHMmain_old.cpp>");
    ClassVar * thisVar;
    if (SeriesCnt <= 0)
    {
        ListBox3 -> Clear ();
    }

    else
    {
        int indx;
        string serTitle;
        int jj;
        SeriesCnt = ListBox3 -> Count;
        cdSeries = new TSeries * [SeriesCnt];
        int Cnt = Global :: DTmax - Global :: DTmin;
        for (int ii = 0; ii < SeriesCnt; ++ ii)
            cdSeries [ii] = new TSeries (Cnt);
        for (jj = 0; jj < SeriesCnt; jj ++)
            serTitle = cdSeries [jj] -> Title;
        if (indx = ListBox3 -> IndexOf (serTitle), indx > - 1)
        {
            thisVar = (ClassVar *) ListBox3 -> Objects [indx];
            if (thisVar -> DLLName == "Macro")
            {
                for (int kk = jj + 1; kk < SeriesCnt; ++ kk)
                    cdSeries [kk - 1] = cdSeries [kk];
                ListBox3 -> Delete (indx);
                SeriesCnt --;
            }

        }

    }

    for (int ii = 0; ii < ListBox1 -> Count; ii ++) {
        thisVar = (ClassVar *) ListBox1 -> Objects [ii];
        if (thisVar != NULL && thisVar -> DLLName == "Macro")
        {
            ListBox1 -> Delete (ii);
            ii = 0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ListBoxMacroClear()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: MacroLoad (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::MacroLoad(void)@@@CRHMmain_old.cpp>");
    Global :: GroupCntTrk = 0;
    Global :: StructCntTrk = 0;
    ClearModules (false);
    if (Global :: MacroModulesList -> Count > 0)
    {
        int Macro = 0;
        while (Macro < Global :: MacroModulesList -> Count) {
            string s = Global :: MacroModulesList -> Strings [Macro];
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
            while (S = Common :: trim (Global :: MacroModulesList -> Strings [Macro]), SS = S.substr (0, 3), ! (SS == "end" && (S.length () == 3 || S.find_first_of (" /") != string :: npos)) && Global :: MacroModulesList -> Count > Macro) ++ Macro;
            ++ Macro;
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::MacroLoad(void)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: DeclObsName (ClassVar * thisVar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DeclObsName(ClassVar * thisVar)@@@CRHMmain_old.cpp>");
    string Newname = thisVar -> name;
    int jj = Global :: OurModulesList -> IndexOf (thisVar -> module);
    if (jj > - 1 && Newname.rfind ("#") != string :: npos)
    {
        ClassModule * thisModule = (ClassModule *) Global :: OurModulesList -> Objects [jj];
        if (thisModule -> isGroup)
        {
            string AA ("@@");
            AA [1] += thisModule -> GroupCnt;
            Newname += AA;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DeclObsName(ClassVar * thisVar)@@@CRHMmain_old.cpp>");
    return Newname;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DeclObsName(ClassVar * thisVar)@@@CRHMmain_old.cpp>");
}
bool CRHMmain :: OpenObsFile (string FileName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::OpenObsFile(string FileName)@@@CRHMmain_old.cpp>");
    ClassData * FileData;
    if (ObsFilesList -> IndexOf (FileName.c_str ()) != - 1)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain_old.cpp>");
        return false;
    }

    if (ObsFilesList -> Count == 0)
    {
        Global :: DTstart = 0;
        Global :: DTend = 0;
    }

    FileData = new ClassData (FileName);
    if (FileData -> Success)
    {
        if (ObsFilesList -> Count == 0)
        {
            if (FileData -> Times != NULL)
            {
                delete FileData;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain_old.cpp>");
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
        MapVar :: iterator itVar;
        ClassVar * thisVar;
        for (int ii = 0; ii < ListBox1 -> Count; ii ++) {
            thisVar = (ClassVar *) ListBox1 -> Objects [ii];
            if (thisVar && thisVar -> varType >= CRHM :: Read)
            {
                ListBox1 -> Delete (ii);
                ii = 0;
            }

        }
        for (int ii = 0; ii < ListBox3 -> Count; ii ++) {
            thisVar = (ClassVar *) ListBox3 -> Objects [ii];
            if (thisVar && thisVar -> varType >= CRHM :: Read)
            {
                ListBox3 -> Delete (ii);
                ii = 0;
            }

        }
        ListBox2 -> Clear ();
        for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
            thisVar = (* itVar).second;
            if (thisVar && thisVar -> varType >= CRHM :: Read)
            {
                if (Common :: IndexOf (ListBox2, thisVar -> name) == - 1)
                {
                    ListBox2 -> AddObject (thisVar -> name, (TObject *) thisVar);
                }

            }

        }
        ObsFilesList -> AddObject (OpenNameObs, (TObject *) FileData);

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain_old.cpp>");
        return true;
    }

    else
    {
        if (ObsFilesList -> Count == 0)
        {
            Global :: DTstart = 0;
            Global :: DTend = 0;
        }

        delete FileData;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain_old.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::OpenObsFile(string FileName)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ObsCloseClick (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ObsCloseClick(void)@@@CRHMmain_old.cpp>");
    ListBox2 -> Clear ();
    for (int ii = 0; ii < ObsFilesList -> Count; ii ++) {
        ClassData * FileData = (ClassData *) ObsFilesList -> Objects [ii];
        delete FileData;
    }
    ObsFilesList -> Clear ();
    Global :: nobs = 1;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ObsCloseClick(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ObsFileClose (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ObsFileClose(void)@@@CRHMmain_old.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    string S;
    int Pos = ObsFilesList -> IndexOf (S);
    if (Pos == 0 && ObsFilesList -> Count > 1)
    {
        ObsCloseClick ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ObsFileClose(void)@@@CRHMmain_old.cpp>");
        return;
    }

    ListBox2 -> Clear ();
    ClassData * FileData = (ClassData *) ObsFilesList -> Objects [Pos];
    delete FileData;
    ObsFilesList -> Delete (Pos);
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType >= CRHM :: Read)
        {
            if (Common :: IndexOf (ListBox2, (* itVar).second -> name) == - 1)
            {
                ListBox2 -> AddObject ((* itVar).second -> name, (TObject *) (* itVar).second);
            }

        }

    }
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> varType < CRHM :: Read && thisVar -> visibility == CRHM :: USUAL)
        {
            if (Common :: IndexOf (ListBox1, (* itVar).second -> name) == - 1)
            {
                ListBox1 -> AddObject ((* itVar).second -> name, (TObject *) (* itVar).second);
            }

        }

    }
    delete cdSeries;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ObsFileClose(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: FormDestroy (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FormDestroy(void)@@@CRHMmain_old.cpp>");
    for (int ii = 0; ii < ObsFilesList -> Count; ++ ii) {
        ClassData * FileData = (ClassData *) ObsFilesList -> Objects [ii];
        delete FileData;
    }
    delete ObsFilesList;
    ModVarRemove (Global :: MapVars);
    Global :: SharedMapPars.clear ();
    delete ProjectList;
    delete ListBox1;
    delete ListBox2;
    delete ListBox3;
    delete ListBox4;
    delete Global :: OurModulesList;
    delete Global :: ModelModulesList;
    delete Global :: DeclRootList;
    delete Global :: PendingDLLModuleList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FormDestroy(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: FreeChart1 (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FreeChart1(void)@@@CRHMmain_old.cpp>");
    if (SeriesCnt > 0)
    {
        for (int ii = 0; ii < SeriesCnt; ii ++) {
            ClassVar * thisVar = (ClassVar *) cdSeries [ii] -> Tag;
            if (thisVar -> FunKind > CRHM :: FOBS && ! thisVar -> values && ! thisVar -> ivalues)
            {
                delete thisVar;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FreeChart1(void)@@@CRHMmain_old.cpp>");
}
bool CRHMmain :: FileExistsSp (string FileName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FileExistsSp(string FileName)@@@CRHMmain_old.cpp>");
    ifstream DataFile;
    DataFile.open (FileName.c_str ());
    if (DataFile)
    {
        DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FileExistsSp(string FileName)@@@CRHMmain_old.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FileExistsSp(string FileName)@@@CRHMmain_old.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FileExistsSp(string FileName)@@@CRHMmain_old.cpp>");
}
bool CRHMmain :: FindFileName (string & FileName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
    string FilePart;
    if (FileExistsSp (FileName))
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
        return true;
    }

    string :: size_type Pos = FileName.find_last_of ("\\/");
    if (Pos)
    {
        FilePart = FileName.substr (Pos + 1, FileName.length ());
        if (FileExistsSp (FilePart))
        {
            FileName = FilePart;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
        return true;
    }

    NewFileName = ApplicationDir + FilePart;
    if (FileExistsSp (NewFileName))
    {
        FileName = NewFileName;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
        return true;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
    return false;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::FindFileName(string & FileName)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: ExtractHruLay (string S, long & Hru, long & Lay)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ExtractHruLay(string S, long & Hru, long & Lay)@@@CRHMmain_old.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLay(string S, long & Hru, long & Lay)@@@CRHMmain_old.cpp>");
    return S.substr (0, jj);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLay(string S, long & Hru, long & Lay)@@@CRHMmain_old.cpp>");
}
MMSData * CRHMmain :: RunClick2Start ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick2Start()@@@CRHMmain_old.cpp>");
    ClassVar * thisVar;
    float ** mmsData;
    long ** mmsDataL;
    bool GoodRun = true;
    MMSData * mmsdata = new MMSData ();
    MapVar :: iterator itVar;
    Global :: ModuleBitSet.reset ();
    Global :: HRU_OBS = Global :: HRU_OBS_DIRECT;
    Global :: OBS_AS_IS = false;
    Global :: WQ_prj = false;
    if (Global :: IndxMin != 0)
    {
        Global :: IndxMin = 0;
    }

    if (Global :: IndxMin != 0)
    {

        #if defined (_WIN32)
            AfxMessageBox (_T ("First observation day - not an entire day"));
        #endif

        #if defined (__linux__) || defined (__APPLE__)
            string message = "First observation day - not an entire day";
            LogMessageX (message.c_str ());
        #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain_old.cpp>");
        return mmsdata;
    }

    if (ListBox3 -> Count == 0)
    {

        #if defined (_WIN32)
            AfxMessageBox (_T ("No model output selected"));
        #endif

        #if defined (__linux__) || defined (__APPLE__)
            string message = "No model output selected";
            LogMessageX (message.c_str ());
        #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain_old.cpp>");
        return mmsdata;
    }

    string Message = "Project file: " + OpenNamePrj;
    LogMessageX (Message.c_str ());
    LogMessageX (" ");
    for (int ii = 0; ii < ObsFilesList -> Count; ii ++) {
        Message = "Observation file: " + ObsFilesList -> Strings [ii];
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
    for (int ii = 0; ii < Global :: OurModulesList -> Count; ++ ii) {
        ClassModule * thisModule = (ClassModule *) Global :: OurModulesList -> Objects [ii];
        S += Global :: OurModulesList -> Strings [ii];
        if (thisModule -> variation != 0)
        {
            string AA ("#0");
            AA [1] += log (thisModule -> variation) / log (2) + 1;
            S += AA;
        }

        if (ii == Global :: OurModulesList -> Count - 1)
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

    Global :: DeclRootList -> Clear ();
    ((ClassModule *) Global :: OurModulesList -> Objects [0]) -> InitReadObs ();
    double DTstartR = Picker1;
    double DTendR = Picker2;
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
    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx + 1);
    int Modii = 0;
    Global :: MapVarsGet.clear ();
    Global :: MapVarsPut.clear ();
    Global :: MapObsGet.clear ();
    try {
        for (Modii = 0; Modii < Global :: OurModulesList -> Count; Modii ++)
            ((ClassModule *) (Global :: OurModulesList -> Objects [Modii])) -> initbase ();
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
    if (ObsFilesList -> Count > 0)
    {
        FileData = (ClassData *) ObsFilesList -> Objects [0];
    }

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

    if (GoodRun)
    {
        if (! OpenStateFlag)
        {
            thisPar = ParFind ("basin INIT_STATE");
            if (thisPar && thisPar -> Strings -> Count && ! thisPar -> Strings -> Strings [0].empty ())
            {
                OpenNameState = thisPar -> Strings -> Strings [0];
                OpenStateFlag = true;
            }

            else
            {
                MapPar :: iterator itPar;
                for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
                    thisPar = (* itPar).second;
                    if (thisPar -> param == "INIT_STATE" && thisPar -> Strings -> Count && ! thisPar -> Strings -> Strings [0].empty ())
                    {
                        OpenNameState = thisPar -> Strings -> Strings [0];
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
        ((ClassModule *) Global :: OurModulesList -> Objects [0]) -> InitReadObs ();
        for (int ii = 0; ii < Modii; ii ++)
            ((ClassModule *) (Global :: OurModulesList -> Objects [ii])) -> finish (false);
        Global :: BuildFlag = CRHM :: DECL;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain_old.cpp>");
        return mmsdata;
    }

    Global :: BuildFlag = CRHM :: RUN;
    Global :: DTmax = (int) ((DTendR - Global :: DTstart) * Global :: Freq);
    SeriesCnt = ListBox3 -> Count;
    int Cnt = Global :: DTmax - Global :: DTmin;
    cdSeries = new TSeries * [SeriesCnt];
    for (int ii = 0; ii < SeriesCnt; ++ ii)
        cdSeries [ii] = new TSeries (Cnt);
    mmsData = new float * [SeriesCnt];
    mmsDataL = new long * [SeriesCnt];
    for (int ii = 0; ii < ListBox3 -> Count; ii ++) {
        thisVar = (ClassVar *) (ListBox3 -> Objects [ii]);
        cdSeries [ii] -> Tag = thisVar;
        string S = ListBox3 -> Strings [ii];
        cdSeries [ii] -> Title = S;
        long lay, dim;
        S = ExtractHruLay (S, dim, lay);
        if (thisVar -> varType == CRHM :: Float)
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
        if (thisVar -> varType == CRHM :: Int)
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
    Global :: ModuleBitSet.reset ();
    ClassModule * Obs_preset;
    int jj = Global :: OurModulesList -> IndexOf ("obs");
    if (jj == - 1)
    {
        Obs_preset = NULL;
    }

    else
    {
        Obs_preset = (ClassModule *) Global :: OurModulesList -> Objects [jj];
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain_old.cpp>");
    return mmsdata;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Start()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: RunClick2Middle (MMSData * mmsdata, long startdate, long enddate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick2Middle(MMSData * mmsdata, long startdate, long enddate)@@@CRHMmain_old.cpp>");
    float ** mmsData = mmsdata -> mmsData;
    long ** mmsDataL = mmsdata -> mmsDataL;
    bool GoodRun = mmsdata -> GoodRun;
    string S = mmsdata -> S;
    ClassModule * Obs_preset = mmsdata -> obs_preset;
    bool First = true;
    try {
        int iter = 0;
        for (Global :: DTindx = startdate; Global :: DTindx < enddate; Global :: DTindx ++) {
            iter ++;
            if (Global :: Freq == 1)
            {
                Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx);
            }

            else
            {
                Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx + 1);
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
                    LogMessage ("Terminate fast loop aheadMain", DD);
                }

                else
                if (Global :: DTnow == Global :: RapidAdvanceTo && Global :: LoopCnt)
                {
                    if (Global :: LoopCntDown == - 1)
                    {
                        Global :: LoopCntDown = Global :: LoopCnt;
                        StatePar = ParFind ("basin StateVars_to_Update");
                        ControlSaveState (true, StatePar, Global :: RunUpBitSet);
                        LogMessage ("Initialise LoopTo Main", DD);
                    }

                }

                else
                if (Global :: DTnow == Global :: LoopTo && Global :: LoopCnt)
                {
                    ControlReadState (true, StatePar);
                    -- Global :: LoopCntDown;
                    LogMessage ("Reached loop Main", DD);
                    if (Global :: LoopCntDown <= 0)
                    {
                        ResetLoopList ();
                        Global :: CRHMStatus &= 125;
                        Global :: CRHMStatus |= 4;
                        Global :: LoopCntDown = - 1;
                        LogMessage ("Terminate LoopTo Main", DD);
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

            for (Global :: CurrentModuleRun = 0; Global :: CurrentModuleRun < Global :: OurModulesList -> Count; Global :: CurrentModuleRun ++) {
                long Last = Global :: CRHMControlSaveCnt;
                ClassModule * p = (ClassModule *) Global :: OurModulesList -> Objects [Global :: CurrentModuleRun];
                if (p -> GroupCnt && ((ClassMacro *) p) -> ObsModule)
                {
                    ((ClassMacro *) p) -> ObsModule -> pre_run ();
                }

                p -> ReadObs (Reset);
                Reset = false;
                if (! p -> isGroup || ! Global :: CRHMStatus || (Global :: CRHMStatus & 1 && Global :: ModuleBitSet [Global :: CurrentModuleRun]))
                {
                    if (! (p -> Name == "WQ_Soil_BGC"))
                    {
                        p -> run ();
                    }

                }

                if (Last != Global :: CRHMControlSaveCnt)
                {
                    Global :: ModuleBitSet.set (Global :: CurrentModuleRun);
                }

            }
            if (Global :: CRHMControlSaveCnt && ! (Global :: CRHMStatus & 1))
            {
                ControlSaveState (false, StatePar, Global :: ModuleBitSet);
                Global :: CRHMStatus |= 1;
                LogMessage ("Start save Main", DD);
            }

            bool DoOutput = true;
            if ((Global :: CRHMStatus & 1) && (! Global :: CRHMControlSaveCnt || Global :: DTindx >= Global :: DTmax - 1))
            {
                ControlReadState (false, NULL);
                Global :: CRHMStatus &= 126;
                Global :: CRHMControlSaveCnt = 0;
                LogMessage ("End save Main", DD);
                LogDebug (" ");
                if (Global :: Freq == 1)
                {
                    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx);
                    Global :: DTindx -= 1;
                }

                else
                {
                    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx + 1);
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

        }
        int d = iter;
        Global :: BuildFlag = CRHM :: DECL;
    }
    catch (exception & E) {
        LogError (S + " (" + FloatToStrF (Global :: DTnow, ffGeneral, 10, 0) + ")", ERR);
        GoodRun = false;
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2Middle(MMSData * mmsdata, long startdate, long enddate)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: RunClick2End (MMSData * mmsdata)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick2End(MMSData * mmsdata)@@@CRHMmain_old.cpp>");
    float ** mmsData = mmsdata -> mmsData;
    long ** mmsDataL = mmsdata -> mmsDataL;
    bool GoodRun = mmsdata -> GoodRun;
    double Dt = StandardConverterUtility :: DateTimeDt ();
    string Message = string ("End of model run: ") + DttoStr (Dt) + " " + FormatString (Dt, "yy mm dd ") + ". Program " + Version;
    LogMessageX (Message.c_str ());
    delete [] mmsData;
    delete [] mmsDataL;
    ((ClassModule *) Global :: OurModulesList -> Objects [0]) -> InitReadObs ();
    if (GoodRun)
    {
        if (ReportAll)
        {
            AllRprt ();
        }

        else
        {
            LastRprt ();
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick2End(MMSData * mmsdata)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: CheckBlankModule ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::CheckBlankModule()@@@CRHMmain_old.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        string s = thisVar -> name;
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::CheckBlankModule()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: RunClick (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClick(void)@@@CRHMmain_old.cpp>");
    MMSData * mmsdata = CRHMmain :: RunClick2Start ();
    CRHMmain :: RunClick2Middle (mmsdata, Global :: DTmin, Global :: DTmax);
    CRHMmain :: RunClick2End (mmsdata);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClick(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: RunClickOld (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RunClickOld(void)@@@CRHMmain_old.cpp>");
    ClassVar * thisVar;
    float ** mmsData;
    long ** mmsDataL;
    bool GoodRun = true;
    clock_t begintime2 = clock ();
    MapVar :: iterator itVar;
    Global :: ModuleBitSet.reset ();
    Global :: HRU_OBS = Global :: HRU_OBS_DIRECT;
    Global :: OBS_AS_IS = false;
    Global :: WQ_prj = false;
    if (Global :: IndxMin != 0)
    {

        #if defined (_WIN32)
            AfxMessageBox (_T ("First observation day - not an entire day"));
        #endif

        #if defined (__linux__) || defined (__APPLE__)
            string message = "First observation day - not an entire day";
            LogMessageX (message.c_str ());
        #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClickOld(void)@@@CRHMmain_old.cpp>");
        return;
    }

    if (ListBox3 -> Count == 0)
    {

        #if defined (_WIN32)
            AfxMessageBox (_T ("No model output selected"));
        #endif

        #if defined (__linux__) || defined (__APPLE__)
            string message = "No model output selected";
            LogMessageX (message.c_str ());
        #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClickOld(void)@@@CRHMmain_old.cpp>");
        return;
    }

    string Message = "Project file: " + OpenProjectPath;
    LogMessageX (Message.c_str ());
    LogMessageX (" ");
    for (int ii = 0; ii < ObsFilesList -> Count; ii ++) {
        Message = "Observation file: " + ObsFilesList -> Strings [ii];
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
    for (int ii = 0; ii < Global :: OurModulesList -> Count; ++ ii) {
        ClassModule * thisModule = (ClassModule *) Global :: OurModulesList -> Objects [ii];
        S += Global :: OurModulesList -> Strings [ii];
        if (thisModule -> variation != 0)
        {
            string AA ("#0");
            AA [1] += log (thisModule -> variation) / log (2) + 1;
            S += AA;
        }

        if (ii == Global :: OurModulesList -> Count - 1)
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

    Global :: DeclRootList -> Clear ();
    ((ClassModule *) Global :: OurModulesList -> Objects [0]) -> InitReadObs ();
    double DTstartR = Picker1;
    double DTendR = Picker2;
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
    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx + 1);
    int Modii = 0;
    Global :: MapVarsGet.clear ();
    Global :: MapVarsPut.clear ();
    Global :: MapObsGet.clear ();
    try {
        for (Modii = 0; Modii < Global :: OurModulesList -> Count; Modii ++)
            ((ClassModule *) (Global :: OurModulesList -> Objects [Modii])) -> initbase ();
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
    if (ObsFilesList -> Count > 0)
    {
        FileData = (ClassData *) ObsFilesList -> Objects [0];
    }

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

    if (GoodRun)
    {
        if (! OpenStateFlag)
        {
            thisPar = ParFind ("basin INIT_STATE");
            if (thisPar && thisPar -> Strings -> Count && ! thisPar -> Strings -> Strings [0].empty ())
            {
                OpenNameState = thisPar -> Strings -> Strings [0];
                OpenStateFlag = true;
            }

            else
            {
                MapPar :: iterator itPar;
                for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
                    thisPar = (* itPar).second;
                    if (thisPar -> param == "INIT_STATE" && thisPar -> Strings -> Count && ! thisPar -> Strings -> Strings [0].empty ())
                    {
                        OpenNameState = thisPar -> Strings -> Strings [0];
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
        ((ClassModule *) Global :: OurModulesList -> Objects [0]) -> InitReadObs ();
        for (int ii = 0; ii < Modii; ii ++)
            ((ClassModule *) (Global :: OurModulesList -> Objects [ii])) -> finish (false);
        Global :: BuildFlag = CRHM :: DECL;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClickOld(void)@@@CRHMmain_old.cpp>");
        return;
    }

    Global :: BuildFlag = CRHM :: RUN;
    Global :: DTmax = (int) ((DTendR - Global :: DTstart) * Global :: Freq);
    SeriesCnt = ListBox3 -> Count;
    int Cnt = Global :: DTmax - Global :: DTmin;
    cdSeries = new TSeries * [SeriesCnt];
    for (int ii = 0; ii < SeriesCnt; ++ ii)
        cdSeries [ii] = new TSeries (Cnt);
    mmsData = new float * [SeriesCnt];
    mmsDataL = new long * [SeriesCnt];
    for (int ii = 0; ii < ListBox3 -> Count; ii ++) {
        thisVar = (ClassVar *) (ListBox3 -> Objects [ii]);
        cdSeries [ii] -> Tag = thisVar;
        string S = ListBox3 -> Strings [ii];
        cdSeries [ii] -> Title = S;
        long lay, dim;
        S = ExtractHruLay (S, dim, lay);
        if (thisVar -> varType == CRHM :: Float)
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
        if (thisVar -> varType == CRHM :: Int)
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

    }
    bool First = true;
    LogMessageX (" ");
    S = string ("timestep ") + DttoStr (Global :: Interval * 24) + " hr.";
    LogDebug (S.c_str ());
    LogDebugT ("\"start of run\".");
    LogMessageX (" ");
    Global :: CRHMControlSaveCnt = 0;
    Global :: CRHMStatus = 0;
    Global :: LoopCntDown = - 1;
    StatePar = NULL;
    Global :: ModuleBitSet.reset ();
    try {
        int iter = 0;
        for (Global :: DTindx = Global :: DTmin; Global :: DTindx < Global :: DTmax; Global :: DTindx ++) {
            iter ++;
            if (Global :: Freq == 1)
            {
                Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx);
            }

            else
            {
                Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx + 1);
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
                    LogMessage ("Terminate fast loop aheadMain", DD);
                }

                else
                if (Global :: DTnow == Global :: RapidAdvanceTo && Global :: LoopCnt)
                {
                    if (Global :: LoopCntDown == - 1)
                    {
                        Global :: LoopCntDown = Global :: LoopCnt;
                        StatePar = ParFind ("basin StateVars_to_Update");
                        ControlSaveState (true, StatePar, Global :: RunUpBitSet);
                        LogMessage ("Initialise LoopTo Main", DD);
                    }

                }

                else
                if (Global :: DTnow == Global :: LoopTo && Global :: LoopCnt)
                {
                    ControlReadState (true, StatePar);
                    -- Global :: LoopCntDown;
                    LogMessage ("Reached loop Main", DD);
                    if (Global :: LoopCntDown <= 0)
                    {
                        ResetLoopList ();
                        Global :: CRHMStatus &= 125;
                        Global :: CRHMStatus |= 4;
                        Global :: LoopCntDown = - 1;
                        LogMessage ("Terminate LoopTo Main", DD);
                        continue;
                    }

                }

            }

            DoObsStatus (First);
            bool Reset = true;
            for (Global :: CurrentModuleRun = 0; Global :: CurrentModuleRun < Global :: OurModulesList -> Count; Global :: CurrentModuleRun ++) {
                long Last = Global :: CRHMControlSaveCnt;
                ClassModule * p = (ClassModule *) Global :: OurModulesList -> Objects [Global :: CurrentModuleRun];
                p -> ReadObs (Reset);
                Reset = false;
                if (! p -> isGroup || ! Global :: CRHMStatus || (Global :: CRHMStatus & 1 && Global :: ModuleBitSet [Global :: CurrentModuleRun]))
                {
                    p -> run ();
                }

                if (Last != Global :: CRHMControlSaveCnt)
                {
                    Global :: ModuleBitSet.set (Global :: CurrentModuleRun);
                }

            }
            if (Global :: CRHMControlSaveCnt && ! (Global :: CRHMStatus & 1))
            {
                ControlSaveState (false, StatePar, Global :: ModuleBitSet);
                Global :: CRHMStatus |= 1;
                LogMessage ("Start save Main", DD);
            }

            bool DoOutput = true;
            if ((Global :: CRHMStatus & 1) && (! Global :: CRHMControlSaveCnt || Global :: DTindx >= Global :: DTmax - 1))
            {
                ControlReadState (false, NULL);
                Global :: CRHMStatus &= 126;
                Global :: CRHMControlSaveCnt = 0;
                LogMessage ("End save Main", DD);
                LogDebug (" ");
                if (Global :: Freq == 1)
                {
                    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx);
                    Global :: DTindx -= 1;
                }

                else
                {
                    Global :: DTnow = Global :: DTstart + Global :: Interval * (Global :: DTindx + 1);
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

        }
        int d = iter;
        Global :: BuildFlag = CRHM :: DECL;
    }
    catch (exception & E) {
        LogError (S + " (" + FloatToStrF (Global :: DTnow, ffGeneral, 10, 0) + ")", ERR);
        GoodRun = false;
    }
    Dt = StandardConverterUtility :: DateTimeDt ();
    Message = string ("End of model run: ") + DttoStr (Dt) + " " + FormatString (Dt, "yy mm dd ") + ". Program " + Version;
    LogMessageX (Message.c_str ());
    delete [] mmsData;
    delete [] mmsDataL;
    ((ClassModule *) Global :: OurModulesList -> Objects [0]) -> InitReadObs ();
    if (GoodRun)
    {
        if (ReportAll)
        {
            AllRprt ();
        }

        else
        {
            LastRprt ();
        }

    }

    float timediff2 = float (clock () - begintime2) / CLOCKS_PER_SEC;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RunClickOld(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ControlSaveState (bool MainLoop, ClassPar * VarPar, BitSet & Bit)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ControlSaveState(bool MainLoop, ClassPar * VarPar, BitSet & Bit)@@@CRHMmain_old.cpp>");
    TStringList * StateList;
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    StateList = new TStringList;
    string S;
    bool Needed;
    Global :: RunUpBitSet.reset ();
    bool Wild = false;
    if (VarPar && ! VarPar -> Strings -> Strings [0].empty ())
    {
        Wild = VarPar -> Strings -> Strings [0].find ("@") == string :: npos;
    }

    if (MainLoop)
    {
        StateList -> Add ("Starting main run-up loop");
    }

    else
    {
        StateList -> Add ("starting module run-ahead to determine future variables");
    }

    StateList -> Add ("######");
    StateList -> Add ("Time:");
    S = FormatString (Global :: DTnow, "yyyy m d");
    StateList -> Add (S);
    StateList -> Add ("######");
    StateList -> Add ("DTindx:");
    StateList -> Add (DttoStr (Global :: DTindx));
    StateList -> Add ("######");
    StateList -> Add ("CurrentModuleRun:");
    StateList -> Add (DttoStr (Global :: CurrentModuleRun));
    StateList -> Add ("######");
    StateList -> Add ("Dimension:");
    StateList -> Add (Common :: longtoStr (Global :: nhru) + " " + Common :: longtoStr (Global :: nlay));
    StateList -> Add ("######");
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        Needed = false;
        if (thisVar -> varType < CRHM :: Read && thisVar -> StatVar)
        {
            if (! thisVar -> InGroup || Global :: ModuleBitSet [thisVar -> InGroup - 1])
            {
                Needed = true;
            }

            else
            if (MainLoop)
            {
                string namebasic = thisVar -> name;
                if (VarPar -> Strings -> IndexOf (namebasic) > - 1)
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
                        if (VarPar -> Strings -> IndexOf (namebasic) > - 1)
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
            StateList -> Add (S);
            S = "";
            if (thisVar -> lay == 0)
            for (int ii = 0; ii < thisVar -> dim; ii ++) {
                if (thisVar -> values != NULL)
                {
                    S = S + FloatToStrF (thisVar -> values [ii], ffGeneral, 7, 0) + " ";
                }

                else
                if (thisVar -> ivalues != NULL)
                {
                    S = S + FloatToStrF (thisVar -> ivalues [ii], ffGeneral, 7, 0) + " ";
                }

                else
                {
                    S = S + "-0 ";
                }

                if (ii % 10 == 9)
                {
                    StateList -> Add (S);
                    S = "";
                }

            }

            else
            for (int ll = 0; ll < thisVar -> lay; ll ++) {
                for (int ii = 0; ii < thisVar -> dim; ii ++) {
                    if (thisVar -> layvalues != NULL)
                    {
                        S = S + FloatToStrF (thisVar -> layvalues [ll] [ii], ffGeneral, 4, 0) + " ";
                    }

                    else
                    if (thisVar -> ivalues != NULL)
                    {
                        S = S + FloatToStrF (thisVar -> ilayvalues [ll] [ii], ffGeneral, 4, 0) + " ";
                    }

                    else
                    {
                        S = S + "-0 ";
                    }

                    if (ii % 10 == 9)
                    {
                        StateList -> Add (S);
                        S = "";
                    }

                }
                if (! S.empty ())
                {
                    StateList -> Add (S);
                }

                S = "";
            }

            if (! S.empty ())
            {
                StateList -> Add (S);
            }

            StateList -> Add ("######");
        }

    }
    if (MainLoop)
    {
        StateList -> SaveToFile (ProjectDirectory + "\\" + "ControlStateFile.tmp1");
    }

    else
    {
        StateList -> SaveToFile (ProjectDirectory + "\\" + "ControlStateFile.tmp2");
    }

    delete StateList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ControlSaveState(bool MainLoop, ClassPar * VarPar, BitSet & Bit)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ReadStateFile (bool & GoodRun)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain_old.cpp>");
    MapPar :: iterator itVar;
    ClassVar * thisVar;
    char module [24], name [24], Descrip [80], Line [80];
    string S;
    ifstream DataFile (OpenNameState.c_str ());
    if (! DataFile)
    {
        Common :: Message ("cannot open file", "File Error");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain_old.cpp>");
        return;
    }

    DataFile.getline (Descrip, 80);
    DataFile.ignore (80, '#');
    DataFile.getline (Line, 80);
    DataFile.getline (Line, 80);
    int D [3];
    DataFile >> D [0] >> D [1] >> D [2];
    double DT = StandardConverterUtility :: EncodeDateTime (D [0], D [1], D [2], 0, 0);
    DataFile.getline (Descrip, 80);
    DataFile.ignore (80, '#');
    DataFile.getline (Line, 80);
    DataFile.getline (Line, 80);
    long filehru, filelay;
    DataFile >> filehru >> filelay;
    if (filehru != Global :: nhru || filelay != Global :: nlay)
    {
        Common :: Message ("State File and Model #HRU's or #LAY's are not equal", "File Error");
        GoodRun = false;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain_old.cpp>");
        return;
    }

    DataFile.ignore (80, '#');
    DataFile.getline (Line, 80);
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

            DataFile.ignore (80, '#');
            DataFile.getline (Line, 80);
        }

        else
        {
            Common :: Message ((string ("State File variable ") + S.c_str ()).c_str (), "Unknown variable");
            DataFile.ignore (80, '#');
            DataFile.getline (Line, 80);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ReadStateFile(bool & GoodRun)@@@CRHMmain_old.cpp>");
}
ClassVar * VarFind (string name)
{
InstrumentLogger::instance()->log_instrument_log("<VarFind(string name)@@@CRHMmain_old.cpp>");
    MapVar :: iterator itVar;
    if ((itVar = Global :: MapVars.find (name)) == Global :: MapVars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</VarFind(string name)@@@CRHMmain_old.cpp>");
        return NULL;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</VarFind(string name)@@@CRHMmain_old.cpp>");
        return ((* itVar).second);
    }

InstrumentLogger::instance()->log_instrument_log("</VarFind(string name)@@@CRHMmain_old.cpp>");
}
ClassPar * ParFind (string name)
{
InstrumentLogger::instance()->log_instrument_log("<ParFind(string name)@@@CRHMmain_old.cpp>");
    MapPar :: iterator itPar;
    if ((itPar = Global :: MapPars.find (name)) == Global :: MapPars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</ParFind(string name)@@@CRHMmain_old.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ParFind(string name)@@@CRHMmain_old.cpp>");
    return ((* itPar).second);
InstrumentLogger::instance()->log_instrument_log("</ParFind(string name)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: AllRprt (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::AllRprt(void)@@@CRHMmain_old.cpp>");
    TStringList * LogList = new TStringList;
    RprtHeader (LogList, SeriesCnt);
    string Sx, Sy;
    for (int nn = 0; nn < cdSeries [0] -> Count (); ++ nn) {
        switch (Global :: TimeFormat) {
        case CRHM :: MS:
            Sx = FloatToStrF (cdSeries [0] -> XValue (nn), ffGeneral, 10, 0);
            break;
        case CRHM :: MMDDYYYY:
            Sx = StandardConverterUtility :: FormatDateTime ("mm/dd/yyyy hh:mm ", cdSeries [0] -> XValue (nn));
            break;
        case CRHM :: YYYYMMDD:
            Sx = StandardConverterUtility :: FormatDateTime ("yyyy-mm-dd hh:mm ", cdSeries [0] -> XValue (nn));
            break;
        default:
            break;
        }
        for (int vv = 0; vv < SeriesCnt; ++ vv) {
            if (cdSeries [0] -> Count () == cdSeries [vv] -> Count ())
            {
                ClassVar * thisVar = (ClassVar *) cdSeries [vv] -> Tag;
                int prec = 7;
                Sy = FloatToStrF (cdSeries [vv] -> YValue (nn), ffGeneral, prec, 10);
                Sx = Sx + "\t" + Sy;
            }

        }
        LogList -> Add (Sx);
    }
    LogList -> SaveToFile (OpenNameReport);
    LogList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::AllRprt(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: LastRprt (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::LastRprt(void)@@@CRHMmain_old.cpp>");
    TStringList * LogList = new TStringList;
    RprtHeader (LogList, SeriesCnt);
    string Sx, Sy;
    int nn = cdSeries [0] -> Count ();
    Sx = FloatToStrF (cdSeries [0] -> XValue (nn - 1), ffGeneral, 10, 0);
    for (int vv = 0; vv < SeriesCnt; ++ vv) {
        ClassVar * thisVar = (ClassVar *) cdSeries [vv] -> Tag;
        int prec = 6;
        if (thisVar -> varType == CRHM :: Int || thisVar -> varType == CRHM :: ReadI)
        {
            prec = 4;
        }

        Sy = FloatToStrF (cdSeries [vv] -> YValue (nn - 1), ffGeneral, prec, 0);
        Sx = Sx + "\t" + Sy;
    }
    LogList -> Add (Sx);
    LogList -> SaveToFile (OpenNameReport);
    LogList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::LastRprt(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: DoObsStatus (bool & First)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DoObsStatus(bool & First)@@@CRHMmain_old.cpp>");
    if (First)
    {
        for (int ii = 0; ii < ObsFilesList -> Count; ii ++) {
            ClassData * FileData = (ClassData *) ObsFilesList -> Objects [ii];
            FileData -> TimeIndx = 0;
        }
        First = false;
    }

    for (int ii = 0; ii < ObsFilesList -> Count; ii ++) {
        ClassData * FileData = (ClassData *) ObsFilesList -> Objects [ii];
        FileData -> GoodInterval = true;
        if (ii == 0)
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DoObsStatus(bool & First)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ResetLoopList (void)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ResetLoopList(void)@@@CRHMmain_old.cpp>");
    if (LoopList == NULL)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ResetLoopList(void)@@@CRHMmain_old.cpp>");
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

    LoopList -> SaveToFile (ProjectDirectory + "\\" + FileName + ".txt");
    delete LoopList;
    LoopList = NULL;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ResetLoopList(void)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ControlReadState (bool MainLoop, ClassPar * VarPar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain_old.cpp>");
    MapPar :: iterator itVar;
    ClassVar * thisVar;
    string Sy;
    string Sx;
    bool first = true;
    bool Wild = false;
    if (VarPar && ! VarPar -> Strings -> Strings [0].empty ())
    {
        Wild = VarPar -> Strings -> Strings [0].find ("@") == string :: npos;
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

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain_old.cpp>");
        return;
    }

    getline (DataFile, Descrip);
    DataFile.ignore (180, '#');
    getline (DataFile, Line);
    getline (DataFile, Line);
    int D [3];
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
        long exist = Global :: OurModulesList -> IndexOf (module);
        ClassModule * mod;
        if (exist > - 1)
        {
            mod = (ClassModule *) Global :: OurModulesList -> Objects [exist];
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
            if (VarPar && VarPar -> Strings -> IndexOf (namebasic) > - 1)
            {
                if (LoopList == NULL)
                {
                    LoopList = new TStringList;
                    Sx = DttoStr (Global :: DTnow);
                    LoopList -> Add (Sx);
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
                            Sy += FloatToStrF (thisVar -> values [ii], ffGeneral, 4, 0) + " ";
                        }

                        else
                        if (thisVar -> ivalues != NULL)
                        {
                            Sy += FloatToStrF (thisVar -> ivalues [ii], ffFixed, 0, 0) + " ";
                        }

                }

                else
                {
                    for (int ll = 0; ll < thisVar -> lay; ll ++)
                        for (int ii = 0; ii < thisVar -> dim; ii ++)
                            if (thisVar -> layvalues != NULL)
                            {
                                Sy += FloatToStrF (thisVar -> layvalues [ll] [ii], ffGeneral, 4, 0) + " ";
                            }

                            else
                            if (thisVar -> ivalues != NULL)
                            {
                                Sy += FloatToStrF (thisVar -> ilayvalues [ll] [ii], ffGeneral, 0, 0) + " ";
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
        if (TraceVarPar && ! TraceVarPar -> Strings -> Strings [0].empty ())
        {
            Wild2 = TraceVarPar -> Strings -> Strings [0].find ("@") == string :: npos;
        }

        for (int ii = 0; ii < TraceVarPar -> Strings -> Count; ++ ii) {
            string Trimmed = Common :: trim (TraceVarPar -> Strings -> Strings [ii]);
            if (! Trimmed.empty ())
            {
                int jj = ListBox1 -> IndexOf (Trimmed);
                if (jj > - 1)
                {
                    for (int ii = 0; ii < Global :: OurModulesList -> Count; ii ++) {
                        ClassVar * thisVar = VarFind (string (Global :: OurModulesList -> Strings [ii]) + ' ' + TraceVarPar -> Strings -> Strings [0]);
                        if (thisVar)
                        {
                            break;
                        }

                    }
                    thisVar = (ClassVar *) ListBox1 -> Objects [jj];
                    if (thisVar)
                    {
                        Sx += ("\t" + string (Trimmed));
                        Sy = "";
                        if (thisVar -> lay == 0)
                        {
                            for (int ii = 0; ii < thisVar -> dim; ii ++)
                                if (thisVar -> values != NULL)
                                {
                                    Sy += FloatToStrF (thisVar -> values [ii], ffGeneral, 4, 0) + " ";
                                }

                                else
                                if (thisVar -> ivalues != NULL)
                                {
                                    Sy += FloatToStrF (thisVar -> ivalues [ii], ffFixed, 0, 0) + " ";
                                }

                        }

                        else
                        {
                            for (int ll = 0; ll < thisVar -> lay; ll ++)
                                for (int ii = 0; ii < thisVar -> dim; ii ++)
                                    if (thisVar -> layvalues != NULL)
                                    {
                                        Sy += FloatToStrF (thisVar -> layvalues [ll] [ii], ffGeneral, 4, 0) + " ";
                                    }

                                    else
                                    if (thisVar -> ivalues != NULL)
                                    {
                                        Sy += FloatToStrF (thisVar -> ilayvalues [ll] [ii], ffGeneral, 0, 0) + " ";
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
        LoopList -> Add (Sx);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ControlReadState(bool MainLoop, ClassPar * VarPar)@@@CRHMmain_old.cpp>");
}
TStringList * CRHMmain :: getObservations ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getObservations()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getObservations()@@@CRHMmain_old.cpp>");
    return ListBox2;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getObservations()@@@CRHMmain_old.cpp>");
}
TStringList * CRHMmain :: getAllmodules ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getAllmodules()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAllmodules()@@@CRHMmain_old.cpp>");
    return Global :: AllModulesList;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getAllmodules()@@@CRHMmain_old.cpp>");
}
TStringList * CRHMmain :: getVariables ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::getVariables()@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getVariables()@@@CRHMmain_old.cpp>");
    return ListBox1;
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::getVariables()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: RprtHeader (TStringList * LogList, int LocalCnt)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::RprtHeader(TStringList * LogList, int LocalCnt)@@@CRHMmain_old.cpp>");
    string Sx, Sy;
    ClassPar * thisPar;
    thisPar = ParFind ("basin RUN_ID");
    long ID = 0;
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

        OpenNameReport += ".obs";
    }

    else
    if (ID < 0)
    {
        ID = - ID;
        OpenNameReport = OpenNamePrj.substr (0, OpenNamePrj.length () - 4) + "_" + Common :: longtoStr (ID) + ".obs";
    }

    LogList -> Add ("Future File Description");
    for (int vv = 0; vv < LocalCnt; ++ vv) {
        ClassVar * thisVar = (ClassVar *) cdSeries [vv] -> Tag;
        Sx = cdSeries [vv] -> Title;
        Sx += string (" 1 ");
        LogList -> Add (Sx);
    }
    Sx = "##### time";
    for (int vv = 0; vv < LocalCnt; ++ vv) {
        string S = cdSeries [vv] -> Title;
        Sx += "\t" + S;
    }
    LogList -> Add (Sx);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::RprtHeader(TStringList * LogList, int LocalCnt)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: DttoStr (double D)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::DttoStr(double D)@@@CRHMmain_old.cpp>");
    ostringstream temp;
    temp << D;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DttoStr(double D)@@@CRHMmain_old.cpp>");
    return temp.str ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::DttoStr(double D)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: inttoStr (int I)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::inttoStr(int I)@@@CRHMmain_old.cpp>");
    ostringstream temp;
    temp << I;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::inttoStr(int I)@@@CRHMmain_old.cpp>");
    return temp.str ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::inttoStr(int I)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: LogMessageX (const char * S)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::LogMessageX(const char * S)@@@CRHMmain_old.cpp>");
    puts (S);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::LogMessageX(const char * S)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: GetCaptionFromAboutBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain_old.cpp>");

    #if defined (_WIN32)
        CRHMAboutBox aboutbox;

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain_old.cpp>");
        return aboutbox.versionstring;
    #endif

    #if defined (__linux__) || defined (__APPLE__)

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain_old.cpp>");
        return "";
    #endif

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetCaptionFromAboutBox()@@@CRHMmain_old.cpp>");
}
void CRHMmain :: SaveProject (string prj_description, string filepath)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::SaveProject(string prj_description, string filepath)@@@CRHMmain_old.cpp>");
    MapPar :: iterator itPar;
    MapDim :: iterator itDim;
    ClassPar * thisPar;
    ClassVar * lastVar = NULL;
    string Output;
    int Y = 0, M = 0, D = 0, H = 0, Min = 0;
    ProjectList -> Add (prj_description);
    double Dt = StandardConverterUtility :: GetCurrentDateTime ();
    string datetime = StandardConverterUtility :: GetDateTimeInString (Dt);
    string S ("  Creation: " + datetime);
    string caption = GetCaptionFromAboutBox ();
    ProjectList -> Add ("###### " + caption + S);
    bool Prj = false;
    if (filepath.find (".prj") != std :: string :: npos)
    {
        Prj = true;
    }

    if (Prj)
    {
        ProjectList -> Add ("Dimensions:");
        ProjectList -> Add ("######");
        ProjectList -> Add (string ("nhru " + to_string (Global :: maxhru)));
        ProjectList -> Add (string ("nlay " + to_string (Global :: nlay)));
        ProjectList -> Add (string ("nobs " + to_string (Global :: nobs)));
        ProjectList -> Add ("######");
        ProjectList -> Add ("Macros:");
        ProjectList -> Add ("######");
        for (int ii = 0; ii < Global :: MacroModulesList -> Count; ++ ii)
            ProjectList -> Add ("'" + Global :: MacroModulesList -> Strings [ii] + "'");
        ProjectList -> Add ("######");
        if (! Global :: MapAKA.empty ())
        {
            Mapstr2 :: iterator it;
            ProjectList -> Add ("AKAs:");
            ProjectList -> Add ("######");
            for (it = Global :: MapAKA.begin (); it != Global :: MapAKA.end (); ++ it) {
                string Var = (* it).first + ' ' + (* it).second;
                ProjectList -> Add (Var.c_str ());
            }
            ProjectList -> Add ("######");
        }

        ProjectList -> Add ("Observations:");
        ProjectList -> Add ("######");
        for (int ii = 0; ii < ObsFilesList -> Count; ii ++) {
            string S = ObsFilesList -> Strings [ii];
            ProjectList -> Add (S);
        }
        ProjectList -> Add ("######");
        ProjectList -> Add ("Dates:");
        ProjectList -> Add ("######");
        string S;
        double date1 = GetStartDate ();
        S = StandardConverterUtility :: GetDateInString (date1);
        if (ObsFilesList -> Count == 0)
        {
            S = S + " " + FloatToStrF (Global :: Freq, ffGeneral, 0, 0);
        }

        ProjectList -> Add (S);
        double date2 = GetEndDate ();
        S = StandardConverterUtility :: GetDateInString (date2);
        ProjectList -> Add (S);
        ProjectList -> Add ("######");

        #ifdef CRHM_DLL
            if (OpenDLLs -> Count > 0)
            {
                ProjectList -> Add ("DLLs:");
                ProjectList -> Add ("######");
                CompactDlls ();
                for (int ii = 0; ii < OpenDLLs -> Count; ii ++) {
                    String S = OpenDLLs -> Strings [ii];
                    ProjectList -> Add (S);
                }
                ProjectList -> Add ("######");
            }

        #endif

        ProjectList -> Add ("Modules:");
        ProjectList -> Add ("######");
        for (int ii = 0; ii < Global :: OurModulesList -> Count; ii ++) {
            ClassModule * thisModule = (ClassModule *) Global :: OurModulesList -> Objects [ii];
            string S = Global :: OurModulesList -> Strings [ii];
            if (thisModule -> variation > 0)
            {
                string AA ("#0 ");
                AA [1] += log (thisModule -> variation) / log (2) + 1;
                S = S + AA.c_str ();
            }

            else
            {
                S = S + " ";
            }

            S = S + thisModule -> DLLName + " ";
            S = S + thisModule -> Version;
            ProjectList -> Add (S);
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
                        AA [1] += log ((* iterM) -> variation) / log (2) + 1;
                        S = S + AA.c_str ();
                    }

                    else
                    {
                        S = S + " ";
                    }

                    S = S + (* iterM) -> DLLName + " ";
                    S = S + (* iterM) -> Version;
                    ProjectList -> Add (S);
                    ++ iterM;
                }
            }

        }
        ProjectList -> Add ("######");
        ProjectList -> Add ("Parameters:");
        ProjectList -> Add ("###### 'basin' parameters always first");
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
                if (thisPar -> varType != CRHM :: Txt)
                {
                    S += " <" + FloatToStrF (thisPar -> minVal, ffGeneral, 4, 0) + " to " + FloatToStrF (thisPar -> maxVal, ffGeneral, 4, 0) + ">";
                }

                ProjectList -> Add (S);
                for (int jj = 0; jj < thisPar -> lay; jj ++) {
                    S = "";
                    for (int ii = 0; ii < thisPar -> dim; ii ++) {
                        if (thisPar -> varType == CRHM :: Float)
                        {
                            S = S + FloatToStrF (thisPar -> layvalues [jj] [ii], ffGeneral, 4, 0) + " ";
                        }

                        else
                        if (thisPar -> varType == CRHM :: Int)
                        {
                            S = S + FloatToStrF (thisPar -> ilayvalues [jj] [ii], ffFixed, 8, 0) + " ";
                        }

                        else
                        if (thisPar -> varType == CRHM :: Txt)
                        {
                            if (thisPar -> Strings -> Count > ii)
                            {
                                S = S + "'" + thisPar -> Strings -> Strings [ii] + "' ";
                            }

                            else
                            {
                                S = "''";
                            }

                        }

                        if (ii % 16 == 15)
                        {
                            ProjectList -> Add (S);
                            S = "";
                        }

                    }
                    if (S.length () != 0)
                    {
                        ProjectList -> Add (S);
                        S = "";
                    }

                }
                if (S.length () != 0)
                {
                    ProjectList -> Add (S);
                }

            }
        }
        ProjectList -> Add ("######");
        ProjectList -> Add ("Initial_State");
        ProjectList -> Add ("######");
        ProjectList -> Add ("######");
        ProjectList -> Add ("Final_State");
        ProjectList -> Add ("######");
        if (SaveStateFlag)
        {
        }

        ProjectList -> Add ("######");
    }

    if (Global :: LOGVARLOAD)
    {
        ProjectList -> Add ("LOGVARLOAD");
        ProjectList -> Add ("######");
    }

    ProjectList -> Add ("Display_Variable:");
    ProjectList -> Add ("######");
    for (int ii = 0; ii < SeriesCnt; ii ++) {
    }
    lastVar = NULL;
    Output = "";
    int c = ListBox1 -> Count;
    for (int ii = 0; ii < ListBox3 -> Count; ++ ii) {
        long lay, dim;
        ExtractHruLay (ListBox3 -> Strings [ii], dim, lay);
        ClassVar * thisVar = (ClassVar *) ListBox3 -> Objects [ii];
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
                ProjectList -> Add (Output);
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
        ProjectList -> Add (Output);
    }

    ProjectList -> Add ("######");
    ProjectList -> Add ("Display_Observation:");
    ProjectList -> Add ("######");
    lastVar = NULL;
    string kind, lastkind;
    Output = "";
    for (int ii = 0; ii < ListBox4 -> Count; ii ++) {
        string S = ListBox4 -> Strings [ii];
        string FullName;
        long dim = 0, lay = 0;
        kind = "_obs";
        string Name = GetObservationName (ListBox4 -> Strings [ii]);
        ExtractHruLay (ListBox4 -> Strings [ii], dim, lay);
        TSeries * cdSeries = (TSeries *) ListBox4 -> Objects [ii];
        ClassVar * thisVar;
        thisVar = NULL;
        thisVar = (ClassVar *) cdSeries -> Tag;
        thisVar = (ClassVar *) ListBox4 -> Objects [ii];
        if (! thisVar || ! thisVar -> FileData)
        {
            if (! thisVar)
            {
                long Indx = ListBox3 -> IndexOf (FullName);
                if (Indx > - 1)
                {
                    thisVar = (ClassVar *) ListBox3 -> Objects [Indx];
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
            ProjectList -> Add (Output + " " + lastkind);
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
        ProjectList -> Add (Output + " " + kind);
    }

    ProjectList -> Add ("######");
    ProjectList -> Add ("TChart:");
    ProjectList -> Add ("######");
    ProjectList -> Add ("######");
    ProjectList -> SaveToFile (filepath);
    ProjectList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::SaveProject(string prj_description, string filepath)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: GetObservationName (string vname)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObservationName(string vname)@@@CRHMmain_old.cpp>");
    for (int i = 0; i < ListBox2 -> Count; i ++) {
        string str = ListBox2 -> Strings [i];
        int ind = vname.find (str);
        if (ind > - 1)
        {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationName(string vname)@@@CRHMmain_old.cpp>");
            return str;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationName(string vname)@@@CRHMmain_old.cpp>");
    return "";
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationName(string vname)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: ExtractHruLayFunct (string S, long & Hru, long & Lay, string & Funct, string & FullName)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ExtractHruLayFunct(string S, long & Hru, long & Lay, string & Funct, string & FullName)@@@CRHMmain_old.cpp>");
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
        Hru = ListHruNames -> IndexOf (S.substr (jj + 1, jj1 - jj - 1));
        if (Hru == - 1)
        {
            Hru = stoi (S.substr (jj + 1, jj1 - jj - 1));
        }

        else
        if (Hru == 0)
        {
            ++ Hru;
        }

    }

    FullName = S.substr (1, jj2);

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLayFunct(string S, long & Hru, long & Lay, string & Funct, string & FullName)@@@CRHMmain_old.cpp>");
    return S.substr (1, jj - 1);
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ExtractHruLayFunct(string S, long & Hru, long & Lay, string & Funct, string & FullName)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: ClearModules (bool All)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::ClearModules(bool All)@@@CRHMmain_old.cpp>");
    ModVarRemove (Global :: MapVars);
    Global :: SharedMapPars.clear ();
    if (All)
    {
        for (int ii = 0; ii < Global :: OurModulesList -> Count; ii ++)
            ((ClassModule *) (Global :: OurModulesList -> Objects [ii])) -> reset ();
    }

    Global :: OurModulesList -> Clear ();
    if (All)
    {
        AdminMacro.MacroClear ();
        Global :: MacroModulesList -> Clear ();
    }

    ListBox1 -> Clear ();
    ListBox3 -> Clear ();
    if (cdSeries)
    {
        cdSeries = NULL;
        SeriesCnt = 0;
    }

    Global :: BuildFlag = CRHM :: BUILD;
    Global :: MapAKA.clear ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::ClearModules(bool All)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: GetObservationNames (char * obsfilepath)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObservationNames(char * obsfilepath)@@@CRHMmain_old.cpp>");
    FILE * obfile = fopen (obsfilepath, "r");
    char line [128], obsname [128];
    char * token;
    char obsnames [50] [128];
    int obsindex = 0, j = 0;
    fgets (line, sizeof line, obfile);
    while (fgets (line, sizeof line, obfile) != NULL) {
        for (int i = 0; i < strlen (line); i ++) {
            obsname [i] = line [i];
            if (line [i] == ' ')
            {
                obsname [i] = '\0';
                strcpy (obsnames [j], obsname);
                break;
            }

        }
        if (line [0] == '#')
        {
            break;
        }

        for (int i = 0; i < j; i ++) {
            char test [128];
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationNames(char * obsfilepath)@@@CRHMmain_old.cpp>");
}
void CRHMmain :: GetObservationData (char * obsfilepath, char * observationname)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::GetObservationData(char * obsfilepath, char * observationname)@@@CRHMmain_old.cpp>");
    int l = strlen (observationname);
    if (observationname [l - 1] == '\n')
    {
        observationname [l - 1] = '\0';
    }

    FILE * obfile = fopen (obsfilepath, "r");
    char line [128], obsname [128];
    char * token, obsnames [50] [128];
    int obsindex = 0, j = 0;
    fgets (line, sizeof line, obfile);
    while (fgets (line, sizeof line, obfile) != NULL) {
        for (int i = 0; i < strlen (line); i ++) {
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

        if (line [0] == '#')
        {
            break;
        }

        for (int i = 0; i < j; i ++) {
            char test [128];
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
    observationseries = new TSeries (50000);
    observationseries -> Title = observationname;
    int obscount = j;
    char tokens [50] [50];
    int tokencount = 0;
    float obsvalue = 0.0;
    int dateelements = 0, year, month, day, hour, minute, second;
    double ddate;
    while (fgets (line, sizeof line, obfile) != NULL) {
        tokencount = 0;
        token = strtok (line, " \t");
        while (token != NULL) {
            strcpy (tokens [tokencount], token);
            tokencount ++;
            token = strtok (NULL, " \t");
        }
        obsvalue = atof (tokens [tokencount - obscount + obsindex - 1]);
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
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::GetObservationData(char * obsfilepath, char * observationname)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: BuildHru (string S, long Hru, CRHM :: TDim dimen)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::BuildHru(string S, long Hru, CRHM :: TDim dimen)@@@CRHMmain_old.cpp>");
    if (! HruNames)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildHru(string S, long Hru, CRHM :: TDim dimen)@@@CRHMmain_old.cpp>");
        return S + "(" + to_string (Hru) + ")";
    }

    else
    {
        string SS;
        if (dimen == CRHM :: BASIN)
        {
            SS = "(" + ListHruNames -> Strings [0] + ")";
        }

        else
        {
            SS = "(" + ListHruNames -> Strings [Hru] + ")";
        }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildHru(string S, long Hru, CRHM :: TDim dimen)@@@CRHMmain_old.cpp>");
        return S + SS;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildHru(string S, long Hru, CRHM :: TDim dimen)@@@CRHMmain_old.cpp>");
}
string CRHMmain :: BuildLay (string S, long Lay)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmain::BuildLay(string S, long Lay)@@@CRHMmain_old.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildLay(string S, long Lay)@@@CRHMmain_old.cpp>");
    return S.substr (1, S.length () - 1) + "," + to_string (Lay) + ")";
InstrumentLogger::instance()->log_instrument_log("</CRHMmain::BuildLay(string S, long Lay)@@@CRHMmain_old.cpp>");
}