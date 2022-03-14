#include "Classalbedoparam.h"
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
Classalbedoparam * Classalbedoparam :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoparam::klone(string name) const@@@Classalbedoparam.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classalbedoparam::klone(string name) const@@@Classalbedoparam.cpp>");
    return new Classalbedoparam (name);
InstrumentLogger::instance()->log_instrument_log("</Classalbedoparam::klone(string name) const@@@Classalbedoparam.cpp>");
}
void Classalbedoparam :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoparam::decl(void)@@@Classalbedoparam.cpp>");
    Description = "'Initialises the variable \"Albedo\" from the parameter \"Albedo_Value\".'";
    declvar ("Albedo", TDim :: NHRU, "Albedo", "()", & Albedo);
    declparam ("Albedo_Value", TDim :: NHRU, "[0.17]", "0.0", "1.0", "Albedo", "()", & Albedo_Value);
InstrumentLogger::instance()->log_instrument_log("</Classalbedoparam::decl(void)@@@Classalbedoparam.cpp>");
}
void Classalbedoparam :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoparam::init(void)@@@Classalbedoparam.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Albedo [hh] = Albedo_Value [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Classalbedoparam::init(void)@@@Classalbedoparam.cpp>");
}
void Classalbedoparam :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoparam::run(void)@@@Classalbedoparam.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Classalbedoparam::run(void)@@@Classalbedoparam.cpp>");
}