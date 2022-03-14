#include "Common.h"
#include "../CRHMmain/CRHMLogger.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include "../InstrumentLogger.h"

using namespace std;
double Common :: estar (double t)
{
InstrumentLogger::instance()->log_instrument_log("<Common::estar(double t)@@@Common.cpp>");
    if (t > 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</Common::estar(double t)@@@Common.cpp>");
        return 0.611 * exp (17.27 * t / (t + 237.3));
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</Common::estar(double t)@@@Common.cpp>");
        return 0.611 * exp (21.88 * t / (t + 265.5));
    }

InstrumentLogger::instance()->log_instrument_log("</Common::estar(double t)@@@Common.cpp>");
}
double Common :: Qs (double P, double tc)
{
InstrumentLogger::instance()->log_instrument_log("<Common::Qs(double P, double tc)@@@Common.cpp>");
    double es;
    if (tc >= 0)
    {
        es = 0.611213 * exp (17.5043 * tc / (241.3 + tc));
    }

    else
    {
        es = 0.611213 * exp (22.4422 * tc / (272.186 + tc));
    }

InstrumentLogger::instance()->log_instrument_log("</Common::Qs(double P, double tc)@@@Common.cpp>");
    return (0.622 * es / P);
InstrumentLogger::instance()->log_instrument_log("</Common::Qs(double P, double tc)@@@Common.cpp>");
}
double Common :: Qswater (double P, double tc)
{
InstrumentLogger::instance()->log_instrument_log("<Common::Qswater(double P, double tc)@@@Common.cpp>");
    double es;
    es = 0.611213 * exp (17.5043 * tc / (241.3 + tc));

InstrumentLogger::instance()->log_instrument_log("</Common::Qswater(double P, double tc)@@@Common.cpp>");
    return (0.622 * es / P);
InstrumentLogger::instance()->log_instrument_log("</Common::Qswater(double P, double tc)@@@Common.cpp>");
}
double Common :: DepthofSnow (double SWE)
{
InstrumentLogger::instance()->log_instrument_log("<Common::DepthofSnow(double SWE)@@@Common.cpp>");
    double Snow_Depth;
    if (SWE > 2.05)
    {
        if (SWE <= 145.45)
        {
            Snow_Depth = (SWE - 2.05) / 2.39;
        }

        else
        {
            Snow_Depth = (SWE + 128.06) / 4.5608;
        }

    }

    else
    {
        Snow_Depth = 0;
    }

InstrumentLogger::instance()->log_instrument_log("</Common::DepthofSnow(double SWE)@@@Common.cpp>");
    return Snow_Depth / 100.0;
InstrumentLogger::instance()->log_instrument_log("</Common::DepthofSnow(double SWE)@@@Common.cpp>");
}
double Common :: SWE_prob (double SWEmean, double SWE, double CV)
{
InstrumentLogger::instance()->log_instrument_log("<Common::SWE_prob(double SWEmean, double SWE, double CV)@@@Common.cpp>");
    if (SWE <= 0.01)
    {

InstrumentLogger::instance()->log_instrument_log("</Common::SWE_prob(double SWEmean, double SWE, double CV)@@@Common.cpp>");
        return 0.0;
    }

    if (SWE >= SWEmean)
    {

InstrumentLogger::instance()->log_instrument_log("</Common::SWE_prob(double SWEmean, double SWE, double CV)@@@Common.cpp>");
        return 1.0;
    }

    double K = - SWE / (SWEmean * CV);
    double Sy = sqrt (log (1.0 + CV * CV));
    double Ky = log (1.0 + K * CV) / Sy + Sy / 2.0;
    double t = 1 / (1 + little_p * Ky);
    double P = (exp (- Ky * Ky / 2) / sqrt (2 * M_PI)) * (a1 * t + a2 * t * t + a3 * t * t * t);
    if (P > 1.0 || P < 0.001)
    {
        P = 1.0;
    }

InstrumentLogger::instance()->log_instrument_log("</Common::SWE_prob(double SWEmean, double SWE, double CV)@@@Common.cpp>");
    return P;
InstrumentLogger::instance()->log_instrument_log("</Common::SWE_prob(double SWEmean, double SWE, double CV)@@@Common.cpp>");
}
double Common :: SVDens (double Temp)
{
InstrumentLogger::instance()->log_instrument_log("<Common::SVDens(double Temp)@@@Common.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Common::SVDens(double Temp)@@@Common.cpp>");
    return 1.324 * exp (22.452 * Temp / (Temp + 273.15)) / (Temp + 273.15);
InstrumentLogger::instance()->log_instrument_log("</Common::SVDens(double Temp)@@@Common.cpp>");
}
void Common :: GroupEnding (string & AA, int Cnt)
{
InstrumentLogger::instance()->log_instrument_log("<Common::GroupEnding(string & AA, int Cnt)@@@Common.cpp>");
    int alphas = Cnt / 26;
    int letter = Cnt % 26;
    if (! letter)
    {
        letter = 26;
        alphas = 0;
    }

    AA = "@@";
    AA [1] += letter;
    if (alphas > 0)
    {
        string B = "@";
        B [0] += alphas;
        AA.insert (1, B);
    }

InstrumentLogger::instance()->log_instrument_log("</Common::GroupEnding(string & AA, int Cnt)@@@Common.cpp>");
}
double Common :: Ice_Bulb (double Tc, double RH, double Pa)
{
InstrumentLogger::instance()->log_instrument_log("<Common::Ice_Bulb(double Tc, double RH, double Pa)@@@Common.cpp>");
    double Tk = Tc + CRHM_constants :: Tm;
    double D = 0.0000206 * pow (Tk / CRHM_constants :: Tm, 1.75);
    double RHO = Pa * 1000.0 / (CRHM_constants :: Rgas * Tk);
    double qt = CRHM_constants :: em / (Pa * 1000.0) * 611.213 * exp (22.4422 * Tc / (CRHM_constants :: Tm + Tc));
    double lamda = 0.000076843 * Tk + 0.003130762;
    double L;
    if (Tc > 0.0)
    {
        L = CRHM_constants :: Lv;
    }

    else
    {
        L = CRHM_constants :: Ls;
    }

    double delta = CRHM_constants :: em * L * qt / (CRHM_constants :: Rgas * sqr (Tk));

InstrumentLogger::instance()->log_instrument_log("</Common::Ice_Bulb(double Tc, double RH, double Pa)@@@Common.cpp>");
    return Tc - L * (1.0 - RH / 100.0) * qt / (CRHM_constants :: Cp + L * delta) * (RHO * CRHM_constants :: Cp * D / lamda);
InstrumentLogger::instance()->log_instrument_log("</Common::Ice_Bulb(double Tc, double RH, double Pa)@@@Common.cpp>");
}
void Common :: Message (const char * s1, const char * s2)
{
InstrumentLogger::instance()->log_instrument_log("<Common::Message(const char * s1, const char * s2)@@@Common.cpp>");
    CRHMLogger :: instance () -> log_to_console (s1 + std :: string (", ") + s2);
    CRHMLogger :: instance () -> log_run_message (s1 + std :: string (", ") + s2);
InstrumentLogger::instance()->log_instrument_log("</Common::Message(const char * s1, const char * s2)@@@Common.cpp>");
}
void Common :: Message (const string s1, const string s2)
{
InstrumentLogger::instance()->log_instrument_log("<Common::Message(const string s1, const string s2)@@@Common.cpp>");
    CRHMLogger :: instance () -> log_to_console (s1 + std :: string (", ") + s2);
    CRHMLogger :: instance () -> log_run_message (s1 + std :: string (", ") + s2);
InstrumentLogger::instance()->log_instrument_log("</Common::Message(const string s1, const string s2)@@@Common.cpp>");
}
string Common :: lowercase (string & s)
{
InstrumentLogger::instance()->log_instrument_log("<Common::lowercase(string & s)@@@Common.cpp>");
    transform (s.begin (), s.end (), s.begin (), (int (*) (int)) tolower);

InstrumentLogger::instance()->log_instrument_log("</Common::lowercase(string & s)@@@Common.cpp>");
    return s;
InstrumentLogger::instance()->log_instrument_log("</Common::lowercase(string & s)@@@Common.cpp>");
}
int Common :: IndexOf (TStringList * Box, const string S)
{
InstrumentLogger::instance()->log_instrument_log("<Common::IndexOf(TStringList * Box, const string S)@@@Common.cpp>");
    for (int ii = 0; ii < Box -> Count; ++ ii) {
        if (Box -> Strings [ii] == S)
        {

InstrumentLogger::instance()->log_instrument_log("</Common::IndexOf(TStringList * Box, const string S)@@@Common.cpp>");
            return ii;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Common::IndexOf(TStringList * Box, const string S)@@@Common.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</Common::IndexOf(TStringList * Box, const string S)@@@Common.cpp>");
}
string Common :: longtoStr (long L)
{
InstrumentLogger::instance()->log_instrument_log("<Common::longtoStr(long L)@@@Common.cpp>");
    ostringstream temp;
    temp << L;

InstrumentLogger::instance()->log_instrument_log("</Common::longtoStr(long L)@@@Common.cpp>");
    return temp.str ();
InstrumentLogger::instance()->log_instrument_log("</Common::longtoStr(long L)@@@Common.cpp>");
}
void Common :: ltrim (std :: string & s)
{
InstrumentLogger::instance()->log_instrument_log("<Common::ltrim(std :: string & s)@@@Common.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Common::ltrim(std :: string & s)@@@Common.cpp>");
}
void Common :: rtrim (std :: string & s)
{
InstrumentLogger::instance()->log_instrument_log("<Common::rtrim(std :: string & s)@@@Common.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Common::rtrim(std :: string & s)@@@Common.cpp>");
}
string Common :: trimleft (string & str)
{
InstrumentLogger::instance()->log_instrument_log("<Common::trimleft(string & str)@@@Common.cpp>");
    Common :: ltrim (str);

InstrumentLogger::instance()->log_instrument_log("</Common::trimleft(string & str)@@@Common.cpp>");
    return str;
InstrumentLogger::instance()->log_instrument_log("</Common::trimleft(string & str)@@@Common.cpp>");
}
string Common :: trimright (string & str)
{
InstrumentLogger::instance()->log_instrument_log("<Common::trimright(string & str)@@@Common.cpp>");
    Common :: rtrim (str);

InstrumentLogger::instance()->log_instrument_log("</Common::trimright(string & str)@@@Common.cpp>");
    return str;
InstrumentLogger::instance()->log_instrument_log("</Common::trimright(string & str)@@@Common.cpp>");
}
string Common :: trim (string & str)
{
InstrumentLogger::instance()->log_instrument_log("<Common::trim(string & str)@@@Common.cpp>");
    str = trimleft (str);
    str = trimright (str);

InstrumentLogger::instance()->log_instrument_log("</Common::trim(string & str)@@@Common.cpp>");
    return str;
InstrumentLogger::instance()->log_instrument_log("</Common::trim(string & str)@@@Common.cpp>");
}
double Common :: StrtoDt (string s)
{
InstrumentLogger::instance()->log_instrument_log("<Common::StrtoDt(string s)@@@Common.cpp>");
    istringstream instr;
    instr.str (s);
    double D;
    instr >> D;

InstrumentLogger::instance()->log_instrument_log("</Common::StrtoDt(string s)@@@Common.cpp>");
    return D;
InstrumentLogger::instance()->log_instrument_log("</Common::StrtoDt(string s)@@@Common.cpp>");
}
bool Common :: EqualUpper (string s1, string s2)
{
InstrumentLogger::instance()->log_instrument_log("<Common::EqualUpper(string s1, string s2)@@@Common.cpp>");
    transform (s1.begin (), s1.end (), s1.begin (), :: toupper);
    transform (s2.begin (), s2.end (), s2.begin (), :: toupper);

InstrumentLogger::instance()->log_instrument_log("</Common::EqualUpper(string s1, string s2)@@@Common.cpp>");
    return (bool) (s1 == s2);
InstrumentLogger::instance()->log_instrument_log("</Common::EqualUpper(string s1, string s2)@@@Common.cpp>");
}
double Common :: KyValue (double probability, double guess)
{
InstrumentLogger::instance()->log_instrument_log("<Common::KyValue(double probability, double guess)@@@Common.cpp>");
    double Ky, TempP, t;
    bool done = false;
    double direction = - 1;
    double tolerance = 0.0001;
    double dKy = 0.1;
    long iterations = 0;
    Ky = guess;
    while (! done) {
        iterations ++;
        t = 1 / (1 + little_p * Ky);
        TempP = (exp (- Ky * Ky / 2) / sqrt (2 * M_PI)) * (a1 * t + a2 * t * t + a3 * t * t * t);
        if (fabs (TempP - probability) <= tolerance)
        {
            done = true;
        }

        else
        {
            if (TempP > (probability + tolerance))
            {
                if (direction == - 1)
                {
                    dKy = dKy / 2;
                    direction = 1;
                }

                else
                {
                    dKy = dKy / 2;
                    direction = - 1;
                }

            }

            Ky = Ky + dKy * direction;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Common::KyValue(double probability, double guess)@@@Common.cpp>");
    return Ky;
InstrumentLogger::instance()->log_instrument_log("</Common::KyValue(double probability, double guess)@@@Common.cpp>");
}
double Common :: K (double Ky, double LogStDev)
{
InstrumentLogger::instance()->log_instrument_log("<Common::K(double Ky, double LogStDev)@@@Common.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Common::K(double Ky, double LogStDev)@@@Common.cpp>");
    return (exp (LogStDev * Ky - (sqr (LogStDev) / 2)) - 1) / (sqrt (exp (sqr (LogStDev)) - 1));
InstrumentLogger::instance()->log_instrument_log("</Common::K(double Ky, double LogStDev)@@@Common.cpp>");
}
string Common :: GetCurrentPath (void)
{
InstrumentLogger::instance()->log_instrument_log("<Common::GetCurrentPath(void)@@@Common.cpp>");
    const char * buffer;
    buffer = getcwd (NULL, 0);
    printf ("Current path is %s", buffer);

InstrumentLogger::instance()->log_instrument_log("</Common::GetCurrentPath(void)@@@Common.cpp>");
    return buffer;
InstrumentLogger::instance()->log_instrument_log("</Common::GetCurrentPath(void)@@@Common.cpp>");
}
bool Common :: Variation_Decide (int Variation_set, long Variation)
{
InstrumentLogger::instance()->log_instrument_log("<Common::Variation_Decide(int Variation_set, long Variation)@@@Common.cpp>");
    VandP V;
    V.Set (Variation);
    long variations = V.GetV ();
    if (((variations & 2048) != 0 && Variation_set == 0) || (variations & 4096) != 0 || (variations == 0) || (variations & Variation_set) != 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Common::Variation_Decide(int Variation_set, long Variation)@@@Common.cpp>");
        return true;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</Common::Variation_Decide(int Variation_set, long Variation)@@@Common.cpp>");
        return false;
    }

InstrumentLogger::instance()->log_instrument_log("</Common::Variation_Decide(int Variation_set, long Variation)@@@Common.cpp>");
}
void Common :: writefile (string filepath, string content)
{
InstrumentLogger::instance()->log_instrument_log("<Common::writefile(string filepath, string content)@@@Common.cpp>");
    ofstream myfile;
    myfile.open (filepath, ios :: app);
    myfile << "\n" << content;
    myfile.close ();
InstrumentLogger::instance()->log_instrument_log("</Common::writefile(string filepath, string content)@@@Common.cpp>");
}
bool static isdigit (char ch)
{
InstrumentLogger::instance()->log_instrument_log("<isdigit(char ch)@@@Common.cpp>");
    if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
    {

InstrumentLogger::instance()->log_instrument_log("</isdigit(char ch)@@@Common.cpp>");
        return true;
    }

InstrumentLogger::instance()->log_instrument_log("</isdigit(char ch)@@@Common.cpp>");
    return false;
InstrumentLogger::instance()->log_instrument_log("</isdigit(char ch)@@@Common.cpp>");
}