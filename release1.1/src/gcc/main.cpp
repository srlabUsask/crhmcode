#include <stdio.h>
#include "CRHMmain.h"

int main (int argc, char * argv [])
{
InstrumentLogger::instance()->log_instrument_log("<main(int argc, char * argv [])@@@main.cpp>");
    CRHMmain * m = new CRHMmain ();
    m -> FormCreate ();
    m -> DoPrjOpen (argv [1], "");
    m -> RunClick ();
InstrumentLogger::instance()->log_instrument_log("</main(int argc, char * argv [])@@@main.cpp>");
}