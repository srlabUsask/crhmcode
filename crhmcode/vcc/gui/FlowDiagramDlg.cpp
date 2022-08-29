/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
// FlowDiagramDlg.cpp : implementation file
//

#include "../stdafx.h"
#include "FlowDiagramDlg.h"
#include "CWebBrowser.h"
//#include "CWebBrowser2.h"
#include "MacroEntryDlg.h"
#include <fstream>
#include <time.h>
#include <filesystem>



// FlowDiagramDlg dialog

IMPLEMENT_DYNAMIC(FlowDiagramDlg, CDialogEx)

FlowDiagramDlg::FlowDiagramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(FlowDiagram_DLG, pParent)
{

}

FlowDiagramDlg::~FlowDiagramDlg()
{
}

void FlowDiagramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, listcontrol);
}


BEGIN_MESSAGE_MAP(FlowDiagramDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &FlowDiagramDlg::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// FlowDiagramDlg message handlers


string FlowDiagramDlg::GetLineString(int x1, int y1, int x2, int y2)
{
	string line = "\nline ("+to_string(x1)+", " + to_string(y1) + "," + to_string(x2) + "," + to_string(y2) + ");";
	return line;
}

string FlowDiagramDlg::GetRectangleString(int x1, int y1, int x2, int y2)
{
	string rectangle = "\nrectangle (" + to_string(x1) + "," + to_string(y1) + "," + to_string(x2) + "," + to_string(y2) + ");";
	return rectangle;
}

string FlowDiagramDlg::GetDrawString(string str, int x1, int y1)
{
	string drawstring = "\ndrawString ('"+str+"',"+to_string(x1)+","+to_string(y1)+");";
	return drawstring;
}


void FlowDiagramDlg::LoadAllModules()
{
	TBuild TempB = Global::BuildFlag;
	Global::BuildFlag = TBuild::BUILD; // default value

	for (
		std::map<std::string, ClassModule*>::iterator modIt = Global::AllModulesList->begin(); 
		modIt != Global::AllModulesList->end(); 
		modIt++
		) 
	{

		ClassModule * thisModule = modIt->second;
		thisModule->variation_max = 0;

		unsigned short Temp = thisModule->variation;
		unsigned short Temp2 = thisModule->variation_set;
		thisModule->variation_set = 0;
		thisModule->variation = 0;
		thisModule->decl();
		thisModule->variation = Temp;
		thisModule->variation_set = Temp2;

		if (thisModule->variation > 0)
			thisModule->hh = (long) (log(thisModule->variation) / log(2) + 1); // set to current variation
		else
			thisModule->hh = 0;
	}

}


void FlowDiagramDlg::DrawDiagram()
{

	/*
	Global::Mapgetvar.clear();
	Global::Mapputvar.clear();
	Global::Mapreadvar.clear();
	Global::Mapdeclvar.clear();
	Global::Mapdeclpar.clear();
	Global::Mapdeclobs.clear();

	Global::BuildFlag = CRHM::BUILD; // default value
	*/

	LoadAllModules();



	FDModule mods[20];
	int mcount = Global::OurModulesList->size();

	GetModulesInputsAndOutputs(mods);
	int ii = 0;
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end(); 
		modIt++
		) 
	{
		ClassModule* thisModule = modIt->second;
		thisModule->variation_max = 0;
		thisModule->decl();

		mods[ii].count = 0;
		//mods[ii].ilength = 0;
		mods[ii].olength = 0;
		GetModuleDetails(thisModule->Name, thisModule, & mods[ii]);
		mods[ii].modulename = thisModule->Name;
		mods[ii].FindInputList();
		mods[ii].FindOutputList();

		ii++;
		//mcount++;
	}
	
	Global::BuildFlag = TBuild::DECL; // model loaded
	


	int rectHeight = 0;
	int x = 400;
	int y = 50;
	int xwidth = 50;
	int minheight = 15;
	int textoffset = 12;
	int lastxleft = 0;
	int lastxright = 0;
	int cordx, cordy;

	//assigning co-ordinates to the module rectangles.
	for (int i = 0; i < mcount; i++)
	{
		//determining the rect height.
		int ilength = mods[i].ilength;
		int olength = mods[i].olength;

		if (ilength > olength) { rectHeight = ilength * minheight + minheight; }
		else { rectHeight = olength * minheight + minheight; }

		mods[i].x1 = x;
		mods[i].y1 = y;
		mods[i].x2 = x + xwidth;
		mods[i].y2 = mods[i].y1 + rectHeight;

		x = mods[i].x2 + (mods[i].olength + 1)*minheight + minheight+150;
		y = mods[i].y2 + 50;
	}

	//reading the header file of the graph.
	string header = "", line="";
	ifstream infile("graphheader.txt");
	while (std::getline(infile, line))
	{
		header += "\n" + line;
	}



	string footer = "";

	//drawing the rectangles.
	for (int i = 0; i < mcount; i++)
	{
		footer += GetRectangleString(mods[i].x1, mods[i].y1, mods[i].x2, mods[i].y2);
		footer += GetDrawString(mods[i].modulename, mods[i].x1, mods[i].y2+5);
	}

	for (int i = 0; i < mcount; i++)
	{
		//setting the inputs.
		for (int j = 0; j < mods[i].ilength; j++)
		{
			//find previous module and input
			string input = mods[i].inputlist[j];
			int mi = FindPreviousModule(input, i, mods);
			if (mi == -1)
			{
				cordx = mods[i].x1; cordy = mods[i].y1 + (j + 1) * minheight;
				footer += GetLineString (50, cordy, cordx, cordy);
				footer += GetDrawString(input, 50, cordy - textoffset);
			}
			else
			{
				int iserial = mods[mi].GetInputSerial(input);
				int oserial = mods[mi].GetOutputSerial(input);
				if (iserial >= 0)
				{
					int yy = mods[mi].y1 + (iserial + 1) * minheight;
					int xx = mods[mi].x1 - (iserial + 1) * minheight;
					int yy2 = mods[i].y1 + (j + 1)*minheight;

					footer += GetLineString(xx, yy, xx, yy2);
					footer += GetLineString(xx, yy2, mods[i].x1, yy2);
					footer += GetDrawString(input, mods[i].x1-50, yy2-textoffset);
				}
				if (oserial >= 0)
				{
					int yy = mods[mi].y1 + (oserial + 1) * minheight;
					int xx = mods[mi].x2 + (oserial + 1) * minheight + 100;
					int yy2 = mods[i].y1 + (j + 1)*minheight;

					footer += GetLineString(xx, yy, xx, yy2);
					footer += GetLineString(xx, yy2, mods[i].x1, yy2);
					footer += GetDrawString(input, mods[i].x1 - 50, yy2 - textoffset);
				}
			}
		}

		//setting the outputs
		for (int j = 0; j < mods[i].olength; j++)
		{
			cordx = mods[i].x2; cordy = mods[i].y1 + (j + 1)*minheight;

			footer += GetLineString(cordx, cordy, cordx+400, cordy);
			footer += GetDrawString(mods[i].outputlist[j], cordx+20, cordy-textoffset);
		}
	}


	footer += "</script></html>";
	string filecontent;
	filecontent = header + footer;


	//writing the context into the file.
	std::ofstream outfile;
	outfile.open("graph.html", std::ios_base::out); // append instead of overwrite
	outfile << filecontent;
	outfile.close();
}


void FlowDiagramDlg::FormActivate() 
{

	time_t start, end1, end2;
	time(&start);

	DrawModules();
	DrawDiagram();

	time(&end1);

	//Manishankar added this portion to get the graph from the current directory.
	string filepath = GetCurrentDir()+"/graph.html";
	BSTR b = _com_util::ConvertStringToBSTR(filepath.c_str());
	LPWSTR lp = b;

	CWebBrowser * browser;
	browser = (CWebBrowser*)GetDlgItem(IDC_EXPLORER1);
	browser->Navigate(lp, NULL, NULL, NULL, NULL);

	time(&end2);

	double seconds1 = difftime(end1, start);
	double seconds2 = difftime(end2, start);

	string s1 = to_string(seconds1);
	string s2 = to_string(seconds2);
	CString cs1(s1.c_str());
	CString cs2(s2.c_str());

	listcontrol.InsertColumn(0, L"Name", LVCFMT_CENTER, 80);
	listcontrol.InsertColumn(1, L"Age", LVCFMT_CENTER, 80);
	listcontrol.InsertColumn(2, L"Address", LVCFMT_CENTER, 80);

	int item = listcontrol.InsertItem(0, L"testname");
	listcontrol.SetItemText(item, 2, L"Mark");

}


