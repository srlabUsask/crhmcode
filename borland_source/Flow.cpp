// 10/03/16
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Flow.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include <printers.hpp>
#include <Graphics.hpp>
#include "About.h"
#include "CRHMmain.h"
#include <vcl\Clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFlowForm *FlowForm;

using namespace std;

//---------------------------------------------------------------------------
__fastcall TFlowForm::TFlowForm(TComponent* Owner)
        : TForm(Owner){ // Init
        
  pFlow = NULL;
  pMetafile = NULL;
  OurDiagram = NULL;
  LocalModulesList = NULL;

  if(Printer()->Printers->Count){
    Printer()->Orientation = poLandscape;
  }
  else {
    TMenuItem *FileItem0 = File1->Items[0]; // Print1Click
    FileItem0->Enabled = false;
    TMenuItem *FileItem1 = File1->Items[1]; // PrinterSetup1Click
    FileItem1->Enabled = false;
  }
  
  DisplyPar = true;

}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::DeleteRow(TStringGrid *Grid, int Row) {

  for(int rr = Row; rr < Grid->RowCount-1; ++rr)
    Grid->Rows[rr] = Grid->Rows[rr+1];
  Grid->RowCount = Grid->RowCount - 1;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::DeleteBlankRows(TStringGrid *Grid) {

  for(int rr = Grid->RowCount - 1; rr > 1 ; --rr) {
    bool Used = false;
    for (int cc = 1; cc < Grid->ColCount; ++cc) {
      if(Grid->Rows[rr]->Strings[cc] != "") {
        Used = true;
        break;
      }
    }
    if(!Used) DeleteRow(Grid, rr);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::DeleteCol(TStringGrid *Grid, int Column) {
  for(int cc = Column; cc < Grid->ColCount-1; ++cc)
    Grid->Cols[cc] = Grid->Cols[cc+1];
  Grid->ColCount = Grid->ColCount - 1;
}
//---------------------------------------------------------------------------
void __fastcall TFlowForm::FormActivate(TObject *Sender){

  if(OurCntrl)
    StringGrid1->Visible = true;
  else
    StringGrid1->Visible = false;

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::BuildFlag = CRHM::BUILD; // default value

  if(LocalModulesList != NULL)
    delete LocalModulesList;
    
  LocalModulesList = new TStringList; // holds parameters/observations already used
  LocalModulesList->Assign(Global::OurModulesList);

  for(int ii = 0; ii < Global::OurModulesList->Count; ii++){
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    thisModule->variation_max = 0;
    thisModule->decl();
  }

  Global::BuildFlag = CRHM::DECL; // model loaded

  DrawGrid(Sender);

  if(LocalModulesList->Count <= 0) {
  
    if(pMetafile)
      pMetafile->Clear();
      
    Application->MessageBox("No modules to display", "No Model loaded", MB_OK);
    return;
  }

  if(OurDiagram != NULL)
    delete OurDiagram;

  OurDiagram = new Diagram(FlowForm);

  OurDiagram->DrawModules();
  
  FormPaint(Sender);
  
  OurCntrl = false;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::DrawGrid(TObject *Sender){

  Mapstr::iterator itMap, pos;

  pair<Mapstr::iterator, Mapstr::iterator> rangeO;
  pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
  pair<Mapstr::iterator, Mapstr::iterator> rangeI;
  pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;

  String S, S1, S2, SS;
  TGridOptions OurOptions;

  OurOptions << goFixedVertLine << goFixedHorzLine << goVertLine
             << goHorzLine << goTabs << goColSizing;
  StringGrid1->Options = OurOptions;

  StringGrid1->FixedCols = 0;
  StringGrid1->FixedRows = 0;
  
  StringGrid1->ColCount = 1; // minimum allowed by FixedCols
  StringGrid1->RowCount = LocalModulesList->Count + 2;

  StringGrid1->Cells[0][0] = "Variable";
  StringGrid1->Cells[0][1] = "Module";

  for (int ii = 0; ii < LocalModulesList->Count; ++ii)
    StringGrid1->Cells[0][ii+2] = LocalModulesList->Strings[ii];

  for(int ii = 0 ; ii < LocalModulesList->Count; ++ii) {

    S = LocalModulesList->Strings[ii];

    rangeO = Global::Mapdeclvar.equal_range(S);
    rangeOobs = Global::Mapdeclobs.equal_range(S);

// add current modules declared variables to list

    for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
      SS = itMap->second.first;
      pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
            value_equals<KeyType2,  KeyType2, Pairstr>(SS));

      if(pos == Global::Mapreadvar.end() && SS[SS.Length()] != '#' && StringGrid1->Rows[0]->IndexOf(SS) < 0 && Variation_Decide(ii, itMap->second.second)){ // NO read or declared OBS
        StringGrid1->ColCount = StringGrid1->ColCount + 1;
        StringGrid1->Cols[StringGrid1->ColCount-1]->Clear();
        StringGrid1->Cells[StringGrid1->ColCount-1][0] = SS; // variable
        StringGrid1->Cells[StringGrid1->ColCount-1][ii+2] = "D";
        StringGrid1->Cells[StringGrid1->ColCount-1][1] = S; // module
      }
    }

// add current modules declared observations to 'list'

    for(itMap = rangeOobs.first; itMap != rangeOobs.second; itMap++) {
      SS = itMap->second.first; // declared observation
      if(Variation_Decide(ii, itMap->second.second)){
        StringGrid1->ColCount = StringGrid1->ColCount + 1;
        StringGrid1->Cols[StringGrid1->ColCount-1]->Clear();
        StringGrid1->Cells[StringGrid1->ColCount-1][0] = SS; // declared observation
        StringGrid1->Cells[StringGrid1->ColCount-1][ii+2] = "DO";
        StringGrid1->Cells[StringGrid1->ColCount-1][1] = S; // module
      } // if
    } // for
  }

// add current modules get/put variables to list

  for (int ii = 0; ii < LocalModulesList->Count; ++ii) {

    S = LocalModulesList->Strings[ii];

    rangeI = Global::Mapgetvar.equal_range(S);
    rangeIobs = Global::Mapreadvar.equal_range(S);

    for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {

      SS = itMap->second.first;
      if(Variation_Decide(ii, itMap->second.second)){
      int jj = SS.Pos(" ");
      S1 = SS.SubString(1, jj-1);  // module
      S2 = SS.SubString(jj+1, SS.Length() - jj); // variable

      int cc = StringGrid1->Rows[0]->IndexOf(S2); // variable
      int rr = StringGrid1->Cols[0]->IndexOf(S); // module
      if(cc == -1){
        String V2;
        int indx = S2.Pos("@");
        if(indx > 0){
          V2 = S2.SubString(1, indx);
          cc = StringGrid1->Rows[0]->IndexOf(V2); // simple variable
          if(cc == -1){
            for(int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2) { // group variable
              String V3 = StringGrid1->Cells[cc2][0].SubString(1, StringGrid1->Cells[cc2][0].Pos("@"));
              if(V2 == V3){
                cc = cc2;
                break;
              }
            }
          }
        }
        else{ // simple variable to group/struct
          for(int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2) { // group variable
            String V3 = StringGrid1->Cells[cc2][0].SubString(1, StringGrid1->Cells[cc2][0].Pos("@"));
            if(S2 == V3){
              cc = cc2;
              break;
            }
          }
        }
      } // if
      if(rr > -1 && cc > -1 && S != StringGrid1->Cells[cc][1]) // Equal implies group
        if(Variation_Decide(ii, itMap->second.second)){
          if(S1 == "*")
            StringGrid1->Cells[cc][rr] = "*G";
          else
            StringGrid1->Cells[cc][rr] = "G";
        }
      } // if decide
    }
    rangeI = Global::Mapputvar.equal_range(S);

    for(itMap = rangeI.first; itMap != rangeI.second; itMap++) {

      SS = itMap->second.first;
      if(Variation_Decide(ii, itMap->second.second)){
      int jj = SS.Pos(" ");
      S1 = SS.SubString(1, jj-1);  // module
      S2 = SS.SubString(jj+1, SS.Length() - jj); // variable

      int cc = StringGrid1->Rows[0]->IndexOf(S2); // variable
      int rr = StringGrid1->Cols[0]->IndexOf(S); // module
      if(cc == -1){
        if(Variation_Decide(ii, itMap->second.second)){
          String V2;
          int indx = S2.Pos("@");
          if(indx > 0){
            V2 = S2.SubString(1, indx);
            cc = StringGrid1->Rows[0]->IndexOf(V2); // variable
            if(cc == -1){
              for(int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2) {
                String V3 = StringGrid1->Cells[cc2][0].SubString(1, StringGrid1->Cells[cc2][0].Pos("@"));
                if(V2 == V3){
                  cc = cc2;
                  break;
                }
              }
            }
          }
        }
      }

      if(rr > -1 && cc > -1 && S != StringGrid1->Cells[cc][1]){ // Equal implies group
          if(S1 == "*")
            StringGrid1->Cells[cc][rr] = "*P";
          else
            StringGrid1->Cells[cc][rr] = "P";
      }
    } // if decide
    } // for

// add needed macro observations to ListUsed

    for(itMap = rangeIobs.first; itMap != rangeIobs.second; itMap++) {
      SS = itMap->second.first; // variable
      pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
            value_equals<KeyType2,  KeyType2, Pairstr>(SS));

      if(pos == Global::Mapdeclobs.end()) continue; // not available or met observation
        if(Variation_Decide(ii, itMap->second.second)){
          S1 = pos->first; // module
          S2 = pos->second.first;
          int cc = MatchDecl_Obs(S, S2); // variable - handles multiple groups
          if(cc > -1) continue; // in group
          cc     = StringGrid1->Rows[0]->IndexOf(S2); // simple module
          int rr = StringGrid1->Cols[0]->IndexOf(S); // module
          if(rr > -1 && cc > -1) {
            StringGrid1->Cells[cc][rr] = "O";
        }
      }
    } // for rangeIobs
  }  // for rangeI

  if(StringGrid1->ColCount > 1) StringGrid1->FixedCols = 1;
  if(StringGrid1->RowCount > 2) StringGrid1->FixedRows = 2;

// Remove any modules not used

  for (int ii = 0; ii < LocalModulesList->Count; ++ii) {

    S = LocalModulesList->Strings[ii];

    int mm = StringGrid1->Rows[1]->IndexOf(S);
    if(mm == -1) // if not in row - not used
      if(StringGrid1->Rows[ii+2]->IndexOf("P") == -1 && StringGrid1->Rows[ii+2]->IndexOf("P*") == -1 || S == "shared"){ // was basin
        int result = IDNO;
        if(result == IDYES ||	S == "shared"){ // was basin
          DeleteRow(StringGrid1, ii+2);
          LocalModulesList->Delete(ii--); // Entry deleted ! back-up index!
        }
        else {

          S = LocalModulesList->Strings[ii];
          rangeO = Global::Mapdeclvar.equal_range(S);

          for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
            SS = itMap->second.first;
            pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
              value_equals<KeyType2,  KeyType2, Pairstr>(SS));

            if(pos == Global::Mapreadvar.end()){
              if(Variation_Decide(ii, itMap->second.second)){
                      StringGrid1->ColCount = StringGrid1->ColCount + 1;
                      StringGrid1->Cols[StringGrid1->ColCount-1]->Clear();
                      StringGrid1->Cells[StringGrid1->ColCount-1][0] = SS;
                      StringGrid1->Cells[StringGrid1->ColCount-1][ii+2] = "D";
                      StringGrid1->Cells[StringGrid1->ColCount-1][1] = S;
              }
            }
          }
        }
      } // if
  } // for

