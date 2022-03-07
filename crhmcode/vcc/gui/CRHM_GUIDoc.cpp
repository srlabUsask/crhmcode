#include "../stdafx.h"
#include "../../src/core/InstrumentLogger.h"

#ifndef SHARED_HANDLERS
    #include "CRHM_GUI.h"
#endif

#include "CRHM_GUIDoc.h"
#include <propkey.h>

#ifdef _DEBUG
    #define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE (CCRHMGUIDoc, CDocument) BEGIN_MESSAGE_MAP (CCRHMGUIDoc, CDocument)
END_MESSAGE_MAP ()

CCRHMGUIDoc :: CCRHMGUIDoc ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::CCRHMGUIDoc()@@@CRHM_GUIDoc.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::CCRHMGUIDoc()@@@CRHM_GUIDoc.cpp>");
}
CCRHMGUIDoc :: ~CCRHMGUIDoc ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::~CCRHMGUIDoc()@@@CRHM_GUIDoc.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::~CCRHMGUIDoc()@@@CRHM_GUIDoc.cpp>");
}
BOOL CCRHMGUIDoc :: OnNewDocument ()
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::OnNewDocument()@@@CRHM_GUIDoc.cpp>");
    if (! CDocument :: OnNewDocument ())
    {

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::OnNewDocument()@@@CRHM_GUIDoc.cpp>");
        return FALSE;
    }

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::OnNewDocument()@@@CRHM_GUIDoc.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::OnNewDocument()@@@CRHM_GUIDoc.cpp>");
}
void CCRHMGUIDoc :: Serialize (CArchive & ar)
{
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::Serialize(CArchive & ar)@@@CRHM_GUIDoc.cpp>");
    if (ar.IsStoring ())
    {
    }

    else
    {
    }

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::Serialize(CArchive & ar)@@@CRHM_GUIDoc.cpp>");
}
#ifdef SHARED_HANDLERS

    void CCRHMGUIDoc :: OnDrawThumbnail (CDC & dc, LPRECT lprcBounds)
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::OnDrawThumbnail(CDC & dc, LPRECT lprcBounds)@@@CRHM_GUIDoc.cpp>");
        dc.FillSolidRect (lprcBounds, RGB (255, 255, 255));
        CString strText = _T ("TODO: implement thumbnail drawing here");
        LOGFONT lf;
        CFont * pDefaultGUIFont = CFont :: FromHandle ((HFONT) GetStockObject (DEFAULT_GUI_FONT));
        pDefaultGUIFont -> GetLogFont (& lf);
        lf.lfHeight = 36;
        CFont fontDraw;
        fontDraw.CreateFontIndirect (& lf);
        CFont * pOldFont = dc.SelectObject (& fontDraw);
        dc.DrawText (strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
        dc.SelectObject (pOldFont);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::OnDrawThumbnail(CDC & dc, LPRECT lprcBounds)@@@CRHM_GUIDoc.cpp>");
}
    void CCRHMGUIDoc :: InitializeSearchContent ()
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::InitializeSearchContent()@@@CRHM_GUIDoc.cpp>");
        CString strSearchContent;
        SetSearchContent (strSearchContent);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::InitializeSearchContent()@@@CRHM_GUIDoc.cpp>");
}
    void CCRHMGUIDoc :: SetSearchContent (const CString & value)
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::SetSearchContent(const CString & value)@@@CRHM_GUIDoc.cpp>");
        if (value.IsEmpty ())
        {
            RemoveChunk (PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
        }

        else
        {
            CMFCFilterChunkValueImpl * pChunk = nullptr;
            ATLTRY (pChunk = new CMFCFilterChunkValueImpl);
            if (pChunk != nullptr)
            {
                pChunk -> SetTextValue (PKEY_Search_Contents, value, CHUNK_TEXT);
                SetChunkValue (pChunk);
            }

        }

InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::SetSearchContent(const CString & value)@@@CRHM_GUIDoc.cpp>");
}
#endif

#ifdef _DEBUG

    void CCRHMGUIDoc :: AssertValid () const
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::AssertValid() const@@@CRHM_GUIDoc.cpp>");
        CDocument :: AssertValid ();
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::AssertValid() const@@@CRHM_GUIDoc.cpp>");
}
    void CCRHMGUIDoc :: Dump (CDumpContext & dc) const
    {
InstrumentLogger::instance()->log_instrument_log("<CCRHMGUIDoc::Dump(CDumpContext & dc) const@@@CRHM_GUIDoc.cpp>");
        CDocument :: Dump (dc);
InstrumentLogger::instance()->log_instrument_log("</CCRHMGUIDoc::Dump(CDumpContext & dc) const@@@CRHM_GUIDoc.cpp>");
}
#endif

