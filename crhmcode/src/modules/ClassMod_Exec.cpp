#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassMod_Exec.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassMod_Exec * ClassMod_Exec :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassMod_Exec::klone(string name) const@@@ClassMod_Exec.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassMod_Exec::klone(string name) const@@@ClassMod_Exec.cpp>");
    return new ClassMod_Exec (name);
InstrumentLogger::instance()->log_instrument_log("</ClassMod_Exec::klone(string name) const@@@ClassMod_Exec.cpp>");
}
void ClassMod_Exec :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMod_Exec::decl(void)@@@ClassMod_Exec.cpp>");
    Description = "'Link variables and parameters to routines in external DLL.'";
    declvar ("statusInit", TDim :: ONE, "status of variables", "()", & statusInit);
    declvar ("statusStep", TDim :: ONE, "status of time step", "()", & statusStep);
    declvar ("Dummy", TDim :: NHRU, "non constant", "()", & Dummy);
    declvar ("Dummy2", TDim :: NHRU, "constant", "()", & Dummy2);
    DLL_name = declparam ("DLL_name", TDim :: ONE, " ", "DLL name, e.g. 'C:/Jose/Borland/Jose1.dll' ", DLL_name);
    trk_Vars = decldiagparam ("trk_Vars", TDim :: TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop.", trk_Vars);
    chg_Pars = decldiagparam ("chg_Pars", TDim :: TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop.", chg_Pars);
    decldiagparam ("Borland_Dll", TDim :: ONE, "1", "0", "1", "Borland_Dll requires an underscore before routine name", "()", & Borland_Dll);
InstrumentLogger::instance()->log_instrument_log("</ClassMod_Exec::decl(void)@@@ClassMod_Exec.cpp>");
}
void ClassMod_Exec :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMod_Exec::init(void)@@@ClassMod_Exec.cpp>");
    Vars_Cnt = 0;
    Pars_Cnt = 0;
    string S;
    nhru = getdim (TDim :: NHRU);
    ClassVar * newVar;
    ClassPar * newPar;
    S_Vars = "";
    S_Pars = "";
    VarArray = NULL;
    ParArray = NULL;
    bool Root = false;
    if (this -> GroupCnt)
    {
        Root = true;
    }

    long GetUnit;
    if (trk_Vars -> size ())
    {
        VarArray = new double * [trk_Vars -> size ()];
        for (size_t ii = 0; ii < trk_Vars -> size (); ii ++) {
            S = Common :: trim (trk_Vars -> at (ii));
            if (S.length () == 0)
            {
                break;
            }

            GetUnit = FindWildVarFloat (S.c_str (), newVar);
            VarArray [ii] = newVar -> values;
            S_Vars += (newVar -> name + " ").c_str ();
            ++ Vars_Cnt;
        }
    }

    if (chg_Pars -> size ())
    {
        ParArray = new double * [chg_Pars -> size ()];
        for (size_t ii = 0; ii < chg_Pars -> size (); ++ ii) {
            S = Common :: trim (chg_Pars -> at (ii));
            if (S.length () == 0)
            {
                break;
            }

            GetUnit = FindWildParFloat (S.c_str (), newPar, false, Root);
            ParArray [ii] = newPar -> values;
            S_Pars += (newPar -> param + " ").c_str ();
            ++ Pars_Cnt;
        }
    }

    string Routine1 = "CRHM_Init";
    string Routine2 = "CRHM_Step";
    if (Borland_Dll [0])
    {
        Routine1 = "_" + Routine1;
        Routine2 = "_" + Routine2;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMod_Exec::init(void)@@@ClassMod_Exec.cpp>");
}
void ClassMod_Exec :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMod_Exec::run(void)@@@ClassMod_Exec.cpp>");
    if (getstep () == 1)
    {
        statusInit [0] = LoadUserInit (this -> Name.c_str (), this -> GroupCnt, nhru, S_Vars.c_str (), Vars_Cnt, VarArray, S_Pars.c_str (), Pars_Cnt, ParArray);
    }

    double Fix = Global :: DTnow;
    statusStep [0] = LoadUserStep (Fix);
InstrumentLogger::instance()->log_instrument_log("</ClassMod_Exec::run(void)@@@ClassMod_Exec.cpp>");
}
void ClassMod_Exec :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMod_Exec::finish(bool good)@@@ClassMod_Exec.cpp>");
    statusStep [0] = LoadUserStep (0.0);
    delete [] VarArray;
    delete [] ParArray;
InstrumentLogger::instance()->log_instrument_log("</ClassMod_Exec::finish(bool good)@@@ClassMod_Exec.cpp>");
}