// delete unused fields. Leave outputs of unused modules.

  long* UseCount = new long[LocalModulesList->Count]; // find unused modules
  for (int ii = 0; ii < LocalModulesList->Count; ++ii)
    UseCount[ii] = 0;

  for(int cc = StringGrid1->ColCount - 1; cc > 0 ; --cc) {

    for (int ii = 0; ii < LocalModulesList->Count; ++ii) {
      if(StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "*P" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "O"){
        long indx = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
          ++UseCount[indx];
      }
    } // for
  }

  for(int cc = StringGrid1->ColCount - 1; cc > 0 ; --cc) {

    bool Used = false;
    for (int ii = LocalModulesList->Count-1; ii > 0; --ii) { // deleting - reverse order

      if(StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "*P" ||
        StringGrid1->Cols[cc]->Strings[ii+2] == "O" ){
          Used = true;
          break;
      }
    }

    long indx = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
    if(!Used && UseCount[indx] != 0) // remove unused outputs except on unused modules
      DeleteCol(StringGrid1, cc);
  } // for

  delete[] UseCount;

  int CurVarIndx = 0;
  int CurModIndx = -1;
  for(int cc = StringGrid1->ColCount - 1; cc > 0 ; --cc) {

    int mm = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);

    if(mm != CurModIndx) { // first module output
      CurModIndx = mm;
      CurVarIndx = 0;
    }
    else
      ++CurVarIndx;

    StringGrid1->Cols[cc]->Objects[1] = (TObject*) CurModIndx; // module position in LocalModulesList
    StringGrid1->Cols[cc]->Objects[0] = (TObject*) CurVarIndx; // range (0 -> max) in reverse order

  } // for
}
//---------------------------------------------------------------------------

