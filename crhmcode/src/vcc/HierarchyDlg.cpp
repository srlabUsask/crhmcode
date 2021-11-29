#include "HierarchyDlg.h"

IMPLEMENT_DYNAMIC(HierarchyDlg, CDialog)

HierarchyDlg::HierarchyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(ID_HIERARCHY_DLG, pParent)
{
}

HierarchyDlg::~HierarchyDlg()
{
}

void HierarchyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_HIERARCHY_CHECK, hierarchyCheck);
	DDX_Control(pDX, ID_HIERARCHY_LIST, hierarchyList);
}

BEGIN_MESSAGE_MAP(HierarchyDlg, CDialog)

END_MESSAGE_MAP()

BOOL HierarchyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    Hierarchy1Click();

    return true;
}

void HierarchyDlg::Hierarchy1Click()
{
    ClassModule * thisModule;
    ClassMacro * thisMacro;
    long Variation;

    this->hierarchyList.ResetContent();
    this->hierarchyCheck.ResetContent();

    //Label1->Caption = "hierarchy";
    //Label1->Tag = 0;

    HierarchyList();



    for (
        static std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
        it != Global::OurModulesList->end();
        it++) 
    {
        std::string S = it->first;
        //long Indx = Global::AllModulesList->find(S);
        thisModule = it->second;
        if (thisModule->DLLName == "Macro") 
        {
            thisMacro = dynamic_cast<ClassMacro*> (thisModule);
            
            if (thisModule->isGroup) 
            {
                hierarchyList.AddString(L"");
                hierarchyList.AddString(CString(S.c_str()));
                hierarchyList.AddString(L"");
                hierarchyCheck.AddString(L" ");
                hierarchyCheck.AddString(CString(S.c_str()));
                hierarchyCheck.AddString(L" ");

                std::list<std::pair<std::string, ClassModule*>> * GrpModuleList = new std::list<std::pair<std::string, ClassModule*>>();
                std::list<std::pair<std::string, ClassModule*>> * TempModuleList = new std::list<std::pair<std::string, ClassModule*>>();
                long * Oldvariation = new long[thisMacro->GrpStringList->size()];

                for (size_t ii = 0; ii < thisMacro->GrpStringList->size(); ii++) 
                {
                    GrpModuleList->push_back(thisMacro->GrpStringList->at(ii));
                }

                int loopCount = 0;
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator ii = GrpModuleList->begin();
                    ii != GrpModuleList->end();
                    ii++
                    )
                {
                    int Pos = ii->first.find("#");
                    if (Pos) 
                    {
                        Variation = pow(2, ii->first[Pos + 1] - char('1'));
                        ii->first = ii->first.substr(1, Pos - 1);
                    }
                    else
                    {
                        Variation = 0;
                    }

                    std::map<std::string, ClassModule*>::iterator jj = Global::AllModulesList->find(ii->first);

                    if (jj != Global::AllModulesList->end()) // Update group Module address
                    { 
                        ii->second = jj->second;
                        ClassModule* thisModule = ii->second;
                        Oldvariation[loopCount] = thisModule->variation; // save original variation
                        thisModule->variation = Variation;
                    }
                    loopCount++;
                }

                Global::Mapgetvar.clear();
                Global::Mapputvar.clear();
                Global::Mapreadvar.clear();
                Global::Mapdeclvar.clear();
                Global::Mapdeclstat.clear();
                Global::Mapdeclpar.clear();
                Global::Mapdeclobs.clear();

                Global::BuildFlag = TBuild::BUILD; // default value

                TempModuleList->assign(Global::OurModulesList->begin(), Global::OurModulesList->end());
                Global::OurModulesList->assign(GrpModuleList->begin(), GrpModuleList->end());

                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator ii = Global::OurModulesList->begin();
                    ii != Global::OurModulesList->end();
                    ii++
                    )
                {
                    ii->second->decl();
                }


                HierarchyList();

                int loopCount2 = 0;
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator ii = GrpModuleList->begin();
                    ii != GrpModuleList->end();
                    ii++
                    )
                {
                    ClassModule* thisModule = ii->second;
                    thisModule->variation = Oldvariation[loopCount2]; // restore original variation
                    loopCount2++;
                }

                Global::OurModulesList->assign(TempModuleList->begin(), TempModuleList->end());

                Global::Mapgetvar.clear();
                Global::Mapputvar.clear();
                Global::Mapreadvar.clear();
                Global::Mapdeclvar.clear();
                Global::Mapdeclstat.clear();
                Global::Mapdeclpar.clear();
                Global::Mapdeclobs.clear();


                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator ii = Global::OurModulesList->begin();
                    ii != Global::OurModulesList->end();
                    ii++
                    )
                {
                    ii->second->decl();
                }

                Global::BuildFlag = TBuild::DECL; // model loaded

                delete GrpModuleList;
                delete TempModuleList;
                delete[] Oldvariation;

            } // isGroup
        }
    }
}


