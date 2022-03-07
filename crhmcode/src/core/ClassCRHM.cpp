#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>
#include "ClassCRHM.h"
#include "Classfilter.h"
#include "../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"
#include "CRHMLogger.h"
#include "InstrumentLogger.h"

using namespace std;
void setdim (string name, long dim)
{
InstrumentLogger::instance()->log_instrument_log("<setdim(string name, long dim)@@@ClassCRHM.cpp>");
    string s = name;
    if (name == "nhru")
    {
        Update_Main_DIM (TDim :: NHRU, dim);
    }

    else
    if (name == "nobs")
    {
        Update_Main_DIM (TDim :: NOBS, dim);
    }

    else
    if (name == "nlay")
    {
        Update_Main_DIM (TDim :: NLAY, dim);
    }

InstrumentLogger::instance()->log_instrument_log("</setdim(string name, long dim)@@@ClassCRHM.cpp>");
}
ClassPar * ClassParFindShared (string name)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParFindShared(string name)@@@ClassCRHM.cpp>");
    MapPar :: iterator itPar;
    if ((itPar = Global :: SharedMapPars.find (name)) == Global :: SharedMapPars.end ())
    {
        CRHMException Except ("Could not find Parameter: " + name, TExcept :: WARNING);
        LogError (Except);

InstrumentLogger::instance()->log_instrument_log("</ClassParFindShared(string name)@@@ClassCRHM.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassParFindShared(string name)@@@ClassCRHM.cpp>");
    return ((* itPar).second);
InstrumentLogger::instance()->log_instrument_log("</ClassParFindShared(string name)@@@ClassCRHM.cpp>");
}
ClassPar * ClassParFind (string name)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParFind(string name)@@@ClassCRHM.cpp>");
    MapPar :: iterator itPar;
    if ((itPar = Global :: MapPars.find (name)) == Global :: MapPars.end ())
    {
        CRHMException Except ("Could not find Parameter: " + name, TExcept :: WARNING);
        LogError (Except);

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string name)@@@ClassCRHM.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string name)@@@ClassCRHM.cpp>");
    return ((* itPar).second);
InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string name)@@@ClassCRHM.cpp>");
}
ClassPar * ClassParFindPar (string name)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParFindPar(string name)@@@ClassCRHM.cpp>");
    MapPar :: iterator itPar;
    ClassPar * thisPar;
    for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); ++ itPar) {
        thisPar = (* itPar).second;
        if (thisPar -> param == name)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassParFindPar(string name)@@@ClassCRHM.cpp>");
            return ((* itPar).second);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassParFindPar(string name)@@@ClassCRHM.cpp>");
    return (NULL);
InstrumentLogger::instance()->log_instrument_log("</ClassParFindPar(string name)@@@ClassCRHM.cpp>");
}
long ClassParFindParBld (ClassPar * thisPar)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParFindParBld(ClassPar * thisPar)@@@ClassCRHM.cpp>");
    Mapstr :: iterator itPar;
    string sparam, smodule;
    long Count = 0;
    for (itPar = Global :: Mapdeclpar.begin (); itPar != Global :: Mapdeclpar.end (); ++ itPar) {
        sparam = (itPar -> second.first).c_str ();
        smodule = (itPar -> first).c_str ();
        if (sparam == thisPar -> param)
        {
            MapPar :: iterator itPar0 = Global :: MapPars.find (smodule + ' ' + thisPar -> param);
            if (itPar0 != Global :: MapPars.end ())
            {
                continue;
            }

            bool smoduleInOurModules = false;
            for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                if (it -> first == smodule.c_str ())
                {
                    smoduleInOurModules = true;
                }

            }
            if (smoduleInOurModules == false)
            {
                continue;
            }

            ++ Count;
            ClassPar * newPar = new ClassPar (* thisPar);
            newPar -> module = smodule;
            PairPar Item = PairPar (newPar -> module + ' ' + newPar -> param, newPar);
            Global :: MapPars.insert (Item);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassParFindParBld(ClassPar * thisPar)@@@ClassCRHM.cpp>");
    return (Count);
InstrumentLogger::instance()->log_instrument_log("</ClassParFindParBld(ClassPar * thisPar)@@@ClassCRHM.cpp>");
}
void ClassParSet (ClassPar * p)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParSet(ClassPar * p)@@@ClassCRHM.cpp>");
    MapPar :: iterator itPar;
    ClassPar * thisPar;
    if ((itPar = Global :: MapPars.find ("Shared " + p -> param)) != Global :: MapPars.end ())
    {
        thisPar = ((* itPar).second);
        if (thisPar -> Same (* p))
        {
            delete p;

InstrumentLogger::instance()->log_instrument_log("</ClassParSet(ClassPar * p)@@@ClassCRHM.cpp>");
            return;
        }

    }

    if ((itPar = Global :: MapPars.find (p -> module + ' ' + p -> param)) != Global :: MapPars.end ())
    {
        thisPar = ((* itPar).second);
        if (! thisPar -> Same (* p) && thisPar -> dim == p -> dim)
        {
            thisPar -> Change (* p);
        }

        delete p;

InstrumentLogger::instance()->log_instrument_log("</ClassParSet(ClassPar * p)@@@ClassCRHM.cpp>");
        return;
    }

    else
    {
        PairPar Item = PairPar (p -> module + ' ' + p -> param, p);
        Global :: MapPars.insert (Item);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassParSet(ClassPar * p)@@@ClassCRHM.cpp>");
}
ClassPar * ClassParFind (string module, string param)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParFind(string module, string param)@@@ClassCRHM.cpp>");
    MapPar :: iterator itPar;
    if ((itPar = Global :: MapPars.find (module + ' ' + param)) != Global :: MapPars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string module, string param)@@@ClassCRHM.cpp>");
        return ((* itPar).second);
    }

    if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string module, string param)@@@ClassCRHM.cpp>");
        return ((* itPar).second);
    }

    else
    {
        long jj = - 1;
        if (Global :: OldModuleName != NULL)
        {
            for (size_t i = 0; i < Global :: OldModuleName -> size (); i ++) {
                if (module.c_str () == Global :: OldModuleName -> at (i))
                {
                    jj = i;
                }

            }
        }

        if (jj > - 1)
        {
            string s = Global :: NewModuleName -> at (jj) + "";
            if ((itPar = Global :: MapPars.find (s + ' ' + param)) != Global :: MapPars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string module, string param)@@@ClassCRHM.cpp>");
                return ((* itPar).second);
            }

        }

        LogError (CRHMException ("Parameter defined in module: " + param + ", " + module + " not found", TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string module, string param)@@@ClassCRHM.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassParFind(string module, string param)@@@ClassCRHM.cpp>");
}
ClassPar * ClassParFindRev (string module, string param)
{
InstrumentLogger::instance()->log_instrument_log("<ClassParFindRev(string module, string param)@@@ClassCRHM.cpp>");
    MapPar :: iterator itPar;
    if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassParFindRev(string module, string param)@@@ClassCRHM.cpp>");
        return ((* itPar).second);
    }

    if ((itPar = Global :: MapPars.find (module + ' ' + param)) != Global :: MapPars.end ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassParFindRev(string module, string param)@@@ClassCRHM.cpp>");
        return ((* itPar).second);
    }

    else
    {
        LogError (CRHMException ("Parameter defined in module: " + param + ", " + module + " not found", TExcept :: TERMINATE));

InstrumentLogger::instance()->log_instrument_log("</ClassParFindRev(string module, string param)@@@ClassCRHM.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassParFindRev(string module, string param)@@@ClassCRHM.cpp>");
}
ClassPar :: ~ClassPar ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::~ClassPar()@@@ClassCRHM.cpp>");
    if (varType == TVar :: Float)
    {
        for (int ii = 0; ii < lay; ++ ii)
            delete [] layvalues [ii];
        delete [] layvalues;
        values = NULL;
    }

    else
    if (varType == TVar :: Int)
    {
        for (int ii = 0; ii < lay; ++ ii)
            delete [] ilayvalues [ii];
        delete [] ilayvalues;
        ivalues = NULL;
    }

    else
    if (varType == TVar :: Txt)
    {
        delete Strings;
    }

    varType = TVar :: none;