Diagram::Diagram(TFlowForm *FlowForm) : FlowForm(FlowForm) {

  int Count = FlowForm->LocalModulesList->Count;

  Boxes = new Box[Count];

  CSpacing = FlowForm->Canvas->TextHeight("ABC") + 1;

  Width = FlowForm->ClientWidth/Count/4;
  Width = (Width/CSpacing +1)*CSpacing;
  Height = FlowForm->ClientHeight/Count/2;
  Height = (Height/CSpacing +1)*CSpacing;

  HSpacing = (Width/2/CSpacing +1)*CSpacing;
  VSpacing = (Height/2/CSpacing +1)*CSpacing;
}
//---------------------------------------------------------------------------

Diagram::~Diagram() {

  delete[] Boxes;
}
//---------------------------------------------------------------------------

void Diagram::DrawModules(){

  Mapstr::iterator itMap;
  pair<Mapstr::iterator, Mapstr::iterator> rangeO;

  String S, SS;

  if(FlowForm->pMetafile != NULL)
    delete FlowForm->pMetafile;

  FlowForm->pMetafile = new TMetafile;

  FlowForm->pMetafile->Enhanced = true; // no effect

  FlowForm->pFlow = new TMetafileCanvas(FlowForm->pMetafile, 0);

  TStringList *List = new TStringList;     // holds parameters/observations already used
  TStringList *ModList = new TStringList;  // holds parameters/observations already used in current module
  TStringList *InputCnt = new TStringList; // holds parameters/observations use count

  int ObsX = CSpacing*8;
  int X = ObsX ;
  int Y = VSpacing;

  int AdjWidth;
  int AdjHeight;

  for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

    S = FlowForm->LocalModulesList->Strings[ii];

// find 'forward' PUT and GET inputs to make space for them

    for(int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

      if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G") {

        int Mod = (int) FlowForm->StringGrid1->Cols[cc]->Objects[1];

        if(ii < Mod){ // later module
          ++Boxes[ii].PadjY;
        } // if later PUT
      } // if PUT
    } // for Columns
  } // for Modules

