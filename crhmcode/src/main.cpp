#include "core/CRHMArguments.h"

int main (int argc, char * argv [])
{
InstrumentLogger::instance()->log_instrument_log("<main(int argc, char * argv [])@@@main.cpp>");
    CRHMArguments * arguments = new CRHMArguments ();
    arguments -> readCommandLine (argc, argv);
    arguments -> validate ();
    CRHMmain * m = new CRHMmain (arguments);
    std :: string projectArgument = arguments -> get_project_name ();
    m -> OpenNamePrj = projectArgument;
    m -> DoPrjOpen (projectArgument, "");
    m -> RunClick ();
InstrumentLogger::instance()->log_instrument_log("</main(int argc, char * argv [])@@@main.cpp>");
}