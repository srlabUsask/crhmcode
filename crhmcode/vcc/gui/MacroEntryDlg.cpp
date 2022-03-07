#include "MacroEntryDlg.h"
#include "../../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (MacroEntryDlg, CDialogEx)
void MacroEntryDlg :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::DoDataExchange(CDataExchange * pDX)@@@MacroEntryDlg.cpp>");
    CDialogEx :: DoDataExchange (pDX);
    DDX_Control (pDX, ID_MACRO_EDIT_BOX, macroEditBox);
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::DoDataExchange(CDataExchange * pDX)@@@MacroEntryDlg.cpp>");
}BEGIN_MESSAGE_MAP (MacroEntryDlg, CDialogEx)
    ON_BN_CLICKED (ID_MACRO_SAVE, & MacroEntryDlg :: OnMacroSaveChanges)
    ON_BN_CLICKED (ID_MACRO_CANCEL, & MacroEntryDlg :: OnMacroCancelChanges)
    ON_COMMAND (ID_MACRO_FILE_OPEN, & MacroEntryDlg :: OnMacroFileOpen)
    ON_COMMAND (ID_MACRO_FILE_SAVE, & MacroEntryDlg :: OnMacroFileSave)
    ON_COMMAND (ID_MACRO_FILE_SAVE_AS, & MacroEntryDlg :: OnMacroFileSaveAs)
    ON_COMMAND (ID_MACRO_FILE_CREATE_GROUP, & MacroEntryDlg :: OnMacroFileCreateGroup)
    ON_COMMAND (ID_MACRO_FILE_CLEAR, & MacroEntryDlg :: OnMacroFileClear)
    ON_COMMAND (ID_MACRO_FILE_EXIT, & MacroEntryDlg :: OnMacroFileExit)
END_MESSAGE_MAP ()

