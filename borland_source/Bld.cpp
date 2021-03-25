// 06/23/16
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Bld.h"
#include "CRHMmain.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include "MacroUnit.h"
#include "Para.h"
#include <vector>
#include <algorithm>
#include <sstream>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TBldForm *BldForm;

extern string AKAstrings[];

String LVLStrings[] = {"BASIC", "MACRO", "ADVANCED", "SUPPORT", "CUSTOM", "PROTOTYPE", "OBSOLETE"};

using namespace std;

bool ModifyBuild = false;

class ClassEntry {
public:
  unsigned long OrigPos; // ListBox2 initial index
  long rank;             // rank bit: highest = 0
  bool used;
  String Name;           // module name
  ClassModule *module;   // pointer for module

  ClassEntry() : Name(""), OrigPos(0), rank(0), module(NULL) {};
  ClassEntry(String Name, ClassModule *module, int OrigPos_) : Name(Name), module(module), OrigPos(OrigPos_), rank(0) {};
  ClassEntry(const ClassEntry & Cl);
  ClassEntry & operator=(const ClassEntry & Cl);

  friend bool operator<(const ClassEntry &x, const ClassEntry &y);
};

bool operator<(const ClassEntry &x, const ClassEntry &y) {
  return x.rank < y.rank;
}

ClassEntry::ClassEntry(const ClassEntry & Cl) {
  OrigPos = Cl.OrigPos;
  rank = Cl.rank;
  used = Cl.used;
  Name = Cl.Name;
  module = Cl.module;
}

ClassEntry & ClassEntry::operator=(const ClassEntry & Cl) {
  if (this == &Cl) return *this;
  OrigPos = Cl.OrigPos;
  rank = Cl.rank;
  used = Cl.used;
  Name = Cl.Name;
  module = Cl.module;
  return *this;
}

void  MoveDown(vector<ClassEntry> &Entries, long to, long from){ // move 'from' downto 'to'
  ClassEntry Temp = Entries[from]; // save 'from'

  for(int jj = from; jj > to; --jj)
    Entries[jj] = Entries[jj-1]; // move entries up to fill space

  Entries[to] = Temp; // save 'from' to 'to'
}

vector<ClassEntry> Entries;

