#include "ClassNOP.h"
#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "../../core/InstrumentLogger.h"

using namespace CRHM;
ClassNOP * ClassNOP :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassNOP::klone(string name) const@@@ClassNOP.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassNOP::klone(string name) const@@@ClassNOP.cpp>");
    return new ClassNOP (name);
InstrumentLogger::instance()->log_instrument_log("</ClassNOP::klone(string name) const@@@ClassNOP.cpp>");
}
void ClassNOP :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNOP::decl(void)@@@ClassNOP.cpp>");
    Description = "'NO operation module. Use only in macro declstruct as filler.'";
InstrumentLogger::instance()->log_instrument_log("</ClassNOP::decl(void)@@@ClassNOP.cpp>");
}
void ClassNOP :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNOP::init(void)@@@ClassNOP.cpp>");
InstrumentLogger::instance()->log_instrument_log("</ClassNOP::init(void)@@@ClassNOP.cpp>");
}
void ClassNOP :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNOP::finish(bool good)@@@ClassNOP.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessage (hh, string ("'" + Name + " (NOP)'").c_str (), TExtra :: BLANK);
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassNOP::finish(bool good)@@@ClassNOP.cpp>");
}