void FlowDiagramDlg::DrawGrid() {

	
	Mapstr::iterator itMap, pos, itMap2;

	pair<Mapstr::iterator, Mapstr::iterator> rangeO;
	pair<Mapstr::iterator, Mapstr::iterator> rangeOobs;
	pair<Mapstr::iterator, Mapstr::iterator> rangeI;
	pair<Mapstr::iterator, Mapstr::iterator> rangeIobs;

	string S, S1, S2, SS;
	//TGridOptions OurOptions; varible is unreferenced commenting out for now - jhs507

	//OurOptions << goFixedVertLine << goFixedHorzLine << goVertLine << goHorzLine << goTabs << goColSizing;
	//StringGrid1->Options = OurOptions;


	StringGrid1 = new TStringGrid();

	StringGrid1->FixedCols = 0;
	StringGrid1->FixedRows = 0;

	StringGrid1->ColCount = 1; // minimum allowed by FixedCols
	StringGrid1->RowCount = LocalModulesList->size() + 2;

	StringGrid1->Cells[0][0] = "Variable";
	StringGrid1->Cells[0][1] = "Module";

	listcontrol.InsertColumn(0, L"Variable", LVCFMT_CENTER, 80);

	for (size_t ii = 0; ii < LocalModulesList->size(); ++ii)
	{
		StringGrid1->Cells[0][ii + 2] = LocalModulesList->at(ii).first;
		//CString cstr(LocalModulesList->array[ii].Name.c_str());
		//listcontrol.InsertItem(0, cstr);
	}


	
	for (size_t ii = 0; ii < LocalModulesList->size(); ++ii) 
	{

		S = LocalModulesList->at(ii).first;

		rangeO = Global::Mapdeclvar.equal_range(S);
		rangeOobs = Global::Mapdeclobs.equal_range(S);

		
		// add current modules declared variables to list

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++) {
			SS = itMap->second.first;

			//pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
				//value_equals<KeyType2, KeyType2, Pairstr>(SS));

			for (itMap2 = Global::Mapreadvar.begin(); itMap2 != Global::Mapreadvar.end(); ++itMap2)
			{
				if (itMap2->second.first == SS)
				{
					break;
				}
			}
			pos = itMap2;

			//if (pos == Global::Mapreadvar.end() && SS[SS.length()-1] != '#' && StringGrid1->Rows[0]->IndexOf(SS) < 0 && Common::Variation_Decide(ii, itMap->second.second)) { // NO read or declared OBS
			if (pos == Global::Mapreadvar.end() 
				&& SS[SS.length() - 1] != '#' 
				//need to change
				&& StringGrid1->ColPos(0,SS) < 0   //StringGrid1->Rows[0]->IndexOf(SS)
				&& Common::Variation_Decide(ii, itMap->second.second)) { // NO read or declared OBS
				StringGrid1->ColCount = StringGrid1->ColCount + 1;
				//StringGrid1->Cols[StringGrid1->ColCount - 1]->Clear();
				StringGrid1->Cells[StringGrid1->ColCount - 1][0] = SS; // variable
				StringGrid1->Cells[StringGrid1->ColCount - 1][ii + 2] = "D";
				StringGrid1->Cells[StringGrid1->ColCount - 1][1] = S; // module
			}
		}

		// add current modules declared observations to 'list'

		for (itMap = rangeOobs.first; itMap != rangeOobs.second; itMap++) {
			SS = itMap->second.first; // declared observation
			if (Common::Variation_Decide(ii, itMap->second.second)) {
				StringGrid1->ColCount = StringGrid1->ColCount + 1;
				//need to activate
				//StringGrid1->Cols[StringGrid1->ColCount - 1]->Clear();
				StringGrid1->Cells[StringGrid1->ColCount - 1][0] = SS; // declared observation
				StringGrid1->Cells[StringGrid1->ColCount - 1][ii + 2] = "DO";
				StringGrid1->Cells[StringGrid1->ColCount - 1][1] = S; // module
			} // if
		} // for

		
	}

	int a = 10;
	

	
	

	// add current modules get/put variables to list

	for (size_t ii = 0; ii < LocalModulesList->size(); ++ii) {

		S = LocalModulesList->at(ii).first;

		rangeI = Global::Mapgetvar.equal_range(S);
		rangeIobs = Global::Mapreadvar.equal_range(S);

		for (itMap = rangeI.first; itMap != rangeI.second; itMap++) {

			SS = itMap->second.first;
			if (Common::Variation_Decide(ii, itMap->second.second)) {
				int jj = SS.find(" ");
				S1 = SS.substr(0, jj);  // module
				S2 = SS.substr(jj + 1, SS.length()); // variable

				int cc = StringGrid1->ColPos (0,S2); // variable
				int rr = StringGrid1->RowPos (0,S); // module
				if (cc == -1) {
					string V2;
					int indx = S2.find("@");
					if (indx >= 0) {
						V2 = S2.substr(0, indx);
						cc = StringGrid1->ColPos (0,V2); // simple variable
						if (cc == -1) {
							for (int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2) { // group variable
								string V3 = StringGrid1->Cells[cc2][0].substr(0, StringGrid1->Cells[cc2][0].find("@"));
								if (V2 == V3) {
									cc = cc2;
									break;
								}
							}
						}
					}
					else { // simple variable to group/struct
						for (int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2) { // group variable
							string V3 = StringGrid1->Cells[cc2][0].substr(0, StringGrid1->Cells[cc2][0].find("@"));
							if (S2 == V3) {
								cc = cc2;
								break;
							}
						}
					}
				} // if
				if (rr > -1 && cc > -1 && S != StringGrid1->Cells[cc][1]) // Equal implies group
					if (Common::Variation_Decide(ii, itMap->second.second)) {
						if (S1 == "*")
							StringGrid1->Cells[cc][rr] = "*G";
						else
							StringGrid1->Cells[cc][rr] = "G";
					}
			} // if decide
		}
		rangeI = Global::Mapputvar.equal_range(S);

		for (itMap = rangeI.first; itMap != rangeI.second; itMap++) {

			SS = itMap->second.first;
			if (Common::Variation_Decide(ii, itMap->second.second)) {
				int jj = SS.find(" ");
				S1 = SS.substr(0, jj);  // module
				S2 = SS.substr(jj + 1, SS.length()); // variable

				int cc = StringGrid1->ColPos(0,S2); // variable
				int rr = StringGrid1->RowPos(0,S); // module
				if (cc == -1) {
					if (Common::Variation_Decide(ii, itMap->second.second)) {
						string V2;
						int indx = S2.find("@");
						if (indx >= 0) {
							V2 = S2.substr(0, indx);
							cc = StringGrid1->ColPos(0,V2); // variable
							if (cc == -1) {
								for (int cc2 = 1; cc2 < StringGrid1->ColCount; ++cc2) {
									string V3 = StringGrid1->Cells[cc2][0].substr(0, StringGrid1->Cells[cc2][0].find("@"));
									if (V2 == V3) {
										cc = cc2;
										break;
									}
								}
							}
						}
					}
				}

				if (rr > -1 && cc > -1 && S != StringGrid1->Cells[cc][1]) { // Equal implies group
					if (S1 == "*")
						StringGrid1->Cells[cc][rr] = "*P";
					else
						StringGrid1->Cells[cc][rr] = "P";
				}
			} // if decide
		} // for

		  // add needed macro observations to ListUsed

		for (itMap = rangeIobs.first; itMap != rangeIobs.second; itMap++) {
			SS = itMap->second.first; // variable
			//pos = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
				//value_equals<KeyType2, KeyType2, Pairstr>(SS));

			for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
			{
				if (itMap2->second.first == SS)
				{
					break;
				}
			}
			pos = itMap2;

			if (pos == Global::Mapdeclobs.end()) continue; // not available or met observation
			if (Common::Variation_Decide(ii, itMap->second.second)) {
				S1 = pos->first; // module
				S2 = pos->second.first;
				int cc = MatchDecl_Obs(S, S2); // variable - handles multiple groups
				if (cc > -1) continue; // in group
				cc = StringGrid1->ColPos(0,S2); // simple module
				int rr = StringGrid1->RowPos(0,S); // module
				if (rr > -1 && cc > -1) {
					StringGrid1->Cells[cc][rr] = "O";
				}
			}
		} // for rangeIobs
	}  // for rangeI

	int b = 10;

	

	if (StringGrid1->ColCount > 1) StringGrid1->FixedCols = 1;
	if (StringGrid1->RowCount > 2) StringGrid1->FixedRows = 2;

	// Remove any modules not used

	for (size_t ii = 0; ii < LocalModulesList->size(); ++ii) {

		S = LocalModulesList->at(ii).first;

		int mm = StringGrid1->ColPos(1,S);
		if (mm == -1) // if not in row - not used
			if (StringGrid1->ColPos(ii+2,"P") == -1 && StringGrid1->ColPos(ii+2,"P*") == -1 || S == "shared") { // was basin
				int result = IDNO;
				if (result == IDYES || S == "shared") 
				{ // was basin
					StringGrid1->DeleteRow(ii + 2);
					LocalModulesList->erase(LocalModulesList->begin()+ii);
					// Entry deleted ! back-up index!
					ii--;
				}
				else 
				{

					S = LocalModulesList->at(ii).first;
					rangeO = Global::Mapdeclvar.equal_range(S);

					for (itMap = rangeO.first; itMap != rangeO.second; itMap++) {
						SS = itMap->second.first;
						//pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
							//value_equals<KeyType2, KeyType2, Pairstr>(SS));
						for (itMap2 = Global::Mapreadvar.begin(); itMap2 != Global::Mapreadvar.end(); ++itMap2)
						{
							if (itMap2->second.first == SS)
							{
								break;
							}
						}
						pos = itMap2;



						if (pos == Global::Mapreadvar.end()) {
							if (Common::Variation_Decide(ii, itMap->second.second)) {
								StringGrid1->ColCount = StringGrid1->ColCount + 1;
								//StringGrid1->Cols[StringGrid1->ColCount - 1]->Clear();
								StringGrid1->Cells[StringGrid1->ColCount - 1][0] = SS;
								StringGrid1->Cells[StringGrid1->ColCount - 1][ii + 2] = "D";
								StringGrid1->Cells[StringGrid1->ColCount - 1][1] = S;
							}
						}
					}
				}
			} // if
	} // for

	int c = 10;

	/*
	
	// delete unused fields. Leave outputs of unused modules.

	long* UseCount = new long[LocalModulesList->Count]; // find unused modules
	for (int ii = 0; ii < LocalModulesList->Count; ++ii)
		UseCount[ii] = 0;

	for (int cc = StringGrid1->ColCount - 1; cc > 0; --cc) {

		for (int ii = 0; ii < LocalModulesList->Count; ++ii) {
			if (StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "*G" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "*P" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "O") {
				long indx = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
				++UseCount[indx];
			}
		} // for
	}

	
	for (int cc = StringGrid1->ColCount - 1; cc > 0; --cc) {

		bool Used = false;
		for (int ii = LocalModulesList->Count - 1; ii > 0; --ii) { // deleting - reverse order

			if (StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "*G" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "*P" ||
				StringGrid1->Cols[cc]->Strings[ii + 2] == "O") {
				Used = true;
				break;
			}
		}

		long indx = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);
		if (!Used && UseCount[indx] != 0) // remove unused outputs except on unused modules
			DeleteCol(StringGrid1, cc);
	} // for

	delete[] UseCount;

	int CurVarIndx = 0;
	int CurModIndx = -1;
	for (int cc = StringGrid1->ColCount - 1; cc > 0; --cc) {

		int mm = LocalModulesList->IndexOf(StringGrid1->Cols[cc]->Strings[1]);

		if (mm != CurModIndx) { // first module output
			CurModIndx = mm;
			CurVarIndx = 0;
		}
		else
			++CurVarIndx;

		StringGrid1->Cols[cc]->Objects[1] = (TObject*)CurModIndx; // module position in LocalModulesList
		StringGrid1->Cols[cc]->Objects[0] = (TObject*)CurVarIndx; // range (0 -> max) in reverse order

	} // for
	*/
}