//---------------------------------------------------------------------------
__fastcall TBldForm::TBldForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBldForm::FormActivate(TObject *Sender)
{
  StatusBar1->SimpleText = "";
  StatusBar1->SimplePanel = true;

  ListBox1->Clear();
  ListBox1->Sorted = false;

  Memo1->Lines->Clear();
  
  Max_Name_Width1 = 0;
  Max_Name_Width2 = 0;

  for(int ii = 0; ii < CheckListBox1->Count; ++ii)
    CheckListBox1->Checked[ii] = false;

  Label3->Caption = "";

  MapAKACopy = Global::MapAKA; // save AKA to restore if no rebuild

  AKAselectiveDelete(Sender); // deletes all AKAs but "OBSR" and "OBSF"  

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclstat.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  CRHM::TBuild TempB = Global::BuildFlag;
  Global::BuildFlag = CRHM::BUILD; // default value

  for(int ii = 0; ii < Global::AllModulesList->Count; ++ii){
    ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[ii];
    thisModule->variation_max = 0;

    long Temp = thisModule->variation;
    long Temp2 = thisModule->variation_set;
    thisModule->variation_set = 0;
    thisModule->variation = 0;
    thisModule->decl();
    thisModule->variation = Temp;
    thisModule->variation_set = Temp2;

    if(thisModule->variation > 0)
      thisModule->hh = log(thisModule->variation)/log(2) + 1; // set to current variation
    else
      thisModule->hh = 0;
  }

  Global::OBS_AS_IS = 0; // Quinton module sets it
  Global::WQ_prj = false; // Set for WQ project
  ListBox2->Clear();

  if(Global::OurModulesList->Count)
    ModifyBuild = true;
  else{
    ModifyBuild = false;
    CheckListBox1->Checked[CRHM::BASIC] = true;
  }

  for(int ii = 0 ; ii < Global::OurModulesList->Count; ++ii){ // fill ListBox2
    CheckListBox1->Checked[((ClassModule*) Global::OurModulesList->Objects[ii])->Lvl] = true;
    ListBox2->Items->AddObject(Global::OurModulesList->Strings[ii], (TObject *) Global::OurModulesList->Objects[ii]);
    SetSuffix(ii);
    String S = Global::OurModulesList->Strings[ii];
    if(S.Length() > 33 && S.Length() > Max_Name_Width2) // 198 pixels roughly 33 caharacters
      Max_Name_Width2 = S.Length();
  }
  ListBox2->ScrollWidth =  Max_Name_Width2*6;

  Execute = false;

  for(int ii = 0 ; ii < Global::AllModulesList->Count; ++ii ) // fill ListBox1 from all levels used
    if(CheckListBox1->Checked[((ClassModule*) Global::AllModulesList->Objects[ii])->Lvl] == true){
      ListBox1->Items->AddObject(Global::AllModulesList->Strings[ii], (TObject *) Global::AllModulesList->Objects[ii]);
      String S = Global::AllModulesList->Strings[ii];
      if(S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
        Max_Name_Width1 = S.Length();
    }
  ListBox1->ScrollWidth =  Max_Name_Width1*6;
  Global::BuildFlag = TempB;

  UpDownMAXHRU->Max = MAXHRU;
  UpDownMAXHRU->Position = Global::maxhru;
  LabelMAXHRU->Caption = "MAXHRU = " + String(UpDownMAXHRU->Position);

  UpDownMAXLAY->Max = MAXLAY;
  UpDownMAXLAY->Position = Global::maxlay;
  LabelMAXLAY->Caption = "MAXLAY = " + String(UpDownMAXLAY->Position);
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::RemoveParameter(TObject *Sender) {

  MapPar::iterator itPar;
  ClassPar *thisPar;

  for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end();){
    thisPar = (*itPar).second;

    int kk = IndexOf(ListBox2, thisPar->module.c_str());

    if(kk == -1 && thisPar->module != "shared") {  // was basin
      Global::MapPars.erase(itPar++);
      delete thisPar;
    }
    else {
      ++itPar;
    }
  }

}
//---------------------------------------------------------------------------

void __fastcall TBldForm::BitBtn2Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::DisplayModule(String S, ClassModule* thisModule, bool LBox1) {
  Mapstr::iterator itMap, pos, pos2;

  int indx;
  String SS, S1, S2;
  TGridOptions OurOptions;

  MapVar::iterator itVar;

  long Variation = 0;
  long Vindx = 0;
  int P;

  SS = S;
  if(P = S.Pos("#"), P > 0){ // remove any suffix
    Vindx = S[P+1] - char('0');
    Variation = pow(2, S[P+1] - char('1'));
    S = S.Delete(S.Length()-1, 2);
  }
    else
      Variation = 0;
      
  if(!thisModule->Description.IsEmpty()){
    TStringList* Fred = new TStringList;
    Fred->QuoteChar = '\'';
    Fred->DelimitedText = thisModule->Description;
    if(thisModule->variation_max > 0) // if variation skip overview
      ++Vindx;

    if(LBox1){ // write it all out
      for(int ii = 0; ii < Fred->Count; ++ii){
        S1 = S;
        if(ii == 0)
          S1 += " Function summary";
        else if(ii > 1)
          S1 += "#" + String(ii-1);
        else
          S1 += "  ";

        S1 += " -> " + Fred->Strings[ii];
        Memo1->Lines->Add(S1);
      }
    }
    else{
      Memo1->Lines->Add(SS + " -> " + Fred->Strings[Vindx]);
      if(thisModule->DLLName == "Macro"){
        ClassMacro *thisMacro  = dynamic_cast<ClassMacro *> (thisModule);

        if(thisMacro->isGroup){
          Memo1->Lines->Add("Group with modules:");
          String S;
          for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
            if(ii == 0)
              S = "  " + thisMacro->GrpStringList->Strings[ii];
            else
              S += ", " + thisMacro->GrpStringList->Strings[ii];
          Memo1->Lines->Add(S);
        }
        else if(thisMacro->isStruct){
          Memo1->Lines->Add("Struct with modules:");
          String S;
          for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
            if(ii == 0)
              S = "  " + thisMacro->GrpStringList->Strings[ii];
            else
              S += ", " + thisMacro->GrpStringList->Strings[ii];
          Memo1->Lines->Add(S);
        }
        else{
          Memo1->Lines->Add("Macro: " );
          Memo1->Lines->Add("declarations:");
          for(int ii = Global::MacroModulesList->IndexOf(thisMacro->Name.c_str()) + 1; ii < thisMacro->Begin - 1; ++ii)
            Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);

          Memo1->Lines->Add("code:");
          for(int ii = thisMacro->Begin; ii < thisMacro->End; ++ii)
            Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
        }
      }
    }
    Memo1->Lines->Add(" ");
    delete Fred;
  }

  OurOptions << goHorzLine << goVertLine << goFixedVertLine << goColSizing;
  StringGrid1->Options = OurOptions;

  for (int I = 0; I < StringGrid1->ColCount; ++I)
    for (int J = 0; J < StringGrid1->RowCount; ++J)
      StringGrid1->Cells[I][J] = "";

  StringGrid1->ColCount = 6;
  StringGrid1->FixedRows = 0;
  StringGrid1->RowCount = 1;

  StringGrid1->Cells[0] [0] = "Observations";
  StringGrid1->Cells[1] [0] = "Modules";
  StringGrid1->Cells[2] [0] = "Inputs";
  StringGrid1->Cells[3] [0] = "Outputs";
  StringGrid1->Cells[4] [0] = "Parameters";
  StringGrid1->Cells[5] [0] = "New Observations";

// insert observations
  pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(S);
  int ii = 0;
  for(itMap = range.first; itMap != range.second; ++itMap) {
    SS = (itMap->second).first;
    if(StringGrid1->RowCount < ii+3) StringGrid1->RowCount = ii+3;
    int Indx = StringGrid1->Cols[0]->IndexOf(SS);
    if(Indx == -1 && Variation_Decide(Variation, (itMap->second).second)){
      StringGrid1->Cells[0] [ii+2] = SS;
      ++ii;
    }
  } // for

// insert put variables used
  range = Global::Mapputvar.equal_range(S);
  ii = 0;
  for(itMap = range.first; itMap != range.second; ++itMap) {
    SS = itMap->second.first;
    int jj = SS.Pos(" ");
    S1 = SS.SubString(1, jj-1); // module
    S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
    if(S1 != S && Variation_Decide(Variation, (itMap->second).second)) {
      if(StringGrid1->RowCount < ii+3) StringGrid1->RowCount = ii+3;
      StringGrid1->Cells[1] [ii+2] = S1;
      StringGrid1->Cells[2] [ii+2] = S2;
      ++ii;
    }
  } // for

// insert get variables used
  range = Global::Mapgetvar.equal_range(S);
//  ii = 0;
  for(itMap = range.first; itMap != range.second; ++itMap) {
    SS = itMap->second.first;
    int jj = SS.Pos(" ");
    S1 = SS.SubString(1, jj-1); // module
    S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
    if(S1 != S && Variation_Decide(Variation, (itMap->second).second)) {
      int Indx = StringGrid1->Cols[2]->IndexOf(S2);
      if(Indx == -1){
        if(StringGrid1->RowCount < ii+3) StringGrid1->RowCount = ii+3;
        StringGrid1->Cells[1] [ii+2] = S1;
        StringGrid1->Cells[2] [ii+2] = S2;
        ++ii;
      }
    }
  } // for

// insert variables declared
  range = Global::Mapdeclvar.equal_range(S);
  ii = 0;
  for(itMap = range.first; itMap != range.second; ++itMap) {
    SS = itMap->second.first;

    pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
            value_equals<KeyType2,  KeyType2, Pairstr>(SS));

    pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
            value_equals<KeyType2,  KeyType2, Pairstr>(SS));

    if((pos == Global::Mapreadvar.end() || Not_Obs(S, SS))&& pos2 == Global::Mapdeclobs.end()){
      int Indx = StringGrid1->Cols[3]->IndexOf(SS);
      if(Indx == -1 && Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)){
        if(StringGrid1->RowCount < ii+3) StringGrid1->RowCount = ii+3;
        StringGrid1->Cells[3] [ii+2] = SS;
        ++ii;
      }
    }
  } // for