MacroEntryDlg :: MacroEntryDlg (CWnd * pParent): CDialogEx (MacroEntry_DLG, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::MacroEntryDlg(CWnd * pParent): CDialogEx (MacroEntry_DLG, pParent)@@@MacroEntryDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::MacroEntryDlg(CWnd * pParent): CDialogEx (MacroEntry_DLG, pParent)@@@MacroEntryDlg.cpp>");
}
MacroEntryDlg :: ~MacroEntryDlg ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::~MacroEntryDlg()@@@MacroEntryDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::~MacroEntryDlg()@@@MacroEntryDlg.cpp>");
}
BOOL MacroEntryDlg :: OnInitDialog ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnInitDialog()@@@MacroEntryDlg.cpp>");
    CDialogEx :: OnInitDialog ();
    CString newline ("\r\n");
    CString cstr ("");
    macroEditBox.SetWindowText (cstr);
    for (size_t ii = 0; ii < Global :: MacroModulesList -> size (); ++ ii) {
        CString cstr1 (Global :: MacroModulesList -> at (ii).c_str ());
        cstr += cstr1 + newline;
    }
    macroEditBox.SetWindowText (cstr);
    ParaList = NULL;
    AKAList = NULL;
    GlobalModule.GrpCnt = 0;
    GlobalModule.StructCnt = 0;

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnInitDialog()@@@MacroEntryDlg.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnInitDialog()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroSaveChanges ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroSaveChanges()@@@MacroEntryDlg.cpp>");
    std :: vector < std :: string > * Lines = new std :: vector < std :: string > ();
    Lines = GetLinesFromEditBox ();
    Global :: MacroModulesList -> clear ();
    for (size_t ii = 0; ii < Lines -> size (); ++ ii) {
        string S;
        if (Lines -> at (ii).length () == 0)
        {
            S = " ";
        }

        else
        {
            S = Common :: trimright (Lines -> at (ii));
        }

        Global :: MacroModulesList -> push_back (S);
    }
    this -> OnOK ();
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroSaveChanges()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroCancelChanges ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroCancelChanges()@@@MacroEntryDlg.cpp>");
    this -> OnCancel ();
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroCancelChanges()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroFileOpen ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroFileOpen()@@@MacroEntryDlg.cpp>");
    FileDialog * openfile = new FileDialog ();
    bool opened = openfile -> Open ("mcr");
    if (opened)
    {
        std :: string filepath = openfile -> filepath;
        std :: vector < std :: string > * slist = new std :: vector < std :: string > ();
        ifstream infile (filepath.c_str ());
        string line;
        while (std :: getline (infile, line)) {
            slist -> push_back (line);
        }
        macroEditBox.SetWindowText (_T (""));
        AddStringsToEditBox (slist);
        this -> macrofile = openfile;
    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroFileOpen()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroFileSave ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroFileSave()@@@MacroEntryDlg.cpp>");
    if (macrofile != NULL)
    {
        if (macrofile -> filepath.length () > 0)
        {
            DoSave ();
        }

        else
        {
            SaveAsClick ();
        }

    }

    else
    {
        SaveAsClick ();
    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroFileSave()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroFileSaveAs ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroFileSaveAs()@@@MacroEntryDlg.cpp>");
    SaveAsClick ();
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroFileSaveAs()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroFileCreateGroup ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroFileCreateGroup()@@@MacroEntryDlg.cpp>");
    CreateGroupClick ();
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroFileCreateGroup()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroFileClear ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroFileClear()@@@MacroEntryDlg.cpp>");
    macroEditBox.SetSel (0, - 1);
    macroEditBox.Clear ();
    macroEditBox.RedrawWindow ();
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroFileClear()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: OnMacroFileExit ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::OnMacroFileExit()@@@MacroEntryDlg.cpp>");
    this -> OnCancel ();
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::OnMacroFileExit()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: DoSave ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::DoSave()@@@MacroEntryDlg.cpp>");
    std :: vector < std :: string > * Lines = new std :: vector < std :: string > ();
    int start;
    int end;
    macroEditBox.GetSel (start, end);
    if (start == end)
    {
        Lines = GetLinesFromEditBox ();
        ofstream file;
        file.open (macrofile -> filepath.c_str ());
        for (size_t it = 0; it < Lines -> size (); it ++) {
            file << Lines -> at (it).c_str () << endl;
        }
        file.close ();
    }

    else
    {
        Lines = GetSelectedLinesFromEditBox ();
        ofstream file;
        file.open (macrofile -> filepath.c_str ());
        for (size_t it = 0; it < Lines -> size (); it ++) {
            file << Lines -> at (it).c_str () << endl;
        }
        file.close ();
    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::DoSave()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: SaveAsClick ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::SaveAsClick()@@@MacroEntryDlg.cpp>");
    macrofile = new FileDialog ();
    bool opened = macrofile -> Save ("mcr");
    if (opened)
    {
        DoSave ();
    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::SaveAsClick()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: AddStringsToEditBox (std :: vector < std :: string > * tstr)
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::AddStringsToEditBox(std :: vector < std :: string > * tstr)@@@MacroEntryDlg.cpp>");
    CString cstr1;
    macroEditBox.GetWindowText (cstr1);
    CString newline ("\r\n");
    CString cstr2, cstr;
    for (size_t i = 0; i < tstr -> size (); i ++) {
        cstr = tstr -> at (i).c_str ();
        if (tstr -> at (i).length () != 0)
        {
            cstr2 += cstr + newline;
        }

    }
    CString finalcstr;
    if (cstr1.GetLength () > 0)
    {
        finalcstr = cstr1 + newline + cstr2;
    }

    else
    {
        finalcstr = cstr2;
    }

    macroEditBox.SetWindowTextW (finalcstr);
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::AddStringsToEditBox(std :: vector < std :: string > * tstr)@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: AddStringsToEditBox (string tstr)
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::AddStringsToEditBox(string tstr)@@@MacroEntryDlg.cpp>");
    CString cstr1;
    macroEditBox.GetWindowText (cstr1);
    CString newline ("\r\n");
    CString cstr2 (tstr.c_str ());
    CString finalcstr;
    if (cstr1.GetLength () > 0)
    {
        finalcstr = cstr1 + newline + cstr2;
    }

    else
    {
        finalcstr = cstr2;
    }

    macroEditBox.SetWindowTextW (finalcstr);
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::AddStringsToEditBox(string tstr)@@@MacroEntryDlg.cpp>");
}
std :: vector < std :: string > * MacroEntryDlg :: GetLinesFromEditBox ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::GetLinesFromEditBox()@@@MacroEntryDlg.cpp>");
    std :: vector < std :: string > * tstring = new std :: vector < std :: string > ();
    CString cstr1;
    macroEditBox.GetWindowText (cstr1);
    string str = CT2A (cstr1);
    int l = str.length ();
    string temp = "";
    for (int i = 0; i < l; i ++) {
        if (str [i] != '\r' && str [i] != '\n')
        {
            temp += str [i];
        }

        else
        {
            if (temp.length () > 0)
            {
                tstring -> push_back (temp);
                temp = "";
            }

        }

    }
    if (temp.length () > 0)
    {
        tstring -> push_back (temp);
    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::GetLinesFromEditBox()@@@MacroEntryDlg.cpp>");
    return tstring;
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::GetLinesFromEditBox()@@@MacroEntryDlg.cpp>");
}
std :: vector < std :: string > * MacroEntryDlg :: GetSelectedLinesFromEditBox ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::GetSelectedLinesFromEditBox()@@@MacroEntryDlg.cpp>");
    std :: vector < std :: string > * tstring = new std :: vector < std :: string > ();
    CString cstr1;
    macroEditBox.GetWindowText (cstr1);
    int start, end;
    CString cstr2;
    macroEditBox.GetSel (start, end);
    cstr2 = cstr1.Mid (start, end - start);
    string str = CT2A (cstr2);
    int l = str.length ();
    string temp = "";
    for (int i = 0; i < l; i ++) {
        if (str [i] != '\r' && str [i] != '\n')
        {
            temp += str [i];
        }

        else
        {
            if (temp.length () > 0)
            {
                tstring -> push_back (temp);
                temp = "";
            }

        }

    }
    if (temp.length () > 0)
    {
        tstring -> push_back (temp);
    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::GetSelectedLinesFromEditBox()@@@MacroEntryDlg.cpp>");
    return tstring;
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::GetSelectedLinesFromEditBox()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: CreateGroupClick ()
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::CreateGroupClick()@@@MacroEntryDlg.cpp>");
    std :: string Txt;
    std :: string S;
    std :: string MacroName;
    std :: string GrpName;
    size_t Indx;
    FileDialog * openfile = new FileDialog ();
    bool opened = openfile -> Open ("prj");
    if (opened == false)
    {

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::CreateGroupClick()@@@MacroEntryDlg.cpp>");
        return;
    }

    MacroName = openfile -> filename;
    Indx = MacroName.rfind ("\\");
    if (Indx != std :: string :: npos)
    {
        MacroName = MacroName.substr (Indx + 1, MacroName.length ());
    }

    Indx = MacroName.rfind (".");
    if (Indx != std :: string :: npos)
    {
        std :: string AA;
        GlobalModule.GrpCnt ++;
        Common :: GroupEnding (AA, GlobalModule.GrpCnt);
        MacroName = MacroName.substr (0, Indx) + "_Grp" + AA;
    }

    if (! isalpha (MacroName [0]))
    {
        MessageBox (_T ("Alpha characters are upper-/lowercase characters from A through Z. Project file name must begin with an alpha character."), MB_OK);

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::CreateGroupClick()@@@MacroEntryDlg.cpp>");
        return;
    }

    GrpName = MacroName;
    if (GlobalModule.GrpCnt > 1)
    {
    }

    std :: vector < std :: string > * ProjectFile = new std :: vector < std :: string > ();
    ModuleList = new std :: vector < std :: string > ();
    MacroList = new std :: vector < std :: pair < std :: string, Module * >> ();
    DefinedList = new std :: vector < std :: pair < std :: string, Module * >> ();
    if (! ParaList)
    {
        ParaList = new std :: vector < std :: string >;
        ParaList -> push_back ("Parameters for created Group Macro");
        ParaList -> push_back ("#####");
    }

    if (! AKAList)
    {
        AKAList = new std :: vector < std :: string > ();
    }

    ifstream infile (openfile -> filepath.c_str ());
    string line;
    while (std :: getline (infile, line)) {
        ProjectFile -> push_back (line);
    }
    size_t ThisEnd = 0;
    Module * ThisModule;
    std :: vector < std :: string > * Lines = new std :: vector < std :: string > ();
    Lines = GetLinesFromEditBox ();
    while (ThisEnd < Lines -> size ()) {
        if (Lines -> at (ThisEnd).length () == 0)
        {
            continue;
        }

        while (ThisEnd < Lines -> size () && (Txt = Common :: trimleft (Lines -> at (ThisEnd)), Txt [0] == '/')) {
            ++ ThisEnd;
        }
        Indx = Txt.find (" ");
        if (Indx)
        {
            Txt = Txt.substr (0, Indx);
        }

        ThisModule = new Module;
        ThisModule -> head = ThisEnd;
        do S = Common :: trim (Lines -> at (++ ThisEnd));
        while (S [0] == '/');
        if (S.find ("declgroup") != std :: string :: npos)
        {
            ++ ThisModule -> GrpCnt;
            ThisModule -> isGroup = true;
        }

        if (S.find ("declstruct") != std :: string :: npos)
        {
            ++ ThisModule -> StructCnt;
            ThisModule -> isStruct = true;
        }

        while (ThisEnd < Lines -> size () && ! (S = Common :: trim (Lines -> at (ThisEnd)), S.substr (0, 3) == "end" && (S.length () == 3 || S [3] == ' ' || S [3] == '/'))) {
            ++ ThisEnd;
        }
        ThisModule -> tail = ThisEnd ++;
        DefinedList -> push_back (std :: pair < std :: string, Module * > (Txt, ThisModule));
    }
    for (size_t ii = 0; ii < ProjectFile -> size (); ++ ii) {
        Txt = ProjectFile -> at (ii);
        if (Txt == "Dimensions:")
        {
            std :: string numHRU = ProjectFile -> at (ii + 2).substr (4, 10);
            Global :: nhru = std :: stoi (numHRU);
            if (Global :: nhru > Global :: maxhru)
            {
                Global :: maxhru = Global :: nhru;
            }

            std :: string numLay = ProjectFile -> at (ii + 3).substr (4, 10);
            Global :: nlay = std :: stoi (numLay);
            if (Global :: nlay > Global :: maxlay)
            {
                Global :: maxlay = Global :: nlay;
            }

        }

        if (Txt == "Parameters:")
        {
            ++ ii;
            ++ ii;
            while (ProjectFile -> at (ii) [0] != '#') {
                if (ProjectFile -> at (ii) [0] == '\'' || ProjectFile -> at (ii) [0] == '-' || iswdigit (ProjectFile -> at (ii) [0]))
                {
                    ParaList -> push_back (ProjectFile -> at (ii));
                }

                else
                {
                    Indx = ProjectFile -> at (ii).find (" ");
                    S = ProjectFile -> at (ii).substr (Indx + 1, ProjectFile -> at (ii).length () - Indx - 1);
                    ParaList -> push_back (GrpName + " " + S);
                }

                ++ ii;
            }
            continue;
        }

        if (Txt == "Macros:")
        {
            ++ ii;
            ++ ii;
            ThisModule = NULL;
            while (ProjectFile -> at (ii) [0] != '#') {
                while (ii < ProjectFile -> size () && (S = Common :: trimleft (ProjectFile -> at (ii)), S [0] == '/')) ++ ii;
                S = S.substr (0, S.length () - 2);
                if (! ThisModule)
                {
                    if (Indx = S.find (" "))
                    {
                        S = S.substr (0, Indx);
                    }

                    ThisModule = new Module;
                    ThisModule -> head = MacroList -> size ();
                    MacroList -> push_back (std :: pair < std :: string, Module * > (S, NULL));
                }

                else
                {
                    if (S.find ("declgroup"))
                    {
                        ++ ThisModule -> GrpCnt;
                        ThisModule -> isGroup = true;
                    }

                    if (S.find ("declstruct"))
                    {
                        ++ ThisModule -> StructCnt;
                        ThisModule -> isStruct = true;
                    }

                    MacroList -> push_back (std :: pair < std :: string, Module * > (S, NULL));
                    if (S.substr (0, 3) == "end" && (S.length () == 3 || S [3] == ' ' || S [3] == '/'))
                    {
                        ThisModule -> tail = MacroList -> size ();
                        MacroList -> at (ThisModule -> head).second = ThisModule;
                        ThisModule = NULL;
                    }

                }

                ++ ii;
            }
            continue;
        }

    }
    for (size_t ii = 0; ii < ProjectFile -> size (); ++ ii) {
        Txt = ProjectFile -> at (ii);
        if (Txt == "AKAs:")
        {
            ++ ii;
            ++ ii;
            while (ProjectFile -> at (ii) [0] != '#') {
                string S = Common :: trim (ProjectFile -> at (ii));
                int Indx = S.find (" ");
                string type = S.substr (0, Indx);
                S = S.substr (Indx + 1, S.length () - Indx - 1);
                Indx = S.find (" ");
                string module = S.substr (0, Indx);
                S = S.substr (Indx + 1, S.length () - Indx - 1);
                Indx = S.find (" ");
                string name = S.substr (0, Indx);
                S = S.substr (Indx + 1, S.length () - Indx - 1);
                string alias;
                Indx = S.find (" ");
                if (Indx == - 1)
                {
                    alias = S;
                    ParaList -> push_back (type + " " + GrpName + " " + name + " " + alias);
                }

                else
                {
                    alias = S.substr (0, Indx);
                    string source = S.substr (Indx + 1, S.length () - Indx - 1);
                    bool sourceInMacroList = false;
                    for (size_t it = 0; it < MacroList -> size (); it ++) {
                        if (MacroList -> at (it).first == source)
                        {
                            sourceInMacroList = true;
                            break;
                        }

                    }
                    if (sourceInMacroList)
                    {
                        AKAList -> push_back (type + " " + GrpName + " " + name + " " + alias + " " + source);
                    }

                    else
                    {
                        AKAList -> push_back (type + " " + GrpName + " " + name + " " + alias + " " + GrpName);
                    }

                }

                ++ ii;
            }
        }

        if (Txt == "Modules:")
        {
            ++ ii;
            ++ ii;
            int indxOfS = - 1;
            for (size_t it = 0; it < DefinedList -> size (); it ++) {
                if (DefinedList -> at (it).first == S)
                {
                    indxOfS = it;
                    break;
                }

            }
            while (indxOfS > - 1) {
                ++ S [S.length () - 1];
                indxOfS = - 1;
                for (size_t it = 0; it < DefinedList -> size (); it ++) {
                    if (DefinedList -> at (it).first == S)
                    {
                        indxOfS = it;
                        break;
                    }

                }
            }
            ModuleList -> push_back (GrpName);
            ModuleList -> push_back ("declgroup " + to_string (Global :: nhru));
            while (ProjectFile -> at (ii) [0] != '#') {
                S = Common :: trim (ProjectFile -> at (ii));
                if (S.find ("+") > - 1)
                {
                    ++ ii;
                    continue;
                }

                if (S.find (" "))
                {
                    S = S.substr (0, S.find (" "));
                }

                ModuleList -> push_back (S);
                ++ ii;
            }
            ModuleList -> push_back ("command");
            ModuleList -> push_back ("end");
            break;
        }

    }
    ProjectFile -> clear ();
    int EndList = (int) ModuleList -> size () - 2;
    for (int ii = 2; ii < EndList; ++ ii) {
        AddGroup (ii);
    }
    AddStringsToEditBox (ModuleList);
    delete ProjectFile;
    delete ModuleList;
    for (size_t ii = 0; ii < MacroList -> size (); ++ ii) {
        delete MacroList -> at (ii).second;
    }
    delete MacroList;
    for (size_t ii = 0; ii < DefinedList -> size (); ++ ii) {
        delete DefinedList -> at (ii).second;
    }
    delete DefinedList;
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::CreateGroupClick()@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: AddGroup (int ii)
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::AddGroup(int ii)@@@MacroEntryDlg.cpp>");
    int Indx;
    bool foundInDefinedList = false;
    for (size_t it = 0; it < DefinedList -> size (); it ++) {
        if (DefinedList -> at (it).first == ModuleList -> at (ii))
        {
            foundInDefinedList = true;
            break;
        }

    }
    if (foundInDefinedList == false)
    {
        Indx = - 1;
        for (size_t it = 0; it < MacroList -> size (); it ++) {
            if (MacroList -> at (it).first == ModuleList -> at (ii))
            {
                Indx = it;
                break;
            }

        }
        if (Indx > - 1)
        {
            Module * ThisModule = MacroList -> at (Indx).second;
            AddSupport (ThisModule);
            for (int jj = ThisModule -> head; jj < ThisModule -> tail; ++ jj) {
                AddStringsToEditBox (MacroList -> at (jj).first);
            }
            ThisModule -> avail = true;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::AddGroup(int ii)@@@MacroEntryDlg.cpp>");
}
void MacroEntryDlg :: AddSupport (Module * ThisModule)
{
InstrumentLogger::instance()->log_instrument_log("<MacroEntryDlg::AddSupport(Module * ThisModule)@@@MacroEntryDlg.cpp>");
    int Indx;
    for (int ii = ThisModule -> head + 2; ii < ThisModule -> tail - 2; ++ ii) {
        bool foundInDefinedList = false;
        for (size_t it = 0; it < DefinedList -> size (); it ++) {
            if (DefinedList -> at (it).first == MacroList -> at (it).first)
            {
                foundInDefinedList = true;
                break;
            }

        }
        if (foundInDefinedList)
        {

InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::AddSupport(Module * ThisModule)@@@MacroEntryDlg.cpp>");
            return;
        }

        Indx = ii;
        if (MacroList -> at (Indx).second != NULL)
        {
            Module * ThisModule = MacroList -> at (Indx).second;
            if (ThisModule -> avail)
            {
                continue;
            }

            if (ThisModule -> isGroup || ThisModule -> isStruct)
            {
                AddSupport (ThisModule);
                ThisModule -> avail = true;
            }

            for (int jj = Indx; jj < ThisModule -> tail; ++ jj) {
                AddStringsToEditBox (MacroList -> at (jj).first);
            }
            ThisModule -> avail = true;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</MacroEntryDlg::AddSupport(Module * ThisModule)@@@MacroEntryDlg.cpp>");
}