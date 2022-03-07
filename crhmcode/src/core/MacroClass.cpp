#include "ClassCRHM.h"
#include "Classfilter.h"
#include "InstrumentLogger.h"

void MacroClass :: addfilter (string Line)
{
InstrumentLogger::instance()->log_instrument_log("<MacroClass::addfilter(string Line)@@@MacroClass.cpp>");
    Classfilter * NewFilter;
    std :: string S = Line.substr (1, Common :: trim (Line).length ());
    if (Line.substr (1, 1) == "$")
    {

InstrumentLogger::instance()->log_instrument_log("</MacroClass::addfilter(string Line)@@@MacroClass.cpp>");
        return;
    }

    long bb = S.find ('(');
    long ee;
    ee = S.find_first_of (" \t");
    std :: string ToVar = "";
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
    std :: string Filter = S.substr (0, ee);
    std :: string FilterStuff = S.substr (ee);
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

InstrumentLogger::instance()->log_instrument_log("</MacroClass::addfilter(string Line)@@@MacroClass.cpp>");
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
        std :: string Mess = "Filter: '" + Filter + "' name not recognised";

InstrumentLogger::instance()->log_instrument_log("</MacroClass::addfilter(string Line)@@@MacroClass.cpp>");
        return;
    }

    if (! NewFilter -> Error)
    {
        FilterList -> push_back (std :: pair < std :: string, Classfilter * > (Filter, NewFilter));
    }

    else
    {
        delete NewFilter;
    }

InstrumentLogger::instance()->log_instrument_log("</MacroClass::addfilter(string Line)@@@MacroClass.cpp>");
}
void MacroClass :: execute (long Line)
{
InstrumentLogger::instance()->log_instrument_log("<MacroClass::execute(long Line)@@@MacroClass.cpp>");
    for (size_t ii = 0; ii < FilterList -> size (); ii ++) {
        FilterList -> at (ii).second -> doFunctions (Line);
    }
InstrumentLogger::instance()->log_instrument_log("</MacroClass::execute(long Line)@@@MacroClass.cpp>");
}
void MacroClass :: fixup (void)
{
InstrumentLogger::instance()->log_instrument_log("<MacroClass::fixup(void)@@@MacroClass.cpp>");
    for (size_t ii = 0; ii < FilterList -> size (); ii ++) {
        FilterList -> at (ii).second -> fixup ();
    }
InstrumentLogger::instance()->log_instrument_log("</MacroClass::fixup(void)@@@MacroClass.cpp>");
}
MacroClass :: MacroClass (ClassData * File): File (File), Interpolation (0)
{
InstrumentLogger::instance()->log_instrument_log("<MacroClass::MacroClass(ClassData * File): File (File), Interpolation (0)@@@MacroClass.cpp>");
    FilterList = new std :: vector < std :: pair < std :: string, Classfilter * >> ();
InstrumentLogger::instance()->log_instrument_log("</MacroClass::MacroClass(ClassData * File): File (File), Interpolation (0)@@@MacroClass.cpp>");
}
MacroClass :: ~MacroClass ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroClass::~MacroClass()@@@MacroClass.cpp>");
    if (Interpolation > 0 && (long) FilterList -> size () > Interpolation)
    {
        LogError ("Filter execution occurs before interpolation -> values may be incorrect." + File -> DataFileName, TExcept :: WARNING);
    }

    delete FilterList;
InstrumentLogger::instance()->log_instrument_log("</MacroClass::~MacroClass()@@@MacroClass.cpp>");
}