int FlowDiagramDlg::MatchDecl_Obs(string module, string Obs) {

	int Col;

	for (Col = 2; Col < StringGrid1->ColCount; ++Col) //
		if (module == StringGrid1->Cells[Col][1] && Obs == StringGrid1->Cells[Col][0])
			return Col;

	return -1;
}





BOOL FlowDiagramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here


	FormActivate();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void FlowDiagramDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here



}


void FlowDiagramDlg::GetModuleDetails(string S, ClassModule* thisModule, FDModule * m)
{
	Mapstr::iterator itMap, pos, pos2, itMap2;

	//int indx; varible is unreferenced commenting out for now - jhs507
	string SS, S1, S2;
	//TGridOptions OurOptions;

	MapVar::iterator itVar;

	long Variation = 0;
	long Vindx = 0;
	int P;

	SS = S;
	if (P = S.find("#"), P > -1) { // remove any suffix
		Vindx = S[P + 1] - char('0');
		Variation = (long) pow(2, S[P + 1] - char('1'));
		S = S.substr(0, S.length() - 2);
	}
	else
		Variation = 0;

	/*
	if (!thisModule->Description.empty()) {
	TStringList* Fred = new TStringList;
	Fred->QuoteChar = '\'';
	Fred->DelimitedText(thisModule->Description);
	if (thisModule->variation_max > 0) // if variation skip overview
	++Vindx;

	if (LBox1) { // write it all out
	for (int ii = 0; ii < Fred->Count; ++ii) {
	S1 = S;
	if (ii == 0)
	S1 += " Function summary";
	else if (ii > 1)
	S1 += "#" + to_string(ii - 1);
	else
	S1 += "  ";

	S1 += " -> " + Fred->Strings[ii];
	//Memo1->Lines->Add(S1);
	AddLinesToMemory(S1);
	}
	}
	else {
	//Memo1->Lines->Add(SS + " -> " + Fred->Strings[Vindx]);
	AddLinesToMemory(SS + " -> " + Fred->Strings[Vindx]);
	if (thisModule->DLLName == "Macro") {
	ClassMacro *thisMacro = dynamic_cast<ClassMacro *> (thisModule);

	if (thisMacro->isGroup) {
	//Memo1->Lines->Add("Group with modules:");
	AddLinesToMemory("Group with modules:");
	string S;
	for (int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
	if (ii == 0)
	S = "  " + thisMacro->GrpStringList->Strings[ii];
	else
	S += ", " + thisMacro->GrpStringList->Strings[ii];
	//Memo1->Lines->Add(S);
	AddLinesToMemory(S);
	}
	else if (thisMacro->isStruct) {
	//Memo1->Lines->Add("Struct with modules:");
	AddLinesToMemory("Struct with modules:");
	string S;
	for (int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
	if (ii == 0)
	S = "  " + thisMacro->GrpStringList->Strings[ii];
	else
	S += ", " + thisMacro->GrpStringList->Strings[ii];
	//Memo1->Lines->Add(S);
	AddLinesToMemory(S);
	}
	else {
	//Memo1->Lines->Add("Macro: ");
	//Memo1->Lines->Add("declarations:");
	AddLinesToMemory("Macro: ");
	AddLinesToMemory("declarations:");
	for (int ii = Global::MacroModulesList->IndexOf(thisMacro->Name.c_str()) + 1; ii < thisMacro->Begin - 1; ++ii)
	{
	//Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
	AddLinesToMemory(" " + Global::MacroModulesList->Strings[ii]);
	}

	//Memo1->Lines->Add("code:");
	AddLinesToMemory("code:");
	for (int ii = thisMacro->Begin; ii < thisMacro->End; ++ii)
	{
	//Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
	AddLinesToMemory(" " + Global::MacroModulesList->Strings[ii]);
	}
	}
	}
	}
	//Memo1->Lines->Add(" ");
	AddLinesToMemory(" ");
	delete Fred;
	}
	*/

	//stringgrid.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_GRIDLINES);

	//stringgrid.insert


	//OurOptions << goHorzLine << goVertLine << goFixedVertLine << goColSizing;
	//StringGrid1->Options = OurOptions;


	StringGrid2 * StringGrid1;

	StringGrid1 = new StringGrid2();

	for (int I = 0; I < StringGrid1->ColCount; ++I)
		for (int J = 0; J < StringGrid1->RowCount; ++J)
			StringGrid1->Cells[I][J] = "";


	StringGrid1->ColCount = 6;
	StringGrid1->FixedRows = 0;
	StringGrid1->RowCount = 1;

	StringGrid1->Cells[0][0] = "Observations";
	StringGrid1->Cells[1][0] = "Modules";
	StringGrid1->Cells[2][0] = "Inputs";
	StringGrid1->Cells[3][0] = "Outputs";
	StringGrid1->Cells[4][0] = "Parameters";
	StringGrid1->Cells[5][0] = "New Observations";


	// insert observations
	pair<Mapstr::iterator, Mapstr::iterator> range = Global::Mapreadvar.equal_range(S);
	int ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = (itMap->second).first;
		if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
		int Indx = StringGrid1->Cols[0].find(SS);
		if (Indx == -1 && Variation_Decide(Variation, (itMap->second).second)) {
			StringGrid1->Cells[0][ii + 2] = SS;
			++ii;
		}
	} // for

	  // insert put variables used
	range = Global::Mapputvar.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = itMap->second.first;
		int jj = SS.find(" ");
		S1 = SS.substr(0, jj); // module
		S2 = SS.substr(jj + 1, SS.length() - jj - 1); // variable
		if (S1 != S && Variation_Decide(Variation, (itMap->second).second)) {
			if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[1][ii + 2] = S1;
			StringGrid1->Cells[2][ii + 2] = S2;
			++ii;
		}
	} // for

	  // insert get variables used
	range = Global::Mapgetvar.equal_range(S);
	//  ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = itMap->second.first;
		int jj = SS.find(" ");
		S1 = SS.substr(0, jj); // module
		S2 = SS.substr(jj + 1, SS.length() - jj - 1); // variable
		if (S1 != S && Variation_Decide(Variation, (itMap->second).second)) {
			int Indx = StringGrid1->Cols[2].find(S2);
			if (Indx == -1) {
				if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
				StringGrid1->Cells[1][ii + 2] = S1;
				StringGrid1->Cells[2][ii + 2] = S2;
				++ii;
			}
		}
	} // for

	  // insert variables declared
	range = Global::Mapdeclvar.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		SS = itMap->second.first;


		//previous code

		//pos = find_if(Global::Mapreadvar.begin(), Global::Mapreadvar.end(),
		//value_equals<KeyType2, KeyType2, Pairstr>(SS));

		//pos2 = find_if(Global::Mapdeclobs.begin(), Global::Mapdeclobs.end(),
		//value_equals<KeyType2, KeyType2, Pairstr>(SS));



		for (itMap2 = Global::Mapreadvar.begin(); itMap2 != Global::Mapreadvar.end(); ++itMap2)
		{
			if (itMap2->second.first == SS)
			{
				break;
			}
		}
		pos = itMap2;

		for (itMap2 = Global::Mapdeclobs.begin(); itMap2 != Global::Mapdeclobs.end(); ++itMap2)
		{
			if (itMap2->second.first == SS)
			{
				break;
			}
		}
		pos2 = itMap2;


		//new code. need to change.		
		//pos = Global::Mapreadvar.end();
		//pos2 = Global::Mapdeclobs.end();


		if ((pos == Global::Mapreadvar.end() || Not_Obs(S, SS)) && pos2 == Global::Mapdeclobs.end()) {
			int Indx = StringGrid1->Cols[3].find(SS);
			if (Indx == -1 && Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) {
				if (StringGrid1->RowCount < ii + 3) StringGrid1->RowCount = ii + 3;
				StringGrid1->Cells[3][ii + 2] = SS;
				++ii;
			}
		}
	} // for

	  // insert parameters declared
	range = Global::Mapdeclpar.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		if (Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) {
			SS = itMap->second.first;
			if (StringGrid1->RowCount < ii + 3)
				StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[4][ii + 2] = SS;
			++ii;
		}
	} // for

	  // insert observations declared
	range = Global::Mapdeclobs.equal_range(S);
	ii = 0;
	for (itMap = range.first; itMap != range.second; ++itMap) {
		if (Variation_Decide(Variation, (itMap->second).second) && Visible_Decide((itMap->second).second)) {
			SS = itMap->second.first;
			if (StringGrid1->RowCount < ii + 3)
				StringGrid1->RowCount = ii + 3;
			StringGrid1->Cells[5][ii + 2] = SS;
			++ii;
		}
	} // for

	if (StringGrid1->RowCount > 1) StringGrid1->FixedRows = 1;

	while (listcontrol.DeleteColumn(0));

	//listcontrol.DeleteAllItems();

	//listcontrol.InsertColumn(0, _T("Observations"), LVCFMT_LEFT, 95);
	//listcontrol.InsertColumn(1, _T("Modules"), LVCFMT_LEFT, 95);
	//listcontrol.InsertColumn(2, _T("Inputs"), LVCFMT_LEFT, 95);
	//listcontrol.InsertColumn(3, _T("Outputs"), LVCFMT_LEFT, 95);
	//listcontrol.InsertColumn(4, _T("Parameters"), LVCFMT_LEFT, 95);
	//listcontrol.InsertColumn(5, _T("New Observations"), LVCFMT_LEFT, 95);

	for (int i = 1; i < StringGrid1->RowCount; i++)
	{
		//CString cstr0(StringGrid1->Cells[0][i].c_str());
		//CString cstr1(StringGrid1->Cells[1][i].c_str());
		//CString cstr2(StringGrid1->Cells[2][i].c_str());
		//CString cstr3(StringGrid1->Cells[3][i].c_str());
		//CString cstr4(StringGrid1->Cells[4][i].c_str());
		//CString cstr5(StringGrid1->Cells[5][i].c_str());

		m->observations.push_back(StringGrid1->Cells[0][i]);
		m->modules.push_back(StringGrid1->Cells[1][i]);
		m->inputs.push_back(StringGrid1->Cells[2][i]);
		m->outputs.push_back(StringGrid1->Cells[3][i]);
		m->parameters.push_back(StringGrid1->Cells[4][i]);
		m->newobservations.push_back(StringGrid1->Cells[5][i]);
		m->count++;

		//int nIndex = listcontrol.InsertItem(i - 1, cstr0);
		//listcontrol.SetItemText(nIndex, 1, cstr1);
		//listcontrol.SetItemText(nIndex, 2, cstr2);
		//listcontrol.SetItemText(nIndex, 3, cstr3);
		//listcontrol.SetItemText(nIndex, 4, cstr4);
		//listcontrol.SetItemText(nIndex, 5, cstr5);
	}
	//fdmodules[fdmoduleCount] = m;
	//fdmoduleCount++;

	//return m;

}