// insert parameters declared
  range = Global::Mapdeclpar.equal_range(S);
  ii = 0;
  for(itMap = range.first; itMap != range.second; ++itMap) {
    if(Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)){
      SS = itMap->second.first;
      if(StringGrid1->RowCount < ii+3)
        StringGrid1->RowCount = ii+3;
      StringGrid1->Cells[4] [ii+2] = SS;
      ++ii;
    }
  } // for

// insert observations declared
  range = Global::Mapdeclobs.equal_range(S);
  ii = 0;
  for(itMap = range.first; itMap != range.second; ++itMap) {
    if(Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)){
      SS = itMap->second.first;
      if(StringGrid1->RowCount < ii+3)
        StringGrid1->RowCount = ii+3;
      StringGrid1->Cells[5] [ii+2] = SS;
      ++ii;
    }
  } // for

  if(StringGrid1->RowCount > 1) StringGrid1->FixedRows = 1;
}
//---------------------------------------------------------------------------

long __fastcall TBldForm::Best_Match(String Var, TStringList *List){

  long found = 10;
  long Indx = -1;

  for(int jj = 0; jj < List->Count; ++jj) {
    String Entry = List->Strings[jj];
    long kk = Entry.Pos(' ');
    String Var1 = Entry.SubString(kk+1, Entry.Length()); // root or group

    bool rootVar = (Var.Pos("@") == 0); // note !root == group
    bool rootVar1 = (Var1.Pos("@") == 0);

    if(Var1 == Var){ // exact match
      found = 0;
      Indx = jj;
      break;
    }
    else if(rootVar && !rootVar1 && Var == Var1.SubString(0, Var1.Pos("@")) && found > 1){ // root variable to GRP match to root variable
      found = 1;
      Indx = jj;
    }
    else if(!rootVar && rootVar1 && Var.SubString(0, Var.Pos("@")) == Var1 && found > 2){  // GRP to root variable match to variable
      found = 2;
      Indx = jj;
    }
    else if(!rootVar && !rootVar1 && Var.SubString(0, Var.Pos("@")) == Var1.SubString(0, Var1.Pos("@")) && found > 3){ // GRP variable root to GRP variable root
      found = 3;
      Indx = jj;
    }
  } // for
  return Indx;
}
//---------------------------------------------------------------------------

long __fastcall TBldForm::CheckModel() {

  long Showing = ListBox2->Items->Count;
  if(Showing == 0) return 0;

  Mapstr::iterator itMap, pos, pos2;
  pair<Mapstr::iterator, Mapstr::iterator> rangeO;
  pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
  pair<Mapstr::iterator, Mapstr::iterator> rangeI;
  pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;

  List = new TStringList;
  ListAll = new TStringList;
  ListUsed = new TStringList; // Object ListBox2 pos index, neg -(index+1)
  ListPuts = new TStringList;
  ListStats = new TStringList;

  List->Sorted = false; // allows duplicates
  ListUsed->Sorted = false; // allows duplicates
  ListPuts->Sorted = false; // allows duplicates
  ListStats->Sorted = false; // allows duplicates

  String S, SS, S1, S2;
  int indx, Error = 0, Wild = 0;
  MapAKAVar.clear();

  StatusBar1->SimpleText = "";
  Memo1->Lines->Clear();

  long Variation = 0;
  long Vindx = 0;
  int P;

Again:

// Add any modules not in ListBox2 but defined as source modules.
// Wild modules must be explicitly added.
  for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {
    S = ListBox2->Items->Strings[ii];

    if(P = S.Pos("#"), P > 0){ // remove any suffix
      Vindx = S[P+1] - char('0');
      Variation = pow(2, S[P+1] - char('1'));
      S = S.Delete(S.Length()-1, 2);
    }
    else
      Variation = 0;

    rangeI = Global::Mapgetvar.equal_range(S);
    for(itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
      SS = itMap->second.first;
      if(Variation_Decide(Variation, (itMap->second).second)){
        int jj = SS.Pos(" ");
        S1 = SS.SubString(1, jj-1);
        S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
        if(S1[1] != '*'){ // handle specified variables
          rangeO = Global::Mapdeclvar.equal_range(S);
          bool Found = false;
          for(pos = rangeO.first; pos != rangeO.second; ++pos) {
            if(S2 == pos->second.first){ // variable
              Found = true;
              break;
            }
          }
          if(!Found){ // not a group!
            indx = IndexOf(ListBox2, S1); // module in model?
            if(indx == -1) { // module not loaded
              indx = IndexOf(ListBox1, S1); // module available?
              if(indx == -1) { // module does not exist
                LogError("module not found: " + S1, ERR); // should not return
                Memo1->Lines->Add("module not found: " + S1);
              }
              else{
                int result = IDYES;
                result = Application->MessageBox(String("To satisfy module " + S + " input " + SS).c_str(), String("Add module " + S1 + " ?").c_str(), MB_YESNO);
                if(result == IDYES)
                  ListBox2->Items->InsertObject(ii, S1, ListBox1->Items->Objects[indx]);
              }
            }
          } // if
        } // if
      } // handle variation
    } // for
  } // for

  for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {
    S = ListBox2->Items->Strings[ii];

    if(P = S.Pos("#"), P > 0){ // remove any suffix
      Vindx = S[P+1] - char('0');
      Variation = pow(2, S[P+1] - char('1'));
      S = S.Delete(S.Length()-1, 2);
    }
    else
      Variation = 0;

// make stats list
    rangeI = Global::Mapdeclstat.equal_range(S);

    for(itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
      SS = itMap->second.first; // module + variable
      if(Variation_Decide(Variation, (itMap->second).second))
        ListStats->Add(SS);
    } // for

    rangeO = Global::Mapdeclvar.equal_range(S);
    rangeOobs = Global::Mapdeclobs.equal_range(S);
    rangeI = Global::Mapgetvar.equal_range(S);
    rangeIobs = Global::Mapreadvar.equal_range(S);

// add current modules declared observations to 'list'
    for(itMap = rangeOobs.first; itMap != rangeOobs.second; ++itMap) {
      SS = itMap->second.first; // variable
      if(Variation_Decide(Variation, (itMap->second).second))
        List->AddObject(S + " " + SS, (TObject *) 0);
    } // for

// add current modules declared variables to 'list'
    for(itMap = rangeO.first; itMap != rangeO.second; ++itMap) {
      SS = itMap->second.first; // variable
      if(Variation_Decide(Variation, (itMap->second).second)){
        pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
              value_equals<KeyType2,  KeyType2, Pairstr>(SS));

        pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
              value_equals<KeyType2,  KeyType2, Pairstr>(SS));

        if((pos == Global::Mapreadvar.end() || Not_Obs(S, SS))&& pos2 == Global::Mapdeclobs.end()){
          S2 = ListBox2->Items->Strings[ii] + " " + SS;
          String S3;
          String M3;
          bool Twice = false;
          int tt;

          for(tt = 0; tt < ListAll->Count; ++tt){
            int jj = ListAll->Strings[tt].Pos(" ");
            S3 = ListAll->Strings[tt].SubString(jj+1, ListAll->Strings[tt].Length() - jj); // variable
            M3 = ListAll->Strings[tt].SubString(1, jj-1); // module
            if(S3 == SS && S != M3 && S != "obs"){
              if(S3[S3.Length()] != '#'){
                Twice = true;
                break;
              }
            }
          }

          if(Twice){
            int result = IDYES;
            result = Application->MessageBox(String("YES to remove '" + S + "' or NO to remove '" + M3 + "'").c_str(),
            String("Module output generated twice: '" + S2 + "' defined earlier as '" + ListAll->Strings[tt] + "'").c_str(), MB_YESNO);

            if(result == IDYES)
              tt = IndexOf(ListBox2, S); // module in model?
            else if(result == IDNO)
              tt = IndexOf(ListBox2, M3); // module in model?

            ListBox2->Items->Delete(tt);

            Entries.clear();
            List->Clear();
            ListAll->Clear();
            ListUsed->Clear();
            ListPuts->Clear();
            ListStats->Clear();

            goto Again;
          }

          ListAll->Add(S2);

          int indx = List->IndexOf(S2);
          if(indx == -1)
            List->AddObject(S2, (TObject *) 0);
        } // if
      } // handle variation
    } // for

