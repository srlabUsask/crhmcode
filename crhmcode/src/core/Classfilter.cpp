#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>
#include "Classfilter.h"
#include "ClassCRHM.h"
#include "../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"
#include "../core/InstrumentLogger.h"

using namespace std;
Classfilter :: Classfilter (ClassData * MyObs, string ToVar, string args, string argtypes): MyObs (MyObs), ToVar (ToVar), args (args), argtypes (argtypes), Vs (0), Cs (0), Error (0), ObsCnt (0), TotalCnt (0), FirstTime (true)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::Classfilter(ClassData * MyObs, string ToVar, string args, string argtypes): MyObs (MyObs), ToVar (ToVar), args (args), argtypes (argtypes), Vs (0), Cs (0), Error (0), ObsCnt (0), TotalCnt (0), FirstTime (true)@@@Classfilter.cpp>");
    for (unsigned int ii = 0; ii < argtypes.length (); ++ ii) {
        if (argtypes [ii] == 'V')
        {
            Vs ++;
        }

        else
        if (argtypes [ii] == 'C')
        {
            Cs ++;
        }

    }
    if (! ToVar.empty ())
    {
        ++ Vs;
    }

    if (Vs)
    {
        Data = new double ** [Vs];
        for (int ii = 0; ii < Vs; ++ ii) {
            Data [ii] = NULL;
        }
        DataIndx = new long [Vs];
        DataObsCnt = new long [Vs];
    }

    if (Cs > 0)
    {
        Constants = new double [Cs];
    }

InstrumentLogger::instance()->log_instrument_log("</Classfilter::Classfilter(ClassData * MyObs, string ToVar, string args, string argtypes): MyObs (MyObs), ToVar (ToVar), args (args), argtypes (argtypes), Vs (0), Cs (0), Error (0), ObsCnt (0), TotalCnt (0), FirstTime (true)@@@Classfilter.cpp>");
}
void Classfilter :: doFunctions (long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::doFunctions(long Line)@@@Classfilter.cpp>");
    for (int jj = 0; jj < ObsCnt; ++ jj) {
        doFunc (jj, Line);
    }
InstrumentLogger::instance()->log_instrument_log("</Classfilter::doFunctions(long Line)@@@Classfilter.cpp>");
}
Classfilter :: ~Classfilter ()
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::~Classfilter()@@@Classfilter.cpp>");
    if (Vs > 0)
    {
        if (! Error)
        {
            for (int jj = 0; jj < Vs; ++ jj)
                delete [] Data [jj];
        }

        delete [] Data;
        delete [] DataIndx;
        delete [] DataObsCnt;
    }

    if (Cs > 0)
    {
        delete [] Constants;
    }

InstrumentLogger::instance()->log_instrument_log("</Classfilter::~Classfilter()@@@Classfilter.cpp>");
}
void Classfilter :: error (string Mess)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::error(string Mess)@@@Classfilter.cpp>");
    string Mess2 = string (Mess);
    string F = string (string ("\"") + typeid (* this).name ());
    CRHMException Except (Mess2.c_str (), TExcept :: ERR);
    LogError (Except);
    Error = true;