bool FlowDiagramDlg::Variation_Decide(int Variation_set, long Variation) {

	VandP V; V.Set(Variation);

	long variations = V.GetV(); // & 2047;

	if ((variations & 2048) != 0 && Variation_set == 0 || // handles VARIATION_0
		(variations & 4096) != 0 ||                        // handles VARIATION_0
		(variations == 0) ||                               // handles VARIATION_ORG
		(variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
		return true;
	else
		return false;
}

bool FlowDiagramDlg::Visible_Decide(long Variation) {

	VandP V; V.Set(Variation);
	long Visible = V.GetP();
	return Visible == 1;
}

bool FlowDiagramDlg::Not_Obs(string Mod, string Var) {

	pair<Mapstr::iterator, Mapstr::iterator> rangeIobs = Global::Mapreadvar.equal_range(Mod);
	for (Mapstr::iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
		if (Var == itMap->second.first)
			return false;

	return true;
}



void FlowDiagramDlg::OnPaint()
{

	/*
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages	
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();
	//rect.SetRect(0,0,1000,1000);

	//AdjustWindowRect(&rect,NULL, false);


	//HFONT hFont = CreateFont(10, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
	HFONT hFont = CreateFont(12, 0, 0, 0, FW_LIGHT, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Times New Roman"));	
	SelectObject(dc, hFont);
	SetBkMode(dc, TRANSPARENT);



	FDModule fdmodules[20];
	int fdmoduleCount = 0;

	if (LocalModulesList != NULL)
		delete LocalModulesList;

	LocalModulesList = new TStringList; // holds parameters/observations already used
	LocalModulesList->Assign(Global::OurModulesList);

	for (int ii = 0; ii < Global::OurModulesList->Count; ii++) {
		ClassModule* thisModule = (ClassModule*)Global::OurModulesList->Objects[ii];
		thisModule->variation_max = 0;
		thisModule->decl();

		fdmodules[ii] = GetModuleDetails(thisModule->Name, thisModule);
		fdmodules[ii].modulename = thisModule->Name;
		fdmodules[ii].FindInputList();
		fdmodules[ii].FindOutputList();

		fdmoduleCount++;
	}

	int rectHeight = height / (fdmoduleCount*2+1);
	int x = 120;
	int y = 50;
	int xwidth = 50;
	int minheight = 15;
	int textoffset = 12;
	int lastxleft = 0;
	int lastxright = 0;
	int cordx, cordy;

	//assigning co-ordinates to the module rectangles.
	for (int i = 0; i < fdmoduleCount; i++)
	{
		//determining the rect height.
		int ilength = fdmodules[i].ilength;
		int olength = fdmodules[i].olength;

		if (ilength > olength) { rectHeight = ilength * minheight + minheight; }
		else { rectHeight = olength * minheight + minheight; }

		fdmodules[i].x1 = x;
		fdmodules[i].y1 = y;
		fdmodules[i].x2 = x+xwidth;
		fdmodules[i].y2 = fdmodules[i].y1 + rectHeight;

		x = fdmodules[i].x2 + (fdmodules[i].olength+1)*minheight + minheight;
		y = fdmodules[i].y2 + 50;
	}

	//drawing the module rectangles.
	for (int i = 0; i < fdmoduleCount; i++)
	{
		CString mname(fdmodules[i].modulename.c_str());

		dc.Rectangle(fdmodules[i].x1, fdmodules[i].y1, fdmodules[i].x2, fdmodules[i].y2);
		dc.TextOutW(fdmodules[i].x1, fdmodules[i].y2+5, mname);
	}


	for (int i = 0; i < fdmoduleCount; i++)
	{
		//setting the inputs.
		for (int j = 0; j < fdmodules[i].ilength; j++)
		{
			//find previous module and input
			string input = fdmodules[i].inputlist[j];
			int mi = FindPreviousModule(input, i, fdmodules);
			if (mi == -1)
			{
				cordx = fdmodules[i].x1; cordy = fdmodules[i].y1 + (j + 1) * minheight;
				dc.MoveTo(0, cordy);
				dc.LineTo(cordx, cordy);

				CString cstr(input.c_str());
				dc.TextOutW(0, cordy- textoffset, cstr);
			}
			else
			{
				int iserial = fdmodules[mi].GetInputSerial(input);
				int oserial = fdmodules[mi].GetOutputSerial(input);
				if (iserial >= 0)
				{
					int yy = fdmodules[mi].y1 + (iserial + 1) * minheight;
					int xx = fdmodules[mi].x1 - (iserial + 1) * minheight;
					dc.MoveTo(xx, yy);
					yy = fdmodules[i].y1 + (j + 1)*minheight;
					dc.LineTo(xx,yy);
					dc.MoveTo(xx,yy);
					dc.LineTo(fdmodules[i].x1,yy);

					CString cstr(input.c_str());
					dc.TextOutW(fdmodules[i].x1-50, yy - textoffset, cstr);
				}
				if (oserial >= 0)
				{
					int yy = fdmodules[mi].y1 + (oserial + 1) * minheight;
					int xx = fdmodules[mi].x2 + (oserial + 1) * minheight;
					dc.MoveTo(xx, yy);
					yy = fdmodules[i].y1 + (j + 1)*minheight;
					dc.LineTo(xx, yy);
					dc.MoveTo(xx, yy);
					dc.LineTo(fdmodules[i].x1, yy);

					CString cstr(input.c_str());
					dc.TextOutW(fdmodules[i].x1 - 50, yy - textoffset, cstr);
				}
			}
		}

		//setting the outputs
		for (int j = 0; j < fdmodules[i].olength; j++)
		{
			cordx = fdmodules[i].x2; cordy = fdmodules[i].y1 + (j + 1)*minheight;

			dc.MoveTo(cordx, cordy);
			dc.LineTo(cordx +400, cordy);

			CString cstr(fdmodules[i].outputlist[j].c_str());
			dc.TextOutW(cordx+20, cordy - textoffset, cstr);
		}
	}

	*/


}

int FlowDiagramDlg::FindPreviousModule(string input, int mcount, FDModule mods[])
{
	for (int i = 0; i < mcount; i++)
	{
		/*for (int j = 0; j < mods[i].count; j++)
		{
			if (input == mods[i].inputs[j]) { return i; }
			if (input == mods[i].parameters[j]) { return i; }
			if (input == mods[i].outputs[j]) { return i; }
		}*/
		for (int j = 0; j < mods[i].ilength; j++) 
		{ 
			if (input == mods[i].inputlist[j]) 
			{ 
				return i; 
			} 
		}
		for (int j = 0; j < mods[i].olength; j++) 
		{ 
			if (input == mods[i].outputlist[j]) 
			{ 
				return i; 
			} 
		}
	}

	return -1;
}

void FlowDiagramDlg::DrawModules() {

	Mapstr::iterator itMap;
	pair<Mapstr::iterator, Mapstr::iterator> rangeO;

	string S, SS;

	//Not used commenting out jhs507
	//std::vector<std::string> *List = new std::vector<std::string>();     // holds parameters/observations already used 
	std::vector<std::string> * ModList = new std::vector<std::string>();  // holds parameters/observations already used in current module
	std::vector<std::pair<std::string, int>> *InputCnt = new std::vector<std::pair<std::string, int>>(); // holds parameters/observations use count

	//int AdjWidth; varible is unreferenced commenting out for now - jhs507
	//int AdjHeight; varible is unreferenced commenting out for now - jhs507

	LocalModulesList = new std::vector<std::pair<std::string, ClassModule *>>(); // holds parameters/observations already used
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end();
		modIt++
		)
	{
		LocalModulesList->push_back(std::pair<std::string, ClassModule *>(modIt->first, modIt->second));
	}

	Box Boxes[1000];

	//for (int ii = 0; LocalModulesList->Count > ii; ++ii) {

	//	S = LocalModulesList->Strings[ii];

	//	// find 'forward' PUT and GET inputs to make space for them

	//	for (int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

	//		if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
	//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P" ||
	//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
	//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G") {

	//			int Mod = (int)FlowForm->StringGrid1->Cols[cc]->Objects[1];

	//			if (ii < Mod) { // later module
	//				++Boxes[ii].PadjY;
	//			} // if later PUT
	//		} // if PUT
	//	} // for Columns
	//} // for Modules

	  // Determine parameters or observations used more than once
	  //   Problem with groups and MultiMaps the same parameter can occur more than once in the group.

	bool DisplyPar = true;

	string inputs[50][100];
	int counts[50];


	for (size_t ii = 0; LocalModulesList->size() > ii; ++ii) {

		S = LocalModulesList->at(ii).first;


		counts[ii] = 0;
		// plot parameters or observations

		Mapstr::iterator pos, End;
		if (DisplyPar) {
			Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
			rangeO = Global::Mapdeclpar.equal_range(S);
			End = Global::Mapdeclpar.end();
		}
		else {
			Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
			rangeO = Global::Mapreadvar.equal_range(S);
			End = Global::Mapreadvar.end();
		}

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++) {
			
			inputs[ii][counts[ii]] = SS; counts[ii]++;

			SS = itMap->second.first; // name of parameter or observation
			if (Variation_Decide(ii, itMap->second.second)) 
			{
				
				int Indx = -1;
				for (size_t it = 0; it < InputCnt->size(); it++)
				{
					if (InputCnt->at(it).first == SS)
					{
						Indx = it;
						break;
					}
				}

				if (Indx == -1) // first time
				{
					InputCnt->push_back(std::pair<std::string, int>(SS, -1));
				}
				else 
				{
					int InCnt = InputCnt->at(Indx).second;
					if (InCnt > 0)
					{
						InputCnt->at(Indx).second = -2; // make negative - cannot count again this group (module)
					}

				} // else
			} // decide
		} // for

		for (size_t ii = 0; ii < InputCnt->size(); ++ii) // make positive
		{
			InputCnt->at(ii).second = abs(InputCnt->at(ii).second);
		}

	}

	// Find module that parameter or observation first used
	for (size_t	ii = 0; LocalModulesList->size() > ii; ++ii) {

		S = LocalModulesList->at(ii).first;

		// plot parameters or observations

		Mapstr::iterator pos, End;
		if (DisplyPar) {
			Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
			rangeO = Global::Mapdeclpar.equal_range(S);
			End = Global::Mapdeclpar.end();
		}
		else {
			Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
			rangeO = Global::Mapreadvar.equal_range(S);
			End = Global::Mapreadvar.end();
		}

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++) 
		{
			SS = itMap->second.first; // name of parameter or observation
			int Indx = -1;
			for (size_t it = 0; it < InputCnt->size(); it++)
			{
				if (InputCnt->at(it).first == SS)
				{
					Indx = it;
					break;
				}
			}

			if (Indx > -1) 
			{
				int InCnt = InputCnt->at(Indx).second;
				if (InCnt > 1) 
				{
					++Boxes[ii].ObsCntX;
					InputCnt->at(Indx).second = -2; // make negative - cannot count again this group (module)
				}
			}
		}

		for (size_t ii = 0; ii < InputCnt->size(); ++ii) // make positive
		{
			InputCnt->at(ii).second = abs(InputCnt->at(ii).second);
		}
	}

	
	for (size_t ii = 0; LocalModulesList->size() > ii; ++ii) {

		S = LocalModulesList->at(ii).first;

		// plot parameters or observations

		//X = X + Boxes[ii].ObsCntX*CSpacing;

		Mapstr::iterator pos, End;
		if (DisplyPar) {
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

		ModList->clear(); // reset for this module

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++)
		{
			SS = itMap->second.first; // name of parameter or observation
			if (!Variation_Decide(ii, itMap->second.second)) // ignore
			{
				continue;
			}

			int indexOfSS = -1;
			for (size_t it = 0; it < ModList->size(); it++)
			{
				if (ModList->at(it) == SS)
				{
					indexOfSS = it;
					break;
				}
			}

			if (indexOfSS > -1) // only once per module
			{
				continue;
			}

			ModList->push_back(SS);

			int Indx = -1;
			for (size_t it = 0; it < InputCnt->size(); it++)
			{
				if (InputCnt->at(it).first == SS)
				{
					Indx = it;
					break;
				}
			}

			kk = 0;
			if (InputCnt->at(Indx).second == 2)
			{
				++kk;
			}

			++jj;

			//Indx = List->IndexOf(SS); 

			//if (Indx == -1) {
			//	FlowForm->pFlow->MoveTo(CSpacing, Y + Height / 2 + jj * CSpacing);
			//	FlowForm->pFlow->LineTo(X, Y + Height / 2 + jj * CSpacing);
			//	FlowForm->pFlow->TextOut(CSpacing, Y + Height / 2 + (jj - 1)*CSpacing + 1, SS);

			//	++Boxes[ii].PadjX;

			//	ModandVar XY;
			//	XY.PutX(ObsX);
			//	XY.PutY(Y + Height / 2 + jj * CSpacing);

			//	List->AddObject(SS, (TObject*)XY.both);

			//	ObsX += (kk*CSpacing);
			//}
			//else {
			//	ModandVar XY;
			//	XY.both = (int)List->Objects[Indx];

			//	FlowForm->pFlow->MoveTo(XY.GetX(), XY.GetY());
			//	FlowForm->pFlow->LineTo(XY.GetX(), Y + Height / 2 + jj * CSpacing);
			//	FlowForm->pFlow->LineTo(X, Y + Height / 2 + jj * CSpacing);

			//	XY.PutY(Y + Height / 2 + jj * CSpacing);
			//	List->Objects[Indx] = (TObject*)XY.both;

			//	int W = FlowForm->pFlow->TextWidth(SS);
			//	FlowForm->pFlow->TextOut(X - W - 1, Y + Height / 2 + (jj - 1)*CSpacing + 1, SS);

			//} // else
		} // for



		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		

		  
		  // plot get variable inputs

		//Boxes[ii].InCnt = 0;
		//for (int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

		//	if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
		//		FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G" ||
		//		FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
		//		FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P") {

		//		++Boxes[ii].InCnt;
		//		int Var = (int)FlowForm->StringGrid1->Cols[cc]->Objects[0];
		//		int Mod = (int)FlowForm->StringGrid1->Cols[cc]->Objects[1];
		//		int ToX, ToY;
		//		int InX = X + Width / 2 + Boxes[ii].InCnt*CSpacing - CSpacing / 2;

		//		if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
		//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G") {
		//			Boxes[Mod].GetXY(Var, InX, ToX, ToY);
		//			if (ii > Mod) {
		//				FlowForm->pFlow->MoveTo(InX, Y);
		//				FlowForm->pFlow->LineTo(InX, ToY);
		//				FlowForm->pFlow->LineTo(ToX, ToY);
		//			}
		//		}
		//	} // if
		//} // for


		  

		  // plot module box

		//int First, Last;
		//Boxes[ii].OutCnt = FlowForm->GetNumVar(ii, First, Last);

		//Boxes[ii].OutXs = new int[Boxes[ii].OutCnt];
		//Boxes[ii].OutYs = new int[Boxes[ii].OutCnt];

		//for (int jj = 0; Boxes[ii].OutCnt > jj; ++jj) {
		//	Boxes[ii].OutXs[jj] = 0;
		//	Boxes[ii].OutYs[jj] = 0;
		//} // for

		//AdjWidth = Width + Boxes[ii].InCnt*CSpacing;
		//AdjHeight = Height + max(Boxes[ii].OutCnt, Boxes[ii].ObsCnt)*CSpacing;
		//Boxes[ii].Height = Height;

		//FlowForm->pFlow->RoundRect(X, Y, X + AdjWidth, Y + AdjHeight, 10, 10);

		// save values

		//Boxes[ii].Xul = X;
		//Boxes[ii].Yul = Y;

		//Boxes[ii].Xlr = X + AdjWidth;
		//Boxes[ii].Ylr = Y + AdjHeight;

		//Boxes[ii].CSpacing = CSpacing;

		//// plot variable output names

		//for (int cc = First; Last > cc; ++cc) {
		//	String S = FlowForm->StringGrid1->Cols[cc]->Strings[0];
		//	FlowForm->pFlow->TextOut(X + AdjWidth + 1, Y + Height / 2 + (cc - First)*CSpacing, S);

		//	int W = FlowForm->pFlow->TextWidth(S);
		//	W = (W / CSpacing + 1)*CSpacing;
		//	if (W > Boxes[ii].MaxOutNameLen)
		//		Boxes[ii].MaxOutNameLen = W;
		//}

		// plot module name

		//int W = FlowForm->pFlow->TextWidth(FlowForm->LocalModulesList->Strings[ii]);

		//String S = FlowForm->LocalModulesList->Strings[ii]; // add variation
		//ClassModule* thisModule = (ClassModule*)FlowForm->LocalModulesList->Objects[ii];
		//if (thisModule->variation != 0) {
		//	String AA("#0");
		//	AA[2] += log(thisModule->variation) / log(2) + 1;
		//	S += AA;
		//}

		//FlowForm->pFlow->TextOut(X + AdjWidth / 2 - W / 2, Y + AdjHeight + VSpacing / 4, S);
		//X = X + Boxes[ii].MaxOutNameLen + AdjWidth;
		//Y = Y + VSpacing + AdjHeight;
	} // for

	/*
	Xmax = (X / 20 + 2) * 20;
	Ymax = (Y / 20 + 2) * 20;

	int Yn = Global::MapAKA.size() + 5;
	int Xn = Xmax - 350;

	// plot backward PUT or GET variables

	for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

		X = Boxes[ii].Xul;
		Y = Boxes[ii].Yul;

		Boxes[ii].InCnt = 0;
		long Back_PGs = 0; // used to offset forward lines

		for (int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

			if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
				FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G" ||
				FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
				FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P") {

				++Boxes[ii].InCnt;
				int Var = (int)FlowForm->StringGrid1->Cols[cc]->Objects[0];
				int Mod = (int)FlowForm->StringGrid1->Cols[cc]->Objects[1];
				int ToX, ToY;
				int InX = X + Width / 2 + Boxes[ii].InCnt*CSpacing - CSpacing / 2;

				Boxes[Mod].GetXY(Var, InX, ToX, ToY);
				int W = FlowForm->pFlow->TextWidth(FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2]);
				if (ii > Mod) {
					if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
						FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P") {
						FlowForm->pFlow->TextOut(InX - W / 2, Y + CSpacing / 4, FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2]);

						FlowForm->pFlow->MoveTo(InX, Y);
						FlowForm->pFlow->LineTo(InX, ToY);
						FlowForm->pFlow->LineTo(ToX, ToY);
					}
				}
				else { // forward puts and gets
					if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
						FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G") {
						String Message = "backward GET" + String(" variable \"") +
							FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
							FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
							FlowForm->StringGrid1->Cols[0]->Strings[ii + 2];
						FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
					}
					else {
						String Message = "backward PUT" + String(" variable \"") +
							FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
							FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
							FlowForm->StringGrid1->Cols[0]->Strings[ii + 2];
						FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
					}

					FlowForm->pFlow->TextOut(InX - W / 2, Y + CSpacing / 4, FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2]);
					FlowForm->pFlow->MoveTo(InX, Y);
					FlowForm->pFlow->LineTo(InX, Y - (Boxes[ii].PadjY - Back_PGs)*CSpacing);

					float XX = Boxes[Mod].Xlr + (Boxes[Mod].OutCnt - Var)*CSpacing + CSpacing + Boxes[Mod].MaxOutNameLen;

					FlowForm->pFlow->LineTo(XX, Y - (Boxes[ii].PadjY - Back_PGs++)*CSpacing);
					FlowForm->pFlow->LineTo(XX, ToY);
					FlowForm->pFlow->LineTo(Boxes[Mod].Xlr, ToY);
				}
			}
		} // for
	} // for

	if (!Global::MapAKA.empty()) {
		Mapstr2::iterator it;

		int Yn = 3; int Yf = 3;
		int Xn = Xmax - 350; int Xf = Xn + 25;

		for (it = Global::MapAKA.begin(); it != Global::MapAKA.end(); ++it) {

			string Message = (*it).first;
			Message = Message.substr(Message.find(' ') + 1);
			Message.insert(Message.find(' ') + 1, " -  ");
			Message = '\"' + Message + '\"';

			if (Yn == 3)
				FlowForm->pFlow->TextOut(Xn, Yn++*CSpacing, "AKAs.");
			string Message2 = (*it).second;
			string::size_type idx = Message2.find(' ');
			Message += " linked to \"" + Message2.substr(idx + 1) + " - " + Message2.substr(0, idx) + '\"';
			FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
		}
	}

	int Mod = FlowForm->LocalModulesList->Count - 1;
	Xmax += Boxes[Mod].MaxOutNameLen + (Boxes[Mod].OutCnt - 1)*CSpacing;

	FlowForm->pFlow->MoveTo(Xmax - 20, Ymax);
	FlowForm->pFlow->LineTo(Xmax, Ymax);
	FlowForm->pFlow->LineTo(Xmax, Ymax - 20);

	int W = FlowForm->pFlow->TextWidth(FlowForm->Title);
	FlowForm->pFlow->TextOut(Xmax / 2 - W / 2, CSpacing, FlowForm->Title);

	FlowForm->HorzScrollBar->Range = Xmax;
	FlowForm->VertScrollBar->Range = Ymax;

	delete FlowForm->pFlow;

	FlowForm->pFlow->Refresh();

	delete List;
	delete ModList;
	delete InputCnt;

	*/
}

