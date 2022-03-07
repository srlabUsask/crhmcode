#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "ResourceDlg.h"
#include "afxdialogex.h"
#include "../../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (ResourceDlg, CDialogEx)
ResourceDlg :: ResourceDlg (CWnd * pParent): CDialogEx (MAIN_DLG, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<ResourceDlg::ResourceDlg(CWnd * pParent): CDialogEx (MAIN_DLG, pParent)@@@ResourceDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</ResourceDlg::ResourceDlg(CWnd * pParent): CDialogEx (MAIN_DLG, pParent)@@@ResourceDlg.cpp>");
}
ResourceDlg :: ~ResourceDlg ()
{
InstrumentLogger::instance()->log_instrument_log("<ResourceDlg::~ResourceDlg()@@@ResourceDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</ResourceDlg::~ResourceDlg()@@@ResourceDlg.cpp>");
}
void ResourceDlg :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<ResourceDlg::DoDataExchange(CDataExchange * pDX)@@@ResourceDlg.cpp>");
    CDialogEx :: DoDataExchange (pDX);
InstrumentLogger::instance()->log_instrument_log("</ResourceDlg::DoDataExchange(CDataExchange * pDX)@@@ResourceDlg.cpp>");
}BEGIN_MESSAGE_MAP (ResourceDlg, CDialogEx)
END_MESSAGE_MAP ()
