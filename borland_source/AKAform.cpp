// 04/26/10
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AKAform.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include "CRHMmain.h"
#include <sstream>

#define REN 3 // rename column
#define ROW2 2 // first active row

using namespace std;

extern string AKAstrings[];

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormAKA *FormAKA;

//---------------------------------------------------------------------------
__fastcall TFormAKA::TFormAKA(TComponent* Owner)
  : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TFormAKA::FormActivate(TObject *Sender)
{
  if(SaveDialogAKA->InitialDir.IsEmpty())
    SaveDialogAKA->InitialDir = GetCurrentDir();

  if(OpenDialogAKA->InitialDir.IsEmpty())
    OpenDialogAKA->InitialDir = GetCurrentDir();

  LastScreenIndex = RadioGroup->ItemIndex; // skips save screen code first time

  TGridOptions OurOptions;

  OurOptions << goEditing << goFixedVertLine << goFixedHorzLine << goColSizing << goTabs;
  StringGrid1->Options = OurOptions;

  StringGrid1->ColWidths[0] = 120;
  StringGrid1->ColWidths[1] = 100;
  StringGrid1->ColWidths[2] = 80;

  MapAKACopy = Global::MapAKA;

  AKAseparate(Sender); // copy global

  Global::MapAKA.clear(); // inhibit any AKA activity

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::BuildFlag = CRHM::BUILD; // default value

// executes the DECL portion of the declvar/declparam etc. routines
  for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
    ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();


  Global::BuildFlag = CRHM::DECL; // model loaded

  ListBox1->Clear();

  for(int ii = 0 ; ii < Global::OurModulesList->Count; ii++ ){
    ListBox1->Items->AddObject(Global::OurModulesList->Strings[ii],
      (TObject *) Global::OurModulesList->Objects[ii]);
  }

  RadioGroupClick(Sender);

  selectCol = REN;
  selectRow = 2;
}

//---------------------------------------------------------------------------
void __fastcall TFormAKA::DrawGridObs(TObject *Sender)
{
  Mapstr::iterator itMap, pos;
  pair<Mapstr::iterator, Mapstr::iterator> rangeO;

  String S, S2, SS;
  int There, uu;

  ClearGrid(Sender);

  StringGrid1->FixedCols = 0;
  StringGrid1->FixedRows = 0;

  StringGrid1->ColCount = 4;
  StringGrid1->RowCount = 2;

  StringGrid1->Cells[0][0] = "Module";
  StringGrid1->Cells[1][1] = "Original Name";
  StringGrid1->Cells[2][1] = "units";
  StringGrid1->Cells[REN][1] = "Renamed";

// add current modules declared observations to list

  for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii) {
    if(ListBox1->Selected[ii] == false  && ListBox1->SelCount != 0) continue;

      S = ListBox1->Items->Strings[ii]; // module
      rangeO = Global::Mapdeclobs.equal_range(S);

      for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
        SS = itMap->second.first; // variable

        StringGrid1->RowCount = StringGrid1->RowCount + 1;
        StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
        StringGrid1->Cells[0][StringGrid1->RowCount-1] = S;
        StringGrid1->Cells[1][StringGrid1->RowCount-1] = SS;
        StringGrid1->Cells[2][StringGrid1->RowCount-1] = GetUnits(S, SS);
      } //for

