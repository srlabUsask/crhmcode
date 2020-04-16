#include "stdafx.h"
#include "utils.h"
#include "TStringList.h"
#include "GlobalCommon.h"
#include "Common.h"
#include "GlobalDll.h"
#include <string.h>
#include <list>
#include <ctime>
#include <atltime.h>

utils::utils()
{
	SaveProject();
}

utils::~utils()
{

}

TStringList utils::SaveProject() {

bool SaveStateFlag;
bool ProjectOpen;
bool ShiftDown; // Linked to ListBox1 and ListBox2

Global::nhru = Global::maxhru;
Global::nobs = Global::maxobs;
Global::nlay = Global::maxlay;

MapPar::iterator itPar;
MapDim::iterator itDim;
ClassPar *thisPar;
ClassVar *lastVar = NULL;
string Output;

string DescripPrj = "Describe";

int x = 5;
int *y = &x;

TStringList Fred;

ProjectList = new TStringList();

ProjectList->Add(DescripPrj.c_str());

/*ProjectList->Add((t1.Format(" hh:mm")));*/

//DateTime Dt = DateTime::CurrentDateTime();

//String("  Creation: " + Dt.DateString() + FormatDateTime(" hh:mm", Dt));
//String("Hello" + "Test");

ProjectList->Add("###### " + string("Test aboutbox caption"));



//bool Prj = (SaveDialogPrj->FileName.LowerCase()).Pos(".prj");
bool Prj = TRUE;
if (Prj) {

	ProjectList->Add("Dimensions:");
	ProjectList->Add("######");
	ProjectList->Add(string("nhru " + Global::maxhru));
	ProjectList->Add(string("nlay " + Global::nlay));
	ProjectList->Add(string("nobs " + Global::nobs));
	ProjectList->Add("######");

	ProjectList->Add("Macros:");
	ProjectList->Add("######");

	for (int ii = 0; ii < Global::MacroModulesList->Count; ++ii)
		ProjectList->Add(string("'" + (Global::MacroModulesList->Strings[ii]) ));

	//ProjectList->Add("######");

	//if (!Global::MapAKA.empty()) {
	//	Mapstr2::iterator it;

	//	ProjectList->Add("AKAs:");
	//	ProjectList->Add("######");

	//	for (it = Global::MapAKA.begin(); it != Global::MapAKA.end(); ++it) {
	//	 string Var = (*it).first + ' ' + (*it).second;
	//		ProjectList->Add(Var.c_str());
	//	}
	//	ProjectList->Add("######");
	//}
}

ProjectList->Add("Observations:");
ProjectList->Add("######");
//		/*for (int ii = 0; ii < ObsFilesList->Count; ii++) {
//		 string S = ObsFilesList->Strings[ii];
//			ProjectList->Add(S);
//		}*/
ProjectList->Add("######");

ProjectList->Add("Dates:");
ProjectList->Add("######");

CTime t1 = CTime::GetCurrentTime();
CTime t2 = t1 + CTimeSpan(0, 1, 0, 0);
CString cs = t1.Format(_T("%A, %B %d, %Y"));

string s2((CStringA)cs);

CT2A ct(cs);
string strr(ct);

string S;

/*if (ObsFilesList->Count == 0)
ProjectList->Add(strr);*/
S = strr;
ProjectList->Add(S);
ProjectList->Add("######");



ProjectList->Add("Modules:");
ProjectList->Add("######");

/*for (int ii = 0; ii < Global::OurModulesList->Count; ii++) {
ClassModule* thisModule = (ClassModule*)Global::OurModulesList->Objects[ii];
String S = Global::OurModulesList->Strings[ii];
if (thisModule->variation > 0) {
string AA("#0 ");
AA[1] += log(thisModule->variation) / log(2) + 1;
S = S + AA.c_str();
}
else
S = S + " ";

S = S + thisModule->DLLName + " ";
S = S + thisModule->Version;
ProjectList->Add(S);*/

//
//	//This is boost library !! Check it out at the end of slides
//
//
//	/*	if (thismodule->isgroup || thismodule->isstruct) {
//	list<moduleptr> ::iterator iterm;
//	iterm = ((classmacro *)thismodule)->modules.begin();
//	while (iterm != ((classmacro *)thismodule)->modules.end()) {
//	boost::weak_ptr<classmodule> mp((*iterm));
// string s = string(" +") + (*iterm)->nameroot.c_str();
//	if ((*iterm)->variation > 0) {
// string aa("#0 ");
//	aa[1] += log((*iterm)->variation) / log(2) + 1;
//	s = s + aa.c_str();
//	}
//	else
//	s = s + " ";
//
//	s = s + (*iterm)->dllname + " ";
//	s = s + (*iterm)->version;
//	projectlist->add(s);
//	++iterm;
//	}
//	}
//
//	}*/
//
//			ProjectList->Add("Parameters:");
//			ProjectList->Add("###### 'basin' parameters always first");
//
//			//for (int bb = 0; bb < 2; ++bb) { // shared parameters first - initially over-write all others
//			//	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
//			//		thisPar = (*itPar).second;
//
//			//		if (thisPar->param == "HRU_group")
//			//			continue;
//			//		if (bb == 0 && thisPar->module != "shared")
//			//			continue;
//			//		if (bb == 1 && thisPar->module == "shared")
//			//			continue;
//
//			//	 string S = string(thisPar->module.c_str()) + " " + string(thisPar->param.c_str());
//
//			//		if (thisPar->varType != CRHM::Txt)
//			//			S += " <" + FloatToStrF(thisPar->minVal, 4) + " to " + FloatToStrF(thisPar->maxVal, 4) + ">";
//			//		ProjectList->Add(S);
//
//			//		for (int jj = 0; jj<thisPar->lay; jj++) {
//			//			S = "";
//			//			for (int ii = 0; ii < thisPar->dim; ii++) {
//			//				if (thisPar->varType == CRHM::Float)
//			//					S = S + FloatToStrF(thisPar->layvalues[jj][ii], 4) + " ";
//			//				else if (thisPar->varType == CRHM::Int)
//			//					S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], 8) + " ";
//			//				else if (thisPar->varType == CRHM::Txt)
//			//					if (thisPar->Strings->Count > ii)
//			//						S = S + "'" + thisPar->Strings->Strings[ii] + "' ";
//			//					else
//			//						S = "''"; // handle null string
//
//			//				if (ii % 16 == 15) {
//			//					ProjectList->Add(S);
//			//					S = "";
//			//				}
//			//			}
//			//			if (!S.empty()) { ProjectList->Add(S); S = ""; }
//			//		}
//			//		if (!S.empty()) ProjectList->Add(S);
//			//	} // output loop
//			//}  // basin module/other loop
//
//			ProjectList->Add("######");
//
//			ProjectList->Add("Initial_State");
//			ProjectList->Add("######");
//
//			//TMenuItem *StateItem;
//			//StateItem = MainMenu1->Items->Items[5];
//
//			//if (StateItem->Count > 5) { // State files open
//			//	for (int ii = 5; ii < StateItem->Count; ++ii)
//			//		ProjectList->Add(StateItem->Items[ii]->Caption);
//			//}
//
//			ProjectList->Add("######");
//
//			ProjectList->Add("Final_State");
//			ProjectList->Add("######");
//			//This is the SaveDiaglogbox from CHRMMain.h more GUI stuff
//			/*if (SaveStateFlag) {
//			ProjectList->Add(SaveDialogState->FileName);
//			}*/
//			ProjectList->Add("######");
//		}
//
//
//		//Taken from CHRMMain.h
//	 string TBases[] = { "Daily", "Water_year", "Calendar_year", "Monthly_summary", "Summarize_all" };
//		long TBase;
//		TBase = 0;
//		long water_year_month = 10;
//	 string TLogFormats[] = { "MS_time", "MM/DD/YYYY", "YYYY-MM-DD" };
//
//
//
//
//
//
//
//		ProjectList->Add("Summary_period");
//		ProjectList->Add("######");
//	 string T = TBases[TBase];
//		/*if (TBase == 1)
//			T = T + " " + LongToStrF(TBase);
//		ProjectList->Add(T);*/
//		ProjectList->Add("######");
//
//
//		ProjectList->Add("Log_Time_Format");
//		ProjectList->Add("######");
//		/*T = TLogFormats[Global::TimeFormat];
//		ProjectList->Add(T);*/
//		ProjectList->Add("######");
//
//		/*if (Global::LOGVARLOAD) {
//			ProjectList->Add("LOGVARLOAD");
//			ProjectList->Add("######");
//		}*/
//
//		ProjectList->Add("Display_Variable:");
//		ProjectList->Add("######");
//
//		//More GUI stuff
//
//		//for (int ii = 0; ii < SeriesCnt; ii++) { // transfer TeeChart data
//
//		//	ClassVar *thisVar = (ClassVar *)cdSeries[ii]->Tag;
//		//	thisVar->TchrtOpt = cdSeries[ii]->VertAxis == aRightAxis;
//		//}
//
//		lastVar = NULL;
//		Output = "";
//
//		//More GUI
//		/*	if (HruNames)
//		HruNameClick(Sender);*/
//
//
//		//for (int ii = 0; ii < 25; ++ii) {
//
//		//	long lay, dim;
//
//		//	//ExtractHruLay(ListBox3->Items->Strings[ii], dim, lay);
//
//		//	ClassVar *thisVar;// = (ClassVar *)(ListBox3->Items->Objects[ii]);
//
//		//	if (thisVar->TchrtOpt)
//		//		dim = -dim;
//		// string SS = LongToStrF(dim);
//		//	if (thisVar->lay > 0) SS += "," + LongToStrF(lay);
//
//		// string Mod = thisVar->module;
//
//		//	if (lastVar == NULL)
//		//		Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
//		//	else if (lastVar != thisVar) {
//		//		ProjectList->Add(Output);
//		//		Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
//		//	}
//		//	else
//		//		Output += " " + SS;
//
//		//	lastVar = thisVar;
//		//}
//
//		//if (!Output.empty()) ProjectList->Add(Output);
//
//		ProjectList->Add("######");
//
//		ProjectList->Add("Display_Observation:");
//		ProjectList->Add("######");
//
//		lastVar = NULL;
//	 string kind, lastkind;
//		Output = "";
//
//		for (int ii = 0; ii < 256; ii++) {
//
//		 string S;// = ListBox4->Items->Strings[ii];
//		 string FullName;
//			long dim, lay;
//			kind = "_obs";
//
//		 string Name;// = ExtractHruLayFunct(ListBox4->Items->Strings[ii], dim, lay, kind, FullName);
//
//						//TLineSeries *cdSeries = (TLineSeries *)ListBox4->Items->Objects[ii];
//
//			ClassVar *thisVar;
//			//thisVar = (ClassVar *)cdSeries->Tag; // always OK for observation
//
//			//if (!thisVar || !thisVar->FileData) {  // VarObsFunct
//			//	if (!thisVar) {
//			//		long Indx;// = ListBox3->Items->IndexOf(FullName);
//			//				  /*if (Indx > -1)
//			//				  thisVar = (ClassVar *)ListBox3->Items->Objects[Indx];
//			//				  else
//			//				  thisVar = VarFind(string(string("obs ") + Name.c_str()));*/
//			//	}
//			//}
//
//			/*if (cdSeries->VertAxis == aRightAxis)
//			dim = -dim;*/
//
//			// string SS = LongToStrF(dim);
//
//			//	if (lay > 0)
//			//		SS += "," + LongToStrF(lay);
//
//			//	if (Output != "" && (thisVar != lastVar || kind != lastkind)) {
//			//		ProjectList->Add(Output + " " + lastkind);
//			//		if (thisVar)
//			//			Output = (thisVar->module + " " + Name.c_str() + " " + SS.c_str()).c_str();
//			//		else // fudge for obs _Avg thru _Tot being null for observations
//			//			Output = (string("obs ") + Name.c_str() + " " + SS.c_str()).c_str();
//			//	}
//			//	else if (lastVar) // add to earlier output
//			//		Output += " " + SS;
//			//	else // first output
//			//		Output = (thisVar->module + " " + Name.c_str() + " " + SS.c_str()).c_str();
//
//			//	lastVar = thisVar;
//			//	lastkind = kind;
//			//}
//
//
//
//			if (!Output.empty()) ProjectList->Add(Output + " " + kind); // handle last output
//
//			ProjectList->Add("######");
//
//
//			// all these are the GUI part. 
//
//			/*if (PrjAutoRun->Checked) {
//			ProjectList->Add("Auto_Run");
//			ProjectList->Add("######");
//			}
//
//			if (SaveChartTemplate->Checked) {
//			ProjectList->Add("SaveChartTemplate");
//			ProjectList->Add("######");
//		 string FileName = ChangeFileExt(SaveDialogPrj->FileName, ".Tee");
//			Chart->RemoveAllSeries();
//			SaveChartToFile(Chart, FileName, false, true);
//			}
//
//			if (PrjAutoExit->Checked) {
//			ProjectList->Add("Auto_Exit");
//			ProjectList->Add("######");
//			}
//
//			if (Last1->Checked) {
//			ProjectList->Add("Log_Last");
//			ProjectList->Add("######");
//			}
//
//			if (All1->Checked) {
//			ProjectList->Add("Log_All");
//			ProjectList->Add("######");
//			}
//
//			if (DebugScreen1->Checked) {
//			ProjectList->Add("Log_Screen");
//			ProjectList->Add("######");
//			}
//
//			if (SummaryScreen1->Checked) {
//			ProjectList->Add("Summary_Screen");
//			ProjectList->Add("######");
//			}*/
//
//			ProjectList->Add("TChart:");
//			ProjectList->Add("######");
//
//			/*for (int ii = 0; ii < Chart->Title->Text->Count; ++ii)
//			ProjectList->Add(Chart->Title->Text->Strings[ii]);
//			ProjectList->Add(" ");
//
//			for (int ii = 0; ii < Chart->SubTitle->Text->Count; ++ii)
//			ProjectList->Add(Chart->SubTitle->Text->Strings[ii]);
//			ProjectList->Add(" ");
//
//			ProjectList->Add(Chart->Axes->Items[2]->Title->Caption);
//			ProjectList->Add(" ");
//			*/
//			//for (int ii = 0; ii < Chart->Foot->Text->Count; ++ii)
//			//	ProjectList->Add(Chart->Foot->Text->Strings[ii]);
//			//ProjectList->Add(" ");
//
//			//for (int ii = 0; ii < Chart->SubFoot->Text->Count; ++ii)
//			//	ProjectList->Add(Chart->SubFoot->Text->Strings[ii]);
//			//ProjectList->Add(" ");
//
//			//if (Chart->MaxPointsPerPage != 0) {
//			// string S = string(Chart->MaxPointsPerPage) + " " + string(Chart->Page);
//			//	ProjectList->Add(S);
//			//}
//			ProjectList->Add("######");
//
//			//ProjectList->SaveToFile(SaveDialogPrj->FileName);
//
//			//ProjectList->Clear();
//
//			dirty = false;
//
//
return *ProjectList;
//
//
//
//		}
}


			 void saveFile(TStringList H)
			 {
				 ofstream myfile;
				 myfile.open("example.txt");

				 for (unsigned int a = 0; a < sizeof(H.Count); a = a + 1)
				 {
					 myfile << "value of a: " << H.Sorted << endl;
				 }

				 myfile.close();

			 }