// Determine parameters or observations used more than once
//   Problem with groups and MultiMaps the same parameter can occur more than once in the group.

      
  for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

    S = FlowForm->LocalModulesList->Strings[ii];

// plot parameters or observations

    Mapstr::iterator pos, End;
    if(FlowForm->DisplyPar) {
      Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
      rangeO = Global::Mapdeclpar.equal_range(S);
      End = Global::Mapdeclpar.end();
    }
    else {
      Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
      rangeO = Global::Mapreadvar.equal_range(S);
      End = Global::Mapreadvar.end();
    }

    for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
      SS = itMap->second.first; // name of parameter or observation
      if(FlowForm->Variation_Decide(ii, itMap->second.second)){
      int Indx = InputCnt->IndexOf(SS);
      if(Indx == -1) // first time
        InputCnt->AddObject(SS, (TObject*) -1);
      else{
        int InCnt = (int) InputCnt->Objects[Indx];
        if(InCnt > 0)
          InputCnt->Objects[Indx] = (TObject*) -2; // make negative - cannot count again this group (module)

      } // else
    } // decide
    } // for

    for( int ii = 0; ii < InputCnt->Count; ++ii) // make positive
      InputCnt->Objects[ii] = (TObject*) abs((int) InputCnt->Objects[ii]);

}

// Find module that parameter or observation first used

  for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

    S = FlowForm->LocalModulesList->Strings[ii];
    