void HierarchyDlg::HierarchyList()
{
    std::string S, SS, S1, S2, Entry;
    bool Self;
    long offset, Act_ii, List_start;
    std::pair<std::string, ClassModule*> * Indx = NULL;
    offset = hierarchyList.GetCount();

    pair<Mapstr::iterator, Mapstr::iterator> range;
    Mapstr::iterator itMap;

    int Twos;
    

    for (
        std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
        it != Global::OurModulesList->end();
        it++
        ) 
    {
        ClassModule * thisModule = it->second;
        long Variation = thisModule->variation;
        std::string S = it->first;

        if (thisModule->DLLName == "Macro")
        {
            Expand_Grp_to_OurModuleList(it->first, it->second); // Changes OurModulelist to GrpStringList, calls decl and then restores current OurModulelist
        }

        std::string AA = "";
        if (Variation) 
        {
            AA = "#0";
            AA[1] += log(thisModule->variation) / log(2) + 1;
        }



        std::string stringToAdd = S + AA;
        CString textToAdd(stringToAdd.c_str());
        this->hierarchyList.AddString(textToAdd);

        Act_ii = this->hierarchyList.GetCount() - 1;

        if (!thisModule->PeerVar.empty()) 
        {
            S1 = thisModule->NameRoot.c_str(); // module
            S2 = thisModule->PeerVar.c_str(); // variable

            Indx = findvar(S, S2, Self);

            if (Indx != NULL) 
            {
                std::pair<std::string, ClassModule*> * Indx2 = findstatvar(S, S2, Self);

                Entry = S + " " + Indx->first + "->" + S2 + " *** Peer Variable";
                if (Indx2 == NULL) 
                { // not state variable
                    //int Twos = (int)ListBox1->Items->Objects[Act_ii];
                    //hierarchyList.find
                    int i = 0;
                    //int Or = Twos | long(powl(2, Indx));
                    //(TObject*)ListBox1->Items->Objects[Act_ii] = (TObject*)(Or);
                }
                else
                {
                    Entry = Entry + " *** Peer Variable";
                }

                hierarchyCheck.AddString(CString(Entry.c_str()));

            }
        }

        range = Global::Mapgetvar.equal_range(S);
        for (itMap = range.first; itMap != range.second; ++itMap) 
        {

            SS = itMap->second.first;
            int jj = SS.find(" ");
            S1 = SS.substr(1, jj - 1); // module
            S2 = SS.substr(jj + 1, SS.length() - jj); // variable
            if (S1 == "*") 
            {
                Indx = findvar(S, S2, Self);
            }
            else
            {
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                    it != Global::OurModulesList->end();
                    it++
                    )
                {
                    if (S1 == it->first)
                    {
                        Indx = new std::pair<std::string, ClassModule*>(it->first, it->second);
                    }
                }
            }

            if (Indx != NULL) 
            {
                std::pair<std::string, ClassModule*> * Indx2 = findstatvar(S, S2, Self);
                Entry = S + " " + itMap->second.first + " from " + Indx->first;
                if (Indx2 == NULL) // not state variable
                { 
                    int i = 0;
                    //int Twos = (int)ListBox1->Items->Objects[Act_ii];

                    //int Or = Twos | long(powl(2, Indx));
                    //(TObject*)ListBox1->Items->Objects[Act_ii] = (TObject*)(Or);
                }
                else
                {
                    Entry = Entry + " *** State Variable";
                }

                hierarchyCheck.AddString(CString(Entry.c_str()));
            }
        } // for

        range = Global::Mapputvar.equal_range(S);
        for (itMap = range.first; itMap != range.second; ++itMap) 
        {
            SS = itMap->second.first;
            int jj = SS.find(" ");
            S1 = SS.substr(1, jj - 1); // module
            S2 = SS.substr(jj + 1, SS.length() - jj); // variable
            if (S1 == "*") 
            {
                Indx = findvar(S, S2, Self);
            }
            else
            {
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                    it != Global::OurModulesList->end();
                    it++
                    )
                {
                    if (S1 == it->first)
                    {
                        Indx = new std::pair<std::string, ClassModule*>(it->first, it->second);
                    }
                }
            }

            if (Indx != NULL) // otherwise in group
            {
                std::string textString = S + " " + itMap->second.first + " from " + Indx->first + " *** Put";
                hierarchyCheck.AddString(CString(textString.c_str()));
            }
        }
    } // for

    bool OK = true;

    int ii = 0;
    for (
        std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
        it != Global::OurModulesList->end();
        it++
        )
    {
        int i = 0;
        //int Twos = (int)ListBox1->Items->Objects[ii + offset];
        int Twos = 0;
        int N = powl(2, ii);
        if (Twos > N)
        {
            OK = false;
        }

        char P[80];
        //strcpy(P, ListBox1->Items->Strings[ii + offset].c_str());

        //TVarRec args[3] = { N, P, Twos };

        //std::string X = Format("%6d  %-30s  %-8d", args, 2);

        //ListBox1->Items->Strings[ii + offset] = X;
        
        ii++;
    }

    hierarchyList.AddString(CString(" "));
    if (OK)
    {
        hierarchyList.AddString(L"Module order is good");
    }
    else
    {
        hierarchyList.AddString(L"Module Order is not correct");
    }


}

