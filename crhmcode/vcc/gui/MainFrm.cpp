#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "MainFrm.h"
#include "../../src/core/InstrumentLogger.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE (CMainFrame, CFrameWndEx) const int iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;
BEGIN_MESSAGE_MAP (CMainFrame, CFrameWndEx)
    ON_WM_CREATE ()
    ON_COMMAND (ID_VIEW_CUSTOMIZE, & CMainFrame :: OnViewCustomize)
    ON_REGISTERED_MESSAGE (AFX_WM_CREATETOOLBAR, & CMainFrame :: OnToolbarCreateNew)
    ON_COMMAND_RANGE (ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, & CMainFrame :: OnApplicationLook)
    ON_UPDATE_COMMAND_UI_RANGE (ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, & CMainFrame :: OnUpdateApplicationLook)
    ON_WM_SETTINGCHANGE ()
END_MESSAGE_MAP ()
static UINT indicators [] = {ID_SEPARATOR, ID_INDICATOR_CAPS, ID_INDICATOR_NUM, ID_INDICATOR_SCRL,};

CMainFrame :: CMainFrame ()
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::CMainFrame()@@@MainFrm.cpp>");
    theApp.m_nAppLook = theApp.GetInt (_T ("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::CMainFrame()@@@MainFrm.cpp>");
}
CMainFrame :: ~CMainFrame ()
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::~CMainFrame()@@@MainFrm.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::~CMainFrame()@@@MainFrm.cpp>");
}
int CMainFrame :: OnCreate (LPCREATESTRUCT lpCreateStruct)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
    if (CFrameWndEx :: OnCreate (lpCreateStruct) == - 1)
    {

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
        return - 1;
    }

    BOOL bNameValid;
    if (! m_wndMenuBar.Create (this))
    {
        TRACE0 ("Failed to create menubar\n");

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
        return - 1;
    }

    m_wndMenuBar.SetPaneStyle (m_wndMenuBar.GetPaneStyle () | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
    CMFCPopupMenu :: SetForceMenuFocus (FALSE);
    if (! m_wndToolBar.CreateEx (this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || ! m_wndToolBar.LoadToolBar (theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
    {
        TRACE0 ("Failed to create toolbar\n");

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
        return - 1;
    }

    CString strToolBarName;
    bNameValid = strToolBarName.LoadString (IDS_TOOLBAR_STANDARD);
    ASSERT (bNameValid);
    m_wndToolBar.SetWindowText (strToolBarName);
    CString strCustomize;
    bNameValid = strCustomize.LoadString (IDS_TOOLBAR_CUSTOMIZE);
    ASSERT (bNameValid);
    m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
    InitUserToolbars (nullptr, uiFirstUserToolBarId, uiLastUserToolBarId);
    if (! m_wndStatusBar.Create (this))
    {
        TRACE0 ("Failed to create status bar\n");

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
        return - 1;
    }

    m_wndStatusBar.SetIndicators (indicators, sizeof (indicators) / sizeof (UINT));
    m_wndMenuBar.EnableDocking (CBRS_ALIGN_ANY);
    m_wndToolBar.EnableDocking (CBRS_ALIGN_ANY);
    EnableDocking (CBRS_ALIGN_ANY);
    DockPane (& m_wndMenuBar);
    DockPane (& m_wndToolBar);
    CDockingManager :: SetDockingMode (DT_SMART);
    EnableAutoHidePanes (CBRS_ALIGN_ANY);
    if (! CreateDockingWindows ())
    {
        TRACE0 ("Failed to create docking windows\n");

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
        return - 1;
    }

    m_wndOutput.EnableDocking (CBRS_ALIGN_ANY);
    DockPane (& m_wndOutput);
    OnApplicationLook (theApp.m_nAppLook);
    EnablePaneMenu (TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);
    CMFCToolBar :: EnableQuickCustomization ();
    if (CMFCToolBar :: GetUserImages () == nullptr)
    {
        if (m_UserImages.Load (_T (".\\UserImages.bmp")))
        {
            CMFCToolBar :: SetUserImages (& m_UserImages);
        }

    }

    CList < UINT, UINT > lstBasicCommands;
    lstBasicCommands.AddTail (ID_FILE_NEW);
    lstBasicCommands.AddTail (ID_FILE_OPEN);
    lstBasicCommands.AddTail (ID_FILE_SAVE);
    lstBasicCommands.AddTail (ID_APP_EXIT);
    lstBasicCommands.AddTail (ID_EDIT_CUT);
    lstBasicCommands.AddTail (ID_EDIT_PASTE);
    lstBasicCommands.AddTail (ID_EDIT_UNDO);
    lstBasicCommands.AddTail (ID_APP_ABOUT);
    lstBasicCommands.AddTail (ID_VIEW_STATUS_BAR);
    lstBasicCommands.AddTail (ID_VIEW_TOOLBAR);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_OFF_2003);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS_2005);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_OFF_2007_BLUE);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_OFF_2007_SILVER);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_OFF_2007_BLACK);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_OFF_2007_AQUA);
    lstBasicCommands.AddTail (ID_VIEW_APPLOOK_WINDOWS_7);
    CMFCToolBar :: SetBasicCommands (lstBasicCommands);

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@MainFrm.cpp>");
}
BOOL CMainFrame :: PreCreateWindow (CREATESTRUCT & cs)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::PreCreateWindow(CREATESTRUCT & cs)@@@MainFrm.cpp>");
    if (! CFrameWndEx :: PreCreateWindow (cs))
    {

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::PreCreateWindow(CREATESTRUCT & cs)@@@MainFrm.cpp>");
        return FALSE;
    }

    cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::PreCreateWindow(CREATESTRUCT & cs)@@@MainFrm.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::PreCreateWindow(CREATESTRUCT & cs)@@@MainFrm.cpp>");
}
BOOL CMainFrame :: CreateDockingWindows ()
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::CreateDockingWindows()@@@MainFrm.cpp>");
    BOOL bNameValid;
    CString strOutputWnd;
    bNameValid = strOutputWnd.LoadString (IDS_OUTPUT_WND);
    ASSERT (bNameValid);
    if (! m_wndOutput.Create (strOutputWnd, this, CRect (0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
    {
        TRACE0 ("Failed to create Output window\n");

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::CreateDockingWindows()@@@MainFrm.cpp>");
        return FALSE;
    }

    SetDockingWindowIcons (theApp.m_bHiColorIcons);

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::CreateDockingWindows()@@@MainFrm.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::CreateDockingWindows()@@@MainFrm.cpp>");
}
void CMainFrame :: SetDockingWindowIcons (BOOL bHiColorIcons)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)@@@MainFrm.cpp>");
    HICON hOutputBarIcon = (HICON) :: LoadImage (:: AfxGetResourceHandle (), MAKEINTRESOURCE (bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, :: GetSystemMetrics (SM_CXSMICON), :: GetSystemMetrics (SM_CYSMICON), 0);
    m_wndOutput.SetIcon (hOutputBarIcon, FALSE);
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)@@@MainFrm.cpp>");
}
#ifdef _DEBUG

    void CMainFrame :: AssertValid () const
    {
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::AssertValid() const@@@MainFrm.cpp>");
        CFrameWndEx :: AssertValid ();
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::AssertValid() const@@@MainFrm.cpp>");
}
    void CMainFrame :: Dump (CDumpContext & dc) const
    {
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::Dump(CDumpContext & dc) const@@@MainFrm.cpp>");
        CFrameWndEx :: Dump (dc);
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::Dump(CDumpContext & dc) const@@@MainFrm.cpp>");
}
#endif

