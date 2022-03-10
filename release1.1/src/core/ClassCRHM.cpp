#if defined (_WIN32)
    #include "stdafx.h"
#endif

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
#include "NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"
#include "InstrumentLogger.h"


using namespace std; long Index_;

void ClassVar :: BackUp ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::BackUp()@@@ClassCRHM.cpp>");
    long Fix = lay;
    if (lay == 0)
    {
        Fix = 1;
    }

    if (varType == TVar :: Float)
    {
        layvaluesBkup = new double * [Fix];
        for (int ii = 0; ii < Fix; ii ++)
            layvaluesBkup [ii] = new double [dim];
        for (int jj = 0; jj < Fix; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                if (lay == 0 && jj == 0)
                {
                    layvaluesBkup [jj] [ii] = values [ii];
                }

                else
                {
                    layvaluesBkup [jj] [ii] = layvalues [jj] [ii];
                }

    }

    else
    if (varType == TVar :: Int)
    {
        ilayvaluesBkup = new long * [Fix];
        for (int ii = 0; ii < Fix; ii ++)
            ilayvaluesBkup [ii] = new long [dim];
        for (int jj = 0; jj < Fix; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                if (lay == 0 && jj == 0)
                {
                    ilayvaluesBkup [jj] [ii] = ivalues [ii];
                }

                else
                {
                    ilayvaluesBkup [jj] [ii] = ilayvalues [jj] [ii];
                }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::BackUp()@@@ClassCRHM.cpp>");
}
void ClassVar :: Restore ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::Restore()@@@ClassCRHM.cpp>");
    long Fix = lay;
    if (lay == 0)
    {
        Fix = 1;
    }

    if (varType == TVar :: Float)
    {
        for (int jj = 0; jj < Fix; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                if (lay == 0 && jj == 0)
                {
                    values [ii] = layvaluesBkup [jj] [ii];
                }

                else
                {
                    layvalues [jj] [ii] = layvaluesBkup [jj] [ii];
                }

        for (int ii = 0; ii < Fix; ++ ii)
            delete [] layvaluesBkup [ii];
        delete [] layvaluesBkup;
        layvaluesBkup = NULL;
    }

    else
    if (varType == TVar :: Int)
    {
        for (int jj = 0; jj < Fix; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                if (lay == 0 && jj == 0)
                {
                    ivalues [ii] = ilayvaluesBkup [jj] [ii];
                }

                else
                {
                    ilayvalues [jj] [ii] = ilayvaluesBkup [jj] [ii];
                }

        for (int ii = 0; ii < Fix; ++ ii)
            delete [] ilayvaluesBkup [ii];
        delete [] ilayvaluesBkup;
        ilayvaluesBkup = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::Restore()@@@ClassCRHM.cpp>");
}
void ClassVar :: ReadVar (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::ReadVar(void)@@@ClassCRHM.cpp>");
    if (FileData -> Times == NULL)
    {
        if (varType == TVar :: ReadF || varType == TVar :: Read)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii)
                    values [ii] = FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin];
            }

            else
            {
                bool exists = (Global :: DTindx / FileData -> ModN >= FileData -> IndxMin) && (Global :: DTindx / FileData -> ModN <= FileData -> IndxMax);
                long cnt0 = min < long > (cnt, dim);
                for (long ii = 0; ii < cnt0; ++ ii)
                    if (exists)
                    {
                        long hruvalue = Global :: HRU_OBS [HRU_OBS_indexed] [ii];
                        long index1 = offset + min < long > (hruvalue, cnt) - 1;
                        long index2 = Global :: DTindx / FileData -> ModN - FileData -> IndxMin;
                        values [ii] = FileData -> Data [index1] [index2];
                    }

                    else
                    {
                        values [ii] = xLimit;
                    }

            }

        }

        else
        if (varType == TVar :: ReadI)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii) {
                    ivalues [ii] = int (FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin] + 0.5);
                }
            }

            else
            {
                bool exists = (Global :: DTindx / FileData -> ModN >= FileData -> IndxMin) && (Global :: DTindx / FileData -> ModN <= FileData -> IndxMax);
                for (long ii = 0; ii < cnt; ++ ii) {
                    if (exists)
                    {
                        ivalues [ii] = int (FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin] + 0.5);
                    }

                    else
                    {
                        ivalues [ii] = lLimit;
                    }

                }
            }

        }

    }

    else
    if (FileData -> GoodInterval)
    {
        if (varType == TVar :: ReadF || varType == TVar :: Read)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii)
                    values [ii] = FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx];
            }

            else
            {
                for (long ii = 0; ii < cnt; ++ ii) {
                    values [ii] = FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx];
                }
            }

        }

        else
        if (varType == TVar :: ReadI)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii) {
                    ivalues [ii] = int (FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx] + 0.5);
                }
            }

            else
            {
                for (long ii = 0; ii < cnt; ++ ii) {
                    ivalues [ii] = int (FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx] + 0.5);
                }
            }

        }

    }

    else
    {
        double doN = dim;
        if (dimen == TDim :: NOBS)
        {
            doN = cnt;
        }

        if (varType == TVar :: ReadF || varType == TVar :: Read)
        {
            for (long ii = 0; ii < doN; ++ ii)
                values [ii] = xLimit;
        }

        else
        if (varType == TVar :: ReadI)
        {
            for (long ii = 0; ii < doN; ++ ii)
                ivalues [ii] = lLimit;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::ReadVar(void)@@@ClassCRHM.cpp>");
}
void ClassVar :: WriteVar (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::WriteVar(void)@@@ClassCRHM.cpp>");
    if (FileData -> Times == NULL)
    {
        if (varType == TVar :: ReadF || varType == TVar :: Read)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii)
                    FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin] = values [ii];
            }

            else
            {
                for (long ii = 0; ii < cnt; ++ ii)
                    FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin] = values [ii];
            }

        }

        else
        if (varType == TVar :: ReadI)
        {
            for (long ii = 0; ii < dim; ++ ii)
                FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin] = ivalues [ii];
        }

        else
        {
            for (long ii = 0; ii < cnt; ++ ii)
                FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [Global :: DTindx / FileData -> ModN - FileData -> IndxMin] = ivalues [ii];
        }

    }

    else
    if (FileData -> GoodInterval)
    {
        if (varType == TVar :: ReadF || varType == TVar :: Read)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii)
                    FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx] = values [ii];
            }

            else
            {
                for (long ii = 0; ii < cnt; ++ ii)
                    FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx] = values [ii];
            }

        }

        else
        if (varType == TVar :: ReadI)
        {
            if (dimen == TDim :: NHRU)
            {
                for (long ii = 0; ii < dim; ++ ii)
                    FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx] = (double) ivalues [ii];
            }

            else
            {
                for (long ii = 0; ii < cnt; ++ ii)
                    FileData -> Data [offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], cnt) - 1] [FileData -> TimeIndx] = (double) ivalues [ii];
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::WriteVar(void)@@@ClassCRHM.cpp>");
}
void ClassVar :: Intvl (void)
{
    double X;
    for (int ii = 0; ii < this -> dim; ++ ii) {
        for (int tt = 0; tt < Global :: Freq; ++ tt) {
            long t1 = min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt);
            long t2 = this -> offset;
            long t3 = (Global :: DTindx + tt) / FileData -> ModN;
            long t4 = FileData -> IndxMin;
            long firstindex = t2 + t1 - 1;
            if (firstindex < 0)
            {
                firstindex = 0;
            }

            X = FileData -> Data [firstindex] [t3 - t4];
            if (layvalues != NULL)
            {
                layvalues [tt] [ii] = X;
            }

            else
            {
                ilayvalues [tt] [ii] = int (X);
            }

        }
    }
}
;

void ClassVar :: LoopFirst (long dim_n)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::LoopFirst(long dim_n)@@@ClassCRHM.cpp>");
    Index_ = Global :: DTindx / FunctVar -> FileData -> ModN;
    (this ->* (this -> UserFunct_)) (dim_n);
InstrumentLogger::instance()->log_instrument_log("</ClassVar::LoopFirst(long dim_n)@@@ClassCRHM.cpp>");
}
void ClassVar :: LoopLast (long dim_n)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::LoopLast(long dim_n)@@@ClassCRHM.cpp>");
    Index_ = Global :: DTindx / FunctVar -> FileData -> ModN + FunctVar -> FileData -> Freq - 1;
    (this ->* (this -> UserFunct_)) (dim_n);
InstrumentLogger::instance()->log_instrument_log("</ClassVar::LoopLast(long dim_n)@@@ClassCRHM.cpp>");
}
void ClassVar :: LoopRange (long dim_n)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::LoopRange(long dim_n)@@@ClassCRHM.cpp>");
    Index_ = Global :: DTindx / FunctVar -> FileData -> ModN;
    do {
        (this ->* (this -> UserFunct_)) (dim_n);
    }
    while (++ Index_ % FunctVar -> FileData -> Freq != 0);
InstrumentLogger::instance()->log_instrument_log("</ClassVar::LoopRange(long dim_n)@@@ClassCRHM.cpp>");
}
void ClassVar :: Tot_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    values [dim_n] += X;
}
;

void ClassVar :: Pos_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt - 1)] [Index_ - FunctVar -> FileData -> IndxMin];
    if (X > 0.0)
    {
        values [dim_n] += X;
    }

}
;

void ClassVar :: Max_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    if (X > values [dim_n])
    {
        values [dim_n] = X;
    }

}
;

void ClassVar :: Min_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    if (X < values [dim_n])
    {
        values [dim_n] = X;
    }

}
;

void ClassVar :: Last_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    values [dim_n] = X;
}
;

void ClassVar :: First_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    values [dim_n] = X;
}
;

void ClassVar :: Avg_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    values [dim_n] += X / this -> FileData -> Freq;
}
;

void ClassVar :: Count_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    if (X > 0.0)
    {
        values [dim_n] += (double) 1.0 / this -> FileData -> Freq;
    }

}
;

void ClassVar :: Count0_ (long dim_n)
{
    double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [dim_n], FunctVar -> cnt) - 1] [Index_ - FunctVar -> FileData -> IndxMin];
    if (X == 0.0)
    {
        values [dim_n] += (double) 1.0 / this -> FileData -> Freq;
    }

}
;

void ClassVar :: Avg (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    long Count = 0;
    for (long ii = 0; ii < this -> dim; ++ ii)
        values [ii] = 0.0;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            long firstindex = FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1;
            long secondindex = Index - FunctVar -> FileData -> IndxMin;
            if (firstindex < 0)
            {
                firstindex = 0;
            }

            double X = FunctVar -> FileData -> Data [firstindex] [secondindex];
            values [ii] += X;
        }
        Count ++;
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
    for (long ii = 0; ii < this -> dim; ++ ii) {
        values [ii] = values [ii] / Count;
    }
}
;