// add needed get variables to ListUsed
    for(itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
      SS = itMap->second.first; // module + variable
      if(Variation_Decide(Variation, (itMap->second).second)){
        int indx = List->IndexOf(SS);
        if(indx == -1 && SS[1] != '*') { // handle groups and ignore wild
          int jj = SS.Pos(" ");
          S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
          S1 = S + ' ' + S2; // check if in the same group
          indx = List->IndexOf(S1);
          if(indx == -1 && S1[S1.Length()-1] == '@') // check if available as root variable
            indx = List->IndexOf(SS.SubString(0, SS.Pos("@"))); // check if available as root variable
        }
        if(indx == -1) {
          ListUsed->AddObject(SS, (TObject *) -(ii+1)); // wild variable or undefined
        }
        else {
          int Cnt = (int) List->Objects[indx]; // increment count of useage
          List->Objects[indx] = (TObject *) ++Cnt;
          ListUsed->AddObject(SS, (TObject *) ii);
        }
      } // neccessary
    } // for

// add needed put variables to ListUsed
    rangeI = Global::Mapputvar.equal_range(S);

    for(itMap = rangeI.first; itMap != rangeI.second; ++itMap) {
      SS = itMap->second.first; // module + variable
      if(Variation_Decide(Variation, (itMap->second).second)){
        int indx = List->IndexOf(SS);
        if(indx == -1) {
          ListPuts->AddObject(SS, (TObject *) ListUsed->Count); // wild variable or undefined
          ListUsed->AddObject(SS, (TObject *) -(ii+1)); // wild variable or undefined
        }
        else {
          int Cnt = (int) List->Objects[indx]; // increment count of useage
          List->Objects[indx] = (TObject *) ++Cnt;
          ListPuts->AddObject(SS, (TObject *) ListUsed->Count);
          ListUsed->AddObject(SS, (TObject *) ii);
        }
      } // handle variation
    } // for

