#include "../stdafx.h"
#include "CRHM_GUI.h"
#include "COptions.h"
#include "afxdialogex.h"
#include "../tchart/CTitles.h"
#include "../tchart/CAspect.h"
#include "../tchart/CLegend.h"
#include "../tchart/CSeries.h"
#include "../tchart/CColorGridSeries.h"
#include "../tchart/CPen0.h"
#include <tchar.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "../../src/core/InstrumentLogger.h"

using namespace std;
struct points {

    int add (CSeries chart_series, const wchar_t * point_x, double point_y)
    {
InstrumentLogger::instance()->log_instrument_log("<add(CSeries chart_series, const wchar_t * point_x, double point_y)@@@COptions.cpp>");
        chart_series.Add (point_y, point_x, 1);

InstrumentLogger::instance()->log_instrument_log("</add(CSeries chart_series, const wchar_t * point_x, double point_y)@@@COptions.cpp>");
        return 0;
InstrumentLogger::instance()->log_instrument_log("</add(CSeries chart_series, const wchar_t * point_x, double point_y)@@@COptions.cpp>");
}} chart1;

IMPLEMENT_DYNAMIC (COptions, CDialogEx)
COptions :: COptions (CWnd * pParent): CDialogEx (MAIN_DLG, pParent), mChart1 ()
{
InstrumentLogger::instance()->log_instrument_log("<COptions::COptions(CWnd * pParent): CDialogEx (MAIN_DLG, pParent), mChart1 ()@@@COptions.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COptions::COptions(CWnd * pParent): CDialogEx (MAIN_DLG, pParent), mChart1 ()@@@COptions.cpp>");
}
COptions :: ~COptions ()
{
InstrumentLogger::instance()->log_instrument_log("<COptions::~COptions()@@@COptions.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COptions::~COptions()@@@COptions.cpp>");
}
void COptions :: initChart ()
{
InstrumentLogger::instance()->log_instrument_log("<COptions::initChart()@@@COptions.cpp>");
InstrumentLogger::instance()->log_instrument_log("</COptions::initChart()@@@COptions.cpp>");
}BEGIN_MESSAGE_MAP (COptions, CDialogEx)
    ON_COMMAND (ID_FILE_OPEN, & COptions :: OnFileOpen)
END_MESSAGE_MAP ()

void COptions :: OnFileOpen ()
{
InstrumentLogger::instance()->log_instrument_log("<COptions::OnFileOpen()@@@COptions.cpp>");
    AfxMessageBox (_T ("message test"));
InstrumentLogger::instance()->log_instrument_log("</COptions::OnFileOpen()@@@COptions.cpp>");
}