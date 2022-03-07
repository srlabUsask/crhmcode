#include "../stdafx.h"
#include "OutputWnd.h"
#include "../Resource.h"
#include "MainFrm.h"
#include "../../src/core/InstrumentLogger.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE [] = __FILE__;
#endif

COutputWnd :: COutputWnd ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::COutputWnd()@@@OutputWnd.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::COutputWnd()@@@OutputWnd.cpp>");
}
COutputWnd :: ~COutputWnd ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::~COutputWnd()@@@OutputWnd.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::~COutputWnd()@@@OutputWnd.cpp>");
}BEGIN_MESSAGE_MAP (COutputWnd, CDockablePane)
    ON_WM_CREATE ()
    ON_WM_SIZE ()
END_MESSAGE_MAP ()

int COutputWnd :: OnCreate (LPCREATESTRUCT lpCreateStruct)
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@OutputWnd.cpp>");
    if (CDockablePane :: OnCreate (lpCreateStruct) == - 1)
    {

InstrumentLogger::instance()->log_instrument_log("</COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@OutputWnd.cpp>");
        return - 1;
    }

    CRect rectDummy;
    rectDummy.SetRectEmpty ();
    if (! m_wndTabs.Create (CMFCTabCtrl :: STYLE_FLAT, rectDummy, this, 1))
    {
        TRACE0 ("Failed to create output tab window\n");

InstrumentLogger::instance()->log_instrument_log("</COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@OutputWnd.cpp>");
        return - 1;
    }

    const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
    if (! m_wndOutputBuild.Create (dwStyle, rectDummy, & m_wndTabs, 2) || ! m_wndOutputDebug.Create (dwStyle, rectDummy, & m_wndTabs, 3) || ! m_wndOutputFind.Create (dwStyle, rectDummy, & m_wndTabs, 4))
    {
        TRACE0 ("Failed to create output windows\n");

InstrumentLogger::instance()->log_instrument_log("</COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@OutputWnd.cpp>");
        return - 1;
    }

    UpdateFonts ();
    CString strTabName;
    BOOL bNameValid;
    bNameValid = strTabName.LoadString (IDS_BUILD_TAB);
    ASSERT (bNameValid);
    m_wndTabs.AddTab (& m_wndOutputBuild, strTabName, (UINT) 0);
    bNameValid = strTabName.LoadString (IDS_DEBUG_TAB);
    ASSERT (bNameValid);
    m_wndTabs.AddTab (& m_wndOutputDebug, strTabName, (UINT) 1);
    bNameValid = strTabName.LoadString (IDS_FIND_TAB);
    ASSERT (bNameValid);
    m_wndTabs.AddTab (& m_wndOutputFind, strTabName, (UINT) 2);
    FillBuildWindow ();
    FillDebugWindow ();
    FillFindWindow ();

InstrumentLogger::instance()->log_instrument_log("</COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@OutputWnd.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)@@@OutputWnd.cpp>");
}
void COutputWnd :: OnSize (UINT nType, int cx, int cy)
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::OnSize(UINT nType, int cx, int cy)@@@OutputWnd.cpp>");
    CDockablePane :: OnSize (nType, cx, cy);
    m_wndTabs.SetWindowPos (nullptr, - 1, - 1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::OnSize(UINT nType, int cx, int cy)@@@OutputWnd.cpp>");
}
void COutputWnd :: AdjustHorzScroll (CListBox & wndListBox)
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::AdjustHorzScroll(CListBox & wndListBox)@@@OutputWnd.cpp>");
    CClientDC dc (this);
    CFont * pOldFont = dc.SelectObject (& afxGlobalData.fontRegular);
    int cxExtentMax = 0;
    for (int i = 0; i < wndListBox.GetCount (); i ++) {
        CString strItem;
        wndListBox.GetText (i, strItem);
        cxExtentMax = max (cxExtentMax, (int) dc.GetTextExtent (strItem).cx);
    }
    wndListBox.SetHorizontalExtent (cxExtentMax);
    dc.SelectObject (pOldFont);
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::AdjustHorzScroll(CListBox & wndListBox)@@@OutputWnd.cpp>");
}
void COutputWnd :: FillBuildWindow ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::FillBuildWindow()@@@OutputWnd.cpp>");
    m_wndOutputBuild.AddString (_T ("Build output is being displayed here."));
    m_wndOutputBuild.AddString (_T ("The output is being displayed in rows of a list view"));
    m_wndOutputBuild.AddString (_T ("but you can change the way it is displayed as you wish..."));
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::FillBuildWindow()@@@OutputWnd.cpp>");
}
void COutputWnd :: FillDebugWindow ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::FillDebugWindow()@@@OutputWnd.cpp>");
    m_wndOutputDebug.AddString (_T ("Debug output is being displayed here."));
    m_wndOutputDebug.AddString (_T ("The output is being displayed in rows of a list view"));
    m_wndOutputDebug.AddString (_T ("but you can change the way it is displayed as you wish..."));
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::FillDebugWindow()@@@OutputWnd.cpp>");
}
void COutputWnd :: FillFindWindow ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::FillFindWindow()@@@OutputWnd.cpp>");
    m_wndOutputFind.AddString (_T ("Find output is being displayed here."));
    m_wndOutputFind.AddString (_T ("The output is being displayed in rows of a list view"));
    m_wndOutputFind.AddString (_T ("but you can change the way it is displayed as you wish..."));
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::FillFindWindow()@@@OutputWnd.cpp>");
}
void COutputWnd :: UpdateFonts ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputWnd::UpdateFonts()@@@OutputWnd.cpp>");
    m_wndOutputBuild.SetFont (& afxGlobalData.fontRegular);
    m_wndOutputDebug.SetFont (& afxGlobalData.fontRegular);
    m_wndOutputFind.SetFont (& afxGlobalData.fontRegular);
