#include "HierarchyDlg.h"
#include "../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (HierarchyDlg, CDialog)
HierarchyDlg :: HierarchyDlg (CWnd * pParent): CDialog (ID_HIERARCHY_DLG, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::HierarchyDlg(CWnd * pParent): CDialog (ID_HIERARCHY_DLG, pParent)@@@HierarchyDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::HierarchyDlg(CWnd * pParent): CDialog (ID_HIERARCHY_DLG, pParent)@@@HierarchyDlg.cpp>");
}
HierarchyDlg :: ~HierarchyDlg ()
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::~HierarchyDlg()@@@HierarchyDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::~HierarchyDlg()@@@HierarchyDlg.cpp>");
}
void HierarchyDlg :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::DoDataExchange(CDataExchange * pDX)@@@HierarchyDlg.cpp>");
    CDialog :: DoDataExchange (pDX);
    DDX_Control (pDX, ID_HIERARCHY_CHECK, hierarchyCheck);
    DDX_Control (pDX, ID_HIERARCHY_LIST, hierarchyList);
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::DoDataExchange(CDataExchange * pDX)@@@HierarchyDlg.cpp>");
}BEGIN_MESSAGE_MAP (HierarchyDlg, CDialog)
END_MESSAGE_MAP ()

BOOL HierarchyDlg :: OnInitDialog ()
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::OnInitDialog()@@@HierarchyDlg.cpp>");
    CDialog :: OnInitDialog ();
    Hierarchy1Click ();

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::OnInitDialog()@@@HierarchyDlg.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::OnInitDialog()@@@HierarchyDlg.cpp>");
}
void HierarchyDlg :: Hierarchy1Click ()
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::Hierarchy1Click()@@@HierarchyDlg.cpp>");
    ClassModule * thisModule;
    ClassMacro * thisMacro;
    long Variation;
    this -> hierarchyList.ResetContent ();
    this -> hierarchyCheck.ResetContent ();
    HierarchyList ();
    for (static std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        std :: string S = it -> first;
        thisModule = it -> second;
        if (thisModule -> DLLName == "Macro")
        {
            thisMacro = dynamic_cast < ClassMacro * > (thisModule);
            if (thisModule -> isGroup)
            {
                hierarchyList.AddString (L"");
                hierarchyList.AddString (CString (S.c_str ()));
                hierarchyList.AddString (L"");
                hierarchyCheck.AddString (L" ");
                hierarchyCheck.AddString (CString (S.c_str ()));
                hierarchyCheck.AddString (L" ");
                std :: list < std :: pair < std :: string, ClassModule * >> * GrpModuleList = new std :: list < std :: pair < std :: string, ClassModule * >> ();
                std :: list < std :: pair < std :: string, ClassModule * >> * TempModuleList = new std :: list < std :: pair < std :: string, ClassModule * >> ();
                unsigned short * Oldvariation = new unsigned short [thisMacro -> GrpStringList -> size ()];
                for (size_t ii = 0; ii < thisMacro -> GrpStringList -> size (); ii ++) {
                    GrpModuleList -> push_back (thisMacro -> GrpStringList -> at (ii));
                }
                size_t loopCount = 0;
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator ii = GrpModuleList -> begin (); ii != GrpModuleList -> end (); ii ++) {
                    int Pos = ii -> first.find ("#");
                    if (Pos)
                    {
                        Variation = (long) pow (2, ii -> first [Pos + 1] - char ('1'));
                        ii -> first = ii -> first.substr (1, Pos - 1);
                    }

                    else
                    {
                        Variation = 0;
                    }

                    std :: map < std :: string, ClassModule * > :: iterator jj = Global :: AllModulesList -> find (ii -> first);
                    if (jj != Global :: AllModulesList -> end ())
                    {
                        ii -> second = jj -> second;
                        ClassModule * thisModule = ii -> second;
                        if (loopCount <= GrpModuleList -> size ())
                        {
                            Oldvariation [loopCount] = thisModule -> variation;
                        }

                        thisModule -> variation = (unsigned short) Variation;
                    }

                    loopCount ++;
                }
                Global :: Mapgetvar.clear ();
                Global :: Mapputvar.clear ();
                Global :: Mapreadvar.clear ();
                Global :: Mapdeclvar.clear ();
                Global :: Mapdeclstat.clear ();
                Global :: Mapdeclpar.clear ();
                Global :: Mapdeclobs.clear ();
                Global :: BuildFlag = TBuild :: BUILD;
                TempModuleList -> assign (Global :: OurModulesList -> begin (), Global :: OurModulesList -> end ());
                Global :: OurModulesList -> assign (GrpModuleList -> begin (), GrpModuleList -> end ());
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator ii = Global :: OurModulesList -> begin (); ii != Global :: OurModulesList -> end (); ii ++) {
                    ii -> second -> decl ();
                }
                HierarchyList ();
                int loopCount2 = 0;
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator ii = GrpModuleList -> begin (); ii != GrpModuleList -> end (); ii ++) {
                    ClassModule * thisModule = ii -> second;
                    thisModule -> variation = (unsigned short) Oldvariation [loopCount2];
                    loopCount2 ++;
                }
                Global :: OurModulesList -> assign (TempModuleList -> begin (), TempModuleList -> end ());
                Global :: Mapgetvar.clear ();
                Global :: Mapputvar.clear ();
                Global :: Mapreadvar.clear ();
                Global :: Mapdeclvar.clear ();
                Global :: Mapdeclstat.clear ();
                Global :: Mapdeclpar.clear ();
                Global :: Mapdeclobs.clear ();
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator ii = Global :: OurModulesList -> begin (); ii != Global :: OurModulesList -> end (); ii ++) {
                    ii -> second -> decl ();
                }
                Global :: BuildFlag = TBuild :: DECL;
                delete GrpModuleList;
                delete TempModuleList;
                delete [] Oldvariation;
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::Hierarchy1Click()@@@HierarchyDlg.cpp>");
}
void HierarchyDlg :: HierarchyList ()
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::HierarchyList()@@@HierarchyDlg.cpp>");
    std :: string S, SS, S1, S2, Entry;
    bool Self;
    long offset, Act_ii;
    std :: pair < std :: string, ClassModule * > * Indx = NULL;
    offset = hierarchyList.GetCount ();
    pair < Mapstr :: iterator, Mapstr :: iterator > range;
    Mapstr :: iterator itMap;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        ClassModule * thisModule = it -> second;
        long Variation = thisModule -> variation;
        std :: string S = it -> first;
        if (thisModule -> DLLName == "Macro")
        {
            Expand_Grp_to_OurModuleList (it -> first, it -> second);
        }

        std :: string AA = "";
        if (Variation)
        {
            AA = "#0";
            AA [1] += (char) (log (thisModule -> variation) / log (2) + 1);
        }

        std :: string stringToAdd = S + AA;
        CString textToAdd (stringToAdd.c_str ());
        this -> hierarchyList.AddString (textToAdd);
        Act_ii = this -> hierarchyList.GetCount () - 1;
        if (! thisModule -> PeerVar.empty ())
        {
            S1 = thisModule -> NameRoot.c_str ();
            S2 = thisModule -> PeerVar.c_str ();
            Indx = findvar (S, S2, Self);
            if (Indx != NULL)
            {
                std :: pair < std :: string, ClassModule * > * Indx2 = findstatvar (S, S2, Self);
                Entry = S + " " + Indx -> first + "->" + S2 + " *** Peer Variable";
                if (Indx2 == NULL)
                {
                    int i = 0;
                }

                else
                {
                    Entry = Entry + " *** Peer Variable";
                }

                hierarchyCheck.AddString (CString (Entry.c_str ()));
            }

        }

        range = Global :: Mapgetvar.equal_range (S);
        for (itMap = range.first; itMap != range.second; ++ itMap) {
            SS = itMap -> second.first;
            int jj = SS.find (" ");
            S1 = SS.substr (1, jj - 1);
            S2 = SS.substr (jj + 1, SS.length () - jj);
            if (S1 == "*")
            {
                Indx = findvar (S, S2, Self);
            }

            else
            {
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                    if (S1 == it -> first)
                    {
                        Indx = new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                    }

                }
            }

            if (Indx != NULL)
            {
                std :: pair < std :: string, ClassModule * > * Indx2 = findstatvar (S, S2, Self);
                Entry = S + " " + itMap -> second.first + " from " + Indx -> first;
                if (Indx2 == NULL)
                {
                    int i = 0;
                }

                else
                {
                    Entry = Entry + " *** State Variable";
                }

                hierarchyCheck.AddString (CString (Entry.c_str ()));
            }

        }
        range = Global :: Mapputvar.equal_range (S);
        for (itMap = range.first; itMap != range.second; ++ itMap) {
            SS = itMap -> second.first;
            int jj = SS.find (" ");
            S1 = SS.substr (1, jj - 1);
            S2 = SS.substr (jj + 1, SS.length () - jj);
            if (S1 == "*")
            {
                Indx = findvar (S, S2, Self);
            }

            else
            {
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                    if (S1 == it -> first)
                    {
                        Indx = new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                    }

                }
            }

            if (Indx != NULL)
            {
                std :: string textString = S + " " + itMap -> second.first + " from " + Indx -> first + " *** Put";
                hierarchyCheck.AddString (CString (textString.c_str ()));
            }

        }
    }
    bool OK = true;
    int ii = 0;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        int i = 0;
        int Twos = 0;
        int N = (int) powl (2, ii);
        if (Twos > N)
        {
            OK = false;
        }

        ii ++;
    }
    hierarchyList.AddString (CString (" "));
    if (OK)
    {
        hierarchyList.AddString (L"Module order is good");
    }

    else
    {
        hierarchyList.AddString (L"Module Order is not correct");
    }

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::HierarchyList()@@@HierarchyDlg.cpp>");
}
void HierarchyDlg :: Expand_Grp_to_OurModuleList (std :: string moduleName, ClassModule * module)
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::Expand_Grp_to_OurModuleList(std :: string moduleName, ClassModule * module)@@@HierarchyDlg.cpp>");
    ClassModule * thisModule;
    ClassMacro * thisMacro;
    long Variation;
    std :: string S = moduleName;
    thisModule = module;
    thisMacro = dynamic_cast < ClassMacro * > (thisModule);
    if (thisMacro -> GrpStringList == NULL || thisMacro -> GrpStringList -> size () <= 0)
    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::Expand_Grp_to_OurModuleList(std :: string moduleName, ClassModule * module)@@@HierarchyDlg.cpp>");
        return;
    }

    std :: list < std :: pair < std :: string, ClassModule * >> * GrpModuleList = new std :: list < std :: pair < std :: string, ClassModule * >> ();
    std :: vector < std :: pair < std :: string, ClassModule * >> * TempModuleList = new std :: vector < std :: pair < std :: string, ClassModule * >> ();
    long * Oldvariation = new long [thisMacro -> GrpStringList -> size ()];
    for (size_t ii = 0; ii < thisMacro -> GrpStringList -> size (); ii ++) {
        GrpModuleList -> push_back (thisMacro -> GrpStringList -> at (ii));
    }
    int ii = 0;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator grpModuleListIt = GrpModuleList -> begin (); grpModuleListIt != GrpModuleList -> end (); grpModuleListIt ++) {
        int Pos = grpModuleListIt -> first.find_first_of ("#");
        if (Pos)
        {
            Variation = (long) pow (2, grpModuleListIt -> first [Pos + 1] - char ('1'));
            grpModuleListIt -> first = grpModuleListIt -> first.substr (1, Pos - 1);
        }

        else
        {
            Variation = 0;
        }

        std :: map < std :: string, ClassModule * > :: iterator jj = Global :: AllModulesList -> find (grpModuleListIt -> first);
        if (jj != Global :: AllModulesList -> end ())
        {
            grpModuleListIt -> second = jj -> second;
            ClassModule * thisModule = (ClassModule *) grpModuleListIt -> second;
            Oldvariation [ii] = thisModule -> variation;
            thisModule -> variation = (unsigned short) Variation;
        }

        ii ++;
    }
    Global :: Mapgetvar.clear ();
    Global :: Mapputvar.clear ();
    Global :: Mapreadvar.clear ();
    Global :: Mapdeclvar.clear ();
    Global :: Mapdeclstat.clear ();
    Global :: Mapdeclpar.clear ();
    Global :: Mapdeclobs.clear ();
    Global :: BuildFlag = TBuild :: BUILD;
    TempModuleList -> assign (Global :: OurModulesList -> begin (), Global :: OurModulesList -> end ());
    Global :: OurModulesList -> assign (GrpModuleList -> begin (), GrpModuleList -> end ());
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator ourModListIt = Global :: OurModulesList -> begin (); ourModListIt != Global :: OurModulesList -> end (); ourModListIt ++) {
        ourModListIt -> second -> decl ();
    }
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator grpModListIt = GrpModuleList -> begin (); grpModListIt != GrpModuleList -> end (); grpModListIt ++) {
        ClassModule * thisModule = grpModListIt -> second;
        thisModule -> variation = (unsigned short) Oldvariation [ii];
    }
    Global :: OurModulesList -> assign (TempModuleList -> begin (), TempModuleList -> end ());
    Global :: Mapgetvar.clear ();
    Global :: Mapputvar.clear ();
    Global :: Mapreadvar.clear ();
    Global :: Mapdeclvar.clear ();
    Global :: Mapdeclstat.clear ();
    Global :: Mapdeclpar.clear ();
    Global :: Mapdeclobs.clear ();
    Global :: BuildFlag = TBuild :: DECL;
    delete GrpModuleList;
    delete TempModuleList;
    delete [] Oldvariation;
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::Expand_Grp_to_OurModuleList(std :: string moduleName, ClassModule * module)@@@HierarchyDlg.cpp>");
}
std :: pair < std :: string, ClassModule * > * HierarchyDlg :: findvar (std :: string who, std :: string what, bool & Self)
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
    Mapstr :: iterator itMap;
    int Pos;
    std :: string S1, S2;
    std :: list < std :: pair < std :: string, ClassModule * >> :: iterator GrpSrc = Global :: OurModulesList -> end ();
    for (itMap = Global :: Mapdeclvar.begin (); itMap != Global :: Mapdeclvar.end (); ++ itMap) {
        if (itMap -> second.first == what)
        {
            if (itMap -> first == who)
            {
                Self = true;

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
                return NULL;
            }

            else
            {
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                    if (itMap -> first == it -> first)
                    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
                        return new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                    }

                }
            }

        }

    }
    for (itMap = Global :: Mapdeclvar.begin (); itMap != Global :: Mapdeclvar.end (); ++ itMap) {
        Pos = what.find ("@");
        if (Pos != std :: string :: npos)
        {
            S1 = what.substr (1, Pos - 1);
            if (itMap -> second.first == S1)
            {
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                    if (itMap -> first == it -> first)
                    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
                        return new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                    }

                }
            }

        }

        else
        {
            S1 = what;
        }

        Pos = itMap -> second.first.find ("@");
        if (Pos == std :: string :: npos)
        {
            S2 = itMap -> second.first.substr (1, Pos - 1);
            if (S1 == S2)
            {
                if (itMap -> second.first == what)
                {
                    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                        if (itMap -> first == it -> first)
                        {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
                            return new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                        }

                    }
                }

                else
                {
                    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                        if (itMap -> first == it -> first)
                        {
                            GrpSrc = it;
                        }

                    }
                }

            }

        }

    }
    if (GrpSrc != Global :: OurModulesList -> end ())
    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
        return new std :: pair < std :: string, ClassModule * > (GrpSrc -> first, GrpSrc -> second);
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
        return NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
}
std :: pair < std :: string, ClassModule * > * HierarchyDlg :: findstatvar (std :: string who, std :: string what, bool & Self)
{
InstrumentLogger::instance()->log_instrument_log("<HierarchyDlg::findstatvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
    Mapstr :: iterator itMap;
    int Pos;
    std :: string S1, S2;
    for (itMap = Global :: Mapdeclstat.begin (); itMap != Global :: Mapdeclstat.end (); ++ itMap) {
        std :: string SS = itMap -> second.first;
        int jj = SS.find (" ");
        std :: string S2 = SS.substr (jj + 1, SS.length () - jj);
        if (S2 == what)
        {
            if (itMap -> first == who)
            {
                Self = true;
            }

            else
            {
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                    if (itMap -> first == it -> first)
                    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findstatvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
                        return new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                    }

                }
            }

        }

        if (Pos = what.find ("@"))
        {
            S1 = what.substr (1, Pos - 1);
            if (S2 == S1)
            {
                for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
                    if (itMap -> first == it -> first)
                    {

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findstatvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
                        return new std :: pair < std :: string, ClassModule * > (it -> first, it -> second);
                    }

                }
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findstatvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
    return NULL;
InstrumentLogger::instance()->log_instrument_log("</HierarchyDlg::findstatvar(std :: string who, std :: string what, bool & Self)@@@HierarchyDlg.cpp>");
}