void FlowDiagramDlg::GetModulesInputsAndOutputs(FDModule * mods) 
{
	Mapstr::iterator itMap;
	pair<Mapstr::iterator, Mapstr::iterator> rangeO;

	string S, SS;

	// holds parameters/observations already used
	std::vector<std::pair<std::string, int>> * List = new std::vector<std::pair<std::string, int>>();
	std::vector<std::string> *ModList = new std::vector<std::string>();  // holds parameters/observations already used in current module
	std::vector<std::pair<std::string, int>> *InputCnt = new std::vector<std::pair<std::string, int>>(); // holds parameters/observations use count

	//int AdjWidth; varible is unreferenced commenting out for now - jhs507
	//int AdjHeight; varible is unreferenced commenting out for now - jhs507

	LocalModulesList = new std::vector<std::pair<std::string, ClassModule *>>(); // holds parameters/observations already used
	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end();
		modIt++
		)
	{
		LocalModulesList->push_back(std::pair<std::string, ClassModule *>(modIt->first, modIt->second));
	}

	Box Boxes[1000];

	//for (int ii = 0; LocalModulesList->Count > ii; ++ii) {

	//	S = LocalModulesList->Strings[ii];

	//	// find 'forward' PUT and GET inputs to make space for them

	//	for (int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

	//		if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
	//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P" ||
	//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
	//			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G") {

	//			int Mod = (int)FlowForm->StringGrid1->Cols[cc]->Objects[1];

	//			if (ii < Mod) { // later module
	//				++Boxes[ii].PadjY;
	//			} // if later PUT
	//		} // if PUT
	//	} // for Columns
	//} // for Modules

	// Determine parameters or observations used more than once
	//   Problem with groups and MultiMaps the same parameter can occur more than once in the group.

	bool DisplyPar = true;

	string inputs[50][100];
	int counts[50];


	for (size_t ii = 0; LocalModulesList->size() > ii; ++ii) {

		S = LocalModulesList->at(ii).first;


		counts[ii] = 0;
		// plot parameters or observations

		Mapstr::iterator pos, End;
		if (DisplyPar) {
			Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
			rangeO = Global::Mapdeclpar.equal_range(S);
			End = Global::Mapdeclpar.end();
		}
		else {
			Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
			rangeO = Global::Mapreadvar.equal_range(S);
			End = Global::Mapreadvar.end();
		}

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++) {

			inputs[ii][counts[ii]] = SS; counts[ii]++;

			SS = itMap->second.first; // name of parameter or observation
			if (Variation_Decide(ii, itMap->second.second)) 
			{
				int Indx = -1;
				for (size_t it = 0; it < InputCnt->size(); it++)
				{
					if (InputCnt->at(it).first == SS)
					{
						Indx = it;
						break;
					}
				}

				if (Indx == -1) // first time
				{
					InputCnt->push_back(std::pair<std::string, int>(SS, -1));
				}
				else 
				{
					int InCnt = InputCnt->at(Indx).second;
					if (InCnt > 0)
					{
						InputCnt->at(Indx).second = -2; // make negative - cannot count again this group (module)
					}

				} // else
			} // decide
		} // for

		for (size_t ii = 0; ii < InputCnt->size(); ++ii) // make positive
		{
			InputCnt->at(ii).second = abs(InputCnt->at(ii).second);
		}

	}

	// Find module that parameter or observation first used
	for (size_t ii = 0; LocalModulesList->size() > ii; ++ii) {

		S = LocalModulesList->at(ii).first;

		// plot parameters or observations

		Mapstr::iterator pos, End;
		if (DisplyPar) {
			Boxes[ii].ObsCnt = Global::Mapdeclpar.count(S);
			rangeO = Global::Mapdeclpar.equal_range(S);
			End = Global::Mapdeclpar.end();
		}
		else {
			Boxes[ii].ObsCnt = Global::Mapreadvar.count(S);
			rangeO = Global::Mapreadvar.equal_range(S);
			End = Global::Mapreadvar.end();
		}

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++) 
		{
			SS = itMap->second.first; // name of parameter or observation
		
			int Indx = -1;
			for (size_t it = 0; it < InputCnt->size(); it++)
			{
				if (InputCnt->at(it).first == SS)
				{
					Indx = it;
					break;
				}
			}

			if (Indx > -1) 
			{
				int InCnt = InputCnt->at(Indx).second;
				if (InCnt > 1) 
				{
					++Boxes[ii].ObsCntX;
					InputCnt->at(Indx).second = -2; // make negative - cannot count again this group (module)
				}
			}
		}

		for (size_t ii = 0; ii < InputCnt->size(); ++ii) // make positive
		{
			InputCnt->at(ii).second =abs(InputCnt->at(ii).second);
		}
	}


	for (size_t ii = 0; LocalModulesList->size() > ii; ++ii) {

		S = LocalModulesList->at(ii).first;

		// plot parameters or observations

		//X = X + Boxes[ii].ObsCntX*CSpacing;

		Mapstr::iterator pos, End;
		if (DisplyPar) {
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

		ModList->clear(); // reset for this module

		for (itMap = rangeO.first; itMap != rangeO.second; itMap++) 
		{
			SS = itMap->second.first; // name of parameter or observation
			if (!Variation_Decide(ii, itMap->second.second)) // ignore
			{
				continue;
			}

			int indxOfSS = -1;
			for (size_t it = 0; it < ModList->size(); it++)
			{
				if (ModList->at(it) == SS)
				{
					indxOfSS = it;
					break;
				}
			}

			if (indxOfSS > -1) // only once per module
			{
				continue;
			}

			ModList->push_back(SS);

			int Indx = -1;
			for (size_t it = 0; it < InputCnt->size(); it++)
			{
				if (InputCnt->at(it).first == SS)
				{
					Indx = it;
					break;
				}
			}


			kk = 0;
			if (InputCnt->at(Indx).second == 2)
			{
				++kk;
			}

			++jj;

			Indx = -1;
			for (size_t it = 0; it < List->size(); it++)
			{
				if (List->at(it).first == SS)
				{
					Indx = it;
					break;
				}
			}

			if (Indx == -1) 
			{
			//	FlowForm->pFlow->MoveTo(CSpacing, Y + Height / 2 + jj * CSpacing);
			//	FlowForm->pFlow->LineTo(X, Y + Height / 2 + jj * CSpacing);
			//	FlowForm->pFlow->TextOut(CSpacing, Y + Height / 2 + (jj - 1)*CSpacing + 1, SS);

				++Boxes[ii].PadjX;

			//	ModandVar XY;
			//	XY.PutX(ObsX);
			//	XY.PutY(Y + Height / 2 + jj * CSpacing);

				List->push_back(std::pair<std::string, int>(SS, NULL));

			//	ObsX += (kk*CSpacing);
			}
			else 
			{
				ModandVar XY;
				XY.both = List->at(Indx).second;

			//	FlowForm->pFlow->MoveTo(XY.GetX(), XY.GetY());
			//	FlowForm->pFlow->LineTo(XY.GetX(), Y + Height / 2 + jj * CSpacing);
			//	FlowForm->pFlow->LineTo(X, Y + Height / 2 + jj * CSpacing);

			//	XY.PutY(Y + Height / 2 + jj * CSpacing);
				List->at(Indx).second = XY.both;

			//	int W = FlowForm->pFlow->TextWidth(SS);
			//	FlowForm->pFlow->TextOut(X - W - 1, Y + Height / 2 + (jj - 1)*CSpacing + 1, SS);

			} // else
		} // for



		///////////////////////////////////////////////////Manishankar Mondal////////////////////////////////////////////////////////////////////

		mods[ii].modulename = S;
		for (size_t i = 0; i < ModList->size(); i++) 
		{ 
			mods[ii].inputlist.push_back(ModList->at(i)); 
		}
		mods[ii].ilength = ModList->size();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		  // plot get variable inputs

		  //Boxes[ii].InCnt = 0;
		  //for (int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

		  //	if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
		  //		FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G" ||
		  //		FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
		  //		FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P") {

		  //		++Boxes[ii].InCnt;
		  //		int Var = (int)FlowForm->StringGrid1->Cols[cc]->Objects[0];
		  //		int Mod = (int)FlowForm->StringGrid1->Cols[cc]->Objects[1];
		  //		int ToX, ToY;
		  //		int InX = X + Width / 2 + Boxes[ii].InCnt*CSpacing - CSpacing / 2;

		  //		if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
		  //			FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G") {
		  //			Boxes[Mod].GetXY(Var, InX, ToX, ToY);
		  //			if (ii > Mod) {
		  //				FlowForm->pFlow->MoveTo(InX, Y);
		  //				FlowForm->pFlow->LineTo(InX, ToY);
		  //				FlowForm->pFlow->LineTo(ToX, ToY);
		  //			}
		  //		}
		  //	} // if
		  //} // for




		  // plot module box

		  //int First, Last;
		  //Boxes[ii].OutCnt = FlowForm->GetNumVar(ii, First, Last);

		  //Boxes[ii].OutXs = new int[Boxes[ii].OutCnt];
		  //Boxes[ii].OutYs = new int[Boxes[ii].OutCnt];

		  //for (int jj = 0; Boxes[ii].OutCnt > jj; ++jj) {
		  //	Boxes[ii].OutXs[jj] = 0;
		  //	Boxes[ii].OutYs[jj] = 0;
		  //} // for

		  //AdjWidth = Width + Boxes[ii].InCnt*CSpacing;
		  //AdjHeight = Height + max(Boxes[ii].OutCnt, Boxes[ii].ObsCnt)*CSpacing;
		  //Boxes[ii].Height = Height;

		  //FlowForm->pFlow->RoundRect(X, Y, X + AdjWidth, Y + AdjHeight, 10, 10);

		  // save values

		  //Boxes[ii].Xul = X;
		  //Boxes[ii].Yul = Y;

		  //Boxes[ii].Xlr = X + AdjWidth;
		  //Boxes[ii].Ylr = Y + AdjHeight;

		  //Boxes[ii].CSpacing = CSpacing;

		  //// plot variable output names

		  //for (int cc = First; Last > cc; ++cc) {
		  //	String S = FlowForm->StringGrid1->Cols[cc]->Strings[0];
		  //	FlowForm->pFlow->TextOut(X + AdjWidth + 1, Y + Height / 2 + (cc - First)*CSpacing, S);

		  //	int W = FlowForm->pFlow->TextWidth(S);
		  //	W = (W / CSpacing + 1)*CSpacing;
		  //	if (W > Boxes[ii].MaxOutNameLen)
		  //		Boxes[ii].MaxOutNameLen = W;
		  //}

		  // plot module name

		  //int W = FlowForm->pFlow->TextWidth(FlowForm->LocalModulesList->Strings[ii]);

		  //String S = FlowForm->LocalModulesList->Strings[ii]; // add variation
		  //ClassModule* thisModule = (ClassModule*)FlowForm->LocalModulesList->Objects[ii];
		  //if (thisModule->variation != 0) {
		  //	String AA("#0");
		  //	AA[2] += log(thisModule->variation) / log(2) + 1;
		  //	S += AA;
		  //}

		  //FlowForm->pFlow->TextOut(X + AdjWidth / 2 - W / 2, Y + AdjHeight + VSpacing / 4, S);
		  //X = X + Boxes[ii].MaxOutNameLen + AdjWidth;
		  //Y = Y + VSpacing + AdjHeight;
	} // for

	  /*
	  Xmax = (X / 20 + 2) * 20;
	  Ymax = (Y / 20 + 2) * 20;

	  int Yn = Global::MapAKA.size() + 5;
	  int Xn = Xmax - 350;

	  // plot backward PUT or GET variables

	  for (int ii = 0; FlowForm->LocalModulesList->Count > ii; ++ii) {

	  X = Boxes[ii].Xul;
	  Y = Boxes[ii].Yul;

	  Boxes[ii].InCnt = 0;
	  long Back_PGs = 0; // used to offset forward lines

	  for (int cc = 1; cc < FlowForm->StringGrid1->ColCount; ++cc) {

	  if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
	  FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G" ||
	  FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
	  FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P") {

	  ++Boxes[ii].InCnt;
	  int Var = (int)FlowForm->StringGrid1->Cols[cc]->Objects[0];
	  int Mod = (int)FlowForm->StringGrid1->Cols[cc]->Objects[1];
	  int ToX, ToY;
	  int InX = X + Width / 2 + Boxes[ii].InCnt*CSpacing - CSpacing / 2;

	  Boxes[Mod].GetXY(Var, InX, ToX, ToY);
	  int W = FlowForm->pFlow->TextWidth(FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2]);
	  if (ii > Mod) {
	  if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "P" ||
	  FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*P") {
	  FlowForm->pFlow->TextOut(InX - W / 2, Y + CSpacing / 4, FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2]);

	  FlowForm->pFlow->MoveTo(InX, Y);
	  FlowForm->pFlow->LineTo(InX, ToY);
	  FlowForm->pFlow->LineTo(ToX, ToY);
	  }
	  }
	  else { // forward puts and gets
	  if (FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "G" ||
	  FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2] == "*G") {
	  String Message = "backward GET" + String(" variable \"") +
	  FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
	  FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
	  FlowForm->StringGrid1->Cols[0]->Strings[ii + 2];
	  FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
	  }
	  else {
	  String Message = "backward PUT" + String(" variable \"") +
	  FlowForm->StringGrid1->Cols[cc]->Strings[1] + String(" - ") +
	  FlowForm->StringGrid1->Cols[cc]->Strings[0] + String("\" to ") +
	  FlowForm->StringGrid1->Cols[0]->Strings[ii + 2];
	  FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
	  }

	  FlowForm->pFlow->TextOut(InX - W / 2, Y + CSpacing / 4, FlowForm->StringGrid1->Cols[cc]->Strings[ii + 2]);
	  FlowForm->pFlow->MoveTo(InX, Y);
	  FlowForm->pFlow->LineTo(InX, Y - (Boxes[ii].PadjY - Back_PGs)*CSpacing);

	  float XX = Boxes[Mod].Xlr + (Boxes[Mod].OutCnt - Var)*CSpacing + CSpacing + Boxes[Mod].MaxOutNameLen;

	  FlowForm->pFlow->LineTo(XX, Y - (Boxes[ii].PadjY - Back_PGs++)*CSpacing);
	  FlowForm->pFlow->LineTo(XX, ToY);
	  FlowForm->pFlow->LineTo(Boxes[Mod].Xlr, ToY);
	  }
	  }
	  } // for
	  } // for

	  if (!Global::MapAKA.empty()) {
	  Mapstr2::iterator it;

	  int Yn = 3; int Yf = 3;
	  int Xn = Xmax - 350; int Xf = Xn + 25;

	  for (it = Global::MapAKA.begin(); it != Global::MapAKA.end(); ++it) {

	  string Message = (*it).first;
	  Message = Message.substr(Message.find(' ') + 1);
	  Message.insert(Message.find(' ') + 1, " -  ");
	  Message = '\"' + Message + '\"';

	  if (Yn == 3)
	  FlowForm->pFlow->TextOut(Xn, Yn++*CSpacing, "AKAs.");
	  string Message2 = (*it).second;
	  string::size_type idx = Message2.find(' ');
	  Message += " linked to \"" + Message2.substr(idx + 1) + " - " + Message2.substr(0, idx) + '\"';
	  FlowForm->pFlow->TextOut(Xn, ++Yn*CSpacing, Message.c_str());
	  }
	  }

	  int Mod = FlowForm->LocalModulesList->Count - 1;
	  Xmax += Boxes[Mod].MaxOutNameLen + (Boxes[Mod].OutCnt - 1)*CSpacing;

	  FlowForm->pFlow->MoveTo(Xmax - 20, Ymax);
	  FlowForm->pFlow->LineTo(Xmax, Ymax);
	  FlowForm->pFlow->LineTo(Xmax, Ymax - 20);

	  int W = FlowForm->pFlow->TextWidth(FlowForm->Title);
	  FlowForm->pFlow->TextOut(Xmax / 2 - W / 2, CSpacing, FlowForm->Title);

	  FlowForm->HorzScrollBar->Range = Xmax;
	  FlowForm->VertScrollBar->Range = Ymax;

	  delete FlowForm->pFlow;

	  FlowForm->pFlow->Refresh();

	  delete List;
	  delete ModList;
	  delete InputCnt;

	  */
}

