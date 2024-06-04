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
#include "ClassMacro.h"
#if defined(__linux__) || defined(__APPLE__) || defined(__MINGW32__)
	#include <cxxabi.h>
#endif

double Fday() { // used for variable DAY
	int year, month, day, h, m;
	StandardConverterUtility::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);
	return day;
}

double Fmonth() { // used for variable MONTH
	int year, month, day, h, m;
	StandardConverterUtility::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);
	return month;
}

double Fyear() { // used for variable YEAR
	int year, month, day, h, m;
	StandardConverterUtility::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);
	return year;
}

double Fjulian() { // used for variable JULIAN
	return julian("now");
}

double Fgetstep() { // used for variable STEP
	return getstep();
}

double Fgetfirst() { // used for variable FIRST

	return (getstep() % Global::Freq == 1);
}

double Fgetlast() { // used for variable LAST

	return (getstep() % Global::Freq == 0);
}

double Fgetrand() { // used for variable STEP
	return (double)rand() / RAND_MAX;
}


ClassMacro* ClassMacro::klone(string name) const {
	return new ClassMacro(name, MacroBegin, "11/13/07");
}

void ClassMacro::decl(void) {

	if (isGroup || isStruct) {

		if (Grpnhru > 0) {
			nhru = Grpnhru;
			if (Grpnhru > Global::maxhru)
				Global::maxhru = Grpnhru;
		}
		else if (nhru == 0)
			nhru = Global::nhru; // transfers current # of HRU's to module

								 //long m = (max<long>(GroupCnt, StructCnt));

		string S = Common::longtoStr((max<long>(GroupCnt, StructCnt)));

		if (isGroup) {

			declparam("HRU_group", TDim::NHRU, S, "1", "1e3", "group #", "()", &HRU_group);
		}

		if (isStruct) 
		{
			std::string Choice;

			std::ostringstream temp;

			for (size_t it = 0; it < GrpStringList->size(); it++)
			{
				if (it)
				{
					temp << ", ";
				}
				temp << GrpStringList->at(it).first;
			}
			temp << endl;
			
			Choice = temp.str();

			declparam("HRU_struct", TDim::NHRU, "[1]", "1", Common::longtoStr(GrpStringList->size()), string("select using 1/2/3 ... module/group from '" + Choice + "'"), "()", &HRU_struct); // _group
		}

		Modules.clear();
		unsigned short Variation;

		for (size_t ii = 0; ii < GrpStringList->size(); ii++) 
		{
			std::string S = GrpStringList->at(ii).first;

			std::string::size_type idx = S.find("#");
			if (idx != std::string::npos) 
			{
				Variation = (unsigned short)(pow(2, S[idx + 1] - char('1')));
				S = S.substr(0, idx);
			}
			else
			{
				Variation = 0;
			}

			int Indx = Global::AllModulesList->count(S);

			if (Indx == 0) 
			{

				Common::Message(string("Module: '" + S + "' not found!"), "Macro Error");
				CRHMException Except(string(string("module: ") + S + " not found in " + Name).c_str(), TExcept::TERMINATE);
				LogError(Except);
				throw Except;

				/*string s1 = "Module: '" + S + "' not found!";
				CString cstr(s1.c_str());
				AfxMessageBox(cstr);*/

				//continue;

			}

			ClassModule* Mod = Global::AllModulesList->find(S)->second;

			//ModulePtr Test(Mod->klone());
			ModulePtr Test(Mod->klone(Name));

			std::weak_ptr<ClassModule> MG(Test);


#if defined(_WIN32) && !defined(__MINGW32__)

			string S1 = typeid(*Mod).name();
			string S2 = typeid(*Test).name();

			S2 = S2.substr(6, S2.length()); // Remove the "class " from the begining of the class name string. 
#endif
#if defined(__linux__) || defined(__APPLE__) || defined(__MINGW32__) //introspection issue resolved for linux and apple as was suggested by Dr. Kevin. Manishankar
			int demangle_status = 0;
			string S1 = abi::__cxa_demangle(typeid(*Mod).name(), 0, 0, &demangle_status);
			auto Test_raw = Test.get(); //Dr. Kevin's edit for removing an warning.
			string S2 = abi::__cxa_demangle(typeid(*Test_raw).name(), 0, 0, &demangle_status);
#endif

			if (S2 == "ClassMacro")
				Test->ID = S;
			else {
				auto Test_raw = Test.get(); //Dr. Kevin's edit for removing an warning.
				Test->ID = typeid(*Test_raw).name();
				if (S2 == "Classobs")
					this->ObsModule = (ClassModule*)Test.get(); // causes HRU_OBS etc. update
			}

			Test->Name = Name; // was not needed in Borland code

			Test->HRU_struct = this->HRU_struct;

			Test->nhru = nhru;

			Test->GroupCnt = this->GroupCnt;

			Test->StructCnt = this->StructCnt;

			//      Test->isGroup = this->isGroup; // Not group - only member

			//      Test->isStruct = this->isStruct; // Not Struct - only member

			Test->variation = Variation;

			Test->DLLName = Mod->DLLName;

			Test->NameRoot = Mod->NameRoot;

			Test->Version = this->Version;

			if (isStruct)
				Test->ModuleIndx = ii + 1;
			else
				Test->ModuleIndx = this->ModuleIndx;

			Modules.push_back(Test);
		}

		/*
		list<ModulePtr> ::iterator iterM;
		iterM = Modules.begin();
		while (iterM != Modules.end()) {
		boost::weak_ptr<ClassModule> MP((*iterM));
		(*iterM)->nhru = nhru;
		//      (*iterM)->DLLName = DLLName;
		(*iterM)->decl();
		++iterM;
		}
		*/

		list<ModulePtr> ::iterator iterM;
		iterM = Modules.begin();
		while (iterM != Modules.end()) {
			//      boost::weak_ptr<ClassModule> MP((*iterM));
			ClassModule* MPP = (ClassModule*)(*iterM).get();
			string SS = (*iterM)->NameRoot.c_str();
			if ((*iterM)->variation > 0) { // handle variation name
				string  AA = "#0";
				AA[1] += (char)(log((*iterM)->variation) / log(2) + 1);
				SS += AA;
			}
			
			long jj = -1;
			for (size_t it = 0; it < GrpStringList->size(); it++)
			{
				if (GrpStringList->at(it).first == SS)
				{
					jj = it;
					break;
				}
			}

			GrpStringList->at(jj).second = MPP; // save pointer to module
			(*iterM)->nhru = nhru;
			(*iterM)->decl();
			++iterM;
		}

		return;
	}

	list<DefCRHMPtr> ::iterator iterC; // non Group - simple macro
									   //  long JJ = Calls.size();
	iterC = Calls.begin();
	while (iterC != Calls.end()) {
		std::weak_ptr<DefCRHM> CP((*iterC));
		(*iterC)->CallDecl();
		++iterC;
	}
}