InstrumentLogger::instance()->log_instrument_log("</Classfilter::error(string Mess)@@@Classfilter.cpp>");
}
void Classfilter :: fixup (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::fixup(void)@@@Classfilter.cpp>");
    for (int ii = 0; ii < Vs; ++ ii) {
        if (! Data [ii])
        {
            Data [ii] = new double * [ObsCnt];
        }

        for (int jj = 0; jj < ObsCnt; ++ jj) {
            if (ii == Vs - 1 && DataIndx [ii] + jj < TotalCnt)
            {
                if (MyObs -> Data [TotalCnt + jj])
                {
                    delete [] MyObs -> Data [TotalCnt + jj];
                }

                MyObs -> Data [TotalCnt + jj] = NULL;
            }

            int jjj = jj;
            if (jjj > DataObsCnt [ii] - 1)
            {
                jjj = DataObsCnt [ii] - 1;
            }

            double * X = MyObs -> Data [DataIndx [ii] + jjj];
            Data [ii] [jj] = X;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</Classfilter::fixup(void)@@@Classfilter.cpp>");
}
void Classfilter :: readargs ()
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::readargs()@@@Classfilter.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar;
    istringstream instr;
    double C;
    string V;
    long ee = args.find (")");
    string Comment = args.substr (ee + 1, args.size ());
    Common :: trim (Comment);
    if (Comment.empty ())
    {
        Comment = "filter";
    }

    else
    {
        long tt;
        while (tt = Comment.find ("\\t"), tt != string :: npos) {
            Comment.erase (tt, 1);
            Comment [tt] = ' ';
        }
    }

    args = args.substr (1, ee - 1);
    while (ee = args.find (','), ee > 0) {
        args [ee] = ' ';
    }
    instr.str (args);
    unsigned long Cnt;
    long IndexC = 0;
    long IndexV = 0;
    long pp, pp2;
    for (Cnt = 0; Cnt < argtypes.length (); ++ Cnt) {
        instr >> V;
        if (instr.fail ())
        {
            break;
        }

        pp = V.find_first_not_of ("0123456789 //:.+-Ee_");
        if (pp == - 1)
        {
            if (argtypes [Cnt] != 'C')
            {
                error ("expected constant");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
                return;
            }

            pp = V.find_first_of ("://_");
            if (pp != - 1)
            {
                pp2 = V.find_first_of ("_");
                if (pp2 == - 1)
                {
                    if (V [pp] == '/')
                    {
                        C = StrToDate (V);
                    }

                    else
                    {
                        C = StrToTime (V);
                    }

                }

                else
                {
                    string z (V, 1, pp2 - 1);
                    C = StrToDate (z);
                    z.assign (V, pp2 + 1, V.size ());
                    C += double (StrToTime (z) - 1.0 / Global :: Freq);
                }

            }

            else
            {
                C = Common :: StrtoDt (V);
            }

            Constants [IndexC ++] = C;
        }

        else
        {
            if (argtypes [Cnt] != 'V')
            {
                error ("expecting CONSTANT");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
                return;
            }

            if ((itVar = Global :: MapVars.find ("obs " + V)) != Global :: MapVars.end ())
            {
                thisVar = (* itVar).second;
                if (thisVar -> varType < TVar :: Read)
                {
                    error ("not observation variable");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
                    return;
                }

            }

            else
            {
                error ("unknown variable");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
                return;
            }

            DataIndx [IndexV] = thisVar -> offset;
            DataObsCnt [IndexV] = thisVar -> dim;
            ++ IndexV;
            if (ObsCnt == 0 || thisVar -> dim < ObsCnt)
            {
                ObsCnt = thisVar -> dim;
            }

        }

    }
    if (Cnt != argtypes.length ())
    {
        error ("too few arguments");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
        return;
    }

    if (Cnt > argtypes.length ())
    {
        error ("too many arguments");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
        return;
    }

    if (! ToVar.empty ())
    {
        TotalCnt = MyObs -> DataCnt + MyObs -> FilterCnt;
        if (ObsCnt == 0)
        {
            ++ ObsCnt;
        }

        MyObs -> FilterCnt += ObsCnt;
        if ((itVar = Global :: MapVars.find ("obs " + ToVar)) != Global :: MapVars.end ())
        {
            thisVar = (* itVar).second;
            if (thisVar -> varType >= TVar :: Read)
            {
                DataIndx [Vs - 1] = thisVar -> offset;
                DataObsCnt [Vs - 1] = ObsCnt;

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
                return;
            }

        }

        thisVar = declread ("obs", ToVar, ObsCnt, TotalCnt, MyObs, Comment);
        DataIndx [Vs - 1] = TotalCnt;
        DataObsCnt [Vs - 1] = ObsCnt;
        thisVar -> review_HRU_OBS ();
    }

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@Classfilter.cpp>");
}
double estar (double t)
{
InstrumentLogger::instance()->log_instrument_log("<estar(double t)@@@Classfilter.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</estar(double t)@@@Classfilter.cpp>");
        return 0.611 * exp (17.27 * t / (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</estar(double t)@@@Classfilter.cpp>");
        return 0.611 * exp (21.88 * t / (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</estar(double t)@@@Classfilter.cpp>");
}