void HierarchyDlg::Expand_Grp_to_OurModuleList(std::string moduleName, ClassModule * module) 
{

    ClassModule* thisModule;
    ClassMacro* thisMacro;
    long Variation;

    std::string S = moduleName;
    thisModule = module;
    thisMacro = dynamic_cast<ClassMacro*> (thisModule);

    if (thisMacro->GrpStringList == NULL || thisMacro->GrpStringList->size() <= 0)
    {
        return; // uses no modules
    }

    std::list<std::pair<std::string, ClassModule *>> * GrpModuleList = new std::list<std::pair<std::string,ClassModule*>>();
    std::vector<std::pair<std::string, ClassModule*>>* TempModuleList = new std::vector<std::pair<std::string, ClassModule*>>();
    long * Oldvariation = new long[thisMacro->GrpStringList->size()];

    for (size_t ii = 0; ii < thisMacro->GrpStringList->size(); ii++) 
    {
        GrpModuleList->push_back(thisMacro->GrpStringList->at(ii));
    }

    int ii = 0;
    for (
        std::list<std::pair<std::string, ClassModule*>>::iterator grpModuleListIt = GrpModuleList->begin();
        grpModuleListIt != GrpModuleList->end();
        grpModuleListIt++
        ) 
    {
        int Pos = grpModuleListIt->first.find_first_of("#");
        if (Pos) 
        {
            Variation = pow(2, grpModuleListIt->first[Pos + 1] - char('1'));
            grpModuleListIt->first = grpModuleListIt->first.substr(1, Pos - 1);
        }
        else
        {
            Variation = 0;
        }

        std::map<std::string, ClassModule* >::iterator jj = Global::AllModulesList->find(grpModuleListIt->first);

        if (jj != Global::AllModulesList->end()) 
        { // Update group Module address
            grpModuleListIt->second = jj->second;
            ClassModule* thisModule = (ClassModule*)grpModuleListIt->second;
            Oldvariation[ii] = thisModule->variation; // save original variation
            thisModule->variation = Variation;
        }
        ii++;
    }

    Global::Mapgetvar.clear();
    Global::Mapputvar.clear();
    Global::Mapreadvar.clear();
    Global::Mapdeclvar.clear();
    Global::Mapdeclstat.clear();
    Global::Mapdeclpar.clear();
    Global::Mapdeclobs.clear();

    Global::BuildFlag = TBuild::BUILD; // default value

    TempModuleList->assign(Global::OurModulesList->begin(), Global::OurModulesList->end());
    Global::OurModulesList->assign(GrpModuleList->begin(), GrpModuleList->end());


    for (
        std::list<std::pair<std::string, ClassModule*>>::iterator ourModListIt = Global::OurModulesList->begin();
        ourModListIt != Global::OurModulesList->end();
        ourModListIt++
        )
    {
        ourModListIt->second->decl();
    }

    for (
        std::list<std::pair<std::string, ClassModule*>>::iterator grpModListIt = GrpModuleList->begin();
        grpModListIt != GrpModuleList->end();
        grpModListIt++
        )
    {
        ClassModule* thisModule = grpModListIt->second;
        thisModule->variation = Oldvariation[ii]; // restore original variation
    }

    Global::OurModulesList->assign(TempModuleList->begin(), TempModuleList->end());

    Global::Mapgetvar.clear();
    Global::Mapputvar.clear();
    Global::Mapreadvar.clear();
    Global::Mapdeclvar.clear();
    Global::Mapdeclstat.clear();
    Global::Mapdeclpar.clear();
    Global::Mapdeclobs.clear();

    Global::BuildFlag = TBuild::DECL; // model loaded

    delete GrpModuleList;
    delete TempModuleList;
    delete[] Oldvariation;
}


