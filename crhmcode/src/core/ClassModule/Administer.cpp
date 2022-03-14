#include "Administer.h"
#include "../InstrumentLogger.h"

Administer :: Administer (string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::Administer(string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)@@@Administer.cpp>");
    DLLModuleList = new TStringList;
    DLLModelList = new TStringList;
    DLLModelModuleList = new TStringList;
    if (Global :: PendingDLLModuleList != NULL)
    {
        Global :: PendingDLLModuleList -> Clear ();
    }

InstrumentLogger::instance()->log_instrument_log("</Administer::Administer(string Version, string _HelpFile): Version (Version), HelpFile (_HelpFile)@@@Administer.cpp>");
}
Administer :: ~Administer ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::~Administer()@@@Administer.cpp>");
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii)
        delete ((ClassModule *) DLLModuleList -> array [ii].Object);
    delete DLLModuleList;
    delete DLLModelList;
    delete DLLModelModuleList;
InstrumentLogger::instance()->log_instrument_log("</Administer::~Administer()@@@Administer.cpp>");
}
void Administer :: MacroClear ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::MacroClear()@@@Administer.cpp>");
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii) {
        ClassModule * thisModule = (ClassModule *) DLLModuleList -> array [ii].Object;
        delete thisModule;
    }
    if (Global :: OurHelpList)
    {
        int indx = Global :: OurHelpList -> IndexOf (HelpFile);
        if (indx > - 1)
        {
            Global :: OurHelpList -> Delete (indx);
        }

    }

    DLLModuleList -> Clear ();
    DLLModelList -> Clear ();
    DLLModelModuleList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</Administer::MacroClear()@@@Administer.cpp>");
}
void Administer :: MacroUpdate ()
{
InstrumentLogger::instance()->log_instrument_log("<Administer::MacroUpdate()@@@Administer.cpp>");
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii) {
        int jj = Global :: OurModulesList -> IndexOf (DLLModuleList -> Strings [ii]);
        if (jj > - 1)
        {
            Global :: OurModulesList -> Objects [jj] = DLLModuleList -> Objects [ii];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Administer::MacroUpdate()@@@Administer.cpp>");
}
void Administer :: AddModule (ClassModule * Module)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::AddModule(ClassModule * Module)@@@Administer.cpp>");
    Module -> OurAdmin = this;
    DLLModuleList -> AddObject ((Module) -> Name.c_str (), (TObject *) Module);
    Global :: PendingDLLModuleList -> AddObject ((Module) -> Name.c_str (), (TObject *) Module);
InstrumentLogger::instance()->log_instrument_log("</Administer::AddModule(ClassModule * Module)@@@Administer.cpp>");
}
void Administer :: AddModel (string ModelName, string ModelModules)
{
InstrumentLogger::instance()->log_instrument_log("<Administer::AddModel(string ModelName, string ModelModules)@@@Administer.cpp>");
    DLLModelModuleList -> Add (ModelModules);
    long long _object = (long long) DLLModelModuleList -> Count - 1;
    DLLModelList -> AddObject (ModelName, (TObject *) _object);
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
    for (int ii = 0; ii < DLLModuleList -> Count; ++ ii) {
        if (Global :: PendingDLLModuleList -> Count > 0 && Global :: PendingDLLModuleList -> IndexOf (DLLModuleList -> Strings [ii]) == - 1)
        {
            continue;
        }

        int jj = Global :: AllModulesList -> IndexOf (DLLModuleList -> Strings [ii]);
        if (jj != - 1)
        {
            Exists = "Over-write existing module \"";
        }

        else
        {
            Exists = "Load Module \"";
        }

        if (Global :: AllModulesList -> IndexOf (DLLModuleList -> Strings [ii]) == - 1 && Global :: OurModulesList -> IndexOf (DLLModuleList -> Strings [ii]) != - 1)
        {
            Result = mbYes;
        }

        switch (Result) {
        case mbYes:
        case mbYesToAll:
            if (jj != - 1)
            {
                LogError (CRHMException ((DLLModuleList -> Strings [ii] + " module being replaced").c_str (), TExcept :: WARNING));
                Global :: AllModulesList -> Delete (jj);
            }

            thisModule = (ClassModule *) DLLModuleList -> Objects [ii];
            thisModule -> DLLName = DLLName;
            if (thisModule -> DLLName != "Macro")
            {
                thisModule -> ID = typeid (* thisModule).name ();
            }

            Global :: AllModulesList -> AddObject (DLLModuleList -> Strings [ii], (TObject *) DLLModuleList -> Objects [ii]);
            break;
        case mbNo:
        case mbNoToAll:
            continue;
        default:
            break;
        }
    }
    for (int ii = 0; ii < DLLModelList -> Count; ++ ii) {
        long long _object = ii;
        Global :: AllModelsList -> AddObject (DLLModelList -> Strings [ii], (TObject *) _object);
        Global :: ModelModulesList -> AddObject (DLLModelModuleList -> Strings [ii], (TObject *) this);
    }
    if (Global :: OurHelpList)
    {
        if (Global :: OurHelpList -> IndexOf (HelpFile) < 0)
        {
            Global :: OurHelpList -> AddObject (HelpFile, (TObject *) 1);
        }

        else
        {
            Global :: OurHelpList -> AddObject (HelpFile, (TObject *) 0);
        }

    }

    Global :: PendingDLLModuleList -> Clear ();
InstrumentLogger::instance()->log_instrument_log("</Administer::Accept(int Result)@@@Administer.cpp>");
}