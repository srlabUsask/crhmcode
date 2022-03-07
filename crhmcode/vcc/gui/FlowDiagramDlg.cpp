#include "../stdafx.h"
#include "FlowDiagramDlg.h"
#include "CWebBrowser.h"
#include "MacroEntryDlg.h"
#include <fstream>
#include <time.h>
#include <filesystem>
#include "../../src/core/InstrumentLogger.h"

IMPLEMENT_DYNAMIC (FlowDiagramDlg, CDialogEx)
FlowDiagramDlg :: FlowDiagramDlg (CWnd * pParent): CDialogEx (FlowDiagram_DLG, pParent)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::FlowDiagramDlg(CWnd * pParent): CDialogEx (FlowDiagram_DLG, pParent)@@@FlowDiagramDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::FlowDiagramDlg(CWnd * pParent): CDialogEx (FlowDiagram_DLG, pParent)@@@FlowDiagramDlg.cpp>");
}
FlowDiagramDlg :: ~FlowDiagramDlg ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::~FlowDiagramDlg()@@@FlowDiagramDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::~FlowDiagramDlg()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: DoDataExchange (CDataExchange * pDX)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::DoDataExchange(CDataExchange * pDX)@@@FlowDiagramDlg.cpp>");
    CDialogEx :: DoDataExchange (pDX);
    DDX_Control (pDX, IDC_LIST4, listcontrol);
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::DoDataExchange(CDataExchange * pDX)@@@FlowDiagramDlg.cpp>");
}BEGIN_MESSAGE_MAP (FlowDiagramDlg, CDialogEx)
    ON_BN_CLICKED (IDC_BUTTON1, & FlowDiagramDlg :: OnBnClickedButton1)
    ON_WM_PAINT ()
END_MESSAGE_MAP ()