// add needed macro observations to ListUsed
    for(itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap) {
      SS = itMap->second.first; // variable
      if(Variation_Decide(Variation, (itMap->second).second)){
        pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
              value_equals<KeyType2,  KeyType2, Pairstr>(SS));

        if(pos == Global::Mapdeclobs.end())
          continue; // not available or met observation
        indx = IndexOf(ListBox2, pos->first); // module available?
        if(indx != ii && indx > -1){ // cannot be its self
          S1 = pos->first;
          SS = pos->second.first;
          S2 = S1 + " " + SS;
          indx = List->IndexOf(S2);
          if(indx == -1) { // used but not declared
            ListUsed->AddObject(S2, (TObject *) -(ii+1));
          }
          else {
            int Cnt = (int) List->Objects[indx]; // increment count of useage
            List->Objects[indx] = (TObject *) ++Cnt;
            ListUsed->AddObject(S2, (TObject *) ii);
          }
        } // if
      } // handle variation
    } // for
  } // for - long loop

  for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {
    S = ListBox2->Items->Strings[ii];

    if(P = S.Pos("#"), P > 0){ // remove any suffix
      Vindx = S[P+1] - char('0');
      Variation = pow(2, S[P+1] - char('1'));
      S = S.Delete(S.Length()-1, 2);
    }
    else{
      Vindx = 0;
      Variation = 0;
    }
// Add module PeerVar to 'ListUsed' to force module to desired rank.
    ClassModule *Module = (ClassModule*) ListBox2->Items->Objects[ii];

    TStringList *Choices = new TStringList;
    Choices->CommaText = Module->PeerVar;

    if(Choices->Count > Vindx)
      SS = Choices->Strings[Vindx];
    else if(Choices->Count)
           SS = Choices->Strings[Choices->Count-1];
         else
           SS = "";

    if(SS != "") {
      for(int jj = 0; jj < List->Count; ++jj) {
        String Entry = List->Strings[jj];
        long kk = Entry.Pos(' ');
        S1 = Entry.SubString(kk+1, Entry.Length());
        if(S1 == SS)
          break;
      } // for

      if(S1 == SS) {
        SS = "* " + SS;
        ListUsed->AddObject(SS, (TObject *) -(ii+1)); // wild variable
        String SSS = "Ranking module '" + S + "' to '" + SS + "'";
        Memo1->Lines->Add(SSS);
      }
      else {
        S2 = "Ranking module '" + S + "' to an inaccessible variable '" + SS + "'";
        Memo1->Lines->Add(S2);
      }
    } // if
  } // for

  for(int ii = 0; ii < ListUsed->Count; ++ii) {

// if wild see if exists anywhere
    if(ListUsed->Strings[ii][1] == '*') {
      String Var = ListUsed->Strings[ii];
      Var = Var.SubString(3, Var.Length());
      int jj = Best_Match(Var, List);
      if(jj > -1){ // match
        ++Wild;
        int thisModule = (int) ListUsed->Objects[ii];
        thisModule = -(thisModule+1);
        String Module = ListBox2->Items->Strings[thisModule];
//        LogError("wild variable: '" + Module + " " + ListUsed->Strings[ii] + "' associated with '" + List->Strings[jj] + "'", WARNING);

//        Memo1->Lines->Add("wild variable: '" + Module + " " + ListUsed->Strings[ii] + "' associated with '" + List->Strings[jj] + "'");

        ListUsed->Strings[ii] =  List->Strings[jj];
        ListUsed->Objects[ii] =  (TObject *) abs((int) ListUsed->Objects[ii]+1); // make positive
      } // if
    } // if 'wild'

    else { // declared module source
      int NotFoundIndx = (int) ListUsed->Objects[ii];
      if(NotFoundIndx < 0) { // variable declared after use in current order?
        int indx = List->IndexOf(ListUsed->Strings[ii]);
        if(ListPuts->IndexOf(ListUsed->Strings[ii]) == -1 && indx == -1)
          ++Error;
        if(indx > -1) {
          ListUsed->Objects[ii] =  (TObject *) abs((int) ListUsed->Objects[ii]+1); // make positive
          continue;
        }
      }
      else{
        continue; // OK
      }
    } // declared module source

    int NotFoundIndx = (int) ListUsed->Objects[ii];
    if(NotFoundIndx < 0 && ListUsed->Strings[ii][1] == '*') { // not found after wild variable search

// make suggestions
      String Message;
      String Message2(" Suggestions: ");
      ++Error;
      LogError("wild variable not found: " + ListUsed->Strings[ii], WARNING);

      int kk =  abs((int) ListUsed->Objects[ii]+1); // make positive

      String Sroot = ListUsed->Strings[ii];
      if(Sroot.Pos("@") != 0)
         Sroot = Sroot.SubString(0, Sroot.Pos("@"));
      Message = "wild variable not found: \" " + Sroot + "\" used by " + ListBox2->Items->Strings[kk] + ".";
      String SW = ListUsed->Strings[ii];
      SW = SW.SubString(3, ListUsed->Strings[ii].Length());
      bool Once = false;
      bool rootVar = (SW.Pos("@") == 0); // note !root == group
      if(!rootVar)
        SW = SW.SubString(0, SW.Pos("@"));
      for(itMap = Global::Mapdeclvar.begin(); itMap != Global::Mapdeclvar.end(); ++itMap) {
        SS = itMap->second.first;
        bool rootVar1 = (SS.Pos("@") == 0); // note !root == group
        if(!rootVar1)
          SS = SS.SubString(0, SS.Pos("@"));
        if(SW == SS) {
          Once = true;
          String S = itMap->first;
          VandP V; V.Set((itMap->second).second);
          long Variation = V.GetV() & 2047;
          if(Variation > 0){
            long NN = log(Variation)/log(2) + 1;
            String  AA = "#0";
            AA[2] += NN;
            S += AA;
          }
          Message2 += S + ", ";
        }
      } // for

      if(!Once)
        Memo1->Lines->Add(Message + " No " + Message2);
      else
        Memo1->Lines->Add(Message + Message2);

    } // if
  } // for - long loop

  if(Error) {
    S = "Errors: " + String(Error) + ';';
    String Line = AnsiString::StringOfChar('*', 80);;
    Memo1->Lines->Add(Line);
  }
  else {
    bool Loop = true;
    int Loops = 0;
    TStringList *OrgList = new TStringList; // source module + varName, original ListBox2 index

    for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {
      OrgList->AddObject(ListBox2->Items->Strings[ii], (TObject*) ii);
      Entries.push_back(ClassEntry()); // create entries
    }

    while(Loop) {

      Loop = false; ++Loops;

// set up ClassEntry vector
      for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {
        Entries[ii].module = (ClassModule*) ListBox2->Items->Objects[ii];
        Entries[ii].Name = ListBox2->Items->Strings[ii]; // (Entries[ii].module)->Name.c_str(); //
        Entries[ii].rank = 0; // clear to highest rank
        Entries[ii].used = false; // set to not used

        unsigned long index = OrgList->IndexOf(ListBox2->Items->Strings[ii]);
        if(index < 0 || index > Entries.size()-1) {
          LogError("Build error: outside range", ERR);  // should not return
        }
        Entries[ii].OrigPos = index;
      } // for

      for(int ii = 0; ii < ListPuts->Count; ++ii) { // handle wild cards in Puts list
        ListPuts->Strings[ii] = ListUsed->Strings[(int) ListPuts->Objects[ii]];
      }

// assign each module its current rank based upon the modules it uses
      for(int ii = 0; ii < ListUsed->Count; ++ii) {
        unsigned long thisModule = (int) ListUsed->Objects[ii]; // original postion

        for(unsigned long nn = 0; nn  < Entries.size(); ++nn) {
          if(Entries[nn].OrigPos == thisModule) {
            thisModule = nn; // current position
            if(thisModule < 0 || thisModule > Entries.size()-1) {
              LogError("Build error: outside range", ERR);  // should not return
            }
            break;
          } // if
        } // for

        String Entry = ListUsed->Strings[ii];
        long kk = Entry.Pos(' ');
        String UsesModule = Entry.SubString(1, kk-1); // extract module name
        String Var_only =  Entry.SubString(kk+1, Entry.Length() - kk); // extract variable name

        unsigned long index;
        ClassModule* checkModule;

        for(index = 0; index < Entries.size(); ++index){ // find modules position
          String Root = Entries[index].Name;
          if(Root == UsesModule){
            checkModule = Entries[index].module;
            break;
          }
        }

        if(checkModule && checkModule->isGroup){ // resides in group
          Entries[index].used = true;
          continue;
        }
        if(index >= Entries.size())
          continue; // ignore

        Entries[index].used = true;

        if(UsesModule == Entries[thisModule].Name) // ignore if self
          continue;

// assume if put or stat, module does not matter
        int jj = Best_Match(Var_only, ListPuts);
        if(jj > -1 && ii == ((int) ListPuts->Objects[jj]))
          continue; // ignore Puts

        jj = Best_Match(Var_only, ListStats);
        if(jj > -1)
          continue; // ignore Stats

        long B = powl(2, index); // calculate weight
        Entries[thisModule].rank |= B; // OR - done more than once

      } // for

// sort by descending rank (ie ascending value)
      for(unsigned long ii = 0; ii < Entries.size()-1; ++ii) {
        for(unsigned long jj = ii+1; jj < Entries.size(); ++jj) {

          if(Entries[jj].rank < Entries[ii].rank) {
            MoveDown(Entries, ii, jj);
            Loop = true;
          }
        } // for
      } // for

// move entries with equal rank together in alphabetic order or peer rank
      for(long ii = 0; ii < Entries.size()-1; ++ii) {
        ClassModule * E2 = (ClassModule*) Entries[ii].module;
        if(E2->PeerRank < 0)
          Entries[ii].used = true;
        for(long jj = ii+1; jj < Entries.size(); ++jj) {
          if(Entries[jj].rank == Entries[ii].rank) {
            ClassModule * E1 = (ClassModule*) Entries[jj].module;

            if(labs(E1->PeerRank) < labs(E2->PeerRank)){
              MoveDown(Entries, ii, jj);
              Loop = true;
            }
          } // if
        } // for
      } // for

      ListBox2->Clear();

// update ListBox2
      for(unsigned long ii = 0; ii <  Entries.size(); ++ii)
        ListBox2->Items->AddObject(Entries[ii].Name, (TObject*) Entries[ii].module);

      if(Loops > 20) { // too many - something funny
        Loop = false;
        Loops = -Loops;
      }
    } // while

    bool Removed = false;
    for(unsigned long ii = 0; ii <  Entries.size()-1; ++ii){
      if(!Entries[ii].used && Entries[ii].Name != "basin"){  // never remove basin
        int result = IDYES;
        result = Application->MessageBox(Entries[ii].Name.c_str(), "Module not used!  Remove module?", MB_YESNO);
        if(result != IDYES)
          continue;
        int indx = IndexOf(ListBox2, Entries[ii].Name);
        ListBox2->Items->Delete(indx);
        Removed = true;
      }
    }

    Entries.clear();
    List->Clear();
    ListAll->Clear();
    ListUsed->Clear();
    ListPuts->Clear();
    ListStats->Clear();

    if(Removed) goto Again;

    int moves = 0;

    for(unsigned long ii = 0; ii < Entries.size(); ++ii)
      if(Entries[ii].OrigPos != ii) ++moves; // final number of modules moved

    if(Loops){
      Memo1->Lines->Add(" ");
      LogError("Number of loops to build: " + String(Loops) + " and modules moved: " + String(moves), WARNING);
      Memo1->Lines->Add("Number of loops to build: " + String(Loops) + " and modules moved: " + String(moves));
    }
    else {
      LogError("Problem with modules in build. Possibly modules referencing one another!", WARNING);
      Memo1->Lines->Add("Problem with modules in build. Possibly modules referencing one another!");
      Application->MessageBox("Problem with modules in build.", "Possibly modules referencing one another!", MB_OK);
    }

    Entries.clear();
    delete OrgList;
    S = "";
  } // else

  if(Global::nlay != UpDownMAXLAY->Position || Global::nhru != UpDownMAXHRU->Position){
    LogError("# of HRUs changed: *** edit parameters ***" , WARNING);
    Memo1->Lines->Add(" ");
    Memo1->Lines->Add("# of HRUs changed: *** edit parameters ***");
  }

  if(Wild) S += "  Wild references: " + String(Wild) + ';';

  StatusBar1->SimpleText = S;
  StatusBar1->Repaint();

  delete List;
  delete ListAll;
  delete ListUsed;

  return Error;
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::CheckClick(TObject *Sender)
{
  CheckModel();
}
//---------------------------------------------------------------------------


