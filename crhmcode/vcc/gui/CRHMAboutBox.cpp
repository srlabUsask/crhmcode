#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "CRHMAboutBox.h"
#include "afxdialogex.h"
#include "../../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (CRHMAboutBox, CDialogEx)
CRHMAboutBox :: CRHMAboutBox (CWnd * pParent): CDialogEx (IDD_ABOUTBOX, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMAboutBox::CRHMAboutBox(CWnd * pParent): CDialogEx (IDD_ABOUTBOX, pParent)@@@CRHMAboutBox.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CRHMAboutBox::CRHMAboutBox(CWnd * pParent): CDialogEx (IDD_ABOUTBOX, pParent)@@@CRHMAboutBox.cpp>");
}
CRHMAboutBox :: ~CRHMAboutBox ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMAboutBox::~CRHMAboutBox()@@@CRHMAboutBox.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CRHMAboutBox::~CRHMAboutBox()@@@CRHMAboutBox.cpp>");
}
void CRHMAboutBox :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<CRHMAboutBox::DoDataExchange(CDataExchange * pDX)@@@CRHMAboutBox.cpp>");
    CDialogEx :: DoDataExchange (pDX);
    DDX_Control (pDX, crhm_version, crhm_version_string);
InstrumentLogger::instance()->log_instrument_log("</CRHMAboutBox::DoDataExchange(CDataExchange * pDX)@@@CRHMAboutBox.cpp>");
}BEGIN_MESSAGE_MAP (CRHMAboutBox, CDialogEx)
    ON_BN_CLICKED (IDOK, & CRHMAboutBox :: OnBnClickedOk)
END_MESSAGE_MAP ()

void CRHMAboutBox :: OnBnClickedOk ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMAboutBox::OnBnClickedOk()@@@CRHMAboutBox.cpp>");
    CDialogEx :: OnOK ();
InstrumentLogger::instance()->log_instrument_log("</CRHMAboutBox::OnBnClickedOk()@@@CRHMAboutBox.cpp>");
}
BOOL CRHMAboutBox :: OnInitDialog ()
{
InstrumentLogger::instance()->log_instrument_log("<CRHMAboutBox::OnInitDialog()@@@CRHMAboutBox.cpp>");
    CDialogEx :: OnInitDialog ();
    CStatic * crhmversion = (CStatic *) GetDlgItem (crhm_version);
    CString cstr (versionstring.c_str ());
    crhmversion -> SetWindowTextW (cstr);

InstrumentLogger::instance()->log_instrument_log("</CRHMAboutBox::OnInitDialog()@@@CRHMAboutBox.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</CRHMAboutBox::OnInitDialog()@@@CRHMAboutBox.cpp>");
}