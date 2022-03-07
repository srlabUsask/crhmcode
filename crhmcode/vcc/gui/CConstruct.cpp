#include "CConstruct.h"
#include "CConstructCore.h"
#include "../../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (CConstruct, CDialog)
CConstruct :: CConstruct (CWnd * pParent): CDialog (CONSTRUCT_DLG, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::CConstruct(CWnd * pParent): CDialog (CONSTRUCT_DLG, pParent)@@@CConstruct.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CConstruct::CConstruct(CWnd * pParent): CDialog (CONSTRUCT_DLG, pParent)@@@CConstruct.cpp>");
}
CConstruct :: ~CConstruct ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::~CConstruct()@@@CConstruct.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CConstruct::~CConstruct()@@@CConstruct.cpp>");
}
void CConstruct :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::DoDataExchange(CDataExchange * pDX)@@@CConstruct.cpp>");
    CDialog :: DoDataExchange (pDX);
    DDX_Control (pDX, ID_ALL_MODS_LIST_BOX, listbox_available_modules);
    listbox_available_modules.setMessageCode (UWM_OPEN_CTX_AVAILABLE_MODS);
    DDX_Control (pDX, ID_SEL_MODS_LIST_BOX, listbox_selected_modules);
    listbox_selected_modules.setMessageCode (UWM_OPEN_CTX_SELECTED_MODS);
    DDX_Control (pDX, ID_MODULE_FILTER_BASIC, module_filter_basic);
    DDX_Control (pDX, ID_MODULE_FILTER_MACRO, module_filter_macro);
    DDX_Control (pDX, ID_MODULE_FILTER_ADVANCED, module_filter_advanced);
    DDX_Control (pDX, ID_MODULE_FILTER_SUPPORT, module_filter_support);
    DDX_Control (pDX, ID_MODULE_FILTER_CUSTOM, module_filter_custom);
    DDX_Control (pDX, ID_MODULE_FILTER_PROTOTYPE, module_filter_prototype);
    DDX_Control (pDX, ID_MODULE_FILTER_OBSOLETE, module_filter_obsolete);
    DDX_Control (pDX, IDC_LIST3, listcontrol);
    DDX_Control (pDX, ID_MAX_HRU_SPIN, max_HRU_spin);
    DDX_Control (pDX, ID_MAX_LAYER_SPIN, max_layer_spin);
InstrumentLogger::instance()->log_instrument_log("</CConstruct::DoDataExchange(CDataExchange * pDX)@@@CConstruct.cpp>");
}BEGIN_MESSAGE_MAP (CConstruct, CDialog)
    ON_BN_CLICKED (ID_CONSTRUCT_CHECK_BUTTON, & CConstruct :: OnClkCheckButton)
    ON_BN_CLICKED (ID_CONSTRUCT_BUILD_BUTTON, & CConstruct :: OnClkBuildButton)
    ON_BN_CLICKED (ID_CONSTRUCT_CANCEL_BUTTON, & CConstruct :: OnClkCancelButton)
    ON_LBN_SELCHANGE (ID_ALL_MODS_LIST_BOX, & CConstruct :: OnSelChangeAllModsListBox)
    ON_MESSAGE (UWM_OPEN_CTX_AVAILABLE_MODS, & CConstruct :: OpenAvailableModsCtxMenu)
    ON_LBN_SELCHANGE (ID_SEL_MODS_LIST_BOX, & CConstruct :: OnSelChangeSelModsListBox)
    ON_MESSAGE (UWM_OPEN_CTX_SELECTED_MODS, & CConstruct :: OpenSelectedModsCtxMenu)
    ON_BN_CLICKED (ID_MODULE_FILTER_BASIC, & CConstruct :: OnClkModuleFilterBasic)
    ON_BN_CLICKED (ID_MODULE_FILTER_MACRO, & CConstruct :: OnClkModuleFilterMacro)
    ON_BN_CLICKED (ID_MODULE_FILTER_ADVANCED, & CConstruct :: OnClkModuleFilterAdvanced)
    ON_BN_CLICKED (ID_MODULE_FILTER_SUPPORT, & CConstruct :: OnClkModuleFilterSupport)
    ON_BN_CLICKED (ID_MODULE_FILTER_CUSTOM, & CConstruct :: OnClkModuleFilterCustom)
    ON_BN_CLICKED (ID_MODULE_FILTER_PROTOTYPE, & CConstruct :: OnClkModuleFilterPrototype)
    ON_BN_CLICKED (ID_MODULE_FILTER_OBSOLETE, & CConstruct :: OnClkModuleFilterObsolete)
    ON_BN_CLICKED (IDC_BUTTON8, & CConstruct :: OnBnClickedButton8)
    ON_BN_CLICKED (IDC_BUTTON1, & CConstruct :: OnBnClickedButton1)
END_MESSAGE_MAP ()

BOOL CConstruct :: OnInitDialog ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnInitDialog()@@@CConstruct.cpp>");
    CDialog :: OnInitDialog ();
    max_HRU_spin.SetRange (1, SHORT_MAX);
    if (Global :: maxhru > 0)
    {
        max_HRU_spin.SetPos (Global :: maxhru);
    }

    else
    {
        max_HRU_spin.SetPos (1);
    }

    max_layer_spin.SetRange (1, SHORT_MAX);
    if (Global :: maxlay > 0)
    {
        max_layer_spin.SetPos (Global :: maxlay);
    }

    else
    {
        max_layer_spin.SetPos (1);
    }

    LoadAllModules ();
    FormActivate ();

InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnInitDialog()@@@CConstruct.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnInitDialog()@@@CConstruct.cpp>");
}
void CConstruct :: LoadAllModules ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::LoadAllModules()@@@CConstruct.cpp>");
    listbox_available_modules.ResetContent ();
    std :: map < std :: string, ClassModule * > * all_modules = CRHMmain :: getInstance () -> getAllmodules ();
    for (std :: map < std :: string, ClassModule * > :: iterator modIt = all_modules -> begin (); modIt != all_modules -> end (); modIt ++) {
        std :: string s = modIt -> first;
        CString c_all_modules (s.c_str ());
        listbox_available_modules.AddString (c_all_modules);
    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::LoadAllModules()@@@CConstruct.cpp>");
}
bool CConstruct :: ModuleIsSelected (CString cstr)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::ModuleIsSelected(CString cstr)@@@CConstruct.cpp>");
    CString cstr1;
    for (int i = 0; i < listbox_selected_modules.GetCount (); i ++) {
        listbox_selected_modules.GetText (i, cstr1);
        if (cstr == cstr1)
        {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::ModuleIsSelected(CString cstr)@@@CConstruct.cpp>");
            return true;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::ModuleIsSelected(CString cstr)@@@CConstruct.cpp>");
    return false;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::ModuleIsSelected(CString cstr)@@@CConstruct.cpp>");
}
void CConstruct :: OnBnClickedButton8 ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnBnClickedButton8()@@@CConstruct.cpp>");
    CString cstr;
    int sel = 0;
    for (size_t i = 0; i < AvailableModules -> size (); i ++) {
        sel = listbox_available_modules.GetSel (i);
        if (sel == 1)
        {
            listbox_available_modules.GetText (i, cstr);
            if (ModuleIsSelected (cstr) == 0)
            {
                listbox_selected_modules.AddString (cstr);
                SelectedModules -> push_back (std :: pair < std :: string, ClassModule * > (AvailableModules -> at (i).first, AvailableModules -> at (i).second));
            }

            listbox_available_modules.SetSel (i, false);
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnBnClickedButton8()@@@CConstruct.cpp>");
}
void CConstruct :: RemoveSelectedModule ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::RemoveSelectedModule()@@@CConstruct.cpp>");
    CString cstr;
    int c = SelectedModules -> size ();
    for (int i = 0; i < c; i ++) {
        int sel = listbox_selected_modules.GetSel (i);
        if (sel == 1)
        {
            listbox_selected_modules.GetText (i, cstr);
            listbox_selected_modules.DeleteString (i);
            CT2A s (cstr);
            string str = s;
            for (size_t SelectedModit = 0; SelectedModit < SelectedModules -> size (); SelectedModit ++) {
                if (SelectedModules -> at (SelectedModit).first == str)
                {
                    SelectedModules -> erase (SelectedModules -> begin () + SelectedModit);
                    break;
                }

            }
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::RemoveSelectedModule()@@@CConstruct.cpp>");
}
void CConstruct :: AddToAvailableModules (string str, ClassModule * obj)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::AddToAvailableModules(string str, ClassModule * obj)@@@CConstruct.cpp>");
    AvailableModules -> push_back (std :: pair < std :: string, ClassModule * > (str, obj));
    CString cstr (str.c_str ());
    listbox_available_modules.AddString ((LPCTSTR) cstr);
InstrumentLogger::instance()->log_instrument_log("</CConstruct::AddToAvailableModules(string str, ClassModule * obj)@@@CConstruct.cpp>");
}
void CConstruct :: AddToSelectedModules (string str, ClassModule * obj)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::AddToSelectedModules(string str, ClassModule * obj)@@@CConstruct.cpp>");
    SelectedModules -> push_back (std :: pair < std :: string, ClassModule * > (str, obj));
    if (obj -> variation != 0)
    {
        unsigned short variationChar = (unsigned short) (log (obj -> variation) / log (2) + 1);
        str = str + "#" + std :: to_string (variationChar);
    }

    CString cstr (str.c_str ());
    listbox_selected_modules.AddString ((LPCTSTR) cstr);
    string S = str;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::AddToSelectedModules(string str, ClassModule * obj)@@@CConstruct.cpp>");
}
void CConstruct :: FormActivate ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::FormActivate()@@@CConstruct.cpp>");
    listbox_available_modules.ResetContent ();
    module_filter_basic.SetCheck (0);
    module_filter_macro.SetCheck (0);
    module_filter_advanced.SetCheck (0);
    module_filter_custom.SetCheck (0);
    module_filter_obsolete.SetCheck (0);
    module_filter_prototype.SetCheck (0);
    module_filter_support.SetCheck (0);
    Mapstr2 MapAKACopy;
    MapAKACopy = Global :: MapAKA;
    AKAselectiveDelete ();
    Global :: Mapgetvar.clear ();
    Global :: Mapputvar.clear ();
    Global :: Mapreadvar.clear ();
    Global :: Mapdeclvar.clear ();
    Global :: Mapdeclstat.clear ();
    Global :: Mapdeclpar.clear ();
    Global :: Mapdeclobs.clear ();
    TBuild TempB = Global :: BuildFlag;
    Global :: BuildFlag = TBuild :: BUILD;
    for (std :: map < std :: string, ClassModule * > :: iterator modIt = Global :: AllModulesList -> begin (); modIt != Global :: AllModulesList -> end (); modIt ++) {
        ClassModule * thisModule = modIt -> second;
        thisModule -> variation_max = 0;
        unsigned short Temp = thisModule -> variation;
        unsigned short Temp2 = thisModule -> variation_set;
        thisModule -> variation_set = 0;
        thisModule -> variation = 0;
        thisModule -> decl ();
        thisModule -> variation = Temp;
        thisModule -> variation_set = Temp2;
        if (thisModule -> variation > 0)
        {
            thisModule -> hh = (long) (log (thisModule -> variation) / log (2) + 1);
        }

        else
        {
            thisModule -> hh = 0;
        }

    }
    Global :: OBS_AS_IS = 0;
    Global :: WQ_prj = false;
    listbox_selected_modules.ResetContent ();
    if (Global :: OurModulesList -> size ())
    {
        ModifyBuild = true;
    }

    else
    {
        ModifyBuild = false;
        module_filter_basic.SetCheck (1);
    }

    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        if (modIt -> second -> Lvl == LMODULE :: BASIC)
        {
            module_filter_basic.SetCheck (1);
        }

        if (modIt -> second -> Lvl == LMODULE :: MACRO)
        {
            module_filter_macro.SetCheck (1);
        }

        if (modIt -> second -> Lvl == LMODULE :: ADVANCE)
        {
            module_filter_advanced.SetCheck (1);
        }

        if (modIt -> second -> Lvl == LMODULE :: SUPPORT)
        {
            module_filter_support.SetCheck (1);
        }

        if (modIt -> second -> Lvl == LMODULE :: CUSTOM)
        {
            module_filter_custom.SetCheck (1);
        }

        if (modIt -> second -> Lvl == LMODULE :: PROTO)
        {
            module_filter_prototype.SetCheck (1);
        }

        if (modIt -> second -> Lvl == LMODULE :: OBSOL)
        {
            module_filter_obsolete.SetCheck (1);
        }

        AddToSelectedModules (modIt -> first, modIt -> second);
        std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos = modIt;
        string S = modIt -> first;
    }
    Execute = false;
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::FormActivate()@@@CConstruct.cpp>");
}
void CConstruct :: SetSuffix (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::SetSuffix(std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos)@@@CConstruct.cpp>");
    ClassModule * thisModule = pos -> second;
    string AA;
    if (thisModule -> hh > 0)
    {
        AA = "#0";
        AA [1] += (char) thisModule -> hh;
    }

    int found = pos -> first.find ("#");
    if (found > - 1)
    {
        for (size_t it = 0; it < SelectedModules -> size (); it ++) {
            if (SelectedModules -> at (it).first == pos -> first)
            {
                SelectedModules -> at (it).first = SelectedModules -> at (it).first.substr (0, SelectedModules -> at (it).first.length () - 2);
                break;
            }

        }
    }

    for (size_t it = 0; SelectedModules -> size (); it ++) {
        if (SelectedModules -> at (it).first == pos -> first)
        {
            SelectedModules -> at (it).first = SelectedModules -> at (it).first + AA;
            break;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::SetSuffix(std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos)@@@CConstruct.cpp>");
}
void CConstruct :: AKAselectiveDelete ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::AKAselectiveDelete()@@@CConstruct.cpp>");
    if (! Global :: MapAKA.empty ())
    {
        Mapstr2 :: iterator it;
        for (it = Global :: MapAKA.begin (); it != Global :: MapAKA.end ();) {
            string Var = (* it).first;
            string :: size_type idx = Var.find (' ');
            string type = Var.substr (0, idx);
            TAKA Type = AKAtype (type);
            switch (Type) {
            case TAKA :: OBSR:
            case TAKA :: OBSF:
                ++ it;
                break;
            default:
                Global :: MapAKA.erase (it ++);
            }
        }
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::AKAselectiveDelete()@@@CConstruct.cpp>");
}
void CConstruct :: AddLineToConstructConsole (std :: string str)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::AddLineToConstructConsole(std :: string str)@@@CConstruct.cpp>");
    CListBox * listbox = (CListBox *) GetDlgItem (ID_CONSTRUCT_CONSOLE);
    CString cstr (str.c_str ());
    listbox -> AddString (cstr);
InstrumentLogger::instance()->log_instrument_log("</CConstruct::AddLineToConstructConsole(std :: string str)@@@CConstruct.cpp>");
}
void CConstruct :: DisplayModule (std :: string moduleName, ClassModule * module, bool LBox1)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::DisplayModule(std :: string moduleName, ClassModule * module, bool LBox1)@@@CConstruct.cpp>");
    long variation = 0;
    long variationIndex = 0;
    std :: string fullModuleName = moduleName;
    int suffPos;
    if (suffPos = moduleName.find ("#"), suffPos > - 1)
    {
        variationIndex = moduleName [suffPos + 1] - char ('0');
        variation = (long) (pow (2, moduleName [suffPos + 1] - char ('1')));
        moduleName = moduleName.substr (0, moduleName.length () - 2);
    }

    else
    {
        variation = 0;
    }

    if (! module -> Description.empty ())
    {
        std :: vector < std :: string > * descriptionVector = new std :: vector < std :: string > ();
        Common :: tokenizeString (module -> Description, descriptionVector);
        if (module -> variation_max > 0)
        {
            ++ variationIndex;
        }

        if (LBox1)
        {
            for (size_t ii = 0; ii < descriptionVector -> size (); ++ ii) {
                std :: string consoleLine = moduleName;
                if (ii == 0)
                {
                    consoleLine += " Function summary";
                }

                else
                if (ii > 1)
                {
                    consoleLine += "#" + to_string (ii - 1);
                }

                else
                {
                    consoleLine += "  ";
                }

                consoleLine += " -> " + descriptionVector -> at (ii);
                AddLineToConstructConsole (consoleLine);
            }
        }

        else
        {
            AddLineToConstructConsole (fullModuleName + " -> " + descriptionVector -> at (variationIndex));
            if (module -> DLLName == "Macro")
            {
                ClassMacro * thisMacro = dynamic_cast < ClassMacro * > (module);
                if (thisMacro -> isGroup)
                {
                    AddLineToConstructConsole ("Group with modules:");
                    std :: string consoleLine;
                    for (size_t ii = 0; ii < thisMacro -> GrpStringList -> size (); ++ ii) {
                        if (ii == 0)
                        {
                            consoleLine = "  " + thisMacro -> GrpStringList -> at (ii).first;
                        }

                        else
                        {
                            consoleLine += ", " + thisMacro -> GrpStringList -> at (ii).first;
                        }

                    }
                    AddLineToConstructConsole (consoleLine);
                }

                else
                if (thisMacro -> isStruct)
                {
                    AddLineToConstructConsole ("Struct with modules:");
                    std :: string consoleLine;
                    for (size_t ii = 0; ii < thisMacro -> GrpStringList -> size (); ++ ii) {
                        if (ii == 0)
                        {
                            consoleLine = "  " + thisMacro -> GrpStringList -> at (ii).first;
                        }

                        else
                        {
                            consoleLine += ", " + thisMacro -> GrpStringList -> at (ii).first;
                        }

                    }
                    AddLineToConstructConsole (consoleLine);
                }

                else
                {
                    AddLineToConstructConsole ("Macro: ");
                    AddLineToConstructConsole ("declarations:");
                    int macroFoundAt;
                    for (size_t i = 0; i < Global :: MacroModulesList -> size (); i ++) {
                        if (Global :: MacroModulesList -> at (i) == thisMacro -> Name.c_str ())
                        {
                            macroFoundAt = i;
                            break;
                        }

                    }
                    for (int ii = macroFoundAt + 1; ii < thisMacro -> Begin - 1; ++ ii) {
                        AddLineToConstructConsole (" " + Global :: MacroModulesList -> at (ii));
                    }
                    AddLineToConstructConsole ("code:");
                    for (int ii = thisMacro -> Begin; ii < thisMacro -> End; ++ ii) {
                        AddLineToConstructConsole (" " + Global :: MacroModulesList -> at (ii));
                    }
                }

            }

        }

        AddLineToConstructConsole (" ");
        delete descriptionVector;
    }

    CListBox * console = (CListBox *) GetDlgItem (ID_CONSTRUCT_CONSOLE);
    console -> SetTopIndex (console -> GetCount () - 1);
    StringGrid1 = new StringGrid ();
    StringGrid1 -> ColCount = 6;
    StringGrid1 -> FixedRows = 0;
    StringGrid1 -> RowCount = 1;
    StringGrid1 -> Cells [0] [0] = "Observations";
    StringGrid1 -> Cells [1] [0] = "Modules";
    StringGrid1 -> Cells [2] [0] = "Inputs";
    StringGrid1 -> Cells [3] [0] = "Outputs";
    StringGrid1 -> Cells [4] [0] = "Parameters";
    StringGrid1 -> Cells [5] [0] = "New Observations";
    pair < Mapstr :: iterator, Mapstr :: iterator > range = Global :: Mapreadvar.equal_range (moduleName);
    int ii = 0;
    for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
        std :: string observationName = (itMap -> second).first;
        if (StringGrid1 -> RowCount < ii + 3)
        {
            StringGrid1 -> RowCount = ii + 3;
        }

        int Indx = StringGrid1 -> Cols [0].find (observationName);
        if (Indx == - 1 && Variation_Decide (variation, (itMap -> second).second))
        {
            StringGrid1 -> Cells [0] [ii + 2] = observationName;
            ++ ii;
        }

    }
    range = Global :: Mapputvar.equal_range (moduleName);
    ii = 0;
    for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
        std :: string putVarName = itMap -> second.first;
        int jj = putVarName.find (" ");
        std :: string mod = putVarName.substr (0, jj);
        std :: string var = putVarName.substr (jj + 1, putVarName.length () - jj - 1);
        if (mod != moduleName && Variation_Decide (variation, (itMap -> second).second))
        {
            if (StringGrid1 -> RowCount < ii + 3)
            {
                StringGrid1 -> RowCount = ii + 3;
            }

            StringGrid1 -> Cells [1] [ii + 2] = mod;
            StringGrid1 -> Cells [2] [ii + 2] = var;
            ++ ii;
        }

    }
    range = Global :: Mapgetvar.equal_range (moduleName);
    ii = 0;
    for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
        std :: string getVarName = itMap -> second.first;
        int jj = getVarName.find (" ");
        std :: string mod = getVarName.substr (0, jj);
        std :: string var = getVarName.substr (jj + 1, getVarName.length () - jj - 1);
        if (mod != moduleName && Variation_Decide (variation, (itMap -> second).second))
        {
            int Indx = StringGrid1 -> Cols [2].find (var);
            if (Indx == - 1)
            {
                if (StringGrid1 -> RowCount < ii + 3)
                {
                    StringGrid1 -> RowCount = ii + 3;
                }

                StringGrid1 -> Cells [1] [ii + 2] = mod;
                StringGrid1 -> Cells [2] [ii + 2] = var;
                ++ ii;
            }

        }

    }
    range = Global :: Mapdeclvar.equal_range (moduleName);
    ii = 0;
    for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
        std :: string varDeclaredName = itMap -> second.first;
        Mapstr :: iterator itMapInner;
        for (itMapInner = Global :: Mapreadvar.begin (); itMapInner != Global :: Mapreadvar.end (); ++ itMapInner) {
            if (itMapInner -> second.first == varDeclaredName)
            {
                break;
            }

        }
        Mapstr :: iterator pos = itMapInner;
        for (itMapInner = Global :: Mapdeclobs.begin (); itMapInner != Global :: Mapdeclobs.end (); ++ itMapInner) {
            if (itMapInner -> second.first == varDeclaredName)
            {
                break;
            }

        }
        Mapstr :: iterator pos2 = itMapInner;
        if ((pos == Global :: Mapreadvar.end () || Not_Obs (moduleName, varDeclaredName)) && pos2 == Global :: Mapdeclobs.end ())
        {
            int Indx = StringGrid1 -> Cols [3].find (varDeclaredName);
            if (Indx == - 1 && Variation_Decide (variation, (itMap -> second).second) && Visible_Decide ((itMap -> second).second))
            {
                if (StringGrid1 -> RowCount < ii + 3)
                {
                    StringGrid1 -> RowCount = ii + 3;
                }

                StringGrid1 -> Cells [3] [ii + 2] = varDeclaredName;
                ++ ii;
            }

        }

    }
    range = Global :: Mapdeclpar.equal_range (moduleName);
    ii = 0;
    for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
        if (Variation_Decide (variation, (itMap -> second).second) && Visible_Decide ((itMap -> second).second))
        {
            std :: string paramName = itMap -> second.first;
            if (StringGrid1 -> RowCount < ii + 3)
            {
                StringGrid1 -> RowCount = ii + 3;
            }

            StringGrid1 -> Cells [4] [ii + 2] = paramName;
            ++ ii;
        }

    }
    range = Global :: Mapdeclobs.equal_range (moduleName);
    ii = 0;
    for (Mapstr :: iterator itMap = range.first; itMap != range.second; ++ itMap) {
        if (Variation_Decide (variation, (itMap -> second).second) && Visible_Decide ((itMap -> second).second))
        {
            std :: string obsName = itMap -> second.first;
            if (StringGrid1 -> RowCount < ii + 3)
            {
                StringGrid1 -> RowCount = ii + 3;
            }

            StringGrid1 -> Cells [5] [ii + 2] = obsName;
            ++ ii;
        }

    }
    if (StringGrid1 -> RowCount > 1)
    {
        StringGrid1 -> FixedRows = 1;
    }

    while (listcontrol.DeleteColumn (0));
    listcontrol.DeleteAllItems ();
    listcontrol.InsertColumn (0, _T ("Observations"), LVCFMT_LEFT, 95);
    listcontrol.InsertColumn (1, _T ("Modules"), LVCFMT_LEFT, 95);
    listcontrol.InsertColumn (2, _T ("Inputs"), LVCFMT_LEFT, 95);
    listcontrol.InsertColumn (3, _T ("Outputs"), LVCFMT_LEFT, 95);
    listcontrol.InsertColumn (4, _T ("Parameters"), LVCFMT_LEFT, 95);
    listcontrol.InsertColumn (5, _T ("New Observations"), LVCFMT_LEFT, 95);
    for (int i = 1; i < StringGrid1 -> RowCount; i ++) {
        CString cstr0 (StringGrid1 -> Cells [0] [i].c_str ());
        CString cstr1 (StringGrid1 -> Cells [1] [i].c_str ());
        CString cstr2 (StringGrid1 -> Cells [2] [i].c_str ());
        CString cstr3 (StringGrid1 -> Cells [3] [i].c_str ());
        CString cstr4 (StringGrid1 -> Cells [4] [i].c_str ());
        CString cstr5 (StringGrid1 -> Cells [5] [i].c_str ());
        int nIndex = listcontrol.InsertItem (i - 1, cstr0);
        listcontrol.SetItemText (nIndex, 1, cstr1);
        listcontrol.SetItemText (nIndex, 2, cstr2);
        listcontrol.SetItemText (nIndex, 3, cstr3);
        listcontrol.SetItemText (nIndex, 4, cstr4);
        listcontrol.SetItemText (nIndex, 5, cstr5);
    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::DisplayModule(std :: string moduleName, ClassModule * module, bool LBox1)@@@CConstruct.cpp>");
}
bool CConstruct :: Variation_Decide (int Variation_set, long Variation)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::Variation_Decide(int Variation_set, long Variation)@@@CConstruct.cpp>");
    VandP V;
    V.Set (Variation);
    long variations = V.GetV ();
    if ((variations & 2048) != 0 && Variation_set == 0 || (variations & 4096) != 0 || (variations == 0) || (variations & Variation_set) != 0)
    {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Variation_Decide(int Variation_set, long Variation)@@@CConstruct.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Variation_Decide(int Variation_set, long Variation)@@@CConstruct.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Variation_Decide(int Variation_set, long Variation)@@@CConstruct.cpp>");
}
bool CConstruct :: Visible_Decide (long Variation)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::Visible_Decide(long Variation)@@@CConstruct.cpp>");
    VandP V;
    V.Set (Variation);
    long Visible = V.GetP ();

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Visible_Decide(long Variation)@@@CConstruct.cpp>");
    return Visible == 1;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::Visible_Decide(long Variation)@@@CConstruct.cpp>");
}
bool CConstruct :: Not_Obs (string Mod, string Var)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::Not_Obs(string Mod, string Var)@@@CConstruct.cpp>");
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeIobs = Global :: Mapreadvar.equal_range (Mod);
    for (Mapstr :: iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++ itMap)
        if (Var == itMap -> second.first)
        {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Not_Obs(string Mod, string Var)@@@CConstruct.cpp>");
            return false;
        }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Not_Obs(string Mod, string Var)@@@CConstruct.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::Not_Obs(string Mod, string Var)@@@CConstruct.cpp>");
}
void CConstruct :: OnSelChangeAllModsListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnSelChangeAllModsListBox()@@@CConstruct.cpp>");
    int selection = listbox_available_modules.GetCurSel ();
    CString cstr;
    listbox_available_modules.GetText (selection, cstr);
    CT2A moduleText (cstr);
    std :: string moduleName = moduleText;
    std :: map < std :: string, ClassModule * > :: iterator modPos = Global :: AllModulesList -> find (moduleName);
    DisplayModule (modPos -> first, modPos -> second, true);
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnSelChangeAllModsListBox()@@@CConstruct.cpp>");
}
void CConstruct :: OnSelChangeSelModsListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnSelChangeSelModsListBox()@@@CConstruct.cpp>");
    int selection = listbox_selected_modules.GetCurSel ();
    CString cstr;
    listbox_selected_modules.GetText (selection, cstr);
    CT2A moduleText (cstr);
    std :: string moduleName = moduleText;
    std :: string trimmedModuleName;
    int pos = moduleName.find_first_of ('#', 0);
    if (pos == std :: string :: npos)
    {
        trimmedModuleName = moduleName;
    }

    else
    {
        trimmedModuleName = moduleName.substr (0, pos);
    }

    std :: map < std :: string, ClassModule * > :: iterator modPos = Global :: AllModulesList -> find (trimmedModuleName);
    DisplayModule (moduleName, modPos -> second, false);
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnSelChangeSelModsListBox()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkCheckButton ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkCheckButton()@@@CConstruct.cpp>");
    CheckModel ();
    UpdateSelectedModulesListBox ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkCheckButton()@@@CConstruct.cpp>");
}
string CConstruct :: StringOfChar (char c, int n)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::StringOfChar(char c, int n)@@@CConstruct.cpp>");
    string result = "";
    for (int i = 0; i < n; i ++) {
        result += c;
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::StringOfChar(char c, int n)@@@CConstruct.cpp>");
    return result;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::StringOfChar(char c, int n)@@@CConstruct.cpp>");
}
long CConstruct :: CheckModel ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::CheckModel()@@@CConstruct.cpp>");
    size_t Showing = SelectedModules -> size ();
    if (Showing == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::CheckModel()@@@CConstruct.cpp>");
        return 0;
    }

    Mapstr :: iterator itMap, pos, pos2, itMap2;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeO;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeOobs;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeI;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeIobs;
    List = new std :: vector < std :: pair < std :: string, int >> ();
    ListAll = new std :: vector < std :: string >;
    ListUsed = new std :: vector < std :: pair < std :: string, int >> ();
    ListPuts = new std :: vector < std :: pair < std :: string, int >> ();
    ListStats = new std :: vector < std :: string > ();
    string S, SS, S1, S2;
    int indx, Error = 0, Wild = 0;
    MapAKAVar.clear ();
    CListBox * listbox = (CListBox *) GetDlgItem (ID_CONSTRUCT_CONSOLE);
    listbox -> ResetContent ();
    long Variation = 0;
    long Vindx = 0;
    Again: for (size_t ii = 0; ii < SelectedModules -> size (); ++ ii) {
        S = SelectedModules -> at (ii).first;
        Variation = SelectedModules -> at (ii).second -> variation;
        if (Variation)
        {
            Vindx = (long) (log (Variation) / log (2) + 1);
        }

        else
        {
            Vindx = 0;
        }

        rangeI = Global :: Mapgetvar.equal_range (S);
        for (itMap = rangeI.first; itMap != rangeI.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                int jj = SS.find (" ");
                S1 = SS.substr (0, jj);
                S2 = SS.substr (jj + 1, SS.length () - jj - 1);
                if (S1 [0] != '*')
                {
                    rangeO = Global :: Mapdeclvar.equal_range (S);
                    bool Found = false;
                    for (pos = rangeO.first; pos != rangeO.second; ++ pos) {
                        if (S2 == pos -> second.first)
                        {
                            Found = true;
                            break;
                        }

                    }
                    if (! Found)
                    {
                        indx = - 1;
                        for (size_t selectedModit = 0; selectedModit < SelectedModules -> size (); selectedModit ++) {
                            if (SelectedModules -> at (selectedModit).first == S1)
                            {
                                indx = selectedModit;
                            }

                        }
                        if (indx == - 1)
                        {
                            for (size_t AllModit = 0; AllModit < AvailableModules -> size (); AllModit ++) {
                                if (AvailableModules -> at (AllModit).first == S1)
                                {
                                    indx = AllModit;
                                }

                            }
                            if (indx == - 1)
                            {
                                LogError ("module not found: " + S1, TExcept :: ERR);
                                AddLineToConstructConsole ("module not found: " + S1);
                            }

                            else
                            {
                                int result = IDYES;
                                string temp = "To satisfy module " + S + " input " + SS;
                                CString cstr (temp.c_str ());
                                string temp2 = "Add module " + S1 + " ?";
                                CString cstr2 (temp2.c_str ());
                                result = MessageBox (cstr, cstr2, MB_YESNO);
                                if (result == IDYES)
                                {
                                    SelectedModules -> push_back (std :: pair < std :: string, ClassModule * > (S1, AvailableModules -> at (indx).second));
                                }

                            }

                        }

                    }

                }

            }

        }
    }
    for (int ii = 0; ii < (int) SelectedModules -> size (); ++ ii) {
        S = SelectedModules -> at (ii).first;
        Variation = SelectedModules -> at (ii).second -> variation;
        if (Variation)
        {
            Vindx = (long) (log (Variation) / log (2) + 1);
        }

        else
        {
            Vindx = 0;
        }

        rangeI = Global :: Mapdeclstat.equal_range (S);
        for (itMap = rangeI.first; itMap != rangeI.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                ListStats -> push_back (SS);
            }

        }
        rangeO = Global :: Mapdeclvar.equal_range (S);
        rangeOobs = Global :: Mapdeclobs.equal_range (S);
        rangeI = Global :: Mapgetvar.equal_range (S);
        rangeIobs = Global :: Mapreadvar.equal_range (S);
        for (itMap = rangeOobs.first; itMap != rangeOobs.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                List -> push_back (std :: pair < std :: string, int > (S + " " + SS, 0));
            }

        }
        for (itMap = rangeO.first; itMap != rangeO.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                for (itMap2 = Global :: Mapreadvar.begin (); itMap2 != Global :: Mapreadvar.end (); ++ itMap2) {
                    if (itMap2 -> second.first == SS)
                    {
                        break;
                    }

                }
                pos = itMap2;
                for (itMap2 = Global :: Mapdeclobs.begin (); itMap2 != Global :: Mapdeclobs.end (); ++ itMap2) {
                    if (itMap2 -> second.first == SS)
                    {
                        break;
                    }

                }
                pos2 = itMap2;
                if ((pos == Global :: Mapreadvar.end () || Not_Obs (S, SS)) && pos2 == Global :: Mapdeclobs.end ())
                {
                    S2 = SelectedModules -> at (ii).first + " " + SS;
                    string S3;
                    string M3;
                    bool Twice = false;
                    size_t tt;
                    for (tt = 0; tt < ListAll -> size (); tt ++) {
                        int jj = ListAll -> at (tt).find (" ");
                        S3 = ListAll -> at (tt).substr (jj + 1, ListAll -> at (tt).length () - jj - 1);
                        M3 = ListAll -> at (tt).substr (0, jj);
                        if (S3 == SS && S != M3 && S != "obs")
                        {
                            if (S3 [S3.length () - 1] != '#')
                            {
                                Twice = true;
                                break;
                            }

                        }

                    }
                    if (Twice)
                    {
                        int result = IDYES;
                        string temp = string ("YES to remove '" + S + "' or NO to remove '" + M3 + "'");
                        CString cstr (temp.c_str ());
                        string temp2 = string ("Module output generated twice: '" + S2 + "' defined earlier as '" + ListAll -> at (tt) + "'");
                        CString cstr2 (temp2.c_str ());
                        result = MessageBox (cstr, cstr2, MB_YESNO);
                        if (result == IDYES)
                        {
                            for (size_t it = 0; it < SelectedModules -> size (); it ++) {
                                if (SelectedModules -> at (it).first == S)
                                {
                                    tt = it;
                                }

                            }
                        }

                        else
                        if (result == IDNO)
                        {
                            for (size_t it = 0; it < SelectedModules -> size (); it ++) {
                                if (SelectedModules -> at (it).first == M3)
                                {
                                    tt = it;
                                }

                            }
                        }

                        SelectedModules -> erase (SelectedModules -> begin () + tt);
                        Entries.clear ();
                        List -> clear ();
                        ListAll -> clear ();
                        ListUsed -> clear ();
                        ListPuts -> clear ();
                        ListStats -> clear ();
                        goto Again;
                    }

                    ListAll -> push_back (S2);
                    int indx = - 1;
                    for (size_t it = 0; it < List -> size (); it ++) {
                        if (List -> at (it).first == S2)
                        {
                            indx = it;
                        }

                    }
                    if (indx == - 1)
                    {
                        List -> push_back (std :: pair < std :: string, int > (S2, 0));
                    }

                }

            }

        }
        for (itMap = rangeI.first; itMap != rangeI.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                int indx = - 1;
                for (size_t it = 0; it < List -> size (); it ++) {
                    if (List -> at (it).first == SS)
                    {
                        indx = it;
                        break;
                    }

                }
                if (indx == - 1 && SS [0] != '*')
                {
                    int jj = SS.find (" ");
                    S2 = SS.substr (jj + 1, SS.length () - jj - 1);
                    S1 = S + ' ' + S2;
                    indx = - 1;
                    for (size_t it = 0; it < List -> size (); it ++) {
                        if (List -> at (it).first == S1)
                        {
                            indx = it;
                            break;
                        }

                    }
                    if (indx == - 1 && S1 [S1.length () - 2] == '@')
                    {
                        indx = - 1;
                        for (size_t it = 0; it < List -> size (); it ++) {
                            if (List -> at (it).first == SS.substr (0, SS.find ("@")))
                            {
                                indx = it;
                                break;
                            }

                        }
                    }

                }

                if (indx == - 1)
                {
                    ListUsed -> push_back (std :: pair < std :: string, int > (SS, - (ii + 1)));
                }

                else
                {
                    int Cnt = List -> at (indx).second;
                    List -> at (indx).second = ++ Cnt;
                    ListUsed -> push_back (std :: pair < std :: string, int > (SS, ii));
                }

            }

        }
        rangeI = Global :: Mapputvar.equal_range (S);
        for (itMap = rangeI.first; itMap != rangeI.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                indx = - 1;
                for (size_t it = 0; it < List -> size (); it ++) {
                    if (List -> at (it).first == SS)
                    {
                        indx = it;
                        break;
                    }

                }
                if (indx == - 1)
                {
                    ListPuts -> push_back (std :: pair < std :: string, int > (SS, (int) ListUsed -> size ()));
                    ListUsed -> push_back (std :: pair < std :: string, int > (SS, - (ii + 1)));
                }

                else
                {
                    int Cnt = List -> at (indx).second;
                    List -> at (indx).second = ++ Cnt;
                    ListPuts -> push_back (std :: pair < std :: string, int > (SS, (int) ListUsed -> size ()));
                    ListUsed -> push_back (std :: pair < std :: string, int > (SS, ii));
                }

            }

        }
        for (itMap = rangeIobs.first; itMap != rangeIobs.second; ++ itMap) {
            SS = itMap -> second.first;
            if (Variation_Decide (Variation, (itMap -> second).second))
            {
                for (itMap2 = Global :: Mapdeclobs.begin (); itMap2 != Global :: Mapdeclobs.end (); ++ itMap2) {
                    if (itMap2 -> second.first == SS)
                    {
                        break;
                    }

                }
                pos = itMap2;
                if (pos == Global :: Mapdeclobs.end ())
                {
                    continue;
                }

                indx = - 1;
                for (size_t it = 0; it < SelectedModules -> size (); it ++) {
                    if (SelectedModules -> at (it).first == pos -> first)
                    {
                        indx = it;
                    }

                }
                if (indx != ii && indx > - 1)
                {
                    S1 = pos -> first;
                    SS = pos -> second.first;
                    S2 = S1 + " " + SS;
                    indx = - 1;
                    for (size_t it = 0; it < List -> size (); it ++) {
                        if (List -> at (it).first == S2)
                        {
                            indx = it;
                            break;
                        }

                    }
                    if (indx == - 1)
                    {
                        ListUsed -> push_back (std :: pair < std :: string, int > (S2, - (ii + 1)));
                    }

                    else
                    {
                        int Cnt = List -> at (indx).second;
                        List -> at (indx).second = ++ Cnt;
                        ListUsed -> push_back (std :: pair < std :: string, int > (S2, ii));
                    }

                }

            }

        }
    }
    for (int ii = 0; ii < (int) SelectedModules -> size (); ++ ii) {
        S = SelectedModules -> at (ii).first;
        Variation = SelectedModules -> at (ii).second -> variation;
        if (Variation)
        {
            Vindx = (long) (log (Variation) / log (2) + 1);
        }

        else
        {
            Vindx = 0;
        }

        ClassModule * Module = SelectedModules -> at (ii).second;
        std :: vector < std :: string > * Choices = new std :: vector < std :: string > ();
        Common :: tokenizeString (Module -> PeerVar, Choices);
        if ((long) Choices -> size () > Vindx)
        {
            SS = Choices -> at (Vindx);
        }

        else
        if (Choices -> size ())
        {
            SS = Choices -> at (Choices -> size () - 1);
        }

        else
        {
            SS = "";
        }

        if (SS != "")
        {
            for (size_t jj = 0; jj < List -> size (); ++ jj) {
                string Entry = List -> at (jj).first;
                long kk = Entry.find (' ');
                S1 = Entry.substr (kk + 1, Entry.length ());
                if (S1 == SS)
                {
                    break;
                }

            }
            if (S1 == SS)
            {
                SS = "* " + SS;
                ListUsed -> push_back (std :: pair < std :: string, int > (SS, - (ii + 1)));
                string SSS = "Ranking module '" + S + "' to '" + SS + "'";
                AddLineToConstructConsole (SSS);
            }

            else
            {
                S2 = "Ranking module '" + S + "' to an inaccessible variable '" + SS + "'";
                AddLineToConstructConsole (S2);
            }

        }

    }
    for (size_t ii = 0; ii < ListUsed -> size (); ++ ii) {
        if (ListUsed -> at (ii).first [0] == '*')
        {
            string Var = ListUsed -> at (ii).first;
            Var = Var.substr (2, Var.length ());
            int jj = Best_Match (Var, List);
            if (jj > - 1)
            {
                ++ Wild;
                int thisModule = ListUsed -> at (ii).second;
                thisModule = - (thisModule + 1);
                string Module = SelectedModules -> at (thisModule).first;
                ListUsed -> at (ii).first = List -> at (jj).first;
                ListUsed -> at (ii).second = abs ((int) ListUsed -> at (ii).second + 1);
            }

        }

        else
        {
            int NotFoundIndx = ListUsed -> at (ii).second;
            if (NotFoundIndx < 0)
            {
                int indx = - 1;
                for (size_t it = 0; List -> size (); it ++) {
                    if (List -> at (it).first == ListUsed -> at (ii).first)
                    {
                        indx = it;
                        break;
                    }

                }
                int ListPutsIndx = - 1;
                for (size_t it = 0; it < ListPuts -> size (); it ++) {
                    if (ListPuts -> at (it).first == ListUsed -> at (ii).first)
                    {
                        ListPutsIndx = it;
                        break;
                    }

                }
                if (ListPutsIndx == - 1 && indx == - 1)
                {
                    ++ Error;
                }

                if (indx > - 1)
                {
                    ListUsed -> at (ii).second = abs (ListUsed -> at (ii).second + 1);
                    continue;
                }

            }

            else
            {
                continue;
            }

        }

        int NotFoundIndx = ListUsed -> at (ii).second;
        if (NotFoundIndx < 0 && ListUsed -> at (ii).first [0] == '*')
        {
            string Message;
            string Message2 (" Suggestions: ");
            ++ Error;
            LogError ("wild variable not found: " + ListUsed -> at (ii).first, TExcept :: WARNING);
            int kk = abs (ListUsed -> at (ii).second + 1);
            string Sroot = ListUsed -> at (ii).first;
            if (Sroot.find ("@") != - 1)
            {
                Sroot = Sroot.substr (0, Sroot.find ("@"));
            }

            Message = "wild variable not found: \" " + Sroot + "\" used by " + SelectedModules -> at (kk).first + ".";
            string SW = ListUsed -> at (ii).first;
            SW = SW.substr (2, ListUsed -> at (ii).first.length ());
            bool Once = false;
            bool rootVar = (SW.find ("@") == - 1);
            if (! rootVar)
            {
                SW = SW.substr (0, SW.find ("@"));
            }

            for (itMap = Global :: Mapdeclvar.begin (); itMap != Global :: Mapdeclvar.end (); ++ itMap) {
                SS = itMap -> second.first;
                bool rootVar1 = (SS.find ("@") == - 1);
                if (! rootVar1)
                {
                    SS = SS.substr (0, SS.find ("@"));
                }

                if (SW == SS)
                {
                    Once = true;
                    string S = itMap -> first;
                    VandP V;
                    V.Set ((itMap -> second).second);
                    long Variation = V.GetV () & 2047;
                    if (Variation > 0)
                    {
                        long NN = (long) (log (Variation) / log (2) + 1);
                        string AA = "#0";
                        AA [1] += (char) NN;
                        S += AA;
                    }

                    Message2 += S + ", ";
                }

            }
            if (! Once)
            {
                AddLineToConstructConsole (Message + " No " + Message2);
            }

            else
            {
                AddLineToConstructConsole (Message + Message2);
            }

        }

    }
    if (Error)
    {
        string temp = "" + Error;
        S = "Errors: " + temp + ';';
        string Line = StringOfChar ('*', 80);
        ;
        AddLineToConstructConsole (Line);
    }

    else
    {
        bool Loop = true;
        int Loops = 0;
        std :: vector < std :: pair < std :: string, int >> * OrgList = new std :: vector < std :: pair < std :: string, int >> ();
        for (size_t ii = 0; ii < SelectedModules -> size (); ++ ii) {
            OrgList -> push_back (std :: pair < std :: string, int > (SelectedModules -> at (ii).first, ii));
            Entries.push_back (ClassEntry ());
        }
        while (Loop) {
            Loop = false;
            ++ Loops;
            for (size_t ii = 0; ii < SelectedModules -> size (); ++ ii) {
                Entries [ii].module = SelectedModules -> at (ii).second;
                Entries [ii].Name = SelectedModules -> at (ii).first;
                Entries [ii].rank = 0;
                Entries [ii].used = false;
                size_t index = - 1;
                for (size_t it = 0; it < OrgList -> size (); it ++) {
                    if (OrgList -> at (it).first == SelectedModules -> at (ii).first)
                    {
                        index = it;
                        break;
                    }

                }
                if (index < 0 || index > Entries.size () - 1)
                {
                    LogError ("Build error: outside range", TExcept :: ERR);
                }

                Entries [ii].OrigPos = index;
            }
            for (size_t ii = 0; ii < ListPuts -> size (); ++ ii) {
                ListPuts -> at (ii).first = ListUsed -> at (ListPuts -> at (ii).second).first;
            }
            for (size_t ii = 0; ii < ListUsed -> size (); ++ ii) {
                unsigned long thisModule = ListUsed -> at (ii).second;
                for (unsigned long nn = 0; nn < Entries.size (); ++ nn) {
                    if (Entries [nn].OrigPos == thisModule)
                    {
                        thisModule = nn;
                        if (thisModule < 0 || thisModule > Entries.size () - 1)
                        {
                            LogError ("Build error: outside range", TExcept :: ERR);
                        }

                        break;
                    }

                }
                string Entry = ListUsed -> at (ii).first;
                long kk = Entry.find (' ');
                string UsesModule = Entry.substr (0, kk);
                string Var_only = Entry.substr (kk + 1, Entry.length () - kk - 1);
                unsigned long index;
                ClassModule * checkModule = NULL;
                for (index = 0; index < Entries.size (); ++ index) {
                    string Root = Entries [index].Name;
                    if (Root == UsesModule)
                    {
                        checkModule = Entries [index].module;
                        break;
                    }

                }
                if (checkModule && checkModule -> isGroup)
                {
                    Entries [index].used = true;
                    continue;
                }

                if (index >= Entries.size ())
                {
                    continue;
                }

                Entries [index].used = true;
                if (UsesModule == Entries [thisModule].Name)
                {
                    continue;
                }

                int jj = Best_Match (Var_only, ListPuts);
                if (jj > - 1 && ii == (ListPuts -> at (jj).second))
                {
                    continue;
                }

                jj = Best_Match (Var_only, ListStats);
                if (jj > - 1)
                {
                    continue;
                }

                long B = (long) powl (2, index);
                Entries [thisModule].rank |= B;
            }
            for (unsigned long ii = 0; ii < Entries.size () - 1; ++ ii) {
                for (unsigned long jj = ii + 1; jj < Entries.size (); ++ jj) {
                    if (Entries [jj].rank < Entries [ii].rank)
                    {
                        MoveDown (Entries, ii, jj);
                        Loop = true;
                    }

                }
            }
            for (long ii = 0; ii < (long) Entries.size () - 1; ++ ii) {
                ClassModule * E2 = (ClassModule *) Entries [ii].module;
                if (E2 -> PeerRank < 0)
                {
                    Entries [ii].used = true;
                }

                for (long jj = ii + 1; jj < (long) Entries.size (); ++ jj) {
                    if (Entries [jj].rank == Entries [ii].rank)
                    {
                        ClassModule * E1 = (ClassModule *) Entries [jj].module;
                        if (labs (E1 -> PeerRank) < labs (E2 -> PeerRank))
                        {
                            MoveDown (Entries, ii, jj);
                            Loop = true;
                        }

                    }

                }
            }
            SelectedModules -> clear ();
            for (unsigned long ii = 0; ii < Entries.size (); ++ ii) {
                SelectedModules -> push_back (std :: pair < std :: string, ClassModule * > (Entries [ii].Name, Entries [ii].module));
            }
            if (Loops > 20)
            {
                Loop = false;
                Loops = - Loops;
            }

        }
        bool Removed = false;
        for (unsigned long ii = 0; ii < Entries.size () - 1; ++ ii) {
            if (! Entries [ii].used && Entries [ii].Name != "basin")
            {
                int result = IDYES;
                CString temp (Entries [ii].Name.c_str ());
                result = MessageBox (temp, _T ("Module not used!  Remove module?"), MB_YESNO);
                if (result != IDYES)
                {
                    continue;
                }

                int indx;
                for (size_t it = 0; it < SelectedModules -> size (); it ++) {
                    if (SelectedModules -> at (it).first == Entries [ii].Name)
                    {
                        indx = it;
                        SelectedModules -> erase (SelectedModules -> begin () + indx);
                        Removed = true;
                        break;
                    }

                }
            }

        }
        Entries.clear ();
        List -> clear ();
        ListAll -> clear ();
        ListUsed -> clear ();
        ListPuts -> clear ();
        ListStats -> clear ();
        if (Removed)
        {
            goto Again;
        }

        int moves = 0;
        for (unsigned long ii = 0; ii < Entries.size (); ++ ii)
            if (Entries [ii].OrigPos != ii)
            {
                ++ moves;
            }

        if (Loops)
        {
            AddLineToConstructConsole (" ");
            LogError ("Number of loops to build: " + to_string (Loops) + " and modules moved: " + to_string (moves), TExcept :: WARNING);
            AddLineToConstructConsole ("Number of loops to build: " + to_string (Loops) + " and modules moved: " + to_string (moves));
        }

        else
        {
            LogError ("Problem with modules in build. Possibly modules referencing one another!", TExcept :: WARNING);
            AddLineToConstructConsole ("Problem with modules in build. Possibly modules referencing one another!");
            MessageBox (_T ("Problem with modules in build."), _T ("Possibly modules referencing one another!"), MB_OK);
        }

        Entries.clear ();
        delete OrgList;
        S = "";
    }

    delete List;
    delete ListAll;
    delete ListUsed;

