#if defined (_WIN32)
    #include "stdafx.h"
    #include <Windows.h>
    #include <direct.h>
#endif

#if defined (__linux__) || defined (__APPLE__)
    #include <unistd.h>
#endif

#include "TStringList.h"
#include <time.h>
#include <cmath>
#include <algorithm>
#include <string>
#include <limits>
#include "ClassCRHM.h"
#include "Common.h"
#include "InstrumentLogger.h"

string TStringList :: CommaText (void)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::CommaText(void)@@@TStringList.cpp>");
    ostringstream temp;
    for (unsigned int ii = 0; ii < array.size (); ++ ii) {
        if (ii)
        {
            temp << ", ";
        }

        temp << array.at (ii).get_Name ();
    }
    temp << endl;

InstrumentLogger::instance()->log_instrument_log("</TStringList::CommaText(void)@@@TStringList.cpp>");
    return temp.str ();
InstrumentLogger::instance()->log_instrument_log("</TStringList::CommaText(void)@@@TStringList.cpp>");
}
void TStringList :: DelimitedText (string s)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::DelimitedText(string s)@@@TStringList.cpp>");
    string in_quote;
    bool quoted = false;
    long pos, here, last_quote, done_to = 0;
    Clear ();
    Common :: trim (s);
    if (s.size () == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</TStringList::DelimitedText(string s)@@@TStringList.cpp>");
        return;
    }

    s.append (",");
    for (pos = 0; pos < (long) s.size (); ++ pos) {
        here = s.find_first_of ("' ,", pos);
        pos = here;
        switch (s [here]) {
        case '\'':
            quoted = true;
            last_quote = s.find ('\'', ++ pos);
            if (last_quote > here + 1)
            {
                in_quote = s.substr (here + 1, last_quote - here - 1);
            }

            else
            {

InstrumentLogger::instance()->log_instrument_log("</TStringList::DelimitedText(string s)@@@TStringList.cpp>");
                return;
            }

            pos = last_quote;
            break;
        case ',':
        case ' ':
            if (quoted)
            {
                Add (in_quote);
            }

            else
            {
                if (pos > done_to)
                {
                    Add (s.substr (done_to, pos - done_to));
                }

                else
                {

InstrumentLogger::instance()->log_instrument_log("</TStringList::DelimitedText(string s)@@@TStringList.cpp>");
                    return;
                }

            }

            done_to = s.find_first_not_of (" ", here + 1);
            if (done_to > - 1)
            {
                pos = done_to - 1;
            }

            else
            {
                pos = here;
            }

            in_quote = "";
            quoted = false;
        default:
            break;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</TStringList::DelimitedText(string s)@@@TStringList.cpp>");
}
void TStringList :: CommaText (string s)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::CommaText(string s)@@@TStringList.cpp>");
    string in_quote;
    string :: size_type pos, here, last_quote, done_to = 0;
    array.clear ();
    Common :: trim (s);
    s.append (",");
    for (pos = 0; pos < s.size (); ++ pos) {
        here = s.find_first_of ("' ,", pos);
        switch (s [here]) {
        case '\'':
            last_quote = s.find ("'", pos);
            in_quote = s.substr (here + 1, last_quote - 1);
            pos = last_quote + 1;
            break;
        case ',':
        case ' ':
            in_quote.append (s.substr (done_to, here - done_to));
            Add (in_quote);
            done_to = s.find_first_not_of (" ", here + 1);
            if (done_to == string :: npos)
            {
                pos = s.size ();
            }

            else
            {
                pos = done_to;
                in_quote = "";
            }

        default:
            break;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</TStringList::CommaText(string s)@@@TStringList.cpp>");
}
void TStringList :: SaveToFile (string FileName)
{
    ofstream file;
    file.open (FileName.c_str ());
    for (unsigned int ii = 0; ii < array.size (); ++ ii)
        file << array.at (ii).get_Name () << endl;
    file.close ();
}
;

string & TStringList :: operator [] (int ii)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::operator[](int ii)@@@TStringList.cpp>");

InstrumentLogger::instance()->log_instrument_log("</TStringList::operator[](int ii)@@@TStringList.cpp>");
    return array [ii].Name;
InstrumentLogger::instance()->log_instrument_log("</TStringList::operator[](int ii)@@@TStringList.cpp>");
}
void TStringList :: AddObject (string s, TObject * thing)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::AddObject(string s, TObject * thing)@@@TStringList.cpp>");
    array.push_back (StringandObject (s, thing));
    Count = array.size ();
InstrumentLogger::instance()->log_instrument_log("</TStringList::AddObject(string s, TObject * thing)@@@TStringList.cpp>");
}
void TStringList :: InsertObject (int ii, string name, TObject * object)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::InsertObject(int ii, string name, TObject * object)@@@TStringList.cpp>");
    array.push_back (StringandObject (name, object));
    Count = array.size ();
