#include "../stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CRHM_GUI.h"
#include "MainFrm.h"
#include "CRHM_GUIDoc.h"
#include "CRHM_GUIView.h"
#include "CTChart.h"
#include "CRHMmainDlg.h"
#include "CWebBrowser.h"
#include "../../src/core/InstrumentLogger.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP (CCRHMGUIApp, CWinAppEx)
    ON_COMMAND (ID_APP_ABOUT, & CCRHMGUIApp :: OnAppAbout)
    ON_COMMAND (ID_FILE_NEW, & CWinAppEx :: OnFileNew)
    ON_COMMAND (ID_FILE_OPEN, & CWinAppEx :: OnFileOpen)
    ON_COMMAND (ID_FILE_PRINT_SETUP, & CWinAppEx :: OnFilePrintSetup)
END_MESSAGE_MAP ()

CCRHMGUIApp :: CCRHMGUIApp ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::CCRHMGUIApp()@@@CRHM_GUI.cpp>");
    m_bHiColorIcons = TRUE;
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;

    #ifdef _MANAGED
        System :: Windows :: Forms :: Application :: SetUnhandledExceptionMode (System :: Windows :: Forms :: UnhandledExceptionMode :: ThrowException);
    #endif

    SetAppID (_T ("CRHMGUI.AppID.NoVersion"));
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::CCRHMGUIApp()@@@CRHM_GUI.cpp>");
}CCRHMGUIApp theApp;

BOOL CCRHMGUIApp :: InitInstance ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::InitInstance()@@@CRHM_GUI.cpp>");
    try {
        INITCOMMONCONTROLSEX InitCtrls;
        InitCtrls.dwSize = sizeof (InitCtrls);
        InitCtrls.dwICC = ICC_WIN95_CLASSES;
        InitCommonControlsEx (& InitCtrls);
        CWinAppEx :: InitInstance ();
        if (! AfxOleInit ())
        {
            AfxMessageBox (IDP_OLE_INIT_FAILED);

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::InitInstance()@@@CRHM_GUI.cpp>");
            return FALSE;
        }

        AfxEnableControlContainer ();
        EnableTaskbarInteraction (TRUE);
        SetRegistryKey (_T ("Local AppWizard-Generated Applications"));
        LoadStdProfileSettings (4);
        InitKeyboardManager ();
        InitTooltipManager ();
        CMFCToolTipInfo ttParams;
        ttParams.m_bVislManagerTheme = TRUE;
        theApp.GetTooltipManager () -> SetTooltipParams (AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS (CMFCToolTipCtrl), & ttParams);
        CSingleDocTemplate * pDocTemplate;
        pDocTemplate = new CSingleDocTemplate (IDR_MAINFRAME, RUNTIME_CLASS (CCRHMGUIDoc), RUNTIME_CLASS (CMainFrame), RUNTIME_CLASS (CCRHMGUIView));
        if (! pDocTemplate)
        {

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::InitInstance()@@@CRHM_GUI.cpp>");
            return FALSE;
        }

        AddDocTemplate (pDocTemplate);
        CString commandText = GetCommandLine ();
        std :: string commandString = CT2A (commandText.GetString ());
        char * cmdLine = new char [commandString.length () + 1];
        strcpy (cmdLine, commandString.c_str ());
        static int numberOfArgs = __argc;
        int argc = 0;
        char ** argv;
        argv = (char **) malloc (sizeof (char *) * numberOfArgs);
        char * pos = strtok (cmdLine, " ");
        while (pos != NULL) {
            argv [argc] = pos;
            pos = strtok (NULL, " ");
            argc ++;
        }
        CRHMArguments * args = new CRHMArguments ();
        if (argc > 1)
        {
            EnablePrintfAtMFC ();
            args -> readCommandLine (argc, argv);
            args -> validate ();
        }

        delete [] cmdLine;
        free (argv);
        if (args -> get_project_name () != "")
        {
            CRHMmain * model = new CRHMmain (args);
            std :: string projectArgument = args -> get_project_name ();
            model -> OpenNamePrj = projectArgument;
            model -> DoPrjOpen (projectArgument, "");
            model -> RunClick ();
        }

        else
        {
            CRHMmainDlg dlgOptions;
            dlgOptions.DoModal ();
        }

        delete args;

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::InitInstance()@@@CRHM_GUI.cpp>");
        return TRUE;
    }
    catch (...) {

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::InitInstance()@@@CRHM_GUI.cpp>");
        return FALSE;
    }
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::InitInstance()@@@CRHM_GUI.cpp>");
}
void CCRHMGUIApp :: EnablePrintfAtMFC ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::EnablePrintfAtMFC()@@@CRHM_GUI.cpp>");
    if (AttachConsole (ATTACH_PARENT_PROCESS))
    {
        FILE * pCout;
        freopen_s (& pCout, "CONOUT$", "w", stdout);
        std :: cout.clear ();
        std :: wcout.clear ();
    }

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::EnablePrintfAtMFC()@@@CRHM_GUI.cpp>");
}
int CCRHMGUIApp :: ExitInstance ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::ExitInstance()@@@CRHM_GUI.cpp>");
    AfxOleTerm (FALSE);

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::ExitInstance()@@@CRHM_GUI.cpp>");
    return CWinAppEx :: ExitInstance ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::ExitInstance()@@@CRHM_GUI.cpp>");
}
class CAboutDlg : public CDialogEx {

  public:
    CAboutDlg ();

    #ifdef AFX_DESIGN_TIME
        enum {IDD = IDD_ABOUTBOX};
    #endif

  protected:
    virtual void DoDataExchange (CDataExchange * pDX);

  protected : public:
    CButton ok;
};

CAboutDlg :: CAboutDlg (): CDialogEx (IDD_ABOUTBOX)
{
InstrumentLogger::instance()->log_instrument_log("<CAboutDlg::CAboutDlg(): CDialogEx (IDD_ABOUTBOX)@@@CRHM_GUI.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CAboutDlg::CAboutDlg(): CDialogEx (IDD_ABOUTBOX)@@@CRHM_GUI.cpp>");
}
void CAboutDlg :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<CAboutDlg::DoDataExchange(CDataExchange * pDX)@@@CRHM_GUI.cpp>");
    CDialogEx :: DoDataExchange (pDX);
    DDX_Control (pDX, IDOK, ok);
InstrumentLogger::instance()->log_instrument_log("</CAboutDlg::DoDataExchange(CDataExchange * pDX)@@@CRHM_GUI.cpp>");
}
void CCRHMGUIApp :: OnAppAbout ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::OnAppAbout()@@@CRHM_GUI.cpp>");
    CAboutDlg aboutDlg;
    aboutDlg.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::OnAppAbout()@@@CRHM_GUI.cpp>");
}
void CCRHMGUIApp :: PreLoadState ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::PreLoadState()@@@CRHM_GUI.cpp>");
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString (IDS_EDIT_MENU);
    ASSERT (bNameValid);
    GetContextMenuManager () -> AddMenu (strName, IDR_POPUP_EDIT);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::PreLoadState()@@@CRHM_GUI.cpp>");
}
void CCRHMGUIApp :: LoadCustomState ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::LoadCustomState()@@@CRHM_GUI.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::LoadCustomState()@@@CRHM_GUI.cpp>");
}
void CCRHMGUIApp :: SaveCustomState ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIApp::SaveCustomState()@@@CRHM_GUI.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIApp::SaveCustomState()@@@CRHM_GUI.cpp>");
}