InstrumentLogger::instance()->log_instrument_log("</CConstruct::CheckModel()@@@CConstruct.cpp>");
    return Error;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::CheckModel()@@@CConstruct.cpp>");
}
long CConstruct :: Best_Match (string Var, std :: vector < std :: pair < std :: string, int >> * List)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::Best_Match(string Var, std :: vector < std :: pair < std :: string, int >> * List)@@@CConstruct.cpp>");
    long found = 10;
    long Indx = - 1;
    for (size_t jj = 0; jj < List -> size (); ++ jj) {
        string Entry = List -> at (jj).first;
        long kk = Entry.find (' ');
        string Var1 = Entry.substr (kk + 1, Entry.length ());
        bool rootVar = (Var.find ("@") == - 1);
        bool rootVar1 = (Var1.find ("@") == - 1);
        if (Var1 == Var)
        {
            found = 0;
            Indx = jj;
            break;
        }

        else
        if (rootVar && ! rootVar1 && Var == Var1.substr (0, Var1.find ("@")) && found > 1)
        {
            found = 1;
            Indx = jj;
        }

        else
        if (! rootVar && rootVar1 && Var.substr (0, Var.find ("@")) == Var1 && found > 2)
        {
            found = 2;
            Indx = jj;
        }

        else
        if (! rootVar && ! rootVar1 && Var.substr (0, Var.find ("@")) == Var1.substr (0, Var1.find ("@")) && found > 3)
        {
            found = 3;
            Indx = jj;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Best_Match(string Var, std :: vector < std :: pair < std :: string, int >> * List)@@@CConstruct.cpp>");
    return Indx;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::Best_Match(string Var, std :: vector < std :: pair < std :: string, int >> * List)@@@CConstruct.cpp>");
}
long CConstruct :: Best_Match (string Var, std :: vector < std :: string > * List)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::Best_Match(string Var, std :: vector < std :: string > * List)@@@CConstruct.cpp>");
    long found = 10;
    long Indx = - 1;
    for (size_t jj = 0; jj < List -> size (); ++ jj) {
        string Entry = List -> at (jj).c_str ();
        long kk = Entry.find (' ');
        string Var1 = Entry.substr (kk + 1, Entry.length ());
        bool rootVar = (Var.find ("@") == - 1);
        bool rootVar1 = (Var1.find ("@") == - 1);
        if (Var1 == Var)
        {
            found = 0;
            Indx = jj;
            break;
        }

        else
        if (rootVar && ! rootVar1 && Var == Var1.substr (0, Var1.find ("@")) && found > 1)
        {
            found = 1;
            Indx = jj;
        }

        else
        if (! rootVar && rootVar1 && Var.substr (0, Var.find ("@")) == Var1 && found > 2)
        {
            found = 2;
            Indx = jj;
        }

        else
        if (! rootVar && ! rootVar1 && Var.substr (0, Var.find ("@")) == Var1.substr (0, Var1.find ("@")) && found > 3)
        {
            found = 3;
            Indx = jj;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::Best_Match(string Var, std :: vector < std :: string > * List)@@@CConstruct.cpp>");
    return Indx;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::Best_Match(string Var, std :: vector < std :: string > * List)@@@CConstruct.cpp>");
}
void CConstruct :: UpdateAvailableModules ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::UpdateAvailableModules()@@@CConstruct.cpp>");
    AvailableModules -> clear ();
    listbox_available_modules.ResetContent ();
    for (std :: map < std :: string, ClassModule * > :: iterator modIt = Global :: AllModulesList -> begin (); modIt != Global :: AllModulesList -> end (); modIt ++) {
        LMODULE str = modIt -> second -> Lvl;
        if (modIt -> second -> Lvl == LMODULE :: BASIC)
        {
            if (module_filter_basic.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

        if (modIt -> second -> Lvl == LMODULE :: ADVANCE)
        {
            if (module_filter_advanced.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

        if (modIt -> second -> Lvl == LMODULE :: CUSTOM)
        {
            if (module_filter_custom.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

        if (str == LMODULE :: MACRO)
        {
            if (module_filter_macro.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

        if (modIt -> second -> Lvl == LMODULE :: OBSOL)
        {
            if (module_filter_obsolete.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

        if (modIt -> second -> Lvl == LMODULE :: PROTO)
        {
            if (module_filter_prototype.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

        if (modIt -> second -> Lvl == LMODULE :: SUPPORT)
        {
            if (module_filter_support.GetCheck () == 1)
            {
                AddToAvailableModules (modIt -> first, modIt -> second);
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::UpdateAvailableModules()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterBasic ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterBasic()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterBasic()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterMacro ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterMacro()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterMacro()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterAdvanced ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterAdvanced()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterAdvanced()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterSupport ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterSupport()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterSupport()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterCustom ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterCustom()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterCustom()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterPrototype ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterPrototype()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterPrototype()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkModuleFilterObsolete ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkModuleFilterObsolete()@@@CConstruct.cpp>");
    UpdateAvailableModules ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkModuleFilterObsolete()@@@CConstruct.cpp>");
}
long CConstruct :: BuildClick ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::BuildClick()@@@CConstruct.cpp>");
    int test = AvailableModules -> size ();
    long Showing = SelectedModules -> size ();
    if (Showing == 0)
    {
        Global :: nlay = max_layer_spin.GetPos ();
        Global :: nhru = max_HRU_spin.GetPos ();

InstrumentLogger::instance()->log_instrument_log("</CConstruct::BuildClick()@@@CConstruct.cpp>");
        return 1;
    }

    long Errors = CheckModel ();
    UpdateSelectedModulesListBox ();
    if (Errors)
    {
        string str = "Errors: " + to_string (Errors);
        CString cstr (str.c_str ());
        MessageBox (L"Model has unsatisfied module inputs or multiple definitions", cstr, MB_OK);

InstrumentLogger::instance()->log_instrument_log("</CConstruct::BuildClick()@@@CConstruct.cpp>");
        return Errors;
    }

    if (ModifyBuild)
    {
        SaveBuildParameters ();
        RemoveParameter ();
    }

    MapAKACopy = Global :: MapAKA;
    CRHMmain * crhmmain = CRHMmain :: getInstance ();
    crhmmain -> ClearModules (false);
    Global :: nlay = max_layer_spin.GetPos ();
    Global :: nhru = max_HRU_spin.GetPos ();
    Global :: maxlay = max_layer_spin.GetPos ();
    Global :: maxhru = max_HRU_spin.GetPos ();
    COleDateTime timeNow;
    timeNow = COleDateTime :: GetCurrentTime ();
    timeNow.m_dt;
    crhmmain -> setStartDate (timeNow.m_dt);
    crhmmain -> setEndDate (timeNow.m_dt);
    Global :: OurModulesList -> clear ();
    for (size_t i = 0; i < SelectedModules -> size (); i ++) {
        std :: string selectedString = SelectedModules -> at (i).first;
        int suffix = 0;
        std :: string trimmedString;
        int pos = selectedString.find_first_of ('#', 0);
        if (pos == std :: string :: npos)
        {
            trimmedString = selectedString;
        }

        else
        {
            trimmedString = selectedString.substr (0, pos);
            suffix = std :: stoi (selectedString.substr (pos + 1, std :: string :: npos));
        }

        if (SelectedModules -> at (i).second -> variation == 0)
        {
            SelectedModules -> at (i).second -> variation = (unsigned short) pow (2, suffix - 1);
        }

        Global :: OurModulesList -> push_back (std :: pair < std :: string, ClassModule * > (trimmedString, SelectedModules -> at (i).second));
    }
    Execute = true;
    Global :: BuildFlag = TBuild :: BUILD;
    if (! MapAKAVar.empty ())
    {
        Mapstr2 :: iterator it;
        for (it = MapAKAVar.begin (); it != MapAKAVar.end (); ++ it)
            MapAKACopy.insert (* it);
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::BuildClick()@@@CConstruct.cpp>");
    return Errors;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::BuildClick()@@@CConstruct.cpp>");
}
void CConstruct :: SaveBuildParameters ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::SaveBuildParameters()@@@CConstruct.cpp>");
    ClassPar * thisPar;
    if (ModifyBuild)
    {
        RemoveSharedParams ();
        ParaList = new std :: vector < std :: pair < std :: string, ClassPar * >> ();
        MapPar :: iterator itPar;
        itPar = Global :: MapPars.begin ();
        while (itPar != Global :: MapPars.end ()) {
            thisPar = (* itPar).second;
            string S = string (((* itPar).second) -> module.c_str ()) + " " + ((* itPar).second) -> param.c_str ();
            int parFound = - 1;
            for (size_t it = 0; it < ParaList -> size (); it ++) {
                if (ParaList -> at (it).first == S)
                {
                    parFound = it;
                    break;
                }

            }
            if (parFound == - 1)
            {
                ClassPar * par (new ClassPar (* thisPar));
                ParaList -> push_back (std :: pair < std :: string, ClassPar * > (S, par));
            }

            ++ itPar;
        }
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::SaveBuildParameters()@@@CConstruct.cpp>");
}
void CConstruct :: ReadBuildParameters ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::ReadBuildParameters()@@@CConstruct.cpp>");
    MapPar :: iterator itPar;
    ClassPar * thisPar;
    if (ModifyBuild)
    {
        itPar = Global :: MapPars.begin ();
        while (itPar != Global :: MapPars.end ()) {
            thisPar = (* itPar).second;
            string S = string (((* itPar).second) -> module.c_str ()) + " " + ((* itPar).second) -> param.c_str ();
            int ii = - 1;
            for (size_t it = 0; it < ParaList -> size (); it ++) {
                if (ParaList -> at (it).first == S)
                {
                    ii = it;
                    break;
                }

            }
            if (ii != - 1)
            {
                ClassPar * OldPar = ParaList -> at (ii).second;
                thisPar -> Change (* OldPar);
            }

            ++ itPar;
        }
        for (size_t ii = 0; ii < ParaList -> size (); ++ ii) {
            delete ParaList -> at (ii).second;
        }
        delete ParaList;
        ParaList = NULL;
        CRHMmain * crhmmain = CRHMmain :: getInstance ();
        crhmmain -> SqueezeParams ();
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::ReadBuildParameters()@@@CConstruct.cpp>");
}
void CConstruct :: RemoveSharedParams ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::RemoveSharedParams()@@@CConstruct.cpp>");
    Global :: Mapgetvar.clear ();
    Global :: Mapputvar.clear ();
    Global :: Mapreadvar.clear ();
    Global :: Mapdeclvar.clear ();
    Global :: Mapdeclstat.clear ();
    Global :: Mapdeclpar.clear ();
    Global :: Mapdeclobs.clear ();
    Global :: DeclRootList -> clear ();
    Global :: BuildFlag = TBuild :: BUILD;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        modIt -> second -> decl ();
    }
    Global :: BuildFlag = TBuild :: DECL;
    ClassPar * thisPar;
    MapPar :: iterator itPar;
    long count;
    itPar = Global :: SharedMapPars.begin ();
    while (itPar != Global :: SharedMapPars.end ()) {
        thisPar = (* itPar).second;
        count = ClassParFindParBld (thisPar);
        Global :: MapPars.erase ("Shared " + thisPar -> param);
        delete thisPar;
        ++ itPar;
    }
    Global :: SharedMapPars.clear ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::RemoveSharedParams()@@@CConstruct.cpp>");
}
void CConstruct :: RemoveParameter ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::RemoveParameter()@@@CConstruct.cpp>");
    MapPar :: iterator itPar;
    ClassPar * thisPar;
    for (itPar = Global :: MapPars.begin (); itPar != Global :: MapPars.end ();) {
        thisPar = (* itPar).second;
        int kk = - 1;
        for (size_t it = 0; it < SelectedModules -> size (); it ++) {
            if (SelectedModules -> at (it).first.c_str () == thisPar -> module.c_str ())
            {
                kk = it;
                break;
            }

        }
        if (kk == - 1 && thisPar -> module != "shared")
        {
            Global :: MapPars.erase (itPar ++);
            delete thisPar;
        }

        else
        {
            ++ itPar;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::RemoveParameter()@@@CConstruct.cpp>");
}
long CConstruct :: FormatMax (long M)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::FormatMax(long M)@@@CConstruct.cpp>");
    M = M & 2047;
    if (M == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::FormatMax(long M)@@@CConstruct.cpp>");
        return 0;
    }

    for (int ii = 1; ii < 8; ++ ii) {
        M = (M >> 1);
        if (M == 0)
        {

InstrumentLogger::instance()->log_instrument_log("</CConstruct::FormatMax(long M)@@@CConstruct.cpp>");
            return ii;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::FormatMax(long M)@@@CConstruct.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::FormatMax(long M)@@@CConstruct.cpp>");
}
void CConstruct :: OnClkBuildButton ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkBuildButton()@@@CConstruct.cpp>");
    long Errors = BuildClick ();
    if (! Errors)
    {
        CDialog :: OnOK ();
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkBuildButton()@@@CConstruct.cpp>");
}
void CConstruct :: OnClkCancelButton ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnClkCancelButton()@@@CConstruct.cpp>");
    CDialog :: OnCancel ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnClkCancelButton()@@@CConstruct.cpp>");
}
void CConstruct :: OnBnClickedButton1 ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OnBnClickedButton1()@@@CConstruct.cpp>");
    RemoveSelectedModule ();
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OnBnClickedButton1()@@@CConstruct.cpp>");
}
LRESULT CConstruct :: OpenAvailableModsCtxMenu (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OpenAvailableModsCtxMenu(WPARAM, LPARAM)@@@CConstruct.cpp>");
    CMenu ctxMenu;
    ctxMenu.CreatePopupMenu ();
    CString addText ("Add");
    ctxMenu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_CTX_AVAILABLE_MOD_ADD, (LPCTSTR) addText);
    CWnd * wind = AfxGetMainWnd ();
    POINT p;
    if (GetCursorPos (& p))
    {
        UINT result;
        if (result = ctxMenu.TrackPopupMenuEx (TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, p.x, p.y, wind, 0))
        {
            if (result == ID_CTX_AVAILABLE_MOD_ADD)
            {
                AddAvailableModsToSelected ();
                UpdateSelectedModulesListBox ();
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::OpenAvailableModsCtxMenu(WPARAM, LPARAM)@@@CConstruct.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OpenAvailableModsCtxMenu(WPARAM, LPARAM)@@@CConstruct.cpp>");
}
LRESULT CConstruct :: OpenSelectedModsCtxMenu (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::OpenSelectedModsCtxMenu(WPARAM, LPARAM)@@@CConstruct.cpp>");
    CMenu ctxMenu;
    ctxMenu.CreatePopupMenu ();
    CString removeText ("Remove");
    ctxMenu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_CTX_SEL_MODS_REMOVE, (LPCTSTR) removeText);
    CString NextVarText ("Next Variation");
    ctxMenu.InsertMenu (1, MF_BYPOSITION | MF_STRING, ID_CTX_SEL_MODS_NEXT, (LPCTSTR) NextVarText);
    CString PrevVariationText ("Previous Variation");
    ctxMenu.InsertMenu (2, MF_BYPOSITION | MF_STRING, ID_CTX_SEL_MODS_PREV, (LPCTSTR) PrevVariationText);
    CWnd * wind = AfxGetMainWnd ();
    POINT p;
    if (GetCursorPos (& p))
    {
        UINT result;
        if (result = ctxMenu.TrackPopupMenuEx (TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, p.x, p.y, wind, 0))
        {
            if (result == ID_CTX_SEL_MODS_REMOVE)
            {
                RemoveModulesFromSelected ();
                UpdateSelectedModulesListBox ();
            }

            else
            if (result == ID_CTX_SEL_MODS_NEXT)
            {
                SetNextVariation ();
            }

            else
            if (result == ID_CTX_SEL_MODS_PREV)
            {
                SetPrevVariation ();
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::OpenSelectedModsCtxMenu(WPARAM, LPARAM)@@@CConstruct.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::OpenSelectedModsCtxMenu(WPARAM, LPARAM)@@@CConstruct.cpp>");
}
void CConstruct :: AddAvailableModsToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::AddAvailableModsToSelected()@@@CConstruct.cpp>");
    int selectedCount = listbox_available_modules.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_available_modules.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_available_modules.GetText (selectedIndicies [i], selectedText);
        if (! ModuleIsSelected (selectedText))
        {
            SelectedModules -> push_back (std :: pair < std :: string, ClassModule * > (this -> AvailableModules -> at (selectedIndicies [i]).first, AvailableModules -> at (selectedIndicies [i]).second));
        }

    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::AddAvailableModsToSelected()@@@CConstruct.cpp>");
}
void CConstruct :: RemoveModulesFromSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::RemoveModulesFromSelected()@@@CConstruct.cpp>");
    int selectedCount = listbox_selected_modules.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_selected_modules.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_selected_modules.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        std :: string trimmedString;
        int pos = selectedString.find_first_of ('#', 0);
        if (pos == std :: string :: npos)
        {
            trimmedString = selectedString;
        }

        else
        {
            trimmedString = selectedString.substr (0, pos);
        }

        for (std :: vector < std :: pair < std :: string, ClassModule * >> :: iterator it = this -> SelectedModules -> begin (); it != this -> SelectedModules -> end (); it ++) {
            if (it -> first == trimmedString)
            {
                this -> SelectedModules -> erase (it);
                break;
            }

        }
    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CConstruct::RemoveModulesFromSelected()@@@CConstruct.cpp>");
}
void CConstruct :: UpdateSelectedModulesListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::UpdateSelectedModulesListBox()@@@CConstruct.cpp>");
    for (int i = 0; i < listbox_selected_modules.GetCount (); i ++) {
        CString moduleText;
        listbox_selected_modules.GetText (i, moduleText);
        CT2CA pszConvertedAnsiString (moduleText);
        std :: string moduleString (pszConvertedAnsiString);
        std :: string trimmedModuleString;
        int pos = moduleString.find_first_of ('#', 0);
        if (pos == std :: string :: npos)
        {
            trimmedModuleString = moduleString;
        }

        else
        {
            trimmedModuleString = moduleString.substr (0, pos);
        }

        bool found = false;
        for (std :: vector < std :: pair < std :: string, ClassModule * >> :: iterator it = SelectedModules -> begin (); it != SelectedModules -> end (); it ++) {
            if (it -> first == trimmedModuleString)
            {
                found = true;
                break;
            }

        }
        if (! found)
        {
            listbox_selected_modules.DeleteString (i);
            i = - 1;
        }

    }
    for (std :: vector < std :: pair < std :: string, ClassModule * >> :: iterator it = SelectedModules -> begin (); it != SelectedModules -> end (); it ++) {
        bool found = false;
        for (int i = 0; i < listbox_selected_modules.GetCount (); i ++) {
            CString moduleText;
            listbox_selected_modules.GetText (i, moduleText);
            CT2CA pszConvertedAnsiString (moduleText);
            std :: string moduleString (pszConvertedAnsiString);
            std :: string trimmedModuleString;
            int pos = moduleString.find_first_of ('#', 0);
            if (pos == std :: string :: npos)
            {
                trimmedModuleString = moduleString;
            }

            else
            {
                trimmedModuleString = moduleString.substr (0, pos);
            }

            if (it -> first == trimmedModuleString)
            {
                found = true;
                break;
            }

        }
        if (! found)
        {
            listbox_selected_modules.AddString (CString (it -> first.c_str ()));
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CConstruct::UpdateSelectedModulesListBox()@@@CConstruct.cpp>");
}
void CConstruct :: SetNextVariation ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::SetNextVariation()@@@CConstruct.cpp>");
    CString selectedText;
    int selIndex = listbox_selected_modules.GetCurSel ();
    listbox_selected_modules.GetText (selIndex, selectedText);
    CT2A text (selectedText);
    std :: string selectedString = text;
    int currentVariation;
    std :: string trimmedModuleName;
    int pos = selectedString.find_first_of ('#', 0);
    if (pos == std :: string :: npos)
    {
        currentVariation = 0;
        trimmedModuleName = selectedString;
    }

    else
    {
        currentVariation = atoi (selectedString.substr (pos + 1, selectedString.length ()).c_str ());
        trimmedModuleName = selectedString.substr (0, pos);
    }

    std :: map < std :: string, ClassModule * > :: iterator modPos = Global :: AllModulesList -> find (trimmedModuleName);
    std :: bitset < 11 > bits = modPos -> second -> variation_max;
    int numberOfVariations = bits.count ();
    if (currentVariation + 1 <= numberOfVariations)
    {
        currentVariation ++;
        std :: string updatedModuleName = trimmedModuleName + "#" + std :: to_string (currentVariation);
        listbox_selected_modules.DeleteString (selIndex);
        listbox_selected_modules.InsertString (selIndex, CString (updatedModuleName.c_str ()));
    }

    else
    {
        currentVariation = 0;
        listbox_selected_modules.DeleteString (selIndex);
        listbox_selected_modules.InsertString (selIndex, CString (trimmedModuleName.c_str ()));
    }

    if (currentVariation != 0)
    {
        for (std :: vector < std :: pair < std :: string, ClassModule * >> :: iterator it = this -> SelectedModules -> begin (); it != this -> SelectedModules -> end (); it ++) {
            if (it -> first == trimmedModuleName)
            {
                it -> second -> variation = (unsigned short) pow (2, currentVariation - 1);
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::SetNextVariation()@@@CConstruct.cpp>");
}
void CConstruct :: SetPrevVariation ()
{
InstrumentLogger::instance()->log_instrument_log("<CConstruct::SetPrevVariation()@@@CConstruct.cpp>");
    CString selectedText;
    int selIndex = listbox_selected_modules.GetCurSel ();
    listbox_selected_modules.GetText (selIndex, selectedText);
    CT2A text (selectedText);
    std :: string selectedString = text;
    int currentVariation;
    std :: string trimmedModuleName;
    int pos = selectedString.find_first_of ('#', 0);
    if (pos == std :: string :: npos)
    {
        currentVariation = 0;
        trimmedModuleName = selectedString;
    }

    else
    {
        currentVariation = atoi (selectedString.substr (pos + 1, selectedString.length ()).c_str ());
        trimmedModuleName = selectedString.substr (0, pos);
    }

    std :: map < std :: string, ClassModule * > :: iterator modPos = Global :: AllModulesList -> find (trimmedModuleName);
    std :: bitset < 11 > bits = modPos -> second -> variation_max;
    int numberOfVariations = bits.count ();
    if (numberOfVariations == 0)
    {
        currentVariation = 0;
        listbox_selected_modules.DeleteString (selIndex);
        listbox_selected_modules.InsertString (selIndex, CString (trimmedModuleName.c_str ()));
    }

    else
    if (currentVariation - 1 >= 0)
    {
        currentVariation --;
        if (currentVariation == 0)
        {
            currentVariation = 0;
            listbox_selected_modules.DeleteString (selIndex);
            listbox_selected_modules.InsertString (selIndex, CString (trimmedModuleName.c_str ()));
        }

        else
        {
            std :: string updatedModuleName = trimmedModuleName + "#" + std :: to_string (currentVariation);
            listbox_selected_modules.DeleteString (selIndex);
            listbox_selected_modules.InsertString (selIndex, CString (updatedModuleName.c_str ()));
        }

    }

    else
    {
        currentVariation = numberOfVariations;
        std :: string updatedModuleName = trimmedModuleName + "#" + std :: to_string (currentVariation);
        listbox_selected_modules.DeleteString (selIndex);
        listbox_selected_modules.InsertString (selIndex, CString (updatedModuleName.c_str ()));
    }

    if (currentVariation != 0)
    {
        for (std :: vector < std :: pair < std :: string, ClassModule * >> :: iterator it = this -> SelectedModules -> begin (); it != this -> SelectedModules -> end (); it ++) {
            if (it -> first == trimmedModuleName)
            {
                it -> second -> variation = (unsigned short) pow (2, currentVariation - 1);
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</CConstruct::SetPrevVariation()@@@CConstruct.cpp>");
}