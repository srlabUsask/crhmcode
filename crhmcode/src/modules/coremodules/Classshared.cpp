#include "Classshared.h"
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
Classshared * Classshared :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classshared::klone(string name) const@@@Classshared.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classshared::klone(string name) const@@@Classshared.cpp>");
    return new Classshared (name);
InstrumentLogger::instance()->log_instrument_log("</Classshared::klone(string name) const@@@Classshared.cpp>");
}
void Classshared :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classshared::decl(void)@@@Classshared.cpp>");
    Description = "'System module only. NEVER use!'";
InstrumentLogger::instance()->log_instrument_log("</Classshared::decl(void)@@@Classshared.cpp>");
}
void Classshared :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classshared::init(void)@@@Classshared.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Classshared::init(void)@@@Classshared.cpp>");
}