void ClassVar :: Max (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    for (long ii = 0; ii < this -> dim; ++ ii)
        values [ii] = - 100000.0;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            if (X > values [ii])
            {
                values [ii] = X;
            }

        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Min (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    for (long ii = 0; ii < this -> dim; ++ ii)
        values [ii] = 100000.0;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            if (X < values [ii])
            {
                values [ii] = X;
            }

        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Dtot (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    for (long ii = 0; ii < this -> dim; ++ ii)
        values [ii] = 0.0;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            values [ii] += X;
        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Tot (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            values [ii] += X;
        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Last (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN + FunctVar -> FileData -> Freq - 1;
    for (long ii = 0; ii < this -> dim; ++ ii) {
        double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
        values [ii] = X;
    }
}
;

void ClassVar :: First (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    for (long ii = 0; ii < this -> dim; ++ ii) {
        double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
        values [ii] = X;
    }
}
;

void ClassVar :: Peak (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            if (X > values [ii])
            {
                values [ii] = X;
            }

        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Count (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    double Divisor = (double) FunctVar -> FileData -> ModN;
    if (this -> root != "")
    {
        Divisor = (double) this -> FileData -> Freq;
    }

    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            if (X > 0.0)
            {
                values [ii] += (double) 1.0 / Divisor;
            }

        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Count0 (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    double Divisor = (double) FunctVar -> FileData -> ModN;
    if (this -> root != "")
    {
        Divisor = (double) this -> FileData -> Freq;
    }

    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt) - 1] [Index - FunctVar -> FileData -> IndxMin];
            if (X == 0.0)
            {
                values [ii] += (double) 1.0 / Divisor;
            }

        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: Pos (void)
{
    long Index = Global :: DTindx / FunctVar -> FileData -> ModN;
    for (long ii = 0; ii < this -> dim; ++ ii)
        values [ii] = 0.0;
    do {
        for (long ii = 0; ii < this -> dim; ++ ii) {
            double X = FunctVar -> FileData -> Data [FunctVar -> offset + min < long > (Global :: HRU_OBS [HRU_OBS_indexed] [ii], FunctVar -> cnt - 1)] [Index - FunctVar -> FileData -> IndxMin];
            if (X > 0.0)
            {
                values [ii] += X;
            }

        }
    }
    while (++ Index % FunctVar -> FileData -> Freq != 0);
}
;

void ClassVar :: do_t (ClassModule * thisModule)
{
    for (int ii = 0; ii < this -> dim; ++ ii)
        values [ii] -= Global :: lapse_rate [ii] * (double) (Global :: hru_elev [ii] - Global :: OBS_ELEV [0] [ii]) / (double) 100.0;
}
;

void ClassVar :: do_t_Clim (ClassModule * thisModule)
{
    do_t (thisModule);
    for (int ii = 0; ii < this -> dim; ++ ii)
        values [ii] += Global :: Warming_t [ii];
}
;

void ClassVar :: do_ppt (ClassModule * thisModule)
{
    for (int ii = 0; ii < this -> dim; ++ ii) {
        values [ii] = values [ii] * ((double) 1.0 + (Global :: hru_elev [ii] - Global :: OBS_ELEV [1] [ii]) / (double) 100.0 * Global :: ppt_adj [ii]);
    }
}
;

void ClassVar :: do_p (ClassModule * thisModule)
{
    for (int ii = 0; ii < this -> dim; ++ ii) {
        values [ii] = FunctVar -> values [ii] * ((double) 1.0 + (Global :: hru_elev [ii] - Global :: OBS_ELEV [1] [ii]) / (double) 100.0 * Global :: ppt_adj [ii]);
    }
}
;

void ClassVar :: do_p_Clim (ClassModule * thisModule)
{
    do_p (thisModule);
    for (int ii = 0; ii < this -> dim; ++ ii) {
        values [ii] = values [ii] * Global :: Warming_p [ii];
    }
}
;

void ClassVar :: do_ppt_Clim (ClassModule * thisModule)
{
    do_ppt (thisModule);
    for (int ii = 0; ii < this -> dim; ++ ii) {
        values [ii] = values [ii] * Global :: Warming_p [ii];
    }
}
;

void ClassVar :: do_t_day (ClassModule * thisModule)
{
    for (int ii = 0; ii < this -> dim; ++ ii) {
        double Fix = (double) (Global :: lapse_rate [ii] * (Global :: hru_elev [ii] - Global :: OBS_ELEV [0] [ii]) / 100.0);
        for (int tt = 0; tt < Global :: Freq; ++ tt) {
            Global :: obs_t_obs [tt] [ii] = layvalues [tt] [ii];
            layvalues [tt] [ii] -= Fix;
            Global :: obs_t [tt] [ii] = layvalues [tt] [ii];
        }
    }
}
;

void ClassVar :: do_t_day_Clim (ClassModule * thisModule)
{
    do_t_day (thisModule);
    for (int ii = 0; ii < this -> dim; ++ ii) {
        for (int tt = 0; tt < Global :: Freq; ++ tt) {
            Global :: obs_t_obs [tt] [ii] = layvalues [tt] [ii];
            layvalues [tt] [ii] += Global :: Warming_t [ii];
            Global :: obs_t [tt] [ii] = layvalues [tt] [ii];
        }
    }
}
;

void ClassVar :: do_rh_day (ClassModule * thisModule)
{
    for (int ii = 0; ii < this -> dim; ++ ii) {
        for (int tt = 0; tt < Global :: Freq; ++ tt) {
            if (Global :: RH_VP_flag [ii])
            {
                Global :: obs_ea [tt] [ii] = (double) (Common :: estar (Global :: obs_t [tt] [ii]) * layvalues [tt] [ii] / 100.0);
                if (Global :: obs_t_obs [tt] [ii] > Global :: obs_t [tt] [ii])
                {
                    double New_es = (double) Common :: estar (Global :: obs_t [tt] [ii]);
                    if (Global :: obs_ea [tt] [ii] > New_es)
                    {
                        Global :: obs_ea [tt] [ii] = New_es;
                        layvalues [tt] [ii] = 100.0;
                    }

                    else
                    {
                        layvalues [tt] [ii] = (double) (Global :: obs_ea [tt] [ii] / New_es * 100.0);
                    }

                }

            }

            else
            {
                Global :: obs_ea [tt] [ii] = (double) (Common :: estar (Global :: obs_t [tt] [ii]) * layvalues [tt] [ii] / 100.0);
            }

        }
    }
}
;

void ClassVar :: do_rh_day_Clim (ClassModule * thisModule)
{
    do_rh_day (thisModule);
    for (int ii = 0; ii < this -> dim; ++ ii) {
        for (int tt = 0; tt < Global :: Freq; ++ tt) {
            if (Global :: RH_VP_flag2 [ii])
            {
                Global :: obs_ea [tt] [ii] = (double) (Common :: estar (Global :: obs_t [tt] [ii]) * layvalues [tt] [ii] / 100.0);
                if (Global :: obs_t_obs [tt] [ii] > Global :: obs_t [tt] [ii])
                {
                    double New_es = (double) Common :: estar (Global :: obs_t [tt] [ii]);
                    if (Global :: obs_ea [tt] [ii] > New_es)
                    {
                        Global :: obs_ea [tt] [ii] = New_es;
                        layvalues [tt] [ii] = 100.0;
                    }

                    else
                    {
                        layvalues [tt] [ii] = (double) (Global :: obs_ea [tt] [ii] / New_es * 100.0);
                    }

                }

            }

            else
            {
                Global :: obs_ea [tt] [ii] = (double) (Common :: estar (Global :: obs_t [tt] [ii]) * layvalues [tt] [ii] / 100.0);
            }

        }
    }
}
;

void ClassVar :: do_ea_day (ClassModule * thisModule)
{
    double New_es;
    for (int ii = 0; ii < this -> dim; ++ ii) {
        for (int tt = 0; tt < Global :: Freq; ++ tt) {
            Global :: obs_rh [tt] [ii] = (double) (layvalues [tt] [ii] / Common :: estar (Global :: obs_t_obs [tt] [ii]) * 100.0);
            New_es = (double) Common :: estar (Global :: obs_t [tt] [ii]);
            if (Global :: RH_VP_flag [ii])
            {
                if (Global :: obs_t_obs [tt] [ii] > Global :: obs_t [tt] [ii])
                {
                    if (layvalues [tt] [ii] > New_es)
                    {
                        layvalues [tt] [ii] = New_es;
                        Global :: obs_rh [tt] [ii] = 100.0;
                    }

                    else
                    {
                        Global :: obs_rh [tt] [ii] = (double) (layvalues [tt] [ii] / New_es * 100.0);
                    }

                }

            }

            else
            {
                layvalues [tt] [ii] = New_es * Global :: obs_rh [tt] [ii] / (double) 100.0;
                double X = layvalues [tt] [ii];
            }

        }
    }
}
;

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
ClassPar :: ClassPar (string module, string param, TDim dimen, string CommaText, string help, TVar varType, int Grpdim): module (module), basemodule (""), param (param), varType (varType), dimen (dimen), help (help), units (""), valstr (""), minVal (0), maxVal (0), Inhibit_share (0), values (NULL), ivalues (NULL), layvalues (NULL), ilayvalues (NULL), Identical (NULL), layvaluesBkup (NULL), ilayvaluesBkup (NULL), lay (1)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::ClassPar(string module, string param, TDim dimen, string CommaText, string help, TVar varType, int Grpdim): module (module), basemodule (""), param (param), varType (varType), dimen (dimen), help (help), units (""), valstr (""), minVal (0), maxVal (0), Inhibit_share (0), values (NULL), ivalues (NULL), layvalues (NULL), ilayvalues (NULL), Identical (NULL), layvaluesBkup (NULL), ilayvaluesBkup (NULL), lay (1)@@@ClassCRHM.cpp>");
    if (Grpdim == 0 && dimen >= TDim :: NHRU)
    {
        Grpdim = Global :: nhru;
    }

    if (dimen < TDim :: NHRU)
    {
        dim = getdim (dimen);
    }

    else
    {
        dim = Grpdim;
    }

    Strings = new TStringList ();
    Strings -> DelimitedText (CommaText);
    if (Strings -> Count == 0)
    {
        Strings -> Add ("");
    }

    if (dimen == TDim :: NHRU)
    {
        for (int ii = Strings -> Count; ii < dim; ++ ii) {
            Strings -> Add (Strings -> Strings [0] + std :: to_string (ii + 1));
        }
    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::ClassPar(string module, string param, TDim dimen, string CommaText, string help, TVar varType, int Grpdim): module (module), basemodule (""), param (param), varType (varType), dimen (dimen), help (help), units (""), valstr (""), minVal (0), maxVal (0), Inhibit_share (0), values (NULL), ivalues (NULL), layvalues (NULL), ilayvalues (NULL), Identical (NULL), layvaluesBkup (NULL), ilayvaluesBkup (NULL), lay (1)@@@ClassCRHM.cpp>");
}
void ClassPar :: ExpandShrink (long new_dim)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::ExpandShrink(long new_dim)@@@ClassCRHM.cpp>");
    if (varType == TVar :: Txt)
    {
        StringsBkup = new TStringList;
        StringsBkup -> Assign (Strings);
    }

    else
    if (varType == TVar :: Float)
    {
        layvaluesBkup = new double * [lay];
        for (int ii = 0; ii < lay; ii ++)
            layvaluesBkup [ii] = new double [dim];
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                layvaluesBkup [jj] [ii] = layvalues [jj] [ii];
    }

    else
    if (varType == TVar :: Int)
    {
        ilayvaluesBkup = new long * [lay];
        for (int ii = 0; ii < lay; ii ++)
            ilayvaluesBkup [ii] = new long [dim];
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                ilayvaluesBkup [jj] [ii] = ilayvalues [jj] [ii];
    }

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
        Strings -> Clear ();
    }

    long lay0 = lay;
    long dim0 = dim;
    dim = new_dim;
    if (dimen == TDim :: NDEFN)
    {
        lay = new_dim;
    }

    if (varType == TVar :: Float)
    {
        if (lay > 0)
        {
            layvalues = new double * [lay];
            for (int ii = 0; ii < lay; ii ++)
                layvalues [ii] = new double [dim];
            for (int jj = 0; jj < lay; ++ jj)
                for (int kk = 0; kk < dim; ++ kk)
                    layvalues [jj] [kk] = 0.0;
        }

        values = new double [dim];
        for (int kk = 0; kk < dim; ++ kk)
            values [kk] = 0.0;
    }

    else
    if (varType == TVar :: Int)
    {
        if (lay > 0)
        {
            ilayvalues = new long * [lay];
            for (int ii = 0; ii < lay; ii ++)
                ilayvalues [ii] = new long [dim];
            for (int jj = 0; jj < lay; ++ jj)
                for (int kk = 0; kk < dim; ++ kk)
                    ilayvalues [jj] [kk] = (int) 0.0;
        }

        ivalues = new long [dim];
        for (int kk = 0; kk < dim; ++ kk)
            ivalues [kk] = 0;
    }

    else
    if (varType == TVar :: Txt)
    {
        Strings -> Clear ();
    }

    if (varType == TVar :: Txt)
    {
        if (StringsBkup -> Count > 0)
        {
            for (int kk = 0; kk < dim; ++ kk)
                Strings -> Add (StringsBkup -> Strings [min < int > (kk, dim0 - 1)] + "");
            delete StringsBkup;
        }

        StringsBkup = NULL;
    }

    else
    if (varType == TVar :: Float)
    {
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                layvalues [jj] [ii] = layvaluesBkup [min < int > (jj, lay0 - 1)] [min < int > (ii, dim0 - 1)];
        for (int ii = 0; ii < lay0; ++ ii)
            delete [] layvaluesBkup [ii];
        delete [] layvaluesBkup;
        layvaluesBkup = NULL;
    }

    else
    if (varType == TVar :: Int)
    {
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                ilayvalues [jj] [ii] = ilayvaluesBkup [min < int > (jj, lay0 - 1)] [min < int > (ii, dim0 - 1)];
        for (int ii = 0; ii < lay0; ++ ii)
            delete [] ilayvaluesBkup [ii];
        delete [] ilayvaluesBkup;
        ilayvaluesBkup = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::ExpandShrink(long new_dim)@@@ClassCRHM.cpp>");
}
void ClassPar :: BackUp ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::BackUp()@@@ClassCRHM.cpp>");
    if (varType == TVar :: Txt)
    {
        StringsBkup = new TStringList;
        StringsBkup -> Assign (Strings);
    }

    else
    if (varType == TVar :: Float)
    {
        layvaluesBkup = new double * [lay];
        for (int ii = 0; ii < lay; ii ++)
            layvaluesBkup [ii] = new double [dim];
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                layvaluesBkup [jj] [ii] = layvalues [jj] [ii];
    }

    else
    if (varType == TVar :: Int)
    {
        ilayvaluesBkup = new long * [lay];
        for (int ii = 0; ii < lay; ii ++)
            ilayvaluesBkup [ii] = new long [dim];
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                ilayvaluesBkup [jj] [ii] = ilayvalues [jj] [ii];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::BackUp()@@@ClassCRHM.cpp>");
}
void ClassPar :: Restore ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::Restore()@@@ClassCRHM.cpp>");
    if (varType == TVar :: Txt)
    {
        Strings -> Assign (StringsBkup);
        delete StringsBkup;
        StringsBkup = NULL;
    }

    else
    if (varType == TVar :: Float)
    {
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                layvalues [jj] [ii] = layvaluesBkup [jj] [ii];
        for (int ii = 0; ii < lay; ++ ii)
            delete [] layvaluesBkup [ii];
        delete [] layvaluesBkup;
        layvaluesBkup = NULL;
    }

    else
    if (varType == TVar :: Int)
    {
        for (int jj = 0; jj < lay; jj ++)
            for (int ii = 0; ii < dim; ii ++)
                ilayvalues [jj] [ii] = ilayvaluesBkup [jj] [ii];
        for (int ii = 0; ii < lay; ++ ii)
            delete [] ilayvaluesBkup [ii];
        delete [] ilayvaluesBkup;
        ilayvaluesBkup = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Restore()@@@ClassCRHM.cpp>");
}
ClassPar :: ClassPar (string module, string param, TDim dimen, string valstr, double minVal, double maxVal, string help, string units, TVar varType, int defdim, int Grpdim): module (module), basemodule (""), param (param), varType (varType), dimen (dimen), valstr (valstr), minVal (minVal), maxVal (maxVal), Inhibit_share (0), help (help), units (units), values (NULL), ivalues (NULL), layvalues (NULL), ilayvalues (NULL), Strings (NULL), layvaluesBkup (NULL), ilayvaluesBkup (NULL), Identical (NULL), StringsBkup (NULL), lay (1)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::ClassPar(string module, string param, TDim dimen, string valstr, double minVal, double maxVal, string help, string units, TVar varType, int defdim, int Grpdim): module (module), basemodule (""), param (param), varType (varType), dimen (dimen), valstr (valstr), minVal (minVal), maxVal (maxVal), Inhibit_share (0), help (help), units (units), values (NULL), ivalues (NULL), layvalues (NULL), ilayvalues (NULL), Strings (NULL), layvaluesBkup (NULL), ilayvaluesBkup (NULL), Identical (NULL), StringsBkup (NULL), lay (1)@@@ClassCRHM.cpp>");
    if (Grpdim == 0 && dimen >= TDim :: NHRU)
    {
        Grpdim = Global :: nhru;
    }

    if (dimen == TDim :: NLAY)
    {
        lay = Global :: nlay;
        dim = Grpdim;
    }

    else
    if (dimen == TDim :: NDEF)
    {
        lay = defdim;
        dim = 1;
    }

    else
    if (dimen == TDim :: NDEFNZ)
    {
        lay = defdim;
        dim = 1;
    }

    else
    if (dimen == TDim :: NDEFN)
    {
        lay = defdim;
        dim = Grpdim;
    }

    else
    if (dimen < TDim :: NHRU)
    {
        dim = getdim (dimen);
        lay = 1;
    }

    else
    {
        dim = Grpdim;
        lay = 1;
    }

    try {
        if (varType == TVar :: Float)
        {
            layvalues = new double * [lay];
            for (int ii = 0; ii < lay; ii ++)
                layvalues [ii] = new double [dim];
            values = layvalues [0];
        }

        else
        if (varType == TVar :: Int)
        {
            ilayvalues = new long * [lay];
            for (int ii = 0; ii < lay; ii ++)
                ilayvalues [ii] = new long [dim];
            ivalues = ilayvalues [0];
        }

    }
    catch (std :: bad_alloc) {
        CRHMException Except ("Could not allocate in ClassPar.", TExcept :: TERMINATE);
        LogError (Except);
        throw CRHMException (Except);
    }
InstrumentLogger::instance()->log_instrument_log("</ClassPar::ClassPar(string module, string param, TDim dimen, string valstr, double minVal, double maxVal, string help, string units, TVar varType, int defdim, int Grpdim): module (module), basemodule (""), param (param), varType (varType), dimen (dimen), valstr (valstr), minVal (minVal), maxVal (maxVal), Inhibit_share (0), help (help), units (units), values (NULL), ivalues (NULL), layvalues (NULL), ilayvalues (NULL), Strings (NULL), layvaluesBkup (NULL), ilayvaluesBkup (NULL), Identical (NULL), StringsBkup (NULL), lay (1)@@@ClassCRHM.cpp>");
}
ClassPar :: ClassPar (ClassPar & p)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::ClassPar(ClassPar & p)@@@ClassCRHM.cpp>");
    module = string (p.module);
    basemodule = string (p.basemodule);
    param = string (p.param);
    units = string (p.units);
    help = string (p.help);
    varType = p.varType;
    dimen = p.dimen;
    dim = p.dim;
    lay = p.lay;
    variation_set = p.variation_set;
    visibility = p.visibility;
    Inhibit_share = p.Inhibit_share;
    valstr = string (p.valstr);
    minVal = p.minVal;
    maxVal = p.maxVal;
    layvaluesBkup = NULL;
    ilayvaluesBkup = NULL;
    Strings = NULL;
    ivalues = NULL;
    values = NULL;
    ilayvalues = NULL;
    layvalues = NULL;
    Identical = NULL;
    try {
        if (varType == TVar :: Float)
        {
            layvalues = new double * [lay];
            for (int ii = 0; ii < lay; ii ++) {
                layvalues [ii] = new double [dim];
            }
            values = layvalues [0];
        }

        else
        if (varType == TVar :: Int)
        {
            ilayvalues = new long * [lay];
            for (int ii = 0; ii < lay; ii ++) {
                ilayvalues [ii] = new long [dim];
            }
            ivalues = ilayvalues [0];
        }

        else
        if (varType == TVar :: Txt)
        {
            Strings = new TStringList;
        }

    }
    catch (std :: bad_alloc) {
        CRHMException Except ("Could not allocate in ClassPar.", TExcept :: TERMINATE);
        LogError (Except);
        throw CRHMException (Except);
    }
    if (varType == TVar :: Float)
    {
        for (int jj = 0; jj < lay; jj ++) {
            for (int ii = 0; ii < dim; ii ++) {
                layvalues [jj] [ii] = p.layvalues [jj] [ii];
            }
        }
    }

    else
    if (varType == TVar :: Int)
    {
        if (ilayvalues != NULL)
        {
            for (int jj = 0; jj < lay; jj ++) {
                for (int ii = 0; ii < dim; ii ++) {
                    ilayvalues [jj] [ii] = p.ilayvalues [jj] [ii];
                }
            }
        }

        else
        {
            CRHMException Except ("ilayvalues array is null allocation must have failed.", TExcept :: TERMINATE);
            LogError (Except);
            throw CRHMException (Except);
        }

    }

    else
    if (varType == TVar :: Txt)
    {
        Strings -> Assign (p.Strings);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::ClassPar(ClassPar & p)@@@ClassCRHM.cpp>");
}
bool ClassPar :: Same (ClassPar & p)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
    if (varType == p.varType && dim == p.dim && param == p.param)
    {
        if (Inhibit_share != 0 || p.Inhibit_share != 0)
        {
            if (Global :: GroupCntTrk)
            {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                return (false);
            }

            else
            {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                return (true);
            }

        }

        if (dim == p.dim)
        {
            if (varType == TVar :: Txt)
            {
                if (! Strings && ! p.Strings)
                {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                    return true;
                }

                if (Strings != NULL && (Strings -> Count != p.Strings -> Count))
                {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                    return (false);
                }

                if (Strings == NULL)
                {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                    return false;
                }

                else
                {
                    for (int ii = 0; ii < Strings -> Count; ++ ii) {
                        if (Strings -> Strings [ii] != p.Strings -> Strings [ii])
                        {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                            return (false);
                        }

                    }
                }

            }

            else
            {
                for (int jj = 0; jj < lay; ++ jj)
                    for (int ii = 0; ii < dim; ++ ii)
                        if (varType == TVar :: Float)
                        {
                            if (layvalues [jj] [ii] != p.layvalues [jj] [ii])
                            {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                                return (false);
                            }

                        }

                        else
                        if (varType == TVar :: Int)
                        {
                            if (ilayvalues [jj] [ii] != p.ilayvalues [jj] [ii])
                            {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
                                return (false);
                            }

                        }

            }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
            return (true);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
    return (false);
InstrumentLogger::instance()->log_instrument_log("</ClassPar::Same(ClassPar & p)@@@ClassCRHM.cpp>");
}
void ClassPar :: Change (ClassPar & p)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::Change(ClassPar & p)@@@ClassCRHM.cpp>");
    if (this == & p)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Change(ClassPar & p)@@@ClassCRHM.cpp>");
        return;
    }

    if (varType == TVar :: Txt)
    {
        Strings -> Assign (p.Strings);
        while (Strings -> Count < dim && Strings -> Count > 0) Strings -> Add (Strings -> Strings [Strings -> Count - 1] + "");
    }

    else
    {
        bool Bang = valstr.find ("!") != string :: npos;
        for (int jj = 0; jj < lay; ++ jj) {
            long jj0 = min < long > (jj, p.lay - 1);
            for (int ii = 0; ii < dim; ++ ii) {
                long ii0 = min < long > (ii, p.dim - 1);
                if (Bang && ii0 < ii)
                {
                    if (varType == TVar :: Float)
                    {
                        layvalues [jj] [ii] = layvalues [jj] [ii - 1] + 1;
                    }

                    else
                    if (varType == TVar :: Int)
                    {
                        ilayvalues [jj] [ii] = ilayvalues [jj] [ii - 1] + 1;
                    }

                }

                else
                {
                    if (varType == TVar :: Float)
                    {
                        layvalues [jj] [ii] = p.layvalues [jj0] [ii0];
                    }

                    else
                    if (varType == TVar :: Int)
                    {
                        ilayvalues [jj] [ii] = p.ilayvalues [jj0] [ii0];
                    }

                }

            }
        }
    }

InstrumentLogger::instance()->log_instrument_log("</ClassPar::Change(ClassPar & p)@@@ClassCRHM.cpp>");
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

            if (Global :: OurModulesList -> IndexOf (smodule.c_str ()) == - 1)
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
            jj = Global :: OldModuleName -> IndexOf (module.c_str ());
        }

        if (jj > - 1)
        {
            string s = Global :: NewModuleName -> Strings [jj] + "";
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
ClassVar :: ClassVar (string module, string name, TDim dimen, string help, string units, TVar varType, bool PointPlot, int Grpdim, int defdim): module (module), name (name), DLLName (""), root (""), varType (varType), lay (0), nfreq (false), optional (false), StatVar (false), InGroup (0), visibility (TVISIBLE :: USUAL), FunKind (TFun :: FOBS), help (help), units (units), layvalues (NULL), ilayvalues (NULL), dim (0), dimMax (0), values (NULL), ivalues (NULL), offset (0), cnt (0), FileData (NULL), HRU_OBS_indexed (0), UserFunct (NULL), FunctVar (NULL), CustomFunct (NULL), No_ReadVar (0), PointPlot (PointPlot), TchrtOpt (0), dimen (dimen)
{
InstrumentLogger::instance()->log_instrument_log("<(string module, string name, TDim dimen, string help, string units, TVar varType, bool PointPlot, int Grpdim, int defdim): module (module), name (name), DLLName (""), root (""), varType (varType), lay (0), nfreq (false), optional (false), StatVar (false), InGroup (0), visibility (TVISIBLE :: USUAL), FunKind (TFun :: FOBS), help (help), units (units), layvalues (NULL), ilayvalues (NULL), dim (0), dimMax (0), values (NULL), ivalues (NULL), offset (0), cnt (0), FileData (NULL), HRU_OBS_indexed (0), UserFunct (NULL), FunctVar (NULL), CustomFunct (NULL), No_ReadVar (0), PointPlot (PointPlot), TchrtOpt (0), dimen (dimen)@@@ClassCRHM.cpp>");
    if (Grpdim == 0)
    {
        Grpdim = Global :: nhru;
    }

    if (dimen == TDim :: NLAY)
    {
        lay = Global :: nlay;
    }

    else
    if (dimen == TDim :: NFREQ)
    {
        lay = Global :: Freq;
        nfreq = true;
    }

    else
    if (dimen == TDim :: NDEF)
    {
        lay = defdim;
        dim = 1;
    }

    else
    if (dimen == TDim :: NDEFN)
    {
        lay = defdim;
        dim = Grpdim;
    }

    else
    if (dimen == TDim :: NREB)
    {
        lay = Grpdim;
    }

    else
    {
        lay = 0;
    }

    if (dimen == TDim :: NOBS)
    {
        dim = Global :: nobs;
    }

    else
    {
        dim = Grpdim;
    }

    try {
        if (varType == TVar :: Float)
        {
            if (lay > 0)
            {
                layvalues = new double * [lay];
                if (! values)
                {
                    values = new double [dim];
                }

                if (dimen != TDim :: NREB)
                {
                    for (int ii = 0; ii < lay; ii ++)
                        layvalues [ii] = new double [dim];
                    values = layvalues [0];
                    for (int jj = 0; jj < lay; ++ jj)
                        for (int kk = 0; kk < dim; ++ kk)
                            layvalues [jj] [kk] = 0.0;
                }

            }

            if (lay == 0 || dimen == TDim :: NREB)
            {
                values = new double [dim];
                for (int kk = 0; kk < dim; ++ kk)
                    values [kk] = 0.0;
            }

        }

        else
        if (varType == TVar :: Int)
        {
            if (lay > 0)
            {
                ilayvalues = new long * [lay];
                if (dimen != TDim :: NREB)
                {
                    for (int ii = 0; ii < lay; ii ++)
                        ilayvalues [ii] = new long [dim];
                    ivalues = ilayvalues [0];
                    for (int jj = 0; jj < lay; ++ jj)
                        for (int kk = 0; kk < dim; ++ kk)
                            ilayvalues [jj] [kk] = (int) 0.0;
                }

            }

            if (lay == 0 || dimen == TDim :: NREB)
            {
                ivalues = new long [dim];
                for (int kk = 0; kk < dim; ++ kk)
                    ivalues [kk] = 0;
            }

        }

    }
    catch (std :: bad_alloc) {
        CRHMException Except ("Could not allocate in ClassVar.", TExcept :: TERMINATE);
        LogError (Except);
        throw CRHMException (Except);
    }
InstrumentLogger::instance()->log_instrument_log("</(string module, string name, TDim dimen, string help, string units, TVar varType, bool PointPlot, int Grpdim, int defdim): module (module), name (name), DLLName (""), root (""), varType (varType), lay (0), nfreq (false), optional (false), StatVar (false), InGroup (0), visibility (TVISIBLE :: USUAL), FunKind (TFun :: FOBS), help (help), units (units), layvalues (NULL), ilayvalues (NULL), dim (0), dimMax (0), values (NULL), ivalues (NULL), offset (0), cnt (0), FileData (NULL), HRU_OBS_indexed (0), UserFunct (NULL), FunctVar (NULL), CustomFunct (NULL), No_ReadVar (0), PointPlot (PointPlot), TchrtOpt (0), dimen (dimen)@@@ClassCRHM.cpp>");
}
ClassVar :: ClassVar (string module, string name, long dim, string help, string units, TVar varType, bool PointPlot): module (module), name (name), DLLName (""), root (""), varType (varType), dim (dim), dimMax (0), lay (0), nfreq (false), optional (false), StatVar (false), InGroup (0), visibility (TVISIBLE :: USUAL), FunKind (TFun :: FOBS), help (help), units (units), layvalues (NULL), ilayvalues (NULL), values (NULL), ivalues (NULL), offset (0), cnt (0), FileData (NULL), HRU_OBS_indexed (0), UserFunct (NULL), FunctVar (NULL), CustomFunct (NULL), No_ReadVar (0), PointPlot (PointPlot), TchrtOpt (0), dimen (TDim :: NHRU)
{
InstrumentLogger::instance()->log_instrument_log("<(string module, string name, long dim, string help, string units, TVar varType, bool PointPlot): module (module), name (name), DLLName (""), root (""), varType (varType), dim (dim), dimMax (0), lay (0), nfreq (false), optional (false), StatVar (false), InGroup (0), visibility (TVISIBLE :: USUAL), FunKind (TFun :: FOBS), help (help), units (units), layvalues (NULL), ilayvalues (NULL), values (NULL), ivalues (NULL), offset (0), cnt (0), FileData (NULL), HRU_OBS_indexed (0), UserFunct (NULL), FunctVar (NULL), CustomFunct (NULL), No_ReadVar (0), PointPlot (PointPlot), TchrtOpt (0), dimen (TDim :: NHRU)@@@ClassCRHM.cpp>");
    try {
        if (varType == TVar :: Float)
        {
            values = new double [dim];
        }

        else
        if (varType == TVar :: Int)
        {
            ivalues = new long [dim];
        }

    }
    catch (std :: bad_alloc) {
        CRHMException Except ("Could not allocate in ClassVar.", TExcept :: TERMINATE);
        LogError (Except);
        throw CRHMException (Except);
    }
InstrumentLogger::instance()->log_instrument_log("</(string module, string name, long dim, string help, string units, TVar varType, bool PointPlot): module (module), name (name), DLLName (""), root (""), varType (varType), dim (dim), dimMax (0), lay (0), nfreq (false), optional (false), StatVar (false), InGroup (0), visibility (TVISIBLE :: USUAL), FunKind (TFun :: FOBS), help (help), units (units), layvalues (NULL), ilayvalues (NULL), values (NULL), ivalues (NULL), offset (0), cnt (0), FileData (NULL), HRU_OBS_indexed (0), UserFunct (NULL), FunctVar (NULL), CustomFunct (NULL), No_ReadVar (0), PointPlot (PointPlot), TchrtOpt (0), dimen (TDim :: NHRU)@@@ClassCRHM.cpp>");
}
void ClassVar :: ReleaseM (bool Keep)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::ReleaseM(bool Keep)@@@ClassCRHM.cpp>");
    if (! values && ! ivalues)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassVar::ReleaseM(bool Keep)@@@ClassCRHM.cpp>");
        return;
    }

    if (varType == TVar :: Float || varType == TVar :: ReadF)
    {
        if (lay > 0)
        {
            if (dimen != TDim :: NREB)
            {
                values = NULL;
            }

            if (dimen != TDim :: NREB)
            {
                for (int ii = 0; ii < lay; ++ ii)
                    delete [] layvalues [ii];
            }

            delete [] layvalues;
            layvalues = NULL;
        }

        if (! Keep && values != NULL)
        {
            delete [] values;
            values = NULL;
        }

    }

    else
    if (varType == TVar :: Int || varType == TVar :: ReadI)
    {
        if (lay > 0)
        {
            if (dimen != TDim :: NREB)
            {
                ivalues = NULL;
            }

            if (dimen != TDim :: NREB)
            {
                for (int ii = 0; ii < lay; ++ ii)
                    delete [] ilayvalues [ii];
            }

            delete [] ilayvalues;
            ilayvalues = NULL;
        }

        if (! Keep && ivalues != NULL)
        {
            delete [] ivalues;
            ivalues = NULL;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::ReleaseM(bool Keep)@@@ClassCRHM.cpp>");
}
ClassVar :: ClassVar (const ClassVar & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::ClassVar(const ClassVar & Cl)@@@ClassCRHM.cpp>");
    module = Cl.module;
    root = Cl.root;
    name = Cl.name;
    help = Cl.help;
    units = Cl.units;
    dim = Cl.dim;
    dimMax = Cl.dimMax;
    variation_set = Cl.variation_set;
    dimen = Cl.dimen;
    lay = Cl.lay;
    varType = Cl.varType;
    visibility = Cl.visibility;
    optional = Cl.optional;
    PointPlot = Cl.PointPlot;
    TchrtOpt = Cl.TchrtOpt;
    VarFunct = Cl.VarFunct;
    StatVar = Cl.StatVar;
    InGroup = Cl.InGroup;
    nfreq = Cl.nfreq;
    FunKind = Cl.FunKind;
    ivalues = NULL;
    ilayvalues = NULL;
    layvalues = NULL;
    offset = Cl.offset;
    cnt = Cl.cnt;
    if (Cl.FileData)
    {
        FileData = new ClassData (* Cl.FileData);
    }

    else
    {
        FileData = NULL;
    }

    HRU_OBS_indexed = Cl.HRU_OBS_indexed;
    UserFunct = Cl.UserFunct;
    FunctVar = Cl.FunctVar;
    CustomFunct = Cl.CustomFunct;
    CustomFunctName = Cl.CustomFunctName;
    No_ReadVar = Cl.No_ReadVar;
    if (lay > 0)
    {
        layvalues = new double * [lay];
        if (dimen != TDim :: NREB)
        {
            for (int ii = 0; ii < lay; ii ++)
                layvalues [ii] = new double [dim];
            values = layvalues [0];
            for (int jj = 0; jj < lay; ++ jj)
                for (int kk = 0; kk < dim; ++ kk)
                    layvalues [jj] [kk] = 0.0;
        }

    }

    if (lay == 0 || dimen == TDim :: NREB)
    {
        varType = TVar :: Float;
        values = new double [dim];
        ivalues = NULL;
        for (int kk = 0; kk < dim; ++ kk)
            values [kk] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassVar::ClassVar(const ClassVar & Cl)@@@ClassCRHM.cpp>");
}
ClassVar & ClassVar :: operator = (const ClassVar & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::operator=(const ClassVar & Cl)@@@ClassCRHM.cpp>");
    if (this == & Cl)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassVar::operator=(const ClassVar & Cl)@@@ClassCRHM.cpp>");
        return * this;
    }

    module = Cl.module;
    root = Cl.root;
    name = Cl.name;
    help = Cl.help;
    units = Cl.units;
    dim = Cl.dim;
    dimMax = Cl.dimMax;
    variation_set = Cl.variation_set;
    dimen = Cl.dimen;
    lay = 0;
    varType = Cl.varType;
    visibility = Cl.visibility;
    optional = Cl.optional;
    PointPlot = Cl.PointPlot;
    TchrtOpt = Cl.TchrtOpt;
    VarFunct = Cl.VarFunct;
    StatVar = Cl.StatVar;
    InGroup = Cl.InGroup;
    nfreq = Cl.nfreq;
    FunKind = Cl.FunKind;
    ivalues = NULL;
    values = NULL;
    ilayvalues = NULL;
    layvalues = NULL;
    offset = Cl.offset;
    cnt = Cl.cnt;
    FileData = Cl.FileData;
    HRU_OBS_indexed = Cl.HRU_OBS_indexed;
    UserFunct = Cl.UserFunct;
    FunctVar = Cl.FunctVar;
    CustomFunct = Cl.CustomFunct;
    CustomFunctName = Cl.CustomFunctName;
    No_ReadVar = Cl.No_ReadVar;

InstrumentLogger::instance()->log_instrument_log("</ClassVar::operator=(const ClassVar & Cl)@@@ClassCRHM.cpp>");
    return * this;
InstrumentLogger::instance()->log_instrument_log("</ClassVar::operator=(const ClassVar & Cl)@@@ClassCRHM.cpp>");
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
double ClassData :: Encode24 (int D [])
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::Encode24(int D [])@@@ClassCRHM.cpp>");
    try {
        if (D [3] == 24)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassCRHM.cpp>");
            return StandardConverterUtility :: EncodeDateTime (D [0], D [1], D [2], 0, D [4]) + 1;
        }

        else
        {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassCRHM.cpp>");
            return StandardConverterUtility :: EncodeDateTime (D [0], D [1], D [2], D [3], D [4]);
        }

    }
    catch (...) {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassCRHM.cpp>");
        return 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassData::Encode24(int D [])@@@ClassCRHM.cpp>");
}
long ClassData :: Veto_Freq (long Freq)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
    const long OK_Values [14] = {1, 2, 3, 4, 6, 8, 12, 24, 48, 72, 96, 144, 192, 288};
    if (Freq <= 1)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
        return 1;
    }

    if (Freq >= OK_Values [13])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
        return OK_Values [13];
    }

    for (int ii = 1; ii < 14; ++ ii) {
        if (Freq <= OK_Values [ii])
        {
            if ((Freq - OK_Values [ii - 1]) < (OK_Values [ii] - Freq))
            {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
                return OK_Values [ii - 1];
            }

            else
            {

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
                return OK_Values [ii];
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
    return (- 1);
InstrumentLogger::instance()->log_instrument_log("</ClassData::Veto_Freq(long Freq)@@@ClassCRHM.cpp>");
}
bool ClassData :: DataReadFile (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
    ifstream DataFile;
    ifstream :: pos_type Here, Here2;
    string Header, Var, Comment;
    istringstream instr;
    bool DecimalTime;
    FirstFile = ! Global :: DTstart;
    int D [5];
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
        DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
        return false;
    }

    getline (DataFile, Description);
    HdrLen = 1;
    myMacro = new Classmacro (this);
    while (! DataFile.eof ()) {
        char c = DataFile.peek ();
        if (DataFile.fail ())
        {
            DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
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
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
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
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
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
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
                return false;
            }

            if (Global :: DTstart != 0.0 && Dt1 >= Global :: DTend)
            {
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
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
                DataFile.close ();

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
                return false;
            }

            else
            if (Cols > DataCnt)
            {
            }

            char c = DataFile.peek ();
            if (DataFile.eof ())
            {
                DataFile.clear ();
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
                if (IndxMin == 0)
                {
                    IndxMin = (long) ((Dt1 - floor (Dt1)) / Interval - 1);
                }

            }

            DataFile.seekg (0, ios_base :: end);
            ifstream :: pos_type Back = DataFile.tellg ();
            char c;
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
                string S;
                LineError = true;
                break;
            }

            for (int ii = 0; ii < DataCnt; ++ ii) {
                char c;
                while (c = DataFile.peek (), c == ' ' || c == '\t') DataFile.get ();
                if (DataFile.peek () == '\n')
                {
                    if (! SparseFlag)
                    {
                    }

                    if (FirstFile)
                    {
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

InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</ClassData::DataReadFile(void)@@@ClassCRHM.cpp>");
}
ClassData :: ~ClassData ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::~ClassData()@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</ClassData::~ClassData()@@@ClassCRHM.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</ClassData::~ClassData()@@@ClassCRHM.cpp>");
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
void Classfilter :: fixup (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::fixup(void)@@@ClassCRHM.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</Classfilter::fixup(void)@@@ClassCRHM.cpp>");
}
void Classfilter :: readargs ()
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::readargs()@@@ClassCRHM.cpp>");
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
    while (ee = args.find (','), ee > 0) args [ee] = ' ';
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

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
                return;
            }

            if ((itVar = Global :: MapVars.find ("obs " + V)) != Global :: MapVars.end ())
            {
                thisVar = (* itVar).second;
                if (thisVar -> varType < TVar :: Read)
                {
                    error ("not observation variable");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
                    return;
                }

            }

            else
            {
                error ("unknown variable");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
        return;
    }

    if (Cnt > argtypes.length ())
    {
        error ("too many arguments");

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
                return;
            }

        }

        thisVar = declread ("obs", ToVar, ObsCnt, TotalCnt, MyObs, Comment);
        DataIndx [Vs - 1] = TotalCnt;
        DataObsCnt [Vs - 1] = ObsCnt;
        thisVar -> review_HRU_OBS ();
    }

InstrumentLogger::instance()->log_instrument_log("</Classfilter::readargs()@@@ClassCRHM.cpp>");
}
Classfilter :: Classfilter (ClassData * MyObs, string ToVar, string args, string argtypes): MyObs (MyObs), ToVar (ToVar), args (args), argtypes (argtypes), Vs (0), Cs (0), Error (0), ObsCnt (0), TotalCnt (0), FirstTime (true)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::Classfilter(ClassData * MyObs, string ToVar, string args, string argtypes): MyObs (MyObs), ToVar (ToVar), args (args), argtypes (argtypes), Vs (0), Cs (0), Error (0), ObsCnt (0), TotalCnt (0), FirstTime (true)@@@ClassCRHM.cpp>");
    for (unsigned int ii = 1; ii < argtypes.length () + 1; ++ ii) {
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
        for (int ii = 0; ii < Vs; ++ ii)
            Data [ii] = NULL;
        DataIndx = new long [Vs];
        DataObsCnt = new long [Vs];
    }

    if (Cs > 0)
    {
        Constants = new double [Cs];
    }

InstrumentLogger::instance()->log_instrument_log("</Classfilter::Classfilter(ClassData * MyObs, string ToVar, string args, string argtypes): MyObs (MyObs), ToVar (ToVar), args (args), argtypes (argtypes), Vs (0), Cs (0), Error (0), ObsCnt (0), TotalCnt (0), FirstTime (true)@@@ClassCRHM.cpp>");
}
void Classfilter :: doFunctions (long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::doFunctions(long Line)@@@ClassCRHM.cpp>");
    for (int jj = 0; jj < ObsCnt; ++ jj)
        doFunc (jj, Line);
InstrumentLogger::instance()->log_instrument_log("</Classfilter::doFunctions(long Line)@@@ClassCRHM.cpp>");
}
Classfilter :: ~Classfilter ()
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::~Classfilter()@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</Classfilter::~Classfilter()@@@ClassCRHM.cpp>");
}
void Classfilter :: error (string Mess)
{
InstrumentLogger::instance()->log_instrument_log("<Classfilter::error(string Mess)@@@ClassCRHM.cpp>");
    string Mess2 = string (Mess);
    string F = string (string ("\"") + typeid (* this).name ());
    CRHMException Except (Mess2.c_str (), TExcept :: ERR);
    LogError (Except);
    Error = true;
InstrumentLogger::instance()->log_instrument_log("</Classfilter::error(string Mess)@@@ClassCRHM.cpp>");
}
void Classmacro :: addfilter (string Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classmacro::addfilter(string Line)@@@ClassCRHM.cpp>");
    Classfilter * NewFilter;
    string S = Line.substr (1, Common :: trim (Line).length ());
    if (Line.substr (1, 1) == "$")
    {

InstrumentLogger::instance()->log_instrument_log("</Classmacro::addfilter(string Line)@@@ClassCRHM.cpp>");
        return;
    }

    long bb = S.find ('(');
    long ee;
    ee = S.find_first_of (" \t");
    string ToVar = "";
    if (bb > ee)
    {
        ToVar = S.substr (0, ee);
    }

    else
    {
        ee = 1;
    }

    S = S.substr (ee);
    S = Common :: trim (S);
    ee = S.find ('(');
    string Filter = S.substr (0, ee);
    string FilterStuff = S.substr (ee);
    FilterStuff = Common :: trim (FilterStuff);
    if (ToVar.empty ())
    {
        if (Filter == "Sim")
        {
            NewFilter = (Classfilter *) new ClassSim (File, ToVar, FilterStuff);
        }

        else
        if (Filter == "ForceInterval")
        {
            NewFilter = (Classfilter *) new ClassForce (File, ToVar, FilterStuff);
        }

        else
        if (Filter == "TimeShift")
        {
            NewFilter = (Classfilter *) new ClassTimeshift (File, ToVar, FilterStuff);
        }

        else
        {
            string Mess = "Filter: '" + Filter + " has no 'to variable'";

InstrumentLogger::instance()->log_instrument_log("</Classmacro::addfilter(string Line)@@@ClassCRHM.cpp>");
            return;
        }

    }

    else
    if (Filter == "missing")
    {
        NewFilter = (Classfilter *) new ClassMissing (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "missing0")
    {
        NewFilter = (Classfilter *) new ClassMissing0 (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "missingC")
    {
        NewFilter = (Classfilter *) new ClassMissingC (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "missingFlag")
    {
        NewFilter = (Classfilter *) new ClassMissingFlag (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "missingFlagAfter")
    {
        NewFilter = (Classfilter *) new ClassMissingFlagAfter (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "missingrepl")
    {
        NewFilter = (Classfilter *) new ClassMissingrepl (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "missinginter")
    {
        NewFilter = (Classfilter *) new ClassMissingInter (File, ToVar, FilterStuff);
        ++ Interpolation;
    }

    else
    if (Filter == "ea")
    {
        NewFilter = (Classfilter *) new Classea (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "rh")
    {
        NewFilter = (Classfilter *) new Classrh (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "RH_WtoI")
    {
        NewFilter = (Classfilter *) new ClassRH_WtoI (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "add")
    {
        NewFilter = (Classfilter *) new Classadd (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "sub")
    {
        NewFilter = (Classfilter *) new Classsub (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "mul")
    {
        NewFilter = (Classfilter *) new Classmul (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "div")
    {
        NewFilter = (Classfilter *) new Classdiv (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "addV")
    {
        NewFilter = (Classfilter *) new ClassaddV (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "subV")
    {
        NewFilter = (Classfilter *) new ClasssubV (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "mulV")
    {
        NewFilter = (Classfilter *) new ClassmulV (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "divV")
    {
        NewFilter = (Classfilter *) new ClassdivV (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "refwind")
    {
        NewFilter = (Classfilter *) new Classrefwind (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "const")
    {
        NewFilter = (Classfilter *) new Classconst (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "sine")
    {
        NewFilter = (Classfilter *) new Classsin (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "sin")
    {
        NewFilter = (Classfilter *) new Classsin (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "cos")
    {
        NewFilter = (Classfilter *) new Classcos (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "abs")
    {
        NewFilter = (Classfilter *) new Classabs (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "square")
    {
        NewFilter = (Classfilter *) new Classsquare (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "ramp")
    {
        NewFilter = (Classfilter *) new Classramp (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "pulse")
    {
        NewFilter = (Classfilter *) new Classpulse (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "exp")
    {
        NewFilter = (Classfilter *) new Classexp (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "expV")
    {
        NewFilter = (Classfilter *) new Classexpv (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "log")
    {
        NewFilter = (Classfilter *) new Classlog (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "logV")
    {
        NewFilter = (Classfilter *) new Classlogv (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "pow")
    {
        NewFilter = (Classfilter *) new Classpow (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "powV")
    {
        NewFilter = (Classfilter *) new Classpowv (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "time")
    {
        NewFilter = (Classfilter *) new Classtime (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "julian")
    {
        NewFilter = (Classfilter *) new Classjulian (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "random")
    {
        NewFilter = (Classfilter *) new Classrandom (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "poly")
    {
        NewFilter = (Classfilter *) new Classpoly (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "polyV")
    {
        NewFilter = (Classfilter *) new Classpolyv (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "smear")
    {
        NewFilter = (Classfilter *) new ClassSmear (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "FtoC")
    {
        NewFilter = (Classfilter *) new ClassFtoC (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "KtoC")
    {
        NewFilter = (Classfilter *) new ClassKtoC (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "CtoK")
    {
        NewFilter = (Classfilter *) new ClassCtoK (File, ToVar, FilterStuff);
    }

    else
    if (Filter == "replace")
    {
        NewFilter = (Classfilter *) new ClassReplace (File, ToVar, FilterStuff);
    }

    else
    {
        string Mess = "Filter: '" + Filter + "' name not recognised";

InstrumentLogger::instance()->log_instrument_log("</Classmacro::addfilter(string Line)@@@ClassCRHM.cpp>");
        return;
    }

    if (! NewFilter -> Error)
    {
        FilterList -> AddObject (Filter, (TObject *) NewFilter);
    }

    else
    {
        delete NewFilter;
    }

InstrumentLogger::instance()->log_instrument_log("</Classmacro::addfilter(string Line)@@@ClassCRHM.cpp>");
}
void Classmacro :: execute (long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classmacro::execute(long Line)@@@ClassCRHM.cpp>");
    for (int ii = 0; ii < FilterList -> Count; ii ++)
        ((Classfilter *) FilterList -> Objects [ii]) -> doFunctions (Line);
InstrumentLogger::instance()->log_instrument_log("</Classmacro::execute(long Line)@@@ClassCRHM.cpp>");
}
void Classmacro :: fixup (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classmacro::fixup(void)@@@ClassCRHM.cpp>");
    for (int ii = 0; ii < FilterList -> Count; ii ++)
        ((Classfilter *) FilterList -> Objects [ii]) -> fixup ();
InstrumentLogger::instance()->log_instrument_log("</Classmacro::fixup(void)@@@ClassCRHM.cpp>");
}
Classmacro :: Classmacro (ClassData * File): File (File), Interpolation (0)
{
InstrumentLogger::instance()->log_instrument_log("<Classmacro::Classmacro(ClassData * File): File (File), Interpolation (0)@@@ClassCRHM.cpp>");
    FilterList = new TStringList;
    FilterList -> Sorted = false;
InstrumentLogger::instance()->log_instrument_log("</Classmacro::Classmacro(ClassData * File): File (File), Interpolation (0)@@@ClassCRHM.cpp>");
}
Classmacro :: ~Classmacro ()
{
InstrumentLogger::instance()->log_instrument_log("<Classmacro::~Classmacro()@@@ClassCRHM.cpp>");
    if (Interpolation > 0 && FilterList -> Count > Interpolation)
    {
        LogError ("Filter execution occurs before interpolation -> values may be incorrect." + File -> DataFileName, TExcept :: WARNING);
    }

    delete FilterList;
InstrumentLogger::instance()->log_instrument_log("</Classmacro::~Classmacro()@@@ClassCRHM.cpp>");
}
ClassFtoC :: ClassFtoC (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassFtoC::ClassFtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassFtoC::ClassFtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassFtoC :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassFtoC::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) ((Data [0] [Obs] [Line] - 32.0) * 5.0 / 9.0);
InstrumentLogger::instance()->log_instrument_log("</ClassFtoC::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassCtoK :: ClassCtoK (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCtoK::ClassCtoK(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassCtoK::ClassCtoK(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassCtoK :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCtoK::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) ((Data [0] [Obs] [Line] + 273.15));
InstrumentLogger::instance()->log_instrument_log("</ClassCtoK::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassReplace :: ClassReplace (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassReplace::ClassReplace(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassReplace::ClassReplace(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassReplace :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassReplace::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    long shift = thisVar -> FileData -> IndxMin;
    for (int Obs = 0; Obs < ObsCnt; ++ Obs)
        outVar -> FileData -> Data [Obs + DataIndx [Vs - 1]] [Line + shift] = Data [0] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassReplace::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassKtoC :: ClassKtoC (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKtoC::ClassKtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassKtoC::ClassKtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassKtoC :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKtoC::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) (Data [0] [Obs] [Line] - 273.15);
InstrumentLogger::instance()->log_instrument_log("</ClassKtoC::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassTimeshift :: ClassTimeshift (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassTimeshift::ClassTimeshift(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    MyObs -> TimeShiftFilter = (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</ClassTimeshift::ClassTimeshift(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
ClassRH_WtoI :: ClassRH_WtoI (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassRH_WtoI::ClassRH_WtoI(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassRH_WtoI::ClassRH_WtoI(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassRH_WtoI :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassRH_WtoI::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    double T = Data [0] [Obs] [Line];
    double RH = Data [1] [Obs] [Line];
    if (T < 0.0)
    {
        Data [Vs - 1] [Obs] [Line] = (double) (RH * 0.9995 * exp (22.452 * T / (272.55 + T)) / exp (17.502 * T / (240.97 + T)));
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = RH;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassRH_WtoI::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classea :: Classea (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classea::Classea(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classea::Classea(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
double estar (double t)
{
InstrumentLogger::instance()->log_instrument_log("<estar(double t)@@@ClassCRHM.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</estar(double t)@@@ClassCRHM.cpp>");
        return 0.611 * exp (17.27 * t / (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</estar(double t)@@@ClassCRHM.cpp>");
        return 0.611 * exp (21.88 * t / (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</estar(double t)@@@ClassCRHM.cpp>");
}
void Classea :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classea::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (Line == MyObs -> IndxMax)
    {
        for (int Obs = 0; Obs < ObsCnt; ++ Obs)
            for (long Line = MyObs -> IndxMin; Line <= MyObs -> IndxMax; ++ Line)
                Data [Vs - 1] [Obs] [Line] = (double) (estar (Data [0] [Obs] [Line]) * Data [1] [Obs] [Line] / 100.0);
    }

InstrumentLogger::instance()->log_instrument_log("</Classea::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classabs :: Classabs (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classabs::Classabs(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classabs::Classabs(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classabs :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classabs::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = abs (Data [0] [Obs] [Line]);
InstrumentLogger::instance()->log_instrument_log("</Classabs::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classrh :: Classrh (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classrh::Classrh(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classrh::Classrh(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classrh :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classrh::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) (Data [1] [Obs] [Line] / estar (Data [0] [Obs] [Line]) * 100.0);
InstrumentLogger::instance()->log_instrument_log("</Classrh::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classsin :: Classsin (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classsin::Classsin(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classsin::Classsin(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classsin :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classsin::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            period = (long) (Constants [0] * MyObs -> Freq);
            phase = (long) (Constants [1] * MyObs -> Freq);
            if (Constants [2] > MyObs -> Dt1 && Constants [2] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [2] - MyObs -> Dt1) * MyObs -> Freq);
            }

            else
            {
                delay = 0;
            }

            if (Constants [3] > 0.0)
            {
                duration = (long) ((Constants [3] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = (double) sin ((double (Line) / period - double (phase) / period) * 2 * M_PI);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classsin::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classcos :: Classcos (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classcos::Classcos(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classcos::Classcos(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classcos :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classcos::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            period = (long) (Constants [0] * MyObs -> Freq);
            phase = (long) (Constants [1] * MyObs -> Freq);
            if (Constants [2] > MyObs -> Dt1 && Constants [2] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [2] - MyObs -> Dt1) * MyObs -> Freq);
            }

            else
            {
                delay = 0;
            }

            if (Constants [3] > 0.0)
            {
                duration = (long) ((Constants [3] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = (double) cos ((double (Line) / period - double (phase) / period) * 2 * M_PI);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classcos::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classramp :: Classramp (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classramp::Classramp(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classramp::Classramp(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classramp :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classramp::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            period = (long) (Constants [0] * MyObs -> Freq);
            phase = (long) (Constants [1] * MyObs -> Freq);
            if (Constants [2] > MyObs -> Dt1 && Constants [2] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [2] - MyObs -> Dt1) * MyObs -> Freq);
            }

            else
            {
                delay = 0;
            }

            if (Constants [3] > 0.0)
            {
                duration = (long) ((Constants [3] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
            double X = (double) fmod (double (static_cast < long long > (Line) - static_cast < long long > (delay)) / double (period) * 2.0, 1.0);
            if (((Line + phase - delay) % period) >= period / 2)
            {
                Data [Vs - 1] [Obs] [Line] = (double) 1.0 - X;
            }

            else
            {
                Data [Vs - 1] [Obs] [Line] = X;
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classramp::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classsquare :: Classsquare (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classsquare::Classsquare(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classsquare::Classsquare(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classsquare :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classsquare::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            period = (long) (Constants [0] * MyObs -> Freq);
            phase = (long) (Constants [1] * MyObs -> Freq);
            if (Constants [2] > MyObs -> Dt1 && Constants [2] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [2] - MyObs -> Dt1) * MyObs -> Freq - 1);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [3] > 0.0)
            {
                duration = (long) ((Constants [3] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            if (((Line + phase) % period) >= period / 2)
            {
                Data [Vs - 1] [Obs] [Line] = 0.0;
            }

            else
            {
                Data [Vs - 1] [Obs] [Line] = 1.0;
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classsquare::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classpulse :: Classpulse (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpulse::Classpulse(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classpulse::Classpulse(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classpulse :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpulse::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            if (Constants [0] > MyObs -> Dt1 && Constants [0] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [0] - MyObs -> Dt1) * MyObs -> Freq - 1);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [1] > 0.0)
            {
                duration = (long) ((Constants [1] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = 1.0;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classpulse::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classexp :: Classexp (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classexp::Classexp(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classexp::Classexp(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classexp :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classexp::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            if (Constants [0] > MyObs -> Dt1 && Constants [0] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [0] - MyObs -> Dt1) * MyObs -> Freq - 1);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [1] > 0.0)
            {
                duration = (long) ((Constants [1] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            A = (double) Constants [2];
            B = (double) (Constants [3] / MyObs -> Freq);
            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = A * exp (B * (static_cast < long long > (Line) - static_cast < long long > (delay) - 1));
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classexp::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classexpv :: Classexpv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classexpv::Classexpv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (! Error)
    {
        A = (double) Constants [0];
        B = (double) Constants [0];
    }

InstrumentLogger::instance()->log_instrument_log("</Classexpv::Classexpv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classexpv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classexpv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = A * exp (B * Data [0] [Obs] [Line]);
InstrumentLogger::instance()->log_instrument_log("</Classexpv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classpoly :: Classpoly (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpoly::Classpoly(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classpoly::Classpoly(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classpoly :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpoly::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            if (Constants [0] > MyObs -> Dt1 && Constants [0] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [0] - MyObs -> Dt1) * MyObs -> Freq - 1);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [1] > 0.0)
            {
                duration = (long) ((Constants [1] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            double x = (static_cast < long long > (Line) - static_cast < long long > (delay) - 1) / double (MyObs -> Freq);
            Data [Vs - 1] [Obs] [Line] = (double) (Constants [2] + Constants [3] * x + Constants [4] * x * x + Constants [5] * x * x * x + Constants [6] * x * x * x * x);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classpoly::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classpolyv :: Classpolyv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpolyv::Classpolyv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classpolyv::Classpolyv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classpolyv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpolyv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    double x = Data [0] [Obs] [Line];
    Data [Vs - 1] [Obs] [Line] = (double) (Constants [0] + Constants [1] * x + Constants [2] * x * x + Constants [3] * x * x * x + Constants [4] * x * x * x * x);
InstrumentLogger::instance()->log_instrument_log("</Classpolyv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classlog :: Classlog (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classlog::Classlog(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classlog::Classlog(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classlog :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classlog::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            if (Constants [0] > MyObs -> Dt1 && Constants [0] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [0] - MyObs -> Dt1) * MyObs -> Freq - 1);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [1] > 0.0)
            {
                duration = (long) ((Constants [1] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            A = (double) Constants [2];
            B = (double) fabs (Constants [3]);
            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = A * log (B * double (static_cast < long long > (Line) - static_cast < long long > (delay)) / MyObs -> Freq);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classlog::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classlogv :: Classlogv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classlogv::Classlogv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (! Error)
    {
        A = (double) fabs (Constants [0]);
        B = (double) fabs (Constants [1]);
    }

InstrumentLogger::instance()->log_instrument_log("</Classlogv::Classlogv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classlogv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classlogv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = A * log (B * Data [0] [Obs] [Line]);
InstrumentLogger::instance()->log_instrument_log("</Classlogv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classpow :: Classpow (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpow::Classpow(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classpow::Classpow(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classpow :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpow::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            if (Constants [0] >= MyObs -> Dt1 && Constants [0] <= MyObs -> Dt2)
            {
                delay = (long) ((Constants [0] - MyObs -> Dt1) * MyObs -> Freq);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [1] > 0.0)
            {
                duration = (long) ((Constants [1] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            A = (double) Constants [2];
            B = (double) Constants [3];
            FirstTime = false;
        }

        if (Line < delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = A * pow ((static_cast < long long > (Line) - static_cast < long long > (delay) + 1) / double (MyObs -> Freq), B);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classpow::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classpowv :: Classpowv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpowv::Classpowv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (! Error)
    {
        A = (double) Constants [0];
        B = (double) Constants [1];
    }

InstrumentLogger::instance()->log_instrument_log("</Classpowv::Classpowv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classpowv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpowv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = A * pow (Data [0] [Obs] [Line], B);
InstrumentLogger::instance()->log_instrument_log("</Classpowv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classtime :: Classtime (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classtime::Classtime(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classtime::Classtime(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classtime :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classtime::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            option = (int) Constants [0];
            if (option)
            {
                start = 0.0;
            }

            else
            {
                start = floor (Global :: DTstart);
            }

            FirstTime = false;
        }

        Data [Vs - 1] [Obs] [Line] = double (start + Line / double (MyObs -> Freq));
    }

InstrumentLogger::instance()->log_instrument_log("</Classtime::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classjulian :: Classjulian (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classjulian::Classjulian(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (! Error)
    {
        option = (int) Constants [0];
    }

InstrumentLogger::instance()->log_instrument_log("</Classjulian::Classjulian(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classjulian :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classjulian::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    switch (option) {
    case 0:
        Data [Vs - 1] [Obs] [Line] = (double) julian ("now");
        break;
    case 1:
        Data [Vs - 1] [Obs] [Line] = (double) julian ("start");
        break;
    case 2:
        Data [Vs - 1] [Obs] [Line] = (double) julian ("end");
        break;
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</Classjulian::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classrandom :: Classrandom (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classrandom::Classrandom(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (! Error)
    {
        srand ((unsigned) Constants [0]);
    }

InstrumentLogger::instance()->log_instrument_log("</Classrandom::Classrandom(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classrandom :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classrandom::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) rand () / RAND_MAX;
InstrumentLogger::instance()->log_instrument_log("</Classrandom::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classrefwind :: Classrefwind (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classrefwind::Classrefwind(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (! Error)
    {
        double d = (double) (Constants [2] * 2.0 / 3.0);
        double Z = (double) (Constants [2] * 0.123);
        Const = (double) (log ((Constants [1] - d) / Z) / log ((Constants [0] - d) / Z));
    }

InstrumentLogger::instance()->log_instrument_log("</Classrefwind::Classrefwind(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classrefwind :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classrefwind::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] * Const;
InstrumentLogger::instance()->log_instrument_log("</Classrefwind::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classadd :: Classadd (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classadd::Classadd(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classadd::Classadd(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classadd :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classadd::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] + (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classadd::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classsub :: Classsub (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classsub::Classsub(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classsub::Classsub(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classsub :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classsub::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] - (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classsub::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classmul :: Classmul (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classmul::Classmul(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classmul::Classmul(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classmul :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classmul::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] * (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classmul::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classdiv :: Classdiv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classdiv::Classdiv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classdiv::Classdiv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classdiv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classdiv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] / (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classdiv::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassaddV :: ClassaddV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassaddV::ClassaddV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassaddV::ClassaddV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassaddV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassaddV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] + Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassaddV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClasssubV :: ClasssubV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClasssubV::ClasssubV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClasssubV::ClasssubV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClasssubV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClasssubV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] - Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClasssubV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassmulV :: ClassmulV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassmulV::ClassmulV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassmulV::ClassmulV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassmulV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassmulV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] * Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassmulV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassdivV :: ClassdivV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassdivV::ClassdivV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassdivV::ClassdivV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassdivV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassdivV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] / Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassdivV::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
Classconst :: Classconst (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classconst::Classconst(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classconst::Classconst(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void Classconst :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classconst::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classconst::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassSim :: ClassSim (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSim::ClassSim(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    MyObs -> Simulation = true;
    MyObs -> Dt1 = Constants [0];
    MyObs -> Dt2 = Constants [1];
    MyObs -> Interval = Constants [2] / 24.0;
    MyObs -> Freq = (long) (1.0 / MyObs -> Interval + 1.0 / 192.0);
    MyObs -> Lines = (long) (ceil (MyObs -> Dt2 - MyObs -> Dt1) * MyObs -> Freq);
    MyObs -> IndxMin = 0;
    MyObs -> IndxMax = (long) (floor ((MyObs -> Dt2 - MyObs -> Dt1) * MyObs -> Freq + MyObs -> Interval / 2.0) - 1);
    if (Global :: DTstart == 0.0)
    {
        Global :: DTstart = floor (MyObs -> Dt1);
        Global :: DTend = floor (MyObs -> Dt2);
        Global :: DTnow = Global :: DTstart;
        Global :: Freq = MyObs -> Freq;
        Global :: Interval = MyObs -> Interval;
    }

    if (Global :: DTend == 0.0)
    {
        Global :: DTend = MyObs -> Dt2;
    }

    if (Global :: DTend != 0.0 && Global :: DTend < MyObs -> Dt2)
    {
        MyObs -> Dt2 = Global :: DTend;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSim::ClassSim(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassSim :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSim::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
InstrumentLogger::instance()->log_instrument_log("</ClassSim::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassForce :: ClassForce (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassForce::ClassForce(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
    readargs ();
    if (MyObs -> FilterCnt > 0)
    {
        error ("ForceFilter filter must be the first filter.");
    }

    if (Constants [0] > 288)
    {
        error ("ForceFilter filter interval cannot be less than 5 minutes ");
    }

    if (Constants [0] < 1)
    {
        error ("ForceFilter filter interval cannot be greater than daily ");
    }

    MyObs -> ForceInterval = (long) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</ClassForce::ClassForce(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCRHM.cpp>");
}
void ClassForce :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassForce::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
InstrumentLogger::instance()->log_instrument_log("</ClassForce::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassSmear :: ClassSmear (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), Minus (false)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSmear::ClassSmear(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), Minus (false)@@@ClassCRHM.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassSmear::ClassSmear(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), Minus (false)@@@ClassCRHM.cpp>");
}
void ClassSmear :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSmear::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (FirstTime)
    {
        if (Constants [0] < 0.0)
        {
            Minus = true;
        }

        if (Constants [0] <= 0.0)
        {
            Constants [0] = MyObs -> Dt1;
        }

        if (Constants [1] <= 0.0)
        {
            Constants [1] = MyObs -> Dt2;
        }

        Constants [0] = MyObs -> Dt1 - MyObs -> Interval / 2.0;
        Constants [1] = MyObs -> Dt2 + MyObs -> Interval / 2.0;
        FirstTime = false;
    }

    double now = MyObs -> Dt1 + Line * MyObs -> Interval;
    double delta = MyObs -> Interval / 2.0;
    double now0 = fmod (now, 1.0);
    if (now0 > - delta && now0 < delta)
    {
        double value = Data [0] [Obs] [Line - MyObs -> Freq + 1] / MyObs -> Freq;
        if (now > Constants [0] && now < Constants [1] && ((Minus && value < 0.0) || ! Minus))
        {
            if (value < 0.0)
            {
                value = - value;
            }

            for (long ii = 0; ii < MyObs -> Freq; ++ ii) {
                if (Line - ii < 0)
                {
                    break;
                }

                Data [Vs - 1] [Obs] [Line - ii] = value;
            }
        }

        else
        {
            for (long ii = 0; ii < MyObs -> Freq; ++ ii) {
                if (Line - ii < 0)
                {
                    break;
                }

                Data [Vs - 1] [Obs] [Line - ii] = Data [0] [Obs] [Line - ii];
            }
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSmear::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassMissing :: ClassMissing (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing::ClassMissing(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassCRHM.cpp>");
    readargs ();
    GoodData = new double [ObsCnt];
InstrumentLogger::instance()->log_instrument_log("</ClassMissing::ClassMissing(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassCRHM.cpp>");
}
void ClassMissing :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    static bool Warned = false;
    if (FirstTime)
    {
        if ((Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1]) && ! Warned)
        {
            LogError ("Missing data in first interval of " + MyObs -> DataFileName, TExcept :: WARNING);
            Warned = true;
        }

        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
        if (Obs + 1 >= ObsCnt)
        {
            FirstTime = false;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMissing::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
        return;
    }

    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = GoodData [Obs];
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissing::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassMissing :: ~ClassMissing ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing::~ClassMissing()@@@ClassCRHM.cpp>");
    delete [] GoodData;
InstrumentLogger::instance()->log_instrument_log("</ClassMissing::~ClassMissing()@@@ClassCRHM.cpp>");
}
ClassMissingInter :: ClassMissingInter (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingInter::ClassMissingInter(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassCRHM.cpp>");
    readargs ();
    GoodData = new double [ObsCnt];
    LastGoodData = new long [ObsCnt];
InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::ClassMissingInter(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassCRHM.cpp>");
}
void ClassMissingInter :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingInter::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    static bool Warned = false;
    if (FirstTime)
    {
        if ((Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1]) && ! Warned)
        {
            LogError ("Missing data in first interval of " + MyObs -> DataFileName, TExcept :: WARNING);
            Warned = true;
            LastGoodData [Obs] = - 1;

InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
            return;
        }

        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
        LastGoodData [Obs] = Line;
        if (Obs + 1 >= ObsCnt)
        {
            FirstTime = false;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
        return;
    }

    if (Data [0] [Obs] [Line] > Constants [0] && Data [0] [Obs] [Line] < Constants [1])
    {
        if (Line - 1 > LastGoodData [Obs] && LastGoodData [Obs] != - 1)
        {
            double dif = (Data [0] [Obs] [Line] - GoodData [Obs]) / (static_cast < long long > (Line) - static_cast < long long > (LastGoodData [Obs]));
            for (int ii = LastGoodData [Obs] + 1; ii < Line; ++ ii)
                Data [Vs - 1] [Obs] [ii] = Data [Vs - 1] [Obs] [ii - 1] + dif;
        }

        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
        LastGoodData [Obs] = Line;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassMissingInter :: ~ClassMissingInter ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingInter::~ClassMissingInter()@@@ClassCRHM.cpp>");
    delete [] GoodData;
    delete [] LastGoodData;
InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::~ClassMissingInter()@@@ClassCRHM.cpp>");
}
void ClassMissing0 :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing0::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = 0.0;
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissing0::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
void ClassMissingC :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingC::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = (double) Constants [2];
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingC::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
void ClassMissingFlagAfter :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingFlagAfter::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (FirstTime)
    {
        First = Line;
        FirstTime = false;
    }

    else
    {
        Last = Line;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingFlagAfter::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
void ClassMissingFlag :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingFlag::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = 1.0;
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingFlag::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
}
ClassMissingFlagAfter :: ~ClassMissingFlagAfter ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingFlagAfter::~ClassMissingFlagAfter()@@@ClassCRHM.cpp>");
    for (int Obs = 0; Obs < ObsCnt; ++ Obs)
        for (int Line = First; Line <= Last; ++ Line) {
            if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
            {
                Data [Vs - 1] [Obs] [Line] = 1.0;
            }

            else
            {
                Data [Vs - 1] [Obs] [Line] = 0.0;
            }

        }
InstrumentLogger::instance()->log_instrument_log("</ClassMissingFlagAfter::~ClassMissingFlagAfter()@@@ClassCRHM.cpp>");
}
void ClassMissingrepl :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingrepl::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = Data [1] [Obs] [Line];
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingrepl::doFunc(long Obs, long Line)@@@ClassCRHM.cpp>");
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
    if (Except.Kind == TExcept :: TERMINATE)
    {
        throw (Except);
    }

InstrumentLogger::instance()->log_instrument_log("</LogError(CRHMException Except)@@@ClassCRHM.cpp>");
}
void LogError (string S, TExcept Kind)
{
InstrumentLogger::instance()->log_instrument_log("<LogError(string S, TExcept Kind)@@@ClassCRHM.cpp>");
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
InstrumentLogger::instance()->log_instrument_log("</LogMessage(long hh, const char * S, TExtra Opt)@@@ClassCRHM.cpp>");
}
void LogDebug (char * S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(char * S)@@@ClassCRHM.cpp>");
    string SS = S;
InstrumentLogger::instance()->log_instrument_log("</LogDebug(char * S)@@@ClassCRHM.cpp>");
}
void LogDebug (long h, char * Text, double v)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(long h, char * Text, double v)@@@ClassCRHM.cpp>");
    string S = to_string (h) + to_string (1);
    S += Text + to_string (v);
InstrumentLogger::instance()->log_instrument_log("</LogDebug(long h, char * Text, double v)@@@ClassCRHM.cpp>");
}
void LogDebugD (char * S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebugD(char * S)@@@ClassCRHM.cpp>");
    string D = FormatString (Global :: DTnow, "yy mm dd ");
    string SS = D + S;
InstrumentLogger::instance()->log_instrument_log("</LogDebugD(char * S)@@@ClassCRHM.cpp>");
}
void LogDebugT (string S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebugT(string S)@@@ClassCRHM.cpp>");
    string D = FormatString (Global :: DTnow, "yy mm dd hh nn ");
    string SS = "yy mm dd hh mm - ";
    SS += D + " - " + S;
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
long ClassVar :: GetUnit (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVar::GetUnit(void)@@@ClassCRHM.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassVar::GetUnit(void)@@@ClassCRHM.cpp>");
    return GetSharedUnit (units);
InstrumentLogger::instance()->log_instrument_log("</ClassVar::GetUnit(void)@@@ClassCRHM.cpp>");
}
long ClassPar :: GetUnit (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassPar::GetUnit(void)@@@ClassCRHM.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassPar::GetUnit(void)@@@ClassCRHM.cpp>");
    return GetSharedUnit (units);
InstrumentLogger::instance()->log_instrument_log("</ClassPar::GetUnit(void)@@@ClassCRHM.cpp>");
}
Convert :: Convert ()
{
InstrumentLogger::instance()->log_instrument_log("<Convert::Convert()@@@ClassCRHM.cpp>");
    NumUnits = 0;
    NumBasicUnits = 0;
    NumMultipliers = 0;
    while (! (Infos [NumUnits].Abbr).empty ()) {
        if ((Infos [NumUnits].Expr).empty ())
        {
            Infos [NumUnits].k = NumBasicUnits;
            ++ NumBasicUnits;
        }

        ++ NumUnits;
    }
    while (Multipliers [NumMultipliers].Abbr) {
        ++ NumMultipliers;
    }
InstrumentLogger::instance()->log_instrument_log("</Convert::Convert()@@@ClassCRHM.cpp>");
}Unit_Info Convert :: Infos [] = {Unit_Info ("1", "1", 1, ""), Unit_Info ("A", "Ampere", 1, ""), Unit_Info ("Bq", "becquerel", 1, "l/s"), Unit_Info ("Btu", "InternationalTableBtu", 1055.05585262, "Kg*m^2/s^2"), Unit_Info ("C", "Coulomb", 1, "A*s"), Unit_Info ("Ci", "Curie", 3.7 * 1010, "l/s"), Unit_Info ("F", "Farad", 1, "A^2*s^4/Kg*m^2"), Unit_Info ("Fdy", "Faraday", 96487, "A*s"), Unit_Info ("Gy", "Gray", 1, "m^2/s^2"), Unit_Info ("H", "Henry", 1, "Kg*m^2/A^2*s^2"), Unit_Info ("Hz", "Hertz", 1, "s^-1"), Unit_Info ("J", "Joule", 1, "Kg*m^2/s^2"), Unit_Info ("K", "Kelvin", 1, ""), Unit_Info ("Knot", "NauticalMilesPerHour", 463.0 / 900.0, "m/s"), Unit_Info ("N", "Newton", 1, "Kg*m/s^2"), Unit_Info ("Ohm", "Ohm", 1, "Kg*m^2/A^2*s^3"), Unit_Info ("OzUK", "UKFluidOunce", 2.8413075e-5, "m^3"), Unit_Info ("P", "Poise", 0.1, "Kg/m*s"), Unit_Info ("Pa", "Pascal", 1, "Kg/m*s"), Unit_Info ("Pdl", "Poundal", 0.13825495376, "Kg*m/s^2"), Unit_Info ("Pica", "Pica", 1.0 / 72.0, "in"), Unit_Info ("R", "Roentgen", 0.000258, "A*s/Kg"), Unit_Info ("S", "Siemens", 1, "A^2*s^3/Kg*m^2"), Unit_Info ("St", "Stokes", 0.0001, "m^2/s"), Unit_Info ("Sv", "Sievert", 1, "m^2/s^2"), Unit_Info ("T", "Tesla", 1, "Kg/A*s^2"), Unit_Info ("U", "UnifiedAtomicMass", 1.6605402e-27, "Kg"), Unit_Info ("V", "Volt", 1, "Kg*m^2/A*s^2"), Unit_Info ("W", "Watt", 1, "Kg*m^2/s^3"), Unit_Info ("Wb", "Weber", 1, "Kg*m^2/A*s^2"), Unit_Info ("acre", "Acre", 4046.87260987, "m^2"), Unit_Info ("arcmin", "ArcMinute", 2.9088820866e-4, "r"), Unit_Info ("arcs", "ArcSecond", 4.848136111e-6, "r"), Unit_Info ("atm", "Attmosphere", 101325, "Kg/m*s^2"), Unit_Info ("au", "AstronomicalUnit", 1.495979 * 1011, "m"), Unit_Info ("b", "Barn", 1e-28, "m^2"), Unit_Info ("bar", "Bar", 100000, "Kg/m*s^2"), Unit_Info ("bbl", "Barrel", 0.158987294928, "m^3"), Unit_Info ("bu", "Bushel", 0.03523907, "m^3"), Unit_Info ("c", "LightSpeed", 299792458, "m/s"), Unit_Info ("cal", "Calorie", 4.1868, "Kg*m^2/s^2"), Unit_Info ("cd", "Candela", 1, ""),
      Unit_Info ("chain", "Chain", 20.1168402337, "m"), Unit_Info ("ct", "Carat", 0.0002, "Kg"), Unit_Info ("cu", "USCup", 2.365882365e-4, "m^3"), Unit_Info ("d", "day", 86400, "s"), Unit_Info ("dyn", "Dyne", 0.00001, "Kg*m/s^2"), Unit_Info ("eV", "ElectronVolt", 1.60217733e-19, "Kg*m^2/s^2"), Unit_Info ("erg", "Erg", 0.0000001, "Kg*m^2/s^2"), Unit_Info ("fath", "Fathom", 1.82880365761, "m"), Unit_Info ("fbm", "BoardFoot", 0.002359737216, "m^3"), Unit_Info ("fc", "Footcandle", 10.7639104167, "cd*sr/m^2"), Unit_Info ("fermi", "Fermi", 1e-15, "m"), Unit_Info ("flam", "Footlambert", 3.42625909964, "cd/m^2"), Unit_Info ("ft", "InternationalFoot", 0.3048, "m"), Unit_Info ("ftUS", "SurveyFoot", 0.304800609601, "m"), Unit_Info ("g", "Gram", 1, ""), Unit_Info ("ga", "StandardFreefall", 9.80665, "m/s^2"), Unit_Info ("gal", "USGallon", 0.003785411784, "m^3"), Unit_Info ("galC", "CanadianGallon", 0.00454609, "m^3"), Unit_Info ("galUK", "UKGallon", 0.004546092, "m^3"), Unit_Info ("gf", "GramForce", 0.00980665, "Kg*m/s^2"), Unit_Info ("grad", "Grade", 1.57079632679e-2, "r"), Unit_Info ("grain", "Grain", 0.00006479891, "Kg"), Unit_Info ("h", "Hour", 3600, "s"), Unit_Info ("ha", "Hectare", 10000, "m^2"), Unit_Info ("hp", "horsepower", 745.699871582, "Kg*m^2/s^2"), Unit_Info ("in", "Inch", 0.0254, "m"), Unit_Info ("inH2O", "InchesOfWater", 248.84, "Kg/m*s^2"), Unit_Info ("inHg", "InchesOfMercury", 3386.38815789, "Kg/m*s^2"), Unit_Info ("int", "CRHM time step", 3600, "s"), Unit_Info ("kip", "KilopoundForce", 4448.22161526, "Kg*m/s^2"), Unit_Info ("kph", "KilometersPerHour", 5.0 / 18.0, "m/s"), Unit_Info ("l", "Liter", 0.001, "m^3"), Unit_Info ("lam", "Lambert", 3183.09886184, "cd/m^2"), Unit_Info ("lb", "AvoirdupoisPound", 0.45359267, "Kg"), Unit_Info ("lbf", "PoundForce", 4.44822161526, "Kg*m/s^2"), Unit_Info ("lbt", "TroyPound", 0.3732417216, "Kg"), Unit_Info ("lm", "Lumen", 1, "cd*sr"), Unit_Info ("lx", "Lux", 1, "cd*sr/m^2"), Unit_Info ("lyr", "LightYear", 9.46052840488 * 1015,
      "m"), Unit_Info ("m", "Meter", 1, ""), Unit_Info ("mho", "Mho", 1, "A^2*s^2/Kg*m^2"), Unit_Info ("mi", "InternationalMile", 1609.344, "m"), Unit_Info ("miUS", "USStatuteMile", 1609.34721869, "m"), Unit_Info ("mil", "Mil", 0.0000254, "m"), Unit_Info ("min", "Minute", 60, "s"), Unit_Info ("mmHg", "MilimeterOfMercury", 133.322368421, "Kg/m*s^2"), Unit_Info ("mol", "Mole", 1, ""), Unit_Info ("mph", "MilesPerHour", 0.44704, "m/s"), Unit_Info ("nmi", "NauticalMile", 1852, "m"), Unit_Info ("oz", "Ounce", 0.028349523125, "Kg"), Unit_Info ("ozfl", "USFluidOunce", 2.95735295625e-5, "m^3"), Unit_Info ("ozt", "TroyOunce", 0.0311034768, "Kg"), Unit_Info ("pc", "Parsec", 3.08567818585106, "m"), Unit_Info ("ph", "Phot", 10000, "cd*sr/m^2"), Unit_Info ("pk", "Peck", 0.0088097675, "m^3"), Unit_Info ("psi", "PoundsPerSquareInch", 6894.75729317, "Kg/m*s^2"), Unit_Info ("pt", "Pint", 0.000473176473, "m^3"), Unit_Info ("qt", "Quart", 0.000946352946, "m^3"), Unit_Info ("r", "Radian", 1, ""), Unit_Info ("rad", "Rad", 0.01, "m^2/s^2"), Unit_Info ("rd", "Rod", 5.02921005842, "m"), Unit_Info ("rem", "Rem", 0.01, "m^2/s^2"), Unit_Info ("s", "Second", 1, ""), Unit_Info ("sb", "Stilb", 10000, "cd/m^2"), Unit_Info ("slug", "Slug", 14.5939029372, "Kg"), Unit_Info ("sr", "Steradian", 1, ""), Unit_Info ("st", "Stere", 1, "m^3"), Unit_Info ("t", "MetricTon", 1000, "Kg"), Unit_Info ("tbsp", "Tablespoon", 1.47867647813e-5, "m^3"), Unit_Info ("therm", "EECTherm", 105506000, "Kg*m^2/s^2"), Unit_Info ("ton", "ShortTon", 907.18474, "Kg"), Unit_Info ("tonUK", "UKLongTon", 1016.0469088, "Kg"), Unit_Info ("torr", "Torr", 133.322368421, "Kg/m^2"), Unit_Info ("tsp", "Teaspoon", 4.92892159375e-6, "m^3"), Unit_Info ("yd", "InternationalYard", 0.9144, "m"), Unit_Info ("yr", "Year", 31556925.9747, "s"), Unit_Info ("\0xB", "Degree", 1.74532925199e-2, "r"), Unit_Info ("\0xB0C", "DegreeCelsius", 1.0, "K"), Unit_Info ("\0xB0F", "DegreesFahrenheit", 1.0 / 1.8, "K"), Unit_Info ("\0xB0R", "DegreesRankine", 1.0 /
      1.8, "K"), Unit_Info ("\0xB5", "Micron", 1e-6, "m"), Unit_Info ("\0xC5", "Angstrom", 1e-10, "m"), Unit_Info ("", "", 0, "")};
Multiplier_Info Convert :: Multipliers [] = {Multiplier_Info ('Y', "Yotta", 1e+24), Multiplier_Info ('Z', "Zetta", 1e+21), Multiplier_Info ('E', "Exa", 1e+18), Multiplier_Info ('P', "Peta", 1e+15), Multiplier_Info ('T', "Tera", 1e+12), Multiplier_Info ('G', "Giga", 1e+9), Multiplier_Info ('M', "Mega", 1e+6), Multiplier_Info ('k', "kilo", 1e+3), Multiplier_Info ('K', "Kilo", 1e+3), Multiplier_Info ('h', "hecto", 1e+2), Multiplier_Info ('H', "Hecto", 1e+2), Multiplier_Info ('D', "Deka", 1e+1), Multiplier_Info ('d', "deci", 1e-1), Multiplier_Info ('c', "cent", 1e-2), Multiplier_Info ('m', "mili", 1e-3), Multiplier_Info ('u', "micro", 1e-6), Multiplier_Info ('n', "nano", 1e-9), Multiplier_Info ('p', "pico", 1e-12), Multiplier_Info ('f', "femto", 1e-15), Multiplier_Info ('a', "atto", 1e-18), Multiplier_Info ('z', "zepto", 1e-21), Multiplier_Info ('y', "yocto", 1e-24), Multiplier_Info ('\0', "", 0.0)};

string tcsinc (string pszIn)
{
InstrumentLogger::instance()->log_instrument_log("<tcsinc(string pszIn)@@@ClassCRHM.cpp>");

InstrumentLogger::instance()->log_instrument_log("</tcsinc(string pszIn)@@@ClassCRHM.cpp>");
    return pszIn.substr (1);
InstrumentLogger::instance()->log_instrument_log("</tcsinc(string pszIn)@@@ClassCRHM.cpp>");
}
string tcsSkipSpaces (string pszIn)
{
InstrumentLogger::instance()->log_instrument_log("<tcsSkipSpaces(string pszIn)@@@ClassCRHM.cpp>");
    while (pszIn [0] == ' ') pszIn = pszIn.substr (1);

InstrumentLogger::instance()->log_instrument_log("</tcsSkipSpaces(string pszIn)@@@ClassCRHM.cpp>");
    return pszIn;
InstrumentLogger::instance()->log_instrument_log("</tcsSkipSpaces(string pszIn)@@@ClassCRHM.cpp>");
}
string tcsSqueeze (string pszIn)
{
InstrumentLogger::instance()->log_instrument_log("<tcsSqueeze(string pszIn)@@@ClassCRHM.cpp>");
    string :: iterator pos;
    string :: size_type Idx;
    char const Misc [] = {"( )%\0xBA\t"};
    Idx = pszIn.find_first_of (Misc);
    while (Idx != string :: npos) {
        pszIn = pszIn.erase (Idx, 1);
        Idx = pszIn.find_first_of (Misc);
    }

InstrumentLogger::instance()->log_instrument_log("</tcsSqueeze(string pszIn)@@@ClassCRHM.cpp>");
    return pszIn;
InstrumentLogger::instance()->log_instrument_log("</tcsSqueeze(string pszIn)@@@ClassCRHM.cpp>");
}
bool Convert :: ConvertUnit (double & dValue, string pszSrcUnit, string pszDstUnit)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
    pszSrcUnit = tcsSkipSpaces (pszSrcUnit);
    pszDstUnit = tcsSkipSpaces (pszDstUnit);
    dValue = 1.0;
    if (pszSrcUnit.compare (pszDstUnit) == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
        return true;
    }

    Tresult uSrcUnit (NumBasicUnits);
    try {
        pszSrcUnit = ParseDivUnitExpr (pszSrcUnit, uSrcUnit);
    }
    catch (int i) {
        if (i == 3)
        {

InstrumentLogger::instance()->log_instrument_log("</Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
            return false;
        }

    }
    Tresult uDstUnit (NumBasicUnits);
    try {
        pszDstUnit = ParseDivUnitExpr (pszDstUnit, uDstUnit);
    }
    catch (int i) {
        if (i == 3)
        {

InstrumentLogger::instance()->log_instrument_log("</Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
            return false;
        }

    }
    for (int i = 0; i < NumBasicUnits; ++ i)
        if (uSrcUnit.aExp [i] != uDstUnit.aExp [i])
        {
            dValue = - 999;

InstrumentLogger::instance()->log_instrument_log("</Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
            return false;
        }

    dValue *= uSrcUnit.k;
    dValue /= uDstUnit.k;

InstrumentLogger::instance()->log_instrument_log("</Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</Convert::ConvertUnit(double & dValue, string pszSrcUnit, string pszDstUnit)@@@ClassCRHM.cpp>");
}
double Convert :: quickPow (double k, int nPow)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::quickPow(double k, int nPow)@@@ClassCRHM.cpp>");
    bool bNegative = (nPow < 0);
    if (bNegative)
    {
        nPow = - nPow;
    }

    double r = 1.0;
    while (nPow != 0) {
        if (nPow & 1)
        {
            r *= k;
        }

        k *= k;
        nPow >>= 1;
    }
    if (bNegative)
    {
        r = 1.0 / r;
    }

InstrumentLogger::instance()->log_instrument_log("</Convert::quickPow(double k, int nPow)@@@ClassCRHM.cpp>");
    return r;
InstrumentLogger::instance()->log_instrument_log("</Convert::quickPow(double k, int nPow)@@@ClassCRHM.cpp>");
}
int Convert :: LookupUnit (string pszIn)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::LookupUnit(string pszIn)@@@ClassCRHM.cpp>");
    int iFirst = 0;
    int iLast = NumUnits;
    int i;
    string :: size_type Idx;
    Idx = pszIn.find_first_of ("*/^");
    if (Idx == string :: npos)
    {
        Idx = pszIn.size ();
    }

    while (iLast >= iFirst) {
        i = (iLast + iFirst) / 2;
        int nCmp = pszIn.compare (0, Idx, Infos [i].Abbr);
        if (nCmp == 0)
        {

InstrumentLogger::instance()->log_instrument_log("</Convert::LookupUnit(string pszIn)@@@ClassCRHM.cpp>");
            return i;
        }

        if (nCmp < 0)
        {
            iLast = i - 1;
        }

        else
        {
            iFirst = i + 1;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Convert::LookupUnit(string pszIn)@@@ClassCRHM.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</Convert::LookupUnit(string pszIn)@@@ClassCRHM.cpp>");
}
void Convert :: DivUnit (Tresult & u1, const Tresult & u2)
{
    u1.k /= u2.k;
    for (int i = 0; i < NumBasicUnits; ++ i)
        u1.aExp [i] -= u2.aExp [i];
}
;

void Convert :: MulUnit (Tresult & u1, const Tresult & u2)
{
    u1.k *= u2.k;
    for (int i = 0; i < NumBasicUnits; ++ i)
        u1.aExp [i] += u2.aExp [i];
}
;

void Convert :: MulUnitK (Tresult & u, double k)
{
    u.k *= k;
}
;

void Convert :: PowUnit (Tresult & u, char nPow)
{
    for (int i = 0; i < NumBasicUnits; ++ i)
        u.aExp [i] *= nPow;
    u.k = quickPow (u.k, nPow);
}
;

void Convert :: SetBasicUnit (Tresult & u, double k, int iUnit)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::SetBasicUnit(Tresult & u, double k, int iUnit)@@@ClassCRHM.cpp>");
    u.k = k;
    int iBasicUnit = (int) (Infos [iUnit].k);
    if (0 <= iBasicUnit)
    {
        u.aExp [iBasicUnit] = 1;
    }

InstrumentLogger::instance()->log_instrument_log("</Convert::SetBasicUnit(Tresult & u, double k, int iUnit)@@@ClassCRHM.cpp>");
}
void Convert :: ExpandUnitExpr (Tresult & u, double k, string pszExpr)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ExpandUnitExpr(Tresult & u, double k, string pszExpr)@@@ClassCRHM.cpp>");
    pszExpr = ParseDivUnitExpr (pszExpr, u);
    u.k *= k;
InstrumentLogger::instance()->log_instrument_log("</Convert::ExpandUnitExpr(Tresult & u, double k, string pszExpr)@@@ClassCRHM.cpp>");
}
string Convert :: ParseDivUnitExpr (string pszIn, Tresult & u)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ParseDivUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    pszIn = ParseMulUnitExpr (pszIn, u);
    if (pszIn.empty ())
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseDivUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return pszIn;
    }

    string pszMark = pszIn;
    pszIn = tcsSkipSpaces (pszIn);
    if (pszIn [0] != '/')
    {
        throw 3;
    }

    pszIn = tcsinc (pszIn);
    pszIn = tcsSkipSpaces (pszIn);
    Tresult uAux (NumBasicUnits);
    pszIn = ParseMulUnitExpr (pszIn, uAux);
    DivUnit (u, uAux);
    pszMark = pszIn;

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseDivUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    return pszMark;
InstrumentLogger::instance()->log_instrument_log("</Convert::ParseDivUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
}
string Convert :: ParseMulUnitExpr (string pszIn, Tresult & u)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ParseMulUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    pszIn = ParsePowUnitExpr (pszIn, u);
    if (pszIn.empty ())
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseMulUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return pszIn;
    }

    string pszMark = pszIn;
    while (pszIn = tcsSkipSpaces (pszIn), pszIn [0] == '*') {
        pszIn = tcsinc (pszIn);
        Tresult uAux (NumBasicUnits);
        pszIn = ParsePowUnitExpr (pszIn, uAux);
        if (pszIn == "error")
        {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseMulUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
            return pszMark;
        }

        MulUnit (u, uAux);
        pszMark = pszIn;
    }

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseMulUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    return pszIn;
InstrumentLogger::instance()->log_instrument_log("</Convert::ParseMulUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
}
string Convert :: ParsePowUnitExpr (string pszIn, Tresult & u)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ParsePowUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    pszIn = ParseUnitPhase1 (pszIn, u);
    if (pszIn.empty ())
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParsePowUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return pszIn;
    }

    string pszMark = pszIn;
    pszIn = tcsSkipSpaces (pszIn);
    if (pszIn [0] != '^')
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParsePowUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return pszMark;
    }

    pszIn = tcsinc (pszIn);
    pszIn = tcsSkipSpaces (pszIn);
    bool bNegative = (pszIn [0] == '-');
    if (pszIn [0] == '+' || pszIn [0] == '-')
    {
        pszIn = tcsinc (pszIn);
    }

    if (iswdigit (pszIn [0]))
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParsePowUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return pszMark;
    }

    char nPow = 0;
    while (iswdigit (pszIn [0])) {
        char nPow2 = nPow * 10 + (pszIn [0] - '0');
        if (nPow2 < nPow)
        {
            break;
        }

        nPow = nPow2;
        pszIn = tcsinc (pszIn);
    }
    if (bNegative)
    {
        nPow = - nPow;
    }

    PowUnit (u, nPow);

InstrumentLogger::instance()->log_instrument_log("</Convert::ParsePowUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    return pszIn;
InstrumentLogger::instance()->log_instrument_log("</Convert::ParsePowUnitExpr(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
}
string Convert :: ParseUnitPhase1 (string pszIn, Tresult & u)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ParseUnitPhase1(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    string pszMark = pszIn;
    pszIn = ParseUnitPhase2 (pszIn, u);
    if (pszIn != "????")
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseUnitPhase1(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return pszIn;
    }

    pszIn = pszMark;
    double k;
    int ii;
    for (ii = 0; ii < NumMultipliers; ++ ii)
        if (pszIn [0] == Multipliers [ii].Abbr)
        {
            k = Multipliers [ii].k;
            break;
        }

    if (ii >= NumMultipliers)
    {
        bool bNegative = (pszIn [0] == '-');
        if (pszIn [0] == '+' || pszIn [0] == '-')
        {
            pszIn = tcsinc (pszIn);
        }

        if (! iswdigit (pszIn [0]))
        {
            throw 1;
        }

        else
        {
            k = 0.0;
            while (iswdigit (pszIn [0])) {
                double nPow2 = (k * 10.0) + ((long long) pszIn [0] - (long long) '0');
                if (nPow2 < k)
                {
                    break;
                }

                k = nPow2;
                pszIn = tcsinc (pszIn);
            }
            if (bNegative)
            {
                k = - k;
            }

            if (pszIn [0] == '*')
            {
                pszIn = tcsinc (pszIn);
            }

        }

    }

    else
    {
        pszIn = tcsinc (pszIn);
    }

    pszIn = ParseUnitPhase2 (pszIn, u);
    MulUnitK (u, k);

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseUnitPhase1(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    return pszIn;
InstrumentLogger::instance()->log_instrument_log("</Convert::ParseUnitPhase1(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
}
string Convert :: ParseUnitPhase2 (string pszIn, Tresult & u)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::ParseUnitPhase2(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    int iUnit = LookupUnit (pszIn);
    if (iUnit < 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseUnitPhase2(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
        return "????";
    }

    if (Infos [iUnit].Expr.empty ())
    {
        SetBasicUnit (u, 1.0, iUnit);
    }

    else
    {
        ExpandUnitExpr (u, Infos [iUnit].k, Infos [iUnit].Expr);
    }

    pszIn = pszIn.substr (Infos [iUnit].Abbr.size ());

InstrumentLogger::instance()->log_instrument_log("</Convert::ParseUnitPhase2(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
    return pszIn;
InstrumentLogger::instance()->log_instrument_log("</Convert::ParseUnitPhase2(string pszIn, Tresult & u)@@@ClassCRHM.cpp>");
}
bool Convert :: CheckUnitsTable ()
{
InstrumentLogger::instance()->log_instrument_log("<Convert::CheckUnitsTable()@@@ClassCRHM.cpp>");
    bool bSuccess = true;
    for (int i = 0; i < NumUnits - 1; ++ i) {
        const Unit_Info info1 = Infos [i];
        const Unit_Info info2 = Infos [i + 1];
        if (info1.Abbr.compare (info2.Abbr) >= 0)
        {
            bSuccess = false;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Convert::CheckUnitsTable()@@@ClassCRHM.cpp>");
    return bSuccess;
InstrumentLogger::instance()->log_instrument_log("</Convert::CheckUnitsTable()@@@ClassCRHM.cpp>");
}
void Convert :: CheckUnitsString (string Name, string variable, string units)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::CheckUnitsString(string Name, string variable, string units)@@@ClassCRHM.cpp>");
    string temp (units);
    units = tcsSqueeze (units);
    if (units.empty ())
    {

InstrumentLogger::instance()->log_instrument_log("</Convert::CheckUnitsString(string Name, string variable, string units)@@@ClassCRHM.cpp>");
        return;
    }

    Tresult uSrcUnit (NumBasicUnits);
    try {
        units = ParseDivUnitExpr (units, uSrcUnit);
        if (! units.empty ())
        {
            units = temp;
            throw 2;
        }

    }
    catch (int i) {
        if (i == 3)
        {
            CRHMException Except ("Units error ParseDivUnitExpr threw error code 3: '" + units + "' in " + Name + ' ' + variable, TExcept :: WARNING);
            LogError (Except);
        }

        else
        {
            CRHMException Except ("Units error ParseDivUnitExpr returned empty: '" + units + "' in " + Name + ' ' + variable, TExcept :: WARNING);
            LogError (Except);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Convert::CheckUnitsString(string Name, string variable, string units)@@@ClassCRHM.cpp>");
}
void Convert :: CheckUnitsObs (string Vunits, string Munits, string declaration)
{
InstrumentLogger::instance()->log_instrument_log("<Convert::CheckUnitsObs(string Vunits, string Munits, string declaration)@@@ClassCRHM.cpp>");
    double d;
    if (! Vunits.empty ())
    {
        if (! ConvertUnit (d, tcsSqueeze (Vunits), tcsSqueeze (Munits)) || d != 1.0)
        {
            CRHMException Except ("Units error: '" + Vunits + " instead of " + Munits + "' in " + declaration, TExcept :: WARNING);
            LogError (Except);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Convert::CheckUnitsObs(string Vunits, string Munits, string declaration)@@@ClassCRHM.cpp>");
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
ClassData :: ClassData (const ClassData & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::ClassData(const ClassData & Cl)@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</ClassData::ClassData(const ClassData & Cl)@@@ClassCRHM.cpp>");
}
ClassData & ClassData :: operator = (const ClassData & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<ClassData::operator=(const ClassData & Cl)@@@ClassCRHM.cpp>");
    if (this == & Cl)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassData::operator=(const ClassData & Cl)@@@ClassCRHM.cpp>");
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

InstrumentLogger::instance()->log_instrument_log("</ClassData::operator=(const ClassData & Cl)@@@ClassCRHM.cpp>");
    return * this;
InstrumentLogger::instance()->log_instrument_log("</ClassData::operator=(const ClassData & Cl)@@@ClassCRHM.cpp>");
}
void LogDebug (const char * S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(const char * S)@@@ClassCRHM.cpp>");
    string SS = S;
InstrumentLogger::instance()->log_instrument_log("</LogDebug(const char * S)@@@ClassCRHM.cpp>");
}
void LogDebug (const string S)
{
InstrumentLogger::instance()->log_instrument_log("<LogDebug(const string S)@@@ClassCRHM.cpp>");
    string SS = S;
InstrumentLogger::instance()->log_instrument_log("</LogDebug(const string S)@@@ClassCRHM.cpp>");
}