#include "CRHMmainDlg.h"
#include "../../src/core/InstrumentLogger.h"

CString globFileName;
IMPLEMENT_DYNAMIC (CRHMmainDlg, CDialogEx)
CRHMmainDlg :: CRHMmainDlg (CWnd * pParent): CDialogEx (CRHMmainDialog, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::CRHMmainDlg(CWnd * pParent): CDialogEx (CRHMmainDialog, pParent)@@@CRHMmainDlg.cpp>");
    CRHMmain * test = CRHMmain :: getInstance ();
    this -> openObsFiles = new std :: map < UINT, std :: pair < std :: string, std :: string >> ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::CRHMmainDlg(CWnd * pParent): CDialogEx (CRHMmainDialog, pParent)@@@CRHMmainDlg.cpp>");
}
CRHMmainDlg :: ~CRHMmainDlg ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::~CRHMmainDlg()@@@CRHMmainDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::~CRHMmainDlg()@@@CRHMmainDlg.cpp>");
}
CRHMmainDlg :: CRHMmainDlg (string argumentfile)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::CRHMmainDlg(string argumentfile)@@@CRHMmainDlg.cpp>");
    CRHMmain * test = CRHMmain :: getInstance ();
    test -> FormCreate ();
    this -> openObsFiles = new std :: map < UINT, std :: pair < std :: string, std :: string >> ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::CRHMmainDlg(string argumentfile)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::DoDataExchange(CDataExchange * pDX)@@@CRHMmainDlg.cpp>");
    CDialogEx :: DoDataExchange (pDX);
    DDX_Control (pDX, ID_ALL_VAR_LIST_BOX, listbox_all_variables);
    listbox_all_variables.setMessageCode (UWM_OPEN_CTX_ALL_VAR);
    DDX_Control (pDX, ID_SEL_VAR_LIST_BOX, listbox_sel_variables);
    listbox_sel_variables.setMessageCode (UWM_OPEN_CTX_SEL_VAR);
    DDX_Control (pDX, ID_ALL_OBS_LIST_BOX, listbox_all_observations);
    listbox_all_observations.setMessageCode (UWM_OPEN_CTX_ALL_OBS);
    DDX_Control (pDX, ID_SEL_OBS_LIST_BOX, listbox_sel_observations);
    listbox_sel_observations.setMessageCode (UWM_OPEN_CTX_SEL_OBS);
    DDX_Control (pDX, IDC_TCHART1, tchart);
    DDX_Control (pDX, ID_START_DATE_PICKER, StartDatePicker);
    DDX_Control (pDX, ID_END_DATE_PICKER, EndDatePicker);
    DDX_Control (pDX, ID_FLIP_TICKS, FlipTicks);
    FlipTicks.setMessageCodeLeft (UWM_FLIP_TICKS_LEFT);
    FlipTicks.setMessageCodeRight (UWM_FLIP_TICKS_RIGHT);
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::DoDataExchange(CDataExchange * pDX)@@@CRHMmainDlg.cpp>");
}BEGIN_MESSAGE_MAP (CRHMmainDlg, CDialogEx)
    ON_COMMAND (ID_FILE_OPEN, & CRHMmainDlg :: OnFileOpen)
    ON_COMMAND (ID_FILE_SAVE, & CRHMmainDlg :: OnFileSave)
    ON_COMMAND (ID_FILE_SAVE_AS, & CRHMmainDlg :: OnFileSaveAs)
    ON_COMMAND (ID_FILE_CLOSE, & CRHMmainDlg :: OnFileClose)
    ON_COMMAND (ID_AUTO_RUN, & CRHMmainDlg :: OnAutoRun)
    ON_COMMAND (ID_AUTO_EXIT, & CRHMmainDlg :: OnAutoExit)
    ON_COMMAND (ID_MENU_EXIT, & CRHMmainDlg :: OnExit)
    ON_COMMAND (ID_MAIN_LOG_ALL, & CRHMmainDlg :: OnLogAll)
    ON_COMMAND (ID_MAIN_LOG_LAST, & CRHMmainDlg :: OnLogLast)
    ON_COMMAND (ID_EXTRACT_GROUP, & CRHMmainDlg :: OnExtractGroup)
    ON_COMMAND (ID_VIEW_HIERARCHY, & CRHMmainDlg :: OnViewHierarchy)
    ON_COMMAND (ID_OPEN_OBS, & CRHMmainDlg :: OnOpenObservation)
    ON_COMMAND_RANGE (ID_OPEN_OBS_FILE_FIRST, ID_OPEN_OBS_FILE_LAST, & CRHMmainDlg :: OnClickOnOpenFile)
    ON_COMMAND (ID_CLOSE_ALL_OBS, & CRHMmainDlg :: OnCloseAllObservations)
    ON_COMMAND (ID_BUILD_CONSTRUCT, & CRHMmainDlg :: OnBuildConstruct)
    ON_COMMAND (ID_CLEAR_MODULES, & CRHMmainDlg :: OnClearModules)
    ON_COMMAND (ID_BUILD_MACRO, & CRHMmainDlg :: OnBuildMacro)
    ON_COMMAND (ID_STATE_OPEN_INIT_STATE, & CRHMmainDlg :: OnClickOnOpenInitState)
    ON_COMMAND (ID_OPEN_INIT_FILE, & CRHMmainDlg :: CloseOpenInitFile)
    ON_COMMAND (ID_STATE_SAVE_STATE, & CRHMmainDlg :: OnSaveState)
    ON_COMMAND (ID_STATE_SAVE_TO, & CRHMmainDlg :: OnSaveStateTo)
    ON_COMMAND (ID_STATE_SAVE_STATE_AS, & CRHMmainDlg :: OnSaveStateAs)
    ON_COMMAND (ID_RUN_RUNMODEL, & CRHMmainDlg :: OnRunRunmodel)
    ON_COMMAND (ID_EXPORT, & CRHMmainDlg :: OnExport)
    ON_COMMAND (ID_FLOWDIAGRAMS_SHOWDIAGRAM, & CRHMmainDlg :: OnFlowdiagramsShowdiagram)
    ON_COMMAND (ID_HELP_ABOUT, & CRHMmainDlg :: OnHelpAbout)
    ON_BN_CLICKED (ID_HRU_DIM_DECREASE, & CRHMmainDlg :: DecreaseHRUDimension)
    ON_BN_CLICKED (ID_HRU_DIM_INCREASE, & CRHMmainDlg :: IncreaseHRUDimension)
    ON_BN_CLICKED (ID_OBS_DIM_DECREASE, & CRHMmainDlg :: DecreaseObsDimension)
    ON_BN_CLICKED (ID_OBS_DIM_INCREASE, & CRHMmainDlg :: IncreaseObsDimension)
    ON_LBN_DBLCLK (ID_ALL_VAR_LIST_BOX, & CRHMmainDlg :: OnDblClkAllVarListBox)
    ON_LBN_DBLCLK (ID_SEL_VAR_LIST_BOX, & CRHMmainDlg :: OnDblClkSelVarListBox)
    ON_LBN_SELCHANGE (ID_ALL_VAR_LIST_BOX, & CRHMmainDlg :: OnVariableSelectChange)
    ON_MESSAGE (UWM_OPEN_CTX_ALL_VAR, & CRHMmainDlg :: OpenAllVarCtxMenu)
    ON_MESSAGE (UWM_OPEN_CTX_SEL_VAR, & CRHMmainDlg :: OpenSelVarCtxMenu)
    ON_LBN_DBLCLK (ID_ALL_OBS_LIST_BOX, & CRHMmainDlg :: OnDblClkAllObsListBox)
    ON_LBN_DBLCLK (ID_SEL_OBS_LIST_BOX, & CRHMmainDlg :: OnDblClkSelObsListBox)
    ON_LBN_SELCHANGE (ID_ALL_OBS_LIST_BOX, & CRHMmainDlg :: OnObservationSelectChange)
    ON_MESSAGE (UWM_OPEN_CTX_ALL_OBS, & CRHMmainDlg :: OpenAllObsCtxMenu)
    ON_MESSAGE (UWM_OPEN_CTX_SEL_OBS, & CRHMmainDlg :: OpenSelObsCtxMenu)
    ON_NOTIFY (DTN_DATETIMECHANGE, ID_START_DATE_PICKER, & CRHMmainDlg :: OnStartDateChange)
    ON_NOTIFY (DTN_DATETIMECHANGE, ID_END_DATE_PICKER, & CRHMmainDlg :: OnEndDateChange)
    ON_MESSAGE (UWM_FLIP_TICKS_LEFT, & CRHMmainDlg :: OnLeftClickFlipTicks)
    ON_MESSAGE (UWM_FLIP_TICKS_RIGHT, & CRHMmainDlg :: OnRightClickFlipTicks)
    ON_MESSAGE (UWM_AUTO_RUN, & CRHMmainDlg :: OnAutoRunMessage)
END_MESSAGE_MAP ()