InstrumentLogger::instance()->log_instrument_log("</ClassPar::~ClassPar()@@@ClassCRHM.cpp>");
}
ClassVar * ClassVarFind (string name)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVarFind(string name)@@@ClassCRHM.cpp>");
    MapVar :: iterator itVar;
    if ((itVar = Global :: MapVars.find (name)) == Global :: MapVars.end ())
    if ((itVar = Global :: MapVars.find ('#' + name)) == Global :: MapVars.end ())
    {
        CRHMException Except ("Could not find Variable: " + name, TExcept :: WARNING);
        LogError (Except);

InstrumentLogger::instance()->log_instrument_log("</ClassVarFind(string name)@@@ClassCRHM.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassVarFind(string name)@@@ClassCRHM.cpp>");
    return ((* itVar).second);
InstrumentLogger::instance()->log_instrument_log("</ClassVarFind(string name)@@@ClassCRHM.cpp>");
}
void ClassVar :: review_HRU_OBS (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::review_HRU_OBS(void)@@@ClassCRHM.cpp>");
    if (name == "t" || name == "t_max" || name == "t_min" || name == "rh" || name == "ea")
    {
        HRU_OBS_indexed = 0;
    }

    else
    if (name == "p" || name == "ppt")
    {
        HRU_OBS_indexed = 1;
    }

    else
    if (name == "u")
    {
        HRU_OBS_indexed = 2;
    }

    else
    if (name == "Qsi" || name == "SunAct" || name == "Qli")
    {
        HRU_OBS_indexed = 3;
    }

    else
    {
        HRU_OBS_indexed = 4;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::review_HRU_OBS(void)@@@ClassCRHM.cpp>");
}
long julian (string when)
{
InstrumentLogger::instance()->log_instrument_log("<julian(string when)@@@ClassCRHM.cpp>");
    int Y, M, D, H, Min;
    double DtBegin;
    if (when == "start")
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTstart, & Y, & M, & D, & H, & Min);
        DtBegin = StandardConverterUtility :: EncodeDateTime ((Word) Y - 1, (Word) 12, (Word) 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</julian(string when)@@@ClassCRHM.cpp>");
        return INT (Global :: DTstart - DtBegin);
    }

    else
    if (when == "end")
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTend, & Y, & M, & D, & H, & Min);
        DtBegin = StandardConverterUtility :: EncodeDateTime ((Word) Y - 1, (Word) 12, (Word) 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</julian(string when)@@@ClassCRHM.cpp>");
        return INT (Global :: DTend - DtBegin);
    }

    else
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & Y, & M, & D, & H, & Min);
        DtBegin = StandardConverterUtility :: EncodeDateTime ((Word) Y - 1, (Word) 12, (Word) 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</julian(string when)@@@ClassCRHM.cpp>");
        return INT (Global :: DTnow - DtBegin);
    }

InstrumentLogger::instance()->log_instrument_log("</julian(string when)@@@ClassCRHM.cpp>");
}
long julian (double DT)
{
InstrumentLogger::instance()->log_instrument_log("<julian(double DT)@@@ClassCRHM.cpp>");
    int Y, M, D, H, Min;
    double DtBegin;
    StandardConverterUtility :: DecodeDateTime (DT, & Y, & M, & D, & H, & Min);
    DtBegin = StandardConverterUtility :: EncodeDateTime (Y - 1, 12, 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</julian(double DT)@@@ClassCRHM.cpp>");
    return INT (DT - DtBegin);
InstrumentLogger::instance()->log_instrument_log("</julian(double DT)@@@ClassCRHM.cpp>");
}
long MonthDaysCnt (double DT)
{
InstrumentLogger::instance()->log_instrument_log("<MonthDaysCnt(double DT)@@@ClassCRHM.cpp>");
    int Y, M, D, H, Min;
    double DTNext;
    StandardConverterUtility :: DecodeDateTime (DT, & Y, & M, & D, & H, & Min);
    ++ M;
    if (M > 12)
    {
        M = 1;
        ++ Y;
    }

    DTNext = StandardConverterUtility :: EncodeDateTime ((Word) Y, (Word) M, (Word) D, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</MonthDaysCnt(double DT)@@@ClassCRHM.cpp>");
    return INT (DTNext - DT);
InstrumentLogger::instance()->log_instrument_log("</MonthDaysCnt(double DT)@@@ClassCRHM.cpp>");
}
double Julian (string when)
{
InstrumentLogger::instance()->log_instrument_log("<Julian(string when)@@@ClassCRHM.cpp>");
    int Y, M, D, H, Min;
    double DtBegin;
    if (when == "start")
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTstart, & Y, & M, & D, & H, & Min);
        DtBegin = StandardConverterUtility :: EncodeDateTime ((Word) Y - 1, (Word) 12, (Word) 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</Julian(string when)@@@ClassCRHM.cpp>");
        return (double) (Global :: DTstart - DtBegin);
    }

    else
    if (when == "end")
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTend, & Y, & M, & D, & H, & Min);
        DtBegin = StandardConverterUtility :: EncodeDateTime ((Word) Y - 1, (Word) 12, (Word) 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</Julian(string when)@@@ClassCRHM.cpp>");
        return (double) (Global :: DTend - DtBegin);
    }

    else
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & Y, & M, & D, & H, & Min);
        DtBegin = StandardConverterUtility :: EncodeDateTime ((Word) Y - 1, (Word) 12, (Word) 31, 0, 0);

InstrumentLogger::instance()->log_instrument_log("</Julian(string when)@@@ClassCRHM.cpp>");
        return double ((double) Global :: DTnow - DtBegin);
    }