// plot parameters or observations

    Mapstr::iterator pos, End;
    if(FlowForm->DisplyPar) {
      Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
      rangeO = Global::Mapdeclpar.equal_range(S);
      End = Global::Mapdeclpar.end();
    }
    else {
      Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
      rangeO = Global::Mapreadvar.equal_range(S);
      End = Global::Mapreadvar.end();
    }

    for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
      SS = itMap->second.first; // name of parameter or observation
      int Indx = InputCnt->IndexOf(SS);
      if(Indx > -1){
        int InCnt = (int) InputCnt->Objects[Indx];
        if(InCnt > 1){
          ++Boxes[ii].ObsCntX;
          InputCnt->Objects[Indx] = (TObject*) -2; // make negative - cannot count again this group (module)
        }
      }
    }

    for( int ii = 0; ii < InputCnt->Count; ++ii) // make positive
      InputCnt->Objects[ii] = (TObject*) abs((int) InputCnt->Objects[ii]);
  }

  for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

    S = FlowForm->LocalModulesList->Strings[ii];

// plot parameters or observations

    X = X + Boxes[ii].ObsCntX*CSpacing;

    Mapstr::iterator pos, End;
    if(FlowForm->DisplyPar) {
      Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
      rangeO = Global::Mapdeclpar.equal_range(S);
      End = Global::Mapdeclpar.end();
    }
    else {
      Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
      rangeO = Global::Mapreadvar.equal_range(S);
      End = Global::Mapreadvar.end();
    }

    int jj = 0;
    int kk = 0;

    ModList->Clear(); // reset for this module

    for(itMap = rangeO.first; itMap != rangeO.second; itMap++) {
      SS = itMap->second.first; // name of parameter or observation
      if(!FlowForm->Variation_Decide(ii, itMap->second.second)) // ignore
        continue;
      if(ModList->IndexOf(SS) > -1) // only once per module
        continue;

      ModList->Add(SS);

      int Indx = InputCnt->IndexOf(SS); // Multiple input?
      kk = 0;
      if(InputCnt->Objects[Indx] == (TObject*) 2)
        ++kk;

      ++jj;

      Indx = List->IndexOf(SS);
      if(Indx == -1) {
        FlowForm->pFlow->MoveTo(CSpacing, Y + Height/2 + jj*CSpacing);
        FlowForm->pFlow->LineTo(X, Y + Height/2 + jj*CSpacing);
        FlowForm->pFlow->TextOut(CSpacing, Y + Height/2 + (jj-1)*CSpacing +1, SS);

        ++Boxes[ii].PadjX;
        
        ModandVar XY;
        XY.PutX(ObsX);
        XY.PutY(Y + Height/2 + jj*CSpacing);

        List->AddObject(SS, (TObject*) XY.both);

        ObsX += (kk*CSpacing);
      }
      else {
        ModandVar XY;
        XY.both = (int) List->Objects[Indx];

        FlowForm->pFlow->MoveTo(XY.GetX(), XY.GetY());
        FlowForm->pFlow->LineTo(XY.GetX(), Y + Height/2 + jj*CSpacing);
        FlowForm->pFlow->LineTo(X, Y + Height/2 + jj*CSpacing);

        XY.PutY(Y + Height/2 + jj*CSpacing);
        List->Objects[Indx] = (TObject*) XY.both;

        int W = FlowForm->pFlow->TextWidth(SS);
        FlowForm->pFlow->TextOut(X - W - 1, Y + Height/2 + (jj-1)*CSpacing +1, SS);

      } // else
    } // for

// plot get variable inputs

    Boxes[ii].InCnt = 0;
    for(int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

      if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P") {

        ++Boxes[ii].InCnt;
        int Var = (int) FlowForm->StringGrid1->Cols[cc]->Objects[0];
        int Mod = (int) FlowForm->StringGrid1->Cols[cc]->Objects[1];
        int ToX, ToY;
        int InX = X + Width/2 + Boxes[ii].InCnt*CSpacing - CSpacing/2;

        if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
          FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G"){
          Boxes[Mod].GetXY(Var, InX, ToX, ToY);
          if(ii > Mod){
            FlowForm->pFlow->MoveTo(InX, Y);
            FlowForm->pFlow->LineTo(InX, ToY);
            FlowForm->pFlow->LineTo(ToX, ToY);
          }
        }
      } // if
    } // for

