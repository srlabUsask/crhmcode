#if defined (_WIN32)
    #include "stdafx.h"
#endif

#include <stdio.h>
#include "assert.h"
#include "ClassModule.h"
#include "Common.h"
#include "InstrumentLogger.h"

using namespace std; TStringList * ReadListN = new TStringList;
TStringList * FunctListN = new TStringList;
string Fstrings [] = {"Observation", "VP_saturated", "W_to_MJ/Int", "MJ/Int_to_W", "Average", "Minimum", "Maximum", "Daily Sum", "Positive", "Total", "First", "Last", "Peak", "Count", "Count0", "Intvl"};
string AKAstrings [] = {"VARG", "OBSR", "VARD", "OBSD", "PARD", "OBSF"};

double ClassModule :: Now (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::Now(void)@@@ClassModule.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassModule::Now(void)@@@ClassModule.cpp>");
    return Global :: DTnow;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::Now(void)@@@ClassModule.cpp>");
}
string ClassModule :: Var_name (ClassModule * thisModule, string S)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::Var_name(ClassModule * thisModule, string S)@@@ClassModule.cpp>");
    if (thisModule -> variation != 0)
    {
        string AA ("#0");
        AA [2] += (char) (log (thisModule -> variation) / log (2) + 1);
        S += AA;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::Var_name(ClassModule * thisModule, string S)@@@ClassModule.cpp>");
    return S;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::Var_name(ClassModule * thisModule, string S)@@@ClassModule.cpp>");
}
void ClassModule :: initbase (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::initbase(void)@@@ClassModule.cpp>");
    Global :: BuildFlag = TBuild :: INIT;
    MapPar :: iterator itPar;
    if (Var_NDEFN_cnt)
    {
        Var_loop_lay_table = new double ** [Var_NDEFN_cnt];
        for (long jj = 0; jj < Var_NDEFN_cnt; ++ jj) {
            Var_loop_lay_table [jj] = new double * [nlay];
        }
        Var_loop_lay_value = new double * [Var_NDEFN_cnt];
        for (long jj = 0; jj < Var_NDEFN_cnt; ++ jj)
            Var_loop_lay_value [jj] = new double [nhru];
    }

    else
    {
        Var_loop_lay_table = NULL;
        Var_loop_lay_value = NULL;
    }

    if (Par_NDEFN_cnt)
    {
        Par_loop_lay_table = new double ** [Par_NDEFN_cnt];
        for (long jj = 0; jj < Par_NDEFN_cnt; ++ jj) {
            Par_loop_lay_table [jj] = new double * [nlay];
            for (long ll = 0; ll < nlay; ++ ll)
                Par_loop_lay_table [ll] = new double * [nhru];
        }
        Par_loop_lay_value = new double * [Par_NDEFN_cnt];
        for (long jj = 0; jj < Par_NDEFN_cnt; ++ jj) {
            Par_loop_lay_value [jj] = new double [nlay];
            for (long ll = 0; ll < nlay; ++ ll)
                Par_loop_lay_value [ll] = new double [nhru];
        }
    }

    else
    {
        Par_loop_lay_table = NULL;
        Par_loop_lay_value = NULL;
    }

    Var_NDEFN_cnt = 0;
    Par_NDEFN_cnt = 0;
    decl ();
    init ();
InstrumentLogger::instance()->log_instrument_log("</ClassModule::initbase(void)@@@ClassModule.cpp>");
}
int ClassModule :: declgrpvar (string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
        return (- 1);
    }

    Convert convert;
    convert.CheckUnitsString (Name, variable, units);
    AKAhook (TAKA :: VARD, Name, variable, variable);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (variable.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclvar.insert (Item);
            PeerVar = queryvar.c_str ();

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
                return 0;
            }

            if (layvalue == NULL)
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
                return - 1;
            }

            if (! Global :: GroupCntTrk)
            {
                LogError (CRHMException ("No groups defined " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
                return - 1;
            }

            newVar = new ClassVar (Name, variable, TDim :: NREB, help, units, TVar :: Float, PointPlot, nhru);
            newVar -> varType = TVar :: Float;
            newVar -> variation_set = variation_set;
            newVar -> InGroup = GroupCnt;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: INIT:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> values;
                for (int ii = 0; ii < nhru; ++ ii)
                    newVar -> layvalues [ii] = NULL;
                if (! Global :: GroupCntTrk)
                {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
                    return 0;
                }

                long querycnt = 0;
                for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
                    ClassVar * foundVar = (* itVar).second;
                    if (newVar != NULL)
                    {
                        if (foundVar -> FileData)
                        {
                            continue;
                        }

                        string S = foundVar -> name;
                        string :: size_type indx = S.find ('@');
                        if (indx != string :: npos)
                        {
                            string N = S.substr (indx + 1);
                            S = S.erase (indx);
                            if (S == queryvar)
                            {
                                newVar -> layvalues [querycnt] = foundVar -> values;
                                newVar -> values [querycnt] = foundVar -> dim;
                                ++ querycnt;
                            }

                        }

                    }

                }
                if (newVar != NULL)
                {
                    * layvalue = newVar -> layvalues;
                }

                else
                {
                    CRHMException Except ("variable was null found: " + Name + ' ' + variable, TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
                return querycnt;
            }

            else
            {
                CRHMException Except ("variable not found: " + Name + ' ' + variable, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgrpvar(string variable, string queryvar, string help, string units, double ** value, double ** * layvalue, bool PointPlot)@@@ClassModule.cpp>");
}
void ClassModule :: decldiag (string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decldiag(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, TVISIBLE Local)@@@ClassModule.cpp>");
    declvar (variable, dimen, help, units, value, layvalue, dim, PointPlot, false, Local);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decldiag(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: decldiag (string variable, TDim dimen, string help, string units, long ** value, long ** * ilayvalue, const int dim, bool PointPlot, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decldiag(string variable, TDim dimen, string help, string units, long ** value, long ** * ilayvalue, const int dim, bool PointPlot, TVISIBLE Local)@@@ClassModule.cpp>");
    declvar (variable, dimen, help, units, value, ilayvalue, dim, PointPlot, false, Local);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decldiag(string variable, TDim dimen, string help, string units, long ** value, long ** * ilayvalue, const int dim, bool PointPlot, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: declstatdiag (string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, TVISIBLE Local)
{
    declvar (variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);
    if (Global :: BuildFlag == TBuild :: BUILD)
    {
        string s = string (Name.c_str ()) + " " + variable.c_str ();
        VandP VP;
        VP.PutV (variation_set);
        VP.PutP ((int) Local);
        PairstrV Item2 = PairstrV (s, VP.both);
        PairstrI Item = PairstrI (Name.c_str (), Item2);
        Global :: Mapdeclstat.insert (Item);
    }

}
;

void ClassModule :: declstatdiag (string variable, TDim dimen, string help, string units, long ** value, long ** * ilayvalue, const int dim, bool PointPlot, TVISIBLE Local)
{
    declvar (variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);
    if (Global :: BuildFlag == TBuild :: BUILD)
    {
        string s = string (Name.c_str ()) + " " + variable.c_str ();
        VandP VP;
        VP.PutV (variation_set);
        VP.PutP ((int) Local);
        PairstrV Item2 = PairstrV (s, VP.both);
        PairstrI Item = PairstrI (Name.c_str (), Item2);
        Global :: Mapdeclstat.insert (Item);
    }

}
;

void ClassModule :: declstatvar (string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, TVISIBLE Local)
{
    declvar (variable, dimen, help, units, value, layvalue, dim, PointPlot, true, Local);
    if (Global :: BuildFlag == TBuild :: BUILD)
    {
        string s = string (Name.c_str ()) + " " + variable.c_str ();
        VandP VP;
        VP.PutV (variation_set);
        VP.PutP ((int) Local);
        PairstrV Item2 = PairstrV (s, VP.both);
        PairstrI Item = PairstrI (Name.c_str (), Item2);
        Global :: Mapdeclstat.insert (Item);
    }

}
;

void ClassModule :: declstatvar (string variable, TDim dimen, string help, string units, long ** value, long ** * ilayvalue, const int dim, bool PointPlot, TVISIBLE Local)
{
    declvar (variable, dimen, help, units, value, ilayvalue, dim, PointPlot, true, Local);
    if (Global :: BuildFlag == TBuild :: BUILD)
    {
        string s = string (Name.c_str ()) + " " + variable.c_str ();
        VandP VP;
        VP.PutV (variation_set);
        VP.PutP ((int) Local);
        PairstrV Item2 = PairstrV (s, VP.both);
        PairstrI Item = PairstrI (Name.c_str (), Item2);
        Global :: Mapdeclstat.insert (Item);
    }

}
;

void ClassModule :: declvar (string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    string Orgvariable = variable;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, variable, units);
    AKAhook (TAKA :: VARD, Name, variable, variable);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) Local);
            PairstrV Item2 = PairstrV (variable.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclvar.insert (Item);
            Global :: DeclRootList -> Add (string (ID.c_str ()) + " " + Orgvariable.c_str ());

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            if (dimen == TDim :: NLAY && layvalue == NULL)
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            if (dimen == TDim :: NDEFN)
            {
                ++ Var_NDEFN_cnt;
            }

            newVar = new ClassVar (Name, variable, dimen, help, units, TVar :: Float, PointPlot, nhru, dim);
            newVar -> varType = TVar :: Float;
            newVar -> StatVar = StatVar;
            newVar -> InGroup = GroupCnt;
            newVar -> visibility = Local;
            newVar -> variation_set = variation_set;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if (newVar -> layvalues != NULL)
                {
                    if (dimen == TDim :: NFREQ && newVar -> lay != Global :: Freq)
                    {
                        newVar -> nfreq = true;
                        newVar -> lay = Global :: Freq;
                        newVar -> ReleaseM (true);
                        newVar -> layvalues = new double * [newVar -> lay];
                        for (int ii = 0; ii < newVar -> lay; ii ++)
                            newVar -> layvalues [ii] = new double [newVar -> dim];
                    }

                    if ((dimen == TDim :: NLAY || dimen == TDim :: NDEFN) && newVar -> lay != dim)
                    {
                        long JJ = newVar -> lay;
                    }

                }

                if (layvalue)
                {
                    * layvalue = newVar -> layvalues;
                }

                * value = newVar -> values;
                if (dimen == TDim :: NDEF)
                {
                    Var_loop_lay_table [Var_NDEFN_cnt] = newVar -> layvalues;
                    Var_loop_lay_value [Var_NDEFN_cnt ++] = newVar -> values;
                }

                Global :: DeclRootList -> Add (string (ID.c_str ()) + " " + Orgvariable.c_str ());

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            else
            {
                CRHMException Except ("variable not found: " + Name + ' ' + variable, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: declvar (string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    string Orgvariable = variable;
    if (Variation_Skip ())
    {
        * ivalue = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: VARD, Name, variable, variable);
    Convert convert;
    convert.CheckUnitsString (Name, variable, units);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) Local);
            PairstrV Item2 = PairstrV (variable.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclvar.insert (Item);
            Global :: DeclRootList -> Add (string (ID.c_str ()) + " " + Orgvariable.c_str ());

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            if (dimen == TDim :: NLAY && ilayvalue == NULL)
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            newVar = new ClassVar (Name, variable, dimen, help, units, TVar :: Int, PointPlot, nhru, dim);
            newVar -> varType = TVar :: Int;
            newVar -> StatVar = StatVar;
            newVar -> InGroup = GroupCnt;
            newVar -> visibility = Local;
            newVar -> variation_set = variation_set;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if ((dimen == TDim :: NLAY || dimen == TDim :: NFREQ) && ilayvalue != NULL)
                {
                    if (newVar -> nfreq && newVar -> lay != Global :: Freq)
                    {
                        newVar -> ReleaseM (true);
                        newVar -> lay = Global :: Freq;
                        newVar -> nfreq = true;
                        newVar -> ilayvalues = new long * [newVar -> lay];
                        for (int ii = 0; ii < newVar -> lay; ii ++)
                            newVar -> ilayvalues [ii] = new long [newVar -> dim];
                    }

                }

                if (ilayvalue)
                {
                    * ilayvalue = newVar -> ilayvalues;
                }

                * ivalue = newVar -> ivalues;
                Global :: DeclRootList -> Add (string (ID.c_str ()) + " " + Orgvariable.c_str ());

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            else
            {
                CRHMException Except ("Variable not found: " + Name + ' ' + variable, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declvar(string variable, TDim dimen, string help, string units, long ** ivalue, long ** * ilayvalue, const int dim, bool PointPlot, bool StatVar, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: decllocal (string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, variable, units);
    AKAhook (TAKA :: VARD, Name, variable, variable);
    switch (Global :: BuildFlag) {
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find ("#" + Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
                return;
            }

            if ((dimen == TDim :: NLAY || dimen == TDim :: NFREQ) && layvalue == NULL)
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
                return;
            }

            newVar = new ClassVar (Name, variable, dimen, help, units, TVar :: Float, false, nhru, dim);
            newVar -> varType = TVar :: Float;
            newVar -> InGroup = GroupCnt;
            newVar -> visibility = TVISIBLE :: PRIVATE;
            newVar -> variation_set = variation_set;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar ("#" + Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            string S = "#" + Name + " " + variable;
            if ((itVar = Global :: MapVars.find (S)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if ((dimen == TDim :: NLAY || dimen == TDim :: NFREQ) && layvalue != NULL)
                {
                    if (newVar -> nfreq && newVar -> lay != Global :: Freq)
                    {
                        newVar -> ReleaseM (true);
                        newVar -> lay = Global :: Freq;
                        newVar -> nfreq = true;
                        newVar -> layvalues = new double * [newVar -> lay];
                        for (int ii = 0; ii < newVar -> lay; ii ++)
                            newVar -> layvalues [ii] = new double [newVar -> dim];
                    }

                    * layvalue = newVar -> layvalues;
                }

                * value = newVar -> values;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
                return;
            }

            else
            {
                CRHMException Except ("variable not found: " + S, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, double ** value, double ** * layvalue, const int dim)@@@ClassModule.cpp>");
}
void ClassModule :: decllocal (string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, variable, units);
    AKAhook (TAKA :: VARD, Name, variable, variable);
    switch (Global :: BuildFlag) {
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find ("#" + Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
                return;
            }

            if (dimen == TDim :: NLAY && layvalue == NULL)
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
                return;
            }

            newVar = new ClassVar (Name, variable, dimen, help, units, TVar :: Int, false, nhru, dim);
            newVar -> varType = TVar :: Int;
            newVar -> InGroup = GroupCnt;
            newVar -> visibility = TVISIBLE :: PRIVATE;
            newVar -> variation_set = variation_set;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar ("#" + Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            string S = "#" + Name + " " + variable;
            if ((itVar = Global :: MapVars.find (S)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if ((dimen == TDim :: NLAY || dimen == TDim :: NFREQ) && layvalue != NULL)
                {
                    if (newVar -> nfreq && newVar -> lay != Global :: Freq)
                    {
                        newVar -> ReleaseM (true);
                        newVar -> lay = Global :: Freq;
                        newVar -> nfreq = true;
                        newVar -> ilayvalues = new long * [newVar -> lay];
                        for (int ii = 0; ii < newVar -> lay; ii ++)
                            newVar -> ilayvalues [ii] = new long [newVar -> dim];
                    }

                    * layvalue = newVar -> ilayvalues;
                }

                * value = newVar -> ivalues;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
                return;
            }

            else
            {
                CRHMException Except ("variable not found: " + S, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocal(string variable, TDim dimen, string help, string units, long ** value, long ** * layvalue, const int dim)@@@ClassModule.cpp>");
}
TStringList * ClassModule :: decldiagparam (string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decldiagparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
    TStringList * fix = declparam (param, dimen, Texts, help, stringsList, Local);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decldiagparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
    return fix;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decldiagparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
}
TStringList * ClassModule :: decllocalparam (string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decllocalparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
    TStringList * fix = declparam (param, dimen, Texts, help, stringsList, Local);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocalparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
    return fix;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocalparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
}
TStringList * ClassModule :: declparam (string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar;
    if (Variation_Skip ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
        return (TStringList *) NULL;
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) Local);
            PairstrV Item2 = PairstrV (param.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
            return (TStringList *) NULL;
        }
    case TBuild :: DECL:
        {
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru || dimen == TDim :: BASIN)
                {
                    newPar = (* itPar).second;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
                    return newPar -> Strings;
                }

                else
                {
                    (* itPar).second -> ExpandShrink (this -> nhru);
                    newPar = (* itPar).second;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
                    return newPar -> Strings;
                }

            }

            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
                return newPar -> Strings;
            }

            newPar = new ClassPar (string (Name.c_str ()), string (param), dimen, Texts, help, TVar :: Txt, nhru);
            newPar -> basemodule = this -> NameRoot;
            newPar -> variation_set = variation_set;
            newPar -> visibility = Local;
            PairPar Item = PairPar (Name + " " + param, newPar);
            Global :: MapPars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
            return newPar -> Strings;
        }
    case TBuild :: INIT:
        {
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                stringsList = newPar -> Strings;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
                return stringsList;
            }

            else
            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                stringsList = newPar -> Strings;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
                return stringsList;
            }

            else
            {
                CRHMException Except ("Parameter not found: " + Name + param, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
    return (TStringList *) NULL;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string Texts, string help, TStringList * stringsList, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: decldiagparam (string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decldiagparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
    declparam (param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decldiagparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: decllocalparam (string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decllocalparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
    declparam (param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocalparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: declparam (string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, param, units);
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) Local);
            PairstrV Item2 = PairstrV (param.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: DECL:
        {
            if (dim <= 0)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            if (dimen == TDim :: NDEFN)
            {
                ++ Par_NDEFN_cnt;
            }

            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru || dimen == TDim :: BASIN)
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share == 2)
                    {
                        newPar -> basemodule = this -> NameRoot;
                        newPar -> variation_set = variation_set;
                        newPar -> visibility = Local;
                        newPar -> Inhibit_share = 1;
                        newPar -> valstr = valstr;
                        newPar -> minVal = atof (minstr.c_str ());
                        newPar -> maxVal = atof (maxstr.c_str ());
                        newPar -> help = help;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                    return;
                }

                else
                {
                    (* itPar).second -> ExpandShrink (this -> nhru);
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share == 2)
                    {
                        newPar -> Inhibit_share = 1;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                    return;
                }

            }

            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru || dimen == TDim :: BASIN)
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share == 2)
                    {
                        newPar -> Inhibit_share = 1;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                    return;
                }

            }

            if ((dimen == TDim :: NLAY && layvalue == NULL) || (dimen == TDim :: NDEF && layvalue == NULL) || (dimen == TDim :: NDEFN && layvalue == NULL))
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + param, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            double minval = atof (minstr.c_str ());
            double maxval = atof (maxstr.c_str ());
            newPar = new ClassPar (string (Name.c_str ()), string (param), dimen, valstr, minval, maxval, help, units, TVar :: Float, dim, nhru);
            newPar -> basemodule = this -> NameRoot;
            newPar -> variation_set = variation_set;
            newPar -> visibility = Local;
            Myparser ob;
            ob.eval_exp (newPar);
            PairPar Item = PairPar (Name + " " + param, newPar);
            Global :: MapPars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                * value = newPar -> values;
            }

            else
            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                * value = newPar -> values;
            }

            else
            if ((newPar = ClassParFindPar (param)))
            {
                * value = newPar -> values;
            }

            else
            {
                CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

            if ((dimen == TDim :: NLAY && layvalue != NULL) || (dimen == TDim :: NDEF && layvalue != NULL) || (dimen == TDim :: NDEFN && layvalue != NULL))
            {
                * layvalue = (const double **) newPar -> layvalues;
            }

            if (dimen == TDim :: NDEF)
            {
                Par_loop_lay_table [Par_NDEFN_cnt] = newPar -> layvalues;
                Par_loop_lay_value [Par_NDEFN_cnt ++] = newPar -> values;
            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const double ** value, const double ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: decldiagparam (string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** value, const long ** * layvalue, const int dim, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decldiagparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** value, const long ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
    declparam (param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decldiagparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** value, const long ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: decllocalparam (string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** value, const long ** * layvalue, const int dim, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::decllocalparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** value, const long ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
    declparam (param, dimen, valstr, minstr, maxstr, help, units, value, layvalue, dim, Local);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::decllocalparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** value, const long ** * layvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
}
void ClassModule :: declparam (string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar;
    if (Variation_Skip ())
    {
        * ivalue = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, param, units);
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) Local);
            PairstrV Item2 = PairstrV (param.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: DECL:
        {
            if (dim <= 0)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            * ivalue = & Dummy;
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru || dimen == TDim :: BASIN)
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share == 2)
                    {
                        newPar -> basemodule = this -> NameRoot;
                        newPar -> variation_set = variation_set;
                        newPar -> visibility = Local;
                        newPar -> Inhibit_share = 1;
                        newPar -> valstr = valstr;
                        newPar -> minVal = atof (minstr.c_str ());
                        newPar -> maxVal = atof (maxstr.c_str ());
                        newPar -> help = help;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                    return;
                }

                else
                {
                    (* itPar).second -> ExpandShrink (this -> nhru);
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share == 2)
                    {
                        assert (0);
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                    return;
                }

            }

            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru || dimen == TDim :: BASIN)
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share == 2)
                    {
                        assert (0);
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                    return;
                }

            }

            if ((dimen == TDim :: NLAY && ilayvalue == NULL) || (dimen == TDim :: NDEF && ilayvalue == NULL) || (dimen == TDim :: NDEFN && ilayvalue == NULL))
            {
                LogError (CRHMException ("Layer Array not defined for " + Name + " " + param, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            double minval = atof (minstr.c_str ());
            double maxval = atof (maxstr.c_str ());
            newPar = new ClassPar (string (Name.c_str ()), string (param), dimen, valstr, minval, maxval, help, units, TVar :: Int, dim, nhru);
            newPar -> basemodule = this -> NameRoot;
            newPar -> variation_set = variation_set;
            newPar -> visibility = Local;
            Myparser ob;
            ob.eval_exp (newPar);
            PairPar Item = PairPar (Name + " " + param, newPar);
            Global :: MapPars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                * ivalue = newPar -> ivalues;
                if ((dimen == TDim :: NLAY && ilayvalue != NULL) || (dimen == TDim :: NDEF && ilayvalue != NULL) || (dimen == TDim :: NDEFN && ilayvalue != NULL))
                {
                    * ilayvalue = (const long **) newPar -> ilayvalues;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            else
            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                * ivalue = newPar -> ivalues;
                if ((dimen == TDim :: NLAY && ilayvalue != NULL) || (dimen == TDim :: NDEF && ilayvalue != NULL) || (dimen == TDim :: NDEFN && ilayvalue != NULL))
                {
                    * ilayvalue = (const long **) newPar -> ilayvalues;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            else
            if ((newPar = ClassParFindPar (param)))
            {
                * ivalue = newPar -> ivalues;
                if ((dimen == TDim :: NLAY && ilayvalue != NULL) || (dimen == TDim :: NDEF && ilayvalue != NULL) || (dimen == TDim :: NDEFN && ilayvalue != NULL))
                {
                    * ilayvalue = (const long **) newPar -> ilayvalues;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
                return;
            }

            else
            {
                CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declparam(string param, TDim dimen, string valstr, string minstr, string maxstr, string help, string units, const long ** ivalue, const long ** * ilayvalue, const int dim, TVISIBLE Local)@@@ClassModule.cpp>");
}
long ClassModule :: FindWildVarFloat (string name, ClassVar * & newVar, bool OnceFlag)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::FindWildVarFloat(string name, ClassVar * & newVar, bool OnceFlag)@@@ClassModule.cpp>");
    string spacename = " " + name;
    ;
    string Var;
    MapVar :: iterator itVar;
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        Var = (* itVar).first;
        if (Var [0] == '#')
        {
            continue;
        }

        string :: size_type indx = Var.rfind (spacename);
        if (indx == string :: npos)
        {
            continue;
        }

        newVar = (* itVar).second;
        if (newVar -> cnt > 0)
        {
            continue;
        }

        if (spacename.substr (1) != newVar -> name)
        {
            continue;
        }

        Global :: thisVar = (TObject *) newVar;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildVarFloat(string name, ClassVar * & newVar, bool OnceFlag)@@@ClassModule.cpp>");
        return newVar -> GetUnit ();
    }
    if (OnceFlag == false)
    {
        OnceFlag = true;
        string :: size_type indx = name.find ('@');
        if (indx != string :: npos)
        {
            spacename = name.substr (0, indx);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildVarFloat(string name, ClassVar * & newVar, bool OnceFlag)@@@ClassModule.cpp>");
            return FindWildVarFloat (spacename, newVar, true);
        }

    }

    Global :: thisVar = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildVarFloat(string name, ClassVar * & newVar, bool OnceFlag)@@@ClassModule.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildVarFloat(string name, ClassVar * & newVar, bool OnceFlag)@@@ClassModule.cpp>");
}
long ClassModule :: FindWildParFloat (string name, ClassPar * & newPar, bool Trunc = false, bool Root = true)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::FindWildParFloat(string name, ClassPar * & newPar, bool Trunc = false, bool Root = true)@@@ClassModule.cpp>");
    string spacename;
    if (! Trunc)
    {
        spacename = " " + name;
    }

    else
    {
        string :: size_type indx2 = name.find ('@');
        if (indx2 == string :: npos)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildParFloat(string name, ClassPar * & newPar, bool Trunc = false, bool Root = true)@@@ClassModule.cpp>");
            return - 1;
        }

        else
        {
            spacename = " " + name.substr (0, indx2);
        }

    }

    MapPar :: iterator itPar;
    for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end (); itPar ++) {
        string Var = (* itPar).first;
        if (Var [0] == '#')
        {
            continue;
        }

        string :: size_type indx = Var.rfind (spacename);
        newPar = (* itPar).second;
        if (indx == string :: npos)
        {
            continue;
        }

        string :: size_type indx2 = newPar -> param.find ('@');
        if (! Root || indx2 == string :: npos)
        {
            if (spacename.substr (1) != newPar -> param)
            {
                continue;
            }

        }

        else
        if (spacename.substr (1) != newPar -> param.substr (0, indx2))
        {
            continue;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildParFloat(string name, ClassPar * & newPar, bool Trunc = false, bool Root = true)@@@ClassModule.cpp>");
        return newPar -> GetUnit ();
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildParFloat(string name, ClassPar * & newPar, bool Trunc = false, bool Root = true)@@@ClassModule.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindWildParFloat(string name, ClassPar * & newPar, bool Trunc = false, bool Root = true)@@@ClassModule.cpp>");
}
long ClassModule :: declgetvar (string source, string name, string units, const double ** value, const double ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: VARG, Name, name, name, source, ID);
    MapPar :: iterator itPar;
    long GetUnit;
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            string s = string (source.c_str ()) + " " + name.c_str ();
            PairstrV Item2 = PairstrV (s, variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapgetvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: DECL:
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: INIT:
        {
            string :: size_type indx2 = name.find ('@');
            if ((itVar = Global :: MapVars.find (source + " " + name)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> values;
                if (layvalue != NULL)
                {
                    * layvalue = (const double **) newVar -> layvalues;
                }

                PairVar Item = PairVar (Name + " " + name, newVar);
                Global :: MapVarsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
                return newVar -> GetUnit ();
            }

            else
            if (indx2 != string :: npos && (itVar = Global :: MapVars.find (source + " " + name.substr (0, indx2))) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> values;
                if (layvalue != NULL)
                {
                    * layvalue = (const double **) newVar -> layvalues;
                }

                PairVar Item = PairVar (Name + " " + name, newVar);
                Global :: MapVarsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
                return newVar -> GetUnit ();
            }

            else
            if (source [0] == '*')
            {
                GetUnit = FindWildVarFloat (name, newVar);
                if (GetUnit > - 1)
                {
                    * value = newVar -> values;
                    if (layvalue != NULL)
                    {
                        * layvalue = (const double **) newVar -> layvalues;
                    }

                    PairVar Item = PairVar (Name + " " + name, newVar);
                    Global :: MapVarsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
                    return GetUnit;
                }

            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: declgetvar (string source, string name, string units, const long ** value, const long ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: VARG, Name, name, name, source, ID);
    MapPar :: iterator itPar;
    long GetUnit;
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            string s = string (source.c_str ()) + " " + name.c_str ();
            PairstrV Item2 = PairstrV (s, variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapgetvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: DECL:
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: INIT:
        {
            if (name == "Not_Used")
            {
                name = "Not_Used_int";
            }

            string :: size_type indx2 = name.find ('@');
            if ((itVar = Global :: MapVars.find (source + " " + name)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> ivalues;
                if (layvalue != NULL)
                {
                    * layvalue = (const long **) newVar -> ilayvalues;
                }

                PairVar Item = PairVar (Name + " " + name, newVar);
                Global :: MapVarsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
                return newVar -> GetUnit ();
            }

            else
            if (indx2 != string :: npos && (itVar = Global :: MapVars.find (source + " " + name.substr (0, indx2))) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> ivalues;
                if (layvalue != NULL)
                {
                    * layvalue = (const long **) newVar -> ilayvalues;
                }

                PairVar Item = PairVar (Name + " " + name, newVar);
                Global :: MapVarsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
                return newVar -> GetUnit ();
            }

            else
            if (source [0] == '*')
            {
                GetUnit = FindWildVarFloat (name, newVar);
                if (GetUnit > - 1)
                {
                    * value = newVar -> ivalues;
                    if (layvalue != NULL)
                    {
                        * layvalue = (const long **) newVar -> ilayvalues;
                    }

                    PairVar Item = PairVar (Name + " " + name, newVar);
                    Global :: MapVarsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
                    return GetUnit;
                }

            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetvar(string source, string name, string units, const long ** value, const long ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: declobs (string name, TDim dimen, string help, string units, double ** value)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    ClassVar * thisVar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, name, units);
    AKAhook (TAKA :: OBSD, Name, name, name);
    int cnt = getdim (dimen);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) TVISIBLE :: USUAL);
            PairstrV Item2 = PairstrV ((name + "#").c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclvar.insert (Item);
            Global :: Mapdeclobs.insert (Item);
            Global :: DeclRootList -> Add (string (ID.c_str ()) + " " + (name + "#").c_str ());

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + name + "#")) != Global :: MapVars.end ())
            {
                thisVar = (* itVar).second;
                if (thisVar -> dim < cnt)
                {
                    thisVar -> ReleaseM ();
                    thisVar -> dim = cnt;
                    if (thisVar -> lay > 0)
                    {
                        thisVar -> layvalues = new double * [thisVar -> lay];
                        for (int ii = 0; ii < thisVar -> lay; ii ++)
                            thisVar -> layvalues [ii] = new double [cnt];
                    }

                    thisVar -> values = new double [cnt];
                }

                thisVar -> dimen = dimen;
                thisVar -> DLLName = DLLName.c_str ();
                thisVar -> root = ID.c_str ();

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
                return (- 1);
            }

            newVar = new ClassVar (Name, name + "#", cnt, 0, NULL);
            newVar -> varType = TVar :: Float;
            newVar -> help = help;
            newVar -> units = units;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            newVar -> values = new double [cnt];
            newVar -> variation_set = variation_set;
            PairVar Item = PairVar (Name + " " + name + "#", newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: INIT:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + name + "#")) != Global :: MapVars.end ())
            {
                Global :: DeclRootList -> Add (string (ID.c_str ()) + " " + (name + "#").c_str ());
                newVar = (* itVar).second;
                if (newVar -> FileData)
                {
                    * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
                    return (- (newVar -> cnt - 1));
                }

                else
                {
                    * value = newVar -> values;
                    newVar -> cnt = cnt;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
                    return (newVar -> cnt - 1);
                }

            }

            else
            {
                CRHMException Except ("Observation not found: " + Name + " " + name + "#", TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobs(string name, TDim dimen, string help, string units, double ** value)@@@ClassModule.cpp>");
}
long ClassModule :: getdimObs (string variable)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::getdimObs(string variable)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    if ((itVar = Global :: MapVars.find ("obs " + variable)) != Global :: MapVars.end ())
    {
        newVar = (* itVar).second;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdimObs(string variable)@@@ClassModule.cpp>");
        return (newVar -> cnt);
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdimObs(string variable)@@@ClassModule.cpp>");
        return (- 1);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdimObs(string variable)@@@ClassModule.cpp>");
}
long ClassModule :: declreadobs (string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    PairVar Item;
    string declModule = "obs ";
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: OBSR, Name, variable, variable, declModule, ID);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (variable.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapreadvar.insert (Item);
            Global :: Mapdeclvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: DECL:
        {
            if (dimen == TDim :: NFREQ && layvalue == NULL)
            {
                LogError (CRHMException ("NFREQ Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                return (- 1);
            }

            if ((itVar = Global :: MapVars.find (declModule + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if (newVar -> varType == TVar :: Read)
                {
                    Convert convert;
                    convert.CheckUnitsObs (newVar -> units, units, variable);
                    newVar -> values = NULL;
                    newVar -> varType = TVar :: ReadF;
                    newVar -> dimen = dimen;
                    newVar -> help = help;
                    newVar -> units = units;
                    Item = PairVar (Name + " " + variable, newVar);
                    Global :: MapVars.insert (Item);
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                return (0);
            }

            if (optional)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                return (- 1);
            }

            newVar = new ClassVar ("obs", variable, dimen, help, units, TVar :: Float);
            newVar -> varType = TVar :: Float;
            Item = PairVar (declModule + variable, newVar);
            Global :: MapVars.insert (Item);
            Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: INIT:
        {
            newVar = NULL;
            if ((itVar = Global :: MapVars.find (declModule + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if ((newVar -> varType == TVar :: ReadF || newVar -> varType == TVar :: Read) && newVar -> values == NULL)
                {
                    Convert convert;
                    convert.CheckUnitsObs (newVar -> units, units, variable);
                    newVar -> varType = TVar :: ReadF;
                    newVar -> dimMax = Global :: maxhru;
                    newVar -> values = new double [newVar -> dimMax];
                    newVar -> help = help;
                    newVar -> units = units;
                    Item = PairVar (Name + " " + variable, newVar);
                    Global :: MapVars.insert (Item);
                }

            }

            string :: size_type indx = 0;
            if (itVar == Global :: MapVars.end () || (! newVar -> cnt && newVar -> DLLName.empty ()))
            {
                string variable2;
                indx = variable.find ('#');
                if (indx == string :: npos)
                {
                    variable2 = variable + '#';
                }

                else
                {
                    variable2 = variable.erase (indx);
                }

                if (GroupCnt)
                {
                    if ((itVar = Global :: MapVars.find (Name + ' ' + variable2)) != Global :: MapVars.end ())
                    {
                        newVar = (* itVar).second;
                    }

                }

                else
                {
                    if ((itVar = Global :: MapVars.find (declModule + variable2)) != Global :: MapVars.end ())
                    {
                        newVar = (* itVar).second;
                    }

                }

            }

            if (newVar == NULL)
            {
                if (optional)
                {
                    * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                    return (- 1);
                }

                CRHMException Except ("Observation not found " + declModule + ": " + variable, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

            if (! newVar -> cnt && newVar -> DLLName.empty () && indx == string :: npos)
            {
                if (optional)
                {
                    * value = NULL;
                    PairVar Item = PairVar (Name + " " + variable, newVar);
                    Global :: MapObsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                    return (- 1);
                }

                else
                {
                    CRHMException Except ("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str () + "'", TExcept :: TERMINATE);
                    LogError (Except);
                    string msgstring = "Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str () + "'";
                    throw Except;
                }

            }

            if (newVar -> FileData)
            {
                if (dimen == TDim :: NHRU)
                {
                    newVar -> dim = nhru;
                }

                else
                {
                    newVar -> dim = newVar -> cnt;
                }

                addtoreadlist (newVar);
            }

            * value = newVar -> values;
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapObsGet.insert (Item);
            if (HRU_index > 0)
            {
                newVar -> HRU_OBS_indexed = HRU_index - 1;
            }

            if (newVar -> cnt > 0)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                return (newVar -> cnt - 1);
            }

            else
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
                return (newVar -> dim - 1);
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const double ** value, long HRU_index, bool optional, const double ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: declreadobs (string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    PairVar Item;
    string declModule = "obs ";
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: OBSR, Name, variable, variable, declModule, ID);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (variable.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapreadvar.insert (Item);
            Global :: Mapdeclvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: DECL:
        {
            if (dimen == TDim :: NFREQ && layvalue == NULL)
            {
                LogError (CRHMException ("NFREQ Array not defined for " + Name + " " + variable, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
                return (- 1);
            }

            if ((itVar = Global :: MapVars.find (declModule + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if (newVar -> varType == TVar :: Read || newVar -> varType == TVar :: ReadI)
                {
                    if (dimen == TDim :: NFREQ && (newVar -> lay == 0 || nhru > newVar -> dim))
                    {
                        newVar -> ReleaseM (true);
                        newVar -> dim = nhru;
                        newVar -> dimMax = newVar -> dim;
                        newVar -> lay = Global :: Freq;
                        newVar -> nfreq = true;
                        newVar -> ilayvalues = new long * [newVar -> lay];
                        for (int ii = 0; ii < newVar -> lay; ++ ii)
                            newVar -> ilayvalues [ii] = new long [newVar -> dimMax];
                    }

                    if (newVar -> varType == TVar :: Read || (newVar -> varType == TVar :: ReadF && nhru > newVar -> dimMax))
                    {
                        if (newVar -> ivalues != NULL)
                        {
                            delete [] newVar -> ivalues;
                        }

                        else
                        {
                            Convert convert;
                            convert.CheckUnitsObs (newVar -> units, units, variable);
                        }

                        newVar -> dimMax = max < long > (nhru, newVar -> cnt);
                        newVar -> ivalues = new long [newVar -> dimMax];
                        newVar -> varType = TVar :: ReadI;
                        newVar -> help = help;
                        newVar -> units = units;
                        Item = PairVar (Name + " " + variable, newVar);
                        Global :: MapVars.insert (Item);
                    }

                    else
                    {
                        Item = PairVar (Name + " " + variable, newVar);
                        Global :: MapVars.insert (Item);
                    }

                }

                else
                if (newVar -> dimen != dimen && dimen == TDim :: NFREQ)
                {
                    newVar -> ReleaseM (true);
                    newVar -> lay = Global :: Freq;
                    newVar -> nfreq = true;
                    newVar -> ilayvalues = new long * [newVar -> lay];
                    for (int ii = 0; ii < newVar -> lay; ii ++)
                        newVar -> ilayvalues [ii] = new long [newVar -> dim];
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
                return (- 1);
            }

            newVar = new ClassVar (declModule, variable, dimen, help, units, TVar :: Int);
            newVar -> varType = TVar :: Int;
            Item = PairVar (declModule + variable, newVar);
            Global :: MapVars.insert (Item);
            Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: INIT:
        {
            newVar = NULL;
            if ((itVar = Global :: MapVars.find (declModule + variable)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if (itVar == Global :: MapVars.end () || (! newVar -> cnt && newVar -> DLLName.empty ()))
                {
                    string variable2;
                    string :: size_type indx = variable.find ('#');
                    if (indx == string :: npos)
                    {
                        variable2 = variable + '#';
                    }

                    else
                    {
                        variable2 = variable.erase (indx);
                    }

                    if (GroupCnt)
                    {
                        if ((itVar = Global :: MapVars.find (Name + ' ' + variable2)) != Global :: MapVars.end ())
                        {
                            newVar = (* itVar).second;
                        }

                    }

                    else
                    {
                        if ((itVar = Global :: MapVars.find (declModule + variable2)) != Global :: MapVars.end ())
                        {
                            newVar = (* itVar).second;
                        }

                    }

                }

            }

            if (newVar == NULL)
            {
                CRHMException Except ("Observation not found " + declModule + ": " + variable, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

            if (! newVar -> cnt && newVar -> DLLName.empty ())
            {
                if (optional)
                {
                    * value = NULL;
                    PairVar Item = PairVar (Name + " " + variable, newVar);
                    Global :: MapObsGet.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
                    return (- 1);
                }

                else
                {
                    CRHMException Except ("Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str () + "'", TExcept :: TERMINATE);
                    LogError (Except);
                    string msgstring = "Observation: '" + variable + "', not in Data file. Requested by '" + Name.c_str () + "'";
                    throw Except;
                }

            }

            newVar -> No_ReadVar = 0;
            if (layvalue != NULL)
            {
                if (newVar -> nfreq && newVar -> lay != Global :: Freq)
                {
                    newVar -> ReleaseM (true);
                    newVar -> lay = Global :: Freq;
                    newVar -> nfreq = true;
                    newVar -> ilayvalues = new long * [newVar -> lay];
                    for (int ii = 0; ii < newVar -> lay; ii ++)
                        newVar -> ilayvalues [ii] = new long [newVar -> dim];
                }

                * layvalue = (const long **) newVar -> ilayvalues;
                newVar -> UserFunct = & ClassVar :: Intvl;
                newVar -> FunKind = TFun :: INTVL;
                newVar -> FunctVar = newVar;
                addtofunctlist (newVar);
            }

            if (newVar -> FileData)
            {
                newVar -> dim = nhru;
                addtoreadlist (newVar);
            }

            * value = newVar -> ivalues;
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapObsGet.insert (Item);
            if (HRU_index > 0)
            {
                newVar -> HRU_OBS_indexed = HRU_index - 1;
            }

            if (newVar -> cnt > 0)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
                return (newVar -> cnt - 1);
            }

            else
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
                return (newVar -> dim - 1);
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declreadobs(string variable, TDim dimen, string help, string units, const long ** value, long HRU_index, bool optional, const long ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: declobsfunc (string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * obsVar, * newVar;
    PairVar Item;
    string declModule = "obs ";
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: OBSF, Name, obs, obs, declModule, ID);
    AKAhook (TAKA :: VARD, Name, variable, variable);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            pair < Mapstr :: iterator, Mapstr :: iterator > range = Global :: Mapreadvar.equal_range (Name.c_str ());
            for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
                if (itMap -> second.first == obs.c_str ())
                {
                    break;
                }

            }
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) TVISIBLE :: DIAGNOSTIC);
            PairstrV Item2 = PairstrV (obs.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapreadvar.insert (Item);
            Global :: Mapdeclvar.insert (Item);
            Item2 = PairstrV (variable.c_str (), VP.both);
            Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (declModule + obs)) == Global :: MapVars.end ())
            {
                LogError (CRHMException ("function obs variable not declared: " + Name + " " + obs, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
                return (- 1);
            }

            obsVar = (* itVar).second;
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
                return (- 1);
            }

            string help = obsVar -> help + " <" + "> ";
            newVar = new ClassVar (Name, variable, nhru, help, obsVar -> units, TVar :: Float);
            newVar -> dimMax = nhru;
            newVar -> varType = TVar :: Float;
            newVar -> visibility = TVISIBLE :: DIAGNOSTIC;
            newVar -> variation_set = variation_set;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
            return (0);
        }
    case TBuild :: INIT:
        {
            itVar = Global :: MapVars.find (Name + " " + variable);
            try {
                if ((itVar = Global :: MapVars.find (declModule + obs)) != Global :: MapVars.end ())
                {
                    newVar = (* itVar).second;
                    obsVar = (* itVar).second;
                    if (! newVar)
                    {
                        newVar = new ClassVar (Name, variable, nhru, obsVar -> help + " <" + Fstrings [(int) typeFun] + "> ", obsVar -> units, TVar :: Float);
                        newVar -> dimMax = nhru;
                        newVar -> varType = TVar :: Float;
                        newVar -> visibility = TVISIBLE :: DIAGNOSTIC;
                        newVar -> variation_set = variation_set;
                        newVar -> DLLName = DLLName.c_str ();
                        newVar -> root = ID.c_str ();
                        PairVar Item = PairVar (Name + " " + variable, newVar);
                        Global :: MapVars.insert (Item);
                    }

                    if (obsVar -> FileData == NULL)
                    {
                        if (optional)
                        {
                            * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
                            return (- 1);
                        }

                        else
                        {
                            CRHMException Except ("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str () + "'. Requested by '" + Name.c_str () + "'", TExcept :: TERMINATE);
                            LogError (Except);
                            throw Except;
                        }

                    }

                    if (obsVar -> FileData -> Times != NULL)
                    {
                        CRHMException Except ("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str () + "'", TExcept :: TERMINATE);
                        LogError (Except);
                        throw Except;
                    }

                    if (typeFun == TFun :: INTVL)
                    {
                        newVar -> ReleaseM (false);
                        newVar -> dim = max < long > (nhru, newVar -> dim);
                        newVar -> dimMax = max < long > (newVar -> dim, newVar -> dimMax);
                        newVar -> lay = Global :: Freq;
                        newVar -> layvalues = new double * [newVar -> lay];
                        * layvalue = newVar -> layvalues;
                        for (int ii = 0; ii < newVar -> lay; ++ ii)
                            newVar -> layvalues [ii] = new double [newVar -> dimMax];
                        newVar -> values = newVar -> layvalues [0];
                        newVar -> FileData = obsVar -> FileData;
                    }

                    else
                    if (nhru > newVar -> dim)
                    {
                        delete [] newVar -> values;
                        newVar -> dimMax = nhru;
                        newVar -> values = new double [newVar -> dimMax];
                        newVar -> dim = newVar -> dimMax;
                    }

                    if (GroupCnt)
                    {
                        newVar -> CustomFunct = NULL;
                    }

                    switch (typeFun) {
                    case TFun :: FOBS:
                        newVar -> FunctVar = obsVar;
                        newVar -> FunKind = TFun :: FOBS;
                        newVar -> FileData = obsVar -> FileData;
                        if (GroupCnt)
                        {
                            newVar -> No_ReadVar = 1;
                        }

                        break;
                    case TFun :: AVG:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Avg;
                        newVar -> FunKind = TFun :: AVG;
                        break;
                    case TFun :: MIN:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Min;
                        newVar -> FunKind = TFun :: MIN;
                        break;
                    case TFun :: MAX:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Max;
                        newVar -> FunKind = TFun :: MAX;
                        break;
                    case TFun :: DTOT:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Dtot;
                        newVar -> FunKind = TFun :: DTOT;
                        break;
                    case TFun :: TOT:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Tot;
                        newVar -> FunKind = TFun :: TOT;
                        break;
                    case TFun :: FIRST:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: First;
                        newVar -> FunKind = TFun :: FIRST;
                        break;
                    case TFun :: LAST:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Last;
                        newVar -> FunKind = TFun :: LAST;
                        break;
                    case TFun :: POS:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Pos;
                        newVar -> FunKind = TFun :: POS;
                        break;
                    case TFun :: INTVL:
                        newVar -> FunctVar = obsVar;
                        newVar -> UserFunct = & ClassVar :: Intvl;
                        newVar -> FunKind = TFun :: INTVL;
                        newVar -> offset = newVar -> FunctVar -> offset;
                        * layvalue = newVar -> layvalues;
                        break;
                    default:
                        break;
                    }
                    * value = newVar -> values;
                    newVar -> HRU_OBS_indexed = obsVar -> HRU_OBS_indexed;
                    if (newVar -> FunKind == TFun :: FOBS)
                    {
                        addtoreadlist (newVar);
                    }

                    else
                    if ((Global :: RH_EA_obs == - 1 && obs == "rh") || (Global :: RH_EA_obs == - 1 && obs == "ea") || Global :: OBS_AS_IS || ! (obs == "ea" || obs == "rh"))
                    {
                        addtofunctlist (newVar);
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
                    return (obsVar -> cnt - 1);
                }

                else
                {
                    if (! optional)
                    {
                        CRHMException Except ("Observation not found obs: " + obs, TExcept :: TERMINATE);
                        LogError (Except);
                        throw Except;
                    }

                    else
                    {
                        * value = NULL;
                    }

                }

            }
            catch (...) {
            }
        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, double ** value, TFun typeFun, double ** * layvalue, bool optional)@@@ClassModule.cpp>");
}
long ClassModule :: declobsfunc (string obs, string variable, long ** value, TFun typeFun, bool optional)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * obsVar, * newVar;
    PairVar Item;
    string declModule = "obs ";
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: OBSF, Name, obs, obs, declModule, ID);
    AKAhook (TAKA :: VARD, Name, variable, variable);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            pair < Mapstr :: iterator, Mapstr :: iterator > range = Global :: Mapreadvar.equal_range (Name.c_str ());
            for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
                if (itMap -> second.first == obs.c_str ())
                {
                    break;
                }

            }
            VandP VP;
            VP.PutV (variation_set);
            VP.PutP ((int) TVISIBLE :: DIAGNOSTIC);
            PairstrV Item2 = PairstrV (obs.c_str (), VP.both);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapreadvar.insert (Item);
            Global :: Mapdeclvar.insert (Item);
            Item2 = PairstrV (variable.c_str (), VP.both);
            Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (declModule + obs)) == Global :: MapVars.end ())
            {
                LogError (CRHMException ("function obs variable not declared: " + Name + " " + obs, TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
                return (- 1);
            }

            obsVar = (* itVar).second;
            if ((itVar = Global :: MapVars.find (Name + " " + variable)) != Global :: MapVars.end ())
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
                return (- 1);
            }

            if (! obsVar -> ivalues)
            {
                obsVar -> ivalues = new long [obsVar -> dim];
                obsVar -> varType = TVar :: ReadI;
            }

            newVar = new ClassVar (Name, variable, obsVar -> dim, obsVar -> help + " <" + Fstrings [(int) typeFun] + "> ", obsVar -> units, TVar :: Float);
            newVar -> varType = TVar :: Float;
            newVar -> visibility = TVISIBLE :: DIAGNOSTIC;
            newVar -> variation_set = variation_set;
            newVar -> DLLName = DLLName.c_str ();
            newVar -> root = ID.c_str ();
            PairVar Item = PairVar (Name + " " + variable, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
            return (- 1);
        }
    case TBuild :: INIT:
        {
            itVar = Global :: MapVars.find (Name + " " + variable);
            newVar = (* itVar).second;
            if ((itVar = Global :: MapVars.find (declModule + obs)) != Global :: MapVars.end ())
            {
                obsVar = (* itVar).second;
                if (obsVar -> FileData == NULL)
                {
                    if (optional)
                    {
                        LogError (CRHMException ("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str () + "'. Requested by '" + Name.c_str () + "' (optional).", TExcept :: WARNING));
                        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
                        return (- 1);
                    }

                    else
                    {
                        CRHMException Except ("Function observation: '" + variable + "', cannot be generated from the declared observation, '" + obs.c_str () + "'. Requested by '" + Name.c_str () + "'", TExcept :: TERMINATE);
                        LogError (Except);
                        throw Except;
                    }

                }

                if (obsVar -> FileData -> Times != NULL)
                {
                    CRHMException Except ("Function observation: '" + variable + "', uses a 'sparse' Data file. Requested by '" + Name.c_str () + "'", TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }

                if (obsVar -> dim != newVar -> dim)
                {
                    delete [] newVar -> ivalues;
                    newVar -> ivalues = new long [obsVar -> dim];
                    newVar -> dim = obsVar -> dim;
                }

                switch (typeFun) {
                case TFun :: AVG:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Avg;
                    newVar -> FunKind = TFun :: AVG;
                    break;
                case TFun :: MIN:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Min;
                    newVar -> FunKind = TFun :: MIN;
                    break;
                case TFun :: MAX:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Max;
                    newVar -> FunKind = TFun :: MAX;
                    break;
                case TFun :: DTOT:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Dtot;
                    newVar -> FunKind = TFun :: DTOT;
                    break;
                case TFun :: TOT:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Tot;
                    newVar -> FunKind = TFun :: TOT;
                    break;
                case TFun :: FIRST:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: First;
                    newVar -> FunKind = TFun :: FIRST;
                    break;
                case TFun :: LAST:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Last;
                    newVar -> FunKind = TFun :: LAST;
                    break;
                case TFun :: POS:
                    newVar -> FunctVar = obsVar;
                    newVar -> UserFunct = & ClassVar :: Pos;
                    newVar -> FunKind = TFun :: POS;
                    break;
                default:
                    break;
                }
                * value = newVar -> ivalues;
                newVar -> No_ReadVar = 0;
                newVar -> HRU_OBS_indexed = obsVar -> HRU_OBS_indexed;
                addtofunctlist (newVar);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
                return (obsVar -> cnt - 1);
            }

            else
            {
                CRHMException Except ("Variable not found obs: " + obs, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declobsfunc(string obs, string variable, long ** value, TFun typeFun, bool optional)@@@ClassModule.cpp>");
}
long ClassModule :: declputvar (string source, string name, string units, double ** value, double ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    long GetUnit;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: VARG, Name, name, name, source, ID);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            string s = string (source.c_str ()) + " " + name.c_str ();
            PairstrV Item2 = PairstrV (s, variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapputvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: DECL:
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: INIT:
        {
            if ((itVar = Global :: MapVars.find (source + " " + name)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> values;
                if (layvalue != NULL)
                {
                    (* layvalue) = newVar -> layvalues;
                }

                PairVar Item = PairVar (Name + " " + name, newVar);
                Global :: MapVarsPut.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
                return newVar -> GetUnit ();
            }

            else
            if (source [0] == '*')
            {
                GetUnit = FindWildVarFloat (name, newVar);
                if (GetUnit > - 1)
                {
                    * value = newVar -> values;
                    if (layvalue != NULL)
                    {
                        (* layvalue) = newVar -> layvalues;
                    }

                    PairVar Item = PairVar (Name + " " + name, newVar);
                    Global :: MapVarsPut.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
                    return GetUnit;
                }

                CRHMException Except ("Wild variable not found: " + source + ' ' + name, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

            else
            {
                CRHMException Except ("Variable not found: " + source + ' ' + name, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: declputvar (string source, string name, string units, long ** value, long ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    long GetUnit;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
        return (- 1);
    }

    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: VARG, Name, name, name, source, ID);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            string s = string (source.c_str ()) + " " + name.c_str ();
            PairstrV Item2 = PairstrV (s, variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapputvar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: DECL:
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
            return 0;
        }
    case TBuild :: INIT:
        {
            if (name == "Not_Used")
            {
                name = "Not_Used_int";
            }

            if ((itVar = Global :: MapVars.find (source + " " + name)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                * value = newVar -> ivalues;
                if (layvalue != NULL)
                {
                    (* layvalue) = newVar -> ilayvalues;
                }

                PairVar Item = PairVar (Name + " " + name, newVar);
                Global :: MapVarsPut.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
                return newVar -> GetUnit ();
            }

            else
            if (source [0] == '*')
            {
                GetUnit = FindWildVarFloat (name, newVar);
                if (GetUnit > - 1)
                {
                    * value = newVar -> ivalues;
                    if (layvalue != NULL)
                    {
                        (* layvalue) = newVar -> ilayvalues;
                    }

                    PairVar Item = PairVar (Name + " " + name, newVar);
                    Global :: MapVarsPut.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
                    return GetUnit;
                }

                CRHMException Except ("Wild variable not found: " + source + ' ' + name, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

            else
            {
                CRHMException Except ("Variable not found: " + source + ' ' + name, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputvar(string source, string name, string units, long ** value, long ** * layvalue)@@@ClassModule.cpp>");
}
void ClassModule :: AKAhook (TAKA type, string module, string OrgName, string & NewName)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName)@@@ClassModule.cpp>");
    Mapstr2 :: iterator it;
    string ID = AKAstrings [(int) type] + ' ' + module + ' ' + OrgName;
    bool Added = false;
    bool Explicit = false;
    if ((it = Global :: MapAKA.find (ID)) != Global :: MapAKA.end ())
    {
        NewName = (* it).second;
        NewName = NewName.substr (0, NewName.find (' '));
        Explicit = true;
    }

    else
    {
        if (type == TAKA :: OBSD)
        {
            string :: size_type idx = ID.size ();
            if (ID [idx - 1] == '#')
            {
                ID.erase (idx, 1);
            }

            else
            {
                ID.insert (idx, "#");
                Added = true;
            }

            if ((it = Global :: MapAKA.find (ID)) != Global :: MapAKA.end ())
            {
                NewName = (* it).second;
                NewName = NewName.substr (0, NewName.find (' '));
                if (Added)
                {
                    NewName = NewName.substr (0, NewName.size () - 1);
                }

                Explicit = true;
            }

            else
            {
                Added = false;
            }

        }

        else
        if (GroupCnt && type == TAKA :: VARD)
        {
            string A;
            Common :: GroupEnding (A, GroupCnt);
            NewName.append (A);
            ID = AKAstrings [(int) type] + ' ' + module + ' ' + NewName;
            if ((it = Global :: MapAKA.find (ID)) != Global :: MapAKA.end ())
            {
                NewName = (* it).second;
                NewName = NewName.substr (0, NewName.find (' '));
                Explicit = true;
            }

        }

        else
        if (StructCnt && type == TAKA :: VARD)
        {
            string A ("@`");
            A [1] += (char) StructCnt;
            NewName.append (A);
        }

    }

    if (Global :: ReportList && Explicit)
    {
        string ID = AKAstrings [(int) type] + ' ' + module + ' ' + OrgName;
        if (Added)
        {
            NewName.insert (NewName.size (), "#");
        }

        if (Explicit)
        {
            NewName.insert (NewName.size (), " **** explicit");
        }

        Global :: ReportList -> Add ((ID + " ---> " + NewName).c_str ());
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName)@@@ClassModule.cpp>");
}
void ClassModule :: AKAhook (TAKA type, string module, string OrgName, string & NewName, string & source, string base)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName, string & source, string base)@@@ClassModule.cpp>");
    Mapstr2 :: iterator it;
    OUTCOME Outcome = OUTCOME :: None;
    TAKA typeL = type;
    if (type == TAKA :: OBSF)
    {
        type = TAKA :: OBSR;
    }

    string Try;
    string ID = AKAstrings [(int) type] + ' ' + module + ' ' + OrgName;
    if ((it = Global :: MapAKA.find (ID)) != Global :: MapAKA.end ())
    {
        Try = (* it).second;
        Try = Try.substr (0, Try.find (' '));
        if (Global :: DeclRootList -> IndexOf (string (base.c_str ()) + " " + Try.c_str ()) > - 1)
        {
            if (typeL == TAKA :: OBSF)
            {
                Outcome = OUTCOME :: IgnoreObsFunct;
            }

            else
            {
                Outcome = OUTCOME :: IgnoreObs;
            }

        }

        else
        if (GroupCnt && type == TAKA :: VARG)
        {
            string A;
            Common :: GroupEnding (A, GroupCnt);
            NewName.append (A);
            ID = AKAstrings [(int) type] + ' ' + module + ' ' + NewName;
            if ((it = Global :: MapAKA.find (ID)) != Global :: MapAKA.end ())
            {
                Try = (* it).second;
                Try = Try.substr (0, Try.find (' '));
                NewName = (* it).second;
                NewName = NewName.substr (0, NewName.find (' '));
                Outcome = OUTCOME :: Implicit;
            }

        }

        else
        if (typeL == TAKA :: OBSF && Try [Try.size () - 1] == '#')
        {
            Outcome = OUTCOME :: IgnoreObsFunct;
        }

        else
        if (type == TAKA :: OBSR)
        {
            if (Try [Try.size () - 1] == '#')
            {
                if (Global :: DeclRootList -> IndexOf (string (base.c_str ()) + " " + Try.c_str ()) > - 1)
                {
                    Outcome = OUTCOME :: IgnoreObs;
                }

            }

            NewName = (* it).second;
            NewName = NewName.substr (0, NewName.find (' '));
            source = (* it).second;
            source = source.substr (source.find (' ') + 1) + ' ';
            Outcome = OUTCOME :: Explicit;
        }

        else
        if (type == TAKA :: VARG)
        {
            NewName = (* it).second;
            NewName = NewName.substr (0, NewName.find (' '));
            source = (* it).second;
            source = source.substr (source.find (' ') + 1);
            Outcome = OUTCOME :: Explicit;
        }

    }

    else
    {
        if (GroupCnt && typeL == TAKA :: OBSR)
        {
            if ((Global :: MapVars.find ("obs " + OrgName)) != Global :: MapVars.end ())
            {
                NewName = OrgName;
                source = "obs ";
                Try = NewName;
                Outcome = OUTCOME :: Implicit;
            }

            else
            {
                string mod_var = ID.substr (ID.find (' ') + 1) + '#';
                if ((Global :: MapVars.find (mod_var)) != Global :: MapVars.end ())
                {
                    NewName = OrgName + '#';
                    source = module + ' ';
                    Try = NewName;
                    Outcome = OUTCOME :: Implicit;
                }

            }

        }

        else
        if ((GroupCnt || StructCnt) && type == TAKA :: VARG)
        {
            string A;
            if (GroupCnt)
            {
                Common :: GroupEnding (A, GroupCnt);
            }

            if (StructCnt)
            {
                Common :: GroupEnding (A, StructCnt);
            }

            NewName.append (A);
            ID = AKAstrings [(int) type] + ' ' + module + ' ' + NewName;
            if ((it = Global :: MapAKA.find (ID)) != Global :: MapAKA.end ())
            {
                Try = (* it).second;
                Try = Try.substr (0, Try.find ('@'));
                if (Global :: DeclRootList -> IndexOf (string (base.c_str ()) + " " + Try.c_str ()) > - 1)
                {
                    Outcome = OUTCOME :: IgnoreVar;
                }

                else
                {
                    NewName = (* it).second;
                    NewName = NewName.substr (0, NewName.find (' '));
                    Outcome = OUTCOME :: Implicit;
                }

            }

        }

    }

    ID = AKAstrings [(int) typeL] + " (" + base + ") " + module + " -> " + OrgName + ' ';
    switch (Outcome) {
    case OUTCOME :: IgnoreObs:
        LogMessage (string (ID + " *** AKA warning, not changed to *** " + source + "->" + Try).c_str ());
        break;
    case OUTCOME :: IgnoreObsFunct:
        LogMessage (string (ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str ());
        break;
    case OUTCOME :: IgnoreVar:
        LogMessage (string (ID + "*** AKA warning, not changed to *** " + source + "->" + Try).c_str ());
        break;
    default:
        break;
    }
    if (Global :: ReportList && Outcome != OUTCOME :: None)
    {
        string reason = "";
        switch (Outcome) {
        case OUTCOME :: Explicit:
            source = (ID + " changed to " + source + "-> " + Try).c_str ();
            reason = " *** Explicit *** ";
            break;
        case OUTCOME :: Implicit:
            source = (ID + " changed to " + source + "-> " + Try).c_str ();
            reason = " *** Implicit *** ";
            break;
        case OUTCOME :: IgnoreObs:
            source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str ();
            reason = " *** source module AKA observation redirection would loop output to input";
            break;
        case OUTCOME :: IgnoreObsFunct:
            source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str ();
            reason = " *** daily function cannot be a declared observation";
            break;
        case OUTCOME :: IgnoreVar:
            source = (ID + " AKA warning, not changed to " + source + "-> " + Try).c_str ();
            reason = " *** source module AKA variable redirection would loop output to input";
            break;
        default:
            break;
        }
        Global :: ReportList -> Add ((source + reason).c_str ());
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::AKAhook(TAKA type, string module, string OrgName, string & NewName, string & source, string base)@@@ClassModule.cpp>");
}
void ClassModule :: InitReadObs (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::InitReadObs(void)@@@ClassModule.cpp>");
    ReadListN -> Clear ();
    FunctListN -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</ClassModule::InitReadObs(void)@@@ClassModule.cpp>");
}
void ClassModule :: ReadObs (bool Reset)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::ReadObs(bool Reset)@@@ClassModule.cpp>");
    static long p;
    static long pN;
    static long LastGroup;
    if (Reset)
    {
        p = 0;
        pN = 0;
        LastGroup = - 1;
    }

    if (Global :: DTindx % Global :: Freq == 0)
    {
        while (pN != FunctListN -> Count && FunctListN -> Strings [pN] == Name.c_str ()) {
            ClassVar * P = (ClassVar *) FunctListN -> array [pN].Object;
            P -> dim = nhru;
            if (P -> FunctVar -> FileData -> GoodDay)
            {
                (P ->* (P -> UserFunct)) ();
                if (P -> name == "t")
                {
                    this -> t_layvalues = P -> layvalues;
                }

                else
                if (P -> name == "rh")
                {
                    this -> rh_layvalues = P -> layvalues;
                }

            }

            if (P -> CustomFunct)
            {
                (P ->* (P -> CustomFunct)) (this);
            }

            ++ pN;
        }
    }

    while (p < ReadListN -> Count && ((ReadListN -> Strings [p] == Name.c_str ()) || GroupCnt == 0)) {
        ClassVar * P = (ClassVar *) ReadListN -> array [p].Object;
        P -> dim = nhru;
        if (P -> module == "obs" || (GroupCnt && ! P -> No_ReadVar))
        {
            P -> ReadVar ();
        }

        if (P -> CustomFunct)
        {
            (P ->* (P -> CustomFunct)) (this);
        }

        ++ p;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadObs(bool Reset)@@@ClassModule.cpp>");
}
bool ClassModule :: ReadAheadObs (long inc)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::ReadAheadObs(long inc)@@@ClassModule.cpp>");
    if (Global :: DTindx + inc >= Global :: DTmax || Global :: DTindx + inc < Global :: DTmin)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadAheadObs(long inc)@@@ClassModule.cpp>");
        return false;
    }

    long CurrentDTindx = Global :: DTindx;
    TDateTime CurrentDTnow = Global :: DTnow;
    Global :: DTindx += inc;
    Global :: DTnow = Global :: DTstart + Global :: Interval * ((long long) Global :: DTindx + 1ll);
    long p = 0;
    while (p < ReadListN -> Count) {
        ClassVar * P = (ClassVar *) ReadListN -> array [p].Object;
        if (P -> FileData -> GoodInterval)
        {
            P -> ReadVar ();
        }

        ++ p;
    }
    if (Global :: DTindx % Global :: Freq == 0)
    {
        p = 0;
        while (p < FunctListN -> Count && FunctListN -> Strings [p] == Name.c_str ()) {
            ClassVar * P = (ClassVar *) FunctListN -> array [p].Object;
            if (P -> FunctVar -> FileData -> GoodDay)
            {
                (P ->* (P -> UserFunct)) ();
            }

            ++ p;
        }
    }

    Global :: DTindx = CurrentDTindx;
    Global :: DTnow = CurrentDTnow;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadAheadObs(long inc)@@@ClassModule.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadAheadObs(long inc)@@@ClassModule.cpp>");
}
bool ClassModule :: ReadAheadObsMacro (long inc)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::ReadAheadObsMacro(long inc)@@@ClassModule.cpp>");
    if (Global :: DTindx + inc >= Global :: DTmax || Global :: DTindx + inc < Global :: DTmin)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadAheadObsMacro(long inc)@@@ClassModule.cpp>");
        return false;
    }

    long CurrentDTindx = Global :: DTindx;
    long ** Save_HRU_obs = Global :: HRU_OBS;
    Global :: DTindx += inc;
    Global :: DTnow = Global :: DTstart + Global :: Interval * ((long long) Global :: DTindx + 1ll);
    long p = 0;
    while (p < ReadListN -> Count) {
        ClassVar * P = (ClassVar *) ReadListN -> array [p].Object;
        if (P -> FileData -> GoodInterval)
        {
            P -> ReadVar ();
        }

        ++ p;
    }
    if (Global :: DTindx % Global :: Freq == 0)
    {
        p = 0;
        while (p < FunctListN -> Count) {
            ClassVar * P = (ClassVar *) FunctListN -> array [p].Object;
            if (P -> FunctVar -> FileData -> GoodDay)
            {
                (P ->* (P -> UserFunct)) ();
            }

            ++ p;
        }
    }

    Global :: DTindx = CurrentDTindx;
    Global :: HRU_OBS = Save_HRU_obs;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadAheadObsMacro(long inc)@@@ClassModule.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::ReadAheadObsMacro(long inc)@@@ClassModule.cpp>");
}
bool ClassModule :: WriteAheadObsMacro (long inc)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::WriteAheadObsMacro(long inc)@@@ClassModule.cpp>");
    if (Global :: DTindx + inc >= Global :: DTmax || Global :: DTindx + inc < Global :: DTmin)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::WriteAheadObsMacro(long inc)@@@ClassModule.cpp>");
        return false;
    }

    long CurrentDTindx = Global :: DTindx;
    Global :: DTindx += inc;
    long p = 0;
    while (p < ReadListN -> Count) {
        ClassVar * P = (ClassVar *) ReadListN -> array [p].Object;
        if (P -> FileData -> GoodInterval)
        {
            P -> WriteVar ();
        }

        ++ p;
    }
    Global :: DTindx = CurrentDTindx;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::WriteAheadObsMacro(long inc)@@@ClassModule.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::WriteAheadObsMacro(long inc)@@@ClassModule.cpp>");
}
void ClassModule :: DelReadObs (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::DelReadObs(void)@@@ClassModule.cpp>");
    ReadListN -> Clear ();
    FunctListN -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</ClassModule::DelReadObs(void)@@@ClassModule.cpp>");
}
bool ClassModule :: AnyOne (double * Data, int Cnt, double Val)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::AnyOne(double * Data, int Cnt, double Val)@@@ClassModule.cpp>");
    if (Data == NULL)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::AnyOne(double * Data, int Cnt, double Val)@@@ClassModule.cpp>");
        return false;
    }

    for (int ii = 0; ii < Cnt; ++ ii)
        if (Data [ii] != Val)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::AnyOne(double * Data, int Cnt, double Val)@@@ClassModule.cpp>");
            return true;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::AnyOne(double * Data, int Cnt, double Val)@@@ClassModule.cpp>");
    return false;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::AnyOne(double * Data, int Cnt, double Val)@@@ClassModule.cpp>");
}
bool ClassModule :: UsingObservations (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::UsingObservations(void)@@@ClassModule.cpp>");
    if (ReadListN -> Count || FunctListN -> Count)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::UsingObservations(void)@@@ClassModule.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::UsingObservations(void)@@@ClassModule.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::UsingObservations(void)@@@ClassModule.cpp>");
}
void ClassModule :: addtoreadlist (ClassVar * newVar)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::addtoreadlist(ClassVar * newVar)@@@ClassModule.cpp>");
    long p = 0;
    ClassVar * P;
    while (p < ReadListN -> Count && GroupCnt == 0) {
        P = (ClassVar *) ReadListN -> array [p].Object;
        if (newVar == P)
        {
            if (this -> Name == this -> NameRoot)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::addtoreadlist(ClassVar * newVar)@@@ClassModule.cpp>");
                return;
            }

        }

        p ++;
    }
    if (((Global :: DTmax - Global :: DTmin) / Global :: Freq + newVar -> FileData -> Dt1 > newVar -> FileData -> Dt2) && ! newVar -> FileData -> Times)
    {
        CRHMException TExcept ((string ("Observation file '") + string (newVar -> FileData -> DataFileName.c_str ()) + "' shorter than model run!").c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    if (GroupCnt)
    {
        ReadListN -> AddObject (Name.c_str (), (TObject *) newVar);
    }

    else
    {
        ReadListN -> AddObject (newVar -> module.c_str (), (TObject *) newVar);
    }

    newVar -> CustomFunct = NULL;
    if (! Global :: OBS_AS_IS)
    {
        string :: size_type idx = newVar -> name.find ('@');
        string root_var;
        if (idx != string :: npos)
        {
            root_var = newVar -> name.substr (0, idx);
        }

        if (newVar -> name == "t_max" || newVar -> name == "t_min")
        {
            if (AnyOne (Global :: Warming_t, nhru, 0.0))
            {
                newVar -> CustomFunct = & ClassVar :: do_t_Clim;
                newVar -> CustomFunctName = "do_t_Clim";
            }

            else
            {
                newVar -> CustomFunct = & ClassVar :: do_t;
                newVar -> CustomFunctName = "do_t";
            }

        }

        else
        if ((! GroupCnt && newVar -> name == "p") || (GroupCnt && root_var == "p"))
        {
            if (AnyOne (Global :: Warming_p, nhru, 1.0))
            {
                newVar -> CustomFunct = & ClassVar :: do_p_Clim;
                newVar -> CustomFunctName = "do_p_Clim";
            }

            else
            {
                newVar -> CustomFunct = & ClassVar :: do_p;
                newVar -> CustomFunctName = "do_p";
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::addtoreadlist(ClassVar * newVar)@@@ClassModule.cpp>");
}
void ClassModule :: addtofunctlist (ClassVar * newVar)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::addtofunctlist(ClassVar * newVar)@@@ClassModule.cpp>");
    long p = 0;
    ClassVar * P;
    string :: size_type indx;
    while (p < FunctListN -> Count) {
        P = (ClassVar *) FunctListN -> array [p].Object;
        if (newVar == P)
        {
            if (this -> Name == this -> NameRoot && GroupCnt == 0)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::addtofunctlist(ClassVar * newVar)@@@ClassModule.cpp>");
                return;
            }

        }

        p ++;
    }
    FunctListN -> AddObject (Name.c_str (), (TObject *) newVar);
    if (NameRoot == "obs" || Name == "obs")
    {
        string RootName = newVar -> name;
        if (indx = RootName.find ("@"), indx != std :: string :: npos)
        {
            RootName = newVar -> name.substr (0, indx);
        }

        if (! Global :: OBS_AS_IS)
        {
            if (RootName == "Tday")
            {
                if (AnyOne (Global :: Warming_t, nhru, 0.0))
                {
                    newVar -> CustomFunct = & ClassVar :: do_t_day_Clim;
                    newVar -> CustomFunctName = "do_t_day_Clim";
                }

                else
                {
                    newVar -> CustomFunct = & ClassVar :: do_t_day;
                    newVar -> CustomFunctName = "do_t_day";
                }

            }

            else
            if (RootName == "RHday")
            {
                if (AnyOne (Global :: Warming_t, nhru, 0.0))
                {
                    newVar -> CustomFunct = & ClassVar :: do_rh_day_Clim;
                    newVar -> CustomFunctName = "do_rh_day_Clim";
                }

                else
                {
                    newVar -> CustomFunct = & ClassVar :: do_rh_day;
                    newVar -> CustomFunctName = "do_rh_day";
                }

            }

            else
            if (RootName == "EAday")
            {
                if (! AnyOne (Global :: Warming_t, nhru, 0.0))
                {
                    newVar -> CustomFunct = & ClassVar :: do_ea_day;
                    newVar -> CustomFunctName = "do_ea_day";
                }

            }

            else
            if (RootName == "t_min" || newVar -> name == "t_max")
            {
                if (AnyOne (Global :: Warming_t, nhru, 0.0))
                {
                    newVar -> CustomFunct = & ClassVar :: do_t_Clim;
                    newVar -> CustomFunctName = "do_t_Clim";
                }

                else
                {
                    newVar -> CustomFunct = & ClassVar :: do_t;
                    newVar -> CustomFunctName = "do_t";
                }

            }

            else
            if (RootName.substr (0, 4) == "pptD")
            {
                if (AnyOne (Global :: Warming_p, nhru, 1.0))
                {
                    newVar -> CustomFunct = & ClassVar :: do_ppt_Clim;
                    newVar -> CustomFunctName = "do_ppt_Clim";
                }

                else
                {
                    newVar -> CustomFunct = & ClassVar :: do_ppt;
                    newVar -> CustomFunctName = "do_ppt";
                }

            }

        }

        else
        {
            newVar -> CustomFunct = NULL;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::addtofunctlist(ClassVar * newVar)@@@ClassModule.cpp>");
}
Administer :: Administer (string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::Administer(string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)@@@ClassModule.cpp>");
    DLLModuleList = new TStringList;
    DLLModelList = new TStringList;
    DLLModelModuleList = new TStringList;
    if (Global :: PendingDLLModuleList != NULL)
    {
        Global :: PendingDLLModuleList -> Clear ();
    }

InstrumentLogger::instance()->log_instrument_log("</Administer::Administer(string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)@@@ClassModule.cpp>");
}
Administer :: ~Administer ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::~Administer()@@@ClassModule.cpp>");
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii)
        delete ((ClassModule *) DLLModuleList -> array [ii].Object);
    delete DLLModuleList;
    delete DLLModelList;
    delete DLLModelModuleList;
InstrumentLogger::instance()->log_instrument_log("</Administer::~Administer()@@@ClassModule.cpp>");
}
void Administer :: MacroClear ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::MacroClear()@@@ClassModule.cpp>");
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii) {
        ClassModule * thisModule = (ClassModule *) DLLModuleList -> array [ii].Object;
        delete thisModule;
    }
    if (Global :: OurHelpList)
    {
        int indx = Global :: OurHelpList -> IndexOf (HelpFile);
        if (indx > - 1)
        {
            Global :: OurHelpList -> Delete (indx);
        }

    }

    DLLModuleList -> Clear ();
    DLLModelList -> Clear ();
    DLLModelModuleList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</Administer::MacroClear()@@@ClassModule.cpp>");
}
void Administer :: MacroUpdate ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::MacroUpdate()@@@ClassModule.cpp>");
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii) {
        int jj = Global :: OurModulesList -> IndexOf (DLLModuleList -> Strings [ii]);
        if (jj > - 1)
        {
            Global :: OurModulesList -> Objects [jj] = DLLModuleList -> Objects [ii];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Administer::MacroUpdate()@@@ClassModule.cpp>");
}
void Administer :: AddModule (ClassModule * Module)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::AddModule(ClassModule * Module)@@@ClassModule.cpp>");
    Module -> OurAdmin = this;
    DLLModuleList -> AddObject ((Module) -> Name.c_str (), (TObject *) Module);
    Global :: PendingDLLModuleList -> AddObject ((Module) -> Name.c_str (), (TObject *) Module);
InstrumentLogger::instance()->log_instrument_log("</Administer::AddModule(ClassModule * Module)@@@ClassModule.cpp>");
}
void Administer :: AddModel (string ModelName, string ModelModules)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::AddModel(string ModelName, string ModelModules)@@@ClassModule.cpp>");
    DLLModelModuleList -> Add (ModelModules);
    long _object = DLLModelModuleList -> Count - 1;
    DLLModelList -> AddObject (ModelName, (TObject *) _object);
InstrumentLogger::instance()->log_instrument_log("</Administer::AddModel(string ModelName, string ModelModules)@@@ClassModule.cpp>");
}
void Administer :: LoadCRHM (string DllName)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::LoadCRHM(string DllName)@@@ClassModule.cpp>");
    DLLName = DllName;
InstrumentLogger::instance()->log_instrument_log("</Administer::LoadCRHM(string DllName)@@@ClassModule.cpp>");
}
void Administer :: Accept (int Result)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::Accept(int Result)@@@ClassModule.cpp>");
    string Exists;
    ClassModule * thisModule;
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii) {
        if (Global :: PendingDLLModuleList -> Count > 0 && Global :: PendingDLLModuleList -> IndexOf (DLLModuleList -> Strings [ii]) == - 1)
        {
            continue;
        }

        int jj = Global :: AllModulesList -> IndexOf (DLLModuleList -> Strings [ii]);
        if (jj != - 1)
        {
            Exists = "Over-write existing module \"";
        }

        else
        {
            Exists = "Load Module \"";
        }

        if (Global :: AllModulesList -> IndexOf (DLLModuleList -> Strings [ii]) == - 1 && Global :: OurModulesList -> IndexOf (DLLModuleList -> Strings [ii]) != - 1)
        {
            Result = mbYes;
        }

        switch (Result) {
        case mbYes:
        case mbYesToAll:
            if (jj != - 1)
            {
                LogError (CRHMException ((DLLModuleList -> Strings [ii] + " module being replaced").c_str (), TExcept :: WARNING));
                Global :: AllModulesList -> Delete (jj);
            }

            thisModule = (ClassModule *) DLLModuleList -> Objects [ii];
            thisModule -> DLLName = DLLName;
            if (thisModule -> DLLName != "Macro")
            {
                thisModule -> ID = typeid (* thisModule).name ();
            }

            Global :: AllModulesList -> AddObject (DLLModuleList -> Strings [ii], (TObject *) DLLModuleList -> Objects [ii]);
            break;
        case mbNo:
        case mbNoToAll:
            continue;
        default:
            break;
        }
    }
    for (int ii = 0; ii < DLLModelList -> Count; ++ ii) {
        long _object = ii;
        Global :: AllModelsList -> AddObject (DLLModelList -> Strings [ii], (TObject *) _object);
        Global :: ModelModulesList -> AddObject (DLLModelModuleList -> Strings [ii], (TObject *) this);
    }
    if (Global :: OurHelpList)
    {
        if (Global :: OurHelpList -> IndexOf (HelpFile) < 0)
        {
            Global :: OurHelpList -> AddObject (HelpFile, (TObject *) 1);
        }

        else
        {
            Global :: OurHelpList -> AddObject (HelpFile, (TObject *) 0);
        }

    }

    Global :: PendingDLLModuleList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</Administer::Accept(int Result)@@@ClassModule.cpp>");
}
Myparser :: Myparser ()
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::Myparser()@@@ClassModule.cpp>");
    exp_ptr = NULL;
    for (int i = 0; i < 80; i ++) {
        token [i] = '\0';
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::Myparser()@@@ClassModule.cpp>");
}
void Myparser :: eval_exp (ClassPar * Par)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp(ClassPar * Par)@@@ClassModule.cpp>");
    LocalPar = Par;
    double result, Last;
    int stop;
    bool OpenBrkt;
    exp_ptr = Par -> valstr.c_str ();
    row = 0;
    col = 0;
    rowrepeat = 1;
    Bang = 0;
    next: repeat = 1;
    repeatset = false;
    OpenBrkt = false;
    get_token ();
    if (* token == '[')
    {
        result = 0.0;
    }

    else
    if (* token)
    {
        eval_exp2 (result);
        if (result > Par -> maxVal)
        {
            result = Par -> maxVal;
        }

        if (result < Par -> minVal)
        {
            result = Par -> minVal;
        }

        Last = result;
    }

    else
    {
        result = 0.0;
    }

    bool end = ! * exp_ptr;
    switch (* token) {
    case '\0':
        if (col >= Par -> dim)
        {
            break;
        }

        if (Par -> varType == TVar :: Float)
        {
            Par -> layvalues [row] [col ++] = result;
        }

        else
        if (Par -> varType == TVar :: Int)
        {
            Par -> ilayvalues [row] [col ++] = (long) result;
        }

        for (int ll = row; ll < Par -> lay; ++ ll) {
            if (Bang)
            {
                for (int ii = col - 1; ii < Par -> dim; ++ ii) {
                    if (Par -> varType == TVar :: Float)
                    {
                        Par -> layvalues [ll] [ii] = Last;
                    }

                    else
                    if (Par -> varType == TVar :: Int)
                    {
                        Par -> ilayvalues [ll] [ii] = (long) Last;
                    }

                    Last += 1;
                }
            }

            else
            {
                for (int ii = col; ii < Par -> dim; ++ ii)
                    if (Par -> varType == TVar :: Float)
                    {
                        Par -> layvalues [ll] [ii] = 0.0;
                    }

                    else
                    if (Par -> varType == TVar :: Int)
                    {
                        Par -> ilayvalues [ll] [ii] = 0;
                    }

            }

            col = 0;
            ;
        }
        break;
    case '[':
        rowrepeat = repeat;
        repeat = 1;
        repeatset = false;
        OpenBrkt = true;
        goto next;
    case ']':
        OpenBrkt = false;
        while (isspace (* exp_ptr)) ++ exp_ptr;
        if (* exp_ptr == ',')
        {
            ++ exp_ptr;
        }

        stop = col + repeat;
        if (stop > Par -> dim)
        {
            stop = Par -> dim;
        }

        for (int ii = col; ii < stop; ++ ii)
            if (Par -> varType == TVar :: Float)
            {
                Par -> layvalues [row] [col ++] = result;
            }

            else
            if (Par -> varType == TVar :: Int)
            {
                Par -> ilayvalues [row] [col ++] = (long) result;
            }

        for (int ii = col; ii < Par -> dim; ++ ii) {
            Last += Bang;
            if (Par -> varType == TVar :: Float)
            {
                Par -> layvalues [row] [ii] = Last;
            }

            else
            if (Par -> varType == TVar :: Int)
            {
                Par -> ilayvalues [row] [ii] = (long) Last;
            }

        }
        Bang = 0;
        row ++;
        col = 0;
        if (rowrepeat > 1 || end)
        {
            stop = row + rowrepeat - 1;
            if (stop > Par -> lay || end)
            {
                stop = Par -> lay;
            }

            for (int ll = row; ll < stop; ++ ll) {
                for (int ii = col; ii < Par -> dim; ++ ii)
                    if (Par -> varType == TVar :: Float)
                    {
                        Par -> layvalues [ll] [ii] = Par -> layvalues [ll - 1] [ii];
                    }

                    else
                    if (Par -> varType == TVar :: Int)
                    {
                        Par -> ilayvalues [ll] [ii] = Par -> ilayvalues [ll - 1] [ii];
                    }

            }
            row = stop;
            rowrepeat = 1;
        }

        if (row >= Par -> lay)
        {
            break;
        }

        goto next;
    case ',':
        stop = col + repeat;
        if (stop > Par -> dim)
        {
            stop = Par -> dim;
        }

        for (int ii = col; ii < stop; ++ ii)
            if (Par -> varType == TVar :: Float)
            {
                Par -> layvalues [row] [col ++] = result;
            }

            else
            if (Par -> varType == TVar :: Int)
            {
                Par -> ilayvalues [row] [col ++] = (long) result;
            }

        if (col >= Par -> dim)
        if (! OpenBrkt && (row + 1 < Par -> lay))
        {
            col = 0;
            ++ row;
        }

        goto next;
    default:
        serror (0);
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp(ClassPar * Par)@@@ClassModule.cpp>");
}
void Myparser :: eval_exp2 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp2(double & result)@@@ClassModule.cpp>");
    char op;
    double temp;
    eval_exp3 (result);
    while ((op = * token) == '+' || op == '-') {
        get_token ();
        eval_exp3 (temp);
        switch (op) {
        case '-':
            result = result - temp;
            break;
        case '+':
            result = result + temp;
            break;
        default:
            break;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp2(double & result)@@@ClassModule.cpp>");
}
void Myparser :: eval_exp3 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp3(double & result)@@@ClassModule.cpp>");
    char op;
    double temp;
    eval_exp4 (result);
    while ((op = * token) == '*' || op == '/' || op == '%') {
        get_token ();
        if (op == '*' && ! repeatset)
        {
            repeat = (int) result;
            repeatset = true;
            if (* token == '[')
            {

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp3(double & result)@@@ClassModule.cpp>");
                return;
            }

            eval_exp4 (result);

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp3(double & result)@@@ClassModule.cpp>");
            return;
        }

        eval_exp4 (temp);
        switch (op) {
        case '*':
            result = result * temp;
            break;
        case '/':
            result = result / temp;
            break;
        case '%':
            result = (int) result % (int) temp;
            break;
        default:
            break;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp3(double & result)@@@ClassModule.cpp>");
}
void Myparser :: eval_exp4 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp4(double & result)@@@ClassModule.cpp>");
    double temp;
    eval_exp5 (result);
    if (* token == '^')
    {
        get_token ();
        eval_exp4 (temp);
        if (temp == 0.0)
        {
            result = 1.0;

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp4(double & result)@@@ClassModule.cpp>");
            return;
        }

        result = pow (result, temp);
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp4(double & result)@@@ClassModule.cpp>");
}
void Myparser :: eval_exp5 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp5(double & result)@@@ClassModule.cpp>");
    char op;
    op = 0;
    if (((tok_type == DELIMITER) && * token == '+') || * token == '-')
    {
        op = * token;
        get_token ();
    }

    eval_exp6 (result);
    if (op == '-')
    {
        result = - result;
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp5(double & result)@@@ClassModule.cpp>");
}
void Myparser :: eval_exp6 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp6(double & result)@@@ClassModule.cpp>");
    if (* token == '(')
    {
        repeatset = true;
        get_token ();
        eval_exp2 (result);
        if (* token != ')')
        {
            serror (1);
        }

        get_token ();
    }

    else
    {
        atom (result);
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp6(double & result)@@@ClassModule.cpp>");
}
void Myparser :: atom (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::atom(double & result)@@@ClassModule.cpp>");
    switch (tok_type) {
    case NUMBER:
        result = atof (token);
        get_token ();

InstrumentLogger::instance()->log_instrument_log("</Myparser::atom(double & result)@@@ClassModule.cpp>");
        return;
    default:
        serror (0);
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::atom(double & result)@@@ClassModule.cpp>");
}
void Myparser :: serror (int error)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::serror(int error)@@@ClassModule.cpp>");
    static string e [] = {"Syntax Error", "Unbalanced Parentheses", "No expression Present"};
    LogError (CRHMException (string (e [error]) + " in module '" + LocalPar -> module + "' parameter '" + LocalPar -> param + "'", TExcept :: WARNING));
    for (int ll = row; ll < LocalPar -> lay; ++ ll) {
        for (int ii = col; ii < LocalPar -> dim; ++ ii)
            if (LocalPar -> varType == TVar :: Float)
            {
                LocalPar -> layvalues [ll] [ii] = 0.0;
            }

            else
            if (LocalPar -> varType == TVar :: Int)
            {
                LocalPar -> ilayvalues [ll] [ii] = 0;
            }

    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::serror(int error)@@@ClassModule.cpp>");
}
void Myparser :: get_token ()
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::get_token()@@@ClassModule.cpp>");
    char * temp;
    tok_type = 0;
    temp = token;
    * temp = '\0';
    if (! * exp_ptr)
    {

InstrumentLogger::instance()->log_instrument_log("</Myparser::get_token()@@@ClassModule.cpp>");
        return;
    }

    while (isspace (* exp_ptr)) ++ exp_ptr;
    if (* exp_ptr == '!')
    {
        Bang = 1;
        ++ exp_ptr;
    }

    if ((* exp_ptr) && strchr ("+-*/%^=(),[]!", * exp_ptr))
    {
        tok_type = DELIMITER;
        * temp ++ = * exp_ptr ++;
    }

    else
    if (isalpha (* exp_ptr))
    {
        while (! isdelim (* exp_ptr)) * temp ++ = * exp_ptr ++;
        tok_type = CRHM :: VARIABLE;
    }

    else
    if (iswdigit (* exp_ptr))
    {
        while ((* exp_ptr) && strchr ("0123456789.", * exp_ptr)) * temp ++ = * exp_ptr ++;
        if ((* exp_ptr) && strchr ("eE", * exp_ptr))
        {
            * temp ++ = * exp_ptr ++;
            while ((* exp_ptr) && strchr ("+- ", * exp_ptr)) * temp ++ = * exp_ptr ++;
            while (! isdelim (* exp_ptr)) * temp ++ = * exp_ptr ++;
        }

        tok_type = NUMBER;
    }

    * temp = '\0';
InstrumentLogger::instance()->log_instrument_log("</Myparser::get_token()@@@ClassModule.cpp>");
}
int Myparser :: isdelim (char c)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::isdelim(char c)@@@ClassModule.cpp>");
    if (((* exp_ptr) && strchr (" +-/*%^=(),[]", c)) || c == 9 || c == '\r' || c == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Myparser::isdelim(char c)@@@ClassModule.cpp>");
        return 1;
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::isdelim(char c)@@@ClassModule.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</Myparser::isdelim(char c)@@@ClassModule.cpp>");
}
ClassClark :: ClassClark (const double * inVar, double * outVar, const double * kstorage, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), kstorage (kstorage), nhru (nhru)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::ClassClark(const double * inVar, double * outVar, const double * kstorage, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), kstorage (kstorage), nhru (nhru)@@@ClassModule.cpp>");
    LastIn = new double [nhru];
    LastOut = new double [nhru];
    c01 = new double [nhru];
    c2 = new double [nhru];
    NO_lag_release = new double [nhru];
    ilag = new long [nhru];
    maxlag = new long [nhru];
    ulag = new long [nhru];
    for (long hh = 0; hh < nhru; hh ++) {
        c01 [hh] = Global :: Interval * 0.5 / (kstorage [hh] + Global :: Interval * 0.5);
        c2 [hh] = (kstorage [hh] - Global :: Interval * 0.5) / (kstorage [hh] + Global :: Interval * 0.5);
        ilag [hh] = (long) (max < double > (lag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
        if (setlag == - 1 || ilag [hh] > setlag)
        {
            maxlag [hh] = ilag [hh] + 1;
        }

        else
        {
            maxlag [hh] = setlag + 1;
        }

        ulag [hh] = 0;
        LastIn [hh] = 0.0;
        LastOut [hh] = 0.0;
        NO_lag_release [hh] = 0.0;
    }
    LagArray = new double * [nhru];
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] = new double [maxlag [hh]];
        for (long jj = 0; jj < maxlag [hh]; jj ++)
            LagArray [hh] [jj] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassClark::ClassClark(const double * inVar, double * outVar, const double * kstorage, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), kstorage (kstorage), nhru (nhru)@@@ClassModule.cpp>");
}
ClassClark :: ~ClassClark ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::~ClassClark()@@@ClassModule.cpp>");
    delete [] LastIn;
    delete [] LastOut;
    delete [] c01;
    delete [] c2;
    delete [] NO_lag_release;
    delete [] ilag;
    delete [] maxlag;
    delete [] ulag;
    for (long hh = 0; hh < nhru; hh ++)
        delete [] LagArray [hh];
    delete [] LagArray;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::~ClassClark()@@@ClassModule.cpp>");
}
double ClassClark :: ChangeStorage (const double * kstorage, const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassModule.cpp>");
    double Last_c01 = c01 [hh];
    double Last_c2 = c2 [hh];
    if (c2 [hh] >= 1.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassModule.cpp>");
        return 0.0;
    }

    double Sstorage = (1.0 / (1.0 - c2 [hh])) * (c01 [hh] * LastIn [hh] + c2 [hh] * outVar [hh]);
    c01 [hh] = Global :: Interval * 0.5 / (kstorage [hh] + Global :: Interval * 0.5);
    c2 [hh] = (kstorage [hh] - Global :: Interval * 0.5) / (kstorage [hh] + Global :: Interval * 0.5);
    if (Sstorage <= 0.0 || Last_c01 == c01 [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassModule.cpp>");
        return 0.0;
    }

    LastOut [hh] = (Sstorage * (1.0 - c2 [hh]) - c01 [hh] * LastIn [hh]) / c2 [hh];

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassModule.cpp>");
    return Sstorage;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassModule.cpp>");
}
double ClassClark :: ChangeLag (const double * newlag, const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
    double LastValue;
    double Lag_storage = 0.0;
    long newilag = (long) (max < double > (newlag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        Lag_storage += LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    if (newilag == ilag [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
        return Lag_storage;
    }

    double * AccArray = new double [ilag [hh]];
    AccArray [0] = 0.0;
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        AccArray [ii] = AccArray [ii - 1] + LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    NO_lag_release [hh] = 0.0;
    delete [] LagArray [hh];
    LagArray [hh] = new double [newilag];
    ulag [hh] = 0;
    LagArray [hh] [ulag [hh]] = 0;
    for (int ii = 1; ii < newilag; ++ ii)
        LagArray [hh] [ii] = 0.0;
    if (newilag == 1)
    {
        NO_lag_release [hh] = AccArray [ilag [hh] - 1];
    }

    else
    if (ilag [hh] > 1 && AccArray [ilag [hh] - 1] > 0.0)
    {
        LastValue = 0.0;
        for (int mm = 1; mm < newilag - 1; ++ mm) {
            double Y = double (mm) / ((long long) newilag - 1ll) * ((long long) ilag [hh] - 1ll);
            int Yint = (int) (Y + 0.0001);
            double Ydif = Y - Yint;
            double NewValue = AccArray [Yint] + Ydif * (AccArray [Yint + 1] - AccArray [Yint]);
            LagArray [hh] [(ulag [hh] + mm) % newilag] = NewValue - LastValue;
            LastValue = NewValue;
        }
        LagArray [hh] [(ulag [hh] + newilag - 1) % newilag] = AccArray [ilag [hh] - 1] - LastValue;
    }

    delete [] AccArray;
    ilag [hh] = newilag;

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
    return Lag_storage;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
}
void ClassClark :: DoClark ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::DoClark()@@@ClassModule.cpp>");
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] [ulag [hh]] = inVar [hh] + NO_lag_release [hh];
        NO_lag_release [hh] = 0.0;
        ulag [hh] = ++ ulag [hh] % ilag [hh];
        outVar [hh] = c01 [hh] * (LagArray [hh] [ulag [hh]] + LastIn [hh]) + c2 [hh] * LastOut [hh];
        LastIn [hh] = LagArray [hh] [ulag [hh]];
        LastOut [hh] = outVar [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassClark::DoClark()@@@ClassModule.cpp>");
}
void ClassClark :: DoClark (const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::DoClark(const long hh)@@@ClassModule.cpp>");
    LagArray [hh] [ulag [hh]] = inVar [hh] + NO_lag_release [hh];
    NO_lag_release [hh] = 0.0;
    ulag [hh] = ++ ulag [hh] % ilag [hh];
    outVar [hh] = c01 [hh] * (LagArray [hh] [ulag [hh]] + LastIn [hh]) + c2 [hh] * LastOut [hh];
    LastIn [hh] = LagArray [hh] [ulag [hh]];
    LastOut [hh] = outVar [hh];
InstrumentLogger::instance()->log_instrument_log("</ClassClark::DoClark(const long hh)@@@ClassModule.cpp>");
}
double ClassClark :: Left (int hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::Left(int hh)@@@ClassModule.cpp>");
    double Slag = 0;
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        Slag += LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    if (c2 [hh] >= 1.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::Left(int hh)@@@ClassModule.cpp>");
        return 0.0;
    }

    double Sstorage = (1.0 / (1.0 - c2 [hh])) * (c01 [hh] * LastIn [hh] + c2 [hh] * outVar [hh]);

InstrumentLogger::instance()->log_instrument_log("</ClassClark::Left(int hh)@@@ClassModule.cpp>");
    return Slag + Sstorage;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::Left(int hh)@@@ClassModule.cpp>");
}
ClassMuskingum :: ClassMuskingum (const double * inVar, double * outVar, const double * k, const double * X_M, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), nhru (nhru)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::ClassMuskingum(const double * inVar, double * outVar, const double * k, const double * X_M, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), nhru (nhru)@@@ClassModule.cpp>");
    LastIn = new double [nhru];
    LastOut = new double [nhru];
    c0 = new double [nhru];
    c1 = new double [nhru];
    c2 = new double [nhru];
    ilag = new long [nhru];
    maxlag = new long [nhru];
    ulag = new long [nhru];
    long Biggest = 0;
    for (long hh = 0; hh < nhru; hh ++) {
        c0 [hh] = (Global :: Interval - 2.0 * k [hh] * X_M [hh]) / (2.0 * k [hh] * (1.0 - X_M [hh]) + Global :: Interval);
        c1 [hh] = (Global :: Interval + 2.0 * k [hh] * X_M [hh]) / (2.0 * k [hh] * (1.0 - X_M [hh]) + Global :: Interval);
        c2 [hh] = (2.0 * k [hh] * (1.0 - X_M [hh]) - Global :: Interval) / (2.0 * k [hh] * (1.0 - X_M [hh]) + Global :: Interval);
        ilag [hh] = (long) (max < double > (lag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
        if (setlag == - 1 || ilag [hh] > setlag)
        {
            maxlag [hh] = ilag [hh];
        }

        else
        {
            maxlag [hh] = setlag;
        }

        ulag [hh] = 0;
        LastIn [hh] = 0.0;
        LastOut [hh] = 0.0;
        if (maxlag [hh] > Biggest)
        {
            Biggest = maxlag [hh];
        }

    }
    LagArray = new double * [nhru];
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] = new double [maxlag [hh]];
        for (long jj = 0; jj < maxlag [hh]; jj ++)
            LagArray [hh] [jj] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::ClassMuskingum(const double * inVar, double * outVar, const double * k, const double * X_M, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), nhru (nhru)@@@ClassModule.cpp>");
}
ClassMuskingum :: ~ClassMuskingum ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::~ClassMuskingum()@@@ClassModule.cpp>");
    delete [] LastIn;
    delete [] LastOut;
    delete [] c0;
    delete [] c1;
    delete [] c2;
    delete [] ilag;
    delete [] maxlag;
    delete [] ulag;
    for (long hh = 0; hh < nhru; hh ++)
        delete [] LagArray [hh];
    delete [] LagArray;
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::~ClassMuskingum()@@@ClassModule.cpp>");
}
void ClassMuskingum :: ChangeLag (const double * newlag, const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
    long newilag = (long) (max < double > (newlag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
    if (newilag == ilag [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
        return;
    }

    double * AccArray = new double [ilag [hh]];
    AccArray [0] = 0.0;
    for (int ii = 1; ii < ilag [hh]; ++ ii) {
        AccArray [ii] = AccArray [ii - 1] + LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    }
    delete [] LagArray [hh];
    LagArray [hh] = new double [newilag];
    ulag [hh] = 0;
    LagArray [hh] [0] = 0.0;
    double LastValue = 0.0;
    for (int mm = 1; mm < newilag - 1; ++ mm) {
        double Y = double (mm) / ((long long) newilag - 1ll) * ((long long) ilag [hh] - 1ll);
        int Yint = (int) (Y + 0.0001);
        if ((Yint + 1) > ilag [hh] - 1)
        {
            CRHMException Except ("Attempting to read out of bounds array address", TExcept :: TERMINATE);
            LogError (Except);
            throw (Except);
        }

        double Ydif = Y - Yint;
        double NewValue = AccArray [Yint] + Ydif * (AccArray [Yint + 1] - AccArray [Yint]);
        LagArray [hh] [(ulag [hh] + mm) % newilag] = NewValue - LastValue;
        LastValue = NewValue;
    }
    LagArray [hh] [(ulag [hh] + newilag - 1) % newilag] = AccArray [ilag [hh] - 1] - LastValue;
    delete [] AccArray;
    ilag [hh] = newilag;
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::ChangeLag(const double * newlag, const long hh)@@@ClassModule.cpp>");
}
void ClassMuskingum :: DoMuskingum ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::DoMuskingum()@@@ClassModule.cpp>");
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] [ulag [hh]] = inVar [hh];
        ulag [hh] = ++ ulag [hh] % ilag [hh];
        outVar [hh] = c0 [hh] * LagArray [hh] [ulag [hh]] + c1 [hh] * LastIn [hh] + c2 [hh] * LastOut [hh];
        LastIn [hh] = LagArray [hh] [ulag [hh]];
        LastOut [hh] = outVar [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::DoMuskingum()@@@ClassModule.cpp>");
}
void ClassMuskingum :: DoMuskingum (const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::DoMuskingum(const long hh)@@@ClassModule.cpp>");
    LagArray [hh] [ulag [hh]] = inVar [hh];
    ulag [hh] = ++ ulag [hh] % ilag [hh];
    outVar [hh] = c0 [hh] * LagArray [hh] [ulag [hh]] + c1 [hh] * LastIn [hh] + c2 [hh] * LastOut [hh];
    LastIn [hh] = LagArray [hh] [ulag [hh]];
    LastOut [hh] = outVar [hh];
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::DoMuskingum(const long hh)@@@ClassModule.cpp>");
}
double ClassMuskingum :: Left (int hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::Left(int hh)@@@ClassModule.cpp>");
    double Slag = 0;
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        Slag += LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    double Sstorage = (1.0 / (1.0 - c2 [hh])) * (c1 [hh] * LastIn [hh] + c2 [hh] * outVar [hh]);

InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::Left(int hh)@@@ClassModule.cpp>");
    return Slag + Sstorage;
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::Left(int hh)@@@ClassModule.cpp>");
}
long ClassModule :: getdim (TDim dimen)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
    MapDim :: iterator itDim;
    string s;
    switch (dimen) {
    case TDim :: BASIN:

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
        return ((int) dimen);
    case TDim :: NHRU:
        if (nhru)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
            return (nhru);
        }

        else
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
            return (Global :: nhru);
        }

    case TDim :: NOBS:

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
        return (Global :: nhru);
    case TDim :: NLAY:

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
        return (Global :: nlay);
    default:

InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
        return (- 1);
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::getdim(TDim dimen)@@@ClassModule.cpp>");
}
TAKA AKAtype (string type)
{
InstrumentLogger::instance()->log_instrument_log("<AKAtype(string type)@@@ClassModule.cpp>");
    TAKA Type = TAKA :: AKAERROR;
    for (int ii = (int) TAKA :: VARG; ii < (int) TAKA :: AKAEND; ++ ii)
        if (type == AKAstrings [ii])
        {
            Type = (TAKA) ii;
            break;
        }

InstrumentLogger::instance()->log_instrument_log("</AKAtype(string type)@@@ClassModule.cpp>");
    return Type;
InstrumentLogger::instance()->log_instrument_log("</AKAtype(string type)@@@ClassModule.cpp>");
}
bool ClassModule :: Variation_Skip (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::Variation_Skip(void)@@@ClassModule.cpp>");
    if ((Global :: BuildFlag == TBuild :: BUILD && variation == 0) || ((variation_set & 2048) != 0 && variation == 0) || (variation_set & 4096) != 0 || (variation_set == 0) || (variation_set & variation) != 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::Variation_Skip(void)@@@ClassModule.cpp>");
        return false;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::Variation_Skip(void)@@@ClassModule.cpp>");
        return true;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::Variation_Skip(void)@@@ClassModule.cpp>");
}
long ClassModule :: declputparam (string source, string param, string units, double ** value, double ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar = NULL;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
        return - 1;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, param, units);
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (param.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
            return - 1;
        }
    case TBuild :: DECL:
        {
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                newPar -> Inhibit_share = 1;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
                return 0;
            }

            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru)
                {
                    newPar = (* itPar).second;
                }

                newPar -> Inhibit_share = 1;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
                return 0;
            }

            newPar = new ClassPar (string (Name.c_str ()), string (param), TDim :: NHRU, "", 0, 0, "", units, TVar :: Float);
            newPar -> basemodule = this -> NameRoot;
            newPar -> variation_set = variation_set;
            newPar -> visibility = TVISIBLE :: USUAL;
            if (this -> GroupCnt)
            {
                newPar -> Inhibit_share = 2;
            }

            Myparser ob;
            ob.eval_exp (newPar);
            PairPar Item = PairPar (Name + " " + param, newPar);
            Global :: MapPars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
            return - 1;
        }
    case TBuild :: INIT:
        {
            if (source [0] != '*')
            {
                if ((itPar = Global :: MapPars.find (source + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share != 2)
                    {
                        * value = newPar -> values;
                        if (layvalue != NULL)
                        {
                            (* layvalue) = newPar -> layvalues;
                        }

                    }

                }

            }

            else
            {
                if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * value = newPar -> values;
                    if (layvalue != NULL)
                    {
                        (* layvalue) = newPar -> layvalues;
                    }

                }

                else
                if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share != 2)
                    {
                        * value = newPar -> values;
                        if (layvalue != NULL)
                        {
                            (* layvalue) = newPar -> layvalues;
                        }

                    }

                }

                else
                if ((newPar = ClassParFindPar (param)))
                {
                    if (newPar -> Inhibit_share != 2)
                    {
                        * value = newPar -> values;
                        if (layvalue != NULL)
                        {
                            (* layvalue) = newPar -> layvalues;
                        }

                    }

                }

                else
                {
                    CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
                return 0;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, double ** value, double ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: declgetparam (string source, string param, string units, const double ** value, const double ** * layvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar;
    if (Variation_Skip ())
    {
        * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
        return - 1;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, param, units);
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (param.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
            return - 1;
        }
    case TBuild :: DECL:
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
            return - 1;
        }
    case TBuild :: INIT:
        {
            if (source [0] != '*')
            {
                if ((itPar = Global :: MapPars.find (source + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * value = newPar -> values;
                    if (layvalue != NULL)
                    {
                        * layvalue = (const double **) newPar -> layvalues;
                    }

                }

            }

            else
            {
                if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * value = (const double *) newPar -> values;
                    if (layvalue != NULL)
                    {
                        * layvalue = (const double **) newPar -> layvalues;
                    }

                }

                else
                if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * value = (const double *) newPar -> values;
                    if (layvalue != NULL)
                    {
                        * layvalue = (const double **) newPar -> layvalues;
                    }

                }

                else
                if ((newPar = ClassParFindPar (param)))
                {
                    * value = newPar -> values;
                    if (layvalue != NULL)
                    {
                        * layvalue = (const double **) newPar -> layvalues;
                    }

                }

                else
                {
                    CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
                return 0;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const double ** value, const double ** * layvalue)@@@ClassModule.cpp>");
}
long ClassModule :: FindModule_from_parameter (string source, string param)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::FindModule_from_parameter(string source, string param)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar = NULL;
    variation_max = variation_max | variation_set;
    AKAhook (TAKA :: PARD, Name, param, param);
    if (source [0] != '*')
    {
        if ((itPar = Global :: MapPars.find (source + " " + param)) != Global :: MapPars.end ())
        {
            newPar = (* itPar).second;
        }

    }

    else
    {
        if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
        {
            newPar = (* itPar).second;
        }

        else
        if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
        {
            newPar = (* itPar).second;
        }

        else
        if ((newPar = ClassParFindPar (param)))
        {
        }

        else
        {
            CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
            LogError (Except);
            throw Except;
        }

    }

    if (GroupCnt)
    {
        long ii = Global :: OurModulesList -> IndexOf (Name.c_str ());
    }

    else
    {
        long ii = Global :: OurModulesList -> IndexOf (newPar -> basemodule.c_str ());

InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindModule_from_parameter(string source, string param)@@@ClassModule.cpp>");
        return (long) Global :: OurModulesList -> array [ii].Object;
    }

    CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
    LogError (Except);
    throw Except;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::FindModule_from_parameter(string source, string param)@@@ClassModule.cpp>");
}
long ClassModule :: declputparam (string source, string param, string units, long ** ivalue, long ** * ilayvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar = NULL;
    if (Variation_Skip ())
    {
        * ivalue = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
        return - 1;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, param, units);
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (param.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
            return - 1;
        }
    case TBuild :: DECL:
        {
            if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
            {
                newPar = (* itPar).second;
                newPar -> Inhibit_share = 1;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
                return 0;
            }

            if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
            {
                if ((* itPar).second -> dim == this -> nhru)
                {
                    newPar = (* itPar).second;
                }

                newPar -> Inhibit_share = 1;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
                return 0;
            }

            newPar = new ClassPar (string (Name.c_str ()), string (param), TDim :: NHRU, "", 0, 0, "", units, TVar :: Int);
            newPar -> basemodule = this -> NameRoot;
            newPar -> variation_set = variation_set;
            newPar -> visibility = TVISIBLE :: USUAL;
            newPar -> Inhibit_share = 2;
            Myparser ob;
            ob.eval_exp (newPar);
            PairPar Item = PairPar (Name + " " + param, newPar);
            Global :: MapPars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
            return - 1;
        }
    case TBuild :: INIT:
        {
            if (source [0] != '*')
            {
                if ((itPar = Global :: MapPars.find (source + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share != 2)
                    {
                        * ivalue = newPar -> ivalues;
                        if (ilayvalue != NULL)
                        {
                            (* ilayvalue) = newPar -> ilayvalues;
                        }

                    }

                }

            }

            else
            {
                if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * ivalue = newPar -> ivalues;
                    if (ilayvalue != NULL)
                    {
                        (* ilayvalue) = newPar -> ilayvalues;
                    }

                }

                else
                if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    if (newPar -> Inhibit_share != 2)
                    {
                        * ivalue = newPar -> ivalues;
                        if (ilayvalue != NULL)
                        {
                            (* ilayvalue) = newPar -> ilayvalues;
                        }

                    }

                }

                else
                if ((newPar = ClassParFindPar (param)))
                {
                    if (newPar -> Inhibit_share != 2)
                    {
                        * ivalue = newPar -> ivalues;
                        if (ilayvalue != NULL)
                        {
                            (* ilayvalue) = newPar -> ilayvalues;
                        }

                    }

                }

                else
                {
                    CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
                return 0;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declputparam(string source, string param, string units, long ** ivalue, long ** * ilayvalue)@@@ClassModule.cpp>");
}
void ClassModule :: declgetparam (string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
    MapPar :: iterator itPar;
    ClassPar * newPar;
    if (Variation_Skip ())
    {
        * ivalue = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
        return;
    }

    variation_max = variation_max | variation_set;
    Convert convert;
    convert.CheckUnitsString (Name, param, units);
    AKAhook (TAKA :: PARD, Name, param, param);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (param.c_str (), variation_set);
            PairstrI Item = PairstrI (Name.c_str (), Item2);
            Global :: Mapdeclpar.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: DECL:
        {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
            return;
        }
    case TBuild :: INIT:
        {
            if (source [0] != '*')
            {
                if ((itPar = Global :: MapPars.find (source + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * ivalue = newPar -> ivalues;
                    if (ilayvalue != NULL)
                    {
                        * ilayvalue = (const long **) newPar -> ilayvalues;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
                    return;
                }

            }

            else
            {
                if ((itPar = Global :: MapPars.find (Name + " " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * ivalue = (const long *) newPar -> ivalues;
                    if (ilayvalue != NULL)
                    {
                        * ilayvalue = (const long **) newPar -> ilayvalues;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
                    return;
                }

                else
                if ((itPar = Global :: MapPars.find ("Shared " + param)) != Global :: MapPars.end ())
                {
                    newPar = (* itPar).second;
                    * ivalue = newPar -> ivalues;
                    if (ilayvalue != NULL)
                    {
                        * ilayvalue = (const long **) newPar -> ilayvalues;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
                    return;
                }

                else
                if ((newPar = ClassParFindPar (param)))
                {
                    * ivalue = newPar -> ivalues;
                    if (ilayvalue != NULL)
                    {
                        * ilayvalue = (const long **) newPar -> ilayvalues;
                    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
                    return;
                }

                else
                {
                    CRHMException Except ("Parameter not found: " + Name + " " + param, TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }

            }

        }
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassModule::declgetparam(string source, string param, string units, const long ** ivalue, const long ** * ilayvalue)@@@ClassModule.cpp>");
}
ClassModule * ClassModule :: link (string Module)
{
InstrumentLogger::instance()->log_instrument_log("<ClassModule::link(string Module)@@@ClassModule.cpp>");
    if (Name == Module.c_str ())
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::link(string Module)@@@ClassModule.cpp>");
        return NULL;
    }

    int jj = Global :: OurModulesList -> IndexOf (Module.c_str ());
    if (jj == - 1)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::link(string Module)@@@ClassModule.cpp>");
        return NULL;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassModule::link(string Module)@@@ClassModule.cpp>");
        return (ClassModule *) Global :: OurModulesList -> array [jj].Object;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassModule::link(string Module)@@@ClassModule.cpp>");
}