InstrumentLogger::instance()->log_instrument_log("</Julian(string when)@@@ClassCRHM.cpp>");
}
bool last_timestep (void)
{
InstrumentLogger::instance()->log_instrument_log("<last_timestep(void)@@@ClassCRHM.cpp>");
    if (Global :: DTindx == Global :: DTmax - 1)
    {

InstrumentLogger::instance()->log_instrument_log("</last_timestep(void)@@@ClassCRHM.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</last_timestep(void)@@@ClassCRHM.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</last_timestep(void)@@@ClassCRHM.cpp>");
}
void dattim (string type, long * itime)
{
InstrumentLogger::instance()->log_instrument_log("<dattim(string type, long * itime)@@@ClassCRHM.cpp>");
    int Year, Month, Day, H, Min, Sec = 0;
    if (type == "start")
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTstart, & Year, & Month, & Day, & H, & Min);
    }

    else
    if (type == "end")
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTend, & Year, & Month, & Day, & H, & Min);
    }

    else
    {
        StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & Year, & Month, & Day, & H, & Min);
    }

    itime [0] = Year;
    itime [1] = Month;
    itime [2] = Day;
    itime [3] = H;
    itime [4] = Min;
    itime [5] = Sec;
InstrumentLogger::instance()->log_instrument_log("</dattim(string type, long * itime)@@@ClassCRHM.cpp>");
}
void dattim (double DT, long * itime)
{
InstrumentLogger::instance()->log_instrument_log("<dattim(double DT, long * itime)@@@ClassCRHM.cpp>");
    int Year, Month, Day, H, Min, Sec = 0;
    StandardConverterUtility :: DecodeDateTime (DT, & Year, & Month, & Day, & H, & Min);
    itime [0] = Year;
    itime [1] = Month;
    itime [2] = Day;
    itime [3] = H;
    itime [4] = Min;
    itime [5] = Sec;
InstrumentLogger::instance()->log_instrument_log("</dattim(double DT, long * itime)@@@ClassCRHM.cpp>");
}
void ModVarRemove (MapVar & MapVars)
{
InstrumentLogger::instance()->log_instrument_log("<ModVarRemove(MapVar & MapVars)@@@ClassCRHM.cpp>");
    ClassVar * thisVar;
    ClassVar * thisVar2;
    ClassPar * thisPar;
    MapVar :: iterator itVar;
    MapVar :: iterator itVar2, itVar3;
    MapPar :: iterator itPar;
    string S, S2;
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar != NULL)
        {
            S = (* itVar).first;
            if (thisVar -> varType < TVar :: Read)
            {
                for (itVar2 = Global :: MapVars.begin (); itVar2 != Global :: MapVars.end (); itVar2 ++) {
                    thisVar2 = (* itVar2).second;
                    if (thisVar2 != NULL)
                    {
                        S2 = (* itVar2).first;
                        if (thisVar == thisVar2)
                        {
                            (* itVar2).second = NULL;
                        }

                    }

                }
                if (thisVar -> module != "")
                {
                    delete thisVar;
                }

                else
                {
                    S = "Fault";
                }

            }

            else
            {
                if (S != ("obs " + thisVar -> name))
                {
                    (* itVar).second = NULL;
                }

            }

        }

    }
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end ();) {
        thisVar = (* itVar).second;
        if (thisVar == NULL)
        {
            Global :: MapVars.erase (itVar ++);
        }

        else
        {
            ++ itVar;
        }

    }
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        switch (thisVar -> varType) {
        case TVar :: ReadI:
            if (thisVar -> lay > 0)
            {
                for (int ii = 0; ii < thisVar -> lay; ++ ii)
                    delete [] thisVar -> ilayvalues [ii];
                delete [] thisVar -> ilayvalues;
                thisVar -> lay = 0;
                thisVar -> ilayvalues = NULL;
            }

            delete [] thisVar -> ivalues;
            thisVar -> ivalues = NULL;
            thisVar -> varType = TVar :: Read;
            thisVar -> dim = thisVar -> cnt;
            break;
        case TVar :: ReadF:
            if (thisVar -> lay > 0)
            {
                for (int ii = 0; ii < thisVar -> lay; ++ ii)
                    delete [] thisVar -> layvalues [ii];
                delete [] thisVar -> layvalues;
                thisVar -> lay = 0;
                thisVar -> layvalues = NULL;
            }

            delete [] thisVar -> values;
            thisVar -> values = NULL;
            thisVar -> varType = TVar :: Read;
            thisVar -> dim = thisVar -> cnt;
            break;
        case TVar :: Int:
        case TVar :: Float:
            exit (1);
        default:
            break;
        }
    }
    for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
        thisPar = (* itPar).second;
        delete thisPar;
    }
    Global :: MapPars.clear ();
    Global :: SharedMapPars.clear ();