// plot module box

    int First, Last;
    Boxes[ii].OutCnt = FlowForm->GetNumVar(ii, First, Last);

    Boxes[ii].OutXs = new int[Boxes[ii].OutCnt];
    Boxes[ii].OutYs = new int[Boxes[ii].OutCnt];
    
    for(int jj = 0; Boxes[ii].OutCnt > jj; ++jj) {
      Boxes[ii].OutXs[jj] = 0;
      Boxes[ii].OutYs[jj] = 0;
    } // for

    AdjWidth = Width + Boxes[ii].InCnt*CSpacing;
    AdjHeight = Height + max(Boxes[ii].OutCnt, Boxes[ii].ObsCnt)*CSpacing;
    Boxes[ii].Height = Height;

    FlowForm->pFlow->RoundRect(X, Y, X + AdjWidth, Y + AdjHeight, 10, 10);

// save values

    Boxes[ii].Xul = X;
    Boxes[ii].Yul = Y;

    Boxes[ii].Xlr = X + AdjWidth;
    Boxes[ii].Ylr = Y + AdjHeight;

    Boxes[ii].CSpacing = CSpacing;

// plot variable output names

    for(int cc = First; Last > cc; ++cc){
      String S = FlowForm->StringGrid1->Cols[cc]->Strings[0];
      FlowForm->pFlow->TextOut(X + AdjWidth + 1, Y + Height/2 + (cc-First)*CSpacing, S);

      int W = FlowForm->pFlow->TextWidth(S);
      W = (W/CSpacing +1)*CSpacing;
      if(W > Boxes[ii].MaxOutNameLen)
        Boxes[ii].MaxOutNameLen = W;
    }

// plot module name

    int W = FlowForm->pFlow->TextWidth(FlowForm->LocalModulesList->Strings[ii]);

    String S = FlowForm->LocalModulesList->Strings[ii]; // add variation
    ClassModule* thisModule = (ClassModule*) FlowForm->LocalModulesList->Objects[ii];
    if(thisModule->variation != 0){
      String AA("#0");
      AA[2] += log(thisModule->variation)/log(2) + 1;
      S += AA;
    }

    FlowForm->pFlow->TextOut(X + AdjWidth/2 - W/2, Y + AdjHeight + VSpacing/4, S);
    X = X + Boxes[ii].MaxOutNameLen + AdjWidth;
    Y = Y + VSpacing + AdjHeight;
  } // for

  Xmax = (X/20 + 2)*20;
  Ymax = (Y/20 + 2)*20;

  int Yn = Global::MapAKA.size() + 5;
  int Xn = Xmax - 350;

