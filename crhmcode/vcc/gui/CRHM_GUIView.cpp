#include "../stdafx.h"
#include "../../src/core/InstrumentLogger.h"

#ifndef SHARED_HANDLERS
    #include "CRHM_GUI.h"
#endif

#include "CRHM_GUIView.h"
#include "../../src/core/CRHMmain.h"

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE (CCRHMGUIView, CView) BEGIN_MESSAGE_MAP (CCRHMGUIView, CView)
    ON_COMMAND (ID_FILE_PRINT, & CView :: OnFilePrint)
    ON_COMMAND (ID_FILE_PRINT_DIRECT, & CView :: OnFilePrint)
    ON_COMMAND (ID_FILE_PRINT_PREVIEW, & CCRHMGUIView :: OnFilePrintPreview)
    ON_WM_CONTEXTMENU ()
    ON_WM_RBUTTONUP ()
    ON_COMMAND (ID_DIALOG_SHOW, & CCRHMGUIView :: OnDialogShow)
    ON_COMMAND (ID_EXPORT, & CCRHMGUIView :: OnExport)
    ON_COMMAND (ID_PARAMETERS, & CCRHMGUIView :: OnParameters)
    ON_COMMAND (ID_BUILD_CONSTRUCT, & CCRHMGUIView :: OnBuildConstruct)
    ON_COMMAND (ID_FILE_SAVE_AS, & CCRHMGUIView :: OnFileSaveAs)
    ON_COMMAND (ID_FILE_OPEN, & CCRHMGUIView :: OnFileOpen)
END_MESSAGE_MAP ()

CCRHMGUIView :: CCRHMGUIView ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::CCRHMGUIView()@@@CRHM_GUIView.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::CCRHMGUIView()@@@CRHM_GUIView.cpp>");
}
CCRHMGUIView :: ~CCRHMGUIView ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::~CCRHMGUIView()@@@CRHM_GUIView.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::~CCRHMGUIView()@@@CRHM_GUIView.cpp>");
}
BOOL CCRHMGUIView :: PreCreateWindow (CREATESTRUCT & cs)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::PreCreateWindow(CREATESTRUCT & cs)@@@CRHM_GUIView.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::PreCreateWindow(CREATESTRUCT & cs)@@@CRHM_GUIView.cpp>");
    return CView :: PreCreateWindow (cs);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::PreCreateWindow(CREATESTRUCT & cs)@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnDraw (CDC *)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnDraw(CDC *)@@@CRHM_GUIView.cpp>");
    CCRHMGUIDoc * pDoc = GetDocument ();
    ASSERT_VALID (pDoc);
    if (! pDoc)
    {

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnDraw(CDC *)@@@CRHM_GUIView.cpp>");
        return;
    }

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnDraw(CDC *)@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnFilePrintPreview ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnFilePrintPreview()@@@CRHM_GUIView.cpp>");
    CReport dlgReport;
    dlgReport.DoModal ();

    #ifndef SHARED_HANDLERS
        AFXPrintPreview (this);
    #endif

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnFilePrintPreview()@@@CRHM_GUIView.cpp>");
}
BOOL CCRHMGUIView :: OnPreparePrinting (CPrintInfo * pInfo)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnPreparePrinting(CPrintInfo * pInfo)@@@CRHM_GUIView.cpp>");

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnPreparePrinting(CPrintInfo * pInfo)@@@CRHM_GUIView.cpp>");
    return DoPreparePrinting (pInfo);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnPreparePrinting(CPrintInfo * pInfo)@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnBeginPrinting (CDC *, CPrintInfo *)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnBeginPrinting(CDC *, CPrintInfo *)@@@CRHM_GUIView.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnBeginPrinting(CDC *, CPrintInfo *)@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnEndPrinting (CDC *, CPrintInfo *)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnEndPrinting(CDC *, CPrintInfo *)@@@CRHM_GUIView.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnEndPrinting(CDC *, CPrintInfo *)@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnRButtonUp (UINT, CPoint point)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnRButtonUp(UINT, CPoint point)@@@CRHM_GUIView.cpp>");
    ClientToScreen (& point);
    OnContextMenu (this, point);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnRButtonUp(UINT, CPoint point)@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnContextMenu (CWnd *, CPoint point)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnContextMenu(CWnd *, CPoint point)@@@CRHM_GUIView.cpp>");

    #ifndef SHARED_HANDLERS
        theApp.GetContextMenuManager () -> ShowPopupMenu (IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
    #endif

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnContextMenu(CWnd *, CPoint point)@@@CRHM_GUIView.cpp>");
}
#ifdef _DEBUG

    void CCRHMGUIView :: AssertValid () const
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::AssertValid() const@@@CRHM_GUIView.cpp>");
        CView :: AssertValid ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::AssertValid() const@@@CRHM_GUIView.cpp>");
}
    void CCRHMGUIView :: Dump (CDumpContext & dc) const
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::Dump(CDumpContext & dc) const@@@CRHM_GUIView.cpp>");
        CView :: Dump (dc);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::Dump(CDumpContext & dc) const@@@CRHM_GUIView.cpp>");
}
    CCRHMGUIDoc * CCRHMGUIView :: GetDocument () const
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::GetDocument() const@@@CRHM_GUIView.cpp>");
        ASSERT (m_pDocument -> IsKindOf (RUNTIME_CLASS (CCRHMGUIDoc)));

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::GetDocument() const@@@CRHM_GUIView.cpp>");
        return (CCRHMGUIDoc *) m_pDocument;
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::GetDocument() const@@@CRHM_GUIView.cpp>");
}
#endif

void CCRHMGUIView :: OnDialogShow ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnDialogShow()@@@CRHM_GUIView.cpp>");
    COptions dlgOptions;
    dlgOptions.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnDialogShow()@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnExport ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnExport()@@@CRHM_GUIView.cpp>");
    CExport dlgExport;
    dlgExport.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnExport()@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnParameters ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnParameters()@@@CRHM_GUIView.cpp>");
    CParameters dlgParameters;
    dlgParameters.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnParameters()@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnBuildConstruct ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnBuildConstruct()@@@CRHM_GUIView.cpp>");
    CConstruct dlgConstruct;
    dlgConstruct.DoModal ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnBuildConstruct()@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnFileSaveAs ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnFileSaveAs()@@@CRHM_GUIView.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnFileSaveAs()@@@CRHM_GUIView.cpp>");
}
void CCRHMGUIView :: OnFileOpen ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIView::OnFileOpen()@@@CRHM_GUIView.cpp>");
    AfxMessageBox (_T ("test"));
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIView::OnFileOpen()@@@CRHM_GUIView.cpp>");
}