void __fastcall TBldForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  Global::MapAKA = MapAKACopy;

  ListBox1->Clear();
  ListBox2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::FormDeactivate(TObject *Sender)
{
  for(int cc = 0; cc < StringGrid1->ColCount; ++cc)
    StringGrid1->Cols[cc]->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::UpDownMAXLAYClick(TObject *Sender,
      TUDBtnType Button)
{
  LabelMAXLAY->Caption = "MAXLAY = " + String(UpDownMAXLAY->Position);
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::UpDownMAXHRUClick(TObject *Sender,
      TUDBtnType Button)
{
  LabelMAXHRU->Caption = "MAXHRU = " + String(UpDownMAXHRU->Position);
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::SaveBuildParameters(TObject *Sender){

  ClassPar *thisPar;

  if(ModifyBuild) {

    Main->RemoveSharedParams(); // change shared parameters to module parameters

    ParaList = new TStringList;

    // make map: keyed by parameter name holding pointer to parameter
    MapPar::iterator itPar;
    itPar = Global::MapPars.begin();
    while (itPar !=  Global::MapPars.end()) {
      thisPar = (*itPar).second;
      String S = String(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
      if(ParaList->IndexOf(S) == -1) {
        ClassPar* par(new ClassPar(*thisPar));
        ParaList->AddObject(S, (TObject *) par);
      }
      ++itPar;
    } // while
  } // if(ModifyBuild)
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::ReadBuildParameters(TObject *Sender){

  MapPar::iterator itPar;
  ClassPar *thisPar;

  if(ModifyBuild) {

    itPar = Global::MapPars.begin();
    while (itPar !=  Global::MapPars.end()) {
      thisPar = (*itPar).second;

      String S = String(((*itPar).second)->module.c_str()) + " " + ((*itPar).second)->param.c_str();
      int ii = ParaList->IndexOf(S);
      if(ii != -1) {
        ClassPar *OldPar = (ClassPar *) ParaList->Objects[ii];
        thisPar->Change(*OldPar);  // restore old value
      }
      ++itPar;
    } // while

    for(int ii = 0; ii < ParaList->Count; ++ii)
      delete (ClassPar *) ParaList->Objects[ii]; // delete Objects

    delete ParaList;
    ParaList = NULL;
    
    Main->SqueezeParams(Sender);  // converts identical parameters to shared parameters
  } // if(ModifyBuild)
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::BitBtn1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  long Showing = ListBox2->Items->Count;
  if(Showing == 0){
    Global::nlay = UpDownMAXLAY->Position;
    Global::nhru = UpDownMAXHRU->Position;
    return;
  }

  long Errors = CheckModel();

  if(Errors) {
    Application->MessageBox("Model has unsatisfied module inputs or multiple definitions",
      String("Errors: " + String(Errors)).c_str(), MB_OK);
    return;
  }

  if(ModifyBuild) {
    SaveBuildParameters(Sender);
    RemoveParameter(Sender);
  }

  MapAKACopy = Global::MapAKA; // keep any renamed OUTPUTs

  Main->ClearModules(Sender, false); // resets Global::MapAKA

  Global::nlay = UpDownMAXLAY->Position;
  Global::nhru = UpDownMAXHRU->Position;

  if(Global::nhru > Global::maxhru){
    Update_Main_DIM(CRHM::NHRU, Global::nhru);
  }
  
  for(int ii = 0; ii < ListBox2->Items->Count; ++ii) { // handle variations
    ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[ii];
    if(FormatMax(thisModule->variation_max) > 0){ // i.e. variation
      thisModule->variation = pow(2, thisModule->hh - 1); // set variation
      if(ListBox2->Items->Strings[ii].Pos("#") > 0){ // remove any suffix
        ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii].Delete(ListBox2->Items->Strings[ii].Length()-1, 2);
      }
    }
  }

  Global::OurModulesList->Assign(ListBox2->Items);

  Execute = true;

  Global::BuildFlag = CRHM::BUILD; // model loaded  was DECL

  if(!MapAKAVar.empty()) {
    Mapstr2::iterator it;

    for (it = MapAKAVar.begin(); it !=  MapAKAVar.end(); ++it)
      MapAKACopy.insert(*it);
  }
  Close();
  return;
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::AKAselectiveDelete(TObject *Sender){

  if(!Global::MapAKA.empty()) { // separate out AKA commands
    Mapstr2::iterator it;

    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ) {
      string Var = (*it).first; // module, type and name

      string::size_type idx = Var.find(' ');
      string type = Var.substr(0, idx);
      TAKA Type = AKAtype(type);

      switch (Type) {
        case OBSR :
        case OBSF :
        ++it;
        break;

        default :
        Global::MapAKA.erase(it++);

      } // end switch
    } // for
  }
}
//---------------------------------------------------------------------------
int __fastcall TBldForm::IndexOf(TListBox *Box, const AnsiString S){
  for(int ii = 0; ii < Box->Count; ++ii){
    if(Box->Items->Strings[ii] == S)
    return ii;
  }
  return -1;
}
//---------------------------------------------------------------------------

bool __fastcall TBldForm::Not_Obs(String Mod, String Var){

  pair<Mapstr::iterator, Mapstr::iterator> rangeIobs = Global::Mapreadvar.equal_range(Mod);

  for(Mapstr::iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
    if(Var == itMap->second.first)
      return false;

  return true;
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::Label1Click(TObject *Sender)
{
  ListBox1->Sorted = !ListBox1->Sorted;
  ListBox1->Clear();
  Max_Name_Width1 = 0;

  for(int ii = 0 ; ii < Global::AllModulesList->Count; ++ii)
    if(CheckListBox1->Checked[((ClassModule*) Global::AllModulesList->Objects[ii])->Lvl] == true){
      ListBox1->Items->AddObject(Global::AllModulesList->Strings[ii], (TObject *) Global::AllModulesList->Objects[ii]);
      String S = Global::AllModulesList->Strings[ii];
      if(S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
        Max_Name_Width1 = S.Length();
  }
  ListBox1->ScrollWidth =  Max_Name_Width1*6;
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::CheckListBox1ClickCheck(TObject *Sender)
{
  ListBox1->Clear();
  Max_Name_Width1 = 0;

  for(int ii = 0 ; ii < Global::AllModulesList->Count; ++ii )
    if(CheckListBox1->Checked[((ClassModule*) Global::AllModulesList->Objects[ii])->Lvl] == true){
      ListBox1->Items->AddObject(Global::AllModulesList->Strings[ii], (TObject *) Global::AllModulesList->Objects[ii]);
      String S = Global::AllModulesList->Strings[ii];
      if(S.Length() > 33 && S.Length() > Max_Name_Width1) // 198 pixels roughly 33 caharacters
        Max_Name_Width1 = S.Length();
    }
  ListBox1->ScrollWidth =  Max_Name_Width1*6;
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::Add1Click(TObject *Sender)
{
  TComponent *pComponent = PopupMenuListBox1->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox1") {

      for(int ii = 0; ii < ListBox1->Items->Count; ++ii) {

        if(ListBox1->Selected[ii]) {
          String S = ListBox1->Items->Strings[ii] ;

          if(IndexOf(ListBox2, S) == -1) {
            ListBox2->Items->AddObject(S, ListBox1->Items->Objects[ii]); // add item
            if(S.Length() > 33 && S.Length() > Max_Name_Width2) // 198 pixels roughly 33 caharacters
              Max_Name_Width2 = S.Length();
            CheckListBox1->Checked[((ClassModule*) ListBox1->Items->Objects[ii])->Lvl] = true; // update check level

            int jj = 0;
            for(int iii = 0; iii < ListBox1->Items->Count; ++iii) { // maintain ListBox1 order in ListBox2
              int kk = IndexOf(ListBox2, ListBox1->Items->Strings[iii]);
              if(kk > -1) {
                if(kk != jj)
                  ListBox2->Items->Exchange(kk, jj);
                ++jj;
                if(jj >= ListBox2->Items->Count-1) break;
              }
            }
          } // if
        } // if
      } // for
      ListBox2->ScrollWidth =  Max_Name_Width2*6;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::Delete1Click(TObject *Sender)
{
  TComponent *pComponent = PopupMenuListBox2->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2") {

      for(int ii = ListBox2->Items->Count-1; ii >= 0; --ii) {

        if(ListBox2->Selected[ii]) {
          ListBox2->Items->Delete(ii);
          Label3->Caption = "";

        } // if
      } // for

      Max_Name_Width2 = 0;

      for(int ii = ListBox2->Items->Count-1; ii >= 0; --ii) {
        String S = ListBox2->Items->Strings[ii] ;
        if(S.Length() > 33 && S.Length() > Max_Name_Width2) // 198 pixels roughly 33 caharacters
          Max_Name_Width2 = S.Length();
      } // for
      
      ListBox2->ScrollWidth =  Max_Name_Width2*6;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::ListBox2Click(TObject *Sender)
{
  String S = ListBox2->Items->Strings[ListBox2->ItemIndex] ;
  ClassModule* thisModule = (ClassModule*)ListBox2->Items->Objects[IndexOf(ListBox2, S)];
  DisplayModule(S, thisModule, false);
  CRHM::LMODULE Lvl = thisModule->Lvl;
  Label3->Caption = LVLStrings[Lvl];
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::ListBox1Click(TObject *Sender)
{
  String S = ListBox1->Items->Strings[ListBox1->ItemIndex] ;
  ClassModule* thisModule = (ClassModule*)ListBox1->Items->Objects[IndexOf(ListBox1, S)];
  DisplayModule(S, thisModule, true);
  CRHM::LMODULE Lvl = thisModule->Lvl;
  Label3->Caption = LVLStrings[Lvl];
}
//---------------------------------------------------------------------------
long __fastcall TBldForm::FormatMax(long M)
{
  M = M & 2047;
  if(M == 0) return 0;
  for(int ii = 1; ii < 8; ++ii){
    M = (M >> 1);
    if(M == 0) return ii;
  }
  return -1; // should never get here
}
//---------------------------------------------------------------------------

void __fastcall TBldForm::Variation1Click(TObject *Sender)
{
  TComponent *pComponent = PopupMenuListBox2->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2") {

      for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {

        if(ListBox2->Selected[ii]) {
          ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[ii];
          if(FormatMax(thisModule->variation_max) > 0){ // meaning variation
            String AA;
            ++thisModule->hh;

            if(thisModule->hh > FormatMax(thisModule->variation_max))
              thisModule->hh = 0;
            else{
              AA = "#0";
              AA[2] += thisModule->hh;
            }
            
            if(ListBox2->Items->Strings[ii].Pos("#") > 0) // remove earlier suffix
              ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii].Delete(ListBox2->Items->Strings[ii].Length()-1, 2);

            ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii] + AA;
            DisplayModule(ListBox2->Items->Strings[ii], thisModule, false);
            ListBox2->Selected[ii] = true;
          }
        } // if
      } // for
    }
  }
}
//---------------------------------------------------------------------------

  void __fastcall TBldForm::SetSuffix(long Row){
    ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[Row];
    String AA;
    if(thisModule->hh > 0){
      AA = "#0";
      AA[2] += thisModule->hh;
    }
    if(ListBox2->Items->Strings[Row].Pos("#") > 0) // remove earlier suffix
      ListBox2->Items->Strings[Row] = ListBox2->Items->Strings[Row].Delete(ListBox2->Items->Strings[Row].Length()-1, 2);

    ListBox2->Items->Strings[Row] = ListBox2->Items->Strings[Row] + AA;
  }
//---------------------------------------------------------------------------

void __fastcall TBldForm::Last1Click(TObject *Sender)
{
  TComponent *pComponent = PopupMenuListBox2->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2") {

      for(int ii = 0; ii < ListBox2->Items->Count; ++ii) {

        if(ListBox2->Selected[ii]) {
          ClassModule* thisModule = (ClassModule*) ListBox2->Items->Objects[ii];
          if(FormatMax(thisModule->variation_max) > 0){ // meaning variation
            String AA;
            --thisModule->hh;
            if(thisModule->hh < 0)
              thisModule->hh = FormatMax(thisModule->variation_max);

            if(thisModule->hh > 0){
              AA = "#0";
              AA[2] += thisModule->hh;
            }

            if(ListBox2->Items->Strings[ii].Pos("#") > 0) // remove earlier suffix
              ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii].Delete(ListBox2->Items->Strings[ii].Length()-1, 2);

            ListBox2->Items->Strings[ii] = ListBox2->Items->Strings[ii] + AA;
            DisplayModule(ListBox2->Items->Strings[ii], thisModule, false);
            ListBox2->Selected[ii] = true;
          }
        } // if
      } // for
    }
  }
}
//---------------------------------------------------------------------------

bool TBldForm::Variation_Decide(int Variation_set, long Variation){

  VandP V; V.Set(Variation);

  long variations = V.GetV(); // & 2047;

  if((variations & 2048) != 0 && Variation_set == 0 || // handles VARIATION_0
    (variations & 4096) != 0 ||                        // handles VARIATION_0
    (variations == 0) ||                               // handles VARIATION_ORG
    (variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
    return true;
  else
    return false;
}

//---------------------------------------------------------------------------

bool TBldForm::Visible_Decide(long Variation){

  VandP V; V.Set(Variation);

  long Visible = V.GetP();

  return Visible == 1;
}