InstrumentLogger::instance()->log_instrument_log("</ModVarRemove(MapVar & MapVars)@@@ClassCRHM.cpp>");
}
ClassVar * declread (string module, string name, long cnt, long offset, ClassData * FileData, string Comment)
{
InstrumentLogger::instance()->log_instrument_log("<declread(string module, string name, long cnt, long offset, ClassData * FileData, string Comment)@@@ClassCRHM.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    string s1 (module);
    string s2 (name);
    string units;
    if (Comment.empty ())
    {
        Comment = "No information in observation file";
    }

    else
    {
        units = extract_units (Comment);
    }

    if (cnt > Global :: nobs)
    {
        Global :: nobs = cnt;
        Global :: maxobs = cnt;
    }

    if ((itVar = Global :: MapVars.find (s1 + " " + s2)) != Global :: MapVars.end ())
    {
        thisVar = (* itVar).second;
        if (thisVar -> varType >= TVar :: Read)
        {
            LogError (CRHMException ("Duplicate Observation variable: " + s1 + " " + s2, TExcept :: ERR));

InstrumentLogger::instance()->log_instrument_log("</declread(string module, string name, long cnt, long offset, ClassData * FileData, string Comment)@@@ClassCRHM.cpp>");
            return NULL;
        }

        thisVar -> FileData = FileData;
        thisVar -> cnt = cnt;
        thisVar -> offset = offset;
        if (thisVar -> varType == TVar :: Int)
        {
            thisVar -> varType = TVar :: ReadI;
        }

        if (thisVar -> varType == TVar :: Float)
        {
            thisVar -> varType = TVar :: ReadF;
        }

InstrumentLogger::instance()->log_instrument_log("</declread(string module, string name, long cnt, long offset, ClassData * FileData, string Comment)@@@ClassCRHM.cpp>");
        return thisVar;
    }

    thisVar = new ClassVar (module, name, cnt, offset, FileData);
    if (thisVar -> name == "p" || thisVar -> name == "ppt")
    {
        thisVar -> dimen = TDim :: NHRU;
    }

    thisVar -> varType = TVar :: Read;
    thisVar -> units = units;
    thisVar -> help = Comment;
    PairVar Item = PairVar (s1 + ' ' + s2, thisVar);
    Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</declread(string module, string name, long cnt, long offset, ClassData * FileData, string Comment)@@@ClassCRHM.cpp>");
    return thisVar;
InstrumentLogger::instance()->log_instrument_log("</declread(string module, string name, long cnt, long offset, ClassData * FileData, string Comment)@@@ClassCRHM.cpp>");
}
void Update_Main_DIM (TDim Dim, long dim)
{
InstrumentLogger::instance()->log_instrument_log("<Update_Main_DIM(TDim Dim, long dim)@@@ClassCRHM.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Update_Main_DIM(TDim Dim, long dim)@@@ClassCRHM.cpp>");
}
void Update_Main_Dirty (void)
{
InstrumentLogger::instance()->log_instrument_log("<Update_Main_Dirty(void)@@@ClassCRHM.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Update_Main_Dirty(void)@@@ClassCRHM.cpp>");
}
long getdim (TDim dimen)
{
InstrumentLogger::instance()->log_instrument_log("<getdim(TDim dimen)@@@ClassCRHM.cpp>");
    MapDim :: iterator itDim;
    string s;
    switch (dimen) {
    case TDim :: BASIN:

InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
        return ((int) TDim :: ONE);
    case TDim :: ONE:
    case TDim :: TWO:
    case TDim :: THREE:
    case TDim :: FOUR:
    case TDim :: FIVE:
    case TDim :: SIX:
    case TDim :: SEVEN:
    case TDim :: EIGHT:
    case TDim :: NINE:
    case TDim :: TEN:
    case TDim :: ELEVEN:
    case TDim :: TWELVE:

InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
        return ((int) dimen);
    case TDim :: NHRU:

InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
        return (Global :: nhru);
    case TDim :: NOBS:

InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
        return (Global :: nobs);
    case TDim :: NLAY:

InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
        return (Global :: nlay);
    default:

InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
        return (- 1);
    }
InstrumentLogger::instance()->log_instrument_log("</getdim(TDim dimen)@@@ClassCRHM.cpp>");
}
long getstep (void)
{
InstrumentLogger::instance()->log_instrument_log("<getstep(void)@@@ClassCRHM.cpp>");

InstrumentLogger::instance()->log_instrument_log("</getstep(void)@@@ClassCRHM.cpp>");
    return Global :: DTindx - Global :: DTmin + 1;
InstrumentLogger::instance()->log_instrument_log("</getstep(void)@@@ClassCRHM.cpp>");
}
bool laststep (void)
{
InstrumentLogger::instance()->log_instrument_log("<laststep(void)@@@ClassCRHM.cpp>");

InstrumentLogger::instance()->log_instrument_log("</laststep(void)@@@ClassCRHM.cpp>");
    return (Global :: DTindx == Global :: DTmax - 1);
InstrumentLogger::instance()->log_instrument_log("</laststep(void)@@@ClassCRHM.cpp>");
}
void setdim (TDim dimen, long dim)
{
InstrumentLogger::instance()->log_instrument_log("<setdim(TDim dimen, long dim)@@@ClassCRHM.cpp>");
    MapDim :: iterator itDim;
    string s;
    switch (dimen) {
    case TDim :: NHRU:
        s = "nhru";
        Update_Main_DIM (TDim :: NHRU, dim);
        break;
    case TDim :: NOBS:
        s = "nobs";
        Update_Main_DIM (TDim :: NOBS, dim);
        break;
    case TDim :: NLAY:
        s = "nlay";
        Update_Main_DIM (TDim :: NLAY, dim);
        break;
    default:

InstrumentLogger::instance()->log_instrument_log("</setdim(TDim dimen, long dim)@@@ClassCRHM.cpp>");
        return;
    }
InstrumentLogger::instance()->log_instrument_log("</setdim(TDim dimen, long dim)@@@ClassCRHM.cpp>");
}
void LogError (CRHMException Except)
{
InstrumentLogger::instance()->log_instrument_log("<LogError(CRHMException Except)@@@ClassCRHM.cpp>");
    CRHMLogger :: instance () -> log_run_error (Except);
    if (Except.Kind == TExcept :: TERMINATE)
    {
        CRHMLogger :: instance () -> log_to_console (Except.Message);
        CRHMLogger :: instance () -> get_run_logger () -> flush ();
        throw (Except);
    }

InstrumentLogger::instance()->log_instrument_log("</LogError(CRHMException Except)@@@ClassCRHM.cpp>");
}
void LogError (string S, TExcept Kind)
{
InstrumentLogger::instance()->log_instrument_log("<LogError(string S, TExcept Kind)@@@ClassCRHM.cpp>");
    CRHMException Except = CRHMException (S, Kind);
    CRHMLogger :: instance () -> log_run_error (Except);
    if (Except.Kind == TExcept :: TERMINATE)
    {
        CRHMLogger :: instance () -> get_run_logger () -> flush ();
        throw (Except);
    }

InstrumentLogger::instance()->log_instrument_log("</LogError(string S, TExcept Kind)@@@ClassCRHM.cpp>");
}
void LogMessage (const char * S, double V, const char * S2, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(const char * S, double V, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V, "ffFixed", 10, 4) + " " + S2;
    LogMessage (SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(const char * S, double V, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (const char * S, double V, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(const char * S, double V, TExtra Opt)@@@ClassCRHM.cpp>");
    string D, SS;
    switch (Opt) {
    case TExtra :: BLANK:
        break;
    case TExtra :: DD:
        D = FormatString (Global :: DTnow, "yy mm dd ");
        break;
    case TExtra :: DT:
        D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
        break;
    case TExtra :: TT:
        D = FormatString (Global :: DTnow, "hh nn ");
    default:
        break;
    }
    if (Opt == TExtra :: BLANK)
    {
        SS = S + FloatToStrF (V, "ffFixed", 10, 4);
    }

    else
    {
        SS = D + S + FloatToStrF (V, "ffFixed", 10, 4);
    }

    CRHMLogger :: instance () -> log_run_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(const char * S, double V, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (const char * S, long V, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(const char * S, long V, TExtra Opt)@@@ClassCRHM.cpp>");
    string D, SS;
    switch (Opt) {
    case TExtra :: BLANK:
        break;
    case TExtra :: DD:
        D = FormatString (Global :: DTnow, "yy mm dd ");
        break;
    case TExtra :: DT:
        D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
        break;
    case TExtra :: TT:
        D = FormatString (Global :: DTnow, "hh nn ");
    default:
        break;
    }
    if (Opt == TExtra :: BLANK)
    {
        SS = S + to_string (V);
    }

    else
    {
        SS = D + S + to_string (V);
    }

    CRHMLogger :: instance () -> log_run_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(const char * S, long V, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (const char * S, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(const char * S, TExtra Opt)@@@ClassCRHM.cpp>");
    string D, SS;
    switch (Opt) {
    case TExtra :: BLANK:
        break;
    case TExtra :: DD:
        D = FormatString (Global :: DTnow, "yy mm dd ");
        break;
    case TExtra :: DT:
        D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
        break;
    case TExtra :: TT:
        D = FormatString (Global :: DTnow, "hh nn ");
    default:
        break;
    }
    if (Opt == TExtra :: BLANK)
    {
        SS = S;
    }

    else
    {
        SS = D + S;
    }

InstrumentLogger::instance()->log_instrument_log("</LogMessage(const char * S, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (long hh, const char * S, double V, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(long hh, const char * S, double V, TExtra Opt)@@@ClassCRHM.cpp>");
    string A = string ("HRU " + to_string (hh + 1) + ": ");
    string D;
    switch (Opt) {
    case TExtra :: BLANK:
        break;
    case TExtra :: DD:
        D = FormatString (Global :: DTnow, "yy mm dd ");
        break;
    case TExtra :: DT:
        D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
        break;
    case TExtra :: TT:
        D = FormatString (Global :: DTnow, "hh nn ");
    default:
        break;
    }
    string SS = A + D + S + FloatToStrF (V, "ffFixed", 10, 4);
    CRHMLogger :: instance () -> log_run_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(long hh, const char * S, double V, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (long hh, const char * S, long V, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(long hh, const char * S, long V, TExtra Opt)@@@ClassCRHM.cpp>");
    string A = string ("HRU " + to_string (hh + 1) + ": ");
    string D;
    switch (Opt) {
    case TExtra :: BLANK:
        break;
    case TExtra :: DD:
        D = FormatString (Global :: DTnow, "yy mm dd ");
        break;
    case TExtra :: DT:
        D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
        break;
    case TExtra :: TT:
        D = FormatString (Global :: DTnow, "hh nn ");
    default:
        break;
    }
    string SS = A + D + S + to_string (V);
    CRHMLogger :: instance () -> log_run_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(long hh, const char * S, long V, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (long hh, const char * S, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(long hh, const char * S, TExtra Opt)@@@ClassCRHM.cpp>");
    string A = string ("HRU " + to_string (hh + 1) + ": ");
    string D;
    switch (Opt) {
    case TExtra :: BLANK:
        break;
    case TExtra :: DD:
        D = FormatString (Global :: DTnow, "yy mm dd ");
        break;
    case TExtra :: DT:
        D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
        break;
    case TExtra :: TT:
        D = FormatString (Global :: DTnow, "hh nn ");
    default:
        break;
    }
    string SS = A + D + S;
    CRHMLogger :: instance () -> log_run_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(long hh, const char * S, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogDebug (char * S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(char * S)@@@ClassCRHM.cpp>");
    string SS = S;
    CRHMLogger :: instance () -> log_run_debug_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogDebug(char * S)@@@ClassCRHM.cpp>");
}
void LogDebug (long h, char * Text, double v)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(long h, char * Text, double v)@@@ClassCRHM.cpp>");
    string S = to_string (h) + to_string (1);
    S += Text + to_string (v);
    CRHMLogger :: instance () -> log_run_debug_message (S);
InstrumentLogger::instance()->log_instrument_log("</LogDebug(long h, char * Text, double v)@@@ClassCRHM.cpp>");
}
void LogDebugD (char * S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebugD(char * S)@@@ClassCRHM.cpp>");
    string D = FormatString (Global :: DTnow, "yy mm dd ");
    string SS = D + S;
    CRHMLogger :: instance () -> log_run_debug_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogDebugD(char * S)@@@ClassCRHM.cpp>");
}
void LogDebugT (string S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebugT(string S)@@@ClassCRHM.cpp>");
    string D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
    string SS = "yy mm dd hh mm - ";
    SS += D + " - " + S;
    CRHMLogger :: instance () -> log_run_debug_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogDebugT(string S)@@@ClassCRHM.cpp>");
}
void Update_Main_Status (string S)
{
InstrumentLogger::instance()->log_instrument_log("<Update_Main_Status(string S)@@@ClassCRHM.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Update_Main_Status(string S)@@@ClassCRHM.cpp>");
}
void LogMessage (long hh, const char * S, double V1, double V2, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(long hh, const char * S, double V1, double V2, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 4) + ' ' + FloatToStrF (V2, "ffFixed", 10, 4);
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(long hh, const char * S, double V1, double V2, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessage (long hh, const char * S, double V1, double V2, double V3, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessage(long hh, const char * S, double V1, double V2, double V3, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 4) + " " + FloatToStrF (V2, "ffFixed", 10, 4) + " " + FloatToStrF (V3, "ffFixed", 10, 4);
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessage(long hh, const char * S, double V1, double V2, double V3, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessageA (long hh, const char * S, double V1, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessageA(long hh, const char * S, double V1, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 2);
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessageA(long hh, const char * S, double V1, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessageA (long hh, const char * S, double V1, const char * S2, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessageA(long hh, const char * S, double V1, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 2) + " " + S2;
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessageA(long hh, const char * S, double V1, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessageA (long hh, const char * S, double V1, const double HRU_area, const double Basin_area, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessageA(long hh, const char * S, double V1, const double HRU_area, const double Basin_area, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 2) + " " + FloatToStrF (V1 * HRU_area, "ffFixed", 10, 2) + " " + FloatToStrF (V1 * HRU_area / Basin_area, "ffFixed", 10, 3);
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessageA(long hh, const char * S, double V1, const double HRU_area, const double Basin_area, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessageA (long hh, const char * S, double V1, const double HRU_area, const double Basin_area, const char * S2, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessageA(long hh, const char * S, double V1, const double HRU_area, const double Basin_area, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 2) + " " + FloatToStrF (V1 * HRU_area, "ffFixed", 10, 2) + " " + FloatToStrF (V1 * HRU_area / Basin_area, "ffFixed", 10, 3) + " " + S2;
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessageA(long hh, const char * S, double V1, const double HRU_area, const double Basin_area, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessageA (long hh, const char * S, double V1, const double Basin_area, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessageA(long hh, const char * S, double V1, const double Basin_area, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 2) + " " + FloatToStrF (V1 / Basin_area, "ffFixed", 10, 3);
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessageA(long hh, const char * S, double V1, const double Basin_area, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogMessageA (long hh, const char * S, double V1, const double Basin_area, const char * S2, TExtra Opt)
{
InstrumentLogger::instance()->log_instrument_log("<LogMessageA(long hh, const char * S, double V1, const double Basin_area, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
    string SS = S + FloatToStrF (V1, "ffFixed", 10, 2) + " " + FloatToStrF (V1 / Basin_area, "ffFixed", 10, 3) + " " + S2;
    LogMessage (hh, SS.c_str (), Opt);
InstrumentLogger::instance()->log_instrument_log("</LogMessageA(long hh, const char * S, double V1, const double Basin_area, const char * S2, TExtra Opt)@@@ClassCRHM.cpp>");
}
long GetSharedUnit (string units)
{
InstrumentLogger::instance()->log_instrument_log("<GetSharedUnit(string units)@@@ClassCRHM.cpp>");
    const string delims ("()/* \t,.-_");
    string :: size_type begIdx, endIdx;
    begIdx = units.find_first_not_of (delims);
    while (begIdx != string :: npos) {
        endIdx = units.find_first_of (delims, begIdx);
        if (endIdx == string :: npos)
        {
            endIdx = units.length ();
        }

        string name (units.substr (begIdx, endIdx - begIdx));
        if (name == "d")
        {

InstrumentLogger::instance()->log_instrument_log("</GetSharedUnit(string units)@@@ClassCRHM.cpp>");
            return Global :: Freq;
        }

        else
        if (name == "int")
        {

InstrumentLogger::instance()->log_instrument_log("</GetSharedUnit(string units)@@@ClassCRHM.cpp>");
            return 1;
        }

        begIdx = units.find_first_not_of (delims, endIdx);
    }

InstrumentLogger::instance()->log_instrument_log("</GetSharedUnit(string units)@@@ClassCRHM.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</GetSharedUnit(string units)@@@ClassCRHM.cpp>");
}
long julian_month (long Year, long julian)
{
InstrumentLogger::instance()->log_instrument_log("<julian_month(long Year, long julian)@@@ClassCRHM.cpp>");
    int Y, Month, Day, H, Min;
    double DT = StandardConverterUtility :: EncodeDateTime ((Word) Year - 1, (Word) 12, (Word) 31, 0, 0);
    DT += (double) julian;
    StandardConverterUtility :: DecodeDateTime (DT, & Y, & Month, & Day, & H, & Min);

InstrumentLogger::instance()->log_instrument_log("</julian_month(long Year, long julian)@@@ClassCRHM.cpp>");
    return Month;
InstrumentLogger::instance()->log_instrument_log("</julian_month(long Year, long julian)@@@ClassCRHM.cpp>");
}
string extract_units (string & Comment)
{
InstrumentLogger::instance()->log_instrument_log("<extract_units(string & Comment)@@@ClassCRHM.cpp>");
    string Lunits;
    string :: size_type Idx, Idx2;
    Idx = Comment.find_first_of ("(");
    if (Idx != string :: npos)
    {
        Idx2 = Comment.find_first_of (")");
        if (Idx != string :: npos)
        {
            Lunits = Comment.substr (Idx, Idx2 - Idx + 1);
            Comment = Comment.substr (Idx2 + 1);
            Idx = Comment.find_first_not_of (" \t");
            if (Idx != string :: npos)
            {
                Comment = Comment.substr (Idx);
            }

            else
            {
                Comment = "";
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</extract_units(string & Comment)@@@ClassCRHM.cpp>");
    return Lunits;
InstrumentLogger::instance()->log_instrument_log("</extract_units(string & Comment)@@@ClassCRHM.cpp>");
}
void LogDebug (const char * S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(const char * S)@@@ClassCRHM.cpp>");
    string SS = S;
    CRHMLogger :: instance () -> log_run_debug_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogDebug(const char * S)@@@ClassCRHM.cpp>");
}
void LogDebug (const string S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(const string S)@@@ClassCRHM.cpp>");
    string SS = S;
    CRHMLogger :: instance () -> log_run_debug_message (SS);
InstrumentLogger::instance()->log_instrument_log("</LogDebug(const string S)@@@ClassCRHM.cpp>");
}