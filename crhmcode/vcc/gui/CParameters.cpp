#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "CParameters.h"
#include "afxdialogex.h"
#include "../../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (CParameters, CDialog)
CParameters :: CParameters (CWnd * pParent): CDialog (PARAMETERS_DLG, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<CParameters::CParameters(CWnd * pParent): CDialog (PARAMETERS_DLG, pParent)@@@CParameters.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CParameters::CParameters(CWnd * pParent): CDialog (PARAMETERS_DLG, pParent)@@@CParameters.cpp>");
}
CParameters :: ~CParameters ()
{
InstrumentLogger::instance()->log_instrument_log("<CParameters::~CParameters()@@@CParameters.cpp>");
InstrumentLogger::instance()->log_instrument_log("</CParameters::~CParameters()@@@CParameters.cpp>");
}
void CParameters :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<CParameters::DoDataExchange(CDataExchange * pDX)@@@CParameters.cpp>");
    CDialog :: DoDataExchange (pDX);
InstrumentLogger::instance()->log_instrument_log("</CParameters::DoDataExchange(CDataExchange * pDX)@@@CParameters.cpp>");
}BEGIN_MESSAGE_MAP (CParameters, CDialog)
END_MESSAGE_MAP ()