// add current modules used observations to list

      rangeO = Global::Mapreadvar.equal_range(S);

      for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
        SS = itMap->second.first; // variable

        int rr = StringGrid1->Cols[1]->IndexOf(SS); // desired met observation

        if(rr == -1) { // assume it is a measured observation
          StringGrid1->RowCount = StringGrid1->RowCount + 1;
          StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
          StringGrid1->Cells[0][StringGrid1->RowCount-1] = "obs";
          StringGrid1->Cells[1][StringGrid1->RowCount-1] = SS;
          StringGrid1->Cells[2][StringGrid1->RowCount-1] = GetUnits(S, SS);
          rr = StringGrid1->RowCount-1;
        }

        There = StringGrid1->Rows[0]->IndexOf(S.c_str());
        if(There < 0){ // first occurrence of module?
          ++StringGrid1->ColCount;
          There = StringGrid1->ColCount-1;
          StringGrid1->Cells[There][0] = S; // add module heading
        }

        StringGrid1->Cells[There][rr] = SS;

      } //for
  } // for

  if(StringGrid1->ColCount > REN) StringGrid1->FixedCols = REN;
  if(StringGrid1->RowCount > 2) StringGrid1->FixedRows = 2;

  Memo->Lines->Clear();

  if(!MapAKAObs.empty()) {
    Mapstr2::iterator it;

    for (it = MapAKAObs.begin(); it !=  MapAKAObs.end(); ++it) {

      string Obs = (*it).first + ' ' + (*it).second;

      TAKA Type = Digest(it, module, name, Newname, source);
      if(source != "obs" && Newname[Newname.length()-1] != '#')
        Newname += '#';

      int rr, cc2;

      switch (Type) {
        case OBSR :
        case OBSF :
          cc2 = StringGrid1->Rows[0]->IndexOf(module.c_str()); // find module using input
          if(cc2 == -1) // added to handle AKA module not selected
            break;

          rr = MatchMod_Name("obs", name.c_str(), 1); // observation

          if(rr == -1){ // missing obs, ??? QsiDObs
            StringGrid1->RowCount = StringGrid1->RowCount + 1;
            rr = StringGrid1->RowCount-1;
            StringGrid1->Rows[rr]->Clear();
            StringGrid1->Cells[0][rr] = "obs";
            StringGrid1->Cells[1][rr] = name.c_str();
          }

          StringGrid1->Cells[cc2][rr] = String("[ ") + name.c_str() + " -> " + Newname.c_str() + " ]"; // put new name in basic obs

          if(Newname[Newname.size()-1] == '#')
            rr = MatchMod_Name(module.c_str(), Newname.c_str(), 1); // declared variable
          else
            rr = MatchMod_Name("obs", Newname.c_str(), 1); // observation

          int rr3 = MatchMod_Name(source.c_str(), Newname.c_str(), 1); // find named variable
          if(rr3 == -1)
            rr3 = MatchMod_Name(source.c_str(), Newname.c_str(), 3); // find renamed variable

          if(rr3 > -1)
            StringGrid1->Cells[cc2][rr3] = String("--> ") + Newname.c_str(); // clear original name

          Memo->Lines->Add(Obs.c_str());

          break;
      } // end switch
    } // for
  } // if
}

//---------------------------------------------------------------------------
void __fastcall TFormAKA::DrawGridVar(TObject *Sender)
{
  Mapstr::iterator itMap, pos;

  pair<Mapstr::iterator, Mapstr::iterator> rangeO;
  pair<Mapstr::iterator, Mapstr::iterator> rangeI;

  String S, S1, S2, SS;
  int There;
  ClassVar* thisVar;

  ClearGrid(Sender);

  StringGrid1->FixedCols = 0;
  StringGrid1->FixedRows = 0;

  StringGrid1->ColCount = 4;
  StringGrid1->RowCount = 2;

  StringGrid1->Cells[0][0] = "Module";
  StringGrid1->Cells[1][1] = "Original Name";
  StringGrid1->Cells[2][1] = "units";
  StringGrid1->Cells[REN][1] = "select";

  for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii) {
    if(ListBox1->Selected[ii] == false && ListBox1->SelCount != 0) continue;

      S = ListBox1->Items->Strings[ii]; // current module

// add current modules declared variables to list

      rangeO = Global::Mapdeclvar.equal_range(S);

      for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
        SS = itMap->second.first; // variable

        int Pound = SS.Pos("#"); // ignore declared observations
        if(Pound > 0)
          continue;

        pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
              value_equals<KeyType2,  KeyType2, Pairstr>(SS)); // Observation?

        if(pos == Global::Mapreadvar.end()){ // Not observation!
          thisVar = GetVar(S, SS);
          if(thisVar == NULL || thisVar->visibility != CRHM::USUAL) // visible (not diagnostic etc.)
            continue;

          int rr = StringGrid1->Cols[1]->IndexOf(SS); // desired variable
          if(rr == -1){
            StringGrid1->RowCount = StringGrid1->RowCount + 1;
            StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
            StringGrid1->Cells[0][StringGrid1->RowCount-1] = S;
            StringGrid1->Cells[1][StringGrid1->RowCount-1] = SS;
            StringGrid1->Cells[2][StringGrid1->RowCount-1] = GetUnits(S, SS);
          }
        } // if
      } // for
  } // for

  for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii) {
    if(ListBox1->Selected[ii] == false && ListBox1->SelCount != 0) continue;

      S = ListBox1->Items->Strings[ii]; // current module

// add current modules get variables to list

      rangeI = Global::Mapgetvar.equal_range(S);
      for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S1 = SS.SubString(1, jj-1);  // source module
        S2 = SS.SubString(jj+1, SS.Length() - jj); // desired variable

        int rr = StringGrid1->Cols[1]->IndexOf(S2); // desired variable

        There = StringGrid1->Rows[0]->IndexOf(S.c_str());

        if(There < 0 && rr > -1){ // first occurrence of module?
          ++StringGrid1->ColCount;
          There = StringGrid1->ColCount-1;
          StringGrid1->Cells[There][0] = S; // add module heading
        }

        if(rr > -1) { // not always found (private, module not selected or name change(hru_evap/hru_evapD)
          StringGrid1->Cells[There][rr] = S2;
        }
      }