InstrumentLogger::instance()->log_instrument_log("</TStringList::InsertObject(int ii, string name, TObject * object)@@@TStringList.cpp>");
}
int TStringList :: IndexOf (string s)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::IndexOf(string s)@@@TStringList.cpp>");
    if (Count <= 0)
    {

InstrumentLogger::instance()->log_instrument_log("</TStringList::IndexOf(string s)@@@TStringList.cpp>");
        return - 1;
    }

    for (unsigned int ii = 0; ii < array.size (); ++ ii)
        if (array.at (ii).get_Name () == s)
        {

InstrumentLogger::instance()->log_instrument_log("</TStringList::IndexOf(string s)@@@TStringList.cpp>");
            return ii;
        }

InstrumentLogger::instance()->log_instrument_log("</TStringList::IndexOf(string s)@@@TStringList.cpp>");
    return - 1;
InstrumentLogger::instance()->log_instrument_log("</TStringList::IndexOf(string s)@@@TStringList.cpp>");
}
void TStringList :: Add (string s)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::Add(string s)@@@TStringList.cpp>");
    array.push_back (StringandObject (s, 0));
    Count = array.size ();
InstrumentLogger::instance()->log_instrument_log("</TStringList::Add(string s)@@@TStringList.cpp>");
}
void TStringList :: Clear ()
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::Clear()@@@TStringList.cpp>");
    array.clear ();
    Count = 0;
InstrumentLogger::instance()->log_instrument_log("</TStringList::Clear()@@@TStringList.cpp>");
}
void TStringList :: Assign (TStringList * Src)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::Assign(TStringList * Src)@@@TStringList.cpp>");
    Clear ();
    for (unsigned int ii = 0; ii < Src -> array.size (); ++ ii)
        AddObject (Src -> array.at (ii).get_Name (), Src -> array [ii].Object);
InstrumentLogger::instance()->log_instrument_log("</TStringList::Assign(TStringList * Src)@@@TStringList.cpp>");
}
void TStringList :: Delete (int Index)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::Delete(int Index)@@@TStringList.cpp>");
    vector < StringandObject > :: iterator pos;
    int cnt = - 1;
    for (pos = array.begin (); pos < array.end (); ++ pos)
        if (Index == ++ cnt)
        {
            array.erase (pos);
            Count = array.size ();

InstrumentLogger::instance()->log_instrument_log("</TStringList::Delete(int Index)@@@TStringList.cpp>");
            return;
        }

    ;
InstrumentLogger::instance()->log_instrument_log("</TStringList::Delete(int Index)@@@TStringList.cpp>");
}
string & TStrings :: operator [] (int ii)
{
InstrumentLogger::instance()->log_instrument_log("<TStrings::operator[](int ii)@@@TStringList.cpp>");
    if (ii < 0 || ii >= StringList -> Count)
    {
        CRHMException Except ("Array index out of bounds.", TExcept :: TERMINATE);
        LogError (Except);
        throw CRHMException (Except);
    }

InstrumentLogger::instance()->log_instrument_log("</TStrings::operator[](int ii)@@@TStringList.cpp>");
    return StringList -> array [ii].Name;
InstrumentLogger::instance()->log_instrument_log("</TStrings::operator[](int ii)@@@TStringList.cpp>");
}
TObject * & TObjects :: operator [] (int ii)
{
InstrumentLogger::instance()->log_instrument_log("<TObjects::operator[](int ii)@@@TStringList.cpp>");
    if (ii < 0 || ii >= StringList -> Count)
    {
        CRHMException Except ("Array index out of bounds.", TExcept :: TERMINATE);
        LogError (Except);
        throw CRHMException (Except);
    }

InstrumentLogger::instance()->log_instrument_log("</TObjects::operator[](int ii)@@@TStringList.cpp>");
    return StringList -> array [ii].Object;
InstrumentLogger::instance()->log_instrument_log("</TObjects::operator[](int ii)@@@TStringList.cpp>");
}
TStringList :: TStringList (const TStringList & p)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::TStringList(const TStringList & p)@@@TStringList.cpp>");
    Sorted = p.Sorted;
    CaseSensitive = p.CaseSensitive;
    array.reserve (64);
    Strings.Init (this);
    Objects.Init (this);
    Count = 0;
InstrumentLogger::instance()->log_instrument_log("</TStringList::TStringList(const TStringList & p)@@@TStringList.cpp>");
}
void TStringList :: LoadFromFile (string filename)
{
InstrumentLogger::instance()->log_instrument_log("<TStringList::LoadFromFile(string filename)@@@TStringList.cpp>");
    ifstream infile (filename.c_str ());
    string line;
    while (std :: getline (infile, line)) {
        AddObject (line, NULL);
    }
InstrumentLogger::instance()->log_instrument_log("</TStringList::LoadFromFile(string filename)@@@TStringList.cpp>");
}