#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>
#include "ClassData.h"
#include "ClassCRHM.h"
#include "../../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "../GlobalDll.h"
#include "../CRHMmain/CRHMLogger.h"
#include "../InstrumentLogger.h"

using namespace std;
ClassData :: ClassData (const ClassData & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::ClassData(const ClassData & Cl)@@@ClassData.cpp>");
    DataFileName = Cl.DataFileName;
    Description = Cl.Description;
    Dt1 = Cl.Dt1;
    Dt2 = Cl.Dt2;
    Interval = Cl.Interval;
    Lines = Cl.Lines;
    Freq = Cl.Freq;
    IndxMin = Cl.IndxMin;
    IndxMax = Cl.IndxMax;
    ModN = Cl.ModN;
    HdrLen = Cl.HdrLen;
    Position = Cl.Position;
    DataCnt = Cl.DataCnt;
    FilterCnt = Cl.FilterCnt;
    myMacro = Cl.myMacro;
    Simulation = Cl.Simulation;
    ForceInterval = Cl.ForceInterval;
    GoodInterval = Cl.GoodInterval;
    GoodDay = Cl.GoodDay;
    RunUsed = Cl.RunUsed;
    Success = Cl.Success;
    TimeIndx = Cl.TimeIndx;
    FirstFile = Cl.FirstFile;
    Data = new double * [DataCnt + FilterCnt];
    for (int jj = 0; jj < DataCnt + FilterCnt; ++ jj)
        Data [jj] = new double [Lines];
    if (Cl.Times)
    {
        Times = new double [Lines];
        for (long ii = 0; ii < Lines; ++ ii)
            Times [ii] = Cl.Times [ii];
    }

    else
    {
        Times = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassData::ClassData(const ClassData & Cl)@@@ClassData.cpp>");
}
ClassData & ClassData :: operator = (const ClassData & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::operator=(const ClassData & Cl)@@@ClassData.cpp>");
    if (this == & Cl)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::operator=(const ClassData & Cl)@@@ClassData.cpp>");
        return * this;
    }

    DataFileName = Cl.DataFileName;
    Description = Cl.Description;
    Dt1 = Cl.Dt1;
    Dt2 = Cl.Dt2;
    Interval = Cl.Interval;
    Lines = Cl.Lines;
    Freq = Cl.Freq;
    IndxMin = Cl.IndxMin;
    IndxMax = Cl.IndxMax;
    ModN = Cl.ModN;
    HdrLen = Cl.HdrLen;
    Position = Cl.Position;
    DataCnt = Cl.DataCnt;
    FilterCnt = Cl.FilterCnt;
    myMacro = Cl.myMacro;
    Simulation = Cl.Simulation;
    ForceInterval = Cl.ForceInterval;
    GoodInterval = Cl.GoodInterval;
    GoodDay = Cl.GoodDay;
    RunUsed = Cl.RunUsed;
    Success = Cl.Success;
    TimeIndx = Cl.TimeIndx;
    FirstFile = Cl.FirstFile;
    Data = new double * [DataCnt + FilterCnt];
    for (int jj = 0; jj < DataCnt + FilterCnt; ++ jj)
        Data [jj] = new double [Lines];
    if (Cl.Times)
    {
        Times = new double [Lines];
        for (long ii = 0; ii < Lines; ++ ii)
            Times [ii] = Cl.Times [ii];
    }

    else
    {
        Times = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassData::operator=(const ClassData & Cl)@@@ClassData.cpp>");
    return * this;
InstrumentLogger::instance()->log_instrument_log("</ClassData::operator=(const ClassData & Cl)@@@ClassData.cpp>");
}
bool ClassData :: DataReadFile (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::DataReadFile(void)@@@ClassData.cpp>");
    ifstream DataFile;
    ifstream :: pos_type Here, Here2;
    string Header, Var, Comment;
    istringstream instr;
    bool DecimalTime;
    FirstFile = ! Global :: DTstart;

    int D [5]
    {
    }
    ;
    long jj;
    long MaxLines = 0;
    bool SparseFlag = false;
    bool LineError = false;
    bool OneLine = false;
    ModN = 1;
    bitset < 128 > MyBitSet;
    DataFile.open (DataFileName, ios_base :: in);
    if (! DataFile)
    {
        CRHMException Except ("Missing observation " + DataFileName, TExcept :: ERR);
        LogError (Except);
        DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
        return false;
    }

    getline (DataFile, Description);
    HdrLen = 1;
    myMacro = new MacroClass (this);
    while (! DataFile.eof ()) {
        char c = DataFile.peek ();
        if (DataFile.fail ())
        {
            CRHMException Except ("Errors in observation file header" + DataFileName, TExcept :: ERR);
            LogError (Except);
            DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
            return false;
        }

        ++ HdrLen;
        if (c == '#')
        {
            getline (DataFile, Comment);
            break;
        }

        if (c == '/')
        {
            getline (DataFile, Comment);
        }

        else
        if (c == '$')
        {
            getline (DataFile, Comment);
            myMacro -> addfilter (Comment);
        }

        else
        {
            if (FilterCnt != 0)
            {
                CRHMException Except ("Filters must follow observations in file header " + DataFileName, TExcept :: ERR);
                LogError (Except);
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
                return false;
            }

            DataFile >> Var;
            DataFile >> jj;
            getline (DataFile, Comment);
            bool negative = false;
            if (jj < 0)
            {
                jj = labs (jj);
                negative = true;
            }

            ClassVar * ThisVar = declread ("obs", Var, jj, DataCnt, this, Comment);
            if (! ThisVar)
            {
                string S = string ("Observation '") + Var + "' defined in earlier observation file";
                CRHMException Except (S + "Observation variable already defined " + DataFileName, TExcept :: ERR);
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
                return false;
            }

            ThisVar -> review_HRU_OBS ();
            for (int ii = 0; ii < jj; ++ ii)
                if (negative)
                {
                    MyBitSet.set (DataCnt + jj - 1);
                }

            DataCnt = DataCnt + jj;
        }

    }
    if (! Simulation)
    {
        do {
            Here = DataFile.tellg ();
            DataFile >> Dt1;
            if (Dt1 > 3000.0)
            {
                DecimalTime = true;
            }

            else
            {
                DecimalTime = false;
                D [0] = (int) Dt1;
                for (int ii = 1; ii < 5; ii ++)
                    DataFile >> D [ii];
                Position = HdrLen;
                Dt1 = Encode24 (D);
            }

            Dt1 += TimeShiftFilter;
            if (DataFile.eof ())
            {
                CRHMException Except ("Error in observation file header " + DataFileName, TExcept :: ERR);
                LogError (Except);
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
                return false;
            }

            if (Global :: DTstart != 0.0 && Dt1 >= Global :: DTend)
            {
                CRHMException Except ("Error in observation file " + DataFileName, TExcept :: ERR);
                LogError (Except);
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
                return false;
            }

            getline (DataFile, Var);
            instr.clear ();
            instr.str (Var);
            double V;
            long Cols = 0;
            for (;;) {
                instr >> V;
                if (instr.fail ())
                {
                    break;
                }

                ++ Cols;
            }
            if (Cols < DataCnt)
            {
                CRHMException Except ("Header of file defines more observations than data columns. "
                    "Observation file header Error " + DataFileName, TExcept :: ERR);
                LogError (Except);
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
                return false;
            }

            else
            if (Cols > DataCnt)
            {
                CRHMException Except ("Header of file defines fewer observations than data columns. "
                    "Observation file header Warning - Column count > Data count " + DataFileName, TExcept :: WARNING);
                LogError (Except);
            }

            char c = DataFile.peek ();
            if (DataFile.eof ())
            {
                DataFile.clear ();
                CRHMException Except ("One line observation file. Observation file warning " + DataFileName, TExcept :: ERR);
                LogError (Except);
                OneLine = true;
                Dt2 = Dt1 + 1.0;
                Freq = 1;
                SparseFlag = true;
                Interval = 0.0;
                break;
            }

        }
        while (Global :: DTstart != 0.0 && Global :: DTstart > Dt1);
        if (Global :: DTstart == 0.0)
        {
            Global :: DTstart = floor (Dt1);
        }

        if (! OneLine)
        {
            if (DecimalTime)
            {
                DataFile >> Dt2;
            }

            else
            {
                for (int ii = 0; ii < 5; ii ++)
                    DataFile >> D [ii];
                Position = HdrLen + 1;
                Dt2 = Encode24 (D);
            }

            Dt2 += TimeShiftFilter;
            Interval = Dt2 - Dt1;
            if (Interval > 1.0)
            {
                Interval = 1.0;
                SparseFlag = true;
            }

            Freq = (long) (1.0 / Interval + 0.8 * Interval);
            Freq = Veto_Freq (Freq);
            Interval = (double) 1.0 / Freq;
            if (FirstFile)
            {
                IndxMin = 0;
            }

            else
            {
                IndxMin = (long) floor ((Dt1 - Global :: DTstart) * Freq + Interval / 2.0);
                if (Interval != 1)
                {
                    -- IndxMin;
                }

            }

            double mid = floor (Dt1) + Interval;
            double range = 0.00002;
            if (Dt1 > mid + range || (Dt1 < mid - range && Interval < 1.0))
            {
                CRHMException Except ("Observation file WARNING " + DataFileName, TExcept :: ERR);
                LogError (Except);
                if (IndxMin == 0)
                {
                    IndxMin = (long) ((Dt1 - floor (Dt1)) / Interval - 1);
                }

            }

            DataFile.seekg (0, ios_base :: end);
            ifstream :: pos_type Back = DataFile.tellg ();
            char c = '\0';
            bool white = true;
            long Fix = - 3;
            do {
                DataFile.seekg (Fix, ios :: end);
                -- Fix;
                c = DataFile.get ();
                if (white)
                {
                    white = isspace (c);
                }

            }
            while (c != '\n' || white);
            if (DecimalTime)
            {
                DataFile >> Dt2;
            }

            else
            {
                for (int ii = 0; ii < 5; ii ++)
                    DataFile >> D [ii];
                Position = 99998;
                Dt2 = Encode24 (D);
            }

        }

        Dt2 += TimeShiftFilter;
        if (Global :: DTend == 0.0)
        {
            Global :: DTend = Dt2;
        }

        if (Global :: DTend != 0.0 && Global :: DTend < Dt2)
        {
            Dt2 = Global :: DTend;
        }

        Lines = (long) ceil ((Dt2 - Dt1 + 1.0 / (static_cast < long long > (Freq) * 2)) * static_cast < long long > (Freq));
        if (SparseFlag && Lines < Global :: Freq)
        {
            Lines = Global :: Freq;
        }

        IndxMax = IndxMin + Lines - 1;
        DataFile.seekg (0, ios_base :: beg);
        getline (DataFile, Comment);
        while (Comment [0] != '#') getline (DataFile, Comment);
    }

    try {
        Data = new double * [DataCnt + FilterCnt];
        MaxLines = Lines;
        if (fmodl (Lines, Freq) > 0)
        {
            MaxLines = (Lines / Freq + 1) * Freq;
        }

        for (int jj = 0; jj < DataCnt + FilterCnt; jj ++) {
            Data [jj] = new double [MaxLines];
        }
        Times = new double [MaxLines];
    }
    catch (std :: bad_alloc) {
        CRHMException Except ("Could not allocate for observations file: " + DataFileName, TExcept :: TERMINATE);
        LogError (Except);
        throw (Except);
    }
    for (int i = 0; i < Lines; i ++) {
        for (int j = 0; j < DataCnt + FilterCnt; j ++) {
            Data [j] [i] = - 999999;
        }
    }
    myMacro -> fixup ();
    Dt1 = floor (Dt1);
    double DeltaH = Interval * 1.5;
    for (Position = 0; Position < Lines; ++ Position) {
        if (! Simulation)
        {
            if (DecimalTime)
            {
                DataFile >> Times [Position];
            }

            else
            {
                for (int ii = 0; ii < 5; ++ ii)
                    DataFile >> D [ii];
                Times [Position] = Encode24 (D);
            }

            if (DataFile.eof ())
            {
                Lines = Position;
                break;
            }

            if (! DecimalTime)
            {
                Times [Position] = Encode24 (D);
            }

            Times [Position] += TimeShiftFilter;
            Global :: DTnow = Times [Position];
            if (Position != 0 && Times [Position] <= Times [Position - 1])
            {
                char S [160];
                sprintf (S, "Earlier Date at line: %lu+, %5u %3u %3u %3u %3u in observation file ", Position, D [0], D [1], D [2], D [3], D [4]);
                CRHMException Except (S + DataFileName, TExcept :: ERR);
                LogError (Except);
                LineError = true;
                break;
            }

            for (int ii = 0; ii < DataCnt; ++ ii) {
                char c;
                while (c = DataFile.peek (), c == ' ' || c == '\t') DataFile.get ();
                if (DataFile.peek () == '\n')
                {
                    string S = string ("Check line ") + to_string (HdrLen + Position + 1) + string (" for missing columns in ");
                    CRHMException Except (S.c_str () + DataFileName, TExcept :: ERR);
                    if (! SparseFlag)
                    {
                    }

                    if (FirstFile)
                    {
                        LogError (Except);
                        LineError = true;
                    }

                    else
                    if (ii == 0)
                    {
                        SparseFlag = true;
                        -- Position;
                        continue;
                    }

                    else
                    {
                        Data [ii] [Position] = 35.93;
                    }

                }

                else
                {
                    DataFile >> Data [ii] [Position];
                }

                if (DataFile.fail ())
                {
                    string S = string ("Faulty data at line ") + to_string (HdrLen + Position + 1) + string (" in observation file ");
                    CRHMException Except (S.c_str () + DataFileName, TExcept :: ERR);
                    LogError (Except);
                    Lines = Position - 1;
                    LineError = true;
                    break;
                }

            }
            if (LineError)
            {
                break;
            }

            if (DataFile.peek () != '\n')
            {
                DataFile.ignore (256, '\n');
            }

            myMacro -> execute (Position);
        }

    }
    if (! Simulation && Dt2 > Times [Position - 1] + Interval / 2.0 && ! SparseFlag)
    {
        string S = string ("Interval frequency increases ") + string (" in observation file ");
        CRHMException Except (S + DataFileName, TExcept :: ERR);
        LogError (Except);
        SparseFlag = true;
    }

    if (Freq > 1 && fmodl (Lines, Freq) > 0 && ! SparseFlag)
    {
        CRHMException Except ("Last day is incomplete and is padded with 0.0 " + DataFileName, TExcept :: WARNING);
        LogError (Except);
        IndxMax = IndxMin + MaxLines - 1;
        for (long ll = Position; ll <= MaxLines - 1; ++ ll) {
            Times [ll] = Times [ll - 1] + 1.0 / Freq;
            Dt2 = Times [ll];
            for (long dd = 0; dd < DataCnt; ++ dd)
                Data [dd] [ll] = 0.0;
        }
    }

    if (LineError)
    {
        for (int ii = 0; ii < DataCnt + FilterCnt; ii ++)
            if (Data [ii])
            {
                delete [] Data [ii];
                Data [ii] = NULL;
            }

        delete [] Data;
        Data = NULL;
        delete [] Times;
        Times = NULL;
    }

    else
    {
        if (Lines < Freq)
        {
            SparseFlag = true;
        }

        if (! SparseFlag)
        {
            delete [] Times;
            Times = NULL;
            if ((ForceInterval == 96 && Freq == 144) || (ForceInterval == 144 && Freq == 96))
            {
                string S = string ("cannot convert 10 minute interval to 15 minute or vice versa") + string (" in observation file ");
                CRHMException Except (S + DataFileName, TExcept :: ERR);
                LogError (Except);
                ForceInterval = 0;
            }

            if (ForceInterval != Freq && ForceInterval)
            {
                double Result = 0.0;
                for (int jj = 0; jj < DataCnt + FilterCnt; ++ jj) {
                    if (! Data [jj])
                    {
                        continue;
                    }

                    double Divisor = 1.0;
                    long NCnt;
                    double Delta;
                    if (ForceInterval > Freq)
                    {
                        NCnt = ForceInterval / Freq;
                        double * NewData = new double [Lines * NCnt];
                        if (! MyBitSet [jj])
                        {
                            for (long ii = 0; ii < Lines * NCnt; ++ ii) {
                                long kk = ii % NCnt;
                                if (kk == 0)
                                {
                                    if (ii == 0)
                                    {
                                        Result = Data [jj] [ii / NCnt] * Divisor;
                                        Delta = 0.0;
                                    }

                                    else
                                    if (ii + NCnt >= Lines * NCnt)
                                    {
                                        Result = Data [jj] [ii / NCnt] * Divisor;
                                        Delta = 0.0;
                                    }

                                    else
                                    {
                                        Result = Data [jj] [ii / NCnt - 1] * Divisor;
                                        Delta = (Data [jj] [ii / NCnt] - Data [jj] [ii / NCnt - 1]) * Divisor;
                                    }

                                }

                                NewData [ii] = Result + Delta * (static_cast < long long > (ii % NCnt) + 1) / NCnt;
                            }
                        }

                        else
                        {
                            Divisor = (double) 1.0 / NCnt;
                            for (long ii = 0; ii < Lines * NCnt; ++ ii) {
                                long kk = ii % NCnt;
                                if (kk == 0)
                                {
                                    Result = Data [jj] [ii / NCnt] * Divisor;
                                }

                                NewData [ii] = Result;
                            }
                        }

                        delete [] Data [jj];
                        Data [jj] = NewData;
                        if (jj + 1 == DataCnt + FilterCnt)
                        {
                            Lines = Lines * NCnt;
                            Freq = Freq * NCnt;
                            Interval = Interval / NCnt;
                            IndxMin *= (long) TimeShiftFilter;
                            IndxMax = IndxMin + Lines - 1;
                        }

                    }

                    else
                    {
                        long NCnt = Freq / ForceInterval;
                        double * NewData = new double [Lines / NCnt];
                        if (! MyBitSet [jj])
                        {
                            Divisor = (double) NCnt;
                        }

                        Result = 0.0;
                        for (long ii = 0; ii < Lines; ++ ii) {
                            Result += Data [jj] [ii];
                            long kk = ii % NCnt;
                            if (kk == NCnt - 1)
                            {
                                NewData [ii / NCnt] = Result / Divisor;
                                Result = 0.0;
                            }

                        }
                        delete [] Data [jj];
                        Data [jj] = NewData;
                    }

                }
                if (ForceInterval < Freq)
                {
                    long NCnt = Freq / ForceInterval;
                    Lines = Lines / NCnt;
                    Freq = Freq / NCnt;
                    Interval = Interval * NCnt;
                    IndxMax = IndxMin + Lines - 1;
                }

                myMacro -> fixup ();
            }

        }

        else
        {
            if (SparseFlag && Simulation)
            {
                CRHMException Except ("File " + DataFileName + " contains simulation data with gaps. Discontinuous times in simulation data files is not currently supported.", TExcept :: TERMINATE);
                LogError (Except);
                throw (Except);
            }

            else
            {
                double * Temp = new double [Lines];
                for (long ii = 0; ii < Lines; ++ ii) {
                    Temp [ii] = Times [ii];
                }
                delete [] Times;
                Times = Temp;
            }

        }

    }

    delete myMacro;
    myMacro = NULL;
    DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassData.cpp>");
}
long ClassData :: Veto_Freq (long Freq)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
    const long OK_Values [14] = {1, 2, 3, 4, 6, 8, 12, 24, 48, 72, 96, 144, 192, 288};
    if (Freq <= 1)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
        return 1;
    }

    if (Freq >= OK_Values [13])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
        return OK_Values [13];
    }

    for (int ii = 1; ii < 14; ++ ii) {
        if (Freq <= OK_Values [ii])
        {
            if ((Freq - OK_Values [ii - 1]) < (OK_Values [ii] - Freq))
            {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
                return OK_Values [ii - 1];
            }

            else
            {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
                return OK_Values [ii];
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassData.cpp>");
}
ClassData :: ~ClassData ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::~ClassData()@@@ClassData.cpp>");
    if (Times != NULL)
    {
        delete [] Times;
        Times = NULL;
    }

    if (Data != NULL)
    {
        for (int ii = 0; ii < DataCnt + FilterCnt; ii ++)
            if (Data [ii])
            {
                delete [] Data [ii];
                Data [ii] = NULL;
            }

        delete [] Data;
        Data = NULL;
    }

    if (HdrLen == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::~ClassData()@@@ClassData.cpp>");
        return;
    }

    if (myMacro)
    {
        delete myMacro;
        myMacro = NULL;
    }

    MapVar :: iterator itVar;
    ClassVar * thisVar;
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end ();) {
        thisVar = (* itVar).second;
        if (thisVar -> varType == TVar :: Read && thisVar -> FileData == this)
        {
            delete thisVar;
            Global :: MapVars.erase (itVar ++);
        }

        else
        {
            ++ itVar;
        }

    }
    for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
        thisVar = (* itVar).second;
        if (thisVar -> FileData == this && (thisVar -> varType == TVar :: ReadF || thisVar -> varType == TVar :: ReadI || thisVar -> varType == TVar :: Float))
        {
            thisVar -> FileData = NULL;
            if (thisVar -> varType == TVar :: Float)
            {
                thisVar -> FunctVar = NULL;
                thisVar -> CustomFunct = NULL;
                thisVar -> CustomFunctName = "";
                continue;
            }

            thisVar -> ReleaseM ();
            thisVar -> dim = 1;
            thisVar -> dimMax = 1;
            if (thisVar -> DLLName.empty ())
            {
                thisVar -> cnt = 0;
            }

            thisVar -> offset = 0;
            if (thisVar -> varType == TVar :: ReadI)
            {
                thisVar -> varType = TVar :: Int;
            }

            if (thisVar -> varType == TVar :: ReadF)
            {
                thisVar -> varType = TVar :: Float;
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassData::~ClassData()@@@ClassData.cpp>");
}
double ClassData :: Encode24 (int D [])
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::Encode24(int D [])@@@ClassData.cpp>");
    try {
        if (D [3] == 24)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassData.cpp>");
            return StandardConverterUtility :: EncodeDateTime (D [0], D [1], D [2], 0, D [4]) + 1;
        }

        else
        {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassData.cpp>");
            return StandardConverterUtility :: EncodeDateTime (D [0], D [1], D [2], D [3], D [4]);
        }

    }
    catch (...) {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassData.cpp>");
        return 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassData.cpp>");
}