// add current modules put variables to list

      rangeI = Global::Mapputvar.equal_range(S);
      for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {
        SS = itMap->second.first;
        int jj = SS.Pos(" ");
        S1 = SS.SubString(1, jj-1);  // source module
        S2 = SS.SubString(jj+1, SS.Length() - jj); // desired variable

        int rr = StringGrid1->Cols[1]->IndexOf(S2); // desired variable

        There = StringGrid1->Rows[0]->IndexOf(S.c_str());

        if(There < 0){ // first occurrence of module?
          ++StringGrid1->ColCount;
          There = StringGrid1->ColCount-1;
          StringGrid1->Cells[There][0] = S; // add module heading
        }

        if(rr > -1) { // should always be found
          StringGrid1->Cells[There][rr] = S2; // not always found (private, module not selected or name change(hru_evap/hru_evapD)
        }
      } // for
  } // for

  if(StringGrid1->ColCount > REN) StringGrid1->FixedCols = REN;
  if(StringGrid1->RowCount > 2) StringGrid1->FixedRows = 2;

  Memo->Lines->Clear();

  if(!MapAKAVar.empty()) {
    Mapstr2::iterator it;

    for (it = MapAKAVar.begin(); it !=  MapAKAVar.end(); ++it) {

      string Var = (*it).first + ' ' + (*it).second;

      TAKA Type = Digest(it, module, name, Newname, source);
      int indx, indx2, cc2;

      switch (Type) {
        case VARG :
        cc2 = StringGrid1->Rows[0]->IndexOf(module.c_str()); // find module using input
        if(cc2 == -1) // added to handle AKA module not selected
          break;

        indx2 = StringGrid1->Rows[0]->IndexOf(module.c_str()); // find current module
        indx = StringGrid1->Cols[1]->IndexOf(name.c_str()); // find variable

        int indx3 = MatchMod_Name(source.c_str(), Newname.c_str(), 1); // find named variable

        if(indx > -1 && indx2 > -1 && indx3 > -1){ //
            StringGrid1->Cells[indx2][indx] = String("[ ") + name.c_str() + " -> " + Newname.c_str() + " ]";
            if(indx != indx3)
              StringGrid1->Cells[indx2][indx3] = String("--> ") + Newname.c_str();
        }

        Memo->Lines->Add(Var.c_str());
        break;
      } // end switch
    } // for
  } // if
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::ListBox1Click(TObject *Sender)
{
  RadioGroupClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormAKA::StringGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
  int There;
  if(ACol == REN && ARow > 1 && ARow < StringGrid1->RowCount){
    CanSelect = true;
    selectCol = ACol;
    selectRow = ARow;
  }
  else {
    CanSelect = false;
// copy name/rename if cell filled.     entered by TAB and MouseLeft
    if(ACol > REN && ACol < StringGrid1->ColCount && ARow > 1 && ARow < StringGrid1->RowCount && !StringGrid1->Cells[ACol][ARow].IsEmpty())
      if(StringGrid1->Cells[ACol][ARow][1] == '-' ){
//        StringGrid1->Cells[ACol][ARow] = "";
        return;
      }

      if(!StringGrid1->Cells[ACol][ARow].IsEmpty())
        if(StringGrid1->Cells[ACol][ARow][1] != '[' && !StringGrid1->Cells[REN][ARow].IsEmpty()){ // rename
          if(StringGrid1->Cells[ACol][ARow] != StringGrid1->Cells[REN][ARow]){
            StringGrid1->Cells[ACol][ARow] = String("[ ") + StringGrid1->Cells[ACol][ARow] + " -> " + StringGrid1->Cells[REN][ARow] + " ]";
            StringGrid1->Objects[ACol][ARow] = (TObject*) ARow; // rename
          }
        }
        else{
          StringGrid1->Cells[ACol][ARow] = StringGrid1->Cells[1][ARow];
          StringGrid1->Objects[ACol][ARow] = (TObject*) -ARow; // name
        }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::StringGrid1KeyPress(TObject *Sender, char &Key)
{
  if(Key == VK_RETURN) {   //  || Key == VK_TAB
    Key = 0;

    StringGrid1->Cells[selectCol][selectRow] = LocalValue;
  }
  else if(Key == VK_ESCAPE){
    Key = 0;
    StringGrid1->Cells[selectCol][selectRow] = LastValue;
  }
  else { // only allow simple observations to be renamed
    if(StringGrid1->Cells[0][selectRow] != "obs")
      Key = 0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::StringGrid1SetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value)
{
  selectCol = ACol;
  selectRow = ARow;
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::StringGrid1GetEditText(TObject *Sender, int ACol,
      int ARow, AnsiString &Value)
{
  LastValue = Value;
  LocalValue = Value;
}
//---------------------------------------------------------------------------


void __fastcall TFormAKA::Open1Click(TObject *Sender){

  OpenDialogAKA->Filter = "Macro Files (*.aka)|*.aka";
  OpenDialogAKA->DefaultExt = "aka";
  OpenDialogAKA->Title = "Open AKA File";
  if(OpenDialogAKA->Execute()) {

    OpenDialogAKA->InitialDir = ExtractFilePath(OpenDialogAKA->FileName);
    if(OpenDialogAKA->InitialDir.IsEmpty())
      OpenDialogAKA->InitialDir = GetCurrentDir();

    SaveDialogAKA->InitialDir = OpenDialogAKA->InitialDir; // assumes all one type

    Memo->Lines->Clear();

    Memo->Lines->LoadFromFile(OpenDialogAKA->FileName);

    ReadMemo(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::SaveClick(TObject *Sender)
{
  if(!SaveDialogAKA->FileName.IsEmpty())
    Memo->Lines->SaveToFile(SaveDialogAKA->FileName);
  else SaveAsClick(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::SaveAsClick(TObject *Sender)
{
  SaveDialogAKA->Title = "Save As";

  SaveDialogAKA->DefaultExt = "aka";
  SaveDialogAKA->Filter = "Macro Files (*.aka)|*.aka";
  if(SaveDialogAKA->Execute()){
    SaveDialogAKA->InitialDir = ExtractFilePath(SaveDialogAKA->FileName);
    if(SaveDialogAKA->InitialDir.IsEmpty())
      SaveDialogAKA->InitialDir = GetCurrentDir();

    Memo->Lines->SaveToFile(SaveDialogAKA->FileName);
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::ExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::RadioGroupClick(TObject *Sender)
{

  switch (RadioGroup->ItemIndex) {
    case 0 :
               DrawGridVar(Sender);
               break;
    case 1 :
               DrawGridObs(Sender);
               break;
  }
  selectCol = 0; selectRow = 0; // blank cell

  LastScreenIndex = RadioGroup->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::FormDeactivate(TObject *Sender)
{
  AKAcombine(Sender);
  Global::MapAKA = MapAKACopy;
  MapAKACopy.clear();

  Main->InitModules(Sender);
}
//---------------------------------------------------------------------------
TAKA TFormAKA::Digest(Mapstr2::iterator it, string & module, string & name, string & Newname, string & source){

  string Var = (*it).first; // module, type and name

  string::size_type idx = Var.find(' ');
  string type = Var.substr(0, idx);

  Var = Var.substr(idx+1);
  idx = Var.find(' ');
  module = Var.substr(0, idx);

  name = Var.substr(idx+1);

  TAKA Type = AKAtype(type);

  if(Type == VARG || Type == OBSR || Type == OBSF) {
    Var = (*it).second; // Newname and source
    idx = Var.find(' ');
    Newname = Var.substr(0, idx);
    source = Var.substr(idx+1);
  }
  else{
    Newname =  (*it).second;
    source = "";
  }
  return Type;
}

//---------------------------------------------------------------------------

void __fastcall TFormAKA::SaveScreenCode(TObject *Sender)
{
  int OnRow, InCol;
  switch (LastScreenIndex) {
    case 0 : // Var

               AKAModuleDelete(MapAKAVar);

               for(int rr = ROW2; rr < StringGrid1->RowCount; ++rr){
                 for(int cc = 4; cc < StringGrid1->ColCount; ++cc){

                     if(!StringGrid1->Cells[cc][rr].IsEmpty() && StringGrid1->Cells[cc][rr][1] == '-'){ // ignore blank fields
                       StringGrid1->Cells[cc][rr] = "";
                       continue;
                     }

                     if(StringGrid1->Cells[cc][rr].IsEmpty() || StringGrid1->Cells[cc][rr][1] != '[') // ignore blank fields
                       continue;

                     name = StringGrid1->Cells[1][rr].c_str();

                     Newname = StringGrid1->Cells[cc][rr].c_str();
                     string::size_type idx = Newname.find('>');
                     string::size_type idx2 = Newname.find(" ]");
                     Newname = Newname.substr(idx+2, idx2 - idx-2);

                     module =  StringGrid1->Cells[cc][0].c_str();

                     int Indx = StringGrid1->Cols[1]->IndexOf(Newname.c_str()); // find original name
                     if(Indx > -1)
                       source = StringGrid1->Cells[0][Indx].c_str();

                     if(name != Newname || module != source)
                       MapAKAVar.insert(make_pair(AKAstrings[VARG] + " " + module + " " + name, Newname + ' ' + source));
                 } // for columns
               } // for rows

               DrawGridVar(Sender);
               break;
    case 1 : // Obs

               AKAModuleDelete(MapAKAObs);

               for(int rr = ROW2; rr < StringGrid1->RowCount; ++rr){
                 for(int cc = 4; cc < StringGrid1->ColCount; ++cc){

                     if(!StringGrid1->Cells[cc][rr].IsEmpty() && StringGrid1->Cells[cc][rr][1] == '-'){ // ignore blank fields
                       StringGrid1->Cells[cc][rr] = "";
                       continue;
                     }

                     if(StringGrid1->Cells[cc][rr].IsEmpty() || StringGrid1->Cells[cc][rr][1] != '[') // ignore blank fields
                       continue;

                     name = StringGrid1->Cells[1][rr].c_str();

                     Newname = StringGrid1->Cells[cc][rr].c_str();
                     string::size_type idx = Newname.find('>');
                     string::size_type idx2 = Newname.find(" ]");
                     Newname = Newname.substr(idx+2, idx2 - idx-2);

                     module =  StringGrid1->Cells[cc][0].c_str();

                     int Indx = MatchMod_Name(module.c_str(), Newname.c_str(), 1); // fails unless is group
                     if(Indx == -1)
                       Indx = MatchSimple_Name(Newname.c_str(), 1); // find simple, i.e. non-group
//                       Indx = StringGrid1->Cols[1]->IndexOf(Newname.c_str()); // find original name
                     if(Indx == -1 && Newname[Newname.length()-1] == '#') // only if declared obs
                       Indx = StringGrid1->Cols[3]->IndexOf(Newname.c_str()); // find renamed declared obs
                     if(Indx > -1) // found renamed declared obs
                       source = StringGrid1->Cells[0][Indx].c_str();
                     else{
                       Indx = MatchMod_Name(module.c_str(), Newname.c_str(), 1); // handles groups
                       if(Indx == -1)
                         Indx = MatchMod_Name(module.c_str(), Newname.c_str(), 2);   // handles group renamed

                       if(Indx > -1) // declared group observation
                         source = StringGrid1->Cells[0][Indx].c_str();
                       else // renamed observation
                         source = "obs";
                     }
                     if(name != Newname || module != source && source != "obs")
                       MapAKAObs.insert(make_pair(AKAstrings[OBSR] + " " + module + " " + name, Newname + ' ' + source));
                } // for columns
               } // for rows

               DrawGridObs(Sender);
               break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::Save1Click(TObject *Sender)
{
  SaveScreenCode(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::VoidClick(TObject *Sender)
{
  RadioGroupClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::RemoveUnusedClick(TObject *Sender)
{
  if(RadioGroup->ItemIndex != 1) // applies to variable screen
    for(int rr = StringGrid1->RowCount - 1; rr > 1 ; --rr) {
      bool Used = false;
      for (int cc = 4; cc < StringGrid1->ColCount; ++cc) {
        if(!StringGrid1->Rows[rr]->Strings[cc].IsEmpty()) {
          Used = true;
          break;
        }
      }
      if(!Used)
        DeleteRow(rr);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::DeleteRow(int Row) {

  for(int rr = Row; rr < StringGrid1->RowCount-1; ++rr)
    StringGrid1->Rows[rr] = StringGrid1->Rows[rr+1];
  StringGrid1->RowCount = StringGrid1->RowCount - 1;
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::AKAseparate(TObject *Sender)
{
  MapAKAVar.clear();
  MapAKAPar.clear();
  MapAKAObs.clear();

  if(!MapAKACopy.empty()) { // separate out AKA commands
    Mapstr2::iterator it;

    for (it = MapAKACopy.begin(); it !=  MapAKACopy.end(); ++it) {
      TAKA Type = Digest(it, module, name, Newname, source);
      switch (Type) {
        case VARG :
        MapAKAVar.insert(make_pair(it->first, it->second));
        break;

        case OBSR :
        case OBSF :
        MapAKAObs.insert(make_pair(it->first, it->second));
        break;
      } // end switch
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::AKAcombine(TObject *Sender)
{
  Mapstr2::iterator it;

  MapAKACopy.clear();

  if(!MapAKAVar.empty()) // add variable commands
    for (it = MapAKAVar.begin(); it !=  MapAKAVar.end(); ++it)
        MapAKACopy.insert(make_pair(it->first, it->second));

  if(!MapAKAPar.empty()) // add parameter commands
    for (it = MapAKAPar.begin(); it !=  MapAKAPar.end(); ++it)
        MapAKACopy.insert(make_pair(it->first, it->second));

  if(!MapAKAObs.empty()) // add observation commands
    for (it = MapAKAObs.begin(); it !=  MapAKAObs.end(); ++it)
        MapAKACopy.insert(make_pair(it->first, it->second));

}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::EscapeClick(TObject *Sender)
{
  AKAseparate(Sender);
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::ClearGrid(TObject *Sender){

  for(int rr = 0; rr < StringGrid1->RowCount; ++rr)
    for(int cc = 0; cc < StringGrid1->ColCount; ++cc){
      StringGrid1->Cells[cc][rr] = "";
      StringGrid1->Objects[cc][rr] = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::StringGrid1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(selectRow < ROW2) return;

  int selectCol1, selectRow1; // must be INT
  StringGrid1->MouseToCell(X, Y, selectCol1, selectRow1);

  if(Button == mbRight && selectCol1 > REN){
    if(StringGrid1->Cells[selectCol1][selectRow1][1] == '['){ // return to original
      int Pos = StringGrid1->Cells[selectCol1][selectRow1].Pos(" ->");
      StringGrid1->Cells[selectCol1][selectRow1] = StringGrid1->Cells[selectCol1][selectRow1].SubString(3, Pos-3);
    }
    if(StringGrid1->Cells[REN][selectRow].IsEmpty())
      if(selectRow1 != selectRow) // do not make equal to itself
        StringGrid1->Cells[selectCol1][selectRow1] = String("[ ") + StringGrid1->Cells[selectCol1][selectRow1] + " -> " + StringGrid1->Cells[1][selectRow] + " ]";
      else
        StringGrid1->Cells[selectCol1][selectRow1] = StringGrid1->Cells[1][selectRow];
    else{ // rename
      if(StringGrid1->Cells[selectCol1][selectRow1] != StringGrid1->Cells[REN][selectRow]){
        if(StringGrid1->Cells[1][selectRow][StringGrid1->Cells[1][selectRow].Length()] == '#' && StringGrid1->Cells[REN][selectRow][StringGrid1->Cells[REN][selectRow].Length()] != '#')
          StringGrid1->Cells[REN][selectRow] = StringGrid1->Cells[REN][selectRow] + '#';
        if(StringGrid1->Cells[selectCol1][selectRow1][1] != '-')
          StringGrid1->Cells[selectCol1][selectRow1] = String("[ ") + StringGrid1->Cells[selectCol1][selectRow1] + " -> " + StringGrid1->Cells[REN][selectRow] + " ]";
      }
    }

    if(selectCol == 3)
      StringGrid1->Objects[selectCol1][selectRow1] = (TObject*) selectRow; // rename
    else
      StringGrid1->Objects[selectCol1][selectRow1] = (TObject*) -selectRow; // name
  }
  else if(Button == mbRight && selectCol1 == REN && !StringGrid1->Cells[REN][selectRow1].IsEmpty()){
    int rr = StringGrid1->Cols[1]->IndexOf(StringGrid1->Cells[REN][selectRow1]); // desired met observation

    if(rr == -1) { // assume it is a measured observation
      StringGrid1->RowCount = StringGrid1->RowCount + 1;
      StringGrid1->Rows[StringGrid1->RowCount-1]->Clear();
      StringGrid1->Cells[1][StringGrid1->RowCount-1] = StringGrid1->Cells[REN][selectRow1];
      StringGrid1->Cells[0][StringGrid1->RowCount-1] = "obs";
      rr = StringGrid1->RowCount-1;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::ReadMemo(TObject *Sender){

  istringstream instr;
  string type;
  Mapstr2 MapAKALocal;
  TAKA Type;

  for (int ii = 0; ii < Memo->Lines->Count; ++ii) {
    if(Memo->Lines->Strings[ii].IsEmpty())
      continue;
    instr.clear(); // check for sufficient data
    instr.str(Memo->Lines->Strings[ii].c_str());
    instr >> type >> module >> name >> Newname;

    Type = AKAtype(type);

    if(Type == VARG || Type == OBSR || Type == OBSF) {
      instr >> source;
      Newname += ' ' + source;
    }

    if(instr.fail() || Type == AKAERROR) {
      Application->MessageBox((OpenDialogAKA->FileName + " on line " + String(ii+1)).c_str(), "Faulty data", MB_OK);
      break;
    }

    if(Type != AKAERROR) {
      Pairstr2 Item = Pairstr2(type + " " + module + " " + name, Newname);
      MapAKALocal.insert(Item);
    }
  }

  switch (RadioGroup->ItemIndex) {
    case 0 :
               MapAKAVar.clear();
               MapAKAVar = MapAKALocal;
               DrawGridVar(Sender);
               break;
    case 1 :
               MapAKAObs.clear();
               MapAKAObs = MapAKALocal;
               DrawGridObs(Sender);
               break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::MemoDblClick(TObject *Sender)
{
  ReadMemo(Sender);
}
//---------------------------------------------------------------------------

bool __fastcall TFormAKA::OriginalVar(String module, String name){
// check if original variable in get or put
  Mapstr::iterator itMap, pos;
  pair<Mapstr::iterator, Mapstr::iterator> rangeI;

  String SS, S2;

  rangeI = Global::Mapgetvar.equal_range(module);
  for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {
    SS = itMap->second.first;
    int jj = SS.Pos(" ");
    S2 = SS.SubString(jj+1, SS.Length() - jj); // desired variable
    if(S2 == name)
      return true;
  }

  rangeI = Global::Mapputvar.equal_range(module);
  for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {
    SS = itMap->second.first;
    int jj = SS.Pos(" ");
    S2 = SS.SubString(jj+1, SS.Length() - jj); // desired variable
    if(S2 == name)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------

bool __fastcall TFormAKA::OriginalObs(String module, String name){
// check if primitive observation
  Mapstr::iterator itMap, pos;
  pair<Mapstr::iterator, Mapstr::iterator> rangeI;

  String SS, S2;

  rangeI = Global::Mapreadvar.equal_range(module);
  for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {
    SS = itMap->second.first;
    int jj = SS.Pos(" ");
    S2 = SS.SubString(jj+1, SS.Length() - jj); // desired variable
    if(S2 == name)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------

int __fastcall TFormAKA::MatchMod_Name(String module, String name, int Col){ // explicit match

  int Row;

  for(Row = 2; Row < StringGrid1->RowCount; ++Row) // was Row = 3
    if(module == StringGrid1->Cells[0][Row] && name == StringGrid1->Cells[Col][Row])
      return Row;

    return -1;
}
//---------------------------------------------------------------------------

int __fastcall TFormAKA::MatchSimple_Name(String name, int Col){ // finds simple match

  int Row;

  for(Row = 2; Row < StringGrid1->RowCount; ++Row) // was Row = 3
    if(!isGroup(StringGrid1->Cells[0][Row].c_str()) && name == StringGrid1->Cells[Col][Row])
      return Row;

    return -1;
}
//---------------------------------------------------------------------------

bool __fastcall TFormAKA::isGroup(string name){
  int Indx = Global::OurModulesList->IndexOf(name.c_str());
  if(Indx == -1)
    return false;
  ClassModule *thisMod = (ClassModule *) Global::OurModulesList->Objects[Indx];
  return (thisMod->GroupCnt > 0);
}
//---------------------------------------------------------------------------

bool __fastcall TFormAKA::isSame_decl(string name, string Newname){
  string s;
  if(name.size() > Newname.size())
    s = name.substr(Newname.size());
  else
    s = Newname.substr(name.size());

  if(s == "#")
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------

String  __fastcall TFormAKA::GetUnits(String S, String SS){

  MapVar::iterator itVar;
  string s = string(S.c_str()) + ' ' + SS.c_str();
  if((itVar = Global::MapVars.find(s)) != Global::MapVars.end()){
    ClassVar *thisVar = ((*itVar).second);
    return thisVar->units.c_str();
  }
  else
    return "";
}
//---------------------------------------------------------------------------

ClassVar*  __fastcall TFormAKA::GetVar(String S, String SS){

  MapVar::iterator itVar;
  string s = string(S.c_str()) + ' ' + SS.c_str();
  if((itVar = Global::MapVars.find(s)) != Global::MapVars.end())
    return ((*itVar).second);
  else
    return NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormAKA::AKAModuleDelete(Mapstr2 &MapAKAany){

  if(!MapAKAany.empty()) { // separate out AKA commands
    Mapstr2::iterator it;

    for (it = MapAKAany.begin(); it !=  MapAKAany.end(); ){
      string Var = (*it).first; // module, type and name

      string::size_type idx = Var.find(' ');
      idx = Var.find(' ', idx);
      Var = Var.substr(idx+1);
      idx = Var.find(' ', idx);
      string module = Var.substr(0, idx);
      bool erased = false;

      for(int ii = 0 ; ii < ListBox1->Items->Count; ++ii) {
        if(ListBox1->Selected[ii] == false  && ListBox1->SelCount != 0) continue;
          if(module == ListBox1->Items->Strings[ii].c_str()){
            MapAKAany.erase(it++);
            erased = true;
            break;
          }
      }
      if(!erased)
        ++it;
    }
  }
}

