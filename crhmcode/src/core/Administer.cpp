#include "Administer.h"
#include "InstrumentLogger.h"

Administer :: Administer (string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::Administer(string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)@@@Administer.cpp>");
    DLLModuleList = new std :: vector < std :: pair < std :: string, ClassModule * >> ();
    DLLModelList = new std :: vector < std :: pair < std :: string, int >> ();
    DLLModelModuleList = new std :: vector < std :: string > ();
    if (Global :: PendingDLLModuleList != NULL)
    {
        Global :: PendingDLLModuleList -> clear ();
    }

InstrumentLogger::instance()->log_instrument_log("</Administer::Administer(string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)@@@Administer.cpp>");
}
Administer :: ~Administer ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::~Administer()@@@Administer.cpp>");
    for (size_t ii = 0; ii < DLLModuleList -> size (); ++ ii) {
        delete DLLModuleList -> at (ii).second;
    }
    delete DLLModuleList;
    delete DLLModelList;
    delete DLLModelModuleList;
InstrumentLogger::instance()->log_instrument_log("</Administer::~Administer()@@@Administer.cpp>");
}
void Administer :: MacroClear ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::MacroClear()@@@Administer.cpp>");
    for (size_t ii = 0; ii < DLLModuleList -> size (); ++ ii) {
        ClassModule * thisModule = DLLModuleList -> at (ii).second;
        delete thisModule;
    }
    if (Global :: OurHelpList)
    {
        std :: map < std :: string, int > :: iterator indx = Global :: OurHelpList -> find (HelpFile);
        if (indx != Global :: OurHelpList -> end ())
        {
            Global :: OurHelpList -> erase (indx);
        }

    }

    DLLModuleList -> clear ();
    DLLModelList -> clear ();
    DLLModelModuleList -> clear ();
InstrumentLogger::instance()->log_instrument_log("</Administer::MacroClear()@@@Administer.cpp>");
}
void Administer :: MacroUpdate ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::MacroUpdate()@@@Administer.cpp>");
    for (size_t ii = 0; ii < DLLModuleList -> size (); ++ ii) {
        std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos;
        bool moduleFound = false;
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
            if (it -> first == DLLModelList -> at (ii).first)
            {
                moduleFound = true;
                pos = it;
            }

        }
        if (moduleFound)
        {
            pos -> second = DLLModuleList -> at (ii).second;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Administer::MacroUpdate()@@@Administer.cpp>");
}
void Administer :: AddModule (ClassModule * Module)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::AddModule(ClassModule * Module)@@@Administer.cpp>");
    Module -> OurAdmin = this;
    DLLModuleList -> push_back (std :: pair < std :: string, ClassModule * > (Module -> Name.c_str (), Module));
    Global :: PendingDLLModuleList -> push_back (std :: pair < std :: string, ClassModule * > ((Module) -> Name.c_str (), Module));
InstrumentLogger::instance()->log_instrument_log("</Administer::AddModule(ClassModule * Module)@@@Administer.cpp>");
}
void Administer :: AddModel (string ModelName, string ModelModules)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::AddModel(string ModelName, string ModelModules)@@@Administer.cpp>");
    DLLModelModuleList -> push_back (ModelModules);
    int _object = DLLModelModuleList -> size () - 1;
    DLLModelList -> push_back (std :: pair < std :: string, int > (ModelName, _object));
InstrumentLogger::instance()->log_instrument_log("</Administer::AddModel(string ModelName, string ModelModules)@@@Administer.cpp>");
}
void Administer :: LoadCRHM (string DllName)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::LoadCRHM(string DllName)@@@Administer.cpp>");
    DLLName = DllName;
InstrumentLogger::instance()->log_instrument_log("</Administer::LoadCRHM(string DllName)@@@Administer.cpp>");
}
void Administer :: Accept (int Result)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::Accept(int Result)@@@Administer.cpp>");
    string Exists;
    ClassModule * thisModule;
    for (size_t ii = 0; ii < DLLModuleList -> size (); ++ ii) {
        bool foundInPending = false;
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: PendingDLLModuleList -> begin (); it != Global :: PendingDLLModuleList -> end (); it ++) {
            if (it -> first == DLLModuleList -> at (ii).first)
            {
                foundInPending = true;
            }

        }
        if (Global :: PendingDLLModuleList -> size () != 0 && foundInPending == false)
        {
            continue;
        }

        int jj = Global :: AllModulesList -> count (DLLModuleList -> at (ii).first);
        if (jj != 0)
        {
            Exists = "Over-write existing module \"";
        }

        else
        {
            Exists = "Load Module \"";
        }

        bool inOurModulesList = false;
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
            if (it -> first == DLLModelList -> at (ii).first)
            {
                inOurModulesList = true;
            }

        }
        if (Global :: AllModulesList -> count (DLLModuleList -> at (ii).first) == 0 && inOurModulesList)
        {
            Result = mbYes;
        }

        switch (Result) {
        case mbYes:
        case mbYesToAll:
            if (jj != 0)
            {
                LogError (CRHMException ((DLLModuleList -> at (ii).first + " module being replaced").c_str (), TExcept :: WARNING));
                Global :: AllModulesList -> erase (DLLModuleList -> at (ii).first);
            }

            thisModule = DLLModuleList -> at (ii).second;
            thisModule -> DLLName = DLLName;
            if (thisModule -> DLLName != "Macro")
            {
                thisModule -> ID = typeid (* thisModule).name ();
            }

            Global :: AllModulesList -> insert (std :: pair < std :: string, ClassModule * > (DLLModuleList -> at (ii).first, DLLModuleList -> at (ii).second));
            break;
        case mbNo:
        case mbNoToAll:
            continue;
        default:
            break;
        }
    }
    for (size_t ii = 0; ii < DLLModelList -> size (); ++ ii) {
        int _object = ii;
        Global :: AllModelsList -> push_back (std :: pair < std :: string, int > (DLLModelList -> at (ii).first, _object));
        Global :: ModelModulesList -> push_back (std :: pair < std :: string, Administer * > (DLLModelModuleList -> at (ii), this));
    }
    if (Global :: OurHelpList)
    {
        if (Global :: OurHelpList -> count (HelpFile) != 0)
        {
            Global :: OurHelpList -> insert (std :: pair < std :: string, int > (HelpFile, 1));
        }

        else
        {
            Global :: OurHelpList -> insert (std :: pair < std :: string, int > (HelpFile, 0));
        }

    }

    Global :: PendingDLLModuleList -> clear ();
InstrumentLogger::instance()->log_instrument_log("</Administer::Accept(int Result)@@@Administer.cpp>");
}