string FlowDiagramDlg :: GetLineString (int x1, int y1, int x2, int y2)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::GetLineString(int x1, int y1, int x2, int y2)@@@FlowDiagramDlg.cpp>");
    string line = "\nline (" + to_string (x1) + ", " + to_string (y1) + "," + to_string (x2) + "," + to_string (y2) + ");";

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetLineString(int x1, int y1, int x2, int y2)@@@FlowDiagramDlg.cpp>");
    return line;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetLineString(int x1, int y1, int x2, int y2)@@@FlowDiagramDlg.cpp>");
}
string FlowDiagramDlg :: GetRectangleString (int x1, int y1, int x2, int y2)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::GetRectangleString(int x1, int y1, int x2, int y2)@@@FlowDiagramDlg.cpp>");
    string rectangle = "\nrectangle (" + to_string (x1) + "," + to_string (y1) + "," + to_string (x2) + "," + to_string (y2) + ");";

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetRectangleString(int x1, int y1, int x2, int y2)@@@FlowDiagramDlg.cpp>");
    return rectangle;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetRectangleString(int x1, int y1, int x2, int y2)@@@FlowDiagramDlg.cpp>");
}
string FlowDiagramDlg :: GetDrawString (string str, int x1, int y1)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::GetDrawString(string str, int x1, int y1)@@@FlowDiagramDlg.cpp>");
    string drawstring = "\ndrawString ('" + str + "'," + to_string (x1) + "," + to_string (y1) + ");";

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetDrawString(string str, int x1, int y1)@@@FlowDiagramDlg.cpp>");
    return drawstring;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetDrawString(string str, int x1, int y1)@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: LoadAllModules ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::LoadAllModules()@@@FlowDiagramDlg.cpp>");
    TBuild TempB = Global :: BuildFlag;
    Global :: BuildFlag = TBuild :: BUILD;
    for (std :: map < std :: string, ClassModule * > :: iterator modIt = Global :: AllModulesList -> begin (); modIt != Global :: AllModulesList -> end (); modIt ++) {
        ClassModule * thisModule = modIt -> second;
        thisModule -> variation_max = 0;
        unsigned short Temp = thisModule -> variation;
        unsigned short Temp2 = thisModule -> variation_set;
        thisModule -> variation_set = 0;
        thisModule -> variation = 0;
        thisModule -> decl ();
        thisModule -> variation = Temp;
        thisModule -> variation_set = Temp2;
        if (thisModule -> variation > 0)
        {
            thisModule -> hh = (long) (log (thisModule -> variation) / log (2) + 1);
        }

        else
        {
            thisModule -> hh = 0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::LoadAllModules()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: DrawDiagram ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::DrawDiagram()@@@FlowDiagramDlg.cpp>");
    LoadAllModules ();
    FDModule mods [20];
    int mcount = Global :: OurModulesList -> size ();
    GetModulesInputsAndOutputs (mods);
    int ii = 0;
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        ClassModule * thisModule = modIt -> second;
        thisModule -> variation_max = 0;
        thisModule -> decl ();
        mods [ii].count = 0;
        mods [ii].olength = 0;
        GetModuleDetails (thisModule -> Name, thisModule, & mods [ii]);
        mods [ii].modulename = thisModule -> Name;
        mods [ii].FindInputList ();
        mods [ii].FindOutputList ();
        ii ++;
    }
    Global :: BuildFlag = TBuild :: DECL;
    int rectHeight = 0;
    int x = 400;
    int y = 50;
    int xwidth = 50;
    int minheight = 15;
    int textoffset = 12;
    int lastxleft = 0;
    int lastxright = 0;
    int cordx, cordy;
    for (int i = 0; i < mcount; i ++) {
        int ilength = mods [i].ilength;
        int olength = mods [i].olength;
        if (ilength > olength)
        {
            rectHeight = ilength * minheight + minheight;
        }

        else
        {
            rectHeight = olength * minheight + minheight;
        }

        mods [i].x1 = x;
        mods [i].y1 = y;
        mods [i].x2 = x + xwidth;
        mods [i].y2 = mods [i].y1 + rectHeight;
        x = mods [i].x2 + (mods [i].olength + 1) * minheight + minheight + 150;
        y = mods [i].y2 + 50;
    }
    string header = "", line = "";
    ifstream infile ("graphheader.txt");
    while (std :: getline (infile, line)) {
        header += "\n" + line;
    }
    string footer = "";
    for (int i = 0; i < mcount; i ++) {
        footer += GetRectangleString (mods [i].x1, mods [i].y1, mods [i].x2, mods [i].y2);
        footer += GetDrawString (mods [i].modulename, mods [i].x1, mods [i].y2 + 5);
    }
    for (int i = 0; i < mcount; i ++) {
        for (int j = 0; j < mods [i].ilength; j ++) {
            string input = mods [i].inputlist [j];
            int mi = FindPreviousModule (input, i, mods);
            if (mi == - 1)
            {
                cordx = mods [i].x1;
                cordy = mods [i].y1 + (j + 1) * minheight;
                footer += GetLineString (50, cordy, cordx, cordy);
                footer += GetDrawString (input, 50, cordy - textoffset);
            }

            else
            {
                int iserial = mods [mi].GetInputSerial (input);
                int oserial = mods [mi].GetOutputSerial (input);
                if (iserial >= 0)
                {
                    int yy = mods [mi].y1 + (iserial + 1) * minheight;
                    int xx = mods [mi].x1 - (iserial + 1) * minheight;
                    int yy2 = mods [i].y1 + (j + 1) * minheight;
                    footer += GetLineString (xx, yy, xx, yy2);
                    footer += GetLineString (xx, yy2, mods [i].x1, yy2);
                    footer += GetDrawString (input, mods [i].x1 - 50, yy2 - textoffset);
                }

                if (oserial >= 0)
                {
                    int yy = mods [mi].y1 + (oserial + 1) * minheight;
                    int xx = mods [mi].x2 + (oserial + 1) * minheight + 100;
                    int yy2 = mods [i].y1 + (j + 1) * minheight;
                    footer += GetLineString (xx, yy, xx, yy2);
                    footer += GetLineString (xx, yy2, mods [i].x1, yy2);
                    footer += GetDrawString (input, mods [i].x1 - 50, yy2 - textoffset);
                }

            }

        }
        for (int j = 0; j < mods [i].olength; j ++) {
            cordx = mods [i].x2;
            cordy = mods [i].y1 + (j + 1) * minheight;
            footer += GetLineString (cordx, cordy, cordx + 400, cordy);
            footer += GetDrawString (mods [i].outputlist [j], cordx + 20, cordy - textoffset);
        }
    }
    footer += "</script></html>";
    string filecontent;
    filecontent = header + footer;
    std :: ofstream outfile;
    outfile.open ("graph.html", std :: ios_base :: out);
    outfile << filecontent;
    outfile.close ();
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::DrawDiagram()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: FormActivate ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::FormActivate()@@@FlowDiagramDlg.cpp>");
    time_t start, end1, end2;
    time (& start);
    DrawModules ();
    DrawDiagram ();
    time (& end1);
    string filepath = GetCurrentDir () + "/graph.html";
    BSTR b = _com_util :: ConvertStringToBSTR (filepath.c_str ());
    LPWSTR lp = b;
    CWebBrowser * browser;
    browser = (CWebBrowser *) GetDlgItem (IDC_EXPLORER1);
    browser -> Navigate (lp, NULL, NULL, NULL, NULL);
    time (& end2);
    double seconds1 = difftime (end1, start);
    double seconds2 = difftime (end2, start);
    string s1 = to_string (seconds1);
    string s2 = to_string (seconds2);
    CString cs1 (s1.c_str ());
    CString cs2 (s2.c_str ());
    listcontrol.InsertColumn (0, L"Name", LVCFMT_CENTER, 80);
    listcontrol.InsertColumn (1, L"Age", LVCFMT_CENTER, 80);
    listcontrol.InsertColumn (2, L"Address", LVCFMT_CENTER, 80);
    int item = listcontrol.InsertItem (0, L"testname");
    listcontrol.SetItemText (item, 2, L"Mark");
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::FormActivate()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: DrawGrid ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::DrawGrid()@@@FlowDiagramDlg.cpp>");
    Mapstr :: iterator itMap, pos, itMap2;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeO;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeOobs;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeI;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeIobs;
    string S, S1, S2, SS;
    StringGrid1 = new TStringGrid ();
    StringGrid1 -> FixedCols = 0;
    StringGrid1 -> FixedRows = 0;
    StringGrid1 -> ColCount = 1;
    StringGrid1 -> RowCount = LocalModulesList -> size () + 2;
    StringGrid1 -> Cells [0] [0] = "Variable";
    StringGrid1 -> Cells [0] [1] = "Module";
    listcontrol.InsertColumn (0, L"Variable", LVCFMT_CENTER, 80);
    for (size_t ii = 0; ii < LocalModulesList -> size (); ++ ii) {
        StringGrid1 -> Cells [0] [ii + 2] = LocalModulesList -> at (ii).first;
    }
    for (size_t ii = 0; ii < LocalModulesList -> size (); ++ ii) {
        S = LocalModulesList -> at (ii).first;
        rangeO = Global :: Mapdeclvar.equal_range (S);
        rangeOobs = Global :: Mapdeclobs.equal_range (S);
        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            SS = itMap -> second.first;
            for (itMap2 = Global :: Mapreadvar.begin (); itMap2 != Global :: Mapreadvar.end (); ++ itMap2) {
                if (itMap2 -> second.first == SS)
                {
                    break;
                }

            }
            pos = itMap2;
            if (pos == Global :: Mapreadvar.end () && SS [SS.length () - 1] != '#' && StringGrid1 -> ColPos (0, SS) < 0 && Common :: Variation_Decide (ii, itMap -> second.second))
            {
                StringGrid1 -> ColCount = StringGrid1 -> ColCount + 1;
                StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [0] = SS;
                StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [ii + 2] = "D";
                StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [1] = S;
            }

        }
        for (itMap = rangeOobs.first; itMap != rangeOobs.second; itMap ++) {
            SS = itMap -> second.first;
            if (Common :: Variation_Decide (ii, itMap -> second.second))
            {
                StringGrid1 -> ColCount = StringGrid1 -> ColCount + 1;
                StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [0] = SS;
                StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [ii + 2] = "DO";
                StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [1] = S;
            }

        }
    }
    int a = 10;
    for (size_t ii = 0; ii < LocalModulesList -> size (); ++ ii) {
        S = LocalModulesList -> at (ii).first;
        rangeI = Global :: Mapgetvar.equal_range (S);
        rangeIobs = Global :: Mapreadvar.equal_range (S);
        for (itMap = rangeI.first; itMap != rangeI.second; itMap ++) {
            SS = itMap -> second.first;
            if (Common :: Variation_Decide (ii, itMap -> second.second))
            {
                int jj = SS.find (" ");
                S1 = SS.substr (0, jj);
                S2 = SS.substr (jj + 1, SS.length ());
                int cc = StringGrid1 -> ColPos (0, S2);
                int rr = StringGrid1 -> RowPos (0, S);
                if (cc == - 1)
                {
                    string V2;
                    int indx = S2.find ("@");
                    if (indx >= 0)
                    {
                        V2 = S2.substr (0, indx);
                        cc = StringGrid1 -> ColPos (0, V2);
                        if (cc == - 1)
                        {
                            for (int cc2 = 1; cc2 < StringGrid1 -> ColCount; ++ cc2) {
                                string V3 = StringGrid1 -> Cells [cc2] [0].substr (0, StringGrid1 -> Cells [cc2] [0].find ("@"));
                                if (V2 == V3)
                                {
                                    cc = cc2;
                                    break;
                                }

                            }
                        }

                    }

                    else
                    {
                        for (int cc2 = 1; cc2 < StringGrid1 -> ColCount; ++ cc2) {
                            string V3 = StringGrid1 -> Cells [cc2] [0].substr (0, StringGrid1 -> Cells [cc2] [0].find ("@"));
                            if (S2 == V3)
                            {
                                cc = cc2;
                                break;
                            }

                        }
                    }

                }

                if (rr > - 1 && cc > - 1 && S != StringGrid1 -> Cells [cc] [1])
                if (Common :: Variation_Decide (ii, itMap -> second.second))
                {
                    if (S1 == "*")
                    {
                        StringGrid1 -> Cells [cc] [rr] = "*G";
                    }

                    else
                    {
                        StringGrid1 -> Cells [cc] [rr] = "G";
                    }

                }

            }

        }
        rangeI = Global :: Mapputvar.equal_range (S);
        for (itMap = rangeI.first; itMap != rangeI.second; itMap ++) {
            SS = itMap -> second.first;
            if (Common :: Variation_Decide (ii, itMap -> second.second))
            {
                int jj = SS.find (" ");
                S1 = SS.substr (0, jj);
                S2 = SS.substr (jj + 1, SS.length ());
                int cc = StringGrid1 -> ColPos (0, S2);
                int rr = StringGrid1 -> RowPos (0, S);
                if (cc == - 1)
                {
                    if (Common :: Variation_Decide (ii, itMap -> second.second))
                    {
                        string V2;
                        int indx = S2.find ("@");
                        if (indx >= 0)
                        {
                            V2 = S2.substr (0, indx);
                            cc = StringGrid1 -> ColPos (0, V2);
                            if (cc == - 1)
                            {
                                for (int cc2 = 1; cc2 < StringGrid1 -> ColCount; ++ cc2) {
                                    string V3 = StringGrid1 -> Cells [cc2] [0].substr (0, StringGrid1 -> Cells [cc2] [0].find ("@"));
                                    if (V2 == V3)
                                    {
                                        cc = cc2;
                                        break;
                                    }

                                }
                            }

                        }

                    }

                }

                if (rr > - 1 && cc > - 1 && S != StringGrid1 -> Cells [cc] [1])
                {
                    if (S1 == "*")
                    {
                        StringGrid1 -> Cells [cc] [rr] = "*P";
                    }

                    else
                    {
                        StringGrid1 -> Cells [cc] [rr] = "P";
                    }

                }

            }

        }
        for (itMap = rangeIobs.first; itMap != rangeIobs.second; itMap ++) {
            SS = itMap -> second.first;
            for (itMap2 = Global :: Mapdeclobs.begin (); itMap2 != Global :: Mapdeclobs.end (); ++ itMap2) {
                if (itMap2 -> second.first == SS)
                {
                    break;
                }

            }
            pos = itMap2;
            if (pos == Global :: Mapdeclobs.end ())
            {
                continue;
            }

            if (Common :: Variation_Decide (ii, itMap -> second.second))
            {
                S1 = pos -> first;
                S2 = pos -> second.first;
                int cc = MatchDecl_Obs (S, S2);
                if (cc > - 1)
                {
                    continue;
                }

                cc = StringGrid1 -> ColPos (0, S2);
                int rr = StringGrid1 -> RowPos (0, S);
                if (rr > - 1 && cc > - 1)
                {
                    StringGrid1 -> Cells [cc] [rr] = "O";
                }

            }

        }
    }
    int b = 10;
    if (StringGrid1 -> ColCount > 1)
    {
        StringGrid1 -> FixedCols = 1;
    }

    if (StringGrid1 -> RowCount > 2)
    {
        StringGrid1 -> FixedRows = 2;
    }

    for (size_t ii = 0; ii < LocalModulesList -> size (); ++ ii) {
        S = LocalModulesList -> at (ii).first;
        int mm = StringGrid1 -> ColPos (1, S);
        if (mm == - 1)
        if (StringGrid1 -> ColPos (ii + 2, "P") == - 1 && StringGrid1 -> ColPos (ii + 2, "P*") == - 1 || S == "shared")
        {
            int result = IDNO;
            if (result == IDYES || S == "shared")
            {
                StringGrid1 -> DeleteRow (ii + 2);
                LocalModulesList -> erase (LocalModulesList -> begin () + ii);
                ii --;
            }

            else
            {
                S = LocalModulesList -> at (ii).first;
                rangeO = Global :: Mapdeclvar.equal_range (S);
                for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
                    SS = itMap -> second.first;
                    for (itMap2 = Global :: Mapreadvar.begin (); itMap2 != Global :: Mapreadvar.end (); ++ itMap2) {
                        if (itMap2 -> second.first == SS)
                        {
                            break;
                        }

                    }
                    pos = itMap2;
                    if (pos == Global :: Mapreadvar.end ())
                    {
                        if (Common :: Variation_Decide (ii, itMap -> second.second))
                        {
                            StringGrid1 -> ColCount = StringGrid1 -> ColCount + 1;
                            StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [0] = SS;
                            StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [ii + 2] = "D";
                            StringGrid1 -> Cells [StringGrid1 -> ColCount - 1] [1] = S;
                        }

                    }

                }
            }

        }

    }
    int c = 10;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::DrawGrid()@@@FlowDiagramDlg.cpp>");
}
int FlowDiagramDlg :: MatchDecl_Obs (string module, string Obs)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::MatchDecl_Obs(string module, string Obs)@@@FlowDiagramDlg.cpp>");
    int Col;
    for (Col = 2; Col < StringGrid1 -> ColCount; ++ Col)
        if (module == StringGrid1 -> Cells [Col] [1] && Obs == StringGrid1 -> Cells [Col] [0])
        {

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::MatchDecl_Obs(string module, string Obs)@@@FlowDiagramDlg.cpp>");
            return Col;
        }

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::MatchDecl_Obs(string module, string Obs)@@@FlowDiagramDlg.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::MatchDecl_Obs(string module, string Obs)@@@FlowDiagramDlg.cpp>");
}
BOOL FlowDiagramDlg :: OnInitDialog ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::OnInitDialog()@@@FlowDiagramDlg.cpp>");
    CDialogEx :: OnInitDialog ();
    FormActivate ();

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::OnInitDialog()@@@FlowDiagramDlg.cpp>");
    return TRUE;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::OnInitDialog()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: OnBnClickedButton1 ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::OnBnClickedButton1()@@@FlowDiagramDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::OnBnClickedButton1()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: GetModuleDetails (string S, ClassModule * thisModule, FDModule * m)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::GetModuleDetails(string S, ClassModule * thisModule, FDModule * m)@@@FlowDiagramDlg.cpp>");
    Mapstr :: iterator itMap, pos, pos2, itMap2;
    string SS, S1, S2;
    MapVar :: iterator itVar;
    long Variation = 0;
    long Vindx = 0;
    int P;
    SS = S;
    if (P = S.find ("#"), P > - 1)
    {
        Vindx = S [P + 1] - char ('0');
        Variation = (long) pow (2, S [P + 1] - char ('1'));
        S = S.substr (0, S.length () - 2);
    }

    else
    {
        Variation = 0;
    }

    StringGrid2 * StringGrid1;
    StringGrid1 = new StringGrid2 ();
    for (int I = 0; I < StringGrid1 -> ColCount; ++ I)
        for (int J = 0; J < StringGrid1 -> RowCount; ++ J)
            StringGrid1 -> Cells [I] [J] = "";
    StringGrid1 -> ColCount = 6;
    StringGrid1 -> FixedRows = 0;
    StringGrid1 -> RowCount = 1;
    StringGrid1 -> Cells [0] [0] = "Observations";
    StringGrid1 -> Cells [1] [0] = "Modules";
    StringGrid1 -> Cells [2] [0] = "Inputs";
    StringGrid1 -> Cells [3] [0] = "Outputs";
    StringGrid1 -> Cells [4] [0] = "Parameters";
    StringGrid1 -> Cells [5] [0] = "New Observations";
    pair < Mapstr :: iterator, Mapstr :: iterator > range = Global :: Mapreadvar.equal_range (S);
    int ii = 0;
    for (itMap = range.first; itMap != range.second; ++ itMap) {
        SS = (itMap -> second).first;
        if (StringGrid1 -> RowCount < ii + 3)
        {
            StringGrid1 -> RowCount = ii + 3;
        }

        int Indx = StringGrid1 -> Cols [0].find (SS);
        if (Indx == - 1 && Variation_Decide (Variation, (itMap -> second).second))
        {
            StringGrid1 -> Cells [0] [ii + 2] = SS;
            ++ ii;
        }

    }
    range = Global :: Mapputvar.equal_range (S);
    ii = 0;
    for (itMap = range.first; itMap != range.second; ++ itMap) {
        SS = itMap -> second.first;
        int jj = SS.find (" ");
        S1 = SS.substr (0, jj);
        S2 = SS.substr (jj + 1, SS.length () - jj - 1);
        if (S1 != S && Variation_Decide (Variation, (itMap -> second).second))
        {
            if (StringGrid1 -> RowCount < ii + 3)
            {
                StringGrid1 -> RowCount = ii + 3;
            }

            StringGrid1 -> Cells [1] [ii + 2] = S1;
            StringGrid1 -> Cells [2] [ii + 2] = S2;
            ++ ii;
        }

    }
    range = Global :: Mapgetvar.equal_range (S);
    for (itMap = range.first; itMap != range.second; ++ itMap) {
        SS = itMap -> second.first;
        int jj = SS.find (" ");
        S1 = SS.substr (0, jj);
        S2 = SS.substr (jj + 1, SS.length () - jj - 1);
        if (S1 != S && Variation_Decide (Variation, (itMap -> second).second))
        {
            int Indx = StringGrid1 -> Cols [2].find (S2);
            if (Indx == - 1)
            {
                if (StringGrid1 -> RowCount < ii + 3)
                {
                    StringGrid1 -> RowCount = ii + 3;
                }

                StringGrid1 -> Cells [1] [ii + 2] = S1;
                StringGrid1 -> Cells [2] [ii + 2] = S2;
                ++ ii;
            }

        }

    }
    range = Global :: Mapdeclvar.equal_range (S);
    ii = 0;
    for (itMap = range.first; itMap != range.second; ++ itMap) {
        SS = itMap -> second.first;
        for (itMap2 = Global :: Mapreadvar.begin (); itMap2 != Global :: Mapreadvar.end (); ++ itMap2) {
            if (itMap2 -> second.first == SS)
            {
                break;
            }

        }
        pos = itMap2;
        for (itMap2 = Global :: Mapdeclobs.begin (); itMap2 != Global :: Mapdeclobs.end (); ++ itMap2) {
            if (itMap2 -> second.first == SS)
            {
                break;
            }

        }
        pos2 = itMap2;
        if ((pos == Global :: Mapreadvar.end () || Not_Obs (S, SS)) && pos2 == Global :: Mapdeclobs.end ())
        {
            int Indx = StringGrid1 -> Cols [3].find (SS);
            if (Indx == - 1 && Variation_Decide (Variation, (itMap -> second).second) && Visible_Decide ((itMap -> second).second))
            {
                if (StringGrid1 -> RowCount < ii + 3)
                {
                    StringGrid1 -> RowCount = ii + 3;
                }

                StringGrid1 -> Cells [3] [ii + 2] = SS;
                ++ ii;
            }

        }

    }
    range = Global :: Mapdeclpar.equal_range (S);
    ii = 0;
    for (itMap = range.first; itMap != range.second; ++ itMap) {
        if (Variation_Decide (Variation, (itMap -> second).second) && Visible_Decide ((itMap -> second).second))
        {
            SS = itMap -> second.first;
            if (StringGrid1 -> RowCount < ii + 3)
            {
                StringGrid1 -> RowCount = ii + 3;
            }

            StringGrid1 -> Cells [4] [ii + 2] = SS;
            ++ ii;
        }

    }
    range = Global :: Mapdeclobs.equal_range (S);
    ii = 0;
    for (itMap = range.first; itMap != range.second; ++ itMap) {
        if (Variation_Decide (Variation, (itMap -> second).second) && Visible_Decide ((itMap -> second).second))
        {
            SS = itMap -> second.first;
            if (StringGrid1 -> RowCount < ii + 3)
            {
                StringGrid1 -> RowCount = ii + 3;
            }

            StringGrid1 -> Cells [5] [ii + 2] = SS;
            ++ ii;
        }

    }
    if (StringGrid1 -> RowCount > 1)
    {
        StringGrid1 -> FixedRows = 1;
    }

    while (listcontrol.DeleteColumn (0));
    for (int i = 1; i < StringGrid1 -> RowCount; i ++) {
        m -> observations [i - 1] = StringGrid1 -> Cells [0] [i];
        m -> modules [i - 1] = StringGrid1 -> Cells [1] [i];
        m -> inputs [i - 1] = StringGrid1 -> Cells [2] [i];
        m -> outputs [i - 1] = StringGrid1 -> Cells [3] [i];
        m -> parameters [i - 1] = StringGrid1 -> Cells [4] [i];
        m -> newobservations [i - 1] = StringGrid1 -> Cells [5] [i];
        m -> count ++;
    }
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetModuleDetails(string S, ClassModule * thisModule, FDModule * m)@@@FlowDiagramDlg.cpp>");
}
bool FlowDiagramDlg :: Variation_Decide (int Variation_set, long Variation)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::Variation_Decide(int Variation_set, long Variation)@@@FlowDiagramDlg.cpp>");
    VandP V;
    V.Set (Variation);
    long variations = V.GetV ();
    if ((variations & 2048) != 0 && Variation_set == 0 || (variations & 4096) != 0 || (variations == 0) || (variations & Variation_set) != 0)
    {

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Variation_Decide(int Variation_set, long Variation)@@@FlowDiagramDlg.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Variation_Decide(int Variation_set, long Variation)@@@FlowDiagramDlg.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Variation_Decide(int Variation_set, long Variation)@@@FlowDiagramDlg.cpp>");
}
bool FlowDiagramDlg :: Visible_Decide (long Variation)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::Visible_Decide(long Variation)@@@FlowDiagramDlg.cpp>");
    VandP V;
    V.Set (Variation);
    long Visible = V.GetP ();

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Visible_Decide(long Variation)@@@FlowDiagramDlg.cpp>");
    return Visible == 1;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Visible_Decide(long Variation)@@@FlowDiagramDlg.cpp>");
}
bool FlowDiagramDlg :: Not_Obs (string Mod, string Var)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::Not_Obs(string Mod, string Var)@@@FlowDiagramDlg.cpp>");
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeIobs = Global :: Mapreadvar.equal_range (Mod);
    for (Mapstr :: iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++ itMap)
        if (Var == itMap -> second.first)
        {

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Not_Obs(string Mod, string Var)@@@FlowDiagramDlg.cpp>");
            return false;
        }

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Not_Obs(string Mod, string Var)@@@FlowDiagramDlg.cpp>");
    return true;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::Not_Obs(string Mod, string Var)@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: OnPaint ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::OnPaint()@@@FlowDiagramDlg.cpp>");
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::OnPaint()@@@FlowDiagramDlg.cpp>");
}
int FlowDiagramDlg :: FindPreviousModule (string input, int mcount, FDModule mods [])
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::FindPreviousModule(string input, int mcount, FDModule mods [])@@@FlowDiagramDlg.cpp>");
    for (int i = 0; i < mcount; i ++) {
        for (int j = 0; j < mods [i].ilength; j ++) {
            if (input == mods [i].inputlist [j])
            {

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::FindPreviousModule(string input, int mcount, FDModule mods [])@@@FlowDiagramDlg.cpp>");
                return i;
            }

        }
        for (int j = 0; j < mods [i].olength; j ++) {
            if (input == mods [i].outputlist [j])
            {

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::FindPreviousModule(string input, int mcount, FDModule mods [])@@@FlowDiagramDlg.cpp>");
                return i;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::FindPreviousModule(string input, int mcount, FDModule mods [])@@@FlowDiagramDlg.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::FindPreviousModule(string input, int mcount, FDModule mods [])@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: DrawModules ()
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::DrawModules()@@@FlowDiagramDlg.cpp>");
    Mapstr :: iterator itMap;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeO;
    string S, SS;
    std :: vector < std :: string > * ModList = new std :: vector < std :: string > ();
    std :: vector < std :: pair < std :: string, int >> * InputCnt = new std :: vector < std :: pair < std :: string, int >> ();
    LocalModulesList = new std :: vector < std :: pair < std :: string, ClassModule * >> ();
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        LocalModulesList -> push_back (std :: pair < std :: string, ClassModule * > (modIt -> first, modIt -> second));
    }
    Box Boxes [1000];
    bool DisplyPar = true;
    string inputs [50] [100];
    int counts [50];
    for (size_t ii = 0; LocalModulesList -> size () > ii; ++ ii) {
        S = LocalModulesList -> at (ii).first;
        counts [ii] = 0;
        Mapstr :: iterator pos, End;
        if (DisplyPar)
        {
            Boxes [ii].ObsCnt = Global :: Mapdeclpar.count (S);
            rangeO = Global :: Mapdeclpar.equal_range (S);
            End = Global :: Mapdeclpar.end ();
        }

        else
        {
            Boxes [ii].ObsCnt = Global :: Mapreadvar.count (S);
            rangeO = Global :: Mapreadvar.equal_range (S);
            End = Global :: Mapreadvar.end ();
        }

        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            inputs [ii] [counts [ii]] = SS;
            counts [ii] ++;
            SS = itMap -> second.first;
            if (Variation_Decide (ii, itMap -> second.second))
            {
                int Indx = - 1;
                for (size_t it = 0; it < InputCnt -> size (); it ++) {
                    if (InputCnt -> at (it).first == SS)
                    {
                        Indx = it;
                        break;
                    }

                }
                if (Indx == - 1)
                {
                    InputCnt -> push_back (std :: pair < std :: string, int > (SS, - 1));
                }

                else
                {
                    int InCnt = InputCnt -> at (Indx).second;
                    if (InCnt > 0)
                    {
                        InputCnt -> at (Indx).second = - 2;
                    }

                }

            }

        }
        for (size_t ii = 0; ii < InputCnt -> size (); ++ ii) {
            InputCnt -> at (ii).second = abs (InputCnt -> at (ii).second);
        }
    }
    for (size_t ii = 0; LocalModulesList -> size () > ii; ++ ii) {
        S = LocalModulesList -> at (ii).first;
        Mapstr :: iterator pos, End;
        if (DisplyPar)
        {
            Boxes [ii].ObsCnt = Global :: Mapdeclpar.count (S);
            rangeO = Global :: Mapdeclpar.equal_range (S);
            End = Global :: Mapdeclpar.end ();
        }

        else
        {
            Boxes [ii].ObsCnt = Global :: Mapreadvar.count (S);
            rangeO = Global :: Mapreadvar.equal_range (S);
            End = Global :: Mapreadvar.end ();
        }

        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            SS = itMap -> second.first;
            int Indx = - 1;
            for (size_t it = 0; it < InputCnt -> size (); it ++) {
                if (InputCnt -> at (it).first == SS)
                {
                    Indx = it;
                    break;
                }

            }
            if (Indx > - 1)
            {
                int InCnt = InputCnt -> at (Indx).second;
                if (InCnt > 1)
                {
                    ++ Boxes [ii].ObsCntX;
                    InputCnt -> at (Indx).second = - 2;
                }

            }

        }
        for (size_t ii = 0; ii < InputCnt -> size (); ++ ii) {
            InputCnt -> at (ii).second = abs (InputCnt -> at (ii).second);
        }
    }
    for (size_t ii = 0; LocalModulesList -> size () > ii; ++ ii) {
        S = LocalModulesList -> at (ii).first;
        Mapstr :: iterator pos, End;
        if (DisplyPar)
        {
            Boxes [ii].ObsCnt = Global :: Mapdeclpar.count (S);
            rangeO = Global :: Mapdeclpar.equal_range (S);
            End = Global :: Mapdeclpar.end ();
        }

        else
        {
            Boxes [ii].ObsCnt = Global :: Mapreadvar.count (S);
            rangeO = Global :: Mapreadvar.equal_range (S);
            End = Global :: Mapreadvar.end ();
        }

        int jj = 0;
        int kk = 0;
        ModList -> clear ();
        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            SS = itMap -> second.first;
            if (! Variation_Decide (ii, itMap -> second.second))
            {
                continue;
            }

            int indexOfSS = - 1;
            for (size_t it = 0; it < ModList -> size (); it ++) {
                if (ModList -> at (it) == SS)
                {
                    indexOfSS = it;
                    break;
                }

            }
            if (indexOfSS > - 1)
            {
                continue;
            }

            ModList -> push_back (SS);
            int Indx = - 1;
            for (size_t it = 0; it < InputCnt -> size (); it ++) {
                if (InputCnt -> at (it).first == SS)
                {
                    Indx = it;
                    break;
                }

            }
            kk = 0;
            if (InputCnt -> at (Indx).second == 2)
            {
                ++ kk;
            }

            ++ jj;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::DrawModules()@@@FlowDiagramDlg.cpp>");
}
void FlowDiagramDlg :: GetModulesInputsAndOutputs (FDModule * mods)
{
InstrumentLogger::instance()->log_instrument_log("<FlowDiagramDlg::GetModulesInputsAndOutputs(FDModule * mods)@@@FlowDiagramDlg.cpp>");
    Mapstr :: iterator itMap;
    pair < Mapstr :: iterator, Mapstr :: iterator > rangeO;
    string S, SS;
    std :: vector < std :: pair < std :: string, int >> * List = new std :: vector < std :: pair < std :: string, int >> ();
    std :: vector < std :: string > * ModList = new std :: vector < std :: string > ();
    std :: vector < std :: pair < std :: string, int >> * InputCnt = new std :: vector < std :: pair < std :: string, int >> ();
    LocalModulesList = new std :: vector < std :: pair < std :: string, ClassModule * >> ();
    for (std :: list < std :: pair < std :: string, ClassModule * >> :: iterator modIt = Global :: OurModulesList -> begin (); modIt != Global :: OurModulesList -> end (); modIt ++) {
        LocalModulesList -> push_back (std :: pair < std :: string, ClassModule * > (modIt -> first, modIt -> second));
    }
    Box Boxes [1000];
    bool DisplyPar = true;
    string inputs [50] [100];
    int counts [50];
    for (size_t ii = 0; LocalModulesList -> size () > ii; ++ ii) {
        S = LocalModulesList -> at (ii).first;
        counts [ii] = 0;
        Mapstr :: iterator pos, End;
        if (DisplyPar)
        {
            Boxes [ii].ObsCnt = Global :: Mapdeclpar.count (S);
            rangeO = Global :: Mapdeclpar.equal_range (S);
            End = Global :: Mapdeclpar.end ();
        }

        else
        {
            Boxes [ii].ObsCnt = Global :: Mapreadvar.count (S);
            rangeO = Global :: Mapreadvar.equal_range (S);
            End = Global :: Mapreadvar.end ();
        }

        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            inputs [ii] [counts [ii]] = SS;
            counts [ii] ++;
            SS = itMap -> second.first;
            if (Variation_Decide (ii, itMap -> second.second))
            {
                int Indx = - 1;
                for (size_t it = 0; it < InputCnt -> size (); it ++) {
                    if (InputCnt -> at (it).first == SS)
                    {
                        Indx = it;
                        break;
                    }

                }
                if (Indx == - 1)
                {
                    InputCnt -> push_back (std :: pair < std :: string, int > (SS, - 1));
                }

                else
                {
                    int InCnt = InputCnt -> at (Indx).second;
                    if (InCnt > 0)
                    {
                        InputCnt -> at (Indx).second = - 2;
                    }

                }

            }

        }
        for (size_t ii = 0; ii < InputCnt -> size (); ++ ii) {
            InputCnt -> at (ii).second = abs (InputCnt -> at (ii).second);
        }
    }
    for (size_t ii = 0; LocalModulesList -> size () > ii; ++ ii) {
        S = LocalModulesList -> at (ii).first;
        Mapstr :: iterator pos, End;
        if (DisplyPar)
        {
            Boxes [ii].ObsCnt = Global :: Mapdeclpar.count (S);
            rangeO = Global :: Mapdeclpar.equal_range (S);
            End = Global :: Mapdeclpar.end ();
        }

        else
        {
            Boxes [ii].ObsCnt = Global :: Mapreadvar.count (S);
            rangeO = Global :: Mapreadvar.equal_range (S);
            End = Global :: Mapreadvar.end ();
        }

        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            SS = itMap -> second.first;
            int Indx = - 1;
            for (size_t it = 0; it < InputCnt -> size (); it ++) {
                if (InputCnt -> at (it).first == SS)
                {
                    Indx = it;
                    break;
                }

            }
            if (Indx > - 1)
            {
                int InCnt = InputCnt -> at (Indx).second;
                if (InCnt > 1)
                {
                    ++ Boxes [ii].ObsCntX;
                    InputCnt -> at (Indx).second = - 2;
                }

            }

        }
        for (size_t ii = 0; ii < InputCnt -> size (); ++ ii) {
            InputCnt -> at (ii).second = abs (InputCnt -> at (ii).second);
        }
    }
    for (size_t ii = 0; LocalModulesList -> size () > ii; ++ ii) {
        S = LocalModulesList -> at (ii).first;
        Mapstr :: iterator pos, End;
        if (DisplyPar)
        {
            Boxes [ii].ObsCnt = Global :: Mapdeclpar.count (S);
            rangeO = Global :: Mapdeclpar.equal_range (S);
            End = Global :: Mapdeclpar.end ();
        }

        else
        {
            Boxes [ii].ObsCnt = Global :: Mapreadvar.count (S);
            rangeO = Global :: Mapreadvar.equal_range (S);
            End = Global :: Mapreadvar.end ();
        }

        int jj = 0;
        int kk = 0;
        ModList -> clear ();
        for (itMap = rangeO.first; itMap != rangeO.second; itMap ++) {
            SS = itMap -> second.first;
            if (! Variation_Decide (ii, itMap -> second.second))
            {
                continue;
            }

            int indxOfSS = - 1;
            for (size_t it = 0; it < ModList -> size (); it ++) {
                if (ModList -> at (it) == SS)
                {
                    indxOfSS = it;
                    break;
                }

            }
            if (indxOfSS > - 1)
            {
                continue;
            }

            ModList -> push_back (SS);
            int Indx = - 1;
            for (size_t it = 0; it < InputCnt -> size (); it ++) {
                if (InputCnt -> at (it).first == SS)
                {
                    Indx = it;
                    break;
                }

            }
            kk = 0;
            if (InputCnt -> at (Indx).second == 2)
            {
                ++ kk;
            }

            ++ jj;
            Indx = - 1;
            for (size_t it = 0; it < List -> size (); it ++) {
                if (List -> at (it).first == SS)
                {
                    Indx = it;
                    break;
                }

            }
            if (Indx == - 1)
            {
                ++ Boxes [ii].PadjX;
                List -> push_back (std :: pair < std :: string, int > (SS, NULL));
            }

            else
            {
                ModandVar XY;
                XY.both = List -> at (Indx).second;
                List -> at (Indx).second = XY.both;
            }

        }
        mods [ii].modulename = S;
        for (size_t i = 0; i < ModList -> size (); i ++) {
            mods [ii].inputlist [i] = ModList -> at (i);
        }
        mods [ii].ilength = ModList -> size ();
    }
InstrumentLogger::instance()->log_instrument_log("</FlowDiagramDlg::GetModulesInputsAndOutputs(FDModule * mods)@@@FlowDiagramDlg.cpp>");
}