// plot backward PUT or GET variables

  for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

    X = Boxes[ii].Xul;
    Y = Boxes[ii].Yul;
    
    Boxes[ii].InCnt = 0;
    long Back_PGs = 0; // used to offset forward lines

    for(int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

      if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
        FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P") {

        ++Boxes[ii].InCnt;
        int Var = (int) FlowForm->StringGrid1->Cols[cc]->Objects[0];
        int Mod = (int) FlowForm->StringGrid1->Cols[cc]->Objects[1];
        int ToX, ToY;
        int InX = X + Width/2 + Boxes[ii].InCnt*CSpacing - CSpacing/2;

          Boxes[Mod].GetXY(Var, InX, ToX, ToY);
          int W = FlowForm->pFlow->TextWidth(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2]);
          if(ii > Mod){
            if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "P" ||
              FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*P"){
              FlowForm->pFlow->TextOut(InX-W/2, Y + CSpacing/4, FlowForm->StringGrid1->Cols[cc]->Strings[ii+2]);

              FlowForm->pFlow->MoveTo(InX, Y);
              FlowForm->pFlow->LineTo(InX, ToY);
              FlowForm->pFlow->LineTo(ToX, ToY);
            }
          }
          else { // forward puts and gets
            if(FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "G" ||
              FlowForm->StringGrid1->Cols[cc]->Strings[ii+2] == "*G"){
              String Message = "backward GET" + String(" variable \"") +
                FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
                FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
                FlowForm->StringGrid1->Cols[0]->Strings[ii+2];
              FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
            }
            else{
              String Message = "backward PUT" + String(" variable \"") +
                FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
                FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
                FlowForm->StringGrid1->Cols[0]->Strings[ii+2];
              FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
            }

            FlowForm->pFlow->TextOut(InX-W/2, Y + CSpacing/4, FlowForm->StringGrid1->Cols[cc]->Strings[ii+2]);
            FlowForm->pFlow->MoveTo(InX, Y);
            FlowForm->pFlow->LineTo(InX, Y-(Boxes[ii].PadjY -Back_PGs)*CSpacing);

            float XX = Boxes[Mod].Xlr + (Boxes[Mod].OutCnt - Var)*CSpacing + CSpacing + Boxes[Mod].MaxOutNameLen;

            FlowForm->pFlow->LineTo(XX, Y-(Boxes[ii].PadjY -Back_PGs++)*CSpacing);
            FlowForm->pFlow->LineTo(XX, ToY);
            FlowForm->pFlow->LineTo(Boxes[Mod].Xlr, ToY);
          }
      }
    } // for
  } // for

  if(!Global::MapAKA.empty()) {
    Mapstr2::iterator it;

    int Yn = 3; int Yf = 3;
    int Xn = Xmax - 350; int Xf = Xn + 25;

    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {

      string Message = (*it).first;
      Message = Message.substr(Message.find(' ')+1);
      Message.insert(Message.find(' ')+1, " -  ");
      Message = '\"' + Message + '\"';

      if(Yn == 3)
        FlowForm->pFlow->TextOut(Xn, Yn++*CSpacing, "AKAs.");
      string Message2 = (*it).second;
      string::size_type idx = Message2.find(' ');
      Message += " linked to \"" + Message2.substr(idx+1) + " - " + Message2.substr(0, idx) + '\"';
      FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
    }
  }

  int Mod = FlowForm->LocalModulesList->Count-1;
  Xmax += Boxes[Mod].MaxOutNameLen  + (Boxes[Mod].OutCnt -1)*CSpacing;

  FlowForm->pFlow->MoveTo(Xmax-20, Ymax);
  FlowForm->pFlow->LineTo(Xmax, Ymax);
  FlowForm->pFlow->LineTo(Xmax, Ymax-20);

  int W = FlowForm->pFlow->TextWidth(FlowForm->Title);
  FlowForm->pFlow->TextOut(Xmax/2 - W/2, CSpacing, FlowForm->Title);

  FlowForm->HorzScrollBar->Range = Xmax;
  FlowForm->VertScrollBar->Range = Ymax;

  delete FlowForm->pFlow;

  FlowForm->pFlow->Refresh();

  delete List;
  delete ModList;
  delete InputCnt;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::FormDestroy(TObject *Sender)
{
  delete OurDiagram;

  delete LocalModulesList;

  delete pMetafile;
}
//---------------------------------------------------------------------------

int __fastcall TFlowForm::GetNumVar(int Mod, int &First, int &Last){

  First = -1;
  Last = -1;

  for(int cc = 1; cc < StringGrid1->ColCount; ++cc) {

    if((int) StringGrid1->Cols[cc]->Objects[1] == Mod) {
      if(First == -1) {
        First = cc;
        Last = First;
      }
      ++Last;
    }
  }
  if(First == -1){

    String S = LocalModulesList->Strings[Mod];
    return 0;
  }

  return (Last - First);  // Last is one greater
}
//---------------------------------------------------------------------------

Box::~Box() {

  if(OutXs){
    delete[] OutXs;
    delete[] OutYs;
  }
}
//---------------------------------------------------------------------------

