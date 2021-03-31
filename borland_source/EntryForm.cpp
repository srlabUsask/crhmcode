// 02/06/19
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EntryForm.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormEntry *FormEntry;

long Module::GrpCnt;
long Module::StructCnt;


//---------------------------------------------------------------------------
__fastcall TFormEntry::TFormEntry(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::FormActivate(TObject *Sender)
{
  if(SaveDialogMcr->InitialDir.IsEmpty())
    SaveDialogMcr->InitialDir = GetCurrentDir();

  if(OpenDialogMcr->InitialDir.IsEmpty())
    OpenDialogMcr->InitialDir = GetCurrentDir();

  Memo->Lines->Clear();

  for (int ii = 0; ii < Global::MacroModulesList->Count; ++ii)
    Memo->Lines->Add(Global::MacroModulesList->Strings[ii]);

  Memo->SelStart = 0;
  Memo->SetFocus();

  Module::GrpCnt = 0;
  Module::StructCnt = 0;

  ParaList = NULL;
  AKAList = NULL;

  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::DoSave(TObject *Sender)
{
  if(Memo->SelLength == 0)
    Memo->Lines->SaveToFile(SaveDialogMcr->FileName);
  else {
    MemoFile->Text = Memo->SelText;
    MemoFile->Lines->SaveToFile(SaveDialogMcr->FileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::ExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::SaveClick(TObject *Sender)
{
  if(!SaveDialogMcr->FileName.IsEmpty())
    DoSave(Sender);
  else SaveAsClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::SaveAsClick(TObject *Sender)
{
  SaveDialogMcr->Title = "Save As";

  SaveDialogMcr->DefaultExt = "mcr";
  SaveDialogMcr->Filter = "Save Macro Files (*.mcr)|*.mcr";
  if(SaveDialogMcr->Execute()){
    SaveDialogMcr->InitialDir = ExtractFilePath(SaveDialogMcr->FileName);
    if(SaveDialogMcr->InitialDir.IsEmpty())
      SaveDialogMcr->InitialDir = GetCurrentDir();

    DoSave(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::DoLoad(TObject *Sender)
{
  MemoFile->Clear();
  MemoFile->Lines->LoadFromFile(OpenDialogMcr->FileName);
  MemoFile->SelectAll();
  Memo->SelText = MemoFile->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::OpenClick(TObject *Sender)
{
  OpenDialogMcr->Filter = "Macro Files (*.mcr)|*.mcr";
  OpenDialogMcr->DefaultExt = "mcr";
  OpenDialogMcr->Title = "Open Macro File";
  if(OpenDialogMcr->Execute()) {

    OpenDialogMcr->InitialDir = ExtractFilePath(OpenDialogMcr->FileName);
    if(OpenDialogMcr->InitialDir.IsEmpty())
      OpenDialogMcr->InitialDir = GetCurrentDir();

    SaveDialogMcr->InitialDir = OpenDialogMcr->InitialDir;

    DoLoad(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::SaveChangesClick(TObject *Sender)
{
  Global::MacroModulesList->Clear();

  for (int ii = 0; ii < Memo->Lines->Count; ++ii) {
    String S;
    if(Memo->Lines->Strings[ii].IsEmpty())
      S = " "; // make empty line a space. Empty lines detected as end
    else
      S = Memo->Lines->Strings[ii].TrimRight();
      
    Memo->Lines->Strings[ii] = S;
    Global::MacroModulesList->Add(S);
  }

  Memo->SelStart = 0;
  Memo->SetFocus();

  if(ParaList){
    ParaList->Add("#####");
    SaveDialogPar->Filter = "Parameter Files (*.par)|*.par";
    SaveDialogPar->DefaultExt = "par";
    SaveDialogPar->Title = "Save Original Parameters As (Load this parameter file after Building the new project to keep the parameters from the cloned projects)";
    SaveDialogPar->InitialDir = GetCurrentDir();
    SaveDialogPar->FileName = "CreateGroup.par";
    if(SaveDialogPar->Execute()) {
      ParaList->SaveToFile(SaveDialogPar->FileName);
      delete ParaList;
      ParaList = NULL;
    }
  }
  
  if(AKAList && AKAList->Count){
    SaveDialogPar->FileName = "CreateGroup.aka";
    AKAList->SaveToFile(SaveDialogPar->FileName);
    delete AKAList;
    AKAList = NULL;
  }
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::CancelChangesClick(TObject *Sender)
{
  Memo->Lines->Clear();

  Memo->SelStart = 0;
  Memo->SetFocus();

  Module::GrpCnt = 0;
  Module::StructCnt = 0;

  if(ParaList){
    delete ParaList;
    ParaList = NULL;
  }

  if(AKAList){
    delete AKAList;
    AKAList = NULL;
  }
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::ClearClick(TObject *Sender)
{
  Memo->Lines->Clear();

  Module::GrpCnt = 0;
  Module::StructCnt = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::CreateGroup1Click(TObject *Sender){

  String Txt, S, MacroName, GrpName;
  int Indx;

  OpenDialogMcr->Filter = "Project Files (*.prj)|*.prj";
  OpenDialogMcr->DefaultExt = "prj";
  OpenDialogMcr->Title = "Create Group from project file";
  if(OpenDialogMcr->Execute()) {

    OpenDialogMcr->InitialDir = ExtractFilePath(OpenDialogMcr->FileName);
    if(OpenDialogMcr->InitialDir.IsEmpty())
      OpenDialogMcr->InitialDir = GetCurrentDir();

    SaveDialogMcr->InitialDir = OpenDialogMcr->InitialDir;

    MacroName = OpenDialogMcr->FileName;
    if(Indx = MacroName.LastDelimiter("\\"), Indx != 0) // handle directories
      MacroName = MacroName.SubString(Indx+1, MacroName.Length() - Indx);

    if(Indx = MacroName.LastDelimiter("."), Indx != 0){ // handle extensions
      String AA;
      GroupEnding(AA, ++Module::GrpCnt);
      MacroName = MacroName.SubString(1, Indx-1) + "_Grp" + AA.SubString(1, 3);
    }

    if(!isalpha(MacroName[1])){ // must be a proper variable name
      Application->MessageBox("Alpha characters are upper-/lowercase characters from A through Z.", "Project file name must begin with an alpha character.", MB_OK);
      return;
    }
    GrpName = MacroName;
    if(Module::GrpCnt > 1)
      Module::GrpCnt = 1;

    ProjectFile = new TStringList; // hold project file
    ModuleList = new TStringList;  // list of modules in group
    MacroList = new TStringList;   // macros in project file
    DefinedList = new TStringList; // macros already defined
    if(!ParaList){
      ParaList = new TStringList; // macros already defined
      ParaList->Add("Parameters for created Group Macro");
      ParaList->Add("#####");
    }

    if(!AKAList){
      AKAList = new TStringList; // macros already defined
    }

    ProjectFile->LoadFromFile(OpenDialogMcr->FileName); // load project

    int ThisEnd = 0;
    Module *ThisModule;

    while (ThisEnd < Memo->Lines->Count) { // current Macros
      if(Memo->Lines->Strings[ThisEnd].Length() == 0) // handle null lines
        continue;

      while(ThisEnd < Memo->Lines->Count && (Txt = Memo->Lines->Strings[ThisEnd].TrimLeft(),
            Txt[1] == '/'))
        ++ThisEnd;

      if(Indx = Txt.Pos(" "))
        Txt = Txt.SubString(1, Indx-1);

      ThisModule = new Module;

      ThisModule->head = ThisEnd;

      do
        S = Memo->Lines->Strings[++ThisEnd].Trim();
      while(S[1] == '/');

      if(S.Pos("declgroup")){
        ++ThisModule->GrpCnt;
        ThisModule->isGroup = true;
      }

      if(S.Pos("declstruct")){
        ++ThisModule->StructCnt;
        ThisModule->isStruct = true;
      }

      while(ThisEnd < Memo->Lines->Count && !(S = Memo->Lines->Strings[ThisEnd].Trim(),
             S.SubString(1,3) == "end" && (S.Length() == 3 || S.IsDelimiter(" /", 4))))

        ++ThisEnd;

      ThisModule->tail = ThisEnd++;
      DefinedList->AddObject(Txt, (TObject*) ThisModule);

    } // while

    for (int ii = 0; ii < ProjectFile->Count; ++ii){ // generate list of project macros
      Txt = ProjectFile->Strings[ii];
      if(Txt == "Dimensions:"){
        Global::nhru = (ProjectFile->Strings[ii+2].SubString(5,10)).ToInt(); // assumes file format
        Global::nlay = (ProjectFile->Strings[ii+3].SubString(5,10)).ToInt(); // assumes file format
      }

      if(Txt == "Parameters:"){
        ++ii; ++ii; // skip #'s

        while(ProjectFile->Strings[ii][1] != '#'){ // end of macro definitions
          if(ProjectFile->Strings[ii][1] == '\'' || ProjectFile->Strings[ii][1] == '-' || isdigit(ProjectFile->Strings[ii][1]))
            ParaList->Add(ProjectFile->Strings[ii]);
          else{
            Indx = ProjectFile->Strings[ii].Pos(" ");
            S = ProjectFile->Strings[ii].SubString(Indx+1, ProjectFile->Strings[ii].Length() - Indx);

            ParaList->Add(GrpName + " " + S);
          }
          ++ii;
        } // while
        continue;
      } // if

      if(Txt == "Macros:"){
        ++ii; ++ii; // skip #'s

        ThisModule = NULL;

        while(ProjectFile->Strings[ii][1] != '#'){ // end of macro definitions

          while(ii < ProjectFile->Count && (S = ProjectFile->Strings[ii].TrimLeft(),
                S[2] == '/')) // first character is single quote
            ++ii;

          S = S.SubString(2, S.Length() - 2); // remove leading and trailing '

          if(!ThisModule){
              if(Indx = S.Pos(" "))
                S = S.SubString(1, Indx-1);

            ThisModule = new Module;

            ThisModule->head = MacroList->Count;

            MacroList->Add(S);
          }
          else{
            if(S.Pos("declgroup")){
              ++ThisModule->GrpCnt;
              ThisModule->isGroup = true;
            }
            if(S.Pos("declstruct")){
              ++ThisModule->StructCnt;
              ThisModule->isStruct = true;
            }
            
            MacroList->Add(S);

            if(S.SubString(1,3) == "end" && (S.Length() == 3 || S.IsDelimiter(" /", 4))){
              ThisModule->tail = MacroList->Count;
              MacroList->Objects[ThisModule->head] = (TObject*) (ThisModule);
              ThisModule = NULL;
            }
          }
          ++ii;
        } // while
        continue;
      } // if
    } // for

    for (int ii = 0; ii < ProjectFile->Count; ++ii){ // make list of modules in project
      Txt = ProjectFile->Strings[ii];
      
      if(Txt == "AKAs:"){
        ++ii; ++ii; // skip #'s
        while(ProjectFile->Strings[ii][1] != '#'){ // end of macro definitions
          String S = ProjectFile->Strings[ii].Trim();
          int Indx = S.Pos(" ");
          String type = S.SubString(1, Indx-1);
          S = S.SubString(Indx+1, S.Length() - Indx);

          Indx = S.Pos(" ");
          String module = S.SubString(1, Indx-1);
          S = S.SubString(Indx+1, S.Length() - Indx);

          Indx = S.Pos(" ");
          String name = S.SubString(1, Indx-1);
          S = S.SubString(Indx+1, S.Length() - Indx);

          String alias;
          Indx = S.Pos(" ");
          if(Indx == 0){
            alias = S;
            ParaList->Add(type + " " + GrpName + " " + name + " " + alias);
          }
          else{
            alias = S.SubString(1, Indx-1);
            String source = S.SubString(Indx+1, S.Length() - Indx);
            if(MacroList->IndexOf(source) > -1)
              AKAList->Add(type + " " + GrpName + " " + name + " " + alias + " " + source);
            else
              AKAList->Add(type + " " + GrpName + " " + name + " " + alias + " " + GrpName);
          }
          ++ii;
        } // while
      } // if

      if(Txt == "Modules:"){
        ++ii; ++ii; // skip #'s

        while(DefinedList->IndexOf(S) > -1){ // already defined
          ++S[S.Length()];
        }

        ModuleList->Add(GrpName);
        ModuleList->Add("declgroup " + String(Global::nhru));

        while(ProjectFile->Strings[ii][1] != '#'){
          S = ProjectFile->Strings[ii].Trim();
          if(S.Pos("+")){ // skip!
            ++ii;
            continue;
          }
          if(S.Pos(" "))
            S = S.SubString(1, S.Pos(" ")-1);
          ModuleList->Add(S);
          ++ii;
        }
        ModuleList->Add("command");
        ModuleList->Add("end");
        break;
      } // if
    } // for

    ProjectFile->Clear();
    int EndList = ModuleList->Count-2; // ignore 'command' and 'end' lines

    for(int ii = 2; ii < EndList; ++ii){ // add modules and required macros
      AddGroup(ii);
    }

    Memo->Lines->AddStrings(ModuleList);

    delete ProjectFile;
    delete ModuleList;
    for(int ii = 0; ii < MacroList->Count; ++ii)
      delete (Module*) MacroList->Objects[ii];
    delete MacroList;
    for(int ii = 0; ii < DefinedList->Count; ++ii)
      delete (Module*) DefinedList->Objects[ii];
    delete DefinedList;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::AddGroup(int ii){ // adds group to TMemo
  int Indx;
  if(DefinedList->IndexOf(ModuleList->Strings[ii]) == -1){ // not defined already
    if(Indx = MacroList->IndexOf(ModuleList->Strings[ii]), Indx > -1){
      Module* ThisModule = (Module*) MacroList->Objects[Indx];
//      int End = ThisModule->tail;

      AddSupport(ThisModule); // check if support required

      for(int jj = ThisModule->head; jj < ThisModule->tail; ++jj) // Add module
        Memo->Lines->Add(MacroList->Strings[jj]);
        
      ThisModule->avail = true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::AddSupport(Module* ThisModule){ // adds modules within groups

  int Indx;
  for(int ii = ThisModule->head + 2; ii < ThisModule->tail-2; ++ii){ // process modules
    if(DefinedList->IndexOf(MacroList->Strings[ii]) > -1) // defined already
      return;

    if(Indx = MacroList->IndexOf(MacroList->Strings[ii]), Indx > -1 && MacroList->Objects[Indx]){
      Module* ThisModule = (Module*) MacroList->Objects[Indx];
      if(ThisModule->avail) // already been added
        continue;
        
      if(ThisModule->isGroup || ThisModule->isStruct){ // if group or struct require further support modules
        AddSupport(ThisModule);
        ThisModule->avail = true;
      }

      for(int jj = Indx; jj < ThisModule->tail; ++jj) // add support module
        Memo->Lines->Add(MacroList->Strings[jj]);

      ThisModule->avail = true;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormEntry::FormDeactivate(TObject *Sender)
{
  if(ParaList){
    delete ParaList;
    ParaList = NULL;
  }

  if(AKAList){
    delete AKAList;
    AKAList = NULL;
  }
}
//---------------------------------------------------------------------------