void ClassMacro::init(void) {

	nhru = getdim(TDim::NHRU); // transfers current # of HRU's to module

	if (isGroup || isStruct) {

		LogMessage(" ");

		string SS;
		if (isGroup)
			SS = "Group: '" + NameRoot + "' ->";
		else
			SS = "Struct: '" + NameRoot + "' ->";

		for (size_t ii = 0; ii < GrpStringList->size(); ++ii)
		{
			SS += " " + GrpStringList->at(ii).first;
		}

		LogMessage(SS.c_str());

		list<ModulePtr> ::iterator iter;
		iter = Modules.begin();
		while (iter != Modules.end()) {
			std::weak_ptr<ClassModule> MP((*iter));
			(*iter)->init();

			++iter;
		}

		if (StructCnt) // force into range of modules in the group
			for (hh = 0; hh < nhru; ++hh) 
			{
				if (HRU_struct[hh] < 1)
				{
					const_cast<long*>  (HRU_struct)[hh] = 1;
				}
				if (HRU_struct[hh] > (long) GrpStringList->size())
				{
					const_cast<long*>  (HRU_struct)[hh] = GrpStringList->size();
				}
			}

		return;
	}

	list<DefCRHMPtr> ::iterator iter;
	iter = Calls.begin();
	while (iter != Calls.end()) {
		DefCRHM Op = (*(*iter));
		(*iter)->CallInit(nhru, nlay);
		++iter;
	}

	FP = vars.find("hh");
	if (FP == vars.end()) {
		vars.insert(make_pair("hh", VarCHRM()));
		FP = vars.find("hh");
	}

	FP->second.kind = TV::CRHMint;
	FP->second.ivalue = const_cast<long*> (&hh);
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "hh";
	FP->second.Me = this;

	FP = vars.find("NHRU");
	if (FP == vars.end()) {
		vars.insert(make_pair("NHRU", VarCHRM()));
		FP = vars.find("NHRU");
	}

	FP->second.kind = TV::LOCAL;
	FP->second.val = nhru;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "NHRU";
	FP->second.Me = this;

	FP = vars.find("GROUP");
	if (FP == vars.end()) {
		vars.insert(make_pair("GROUP", VarCHRM()));
		FP = vars.find("GROUP");
	}

	FP->second.kind = TV::LOCAL;
	FP->second.val = GroupCnt;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "GROUP";
	FP->second.Me = this;

	FP = vars.find("STRUCT");
	if (FP == vars.end()) {
		vars.insert(make_pair("STRUCT", VarCHRM()));
		FP = vars.find("STRUCT");
	}

	FP->second.kind = TV::LOCAL;
	FP->second.val = StructCnt;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "STRUCT";
	FP->second.Me = this;

	FP = vars.find("PI");
	if (FP == vars.end()) {
		vars.insert(make_pair("PI", VarCHRM()));
		FP = vars.find("PI");
	}
	FP->second.kind = TV::LOCAL;
	FP->second.val = M_PI;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "PI";

	FP = vars.find("NO_DISPLAY");
	if (FP == vars.end()) {
		vars.insert(make_pair("NO_DISPLAY", VarCHRM()));
		FP = vars.find("NO_DISPLAY");
	}
	FP->second.kind = TV::LOCAL;
	//FP->second.val = xLimit;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "NO_DISPLAY";

	FP = vars.find("FREQ");
	if (FP == vars.end()) {
		vars.insert(make_pair("FREQ", VarCHRM()));
		FP = vars.find("FREQ");
	}
	FP->second.kind = TV::LOCAL;
	FP->second.val = Global::Freq;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "FREQ";

	FP = vars.find("RAND");
	if (FP == vars.end()) {
		vars.insert(make_pair("RAND", VarCHRM()));
		FP = vars.find("RAND");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "RAND";
	FP->second.pget = Fgetrand;

	FP = vars.find("STEP");
	if (FP == vars.end()) {
		vars.insert(make_pair("STEP", VarCHRM()));
		FP = vars.find("STEP");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "STEP";
	FP->second.pget = Fgetstep;

	FP = vars.find("LASTINT");
	if (FP == vars.end()) {
		vars.insert(make_pair("LASTINT", VarCHRM()));
		FP = vars.find("LASTINT");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "LASTINT";
	FP->second.pget = Fgetlast;

	FP = vars.find("FIRSTINT");
	if (FP == vars.end()) {
		vars.insert(make_pair("FIRSTINT", VarCHRM()));
		FP = vars.find("FIRSTINT");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "FIRSTINT";
	FP->second.pget = Fgetfirst;

	FP = vars.find("JULIAN");
	if (FP == vars.end()) {
		vars.insert(make_pair("JULIAN", VarCHRM()));
		FP = vars.find("JULIAN");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "JULIAN";
	FP->second.pget = Fjulian;

	FP = vars.find("YEAR");
	if (FP == vars.end()) {
		vars.insert(make_pair("YEAR", VarCHRM()));
		FP = vars.find("YEAR");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "YEAR";
	FP->second.pget = Fyear;

	FP = vars.find("MONTH");
	if (FP == vars.end()) {
		vars.insert(make_pair("MONTH", VarCHRM()));
		FP = vars.find("MONTH");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "MONTH";
	FP->second.pget = Fmonth;

	FP = vars.find("DAY");
	if (FP == vars.end()) {
		vars.insert(make_pair("DAY", VarCHRM()));
		FP = vars.find("DAY");
	}
	FP->second.kind = TV::FUNget;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "DAY";
	FP->second.pget = Fday;

	FP = vars.find("ReadAheadObs");
	if (FP == vars.end()) {
		vars.insert(make_pair("ReadAheadObs", VarCHRM()));
		FP = vars.find("ReadAheadObs");
	}

	FP->second.kind = TV::FUNobs;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "ReadAheadObs";
	FP->second.Me = this;


	FP = vars.find("WriteAheadObs");
	if (FP == vars.end()) {
		vars.insert(make_pair("WriteAheadObs", VarCHRM()));
		FP = vars.find("WriteAheadObs");
	}

	FP->second.kind = TV::FUNobs;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "WriteAheadObs";
	FP->second.Me = this;

	calculator calc(eval, vars, Operations, PCiter, LastVar, LastVas); //  Our parser

	Operations.clear();

	string str(Global::MacroModulesList->at(Begin));

	for (int jj = Begin + 1; jj < End; ++jj) {
		string::size_type P = Global::MacroModulesList->at(jj).find("//");
		if (P != string::npos) {
			if (P - 1 > 0)
				str += " \n" + Global::MacroModulesList->at(jj).substr(1, P - 1);
		}
		else
			str += " \n" + Global::MacroModulesList->at(jj);
	}

	//str = str + " \n"; //updated by Manishankar for solving the parsing problem.

	execbase::Index = 0;
	string::iterator first = str.begin();
	parse_info<string::iterator> info;

	do {
		info = parse(first, str.end(), calc, space_p);

		if (!info.hit || info.length == 0)
		{
			string err(first, str.end());
			CRHMException TExcept(string("cannot parse the command string: ") + err.c_str(), TExcept::TERMINATE);
			LogError(TExcept);
		}
		else if (!info.full)
			first = info.stop;
	} while (!(info.full && info.hit));

	PCiter = Operations.begin();
	int n = 1;
	while (PCiter != Operations.end()) {
		(*PCiter)->OurOrder = n++;
		++PCiter;
	}
}

void ClassMacro::run(void) { // executed every interval

	if (isGroup || isStruct) {
		list<ModulePtr> ::iterator iter;
		iter = Modules.begin();
		while (iter != Modules.end()) {
			ModulePtr Op = (*iter);

			(*iter)->pre_run();
			(*iter)->run();
			++iter;
		}

		return;
	}

	for (hh = 1; chkStructOff(hh, nhru + 1); ++hh) { // note offset range

		PCiter = Operations.begin();
		while (PCiter != Operations.end()) {
			execbase Op = (*(*PCiter));
			double X = (*(*PCiter))(); // run instruction
			++PCiter;
			int Cnt = eval.size();
		}
	}

	int Cnt = eval.size();
	assert(eval.empty());
	assert(LastVar.empty());
	assert(LastVas.empty());
}

void ClassMacro::finish(bool good) { // only required for local storage and final output

	if (isGroup || isStruct) {
		list<ModulePtr> ::iterator iter;
		iter = Modules.begin();
		while (iter != Modules.end()) {
			ModulePtr Op = (*iter);
			Op->finish(false);
			++iter;
		}

		return;
	}

	Operations.clear();

	symtab_t::iterator pos;

	for (pos = vars.begin(); pos != vars.end();) { // remove local variables
		if (pos->second.kind == TV::LOCAL) {
			vars.erase(pos++);
		}
		else {
			++pos;
		}
	}
}

ClassMacro::ClassMacro(string Name, int ThisBegin, string Version, string Desc) : ClassModule(Name, Version, LMODULE::MACRO) {

	size_t ThisEnd = ThisBegin;
	MacroBegin = ThisBegin;
	Description = Desc;

	string S, SS;
	ID = Name;
	Grpnhru = 0;

	//Common::Message ("test 11", "test 11");
	//Common::Message ("test 11", std::to_string(ThisEnd));
	//Common::Message ("test 11", Global::MacroModulesList->Strings[ThisEnd]);	


	S = Global::MacroModulesList->at(ThisEnd).c_str();
	S = Common::trim(S);
	SS = S.substr(0, 3);

	while (
		!(SS == "end" &&
			(S.length() == 3 || S.find_first_of(" /") != string::npos)) &&
		Global::MacroModulesList->size() > ThisEnd
		)
	{
		ThisEnd++;
		S = Global::MacroModulesList->at(ThisEnd).c_str();
		S = Common::trim(S);
		SS = S.substr(0, 3);
	}

	//Common::Message ("test", "test 12");

	if (!DefCRHM::DefStringList) 
	{
		DefCRHM::DefStringList = new std::vector<std::string>();
	}

	//Common::Message ("test", "test 13");

	isGroup = false;
	isStruct = false;

	for (size_t ii = ThisBegin + 1; ii < ThisEnd - 1; ++ii) {

		//Common::Message ("test", "test 14");

		string::size_type Indx;
		Indx = Global::MacroModulesList->at(ii).find("//");  //Manishankar did this to resolve a warning.
		if (Indx != string::npos) 
		{
			string temp = Global::MacroModulesList->at(ii).substr(0, Indx - 1);
			temp = Common::trimright(temp);
			Common::tokenizeString(Add_Quote(temp), DefCRHM::DefStringList);
		}
		else
		{
			Common::tokenizeString(Add_Quote(Global::MacroModulesList->at(ii)), DefCRHM::DefStringList);
		}
			


		//Common::Message ("test", "test 15");

		long Pcnt = (long) DefCRHM::DefStringList->size();
		if (Pcnt < 1)
		{
			continue;
		}

		DefCRHM::DefStringList->at(0) = Common::trimleft(DefCRHM::DefStringList->at(0));

		if (!DefCRHM::DefStringList->at(0).compare("//") || DefCRHM::DefStringList->at(0).empty()) // comment
		{
			continue;
		}

		//Common::Message ("test", "test 16");

		if (DefCRHM::DefStringList->at(0).find("command") == 0) 
		{
			Begin = ii + 1; End = ThisEnd;
			DefCRHMPtr Call(new Defcommand(this));
			break;
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declgroup")) 
		{
			if (!isGroup) 
			{
				isGroup = true;
				GroupCnt = ++Global::GroupCntTrk;
				GrpStringList = new std::vector<std::pair<std::string, ClassModule *>>();

				if (DefCRHM::DefStringList->size() > 1 && (DefCRHM::DefStringList->at(1).find("//") == string::npos)) // ignore comments
				{
					Grpnhru = Strtolong(DefCRHM::DefStringList->at(1));
				}
				else
				{
					Grpnhru = nhru;
				}
			}
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declstruct")) {
			if (!isStruct) {
				isStruct = true;
				StructCnt = ++Global::StructCntTrk;
				GrpStringList = new std::vector<std::pair<std::string, ClassModule *>>();

				if (DefCRHM::DefStringList->size() > 1 && !DefCRHM::DefStringList->at(1).find("//")) // ignore comments
				{
					Grpnhru = Strtolong(DefCRHM::DefStringList->at(1));
				}
				else
				{
					Grpnhru = nhru;
				}
			}
		}
		else if (isGroup || isStruct) 
		{
			string S = DefCRHM::DefStringList->at(0);
			string V;
			string::size_type N = S.find("#"); // remove any variation
			if (N != string::npos) {
				V = S.substr(N, 2);
				S = S.substr(1, N - 1);
			}

			long jj = -1;
			if (Global::OldModuleName != NULL)
			{
				for (size_t i = 0; i < Global::OldModuleName->size(); i++)
				{
					if (Global::OldModuleName->at(i) == S)
					{
						jj = i;
					}
				}
			}
			if (jj == -1) // not changed
			{
				GrpStringList->push_back(std::pair<std::string, ClassModule *>(DefCRHM::DefStringList->at(0), NULL)); // original name
			}
			else 
			{
				GrpStringList->push_back(std::pair<std::string, ClassModule *>((Global::NewModuleName->at(jj) + V), NULL)); // new name
				string Message = "Converting module " + Global::OldModuleName->at(jj) + V + " to " + Global::NewModuleName->at(jj) + V + " in macro " + Name.c_str();
				LogMessage(Message.c_str());
			}
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declparam") && Pcnt >= 8) 
		{
			DefCRHMPtr Call(new Defdeclparam(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("decldiagparam") && Pcnt >= 8) 
		{
			DefCRHMPtr Call(new Defdeclparam(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declreadobs") && Pcnt >= 5) 
		{
			DefCRHMPtr Call(new Defdeclreadobs(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declobsfunc") && Pcnt >= 4) 
		{
			DefCRHMPtr Call(new Defdeclobsfunc(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declvar") && Pcnt >= 5) 
		{
			DefCRHMPtr Call(new Defdeclvar(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("decldiag") && Pcnt >= 5) 
		{
			DefCRHMPtr Call(new Defdecldiag(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declstatvar") && Pcnt >= 5) 
		{
			DefCRHMPtr Call(new Defdeclstatvar(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("decllocal") && Pcnt >= 5) 
		{
			DefCRHMPtr Call(new Defdecllocal(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declgetvar") && Pcnt >= 4) 
		{
			DefCRHMPtr Call(new Defdeclgetvar(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declputvar") && Pcnt >= 4) 
		{
			DefCRHMPtr Call(new Defdeclputvar(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declputparam") && Pcnt >= 4) 
		{
			DefCRHMPtr Call(new Defdeclputparam(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("declobs") && Pcnt >= 5) 
		{
			DefCRHMPtr Call(new Defdeclobs(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->at(0).compare("setpeer")) 
		{
			if (DefCRHM::DefStringList->size() > 2)
			{
				PeerVar = DefCRHM::DefStringList->at(1);
				PeerRank = Strtolong(DefCRHM::DefStringList->at(2));
			}
		}
		else 
		{
			Common::Message(string(string("function not recognised or too few parameters: ")
				+ "\"" + Global::MacroModulesList->at(ii) + "\""), "Macro Error");
		}
	}
}

ClassMacro::~ClassMacro() { // Can be Group or Struct or module

							// list only used by Groups and Structs
	Calls.clear(); // burrows down and deletes modules ???
};


long ClassMacro::declobs(string module, string name, TDim dimen, string help, string units, double** value) {
	MapVar::iterator itVar;
	ClassVar* newVar;
	ClassVar* thisVar;

	int cnt = getdim(dimen);

	Convert convert;
	convert.CheckUnitsString(Name, name, units);

	switch (Global::BuildFlag) {

	case TBuild::BUILD: {

		PairstrV Item2 = PairstrV(name, variation_set);
		PairstrI Item = PairstrI(module, Item2);
		Global::Mapdeclvar.insert(Item);
		Global::Mapdeclobs.insert(Item);

		return(-1);
	}

	case TBuild::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + name)) != Global::MapVars.end()) {
			thisVar = (*itVar).second;
			if (thisVar->dim < cnt) {
				thisVar->ReleaseM(); // releases everything
				thisVar->dim = cnt;
				if (thisVar->lay > 0) {
					thisVar->layvalues = new double* [thisVar->lay];
					for (int ii = 0; ii < thisVar->lay; ii++) thisVar->layvalues[ii] = new double[cnt];
				}
				thisVar->values = new double[cnt];
			}

			thisVar->dimen = dimen;
			thisVar->module = module;

			thisVar->DLLName = DLLName;
			thisVar->root = ID;

			return(-1);
		}

		newVar = new ClassVar("obs", name, cnt, 0, NULL);

		newVar->varType = TVar::Float;
		newVar->help = help;
		newVar->units = units;
		newVar->module = module;
		newVar->DLLName = DLLName;
		newVar->root = ID;

		newVar->values = new double[cnt];

		PairVar Item = PairVar("obs " + name, newVar);
		Global::MapVars.insert(Item);

		Item = PairVar(Name + " " + name, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case TBuild::INIT: {
		if ((itVar = Global::MapVars.find(Name + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if (newVar->FileData) {
				*value = NULL;
				return(-(newVar->cnt - 1));
			}
			else {
				*value = newVar->values;
				newVar->cnt = cnt; // required if previously an observation file
				LogError(CRHMException(" macro module '" + module + "' creating declared observation: '" + name + "'", TExcept::WARNING));
				return(newVar->cnt - 1);
			}
		}
		else {
			CRHMException Except("observation not found: " + module + " " + name, TExcept::TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
	default:
		break;
	}
	return 0; // Check
}

string Add_Quote(string s) { // changes " to ' eliminating duplicates
	string::size_type pos, here;
	for (pos = 0; pos < s.size(); ++pos) {
		here = s.find_first_of('\"', pos);
		if (here == string::npos)
			break; // no remaining quotes

		else {
			if (s[++here] != '\'') // handle first "
				s.insert(here, "'");

			here = s.find_first_of('\"', here);
			if (s[here - 1] != '\'') // handle second "
				s.insert(here, "'");

			pos = here + 1;
		}
	} // for loop
	return s;
}


void ClassMacro::RetrieveAllParameters(std::list<std::pair<std::string, ClassPar*>>* allParameters)
{

	std::vector<std::pair<std::string, ClassModule*>>* modulesVector = this->GrpStringList;

	for (
		std::vector<std::pair<std::string, ClassModule*>>::iterator modulesIt = modulesVector->begin();
		modulesIt != modulesVector->end();
		modulesIt++
		)
	{

		std::list<std::pair<std::string, ClassPar*>> parametersList = *modulesIt->second->getParametersList();

		for (
			std::list<std::pair<std::string, ClassPar*>>::iterator it = parametersList.begin();
			it != parametersList.end();
			it++
			)
		{
			allParameters->push_back(std::pair<std::string, ClassPar*>(it->first, it->second));
		}

	}

}