InstrumentLogger::instance()->log_instrument_log("</COutputWnd::UpdateFonts()@@@OutputWnd.cpp>");
}
COutputList :: COutputList ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputList::COutputList()@@@OutputWnd.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COutputList::COutputList()@@@OutputWnd.cpp>");
}
COutputList :: ~COutputList ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputList::~COutputList()@@@OutputWnd.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COutputList::~COutputList()@@@OutputWnd.cpp>");
}BEGIN_MESSAGE_MAP (COutputList, CListBox)
    ON_WM_CONTEXTMENU ()
    ON_COMMAND (ID_EDIT_COPY, OnEditCopy)
    ON_COMMAND (ID_EDIT_CLEAR, OnEditClear)
    ON_COMMAND (ID_VIEW_OUTPUTWND, OnViewOutput)
    ON_WM_WINDOWPOSCHANGING ()
END_MESSAGE_MAP ()

void COutputList :: OnContextMenu (CWnd *, CPoint point)
{
InstrumentLogger::instance()->log_instrument_log("<COutputList::OnContextMenu(CWnd *, CPoint point)@@@OutputWnd.cpp>");
    CMenu menu;
    menu.LoadMenu (IDR_OUTPUT_POPUP);
    CMenu * pSumMenu = menu.GetSubMenu (0);
    if (AfxGetMainWnd () -> IsKindOf (RUNTIME_CLASS (CMDIFrameWndEx)))
    {
        CMFCPopupMenu * pPopupMenu = new CMFCPopupMenu;
        if (! pPopupMenu -> Create (this, point.x, point.y, (HMENU) pSumMenu -> m_hMenu, FALSE, TRUE))
        {

InstrumentLogger::instance()->log_instrument_log("</COutputList::OnContextMenu(CWnd *, CPoint point)@@@OutputWnd.cpp>");
            return;
        }

        ((CMDIFrameWndEx *) AfxGetMainWnd ()) -> OnShowPopupMenu (pPopupMenu);
        UpdateDialogControls (this, FALSE);
    }

    SetFocus ();
InstrumentLogger::instance()->log_instrument_log("</COutputList::OnContextMenu(CWnd *, CPoint point)@@@OutputWnd.cpp>");
}
void COutputList :: OnEditCopy ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputList::OnEditCopy()@@@OutputWnd.cpp>");
    MessageBox (_T ("Copy output"));
InstrumentLogger::instance()->log_instrument_log("</COutputList::OnEditCopy()@@@OutputWnd.cpp>");
}
void COutputList :: OnEditClear ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputList::OnEditClear()@@@OutputWnd.cpp>");
    MessageBox (_T ("Clear output"));
InstrumentLogger::instance()->log_instrument_log("</COutputList::OnEditClear()@@@OutputWnd.cpp>");
}
void COutputList :: OnViewOutput ()
{
InstrumentLogger::instance()->log_instrument_log("<COutputList::OnViewOutput()@@@OutputWnd.cpp>");
    CDockablePane * pParentBar = DYNAMIC_DOWNCAST (CDockablePane, GetOwner ());
    CMDIFrameWndEx * pMainFrame = DYNAMIC_DOWNCAST (CMDIFrameWndEx, GetTopLevelFrame ());
    if (pMainFrame != nullptr && pParentBar != nullptr)
    {
        pMainFrame -> SetFocus ();
        pMainFrame -> ShowPane (pParentBar, FALSE, FALSE, FALSE);
        pMainFrame -> RecalcLayout ();
    }

InstrumentLogger::instance()->log_instrument_log("</COutputList::OnViewOutput()@@@OutputWnd.cpp>");
}