BOOL CRHMmainDlg :: OnInitDialog ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnInitDialog()@@@CRHMmainDlg.cpp>");
    CDialogEx :: OnInitDialog ();
    std :: string str1 = "The Cold Regions Hydrological Model";
    CString cStr (str1.c_str ());
    SetDlgItemText (ID_OBS_LAY_DIM_LABEL, L"OBS");
    SetDlgItemText (ID_HRU_DIM_DISPLAY, _T ("1"));
    SetDlgItemText (ID_OBS_DIM_DISPLAY, _T ("1"));
    SetDlgItemText (ID_OBS_HELP_DISPLAY, _T (""));
    SetDlgItemText (ID_VAR_HELP_DISPLAY, _T (""));
    CFont * varHelpFont = new CFont ();
    varHelpFont -> CreatePointFont (96, _T ("Ariel"));
    GetDlgItem (ID_VAR_HELP_DISPLAY) -> SetFont (varHelpFont);
    CFont * obsHelpFont = new CFont ();
    obsHelpFont -> CreatePointFont (96, _T ("Ariel"));
    GetDlgItem (ID_OBS_HELP_DISPLAY) -> SetFont (obsHelpFont);
    loadGuiComponents ();
    delete varHelpFont;
    delete obsHelpFont;

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnInitDialog()@@@CRHMmainDlg.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnInitDialog()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: ProcessCommandLineArgument ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::ProcessCommandLineArgument()@@@CRHMmainDlg.cpp>");
    CRHMmain * test = CRHMmain :: getInstance ();
    test -> FormCreate ();
    test -> DoPrjOpen (ProjectFileArgument, "");
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::ProcessCommandLineArgument()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: loadGuiComponents ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::loadGuiComponents()@@@CRHMmainDlg.cpp>");
    listbox_all_variables.ResetContent ();
    listbox_sel_variables.ResetContent ();
    listbox_all_observations.ResetContent ();
    listbox_sel_observations.ResetContent ();
    CRHMmain * crhm_core = CRHMmain :: getInstance ();
    std :: map < std :: string, ClassVar * > * variables = CRHMmain :: getInstance () -> getVariables ();
    std :: map < std :: string, ClassVar * > :: iterator it;
    for (it = variables -> begin (); it != variables -> end (); it ++) {
        std :: string s = it -> first;
        CString cvariables (s.c_str ());
        if (s != "t")
        {
            listbox_all_variables.AddString (cvariables);
        }

    }
    std :: map < std :: string, ClassVar * > * observations = CRHMmain :: getInstance () -> getObservations ();
    std :: map < std :: string, ClassVar * > :: iterator observationIt;
    for (observationIt = observations -> begin (); observationIt != observations -> end (); observationIt ++) {
        std :: string s = observationIt -> first;
        CString observations (s.c_str ());
        listbox_all_observations.AddString (observations);
    }
    std :: list < std :: pair < std :: string, ClassVar * >> * sel_variables = CRHMmain :: getInstance () -> getSelectedVariables ();
    for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = sel_variables -> begin (); it != sel_variables -> end (); it ++) {
        std :: string s = it -> first;
        CString observations (s.c_str ());
        listbox_sel_variables.AddString (observations);
    }
    std :: list < std :: pair < std :: string, TSeries * >> * sel_observations = CRHMmain :: getInstance () -> getSelectedObservations ();
    for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = sel_observations -> begin (); it != sel_observations -> end (); it ++) {
        std :: string s = it -> first;
        CString observations (s.c_str ());
        listbox_sel_observations.AddString (observations);
    }
    CRHMmain * main = CRHMmain :: getInstance ();
    SetTime (main -> GetStartDate (), main -> GetEndDate ());
    if (main -> getAutoRun ())
    {
        CMenu * menu = GetMenu ();
        menu -> CheckMenuItem (ID_AUTO_RUN, MF_CHECKED);
    }

    else
    {
        CMenu * menu = GetMenu ();
        menu -> CheckMenuItem (ID_AUTO_RUN, MF_UNCHECKED);
    }

    if (main -> getAutoExit ())
    {
        CMenu * menu = GetMenu ();
        menu -> CheckMenuItem (ID_AUTO_EXIT, MF_CHECKED);
    }

    else
    {
        CMenu * menu = GetMenu ();
        menu -> CheckMenuItem (ID_AUTO_RUN, MF_UNCHECKED);
    }

    if (main -> getReportAll ())
    {
        CMenu * menu = GetMenu ();
        menu -> CheckMenuItem (ID_MAIN_LOG_ALL, MF_CHECKED);
        menu -> CheckMenuItem (ID_MAIN_LOG_LAST, MF_UNCHECKED);
    }

    else
    {
        CMenu * menu = GetMenu ();
        menu -> CheckMenuItem (ID_MAIN_LOG_ALL, MF_UNCHECKED);
        menu -> CheckMenuItem (ID_MAIN_LOG_LAST, MF_CHECKED);
    }

    if (crhm_core -> getAutoRun ())
    {
        ShowWindow (1);
        CenterWindow ();
        UpdateWindow ();
        PostMessage (UWM_AUTO_RUN, 0, 0);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::loadGuiComponents()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: InitModules ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::InitModules()@@@CRHMmainDlg.cpp>");
    Global :: BuildFlag = TBuild :: DECL;
    Box1Disply = (int) TVISIBLE :: OUTPUT;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        modIt -> second -> nhru = Global :: nhru;
        modIt -> second -> decl ();
    }
    Global :: CurrentModuleRun = Global :: OurModulesList -> rbegin () -> first;
    GetAllVariables ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::InitModules()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: GetAllVariables ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::GetAllVariables()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    CConstruct * buildform = new CConstruct ();
    ClassVar * thisVar;
    MapVar :: iterator itVar;
    string Labels [] = {"Variables", "Variables by Module", "Diagnostic Variables", "Private Variables"};
    string Newname;
    ++ Box1Disply;
    if (Box1Disply > (int) TVISIBLE :: PRIVATE)
    {
        Box1Disply = (int) TVISIBLE :: OUTPUT;
    }

    model -> AllVariables -> clear ();
    if (Box1Disply == (int) TVISIBLE :: OUTPUT)
    {
        for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
            thisVar = (* itVar).second;
            if (thisVar -> varType < TVar :: Read && thisVar -> visibility == TVISIBLE :: USUAL && thisVar -> dimen != TDim :: NREB && (thisVar -> values || thisVar -> ivalues) && ! thisVar -> FileData)
            {
                Newname = DeclObsName (thisVar);
                if (model -> AllVariables -> count (Newname) == 0)
                {
                    model -> AllVariables -> insert (std :: pair < std :: string, ClassVar * > (Newname, thisVar));
                }

            }

        }
    }

    else
    {
        string S0;
        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
            string S = modIt -> first;
            ClassModule * thisModule = modIt -> second;
            if (S0 != S)
            {
                if (! (S0.length () == 0))
                {
                }

                S0 = S;
                if (thisModule -> variation != 0)
                {
                    string AA ("#0");
                    AA [1] += (char) (log (thisModule -> variation) / log (2) + 1);
                    S0 += AA;
                }

                S0 = "   --- " + S0;
            }

            switch (Box1Disply) {
            case (int) TVISIBLE :: USUAL:
                for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
                    thisVar = (* itVar).second;
                    if (S == thisVar -> module.c_str () && thisVar -> visibility == TVISIBLE :: USUAL && Variation_Decide (thisVar -> variation_set, thisModule -> variation) && thisVar -> dimen != TDim :: NREB && (thisVar -> values || thisVar -> ivalues) && ! thisVar -> FileData)
                    {
                        Newname = DeclObsName (thisVar);
                        if (model -> AllVariables -> count (Newname) == 0)
                        {
                            model -> AllVariables -> insert (std :: pair < std :: string, ClassVar * > (Newname, thisVar));
                        }

                    }

                }
                break;
            case (int) TVISIBLE :: DIAGNOSTIC:
                for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
                    thisVar = (* itVar).second;
                    if (S == thisVar -> module.c_str () && thisVar -> visibility == TVISIBLE :: DIAGNOSTIC && thisVar -> dimen != TDim :: NREB && (thisVar -> values || thisVar -> ivalues) && ! thisVar -> FileData)
                    {
                        Newname = DeclObsName (thisVar);
                        if (model -> AllVariables -> count (Newname) == 0)
                        {
                            model -> AllVariables -> insert (std :: pair < std :: string, ClassVar * > (Newname, thisVar));
                        }

                    }

                }
                break;
            case (int) TVISIBLE :: PRIVATE:
                for (itVar = Global :: MapVars.begin (); itVar != Global :: MapVars.end (); itVar ++) {
                    thisVar = (* itVar).second;
                    if (S == thisVar -> module.c_str () && thisVar -> visibility == TVISIBLE :: PRIVATE && thisVar -> dimen != TDim :: NREB && (thisVar -> values || thisVar -> ivalues) && ! thisVar -> FileData)
                    {
                        Newname = DeclObsName (thisVar);
                        if (model -> AllVariables -> count (Newname) == 0)
                        {
                            model -> AllVariables -> insert (std :: pair < std :: string, ClassVar * > (Newname, thisVar));
                        }

                    }

                }
                break;
            default:
                break;
            }
        }
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::GetAllVariables()@@@CRHMmainDlg.cpp>");
}
bool CRHMmainDlg :: Variation_Decide (int Variation_set, long Variation)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::Variation_Decide(int Variation_set, long Variation)@@@CRHMmainDlg.cpp>");
    VandP V;
    V.Set (Variation);
    long variations = V.GetV ();
    if ((Variation_set & 2048) != 0 && variations == 0 || (Variation_set & 4096) != 0 || (Variation_set == 0) || (variations & Variation_set) != 0)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::Variation_Decide(int Variation_set, long Variation)@@@CRHMmainDlg.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::Variation_Decide(int Variation_set, long Variation)@@@CRHMmainDlg.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::Variation_Decide(int Variation_set, long Variation)@@@CRHMmainDlg.cpp>");
}
std :: string CRHMmainDlg :: DeclObsName (ClassVar * thisVar)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::DeclObsName(ClassVar * thisVar)@@@CRHMmainDlg.cpp>");
    std :: string Newname = thisVar -> name.c_str ();
    std :: list < std :: pair < std :: string, ClassModule * >> :: iterator pos = Global :: OurModulesList -> end ();
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator it = Global :: OurModulesList -> begin (); it != Global :: OurModulesList -> end (); it ++) {
        if (it -> first == thisVar -> module.c_str ())
        {
            pos = it;
            break;
        }

    }
    int found = Newname.find ("#");
    if (pos != Global :: OurModulesList -> end () && found > 0)
    {
        ClassModule * thisModule = pos -> second;
        if (thisModule -> isGroup)
        {
            string AA;
            Common :: GroupEnding (AA, thisModule -> GroupCnt);
            Newname += AA;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::DeclObsName(ClassVar * thisVar)@@@CRHMmainDlg.cpp>");
    return Newname;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::DeclObsName(ClassVar * thisVar)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: RunClickFunction ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::RunClickFunction()@@@CRHMmainDlg.cpp>");
    CRHMmain * test = CRHMmain :: getInstance ();
    if (test -> ObsFilesList -> size () == 0)
    {
        MessageBox (_T ("Please open an observation file."));

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::RunClickFunction()@@@CRHMmainDlg.cpp>");
        return;
    }

    MMSData * mmsdata = test -> RunClick2Start ();
    int seriesCount = test -> SeriesCnt;
    if (seriesCount == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::RunClickFunction()@@@CRHMmainDlg.cpp>");
        return;
    }

    CSeries series [1000];
    std :: list < std :: pair < std :: string, ClassVar * >> :: iterator selectedVariableIt = test -> SelectedVariables -> begin ();
    for (int i = 0; i < seriesCount; i ++) {
        string s = selectedVariableIt -> first;
        CString cs (s.c_str ());
        int removed = 0;
        int cnt = tchart.get_SeriesCount ();
        for (int j = 0; j < cnt; j ++) {
            if (tchart.SeriesTitleLegend (j) == cs)
            {
                tchart.RemoveSeries (j);
                removed = 1;
                break;
            }

        }
        tchart.AddSeries (0);
        if (removed == 1)
        {
            series [i] = tchart.Series (cnt - 1);
        }

        else
        {
            series [i] = tchart.Series (cnt);
        }

        series [i].put_LegendTitle (cs);
        selectedVariableIt ++;
    }
    string values = "";
    int seriesIndex = 0;
    int TotalCount = 0;
    int pcount = 0;
    int n = 0;
    for (int indx = Global :: DTmin; indx < Global :: DTmax; indx = indx + 500) {
        int next = indx + 500;
        if (next >= Global :: DTmax)
        {
            test -> RunClick2Middle (mmsdata, indx, Global :: DTmax);
        }

        else
        {
            test -> RunClick2Middle (mmsdata, indx, indx + 500);
        }

        TotalCount = test -> cdSeries [0] -> Count ();
        for (int i = pcount; i < TotalCount; i ++) {
            for (int j = 0; j < seriesCount; j ++) {
                int y, m, d, h, mi;
                StandardConverterUtility :: GetDateTimeElements (test -> cdSeries [j] -> XValues.at (i), & y, & m, & d, & h, & mi);
                string dt = to_string (m) + "/" + to_string (d) + "/" + to_string (y);
                CString str (dt.c_str ());
                LPCTSTR dtstr = (LPCTSTR) str;
                series [j].AddXY (test -> cdSeries [j] -> XValues.at (i), test -> cdSeries [j] -> YValues.at (i), dtstr, series [j].get_Color ());
            }
            n ++;
            if (n % 500 == 0)
            {
                tchart.Repaint ();
            }

        }
        pcount = TotalCount;
    }
    tchart.Repaint ();
    test -> RunClick2End (mmsdata);
    if (test -> getAutoExit ())
    {
        GetActiveWindow () -> PostMessageW (WM_QUIT);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::RunClickFunction()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: AddSeriesToTChart (TSeries * tseries)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::AddSeriesToTChart(TSeries * tseries)@@@CRHMmainDlg.cpp>");
    CSeries series;
    tchart.AddSeries (0);
    int count = tchart.get_SeriesCount ();
    series = tchart.Series (count - 1);
    CString cstr (tseries -> Title.c_str ());
    series.put_LegendTitle (cstr);
    for (size_t i = 0; i < tseries -> XValues.size (); i ++) {
        int y, m, d, h, mi;
        StandardConverterUtility :: GetDateTimeElements (tseries -> XValues.at (i), & y, & m, & d, & h, & mi);
        string dt = to_string (m) + "/" + to_string (d) + "/" + to_string (y);
        CString str (dt.c_str ());
        LPCTSTR dtstr = (LPCTSTR) str;
        series.AddXY (tseries -> XValues.at (i), tseries -> YValues.at (i), dtstr, series.get_Color ());
    }
    tchart.Repaint ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::AddSeriesToTChart(TSeries * tseries)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: AddObsPlot (ClassVar * thisVar, TSeries * cdSeries, string S, TFun Funct)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::AddObsPlot(ClassVar * thisVar, TSeries * cdSeries, string S, TFun Funct)@@@CRHMmainDlg.cpp>");
    CRHMmain * test = CRHMmain :: getInstance ();
    ClassVar * newVar;
    Global :: HRU_OBS = Global :: HRU_OBS_DIRECT;
    double ** Data = thisVar -> FileData -> Data;
    double xx;
    double DTstartR = test -> GetStartDate ();
    double DTendR = test -> GetEndDate ();
    if (DTstartR >= DTendR)
    {

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::AddObsPlot(ClassVar * thisVar, TSeries * cdSeries, string S, TFun Funct)@@@CRHMmainDlg.cpp>");
        return;
    }

    TDateTime Save_DTnow = Global :: DTnow;
    double MyInterval = thisVar -> FileData -> Interval;
    long DTmin = INT ((DTstartR - Global :: DTstart) * thisVar -> FileData -> Freq) * Global :: Freq / thisVar -> FileData -> Freq;
    long DTmax = INT ((DTendR - Global :: DTstart) * thisVar -> FileData -> Freq) * Global :: Freq / thisVar -> FileData -> Freq;
    long jj1 = S.rfind ("(");
    long jj2 = S.rfind (")");
    long Indx;
    string :: size_type pp;
    pp = thisVar -> name.rfind ('(');
    bool AlreadyIndex = (pp != string :: npos);
    if (test -> ListHruNames && thisVar -> varType < TVar :: Read)
    {
        string sub = S.substr (jj1 + 1, jj2 - jj1 - 1);
        bool found = false;
        int n;
        for (size_t i = 0; i < test -> ListHruNames -> size (); i ++) {
            if (test -> ListHruNames -> at (i) == sub)
            {
                n = i;
                found = true;
            }

        }
        if (found == false)
        {
            n = - 1;
        }

        Indx = n - 1;
    }

    else
    {
        if (thisVar -> root != "" || AlreadyIndex)
        {
            Indx = 0;
        }

        else
        {
            Indx = stoi (S.substr (jj1 + 1, jj2 - jj1 - 1)) - 1;
        }

    }

    long IndxMin = thisVar -> FileData -> IndxMin;
    long IndxMax = thisVar -> FileData -> IndxMax;
    if (thisVar -> FileData -> Times != NULL)
    {
        if (Global :: Freq == 1)
        {
            -- DTendR;
        }

        double Sum = 0.0;
        for (long ii = 0; ii < thisVar -> FileData -> Lines; ++ ii) {
            if (thisVar -> FileData -> Times [ii] < DTstartR)
            {
                continue;
            }

            if (thisVar -> FileData -> Times [ii] > DTendR)
            {
                continue;
            }

            xx = Data [thisVar -> offset + Indx] [ii];
            if (Funct == TFun :: TOT)
            {
                Sum += xx;
                xx = Sum;
            }

            cdSeries -> AddXY (thisVar -> FileData -> Times [ii], xx);
        }
    }

    else
    if (Funct <= TFun :: MJ_W)
    {
        for (Global :: DTindx = DTmin; Global :: DTindx < DTmax; Global :: DTindx ++) {
            Global :: DTnow = Global :: DTstart + Global :: Interval * Global :: DTindx + Global :: Interval;
            if (MyInterval >= 1)
            {
                -- Global :: DTnow;
            }

            if (Global :: DTindx * thisVar -> FileData -> Freq / Global :: Freq >= IndxMin && Global :: DTindx * thisVar -> FileData -> Freq / Global :: Freq <= IndxMax)
            {
                xx = Data [thisVar -> offset + Indx] [(Global :: DTindx * thisVar -> FileData -> Freq / Global :: Freq - IndxMin)];
                if (Funct == TFun :: FOBS)
                {
                }

                else
                if (Funct == TFun :: VP_SAT)
                {
                    if (xx > 0.0)
                    {
                        xx = 0.611 * exp (17.27 * xx / (xx + 237.3));
                    }

                    else
                    {
                        xx = 0.611 * exp (21.88 * xx / (xx + 265.5));
                    }

                }

                else
                if (Funct == TFun :: W_MJ)
                {
                    xx *= thisVar -> FileData -> Interval * 86400 / 1.0E6;
                }

                else
                if (Funct == TFun :: MJ_W)
                {
                    xx *= 1.0E6 / 86400 / thisVar -> FileData -> Interval;
                }

                cdSeries -> AddXY (Global :: DTnow, xx);
            }

        }
    }

    else
    {
        newVar = new ClassVar (* thisVar);
        newVar -> name = S.c_str ();
        newVar -> FileData -> DataFileName = "Copy";
        string :: size_type pp = thisVar -> units.find_last_of (")");
        if (thisVar -> FileData -> Freq > 1 && (thisVar -> units [pp - 1] == 'd'))
        {
            thisVar -> Daily = TRUE;
        }

        else
        {
            thisVar -> Daily = FALSE;
        }

        if (newVar -> root == "")
        {
            if (thisVar -> FileData -> Freq == 1)
            {
                newVar -> LoopFunct = & ClassVar :: LoopFirst;
            }

            else
            if (thisVar -> Daily)
            {
                newVar -> LoopFunct = & ClassVar :: LoopFirst;
            }

            else
            {
                newVar -> LoopFunct = & ClassVar :: LoopRange;
            }

        }

        else
        {
            if (thisVar -> Daily)
            {
                newVar -> LoopFunct = & ClassVar :: LoopLast;
            }

            else
            {
                newVar -> LoopFunct = & ClassVar :: LoopRange;
            }

        }

        newVar -> FunctVar = thisVar;
        switch (Funct) {
        case TFun :: AVG:
            newVar -> UserFunct_ = & ClassVar :: Tot_;
            newVar -> FunKind = TFun :: AVG;
            break;
        case TFun :: MIN:
            newVar -> UserFunct_ = & ClassVar :: Min_;
            newVar -> FunKind = TFun :: MIN;
            break;
        case TFun :: MAX:
            newVar -> UserFunct_ = & ClassVar :: Max_;
            newVar -> FunKind = TFun :: MAX;
            break;
        case TFun :: TOT:
            newVar -> UserFunct_ = & ClassVar :: Tot_;
            newVar -> FunKind = TFun :: TOT;
            break;
        case TFun :: POS:
            newVar -> UserFunct_ = & ClassVar :: Pos_;
            newVar -> FunKind = TFun :: POS;
            break;
        case TFun :: FIRST:
            newVar -> UserFunct_ = & ClassVar :: First_;
            newVar -> FunKind = TFun :: FIRST;
            newVar -> LoopFunct = & ClassVar :: LoopFirst;
            break;
        case TFun :: LAST:
            newVar -> UserFunct_ = & ClassVar :: Last_;
            newVar -> FunKind = TFun :: LAST;
            newVar -> LoopFunct = & ClassVar :: LoopLast;
            break;
        case TFun :: CNT:
            newVar -> UserFunct_ = & ClassVar :: Count_;
            newVar -> FunKind = TFun :: CNT;
            break;
        case TFun :: CNT0:
            newVar -> UserFunct_ = & ClassVar :: Count0_;
            newVar -> FunKind = TFun :: CNT0;
            break;
        case TFun :: DLTA:
            newVar -> UserFunct_ = & ClassVar :: First_;
            newVar -> LoopFunct = & ClassVar :: LoopFirst;
            newVar -> FunKind = TFun :: DLTA;
            break;
        default:
            break;
        }
        bool First = false;
        long Next = - 1;
        long Days = 0;
        long LastDays = 0;
        long Lastkk = 0;
        long CurrentIndx = - 1;
        long LastIndex = - 1;
        long itime [6];
        long Greatest;
        long DTminX = DTmin;
        if (IndxMin > 0)
        {
            DTminX = IndxMin;
        }

        double Delta0 = 0.0;
        double First0;
        double Temp;
        dattim ("now", itime);
        for (Global :: DTindx = DTmin; Global :: DTindx < DTmax; Global :: DTindx += Global :: Freq) {
            Global :: DTnow = Global :: DTstart + Global :: Interval * Global :: DTindx + Global :: Interval;
            if (Global :: DTindx * Global :: Freq / thisVar -> FileData -> Freq >= IndxMin)
            if (Global :: DTindx * thisVar -> FileData -> Freq / Global :: Freq > IndxMax)
            {
                break;
            }

            else
            {
                if (Global :: Interval >= 1)
                {
                    -- Global :: DTnow;
                }

                dattim ("now", itime);
                switch (TBase) {
                case 0:
                    if (Next == - 1 || Next != itime [2])
                    {
                        Next = itime [2];
                        First = TRUE;
                    }

                    break;
                case 1:
                    if (Next == - 1 || itime [0] == Next && itime [1] == water_year_month)
                    {
                        if (Next == - 1 && itime [1] < water_year_month)
                        {
                            Next = itime [0];
                        }

                        else
                        {
                            Next = itime [0] + 1;
                        }

                        First = TRUE;
                    }

                    break;
                case 2:
                    if (Next == - 1 || itime [0] == Next && itime [1] == 1)
                    {
                        Next = itime [0] + 1;
                        First = TRUE;
                    }

                    break;
                case 3:
                    if (Next == - 1 || Next == itime [1])
                    {
                        Next = (itime [1]) % 12 + 1;
                        First = TRUE;
                    }

                    break;
                case 4:
                    if (Next == - 1)
                    {
                        Next = 0;
                        First = TRUE;
                    }

                default:
                    break;
                }
                CurrentIndx = (Global :: DTindx - DTminX) / thisVar -> FileData -> Freq - 1;
                if (First)
                {
                    if (Global :: DTindx > DTmin && Global :: DTindx > IndxMin)
                    {
                        switch (Funct) {
                        case TFun :: DLTA:
                            Temp = cdSeries -> YValue ((Global :: DTindx - DTmin) / thisVar -> FileData -> Freq - 1);
                            cdSeries -> YValues.at (CurrentIndx) -= Delta0;
                            Delta0 = Temp;
                        case TFun :: AVG:
                        case TFun :: MIN:
                        case TFun :: MAX:
                        case TFun :: TOT:
                        case TFun :: POS:
                        case TFun :: LAST:
                        case TFun :: CNT:
                        case TFun :: CNT0:
                            if (ObsFunct_Toggle == 1)
                            {
                                for (long jj = LastIndex + 1; jj <= CurrentIndx; ++ jj)
                                    cdSeries -> YValues [jj] = cdSeries -> YValues [CurrentIndx];
                            }

                            break;
                        case TFun :: FIRST:
                            for (long jj = LastIndex + 1; jj <= CurrentIndx; ++ jj)
                                cdSeries -> YValues.at (jj) = First0;
                            break;
                        default:
                            break;
                        }
                    }

                    else
                    if (Funct == TFun :: DLTA && TBase)
                    {
                        (newVar ->* (newVar -> LoopFunct)) (Indx);
                        Delta0 = newVar -> values [Indx];
                        newVar -> UserFunct_ = & ClassVar :: Last_;
                        newVar -> FunKind = TFun :: LAST;
                        newVar -> LoopFunct = & ClassVar :: LoopLast;
                    }

                    Lastkk = Global :: DTindx;
                    if (CurrentIndx > - 1)
                    {
                        LastIndex = CurrentIndx;
                    }

                    switch (Funct) {
                    case TFun :: MAX:
                        newVar -> values [Indx] = - 1000000.0;
                        break;
                    case TFun :: MIN:
                        newVar -> values [Indx] = 1000000.0;
                        break;
                    case TFun :: AVG:
                    case TFun :: TOT:
                    case TFun :: CNT:
                    case TFun :: CNT0:
                    case TFun :: DLTA:
                    case TFun :: POS:
                        newVar -> values [Indx] = 0.0;
                    default:
                        break;
                    }
                    LastDays = Days;
                    Days = 0;
                }

                (newVar ->* (newVar -> LoopFunct)) (Indx);
                xx = newVar -> values [Indx];
                cdSeries -> AddXY (Global :: DTnow, xx);
                if (First)
                {
                    First0 = xx;
                }

                if (Global :: DTindx > DTmin && Global :: DTindx > IndxMin)
                {
                    switch (Funct) {
                    case TFun :: AVG:
                        Greatest = Days;
                        if (LastDays > Days)
                        {
                            Greatest = LastDays;
                        }

                        cdSeries -> YValues.at (CurrentIndx) /= ((long long) Global :: Freq * (long long) Greatest);
                        LastDays = 0;
                        break;
                    case TFun :: DLTA:
                        if (! First)
                        {
                            cdSeries -> YValues.at (CurrentIndx) -= Delta0;
                        }

                        break;
                    default:
                        break;
                    }
                }

                ++ Days;
                First = FALSE;
            }

        }
        if (Global :: DTindx > DTmin && Global :: DTindx > IndxMin)
        {
            CurrentIndx = (Global :: DTindx - DTminX) / thisVar -> FileData -> Freq - 1;
            switch (Funct) {
            case TFun :: AVG:
                Greatest = Days;
                if (LastDays > Days)
                {
                    Greatest = LastDays;
                }

                cdSeries -> YValues.at (CurrentIndx) /= ((long long) Global :: Freq * (long long) Greatest);
                if (ObsFunct_Toggle == 1)
                {
                    for (long jj = LastIndex + 1; jj <= CurrentIndx; ++ jj)
                        cdSeries -> YValues [jj] = cdSeries -> YValues [CurrentIndx];
                }

                break;
            case TFun :: DLTA:
                cdSeries -> YValues.at (CurrentIndx) -= Delta0;
            case TFun :: MIN:
            case TFun :: MAX:
            case TFun :: TOT:
            case TFun :: POS:
            case TFun :: LAST:
            case TFun :: CNT:
            case TFun :: CNT0:
                if (ObsFunct_Toggle == 1)
                {
                    for (long jj = LastIndex + 1; jj <= CurrentIndx; ++ jj)
                        cdSeries -> YValues [jj] = cdSeries -> YValues [CurrentIndx];
                }

                break;
            case TFun :: FIRST:
                for (long jj = LastIndex + 1; jj <= CurrentIndx; ++ jj)
                    cdSeries -> YValues.at (jj) = First0;
                break;
            default:
                break;
            }
        }

        delete newVar -> FileData;
        delete newVar;
        cdSeries -> Tag = NULL;
    }

    Global :: DTnow = Save_DTnow;
    AddSeriesToTChart (cdSeries);
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::AddObsPlot(ClassVar * thisVar, TSeries * cdSeries, string S, TFun Funct)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: SetTime (double startDate, double endDate)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::SetTime(double startDate, double endDate)@@@CRHMmainDlg.cpp>");
    COleDateTime oletimeTime (startDate);
    VERIFY (StartDatePicker.SetTime (oletimeTime));
    COleDateTime oletimeTime2 (endDate);
    VERIFY (EndDatePicker.SetTime (oletimeTime2));
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::SetTime(double startDate, double endDate)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OpenProject (std :: string filepath, std :: string filename)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OpenProject(std :: string filepath, std :: string filename)@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    bool errorOpening = ! model -> DoPrjOpen (filepath, filename);
    std :: string errorString = "Cannot open open observation file: \n" + filename + "\n\nCheck that it is correctly specified in the project file and located at: \n" + filepath;
    if (errorOpening)
    {
        MessageBox ((LPCWSTR) CString (errorString.c_str ()), (LPCWSTR) L"Error opening observation file.", MB_OK);

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenProject(std :: string filepath, std :: string filename)@@@CRHMmainDlg.cpp>");
        return;
    }

    model -> OpenProjectPath = filepath;
    loadGuiComponents ();
    std :: string str1 = "The Cold Regions Hydrological Model - ";
    str1.append (filepath);
    CString cFilePath (str1.c_str ());
    if (filepath == defaultprojectpath)
    {
        SetWindowText (L"The Cold Regions Hydrological Model");
    }

    else
    {
        SetWindowText (cFilePath);
    }

    if (model -> getAutoRun ())
    {
        UpdateWindow ();
        this -> RunClickFunction ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenProject(std :: string filepath, std :: string filename)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: ReopenProject ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::ReopenProject()@@@CRHMmainDlg.cpp>");
    CRHMmain * t = CRHMmain :: getInstance ();
    if (t -> OpenProjectPath.length () == 0)
    {
        OpenProject (defaultprojectpath, defaultprojectname);
    }

    else
    {
        OpenProject (t -> OpenProjectPath, t -> OpenProjectPath);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::ReopenProject()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: SaveProject ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::SaveProject()@@@CRHMmainDlg.cpp>");
    CRHMmain * crhmmain = CRHMmain :: getInstance ();
    std :: list < std :: pair < std :: string, ClassVar * >> * selected_variables = GetSelectedVariables ();
    std :: list < std :: pair < std :: string, TSeries * >> * selected_observations = GetSelectedObservations ();
    crhmmain -> setSelectedVariables (selected_variables);
    crhmmain -> setSelectedObservatoions (selected_observations);
    if (crhmmain -> OpenProjectPath.length () == 0)
    {
        crhmmain -> OpenProjectPath = defaultprojectpath;
    }

    crhmmain -> SaveProject ("Description - to be added", crhmmain -> OpenProjectPath);
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::SaveProject()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: CloseProject ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::CloseProject()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    listbox_all_variables.ResetContent ();
    ASSERT (listbox_all_variables.GetCount () == 0);
    model -> AllVariables -> clear ();
    listbox_sel_variables.ResetContent ();
    ASSERT (listbox_sel_variables.GetCount () == 0);
    model -> SelectedVariables -> clear ();
    listbox_all_observations.ResetContent ();
    ASSERT (listbox_all_observations.GetCount () == 0);
    model -> AllObservations -> clear ();
    listbox_sel_observations.ResetContent ();
    ASSERT (listbox_sel_observations.GetCount () == 0);
    model -> SelectedObservations -> clear ();
    COleDateTime oletimeTime (StandardConverterUtility :: GetCurrentDateTime ());
    VERIFY (StartDatePicker.SetTime (oletimeTime));
    VERIFY (EndDatePicker.SetTime (oletimeTime));
    model -> FormDestroy ();
    model -> FormCreate ();
    model -> ObsCloseClick ();
    updateOpenObsFileMenu ();
    model -> OpenNameState = "";
    model -> OpenStateFlag = false;
    model -> SaveStateFileName = "";
    model -> SaveStateFlag = false;
    updateOpenStateFileMenu ();
    globFileName = "";
    model -> OpenProjectPath = "";
    SetWindowText (L"The Cold Regions Hydrological Model");
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::CloseProject()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: AddDataToSeries (CSeries series, double xvalue, double yvalue)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::AddDataToSeries(CSeries series, double xvalue, double yvalue)@@@CRHMmainDlg.cpp>");
    int y, m, d, h, mi;
    StandardConverterUtility :: GetDateTimeElements (xvalue, & y, & m, & d, & h, & mi);
    string dt = to_string (m) + "/" + to_string (d) + "/" + to_string (y);
    CString str (dt.c_str ());
    LPCTSTR dtstr = (LPCTSTR) str;
    series.AddXY (xvalue, yvalue, dtstr, series.get_Color ());
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::AddDataToSeries(CSeries series, double xvalue, double yvalue)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OpenObservation (std :: string obsfilepath)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OpenObservation(std :: string obsfilepath)@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    model -> OpenObsFile (obsfilepath);
    std :: map < std :: string, ClassVar * > * observations = model -> getObservations ();
    std :: map < std :: string, ClassVar * > :: iterator it;
    for (it = observations -> begin (); it != observations -> end (); it ++) {
        CString cstr (it -> first.c_str ());
        listbox_all_observations.AddString (cstr);
    }
    SetTime (model -> GetStartDate (), model -> GetEndDate ());
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenObservation(std :: string obsfilepath)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: AddOpenObsFile (std :: string filepath, std :: string filename)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::AddOpenObsFile(std :: string filepath, std :: string filename)@@@CRHMmainDlg.cpp>");
    CString obsFileName = CString (filename.c_str ());
    CMenu * menu = GetActiveWindow () -> GetMenu ();
    CMenu * submenu = menu -> GetSubMenu (1);
    UINT OPEN_ID = BEGIN_OPEN_OBS_FILE_ID;
    for (UINT ID = ID_OPEN_OBS_FILE_FIRST; ID < END_OPEN_OBS_FILE_ID; ID ++) {
        if (! this -> openObsFiles -> count (ID))
        {
            OPEN_ID = ID;
            break;
        }

    }
    if (OPEN_ID == BEGIN_OPEN_OBS_FILE_ID || OPEN_ID == END_OPEN_OBS_FILE_ID)
    {
    }

    else
    {
        this -> openObsFiles -> insert (std :: pair < UINT, std :: pair < std :: string, std :: string >> (OPEN_ID, std :: pair < std :: string, std :: string > (filepath, filename)));
        submenu -> AppendMenu (MF_STRING, OPEN_ID, (LPCTSTR) obsFileName);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::AddOpenObsFile(std :: string filepath, std :: string filename)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: updateGuiMenuItems ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::updateGuiMenuItems()@@@CRHMmainDlg.cpp>");
    updateOpenObsFileMenu ();
    updateOpenStateFileMenu ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::updateGuiMenuItems()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: updateOpenObsFileMenu ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::updateOpenObsFileMenu()@@@CRHMmainDlg.cpp>");
    listbox_all_observations.ResetContent ();
    listbox_sel_observations.ResetContent ();
    tchart.RemoveAllSeries ();
    CMenu * menu = GetActiveWindow () -> GetMenu ();
    CMenu * submenu = menu -> GetSubMenu (1);
    for (std :: map < UINT, std :: pair < std :: string, std :: string >> :: iterator it = this -> openObsFiles -> begin (); it != this -> openObsFiles -> end (); it ++) {
        submenu -> RemoveMenu (it -> first, MF_BYCOMMAND);
    }
    this -> openObsFiles -> clear ();
    CRHMmain * main = CRHMmain :: getInstance ();
    std :: map < std :: string, ClassVar * > * observations = main -> getObservations ();
    std :: list < std :: pair < std :: string, TSeries * >> * selectedObservations = main -> getSelectedObservations ();
    std :: list < std :: pair < std :: string, ClassData * >> * listOfObsFiles = main -> ObsFilesList;
    for (std :: list < std :: pair < std :: string, ClassData * >> :: iterator it = listOfObsFiles -> begin (); it != listOfObsFiles -> end (); it ++) {
        CString obsFileName = CString (it -> second -> DataFileName.c_str ());
        UINT OPEN_ID = BEGIN_OPEN_OBS_FILE_ID;
        for (UINT ID = ID_OPEN_OBS_FILE_FIRST; ID < END_OPEN_OBS_FILE_ID; ID ++) {
            if (! this -> openObsFiles -> count (ID))
            {
                OPEN_ID = ID;
                break;
            }

        }
        if (OPEN_ID == BEGIN_OPEN_OBS_FILE_ID || OPEN_ID == END_OPEN_OBS_FILE_ID)
        {
        }

        else
        {
            this -> openObsFiles -> insert (std :: pair < UINT, std :: pair < std :: string, std :: string >> (OPEN_ID, std :: pair < std :: string, std :: string > (it -> second -> DataFileName, it -> second -> DataFileName)));
            submenu -> AppendMenu (MF_STRING, OPEN_ID, (LPCTSTR) obsFileName);
        }

    }
    for (std :: map < std :: string, ClassVar * > :: iterator it = observations -> begin (); it != observations -> end (); it ++) {
        CString cstr (it -> first.c_str ());
        listbox_all_observations.AddString (cstr);
    }
    std :: vector < std :: list < std :: pair < std :: string, TSeries * >> :: iterator > toErase;
    for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = selectedObservations -> begin (); it != selectedObservations -> end (); it ++) {
        std :: string withoutSuffix = it -> first.substr (0, it -> first.find_last_of ('('));
        int found = main -> AllObservations -> count (withoutSuffix);
        if (! found)
        {
            toErase.push_back (it);
        }

    }
    for (size_t i = 0; i < toErase.size (); i ++) {
        selectedObservations -> erase (toErase.at (i));
    }
    updateSelectedObservationListBox ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::updateOpenObsFileMenu()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: updateOpenStateFileMenu ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::updateOpenStateFileMenu()@@@CRHMmainDlg.cpp>");
    CMenu * menu = GetActiveWindow () -> GetMenu () -> GetSubMenu (4);
    CRHMmain * model = CRHMmain :: getInstance ();
    if (menu -> GetMenuItemCount () > 6)
    {
        menu -> RemoveMenu (ID_OPEN_INIT_FILE, MF_BYCOMMAND);
    }

    if (model -> OpenStateFlag)
    {
        std :: string stateFileMenuItemName = "Open State File: ";
        stateFileMenuItemName += model -> OpenNameState.c_str ();
        CString stateFileName = CString (stateFileMenuItemName.c_str ());
        menu -> InsertMenu (0, MF_STRING, ID_OPEN_INIT_FILE, (LPCTSTR) stateFileName);
    }

    if (model -> getFinishedRun ())
    {
        menu -> EnableMenuItem (ID_STATE_SAVE_STATE_AS, MF_ENABLED);
    }

    else
    {
        menu -> EnableMenuItem (ID_STATE_SAVE_STATE_AS, MF_DISABLED);
    }

    if (model -> SaveStateFlag == true)
    {
        menu -> CheckMenuItem (ID_STATE_SAVE_STATE, MF_CHECKED);
        std :: string saveTo = "Save State To: ";
        saveTo += model -> SaveStateFileName;
        CString saveTo_CString = CString (saveTo.c_str ());
        menu -> ModifyMenu (ID_STATE_SAVE_TO, MF_BYCOMMAND, ID_STATE_SAVE_TO, (LPCTSTR) saveTo_CString);
        menu -> EnableMenuItem (ID_STATE_SAVE_TO, MF_ENABLED);
    }

    else
    {
        menu -> CheckMenuItem (ID_STATE_SAVE_STATE, MF_UNCHECKED);
        std :: string saveTo = "Save State To:";
        CString saveTo_CString = CString (saveTo.c_str ());
        menu -> ModifyMenu (ID_STATE_SAVE_TO, MF_BYCOMMAND, ID_STATE_SAVE_TO, (LPCTSTR) saveTo_CString);
        menu -> EnableMenuItem (ID_STATE_SAVE_TO, MF_DISABLED);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::updateOpenStateFileMenu()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: updateSelectedVariablesListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::updateSelectedVariablesListBox()@@@CRHMmainDlg.cpp>");
    CWaitCursor wait;
    CRHMmain * model = CRHMmain :: getInstance ();
    std :: list < std :: pair < std :: string, ClassVar * >> * listOfSelectedVariables = model -> getSelectedVariables ();
    for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = listOfSelectedVariables -> begin (); it != listOfSelectedVariables -> end (); it ++) {
        int found = listbox_sel_variables.FindString (- 1, CString (it -> first.c_str ()));
        if (found == LB_ERR)
        {
            CString selectedVariable = CString (it -> first.c_str ());
            listbox_sel_variables.AddString (selectedVariable);
        }

    }
    for (int i = 0; i < listbox_sel_variables.GetCount (); i ++) {
        CString text;
        listbox_sel_variables.GetText (i, text);
        std :: string str = CT2A (text.GetString ());
        bool found = false;
        std :: list < std :: pair < std :: string, ClassVar * >> * listOfSelectedVariables = model -> getSelectedVariables ();
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = listOfSelectedVariables -> begin (); it != listOfSelectedVariables -> end (); it ++) {
            if (it -> first == str)
            {
                found = true;
                break;
            }

        }
        if (! found)
        {
            listbox_sel_variables.DeleteString (i);
            i = - 1;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::updateSelectedVariablesListBox()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: updateSelectedObservationListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::updateSelectedObservationListBox()@@@CRHMmainDlg.cpp>");
    CWaitCursor wait;
    CRHMmain * model = CRHMmain :: getInstance ();
    std :: list < std :: pair < std :: string, TSeries * >> * listOfSelectedObs = model -> SelectedObservations;
    for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = listOfSelectedObs -> begin (); it != listOfSelectedObs -> end (); it ++) {
        int found = listbox_sel_observations.FindString (- 1, CString (it -> first.c_str ()));
        if (found == LB_ERR)
        {
            it -> second -> XValues.clear ();
            it -> second -> YValues.clear ();
            AddObsPlot (it -> second -> Tag, it -> second, it -> first, model -> Funct);
            CString selectedObservation = CString (it -> first.c_str ());
            listbox_sel_observations.AddString (selectedObservation);
        }

    }
    for (int i = 0; i < listbox_sel_observations.GetCount (); i ++) {
        CString text;
        listbox_sel_observations.GetText (i, text);
        std :: string str = CT2A (text.GetString ());
        bool found = false;
        std :: list < std :: pair < std :: string, TSeries * >> * listOfSelectedObs = model -> SelectedObservations;
        for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = listOfSelectedObs -> begin (); it != listOfSelectedObs -> end (); it ++) {
            if (it -> first == str)
            {
                found = true;
                break;
            }

        }
        if (! found)
        {
            for (int j = 0; j < tchart.get_SeriesCount (); j ++) {
                CString title = tchart.SeriesTitleLegend (j);
                if (title == text)
                {
                    tchart.RemoveSeries (j);
                    break;
                }

            }
            listbox_sel_observations.DeleteString (i);
            i = - 1;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::updateSelectedObservationListBox()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnFileOpen ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnFileOpen()@@@CRHMmainDlg.cpp>");
    CWaitCursor wait;
    CFile theFile;
    TCHAR szFilters [] = _T ("MyType Files (*.prj)|*.prj|All Files (*.*)|*.*||");
    CString fileName;
    wchar_t * p = fileName.GetBuffer (FILE_LIST_BUFFER_SIZE);
    CFileDialog fileDlg (TRUE, _T ("prj"), _T ("*.prj"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
    if (fileDlg.DoModal () == IDOK)
    {
        this -> CloseProject ();
        CString filepath = fileDlg.GetPathName ();
        CString filename = fileDlg.GetFileName ();
        globFileName = filename;
        string file_p = CT2A (filepath.GetString ());
        string file_n = CT2A (filename.GetString ());
        OpenProject (file_p, file_n);
        updateGuiMenuItems ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnFileOpen()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnFileSave ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnFileSave()@@@CRHMmainDlg.cpp>");
    SaveProject ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnFileSave()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnFileSaveAs ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnFileSaveAs()@@@CRHMmainDlg.cpp>");
    TCHAR szFilters [] = _T ("MyType Files (*.prj)|*.prj|All Files (*.*)|*.*||");
    CString fileName;
    wchar_t * p = fileName.GetBuffer (FILE_LIST_BUFFER_SIZE);
    CFileDialog fileDlg (FALSE, _T ("prj"), _T ("*.prj"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
    INT_PTR result = fileDlg.DoModal ();
    if (result == IDOK)
    {
        CRHMmain * crhmmain = CRHMmain :: getInstance ();
        std :: list < std :: pair < std :: string, ClassVar * >> * selected_variables = GetSelectedVariables ();
        std :: list < std :: pair < std :: string, TSeries * >> * selected_observations = GetSelectedObservations ();
        crhmmain -> setSelectedVariables (selected_variables);
        crhmmain -> setSelectedObservatoions (selected_observations);
        fileName = fileDlg.GetPathName ();
        string filepath = CT2A (fileName.GetString ());
        crhmmain -> SaveProject ("Description - to be added", filepath);
        if (result == IDOK)
        {
            MessageBox (_T ("Your project has been saved."));
        }

        CRHMmain * model = CRHMmain :: getInstance ();
        model -> OpenProjectPath = filepath;
        std :: string str1 = "The Cold Regions Hydrological Model - ";
        str1.append (filepath);
        CString cFilePath (str1.c_str ());
        SetWindowText (cFilePath);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnFileSaveAs()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnFileClose ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnFileClose()@@@CRHMmainDlg.cpp>");
    CWaitCursor wait;
    CString filename = globFileName;
    CRHMmain * model = CRHMmain :: getInstance ();
    if (model -> OpenProjectPath == defaultprojectname)
    {
        if (listbox_all_variables.GetCount () == 0 && listbox_sel_variables.GetCount () == 0 && listbox_all_observations.GetCount () == 0 && listbox_sel_observations.GetCount () == 0)
        {
            this -> CloseProject ();
        }

        else
        {
            const int result = MessageBox (L"Do you want to save this project?", L"CRHM_GUI", MB_YESNOCANCEL);
            if (result == IDYES)
            {
                OnFileSaveAs ();
                this -> CloseProject ();
            }

            if (result == IDCANCEL)
            {

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnFileClose()@@@CRHMmainDlg.cpp>");
                return;
            }

            if (result == IDNO)
            {
                this -> CloseProject ();
            }

        }

    }

    else
    {
        this -> CloseProject ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnFileClose()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnExtractGroup ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnExtractGroup()@@@CRHMmainDlg.cpp>");
    CReport report;
    report.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnExtractGroup()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnViewHierarchy ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnViewHierarchy()@@@CRHMmainDlg.cpp>");
    HierarchyDlg hierarchy;
    hierarchy.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnViewHierarchy()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnAutoRun ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnAutoRun()@@@CRHMmainDlg.cpp>");
    CRHMmain * main = CRHMmain :: getInstance ();
    CMenu * menu = GetActiveWindow () -> GetMenu ();
    main -> setAutoRun (true);
    if (menu -> CheckMenuItem (ID_AUTO_RUN, MF_CHECKED) == MF_CHECKED)
    {
        main -> setAutoRun (false);
        menu -> CheckMenuItem (ID_AUTO_RUN, MF_UNCHECKED);
    }

    ;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnAutoRun()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnAutoExit ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnAutoExit()@@@CRHMmainDlg.cpp>");
    CRHMmain * main = CRHMmain :: getInstance ();
    CMenu * menu = GetActiveWindow () -> GetMenu ();
    main -> setAutoExit (true);
    if (menu -> CheckMenuItem (ID_AUTO_EXIT, MF_CHECKED) == MF_CHECKED)
    {
        main -> setAutoExit (false);
        menu -> CheckMenuItem (ID_AUTO_EXIT, MF_UNCHECKED);
    }

    ;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnAutoExit()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnExit ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnExit()@@@CRHMmainDlg.cpp>");
    CString filename = globFileName;
    CRHMmain * t = CRHMmain :: getInstance ();
    if (listbox_all_variables.GetCount () == 0 && listbox_sel_variables.GetCount () == 0 && listbox_all_observations.GetCount () == 0 && listbox_sel_observations.GetCount () == 0)
    {
    }

    else
    {
        if (t -> OpenProjectPath == defaultprojectname)
        {
            const int result = MessageBox (L"Do you want to save this project?", L"CRHM_GUI", MB_YESNOCANCEL);
            if (result == IDYES)
            {
                OnFileSaveAs ();
            }

            if (result == IDCANCEL)
            {

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnExit()@@@CRHMmainDlg.cpp>");
                return;
            }

        }

    }

    exit (0);
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnExit()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnLogAll ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnLogAll()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    model -> setReportAll (true);
    CMenu * menu = GetActiveWindow () -> GetMenu ();
    menu -> CheckMenuItem (ID_MAIN_LOG_LAST, MF_UNCHECKED);
    if (menu -> CheckMenuItem (ID_MAIN_LOG_ALL, MF_CHECKED) == MF_CHECKED)
    {
        menu -> CheckMenuItem (ID_MAIN_LOG_ALL, MF_UNCHECKED);
    }

    ;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnLogAll()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnLogLast ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnLogLast()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    model -> setReportAll (false);
    CMenu * menu = GetActiveWindow () -> GetMenu ();
    menu -> CheckMenuItem (ID_MAIN_LOG_ALL, MF_UNCHECKED);
    if (menu -> CheckMenuItem (ID_MAIN_LOG_LAST, MF_CHECKED) == MF_CHECKED)
    {
        menu -> CheckMenuItem (ID_MAIN_LOG_LAST, MF_UNCHECKED);
    }

    ;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnLogLast()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnOpenObservation ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnOpenObservation()@@@CRHMmainDlg.cpp>");
    CFile theFile;
    TCHAR szFilters [] = _T ("MyType Files (*.obs)|*.obs|All Files (*.*)|*.*||");
    CString fileName;
    wchar_t * p = fileName.GetBuffer (FILE_LIST_BUFFER_SIZE);
    CFileDialog fileDlg (TRUE, _T ("obs"), _T ("*.obs"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
    if (fileDlg.DoModal () == IDOK)
    {
        CString filepath = fileDlg.GetPathName ();
        CString filename = fileDlg.GetFileName ();
        std :: string file_p = CT2A (filepath.GetString ());
        std :: string file_n = CT2A (filename.GetString ());
        Box1Disply = (int) TVISIBLE :: PRIVATE;
        GetAllVariables ();
        OpenObservation (file_p);
        updateOpenObsFileMenu ();
    }

    Box1Disply = (int) TVISIBLE :: OUTPUT;
    GetAllVariables ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnOpenObservation()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnClickOnOpenFile (UINT ID)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnClickOnOpenFile(UINT ID)@@@CRHMmainDlg.cpp>");
    std :: map < UINT, std :: pair < std :: string, std :: string >> :: iterator pos = this -> openObsFiles -> find (ID);
    CRHMmain * main = CRHMmain :: getInstance ();
    main -> ObsFileClose (pos -> second.first);
    updateOpenObsFileMenu ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnClickOnOpenFile(UINT ID)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnCloseAllObservations ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnCloseAllObservations()@@@CRHMmainDlg.cpp>");
    CRHMmain * main = CRHMmain :: getInstance ();
    main -> ObsCloseClick ();
    updateOpenObsFileMenu ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnCloseAllObservations()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnBuildConstruct ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnBuildConstruct()@@@CRHMmainDlg.cpp>");
    CConstruct * build_form;
    std :: map < std :: string, ClassModule * > * all_module_list = CRHMmain :: getInstance () -> getAllmodules ();
    build_form = new CConstruct ();
    INT_PTR nRet = build_form -> DoModal ();
    if (build_form -> Execute)
    {
        InitModules ();
        build_form -> ReadBuildParameters ();
        loadGuiComponents ();
    }

    globFileName = defaultprojectpath.c_str ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnBuildConstruct()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnClearModules ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnClearModules()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    Global :: OurModulesList -> clear ();
    model -> SelectedVariables -> clear ();
    model -> AllVariables -> clear ();
    Global :: MapPars.clear ();
    loadGuiComponents ();
    updateSelectedVariablesListBox ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnClearModules()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnBuildMacro ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnBuildMacro()@@@CRHMmainDlg.cpp>");
    MacroEntryDlg * macroEntry;
    macroEntry = new MacroEntryDlg ();
    if (macroEntry -> DoModal () == IDOK)
    {
        CRHMmain * t = CRHMmain :: getInstance ();
        t -> MacroClick ();
        tchart.RemoveAllSeries ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnBuildMacro()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnClickOnOpenInitState ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnClickOnOpenInitState()@@@CRHMmainDlg.cpp>");
    CRHMmain * main = CRHMmain :: getInstance ();
    CFile theFile;
    TCHAR szFilters [] = _T ("MyType Files (*.int)|*.int |All Files (*.*)|*.*||");
    CString fileName;
    wchar_t * p = fileName.GetBuffer (FILE_LIST_BUFFER_SIZE);
    CFileDialog fileDlg (TRUE, _T ("int"), _T ("*.int"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
    if (fileDlg.DoModal () == IDOK)
    {
        CString folderPath = fileDlg.GetFolderPath ();
        CString filename = fileDlg.GetFileName ();
        main -> OpenNameState = CT2A (folderPath);
        main -> OpenStateFlag = true;
        updateOpenStateFileMenu ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnClickOnOpenInitState()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: CloseOpenInitFile ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::CloseOpenInitFile()@@@CRHMmainDlg.cpp>");
    CRHMmain * main = CRHMmain :: getInstance ();
    main -> OpenNameState = "";
    main -> OpenStateFlag = false;
    updateOpenStateFileMenu ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::CloseOpenInitFile()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnSaveState ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnSaveState()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    if (model -> SaveStateFlag == true)
    {
        model -> SaveStateFlag = false;
    }

    else
    {
        model -> SaveStateFlag = true;
        if (model -> SaveStateFileName == "")
        {
            std :: string defaultSaveStateFile = GetCurrentDir ();
            defaultSaveStateFile += "\\Final_State.int";
            model -> SaveStateFileName = defaultSaveStateFile;
        }

    }

    updateOpenStateFileMenu ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnSaveState()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnSaveStateTo ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnSaveStateTo()@@@CRHMmainDlg.cpp>");
    TCHAR szFilters [] = _T ("MyType Files (*.int)|*.int|All Files (*.*)|*.*||");
    CString fileName;
    wchar_t * p = fileName.GetBuffer (FILE_LIST_BUFFER_SIZE);
    CFileDialog fileDlg (FALSE, _T ("int"), _T ("*.int"), OFN_HIDEREADONLY, szFilters);
    if (fileDlg.DoModal () == IDOK)
    {
        CRHMmain * model = CRHMmain :: getInstance ();
        fileName = fileDlg.GetPathName ();
        string filepath = CT2A (fileName.GetString ());
        model -> SaveStateFileName = filepath;
        model -> SaveStateFlag = true;
        updateOpenStateFileMenu ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnSaveStateTo()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnSaveStateAs ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnSaveStateAs()@@@CRHMmainDlg.cpp>");
    TCHAR szFilters [] = _T ("MyType Files (*.int)|*.int|All Files (*.*)|*.*||");
    CRHMAboutBox * test;
    test = new CRHMAboutBox ();
    CString fileName;
    wchar_t * p = fileName.GetBuffer (FILE_LIST_BUFFER_SIZE);
    CFileDialog fileDlg (FALSE, _T ("int"), _T ("*.int"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
    if (fileDlg.DoModal () == IDOK)
    {
        CRHMmain * model = CRHMmain :: getInstance ();
        fileName = fileDlg.GetPathName ();
        string filepath = CT2A (fileName.GetString ());
        model -> SaveStateFileName = filepath;
        model -> SaveStateFlag = true;
        model -> SaveState ();
        updateOpenStateFileMenu ();
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnSaveStateAs()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnRunRunmodel ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnRunRunmodel()@@@CRHMmainDlg.cpp>");
    RunClickFunction ();
    updateOpenStateFileMenu ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnRunRunmodel()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnExport ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnExport()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    if (model -> getFinishedRun ())
    {
        CExport exportDlg;
        exportDlg.DoModal ();
    }

    else
    {
        CString text (L"Run must be completed before export can be performed.");
        MessageBox (text, MB_OK);
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnExport()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnFlowdiagramsShowdiagram ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnFlowdiagramsShowdiagram()@@@CRHMmainDlg.cpp>");
    FlowDiagramDlg flowdiagram;
    flowdiagram.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnFlowdiagramsShowdiagram()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnHelpAbout ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnHelpAbout()@@@CRHMmainDlg.cpp>");
    CRHMAboutBox aboutbox;
    aboutbox.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnHelpAbout()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: DecreaseHRUDimension ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::DecreaseHRUDimension()@@@CRHMmainDlg.cpp>");
    CString currentValue;
    CString newValue;
    int dimension = 0;
    GetDlgItemText (ID_HRU_DIM_DISPLAY, currentValue);
    dimension = _ttoi (currentValue);
    if (currentValue.Trim ().GetLength () > 0)
    {
        if (dimension > 1)
        {
            dimension = _ttoi (currentValue) - 1;
            newValue.Format (_T ("%d"), dimension);
            SetDlgItemText (ID_HRU_DIM_DISPLAY, newValue);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::DecreaseHRUDimension()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: IncreaseHRUDimension ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::IncreaseHRUDimension()@@@CRHMmainDlg.cpp>");
    CString currentValue;
    CString newValue;
    int dimension = 0;
    GetDlgItemText (ID_HRU_DIM_DISPLAY, currentValue);
    dimension = _ttoi (currentValue);
    if (currentValue.Trim ().GetLength () > 0)
    {
        if (dimension < Global :: maxhru)
        {
            dimension = _ttoi (currentValue) + 1;
            newValue.Format (_T ("%d"), dimension);
            SetDlgItemText (ID_HRU_DIM_DISPLAY, newValue);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::IncreaseHRUDimension()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: DecreaseObsDimension ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::DecreaseObsDimension()@@@CRHMmainDlg.cpp>");
    CString currentValue;
    CString newValue;
    int dimension = 0;
    GetDlgItemText (ID_OBS_DIM_DISPLAY, currentValue);
    dimension = _ttoi (currentValue);
    if (currentValue.Trim ().GetLength () > 0)
    {
        if (dimension > 1)
        {
            dimension = _ttoi (currentValue) - 1;
            newValue.Format (_T ("%d"), dimension);
            SetDlgItemText (ID_OBS_DIM_DISPLAY, newValue);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::DecreaseObsDimension()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: IncreaseObsDimension ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::IncreaseObsDimension()@@@CRHMmainDlg.cpp>");
    CString mode;
    GetDlgItemText (ID_OBS_LAY_DIM_LABEL, mode);
    if (mode == L"OBS")
    {
        CString currentValue;
        CString newValue;
        int dimension = 0;
        GetDlgItemText (ID_OBS_DIM_DISPLAY, currentValue);
        dimension = _ttoi (currentValue);
        if (currentValue.Trim ().GetLength () > 0)
        {
            if (dimension < Global :: maxobs)
            {
                dimension = _ttoi (currentValue) + 1;
                newValue.Format (_T ("%d"), dimension);
                SetDlgItemText (ID_OBS_DIM_DISPLAY, newValue);
            }

        }

    }

    else
    if (mode == L"LAY")
    {
        int maxLayerInSelection = getMaxLayofSelection ();
        CString currentValue;
        CString newValue;
        int dimension = 0;
        GetDlgItemText (ID_OBS_DIM_DISPLAY, currentValue);
        dimension = _ttoi (currentValue);
        if (currentValue.Trim ().GetLength () > 0)
        {
            if (dimension < maxLayerInSelection)
            {
                dimension = _ttoi (currentValue) + 1;
                newValue.Format (_T ("%d"), dimension);
                SetDlgItemText (ID_OBS_DIM_DISPLAY, newValue);
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::IncreaseObsDimension()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnDblClkAllVarListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnDblClkAllVarListBox()@@@CRHMmainDlg.cpp>");
    addVariablesToSelected ();
    updateSelectedVariablesListBox ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnDblClkAllVarListBox()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnDblClkSelVarListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnDblClkSelVarListBox()@@@CRHMmainDlg.cpp>");
    removeVariablesFromSelected ();
    updateSelectedVariablesListBox ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnDblClkSelVarListBox()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnVariableSelectChange ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnVariableSelectChange()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedIndex = listbox_all_variables.GetCurSel ();
    CString selectedText;
    listbox_all_variables.GetText (selectedIndex, selectedText);
    CT2CA pszConvertedAnsiString (selectedText);
    std :: string selectedString (pszConvertedAnsiString);
    std :: map < std :: string, ClassVar * > :: iterator selectedVariable = model -> AllVariables -> find (selectedString);
    std :: string helpString = selectedVariable -> second -> help;
    std :: string unitsString = selectedVariable -> second -> units;
    std :: string nameString = selectedVariable -> second -> name;
    std :: string infoString = nameString + "  Units: " + unitsString + " Help: " + helpString;
    CString infoText (infoString.c_str ());
    SetDlgItemText (ID_VAR_HELP_DISPLAY, (LPCTSTR) infoText);
    setDimensionSelectorToLay ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnVariableSelectChange()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnDblClkAllObsListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnDblClkAllObsListBox()@@@CRHMmainDlg.cpp>");
    addObservationsToSelected ();
    updateSelectedObservationListBox ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnDblClkAllObsListBox()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnDblClkSelObsListBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnDblClkSelObsListBox()@@@CRHMmainDlg.cpp>");
    removeObservationsFromSelected ();
    updateSelectedObservationListBox ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnDblClkSelObsListBox()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnObservationSelectChange ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnObservationSelectChange()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedIndex = listbox_all_observations.GetCurSel ();
    CString selectedText;
    listbox_all_observations.GetText (selectedIndex, selectedText);
    CT2CA pszConvertedAnsiString (selectedText);
    std :: string selectedString (pszConvertedAnsiString);
    std :: map < std :: string, ClassVar * > :: iterator selectedObservation = model -> AllObservations -> find (selectedString);
    std :: string helpString = selectedObservation -> second -> help;
    std :: string unitsString = selectedObservation -> second -> units;
    std :: string nameString = selectedObservation -> second -> name;
    std :: string infoString = nameString + "  Units: " + unitsString + " Help: " + helpString;
    CString infoText (infoString.c_str ());
    SetDlgItemText (ID_OBS_HELP_DISPLAY, (LPCTSTR) infoText);
    setDimensionSelectorToObs ();
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnObservationSelectChange()@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OpenAllVarCtxMenu (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OpenAllVarCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    CMenu ctxMenu;
    ctxMenu.CreatePopupMenu ();
    CString addText ("Add");
    CString addArrayText ("Add All HRUs");
    CString addLayersText ("Add All Layers");
    CString addHRULayersText ("Add All HRUs and Layers");
    ctxMenu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_CTX_ALL_VAR_ADD, (LPCTSTR) addText);
    ctxMenu.InsertMenu (1, MF_BYPOSITION | MF_STRING, ID_CTX_ALL_VAR_ADD_ARRAY, (LPCTSTR) addArrayText);
    ctxMenu.InsertMenu (2, MF_BYPOSITION | MF_STRING, ID_CTX_ALL_VAR_ADD_LAY_ARRAY, (LPCTSTR) addLayersText);
    ctxMenu.InsertMenu (3, MF_BYPOSITION | MF_STRING, ID_CTX_ALL_VAR_ADD_HRU_LAY_ARRAY, (LPCTSTR) addHRULayersText);
    CWnd * wind = AfxGetMainWnd ();
    POINT p;
    if (GetCursorPos (& p))
    {
        UINT result;
        if (result = ctxMenu.TrackPopupMenuEx (TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, p.x, p.y, wind, 0))
        {
            if (result == ID_CTX_ALL_VAR_ADD)
            {
                addVariablesToSelected ();
                updateSelectedVariablesListBox ();
            }

            else
            if (result == ID_CTX_ALL_VAR_ADD_ARRAY)
            {
                addVariablesArrayToSelected ();
                updateSelectedVariablesListBox ();
            }

            else
            if (result == ID_CTX_ALL_VAR_ADD_LAY_ARRAY)
            {
                addVariablesLayerArrayToSelected ();
                updateSelectedVariablesListBox ();
            }

            else
            if (result == ID_CTX_ALL_VAR_ADD_HRU_LAY_ARRAY)
            {
                addVariablesHRULayerArrayToSelected ();
                updateSelectedVariablesListBox ();
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenAllVarCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenAllVarCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OpenSelVarCtxMenu (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OpenSelVarCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    CMenu ctxMenu;
    ctxMenu.CreatePopupMenu ();
    CString removeText ("Remove");
    ctxMenu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_CTX_SEL_VAR_REMOVE, (LPCTSTR) removeText);
    CWnd * wind = AfxGetMainWnd ();
    POINT p;
    if (GetCursorPos (& p))
    {
        UINT result;
        if (result = ctxMenu.TrackPopupMenuEx (TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, p.x, p.y, wind, 0))
        {
            if (result == ID_CTX_SEL_VAR_REMOVE)
            {
                removeVariablesFromSelected ();
                updateSelectedVariablesListBox ();
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenSelVarCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenSelVarCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OpenAllObsCtxMenu (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OpenAllObsCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    CMenu ctxMenu;
    ctxMenu.CreatePopupMenu ();
    CString addText ("Add");
    CString addArrayText ("Add Array");
    ctxMenu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_CTX_ALL_OBS_ADD, (LPCTSTR) addText);
    ctxMenu.InsertMenu (1, MF_BYPOSITION | MF_STRING, ID_CTX_ALL_OBS_ADD_ARRAY, (LPCTSTR) addArrayText);
    CWnd * wind = AfxGetMainWnd ();
    POINT p;
    if (GetCursorPos (& p))
    {
        UINT result;
        if (result = ctxMenu.TrackPopupMenuEx (TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, p.x, p.y, wind, 0))
        {
            if (result == ID_CTX_ALL_OBS_ADD)
            {
                addObservationsToSelected ();
                updateSelectedObservationListBox ();
            }

            else
            if (result == ID_CTX_ALL_OBS_ADD_ARRAY)
            {
                addObservationsArrayToSelected ();
                updateSelectedObservationListBox ();
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenAllObsCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenAllObsCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OpenSelObsCtxMenu (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OpenSelObsCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    CMenu ctxMenu;
    ctxMenu.CreatePopupMenu ();
    CString removeText ("Remove");
    ctxMenu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_CTX_SEL_OBS_REMOVE, (LPCTSTR) removeText);
    CWnd * wind = AfxGetMainWnd ();
    POINT p;
    if (GetCursorPos (& p))
    {
        UINT result;
        if (result = ctxMenu.TrackPopupMenuEx (TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, p.x, p.y, wind, 0))
        {
            if (result == ID_CTX_SEL_OBS_REMOVE)
            {
                removeObservationsFromSelected ();
                updateSelectedObservationListBox ();
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenSelObsCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OpenSelObsCtxMenu(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnStartDateChange (NMHDR * pNMHDR, LRESULT * pResult)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnStartDateChange(NMHDR * pNMHDR, LRESULT * pResult)@@@CRHMmainDlg.cpp>");
    COleDateTime dateTime;
    StartDatePicker.GetTime (dateTime);
    CRHMmain :: getInstance () -> setStartDate (dateTime.m_dt);
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnStartDateChange(NMHDR * pNMHDR, LRESULT * pResult)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnEndDateChange (NMHDR * pNMHDR, LRESULT * pResult)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnEndDateChange(NMHDR * pNMHDR, LRESULT * pResult)@@@CRHMmainDlg.cpp>");
    COleDateTime dateTime;
    EndDatePicker.GetTime (dateTime);
    CRHMmain :: getInstance () -> setEndDate (dateTime.m_dt);
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnEndDateChange(NMHDR * pNMHDR, LRESULT * pResult)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: OnClickFlipTicks ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnClickFlipTicks()@@@CRHMmainDlg.cpp>");
    CSeries series;
    bool active;
    int count = tchart.get_SeriesCount ();
    for (int i = 0; i < count; i ++) {
        series = tchart.Series (i);
        active = series.get_Active ();
        series.put_Active (! active);
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnClickFlipTicks()@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OnLeftClickFlipTicks (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnLeftClickFlipTicks(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    CSeries series;
    bool active;
    int count = tchart.get_SeriesCount ();
    for (int i = 0; i < count; i ++) {
        series = tchart.Series (i);
        CString title = series.get_LegendTitle ();
        CT2CA convert (title);
        std :: string titleString (convert);
        std :: list < std :: pair < std :: string, TSeries * >> * selectedObservations = model -> getSelectedObservations ();
        for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = selectedObservations -> begin (); it != selectedObservations -> end (); it ++) {
            if (it -> first == titleString)
            {
                active = series.get_Active ();
                series.put_Active (! active);
                break;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnLeftClickFlipTicks(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnLeftClickFlipTicks(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OnRightClickFlipTicks (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnRightClickFlipTicks(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    CSeries series;
    bool active;
    int count = tchart.get_SeriesCount ();
    for (int i = 0; i < count; i ++) {
        series = tchart.Series (i);
        CString title = series.get_LegendTitle ();
        CT2CA convert (title);
        std :: string titleString (convert);
        std :: list < std :: pair < std :: string, ClassVar * >> * selectedVariables = model -> getSelectedVariables ();
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = selectedVariables -> begin (); it != selectedVariables -> end (); it ++) {
            if (it -> first == titleString)
            {
                active = series.get_Active ();
                series.put_Active (! active);
                break;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnRightClickFlipTicks(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnRightClickFlipTicks(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: addVariablesToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::addVariablesToSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_variables.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_variables.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        bool dimensionSelected = true;
        std :: string seriesTitle = "";
        CString selectedText;
        listbox_all_variables.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        CString hruDimensionText;
        int hruDimension = 1;
        GetDlgItemText (ID_HRU_DIM_DISPLAY, hruDimensionText);
        hruDimension = _ttoi (hruDimensionText);
        CString layDimensionText;
        int layDimension = 0;
        GetDlgItemText (ID_OBS_DIM_DISPLAY, layDimensionText);
        layDimension = _ttoi (layDimensionText);
        ClassVar * varVar = model -> AllVariables -> find (selectedString) -> second;
        if (varVar -> lay == 0)
        {
            seriesTitle = selectedString + "(" + to_string (hruDimension) + ")";
            dimensionSelected = variableIsSelected (seriesTitle);
            while (dimensionSelected && hruDimension < Global :: maxhru) {
                hruDimension ++;
                seriesTitle = selectedString + "(" + to_string (hruDimension) + ")";
                dimensionSelected = variableIsSelected (seriesTitle);
            }
        }

        else
        if (varVar -> lay > 0)
        {
            if (layDimension <= varVar -> lay)
            {
                seriesTitle = selectedString + "(" + to_string (hruDimension) + "," + to_string (layDimension) + ")";
                dimensionSelected = variableIsSelected (seriesTitle);
                while (dimensionSelected && hruDimension < Global :: maxhru) {
                    hruDimension ++;
                    seriesTitle = selectedString + "(" + to_string (hruDimension) + "," + to_string (layDimension) + ")";
                    dimensionSelected = variableIsSelected (seriesTitle);
                }
            }

        }

        if (dimensionSelected == false)
        {
            model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (seriesTitle, varVar));
        }

    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::addVariablesToSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: addVariablesArrayToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::addVariablesArrayToSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_variables.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_variables.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_all_variables.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        CString layDimensionText;
        int layDimension = 0;
        GetDlgItemText (ID_OBS_DIM_DISPLAY, layDimensionText);
        layDimension = _ttoi (layDimensionText);
        ClassVar * varVar = model -> AllVariables -> find (selectedString) -> second;
        if (varVar -> lay == 0)
        {
            for (int i = 1; i <= Global :: maxhru; i ++) {
                std :: string varTitle = selectedString + "(" + to_string (i) + ")";
                bool dimensionSelected = variableIsSelected (varTitle);
                if (dimensionSelected == false)
                {
                    model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (varTitle, varVar));
                }

            }
        }

        else
        {
            for (int i = 1; i <= Global :: maxhru; i ++) {
                std :: string varTitle = selectedString + "(" + to_string (i) + "," + to_string (layDimension) + ")";
                bool dimensionSelected = variableIsSelected (varTitle);
                if (dimensionSelected == false)
                {
                    model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (varTitle, varVar));
                }

            }
        }

    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::addVariablesArrayToSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: addVariablesLayerArrayToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::addVariablesLayerArrayToSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_variables.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_variables.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_all_variables.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        CString hruDimensionText;
        int hruDimension = 1;
        GetDlgItemText (ID_HRU_DIM_DISPLAY, hruDimensionText);
        hruDimension = _ttoi (hruDimensionText);
        ClassVar * varVar = model -> AllVariables -> find (selectedString) -> second;
        if (varVar -> lay == 0)
        {
            std :: string varTitle = selectedString + "(" + to_string (hruDimension) + ")";
            bool dimensionSelected = variableIsSelected (varTitle);
            if (dimensionSelected == false)
            {
                model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (varTitle, varVar));
            }

        }

        else
        {
            for (int j = 1; j <= varVar -> lay; j ++) {
                std :: string varTitle = selectedString + "(" + to_string (hruDimension) + "," + to_string (j) + ")";
                bool dimensionSelected = variableIsSelected (varTitle);
                if (dimensionSelected == false)
                {
                    model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (varTitle, varVar));
                }

            }
        }

    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::addVariablesLayerArrayToSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: addVariablesHRULayerArrayToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::addVariablesHRULayerArrayToSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_variables.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_variables.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        bool dimensionSelected = true;
        std :: string seriesTitle = "";
        CString selectedText;
        listbox_all_variables.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        ClassVar * varVar = model -> AllVariables -> find (selectedString) -> second;
        if (varVar -> lay == 0)
        {
            for (int j = 1; j <= Global :: maxhru; j ++) {
                seriesTitle = selectedString + "(" + to_string (j) + ")";
                dimensionSelected = variableIsSelected (seriesTitle);
                if (dimensionSelected == false)
                {
                    model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (seriesTitle, varVar));
                }

            }
        }

        else
        if (varVar -> lay > 0)
        {
            for (int j = 1; j <= Global :: maxhru; j ++) {
                for (int k = 1; k <= varVar -> lay; k ++) {
                    seriesTitle = selectedString + "(" + to_string (j) + "," + to_string (k) + ")";
                    dimensionSelected = variableIsSelected (seriesTitle);
                    if (dimensionSelected == false)
                    {
                        model -> SelectedVariables -> push_back (std :: pair < std :: string, ClassVar * > (seriesTitle, varVar));
                    }

                }
            }
        }

    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::addVariablesHRULayerArrayToSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: addObservationsToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::addObservationsToSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_observations.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_observations.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_all_observations.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        CString currentValue;
        int dimension = 1;
        GetDlgItemText (ID_OBS_DIM_DISPLAY, currentValue);
        dimension = _ttoi (currentValue);
        ClassVar * obsVar = model -> AllObservations -> find (selectedString) -> second;
        std :: string seriesTitle = selectedString + "(" + to_string (dimension) + ")";
        bool dimensionSelected = observationIsSelected (seriesTitle);
        while (dimensionSelected && dimension < Global :: maxobs) {
            dimension ++;
            seriesTitle = selectedString + "(" + to_string (dimension) + ")";
            dimensionSelected = observationIsSelected (seriesTitle);
        }
        if (dimensionSelected == false)
        {
            TSeries * cdSeries = NULL;
            if (obsVar -> FileData -> Times == NULL)
            {
                cdSeries = new TSeries ();
            }

            else
            {
                cdSeries = new TSeries ();
            }

            cdSeries -> Tag = obsVar;
            cdSeries -> Title = seriesTitle;
            model -> SelectedObservations -> push_back (std :: pair < std :: string, TSeries * > (seriesTitle, cdSeries));
        }

    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::addObservationsToSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: addObservationsArrayToSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::addObservationsArrayToSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_observations.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_observations.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_all_observations.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        ClassVar * obsVar = model -> AllObservations -> find (selectedString) -> second;
        for (int i = 1; i <= Global :: maxobs; i ++) {
            std :: string seriesTitle = selectedString + "(" + to_string (i) + ")";
            bool dimensionSelected = observationIsSelected (seriesTitle);
            if (dimensionSelected == false)
            {
                TSeries * cdSeries = NULL;
                if (obsVar -> FileData -> Times == NULL)
                {
                    cdSeries = new TSeries ();
                }

                else
                {
                    cdSeries = new TSeries ();
                }

                cdSeries -> Tag = obsVar;
                cdSeries -> Title = seriesTitle;
                model -> SelectedObservations -> push_back (std :: pair < std :: string, TSeries * > (seriesTitle, cdSeries));
            }

        }
    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::addObservationsArrayToSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: removeVariablesFromSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::removeVariablesFromSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_sel_variables.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_sel_variables.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_sel_variables.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        std :: list < std :: pair < std :: string, ClassVar * >> * listOfSelectedVariables = model -> SelectedVariables;
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = listOfSelectedVariables -> begin (); it != listOfSelectedVariables -> end (); it ++) {
            if (it -> first == selectedString)
            {
                listOfSelectedVariables -> erase (it);
                break;
            }

        }
    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::removeVariablesFromSelected()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: removeObservationsFromSelected ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::removeObservationsFromSelected()@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_sel_observations.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_sel_observations.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_sel_observations.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        std :: list < std :: pair < std :: string, TSeries * >> * selectedObservations = model -> SelectedObservations;
        for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = selectedObservations -> begin (); it != selectedObservations -> end (); it ++) {
            if (it -> first == selectedString)
            {
                delete (it -> second);
                selectedObservations -> erase (it);
                break;
            }

        }
    }
    delete [] selectedIndicies;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::removeObservationsFromSelected()@@@CRHMmainDlg.cpp>");
}
bool CRHMmainDlg :: variableIsSelected (std :: string seriesTitle)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::variableIsSelected(std :: string seriesTitle)@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    bool alreadyInModel = false;
    for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator it = model -> SelectedVariables -> begin (); it != model -> SelectedVariables -> end (); it ++) {
        if (it -> first == seriesTitle)
        {
            alreadyInModel = true;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::variableIsSelected(std :: string seriesTitle)@@@CRHMmainDlg.cpp>");
    return alreadyInModel;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::variableIsSelected(std :: string seriesTitle)@@@CRHMmainDlg.cpp>");
}
bool CRHMmainDlg :: observationIsSelected (std :: string seriesTitle)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::observationIsSelected(std :: string seriesTitle)@@@CRHMmainDlg.cpp>");
    CRHMmain * model = CRHMmain :: getInstance ();
    bool alreadyInModel = false;
    for (std :: list < std :: pair < std :: string, TSeries * >> :: iterator it = model -> SelectedObservations -> begin (); it != model -> SelectedObservations -> end (); it ++) {
        if (it -> first == seriesTitle)
        {
            alreadyInModel = true;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::observationIsSelected(std :: string seriesTitle)@@@CRHMmainDlg.cpp>");
    return alreadyInModel;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::observationIsSelected(std :: string seriesTitle)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: SetItemsToListBox (int listboxid, std :: vector < std :: string > * list)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::SetItemsToListBox(int listboxid, std :: vector < std :: string > * list)@@@CRHMmainDlg.cpp>");
    CListBox * listbox = (CListBox *) GetDlgItem (listboxid);
    size_t count = list -> size ();
    for (size_t i = 0; i < count; i ++) {
        string str = list -> at (i);
        CString cstr (str.c_str ());
        listbox -> AddString (cstr);
    }
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::SetItemsToListBox(int listboxid, std :: vector < std :: string > * list)@@@CRHMmainDlg.cpp>");
}
std :: list < std :: pair < std :: string, ClassVar * >> * CRHMmainDlg :: GetSelectedVariables ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::GetSelectedVariables()@@@CRHMmainDlg.cpp>");
    CRHMmain * t = CRHMmain :: getInstance ();
    std :: list < std :: pair < std :: string, ClassVar * >> * list = new std :: list < std :: pair < std :: string, ClassVar * >> ();
    CListBox * listbox = (CListBox *) GetDlgItem (ID_SEL_VAR_LIST_BOX);
    int itemcount = listbox -> GetCount ();
    for (int i = 0; i < itemcount; i ++) {
        CString cstr;
        listbox -> GetText (i, cstr);
        CT2A str (cstr);
        string s = str;
        ClassVar * obj = t -> GetObjectOfVariable (s);
        list -> push_back (std :: pair < std :: string, ClassVar * > (s, obj));
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::GetSelectedVariables()@@@CRHMmainDlg.cpp>");
    return list;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::GetSelectedVariables()@@@CRHMmainDlg.cpp>");
}
std :: list < std :: pair < std :: string, TSeries * >> * CRHMmainDlg :: GetSelectedObservations ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::GetSelectedObservations()@@@CRHMmainDlg.cpp>");
    CRHMmain * t = CRHMmain :: getInstance ();
    std :: list < std :: pair < std :: string, TSeries * >> * list = new std :: list < std :: pair < std :: string, TSeries * >> ();
    CListBox * listbox = (CListBox *) GetDlgItem (ID_SEL_OBS_LIST_BOX);
    int itemcount = listbox -> GetCount ();
    for (int i = 0; i < itemcount; i ++) {
        CString cstr;
        listbox -> GetText (i, cstr);
        CT2A str (cstr);
        string s = str;
        ClassVar * var = t -> GetObjectOfObservation (s);
        TSeries * obj = new TSeries ();
        obj -> Tag = var;
        obj -> Title = s;
        list -> push_back (std :: pair < std :: string, TSeries * > (s, obj));
    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::GetSelectedObservations()@@@CRHMmainDlg.cpp>");
    return list;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::GetSelectedObservations()@@@CRHMmainDlg.cpp>");
}
void HruNameClick ()
{
InstrumentLogger::instance()->log_instrument_log("<HruNameClick()@@@CRHMmainDlg.cpp>");
    CRHMmain * test = CRHMmain :: getInstance ();
    MapPar :: iterator itPar;
    ClassPar * newPar;
    long Hru, Lay;
    if (! test -> ListHruNames)
    {
        test -> ListHruNames = new std :: vector < std :: string >;
        test -> MapGrpNames = new MapstrSS;
        if ((itPar = Global :: MapPars.find ("basin basin_name")) != Global :: MapPars.end ())
        {
            newPar = (* itPar).second;
            test -> ListHruNames -> push_back (newPar -> Strings -> at (0));
        }

        else
        {
            test -> ListHruNames -> push_back ("Basin");
        }

        if ((itPar = Global :: MapPars.find ("basin hru_names")) != Global :: MapPars.end ())
        {
            newPar = (* itPar).second;
            for (size_t ii = 0; ii < newPar -> Strings -> size (); ++ ii) {
                test -> ListHruNames -> push_back (newPar -> Strings -> at (ii));
            }
        }

        else
        {
            for (int ii = 0; ii < Global :: nhru; ++ ii)
                test -> ListHruNames -> push_back ("hru" + to_string (ii));
        }

        for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
            ClassModule * Mod = modIt -> second;
            string S = modIt -> first;
            if (Mod -> GroupCnt > 0 || Mod -> StructCnt > 0)
            {
                if (Mod -> GroupCnt > 0)
                {
                    string AA;
                    Common :: GroupEnding (AA, Mod -> GroupCnt);
                    Pairstr Item = Pairstr (AA.c_str (), ('@' + Mod -> Name).c_str ());
                    test -> MapGrpNames -> insert (Item);
                }

                else
                if (Mod -> StructCnt > 0)
                {
                    string AA;
                    Common :: GroupEnding (AA, Mod -> GroupCnt);
                    Pairstr Item = Pairstr (AA.c_str (), ('@' + Mod -> Name).c_str ());
                    test -> MapGrpNames -> insert (Item);
                }

            }

        }
        std :: list < std :: pair < std :: string, ClassVar * >> * SelectedVariablesUpdated = new std :: list < std :: pair < std :: string, ClassVar * >> ();
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator selectedVariablesIt = test -> SelectedVariables -> begin (); selectedVariablesIt != test -> SelectedVariables -> end (); selectedVariablesIt ++) {
            string S = selectedVariablesIt -> first;
            ClassVar * thisVar = selectedVariablesIt -> second;
            test -> HruNames = false;
            S = test -> ExtractHruLay (S, Hru, Lay);
            test -> HruNames = true;
            S = test -> BuildHru (S, Hru, thisVar -> dimen);
            if (Lay)
            {
                S = test -> BuildLay (S, Lay);
            }

            int Indx = S.find ("@");
            if (Indx)
            {
                MapstrSS :: iterator it;
                if ((it = test -> MapGrpNames -> find (S.substr (Indx, 2))) != test -> MapGrpNames -> end ())
                {
                    string NewName = (* it).second;
                    S.replace (Indx, 2, "");
                    S.insert (Indx, NewName);
                }

            }

            SelectedVariablesUpdated -> push_back (std :: pair < std :: string, ClassVar * > (S, thisVar));
        }
        delete test -> SelectedVariables;
        test -> setSelectedVariables (SelectedVariablesUpdated);
    }

    else
    {
        std :: list < std :: pair < std :: string, ClassVar * >> * SelectedVariablesUpdated = new std :: list < std :: pair < std :: string, ClassVar * >> ();
        for (std :: list < std :: pair < std :: string, ClassVar * >> :: iterator selectedVariableIt = test -> SelectedVariables -> begin (); selectedVariableIt != test -> SelectedVariables -> end (); selectedVariableIt ++) {
            string S = selectedVariableIt -> first;
            test -> HruNames = true;
            S = test -> ExtractHruLay (S, Hru, Lay);
            test -> HruNames = false;
            S = test -> BuildHru (S, Hru, TDim :: NHRU);
            if (Lay)
            {
                S = test -> BuildLay (S, Lay);
            }

            int Indx = S.find ("@");
            if (Indx)
            {
                MapstrSS :: iterator it;
                for (it = test -> MapGrpNames -> begin (); it != test -> MapGrpNames -> end (); ++ it) {
                    int pos = S.find ((* it).second);
                    if (pos)
                    {
                        string NewName = (* it).first;
                        string Name = (* it).second;
                        int Len = Name.length ();
                        int End = S.find ("(");
                        if (End - pos == Len)
                        {
                            S.replace (pos, Len, "");
                            S.insert (pos, NewName);
                            break;
                        }

                    }

                }
            }

            SelectedVariablesUpdated -> push_back (std :: pair < std :: string, ClassVar * > (S, selectedVariableIt -> second));
        }
        delete test -> SelectedVariables;
        test -> setSelectedVariables (SelectedVariablesUpdated);
        delete test -> ListHruNames;
        test -> ListHruNames = NULL;
        delete test -> MapGrpNames;
        test -> MapGrpNames = NULL;
    }

InstrumentLogger::instance()->log_instrument_log("</HruNameClick()@@@CRHMmainDlg.cpp>");
}
LRESULT CRHMmainDlg :: OnAutoRunMessage (WPARAM, LPARAM)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::OnAutoRunMessage(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    this -> RunClickFunction ();

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnAutoRunMessage(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::OnAutoRunMessage(WPARAM, LPARAM)@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: setDimensionSelectorToObs ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::setDimensionSelectorToObs()@@@CRHMmainDlg.cpp>");
    SetDlgItemText (ID_OBS_LAY_DIM_LABEL, L"OBS");
    CString currentValue;
    int dimension = 0;
    GetDlgItemText (ID_OBS_DIM_DISPLAY, currentValue);
    dimension = _ttoi (currentValue);
    if (currentValue.Trim ().GetLength () > 0)
    {
        if (dimension > Global :: maxobs)
        {
            SetDlgItemText (ID_OBS_DIM_DISPLAY, L"1");
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::setDimensionSelectorToObs()@@@CRHMmainDlg.cpp>");
}
void CRHMmainDlg :: setDimensionSelectorToLay ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::setDimensionSelectorToLay()@@@CRHMmainDlg.cpp>");
    int maxLayInSelection = getMaxLayofSelection ();
    SetDlgItemText (ID_OBS_LAY_DIM_LABEL, L"LAY");
    CString currentValue;
    int dimension = 0;
    GetDlgItemText (ID_OBS_DIM_DISPLAY, currentValue);
    dimension = _ttoi (currentValue);
    if (currentValue.Trim ().GetLength () > 0)
    {
        if (dimension > maxLayInSelection)
        {
            SetDlgItemText (ID_OBS_DIM_DISPLAY, L"1");
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::setDimensionSelectorToLay()@@@CRHMmainDlg.cpp>");
}
int CRHMmainDlg :: getMaxLayofSelection ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMmainDlg::getMaxLayofSelection()@@@CRHMmainDlg.cpp>");
    int maxLayInSelection = 0;
    CRHMmain * model = CRHMmain :: getInstance ();
    int selectedCount = listbox_all_variables.GetSelCount ();
    int * selectedIndicies = new int [selectedCount];
    listbox_all_variables.GetSelItems (selectedCount, selectedIndicies);
    for (int i = 0; i < selectedCount; i ++) {
        CString selectedText;
        listbox_all_variables.GetText (selectedIndicies [i], selectedText);
        CT2CA pszConvertedAnsiString (selectedText);
        std :: string selectedString (pszConvertedAnsiString);
        std :: map < std :: string, ClassVar * > :: iterator selected = model -> AllVariables -> find (selectedString);
        int layers = selected -> second -> lay;
        if (layers > maxLayInSelection)
        {
            maxLayInSelection = layers;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::getMaxLayofSelection()@@@CRHMmainDlg.cpp>");
    return maxLayInSelection;
InstrumentLogger::instance()->log_instrument_log("</CRHMmainDlg::getMaxLayofSelection()@@@CRHMmainDlg.cpp>");
}