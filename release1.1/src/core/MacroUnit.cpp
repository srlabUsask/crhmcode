#include <stdio.h>
#include "MacroUnit.h"
#include <map>
#include <boost/spirit/include/classic_exceptions.hpp>
#include "../../core/InstrumentLogger.h"

#if defined (__linux__) || defined (__APPLE__)
    #include <cxxabi.h>
#endif

extern double xLimit;

double Fday ()
{
InstrumentLogger::instance()->log_instrument_log("<Fday()@@@MacroUnit.cpp>");
    int year, month, day, h, m;
    StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & year, & month, & day, & h, & m);

InstrumentLogger::instance()->log_instrument_log("</Fday()@@@MacroUnit.cpp>");
    return day;
InstrumentLogger::instance()->log_instrument_log("</Fday()@@@MacroUnit.cpp>");
}
double Fmonth ()
{
InstrumentLogger::instance()->log_instrument_log("<Fmonth()@@@MacroUnit.cpp>");
    int year, month, day, h, m;
    StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & year, & month, & day, & h, & m);

InstrumentLogger::instance()->log_instrument_log("</Fmonth()@@@MacroUnit.cpp>");
    return month;
InstrumentLogger::instance()->log_instrument_log("</Fmonth()@@@MacroUnit.cpp>");
}
double Fyear ()
{
InstrumentLogger::instance()->log_instrument_log("<Fyear()@@@MacroUnit.cpp>");
    int year, month, day, h, m;
    StandardConverterUtility :: DecodeDateTime (Global :: DTnow, & year, & month, & day, & h, & m);

InstrumentLogger::instance()->log_instrument_log("</Fyear()@@@MacroUnit.cpp>");
    return year;
InstrumentLogger::instance()->log_instrument_log("</Fyear()@@@MacroUnit.cpp>");
}
double Fjulian ()
{
InstrumentLogger::instance()->log_instrument_log("<Fjulian()@@@MacroUnit.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Fjulian()@@@MacroUnit.cpp>");
    return Julian ("now");
InstrumentLogger::instance()->log_instrument_log("</Fjulian()@@@MacroUnit.cpp>");
}
double Fgetstep ()
{
InstrumentLogger::instance()->log_instrument_log("<Fgetstep()@@@MacroUnit.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Fgetstep()@@@MacroUnit.cpp>");
    return getstep ();
InstrumentLogger::instance()->log_instrument_log("</Fgetstep()@@@MacroUnit.cpp>");
}
double Fgetfirst ()
{
InstrumentLogger::instance()->log_instrument_log("<Fgetfirst()@@@MacroUnit.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Fgetfirst()@@@MacroUnit.cpp>");
    return (getstep () % Global :: Freq == 1);
InstrumentLogger::instance()->log_instrument_log("</Fgetfirst()@@@MacroUnit.cpp>");
}
double Fgetlast ()
{
InstrumentLogger::instance()->log_instrument_log("<Fgetlast()@@@MacroUnit.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Fgetlast()@@@MacroUnit.cpp>");
    return (getstep () % Global :: Freq == 0);
InstrumentLogger::instance()->log_instrument_log("</Fgetlast()@@@MacroUnit.cpp>");
}
double Fgetrand ()
{
InstrumentLogger::instance()->log_instrument_log("<Fgetrand()@@@MacroUnit.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Fgetrand()@@@MacroUnit.cpp>");
    return (double) rand () / RAND_MAX;
InstrumentLogger::instance()->log_instrument_log("</Fgetrand()@@@MacroUnit.cpp>");
}
ClassMacro * ClassMacro :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::klone(string name) const@@@MacroUnit.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::klone(string name) const@@@MacroUnit.cpp>");
    return new ClassMacro (name, MacroBegin, "11/13/07");
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::klone(string name) const@@@MacroUnit.cpp>");
}
void ClassMacro :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::decl(void)@@@MacroUnit.cpp>");
    if (isGroup || isStruct)
    {
        if (Grpnhru > 0)
        {
            nhru = Grpnhru;
            if (Grpnhru > Global :: maxhru)
            {
                Global :: maxhru = Grpnhru;
            }

        }

        else
        if (nhru == 0)
        {
            nhru = Global :: nhru;
        }

        string S = Common :: longtoStr ((max < long > (GroupCnt, StructCnt)));
        if (isGroup)
        {
            declparam ("HRU_group", TDim :: NHRU, S, "1", "1e3", "group #", "()", & HRU_group);
        }

        if (isStruct)
        {
            string Choice = GrpStringList -> CommaText ();
            declparam ("HRU_struct", TDim :: NHRU, "[1]", "1", Common :: longtoStr (GrpStringList -> Count), string ("select using 1/2/3 ... module/group from '" + Choice + "'"), "()", & HRU_struct);
        }

        Modules.clear ();
        unsigned short Variation;
        for (int ii = 0; ii < GrpStringList -> Count; ++ ii) {
            string S = GrpStringList -> Strings [ii];
            string :: size_type idx = S.find ("#");
            if (idx != string :: npos)
            {
                Variation = (unsigned short) (pow (2, S [idx + 1] - char ('1')));
                S = S.substr (0, idx);
            }

            else
            {
                Variation = 0;
            }

            int Indx = Global :: AllModulesList -> IndexOf (S);
            if (Indx == - 1)
            {
                Common :: Message (string ("Module: '" + S + "' not found!"), "Macro Error");
                CRHMException Except (string (string ("module: ") + S + " not found in " + Name).c_str (), TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

            ClassModule * Mod = (ClassModule *) Global :: AllModulesList -> Objects [Indx];
            ModulePtr Test (Mod -> klone (Name));
            std :: weak_ptr < ClassModule > MG (Test);

            #if defined (_WIN32)
                string S1 = typeid (* Mod).name ();
                string S2 = typeid (* Test).name ();
            #endif

            #if defined (__linux__) || defined (__APPLE__)
                int demangle_status = 0;
                string S1 = abi :: __cxa_demangle (typeid (* Mod).name (), 0, 0, & demangle_status);
                auto Test_raw = Test.get ();
                string S2 = abi :: __cxa_demangle (typeid (* Test_raw).name (), 0, 0, & demangle_status);
            #endif

            if (S2 == "ClassMacro")
            {
                Test -> ID = S;
            }

            else
            {
                auto Test_raw = Test.get ();
                Test -> ID = typeid (* Test_raw).name ();
                if (S2 == "Classobs")
                {
                    this -> ObsModule = (ClassModule *) Test.get ();
                }

            }

            Test -> Name = Name;
            Test -> HRU_struct = this -> HRU_struct;
            Test -> nhru = nhru;
            Test -> GroupCnt = this -> GroupCnt;
            Test -> StructCnt = this -> StructCnt;
            Test -> variation = Variation;
            Test -> DLLName = Mod -> DLLName;
            Test -> NameRoot = Mod -> NameRoot;
            Test -> Version = this -> Version;
            if (isStruct)
            {
                Test -> ModuleIndx = ii + 1;
            }

            else
            {
                Test -> ModuleIndx = this -> ModuleIndx;
            }

            Modules.push_back (Test);
        }
        list < ModulePtr > :: iterator iterM;
        iterM = Modules.begin ();
        while (iterM != Modules.end ()) {
            ClassModule * MPP = (ClassModule *) (* iterM).get ();
            string SS = (* iterM) -> NameRoot.c_str ();
            if ((* iterM) -> variation > 0)
            {
                string AA = "#0";
                AA [1] += (char) (log ((* iterM) -> variation) / log (2) + 1);
                SS += AA;
            }

            long jj = GrpStringList -> IndexOf (SS);
            GrpStringList -> Objects [jj] = (TObject *) MPP;
            (* iterM) -> nhru = nhru;
            (* iterM) -> decl ();
            ++ iterM;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::decl(void)@@@MacroUnit.cpp>");
        return;
    }

    list < DefCRHMPtr > :: iterator iterC;
    iterC = Calls.begin ();
    while (iterC != Calls.end ()) {
        std :: weak_ptr < DefCRHM > CP ((* iterC));
        (* iterC) -> CallDecl ();
        ++ iterC;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::decl(void)@@@MacroUnit.cpp>");
}
void ClassMacro :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::init(void)@@@MacroUnit.cpp>");
    nhru = getdim (TDim :: NHRU);
    if (isGroup || isStruct)
    {
        LogMessage (" ");
        string SS;
        if (isGroup)
        {
            SS = "Group: '" + NameRoot + "' ->";
        }

        else
        {
            SS = "Struct: '" + NameRoot + "' ->";
        }

        for (int ii = 0; ii < GrpStringList -> Count; ++ ii)
            SS += " " + GrpStringList -> Strings [ii];
        LogMessage (SS.c_str ());
        list < ModulePtr > :: iterator iter;
        iter = Modules.begin ();
        while (iter != Modules.end ()) {
            std :: weak_ptr < ClassModule > MP ((* iter));
            (* iter) -> init ();
            ++ iter;
        }
        if (StructCnt)
        {
            for (hh = 0; hh < nhru; ++ hh) {
                if (HRU_struct [hh] < 1)
                {
                    const_cast < long * > (HRU_struct) [hh] = 1;
                }

                if (HRU_struct [hh] > GrpStringList -> Count)
                {
                    const_cast < long * > (HRU_struct) [hh] = GrpStringList -> Count;
                }

            }
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::init(void)@@@MacroUnit.cpp>");
        return;
    }

    list < DefCRHMPtr > :: iterator iter;
    iter = Calls.begin ();
    while (iter != Calls.end ()) {
        DefCRHM Op = (* (* iter));
        (* iter) -> CallInit (nhru, nlay);
        ++ iter;
    }
    FP = vars.find ("hh");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("hh", VarCHRM ()));
        FP = vars.find ("hh");
    }

    FP -> second.kind = TV :: CRHMint;
    FP -> second.ivalue = const_cast < long * > (& hh);
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "hh";
    FP -> second.Me = this;
    FP = vars.find ("NHRU");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("NHRU", VarCHRM ()));
        FP = vars.find ("NHRU");
    }

    FP -> second.kind = TV :: LOCAL;
    FP -> second.val = nhru;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "NHRU";
    FP -> second.Me = this;
    FP = vars.find ("GROUP");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("GROUP", VarCHRM ()));
        FP = vars.find ("GROUP");
    }

    FP -> second.kind = TV :: LOCAL;
    FP -> second.val = GroupCnt;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "GROUP";
    FP -> second.Me = this;
    FP = vars.find ("STRUCT");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("STRUCT", VarCHRM ()));
        FP = vars.find ("STRUCT");
    }

    FP -> second.kind = TV :: LOCAL;
    FP -> second.val = StructCnt;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "STRUCT";
    FP -> second.Me = this;
    FP = vars.find ("PI");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("PI", VarCHRM ()));
        FP = vars.find ("PI");
    }

    FP -> second.kind = TV :: LOCAL;
    FP -> second.val = M_PI;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "PI";
    FP = vars.find ("NO_DISPLAY");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("NO_DISPLAY", VarCHRM ()));
        FP = vars.find ("NO_DISPLAY");
    }

    FP -> second.kind = TV :: LOCAL;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "NO_DISPLAY";
    FP = vars.find ("FREQ");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("FREQ", VarCHRM ()));
        FP = vars.find ("FREQ");
    }

    FP -> second.kind = TV :: LOCAL;
    FP -> second.val = Global :: Freq;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "FREQ";
    FP = vars.find ("RAND");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("RAND", VarCHRM ()));
        FP = vars.find ("RAND");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "RAND";
    FP -> second.pget = Fgetrand;
    FP = vars.find ("STEP");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("STEP", VarCHRM ()));
        FP = vars.find ("STEP");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "STEP";
    FP -> second.pget = Fgetstep;
    FP = vars.find ("LASTINT");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("LASTINT", VarCHRM ()));
        FP = vars.find ("LASTINT");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "LASTINT";
    FP -> second.pget = Fgetlast;
    FP = vars.find ("FIRSTINT");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("FIRSTINT", VarCHRM ()));
        FP = vars.find ("FIRSTINT");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "FIRSTINT";
    FP -> second.pget = Fgetfirst;
    FP = vars.find ("JULIAN");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("JULIAN", VarCHRM ()));
        FP = vars.find ("JULIAN");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "JULIAN";
    FP -> second.pget = Fjulian;
    FP = vars.find ("YEAR");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("YEAR", VarCHRM ()));
        FP = vars.find ("YEAR");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "YEAR";
    FP -> second.pget = Fyear;
    FP = vars.find ("MONTH");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("MONTH", VarCHRM ()));
        FP = vars.find ("MONTH");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "MONTH";
    FP -> second.pget = Fmonth;
    FP = vars.find ("DAY");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("DAY", VarCHRM ()));
        FP = vars.find ("DAY");
    }

    FP -> second.kind = TV :: FUNget;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "DAY";
    FP -> second.pget = Fday;
    FP = vars.find ("ReadAheadObs");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("ReadAheadObs", VarCHRM ()));
        FP = vars.find ("ReadAheadObs");
    }

    FP -> second.kind = TV :: FUNobs;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "ReadAheadObs";
    FP -> second.Me = this;
    FP = vars.find ("WriteAheadObs");
    if (FP == vars.end ())
    {
        vars.insert (make_pair ("WriteAheadObs", VarCHRM ()));
        FP = vars.find ("WriteAheadObs");
    }

    FP -> second.kind = TV :: FUNobs;
    FP -> second.val = 0;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = 0;
    FP -> second.name = "WriteAheadObs";
    FP -> second.Me = this;
    calculator calc (eval, vars, Operations, PCiter, LastVar, LastVas);
    Operations.clear ();
    string str (Global :: MacroModulesList -> Strings [Begin]);
    for (int jj = Begin + 1; jj < End; ++ jj) {
        string :: size_type P = Global :: MacroModulesList -> Strings [jj].find ("//");
        if (P != string :: npos)
        {
            if (P - 1 > 0)
            {
                str += " \n" + Global :: MacroModulesList -> Strings [jj].substr (1, P - 1);
            }

        }

        else
        {
            str += " \n" + Global :: MacroModulesList -> Strings [jj];
        }

    }
    execbase :: Index = 0;
    string :: iterator first = str.begin ();
    parse_info < string :: iterator > info;
    do {
        info = parse (first, str.end (), calc, space_p);
        if (! info.hit || info.length == 0)
        {
            string err (first, str.end ());
            CRHMException TExcept (string ("cannot parse the command string: ") + err.c_str (), TExcept :: TERMINATE);
            LogError (TExcept);
        }

        else
        if (! info.full)
        {
            first = info.stop;
        }

    }
    while (! (info.full && info.hit));
    PCiter = Operations.begin ();
    int n = 1;
    while (PCiter != Operations.end ()) {
        (* PCiter) -> OurOrder = n ++;
        ++ PCiter;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::init(void)@@@MacroUnit.cpp>");
}
void ClassMacro :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::run(void)@@@MacroUnit.cpp>");
    if (isGroup || isStruct)
    {
        list < ModulePtr > :: iterator iter;
        iter = Modules.begin ();
        while (iter != Modules.end ()) {
            ModulePtr Op = (* iter);
            Op -> t_layvalues = Global :: t_layvalues;
            Op -> rh_layvalues = Global :: rh_layvalues;
            (* iter) -> pre_run ();
            (* iter) -> run ();
            ++ iter;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::run(void)@@@MacroUnit.cpp>");
        return;
    }

    for (hh = 1; chkStructOff (hh, nhru + 1); ++ hh) {
        PCiter = Operations.begin ();
        while (PCiter != Operations.end ()) {
            execbase Op = (* (* PCiter));
            double X = (* (* PCiter)) ();
            ++ PCiter;
            int Cnt = eval.size ();
        }
    }
    int Cnt = eval.size ();
    assert (eval.empty ());
    assert (LastVar.empty ());
    assert (LastVas.empty ());
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::run(void)@@@MacroUnit.cpp>");
}
void ClassMacro :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::finish(bool good)@@@MacroUnit.cpp>");
    if (isGroup || isStruct)
    {
        list < ModulePtr > :: iterator iter;
        iter = Modules.begin ();
        while (iter != Modules.end ()) {
            ModulePtr Op = (* iter);
            Op -> finish (false);
            ++ iter;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::finish(bool good)@@@MacroUnit.cpp>");
        return;
    }

    Operations.clear ();
    symtab_t :: iterator pos;
    for (pos = vars.begin (); pos != vars.end ();) {
        if (pos -> second.kind == TV :: LOCAL)
        {
            vars.erase (pos ++);
        }

        else
        {
            ++ pos;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::finish(bool good)@@@MacroUnit.cpp>");
}
ClassMacro :: ClassMacro (string Name, int ThisBegin, string Version, string Desc): ClassModule (Name, Version, LMODULE :: MACRO)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::ClassMacro(string Name, int ThisBegin, string Version, string Desc): ClassModule (Name, Version, LMODULE :: MACRO)@@@MacroUnit.cpp>");
    int ThisEnd = ThisBegin;
    MacroBegin = ThisBegin;
    Description = Desc;
    string S, SS;
    ID = Name;
    Grpnhru = 0;
    while (S = Common :: trim (Global :: MacroModulesList -> Strings [ThisEnd]), SS = S.substr (0, 3), ! (SS == "end" && (S.length () == 3 || S.find_first_of (" /") != string :: npos)) && Global :: MacroModulesList -> Count > ThisEnd) {
        ++ ThisEnd;
    }
    if (! DefCRHM :: DefStringList)
    {
        DefCRHM :: DefStringList = new TStringList;
    }

    isGroup = false;
    isStruct = false;
    for (int ii = ThisBegin + 1; ii < ThisEnd - 1; ++ ii) {
        string :: size_type Indx;
        Indx = Global :: MacroModulesList -> Strings [ii].find ("//");
        if (Indx != string :: npos)
        {
            string temp = Global :: MacroModulesList -> Strings [ii].substr (0, Indx - 1);
            temp = Common :: trimright (temp);
            DefCRHM :: DefStringList -> DelimitedText (Add_Quote (temp));
        }

        else
        {
            DefCRHM :: DefStringList -> DelimitedText (Add_Quote (Global :: MacroModulesList -> Strings [ii]));
        }

        long Pcnt = DefCRHM :: DefStringList -> Count;
        if (Pcnt < 1)
        {
            continue;
        }

        DefCRHM :: DefStringList -> Strings [0] = Common :: trimleft (DefCRHM :: DefStringList -> Strings [0]);
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("//") || DefCRHM :: DefStringList -> Strings [0].empty ())
        {
            continue;
        }

        if (DefCRHM :: DefStringList -> Strings [0].find ("command") == 0)
        {
            Begin = ii + 1;
            End = ThisEnd;
            DefCRHMPtr Call (new Defcommand (this));
            break;
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declgroup"))
        {
            if (! isGroup)
            {
                isGroup = true;
                GroupCnt = ++ Global :: GroupCntTrk;
                GrpStringList = new TStringList;
                if (DefCRHM :: DefStringList -> Count > 1 && (DefCRHM :: DefStringList -> Strings [1].find ("//") != string :: npos))
                {
                    Grpnhru = Strtolong (DefCRHM :: DefStringList -> Strings [1]);
                }

                else
                {
                    Grpnhru = nhru;
                }

            }

        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declstruct"))
        {
            if (! isStruct)
            {
                isStruct = true;
                StructCnt = ++ Global :: StructCntTrk;
                GrpStringList = new TStringList;
                if (DefCRHM :: DefStringList -> Count > 1 && ! DefCRHM :: DefStringList -> Strings [1].find ("//"))
                {
                    Grpnhru = Strtolong (DefCRHM :: DefStringList -> Strings [1]);
                }

                else
                {
                    Grpnhru = nhru;
                }

            }

        }

        else
        if (isGroup || isStruct)
        {
            string S = DefCRHM :: DefStringList -> Strings [0];
            string V;
            string :: size_type N = S.find ("#");
            if (N != string :: npos)
            {
                V = S.substr (N, 2);
                S = S.substr (1, N - 1);
            }

            long jj = - 1;
            if (Global :: OldModuleName != NULL)
            {
                jj = Global :: OldModuleName -> IndexOf (S);
            }

            if (jj == - 1)
            {
                GrpStringList -> Add (DefCRHM :: DefStringList -> Strings [0]);
            }

            else
            {
                GrpStringList -> Add (Global :: NewModuleName -> Strings [jj] + V);
                string Message = "Converting module " + Global :: OldModuleName -> Strings [jj] + V + " to " + Global :: NewModuleName -> Strings [jj] + V + " in macro " + Name.c_str ();
                LogMessage (Message.c_str ());
            }

        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declparam") && Pcnt >= 8)
        {
            DefCRHMPtr Call (new Defdeclparam (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("decldiagparam") && Pcnt >= 8)
        {
            DefCRHMPtr Call (new Defdeclparam (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declreadobs") && Pcnt >= 5)
        {
            DefCRHMPtr Call (new Defdeclreadobs (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declobsfunc") && Pcnt >= 4)
        {
            DefCRHMPtr Call (new Defdeclobsfunc (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declvar") && Pcnt >= 5)
        {
            DefCRHMPtr Call (new Defdeclvar (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("decldiag") && Pcnt >= 5)
        {
            DefCRHMPtr Call (new Defdecldiag (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declstatvar") && Pcnt >= 5)
        {
            DefCRHMPtr Call (new Defdeclstatvar (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("decllocal") && Pcnt >= 5)
        {
            DefCRHMPtr Call (new Defdecllocal (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declgetvar") && Pcnt >= 4)
        {
            DefCRHMPtr Call (new Defdeclgetvar (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declputvar") && Pcnt >= 4)
        {
            DefCRHMPtr Call (new Defdeclputvar (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declputparam") && Pcnt >= 4)
        {
            DefCRHMPtr Call (new Defdeclputparam (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("declobs") && Pcnt >= 5)
        {
            DefCRHMPtr Call (new Defdeclobs (this));
            Calls.push_back (Call);
        }

        else
        if (! DefCRHM :: DefStringList -> Strings [0].compare ("setpeer"))
        {
            if (DefCRHM :: DefStringList -> Count > 2)
            {
                PeerVar = DefCRHM :: DefStringList -> Strings [1];
                PeerRank = Strtolong (DefCRHM :: DefStringList -> Strings [2]);
            }

        }

        else
        {
            Common :: Message (string (string ("function not recognised or too few parameters: ") + "\"" + Global :: MacroModulesList -> Strings [ii] + "\""), "Macro Error");
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::ClassMacro(string Name, int ThisBegin, string Version, string Desc): ClassModule (Name, Version, LMODULE :: MACRO)@@@MacroUnit.cpp>");
}
ClassMacro :: ~ClassMacro ()
{
    Calls.clear ();
}
;
TStringList * DefCRHM :: DefStringList = NULL;

TDim DefCRHM :: getTDim (string D)
{
InstrumentLogger::instance()->log_instrument_log("<DefCRHM::getTDim(string D)@@@MacroUnit.cpp>");
    char table [] [7] = {"BASIN", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE", "NHRU", "NOBS", "NLAY", "NDEF", "NFREQ", "NREB", "NDEFN", "DEFX"};
    for (long ii = 0; ii < 21; ++ ii)
        if (D == table [ii])
        {

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTDim(string D)@@@MacroUnit.cpp>");
            return (TDim) ii;
        }

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTDim(string D)@@@MacroUnit.cpp>");
    return (TDim) - 1;
InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTDim(string D)@@@MacroUnit.cpp>");
}
TFun DefCRHM :: getTFunc (string D)
{
InstrumentLogger::instance()->log_instrument_log("<DefCRHM::getTFunc(string D)@@@MacroUnit.cpp>");
    char table [] [9] = {"FOBS", "W_MJ", "MJ_W", "AVG", "MIN", "MAX", "DTOT", "POS", "TOT", "FIRST", "LAST", "CNT", "CNT0", "INTVL"};
    for (long ii = 1; ii < 11; ++ ii)
        if (D == table [ii])
        {

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTFunc(string D)@@@MacroUnit.cpp>");
            return (TFun) ii;
        }

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTFunc(string D)@@@MacroUnit.cpp>");
    return (TFun) - 1;
InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTFunc(string D)@@@MacroUnit.cpp>");
}
Defdeclparam :: Defdeclparam (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclparam::Defdeclparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    if (DefStringList -> Strings [0] == "decldiagparam")
    {
        visibility = TVISIBLE :: DIAGNOSTIC;
    }

    else
    {
        visibility = TVISIBLE :: USUAL;
    }

    name = DefStringList -> Strings [1];
    Dim = getTDim (DefStringList -> Strings [2]);
    Default = DefStringList -> Strings [3];
    Min = DefStringList -> Strings [4];
    Max = DefStringList -> Strings [5];
    Description = DefStringList -> Strings [6];
    Units = DefStringList -> Strings [7];
    if (DefCRHM :: DefStringList -> Count > 8 && DefStringList -> Strings [8] == "Int")
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (DefCRHM :: DefStringList -> Count > 9)
    {
        nlay = Strtolong (DefStringList -> Strings [9]);
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclparam::Defdeclparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclvar :: Defdeclvar (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclvar::Defdeclvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    name = DefStringList -> Strings [1];
    Dim = getTDim (DefStringList -> Strings [2]);
    Description = DefStringList -> Strings [3];
    Units = DefStringList -> Strings [4];
    if (DefCRHM :: DefStringList -> Count > 5 && DefStringList -> Strings [5] == "Int")
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclvar::Defdeclvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdecldiag :: Defdecldiag (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdecldiag::Defdecldiag(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    name = DefStringList -> Strings [1];
    Dim = getTDim (DefStringList -> Strings [2]);
    Description = DefStringList -> Strings [3];
    Units = DefStringList -> Strings [4];
    if (DefCRHM :: DefStringList -> Count > 5 && DefStringList -> Strings [5] == "Int")
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdecldiag::Defdecldiag(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclstatvar :: Defdeclstatvar (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclstatvar::Defdeclstatvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    name = DefStringList -> Strings [1];
    Dim = getTDim (DefStringList -> Strings [2]);
    Description = DefStringList -> Strings [3];
    Units = DefStringList -> Strings [4];
    if (DefCRHM :: DefStringList -> Count > 5 && DefStringList -> Strings [5] == "Int")
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclstatvar::Defdeclstatvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdecllocal :: Defdecllocal (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdecllocal::Defdecllocal(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    name = DefStringList -> Strings [1];
    Dim = getTDim (DefStringList -> Strings [2]);
    Description = DefStringList -> Strings [3];
    Units = DefStringList -> Strings [4];
    if (DefCRHM :: DefStringList -> Count > 5 && DefStringList -> Strings [5] == "Int")
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdecllocal::Defdecllocal(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclobs :: Defdeclobs (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobs::Defdeclobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    string S = DefStringList -> Strings [1];
    string :: size_type Pos = S.find ("#");
    if (Pos == string :: npos)
    {
        S += "#";
    }

    else
    {
        S = S.substr (0, Pos + 1);
    }

    name = S;
    Dim = getTDim (DefStringList -> Strings [2]);
    Description = DefStringList -> Strings [3];
    Units = DefStringList -> Strings [4];
InstrumentLogger::instance()->log_instrument_log("</Defdeclobs::Defdeclobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclgetvar :: Defdeclgetvar (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclgetvar::Defdeclgetvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    module = DefStringList -> Strings [1];
    name = DefStringList -> Strings [2];
    Units = DefStringList -> Strings [3];
InstrumentLogger::instance()->log_instrument_log("</Defdeclgetvar::Defdeclgetvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclputvar :: Defdeclputvar (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputvar::Defdeclputvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    module = DefStringList -> Strings [1];
    name = DefStringList -> Strings [2];
    Units = DefStringList -> Strings [3];
InstrumentLogger::instance()->log_instrument_log("</Defdeclputvar::Defdeclputvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclputparam :: Defdeclputparam (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputparam::Defdeclputparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    module = DefStringList -> Strings [1];
    name = DefStringList -> Strings [2];
    Units = DefStringList -> Strings [3];
InstrumentLogger::instance()->log_instrument_log("</Defdeclputparam::Defdeclputparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclreadobs :: Defdeclreadobs (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclreadobs::Defdeclreadobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    name = DefStringList -> Strings [1];
    Dim = getTDim (DefStringList -> Strings [2]);
    Description = DefStringList -> Strings [3];
    Units = DefStringList -> Strings [4];
    if (DefCRHM :: DefStringList -> Count > 5)
    {
        HRU_OBS_indexed = Strtolong (DefStringList -> Strings [5]);
    }

    else
    {
        HRU_OBS_indexed = 0;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclreadobs::Defdeclreadobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
Defdeclobsfunc :: Defdeclobsfunc (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobsfunc::Defdeclobsfunc(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
    obs = DefStringList -> Strings [1];
    name = DefStringList -> Strings [2];
    typeFun = getTFunc (DefStringList -> Strings [3]);
InstrumentLogger::instance()->log_instrument_log("</Defdeclobsfunc::Defdeclobsfunc(ClassMacro * Macro_): DefCRHM (Macro_)@@@MacroUnit.cpp>");
}
void Defdeclparam :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclparam::CallDecl()@@@MacroUnit.cpp>");
    if (Int)
    {
        Macro -> declparam (name, Dim, Default, Min, Max, Description, Units, & fix_long_const, & fix2_long_const, nlay, visibility);
    }

    else
    {
        Macro -> declparam (name, Dim, Default, Min, Max, Description, Units, & fix_const, & fix2_const, Macro -> nhru, visibility);
    }

    if (Global :: BuildFlag == TBuild :: INIT)
    {
        FP = Macro -> vars.find (name);
        if (FP == Macro -> vars.end ())
        {
            Macro -> vars.insert (make_pair (name, VarCHRM ()));
            FP = Macro -> vars.find (name);
        }

        FP -> second.name = name;
        FP -> second.Ihh = 0;
        FP -> second.IndexMax = Macro -> nhru - 1;
        FP -> second.IndexMaxLay = Macro -> nhru - 1;
        FP -> second.Me = Macro;
        if (Int)
        {
            if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
            {
                FP -> second.kind = TV :: CRHMint2;
                FP -> second.ivalue2 = const_cast < long ** > (fix2_long_const);
            }

            else
            {
                FP -> second.kind = TV :: CRHMint;
                FP -> second.ivalue = const_cast < long * > (fix_long_const);
            }

        }

        else
        {
            if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
            {
                FP -> second.kind = TV :: CRHM2;
                FP -> second.value2 = const_cast < double ** > (fix2_const);
            }

            else
            {
                FP -> second.kind = TV :: CRHM;
                FP -> second.value = const_cast < double * > (fix_const);
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclparam::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclparam :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclparam::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Defdeclparam::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclvar :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclvar::CallDecl()@@@MacroUnit.cpp>");
    if (Int)
    {
        Macro -> declvar (name, Dim, Description, Units, & fix_long);
    }

    else
    {
        Macro -> declvar (name, Dim, Description, Units, & fix, & fix2);
    }

    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.Ill = 0;
    FP -> second.IndexMax = Global :: nhru - 1;
    FP -> second.IndexMaxLay = Macro -> nhru - 1;
    FP -> second.Me = Macro;
    if (Int)
    {
        FP -> second.kind = TV :: CRHMint;
        FP -> second.ivalue = const_cast < long * > (fix_long);
    }

    else
    if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
    {
        FP -> second.value2 = fix2;
        FP -> second.kind = TV :: CRHM2;
    }

    else
    {
        FP -> second.kind = TV :: CRHM;
        FP -> second.value = fix;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclvar::CallDecl()@@@MacroUnit.cpp>");
}
void Defdecldiag :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdecldiag::CallDecl()@@@MacroUnit.cpp>");
    if (Int)
    {
        Macro -> decldiag (name, Dim, Description, Units, & fix_long);
    }

    else
    {
        Macro -> decldiag (name, Dim, Description, Units, & fix, & fix2);
    }

    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.Ill = 0;
    FP -> second.IndexMax = Global :: nhru - 1;
    FP -> second.IndexMaxLay = Macro -> nhru - 1;
    FP -> second.Me = Macro;
    if (Int)
    {
        FP -> second.kind = TV :: CRHMint;
        FP -> second.ivalue = const_cast < long * > (fix_long);
    }

    else
    if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
    {
        FP -> second.value2 = fix2;
        FP -> second.kind = TV :: CRHM2;
    }

    else
    {
        FP -> second.kind = TV :: CRHM;
        FP -> second.value = fix;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdecldiag::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclstatvar :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclstatvar::CallDecl()@@@MacroUnit.cpp>");
    if (Int)
    {
        Macro -> declstatvar (name, Dim, Description, Units, & fix_long);
    }

    else
    {
        Macro -> declstatvar (name, Dim, Description, Units, & fix);
    }

    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.Ill = 0;
    FP -> second.IndexMax = Global :: nhru - 1;
    FP -> second.IndexMaxLay = Macro -> nhru - 1;
    FP -> second.Me = Macro;
    if (Int)
    {
        FP -> second.kind = TV :: CRHMint;
        FP -> second.ivalue = const_cast < long * > (fix_long);
    }

    else
    if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
    {
        FP -> second.value2 = fix2;
        FP -> second.kind = TV :: CRHM2;
    }

    else
    {
        FP -> second.kind = TV :: CRHM;
        FP -> second.value = fix;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclstatvar::CallDecl()@@@MacroUnit.cpp>");
}
void Defdecllocal :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdecllocal::CallDecl()@@@MacroUnit.cpp>");
    if (Int)
    {
        Macro -> decllocal (name, Dim, Description, Units, & fix_long);
    }

    else
    {
        Macro -> decllocal (name, Dim, Description, Units, & fix);
    }

    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.Ill = 0;
    FP -> second.IndexMax = Global :: nhru - 1;
    FP -> second.IndexMaxLay = Macro -> nhru - 1;
    FP -> second.Me = Macro;
    if (Int)
    {
        FP -> second.kind = TV :: CRHMint;
        FP -> second.ivalue = const_cast < long * > (fix_long);
    }

    else
    if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
    {
        FP -> second.value2 = fix2;
        FP -> second.kind = TV :: CRHM2;
    }

    else
    {
        FP -> second.kind = TV :: CRHM;
        FP -> second.value = fix;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdecllocal::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclgetvar :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclgetvar::CallDecl()@@@MacroUnit.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar = NULL;
    long GetUnit;
    GetUnit = Macro -> FindWildVarFloat (name, thisVar);
    if (Global :: thisVar != NULL && ((ClassVar *) Global :: thisVar) -> varType == TVar :: Int)
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (Int)
    {
        Macro -> declgetvar (module, name, Units, & fix_long_const, & fix2_long_const);
    }

    else
    {
        Macro -> declgetvar (module, name, Units, & fix_const, & fix2_const);
    }

    if (Global :: BuildFlag == TBuild :: INIT)
    {
        FP = Macro -> vars.find (name);
        if (FP == Macro -> vars.end ())
        {
            Macro -> vars.insert (make_pair (name, VarCHRM ()));
            FP = Macro -> vars.find (name);
        }

        FP -> second.name = name;
        FP -> second.Ihh = 0;
        FP -> second.Ill = 0;
        FP -> second.IndexMax = Macro -> nhru - 1;
        FP -> second.IndexMaxLay = Macro -> nhru - 1;
        FP -> second.Me = Macro;
        if (Int)
        {
            if (((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEF || ((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEFN)
            {
                FP -> second.kind = TV :: CRHMint2;
                FP -> second.ivalue2 = const_cast < long ** > (fix2_long_const);
            }

            else
            {
                FP -> second.kind = TV :: CRHMint;
                FP -> second.ivalue = const_cast < long * > (fix_long_const);
            }

        }

        else
        {
            if (Global :: thisVar != NULL && (((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEF || ((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEFN))
            {
                FP -> second.kind = TV :: CRHM2;
                FP -> second.value2 = const_cast < double ** > (fix2_const);
            }

            else
            {
                FP -> second.kind = TV :: CRHM;
                FP -> second.value = const_cast < double * > (fix_const);
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclgetvar::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclputvar :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputvar::CallDecl()@@@MacroUnit.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar = NULL;
    long GetUnit;
    GetUnit = Macro -> FindWildVarFloat (name, thisVar);
    if (Global :: thisVar != NULL && ((ClassVar *) Global :: thisVar) -> varType == TVar :: Int)
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (Int)
    {
        Macro -> declputvar (module, name, Units, & fix_long);
    }

    else
    {
        Macro -> declputvar (module, name, Units, & fix, & fix2);
    }

    if (Global :: BuildFlag == TBuild :: INIT)
    {
        FP = Macro -> vars.find (name);
        if (FP == Macro -> vars.end ())
        {
            Macro -> vars.insert (make_pair (name, VarCHRM ()));
            FP = Macro -> vars.find (name);
        }

        FP -> second.name = name;
        FP -> second.Ihh = 0;
        FP -> second.Ill = 0;
        FP -> second.IndexMax = Macro -> nhru - 1;
        FP -> second.IndexMaxLay = Macro -> nhru - 1;
        FP -> second.Me = Macro;
        if (Int)
        {
            FP -> second.kind = TV :: CRHMint;
            FP -> second.ivalue = const_cast < long * > (fix_long);
        }

        else
        if (Global :: thisVar != NULL && (((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEF || ((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEFN))
        {
            FP -> second.kind = TV :: CRHM2;
            FP -> second.value2 = const_cast < double ** > (fix2);
        }

        else
        {
            FP -> second.kind = TV :: CRHM;
            FP -> second.value = const_cast < double * > (fix);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclputvar::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclputparam :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputparam::CallDecl()@@@MacroUnit.cpp>");
    MapPar :: iterator itPar;
    ClassPar * thisPar = NULL;
    int GetUnit;
    GetUnit = Macro -> FindWildParFloat (name, thisPar, false, false);
    if (thisPar != NULL && thisPar -> varType == TVar :: Int)
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (Int)
    {
        Macro -> declputparam (module, name, Units, & fix_long);
    }

    else
    {
        Macro -> declputparam (module, name, Units, & fix, & fix2);
    }

    if (Global :: BuildFlag == TBuild :: INIT)
    {
        FP = Macro -> vars.find (name);
        if (FP == Macro -> vars.end ())
        {
            Macro -> vars.insert (make_pair (name, VarCHRM ()));
            FP = Macro -> vars.find (name);
        }

        FP -> second.name = name;
        FP -> second.Ihh = 0;
        FP -> second.Ill = 0;
        FP -> second.IndexMax = Macro -> nhru - 1;
        FP -> second.IndexMaxLay = Macro -> nhru - 1;
        FP -> second.Me = Macro;
        if (Int)
        {
            FP -> second.kind = TV :: CRHMint;
            FP -> second.ivalue = const_cast < long * > (fix_long);
        }

        else
        if (thisPar != NULL && (thisPar -> dimen == TDim :: NDEF || thisPar -> dimen == TDim :: NDEFN))
        {
            FP -> second.kind = TV :: CRHM2;
            FP -> second.value2 = const_cast < double ** > (fix2);
        }

        else
        {
            FP -> second.kind = TV :: CRHM;
            FP -> second.value = const_cast < double * > (fix);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclputparam::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclobs :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobs::CallDecl()@@@MacroUnit.cpp>");
    long cnt = Macro -> declobs (Macro -> Name, name, Dim, Description, Units, & fix);
    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    if (fix)
    {
        FP -> second.kind = TV :: CRHM;
    }

    else
    {
        FP -> second.kind = TV :: NOP;
    }

    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = cnt;
    FP -> second.value = fix;
    FP -> second.Me = Macro;
InstrumentLogger::instance()->log_instrument_log("</Defdeclobs::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclobs :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobs::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    for (int hh = 0; hh <= FP -> second.IndexMax; ++ hh) {
        FP -> second.Ihh = hh;
        FP -> second.put (0.0);
    }
InstrumentLogger::instance()->log_instrument_log("</Defdeclobs::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclvar :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
    for (int hh = 0; hh <= FP -> second.IndexMax; ++ hh) {
        FP -> second.Ihh = hh;
        FP -> second.put (0.0);
    }
InstrumentLogger::instance()->log_instrument_log("</Defdeclvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdecldiag :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdecldiag::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
    for (int hh = 0; hh <= FP -> second.IndexMax; ++ hh) {
        FP -> second.Ihh = hh;
        FP -> second.put (0.0);
    }
InstrumentLogger::instance()->log_instrument_log("</Defdecldiag::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclstatvar :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclstatvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
    for (int hh = 0; hh <= FP -> second.IndexMax; ++ hh) {
        FP -> second.Ihh = hh;
        FP -> second.put (0.0);
    }
InstrumentLogger::instance()->log_instrument_log("</Defdeclstatvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdecllocal :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdecllocal::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
    for (int hh = 0; hh <= FP -> second.IndexMax; ++ hh) {
        FP -> second.Ihh = hh;
        FP -> second.put (0.0);
    }
InstrumentLogger::instance()->log_instrument_log("</Defdecllocal::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclgetvar :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclgetvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
InstrumentLogger::instance()->log_instrument_log("</Defdeclgetvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclputvar :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
InstrumentLogger::instance()->log_instrument_log("</Defdeclputvar::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclputparam :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputparam::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
    FP -> second.IndexMax = nhru - 1;
InstrumentLogger::instance()->log_instrument_log("</Defdeclputparam::CallInit(long nhru, long nlay)@@@MacroUnit.cpp>");
}
void Defdeclreadobs :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclreadobs::CallDecl()@@@MacroUnit.cpp>");
    long cnt = Macro -> declreadobs (name, Dim, Description, Units, & fix_const, HRU_OBS_indexed);
    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.kind = TV :: CRHM;
    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = cnt;
    FP -> second.value = const_cast < double * > (fix_const);
    FP -> second.Me = Macro;
InstrumentLogger::instance()->log_instrument_log("</Defdeclreadobs::CallDecl()@@@MacroUnit.cpp>");
}
void Defdeclobsfunc :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobsfunc::CallDecl()@@@MacroUnit.cpp>");
    long cnt = Macro -> declobsfunc (obs, name, & fix, typeFun);
    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.kind = TV :: CRHM;
    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = cnt;
    FP -> second.value = fix;
    FP -> second.Me = Macro;
InstrumentLogger::instance()->log_instrument_log("</Defdeclobsfunc::CallDecl()@@@MacroUnit.cpp>");
}
long ClassMacro :: declobs (string module, string name, TDim dimen, string help, string units, double ** value)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
    MapVar :: iterator itVar;
    ClassVar * newVar;
    ClassVar * thisVar;
    int cnt = getdim (dimen);
    Convert convert;
    convert.CheckUnitsString (Name, name, units);
    switch (Global :: BuildFlag) {
    case TBuild :: BUILD:
        {
            PairstrV Item2 = PairstrV (name, variation_set);
            PairstrI Item = PairstrI (module, Item2);
            Global :: Mapdeclvar.insert (Item);
            Global :: Mapdeclobs.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
            return (- 1);
        }
    case TBuild :: DECL:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + name)) != Global :: MapVars.end ())
            {
                thisVar = (* itVar).second;
                if (thisVar -> dim < cnt)
                {
                    thisVar -> ReleaseM ();
                    thisVar -> dim = cnt;
                    if (thisVar -> lay > 0)
                    {
                        thisVar -> layvalues = new double * [thisVar -> lay];
                        for (int ii = 0; ii < thisVar -> lay; ii ++)
                            thisVar -> layvalues [ii] = new double [cnt];
                    }

                    thisVar -> values = new double [cnt];
                }

                thisVar -> dimen = dimen;
                thisVar -> module = module;
                thisVar -> DLLName = DLLName;
                thisVar -> root = ID;

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
                return (- 1);
            }

            newVar = new ClassVar ("obs", name, cnt, 0, NULL);
            newVar -> varType = TVar :: Float;
            newVar -> help = help;
            newVar -> units = units;
            newVar -> module = module;
            newVar -> DLLName = DLLName;
            newVar -> root = ID;
            newVar -> values = new double [cnt];
            PairVar Item = PairVar ("obs " + name, newVar);
            Global :: MapVars.insert (Item);
            Item = PairVar (Name + " " + name, newVar);
            Global :: MapVars.insert (Item);

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
            return (- 1);
        }
    case TBuild :: INIT:
        {
            if ((itVar = Global :: MapVars.find (Name + " " + name)) != Global :: MapVars.end ())
            {
                newVar = (* itVar).second;
                if (newVar -> FileData)
                {
                    * value = NULL;

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
                    return (- (newVar -> cnt - 1));
                }

                else
                {
                    * value = newVar -> values;
                    newVar -> cnt = cnt;
                    LogError (CRHMException (" macro module '" + module + "' creating declared observation: '" + name + "'", TExcept :: WARNING));

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
                    return (newVar -> cnt - 1);
                }

            }

            else
            {
                CRHMException Except ("observation not found: " + module + " " + name, TExcept :: TERMINATE);
                LogError (Except);
                throw Except;
            }

        }
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double ** value)@@@MacroUnit.cpp>");
}
string Add_Quote (string s)
{
InstrumentLogger::instance()->log_instrument_log("<Add_Quote(string s)@@@MacroUnit.cpp>");
    string :: size_type pos, here;
    for (pos = 0; pos < s.size (); ++ pos) {
        here = s.find_first_of ('\"', pos);
        if (here == string :: npos)
        {
            break;
        }

        else
        {
            if (s [++ here] != '\'')
            {
                s.insert (here, "'");
            }

            here = s.find_first_of ('\"', here);
            if (s [here - 1] != '\'')
            {
                s.insert (here, "'");
            }

            pos = here + 1;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Add_Quote(string s)@@@MacroUnit.cpp>");
    return s;
InstrumentLogger::instance()->log_instrument_log("</Add_Quote(string s)@@@MacroUnit.cpp>");
}