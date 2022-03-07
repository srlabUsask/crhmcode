#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Class3D_param.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Class3D_param * Class3D_param :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Class3D_param::klone(string name) const@@@Class3D_param.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Class3D_param::klone(string name) const@@@Class3D_param.cpp>");
    return new Class3D_param (name);
InstrumentLogger::instance()->log_instrument_log("</Class3D_param::klone(string name) const@@@Class3D_param.cpp>");
}
void Class3D_param :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Class3D_param::decl(void)@@@Class3D_param.cpp>");
    Description = "'Initialises the variable \"Param_3D\" from the parameter \"Var_3D\".'";
    declvar ("Var_3D", TDim :: NHRU, "Var_3D", "()", & Var_3D);
    declparam ("Param_3D", TDim :: NHRU, "[0.17]", "0.0", "1.0", "Param_3D", "()", & Param_3D);
InstrumentLogger::instance()->log_instrument_log("</Class3D_param::decl(void)@@@Class3D_param.cpp>");
}
void Class3D_param :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Class3D_param::init(void)@@@Class3D_param.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Var_3D [hh] = Param_3D [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Class3D_param::init(void)@@@Class3D_param.cpp>");
}
void Class3D_param :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Class3D_param::run(void)@@@Class3D_param.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Class3D_param::run(void)@@@Class3D_param.cpp>");
}
void Class3D_param :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Class3D_param::finish(bool good)@@@Class3D_param.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        string s = "'" + Name + " (3D_param)' ";
        LogMessage (hh, s.c_str ());
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</Class3D_param::finish(bool good)@@@Class3D_param.cpp>");
}