std::pair<std::string, ClassModule*> * HierarchyDlg::findvar(std::string who, std::string what, bool& Self)
{
    Mapstr::iterator itMap;
    int Pos;
    std::string S1, S2;
    std::list<std::pair<std::string, ClassModule*>>::iterator GrpSrc = Global::OurModulesList->end();

    for (itMap = Global::Mapdeclvar.begin(); itMap != Global::Mapdeclvar.end(); ++itMap) 
    {
        if (itMap->second.first == what) // root variable
        {  
            if (itMap->first == who) 
            {
                Self = true;
                return NULL;
            }
            else
            {
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                    it != Global::OurModulesList->end();
                    it++
                    )
                {
                    if (itMap->first == it->first)
                    {
                        return new std::pair<std::string, ClassModule*>(it->first, it->second);
                    }
                }
                
            }
        }
    }

    for (itMap = Global::Mapdeclvar.begin(); itMap != Global::Mapdeclvar.end(); ++itMap) 
    {
        Pos = what.find("@");
        if (Pos != std::string::npos) // remove @... from module rquiring input
        { 
            S1 = what.substr(1, Pos - 1);
            if (itMap->second.first == S1)
            {
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                    it != Global::OurModulesList->end();
                    it++
                    )
                {
                    if (itMap->first == it->first)
                    {
                        return new std::pair<std::string, ClassModule*>(it->first, it->second);
                    }
                }
            }
        }
        else
        {
            S1 = what;
        }

        Pos = itMap->second.first.find("@");
        if (Pos = std::string::npos) // remove @... from possible source module
        { 
            S2 = itMap->second.first.substr(1, Pos - 1);
            if (S1 == S2) 
            {
                if (itMap->second.first == what)
                {
                    for (
                        std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                        it != Global::OurModulesList->end();
                        it++
                        )
                    {
                        if (itMap->first == it->first)
                        {
                            return new std::pair<std::string, ClassModule*>(it->first, it->second);
                        }
                    }
                }
                else
                {
                    for (
                        std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                        it != Global::OurModulesList->end();
                        it++
                        )
                    {
                        if (itMap->first == it->first)
                        {
                            GrpSrc = it;
                        }
                    }
                }
            }
        }
    }

    if (GrpSrc != Global::OurModulesList->end())
    {
        return new std::pair<std::string, ClassModule*>(GrpSrc->first, GrpSrc->second);
    }
    else
    {
        return NULL;
    }
}


std::pair<std::string, ClassModule*> * HierarchyDlg::findstatvar(std::string who, std::string what, bool &Self)
{
    Mapstr::iterator itMap;
    int Pos;
    std::string S1, S2;

    for(itMap = Global::Mapdeclstat.begin(); itMap !=  Global::Mapdeclstat.end(); ++itMap) 
    {
        std::string SS = itMap->second.first;
        int jj = SS.find(" ");
        std::string S2 = SS.substr(jj+1, SS.length() - jj); // variable
        if(S2 == what)
        {
            if (itMap->first == who)
            {
                Self = true;
            }
            else
            {
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                    it != Global::OurModulesList->end();
                    it++
                    )
                {
                    if (itMap->first == it->first)
                    {
                        return new std::pair<std::string, ClassModule*>(it->first, it->second);
                    }
                }

            }
        }

        if(Pos = what.find("@"))
        {
            S1 = what.substr(1, Pos-1);
            if (S2 == S1)
            {
                for (
                    std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
                    it != Global::OurModulesList->end();
                    it++
                    )
                {
                    if (itMap->first == it->first)
                    {
                        return new std::pair<std::string, ClassModule*>(it->first, it->second);
                    }
                }
            }
        }
    }
  
    return NULL;
}