void Box::GetXY(int Out_Var, int InX, int &ToX, int &ToY){

  if(!OutXs) {
    ToX = 0;
    ToY = 0;
    return;
  }

  if(OutXs[Out_Var] != 0) {
    ToX = OutXs[Out_Var];
    OutXs[Out_Var] = InX;
  }
  else
    ToX = Xlr;

  ToY = Yul + Height/2 + (OutCnt - Out_Var)*CSpacing;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::Exit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::FormResize(TObject *Sender)
{
  Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::FormPaint(TObject *Sender)
{

  FlowForm->Canvas->Brush->Color = clWhite;
  FlowForm->Canvas->FillRect(Rect(0, 0, FlowForm->ClientWidth, FlowForm->ClientHeight));
  
  int X = FlowForm->HorzScrollBar->Position;
  int Y = FlowForm->VertScrollBar->Position;

  FlowForm->Canvas->Draw(-X, -Y, pMetafile);

}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::FormCreate(TObject *Sender)
{
  FlowForm->HorzScrollBar->Range = FlowForm->ClientWidth;
  FlowForm->VertScrollBar->Range = FlowForm->ClientHeight;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::Print1Click(TObject *Sender){

  TPicture *pPicture = new TPicture;

  pPicture->Metafile = pMetafile;

  Printer()->BeginDoc();

  float ScaleX = (float) pPicture->Width/OurDiagram->Xmax;
  float ScaleY = (float) pPicture->Height/OurDiagram->Ymax;

  Printer()->Canvas->StretchDraw(Rect(0, 0, Printer()->PageWidth*ScaleX, Printer()->PageHeight*ScaleY), pPicture->Graphic);

  Printer()->EndDoc();

  delete pPicture;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::PrinterSetUp1Click(TObject *Sender)
{
  //Bring up the print setup dialog box
  PrinterSetupDialog1->Execute();
  //Change the font of the printer just in case user changed
  Printer()->Canvas->Font = FontDialog1->Font;
}
//---------------------------------------------------------------------------

void TFlowForm::SetTitle(String Text){
  Title = Text;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::Selection1Click(TObject *Sender){

  DisplyPar = !DisplyPar;

  FormActivate(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::BitFile1Click(TObject *Sender)
{
  TPicture *pPicture = new TPicture;
  
  pPicture->Metafile = pMetafile;
  Clipboard()->Assign(pPicture);

  delete pPicture;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::MetaFile1Click(TObject *Sender){

  TPicture *pPicture = new TPicture;

  pPicture->Metafile = pMetafile;

  FlowForm->pFlow = new TMetafileCanvas(pPicture->Metafile, 0);

  float ScaleX = (float) pMetafile->Width/OurDiagram->Xmax;
  float ScaleY = (float) pMetafile->Height/OurDiagram->Ymax;

//  FlowForm->Canvas->Brush->Color = clWhite;
//  FlowForm->Canvas->FillRect(Rect(0, 0, FlowForm->Width, FlowForm->Height));

  FlowForm->pFlow->Refresh();
  FlowForm->Canvas->Refresh();

//  FlowForm->Canvas->StretchDraw(Rect(0, 0, FlowForm->Width*ScaleX, FlowForm->Height*ScaleY), pPicture->Graphic);
//  FlowForm->Canvas->StretchDraw(Rect(100, 100, 1, 1), pPicture->Graphic);
//  Clipboard()->Canvas->Draw(100, 100, pPicture->Graphic);

  pPicture->Graphic->SaveToFile("c:\\oneeye.jpg");

  Clipboard()->Assign(pPicture->Graphic);

  FlowForm->pFlow->Refresh();

  delete pPicture;
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Shift.Contains(ssCtrl)){
    OurCntrl = true; // display StringGrid
  }
  else{
    OurCntrl = false; // do not display StringGrid
  }
}
//---------------------------------------------------------------------------

void __fastcall TFlowForm::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  OurCntrl = false; // do not display StringGrid
}
//---------------------------------------------------------------------------

int __fastcall TFlowForm::MatchDecl_Obs(String module, String Obs){

  int Col;

  for(Col = 2; Col < StringGrid1->ColCount; ++Col) //
    if(module == StringGrid1->Cells[Col][1] && Obs == StringGrid1->Cells[Col][0])
      return Col;

    return -1;
}
//---------------------------------------------------------------------------

bool TFlowForm::Variation_Decide(int indx, long Variation){

  ClassModule* thisModule = (ClassModule*) FlowForm->LocalModulesList->Objects[indx];

  VandP V; V.Set(Variation);

  long variations = V.GetV(); // & 2047;
  
  long Variation_set = thisModule->variation;

  if((variations & 2048) != 0 && Variation_set == 0 || // handles VARIATION_0
    (variations & 4096) != 0 ||                        // handles VARIATION_0
    (variations == 0) ||                               // handles VARIATION_ORG
    (variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
    return true;
  else
    return false;
}