void CMainFrame :: OnViewCustomize ()
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::OnViewCustomize()@@@MainFrm.cpp>");
    CMFCToolBarsCustomizeDialog * pDlgCust = new CMFCToolBarsCustomizeDialog (this, TRUE);
    pDlgCust -> EnableUserDefinedToolbars ();
    pDlgCust -> Create ();
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnViewCustomize()@@@MainFrm.cpp>");
}
LRESULT CMainFrame :: OnToolbarCreateNew (WPARAM wp, LPARAM lp)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)@@@MainFrm.cpp>");
    LRESULT lres = CFrameWndEx :: OnToolbarCreateNew (wp, lp);
    if (lres == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)@@@MainFrm.cpp>");
        return 0;
    }

    CMFCToolBar * pUserToolbar = (CMFCToolBar *) lres;
    ASSERT_VALID (pUserToolbar);
    BOOL bNameValid;
    CString strCustomize;
    bNameValid = strCustomize.LoadString (IDS_TOOLBAR_CUSTOMIZE);
    ASSERT (bNameValid);
    pUserToolbar -> EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)@@@MainFrm.cpp>");
    return lres;
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnToolbarCreateNew(WPARAM wp, LPARAM lp)@@@MainFrm.cpp>");
}
void CMainFrame :: OnApplicationLook (UINT id)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::OnApplicationLook(UINT id)@@@MainFrm.cpp>");
    CWaitCursor wait;
    theApp.m_nAppLook = id;
    switch (theApp.m_nAppLook) {
    case ID_VIEW_APPLOOK_WIN_2000:
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManager));
        break;
    case ID_VIEW_APPLOOK_OFF_XP:
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerOfficeXP));
        break;
    case ID_VIEW_APPLOOK_WIN_XP:
        CMFCVisualManagerWindows :: m_b3DTabsXPTheme = TRUE;
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerWindows));
        break;
    case ID_VIEW_APPLOOK_OFF_2003:
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerOffice2003));
        CDockingManager :: SetDockingMode (DT_SMART);
        break;
    case ID_VIEW_APPLOOK_VS_2005:
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerVS2005));
        CDockingManager :: SetDockingMode (DT_SMART);
        break;
    case ID_VIEW_APPLOOK_VS_2008:
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerVS2008));
        CDockingManager :: SetDockingMode (DT_SMART);
        break;
    case ID_VIEW_APPLOOK_WINDOWS_7:
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerWindows7));
        CDockingManager :: SetDockingMode (DT_SMART);
        break;
    default:
        switch (theApp.m_nAppLook) {
        case ID_VIEW_APPLOOK_OFF_2007_BLUE:
            CMFCVisualManagerOffice2007 :: SetStyle (CMFCVisualManagerOffice2007 :: Office2007_LunaBlue);
            break;
        case ID_VIEW_APPLOOK_OFF_2007_BLACK:
            CMFCVisualManagerOffice2007 :: SetStyle (CMFCVisualManagerOffice2007 :: Office2007_ObsidianBlack);
            break;
        case ID_VIEW_APPLOOK_OFF_2007_SILVER:
            CMFCVisualManagerOffice2007 :: SetStyle (CMFCVisualManagerOffice2007 :: Office2007_Silver);
            break;
        case ID_VIEW_APPLOOK_OFF_2007_AQUA:
            CMFCVisualManagerOffice2007 :: SetStyle (CMFCVisualManagerOffice2007 :: Office2007_Aqua);
            break;
        }
        CMFCVisualManager :: SetDefaultManager (RUNTIME_CLASS (CMFCVisualManagerOffice2007));
        CDockingManager :: SetDockingMode (DT_SMART);
    }
    m_wndOutput.UpdateFonts ();
    RedrawWindow (nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
    theApp.WriteInt (_T ("ApplicationLook"), theApp.m_nAppLook);
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnApplicationLook(UINT id)@@@MainFrm.cpp>");
}
void CMainFrame :: OnUpdateApplicationLook (CCmdUI * pCmdUI)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::OnUpdateApplicationLook(CCmdUI * pCmdUI)@@@MainFrm.cpp>");
    pCmdUI -> SetRadio (theApp.m_nAppLook == pCmdUI -> m_nID);
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnUpdateApplicationLook(CCmdUI * pCmdUI)@@@MainFrm.cpp>");
}
BOOL CMainFrame :: LoadFrame (UINT nIDResource, DWORD dwDefaultStyle, CWnd * pParentWnd, CCreateContext * pContext)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd * pParentWnd, CCreateContext * pContext)@@@MainFrm.cpp>");
    if (! CFrameWndEx :: LoadFrame (nIDResource, dwDefaultStyle, pParentWnd, pContext))
    {

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd * pParentWnd, CCreateContext * pContext)@@@MainFrm.cpp>");
        return FALSE;
    }

    BOOL bNameValid;
    CString strCustomize;
    bNameValid = strCustomize.LoadString (IDS_TOOLBAR_CUSTOMIZE);
    ASSERT (bNameValid);
    for (int i = 0; i < iMaxUserToolbars; i ++) {
        CMFCToolBar * pUserToolbar = GetUserToolBarByIndex (i);
        if (pUserToolbar != nullptr)
        {
            pUserToolbar -> EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd * pParentWnd, CCreateContext * pContext)@@@MainFrm.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd * pParentWnd, CCreateContext * pContext)@@@MainFrm.cpp>");
}
void CMainFrame :: OnSettingChange (UINT uFlags, LPCTSTR lpszSection)
{
InstrumentLogger::instance()->log_instrument_log("<CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)@@@MainFrm.cpp>");
    CFrameWndEx :: OnSettingChange (uFlags, lpszSection);
    m_wndOutput.UpdateFonts ();
InstrumentLogger::instance()->log_instrument_log("</CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)@@@MainFrm.cpp>");
}