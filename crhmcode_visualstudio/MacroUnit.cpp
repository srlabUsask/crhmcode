// 10/04/12
//---------------------------------------------------------------------------

#include "stdafx.h"
#include "MacroUnit.h"
#include <map>

//---------------------------------------------------------------------------

//#include "CRHM_parse.h"
#include <boost/spirit/include/classic_exceptions.hpp>
//#include "CRHMmain.h"

extern double xLimit;

float Fday() { // used for variable DAY
	int year, month, day, h, m;
	Common::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);
	return day;
}

float Fmonth() { // used for variable MONTH
	int year, month, day, h, m;
	Common::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);
	return month;
}

float Fyear() { // used for variable YEAR
	int year, month, day, h, m;
	Common::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);
	return year;
}

float Fjulian() { // used for variable JULIAN

	//clock_t begintime = clock();///////////////////////////////////////////////////////////////////////////////////////

	float f = Julian("now");

	//float timediff = float(clock() - begintime) / CLOCKS_PER_SEC; /////////////////////////////////////////////////////
	//Common::addTime("julian", timediff, "d:/testfile2.txt");


	return f;
}

float Fgetstep() { // used for variable STEP
	return getstep();
}

float Fgetfirst() { // used for variable FIRST

	return (getstep() % Global::Freq == 1);
}

float Fgetlast() { // used for variable LAST

	return (getstep() % Global::Freq == 0);
}

float Fgetrand() { // used for variable STEP
	return (float)rand() / RAND_MAX;
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

			declparam("HRU_group", CRHM::NHRU, S, "1", "1e3", "group #", "()", &HRU_group);
		}

		if (isStruct) {
			string Choice = GrpStringList->CommaText();
			declparam("HRU_struct", CRHM::NHRU, "[1]", "1", Common::longtoStr(GrpStringList->Count), string("select using 1/2/3 ... module/group from '" + Choice + "'"), "()", &HRU_struct); // _group
		}

		Modules.clear();
		long Variation;

		for (int ii = 0; ii < GrpStringList->Count; ++ii) {
			string S = GrpStringList->Strings[ii];

			string::size_type idx = S.find("#");
			if (idx != string::npos) {
				Variation = pow(2, S[idx + 1] - char('1'));
				S = S.substr(0, idx);
			}
			else
				Variation = 0;

			int Indx = Global::AllModulesList->IndexOf(S);

			if (Indx == -1) {

				Common::Message(string("Module: '" + S + "' not found!"), "Macro Error");
				CRHMException Except(string(string("module: ") + S + " not found in " + Name).c_str(), TERMINATE);
				LogError(Except);
				throw Except;

				/*string s1 = "Module: '" + S + "' not found!";
				CString cstr(s1.c_str());
				AfxMessageBox(cstr);*/

				//continue;

			}

			ClassModule* Mod = (ClassModule*)Global::AllModulesList->Objects[Indx];

			//ModulePtr Test(Mod->klone());
			ModulePtr Test(Mod->klone(Name));

			std::weak_ptr<ClassModule> MG(Test);

			string S1 = typeid(*Mod).name();
			string S2 = typeid(*Test).name();

			if (S2 == "ClassMacro")
				Test->ID = S;
			else {
				Test->ID = typeid(*Test).name();
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
				AA[1] += log((*iterM)->variation) / log(2) + 1;
				SS += AA;
			}
			long jj = GrpStringList->IndexOf(SS); // find module entry
			GrpStringList->Objects[jj] = (TObject *)MPP; // save pointer to module
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

	ts->addTime("macro-function", 0, "d:/testfile2.txt");

	nhru = getdim(CRHM::NHRU); // transfers current # of HRU's to module

	if (isGroup || isStruct) {

		LogMessage(" ");

		string SS;
		if (isGroup)
			SS = "Group: '" + string(NameRoot + string("' ->"));
		else
			SS = "Struct: '" + string(NameRoot + string("' ->"));

		for (int ii = 0; ii < GrpStringList->Count; ++ii)
			SS += " " + GrpStringList->Strings[ii];

		LogMessage(SS.c_str());

		list<ModulePtr> ::iterator iter;
		iter = Modules.begin();
		while (iter != Modules.end()) {
			std::weak_ptr<ClassModule> MP((*iter));
			(*iter)->init();

			++iter;
		}

		if (StructCnt) // force into range of modules in the group
			for (hh = 0; hh < nhru; ++hh) {
				if (HRU_struct[hh] < 1)
					const_cast<long *>  (HRU_struct)[hh] = 1;
				if (HRU_struct[hh] > GrpStringList->Count)
					const_cast<long *>  (HRU_struct)[hh] = GrpStringList->Count;
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

	FP->second.kind = VarCHRM::CRHMint;
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

	FP->second.kind = VarCHRM::LOCAL;
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

	FP->second.kind = VarCHRM::LOCAL;
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

	FP->second.kind = VarCHRM::LOCAL;
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
	FP->second.kind = VarCHRM::LOCAL;
	FP->second.val = M_PI;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "PI";

	FP = vars.find("NO_DISPLAY");
	if (FP == vars.end()) {
		vars.insert(make_pair("NO_DISPLAY", VarCHRM()));
		FP = vars.find("NO_DISPLAY");
	}
	FP->second.kind = VarCHRM::LOCAL;
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
	FP->second.kind = VarCHRM::LOCAL;
	FP->second.val = Global::Freq;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "FREQ";

	FP = vars.find("RAND");
	if (FP == vars.end()) {
		vars.insert(make_pair("RAND", VarCHRM()));
		FP = vars.find("RAND");
	}
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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
	FP->second.kind = VarCHRM::FUNget;
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

	FP->second.kind = VarCHRM::FUNobs;
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

	FP->second.kind = VarCHRM::FUNobs;
	FP->second.val = 0;
	FP->second.Ihh = 0;
	FP->second.IndexMax = 0;
	FP->second.name = "WriteAheadObs";
	FP->second.Me = this;

	calculator calc(eval, vars, Operations, PCiter, LastVar, LastVas); //  Our parser

	Operations.clear();

	string str(Global::MacroModulesList->Strings[Begin]);

	for (int jj = Begin + 1; jj < End; ++jj) {
		string::size_type P = Global::MacroModulesList->Strings[jj].find("//");
		if (P != string::npos) {
			if (P - 1 > 0)
				str += " \n" + Global::MacroModulesList->Strings[jj].substr(1, P - 1);
		}
		else
			str += " \n" + Global::MacroModulesList->Strings[jj];
	}

	str = str + " \n"; //updated by Manishankar for solving the parsing problem.

	execbase::Index = 0;
	string::iterator first = str.begin();
	parse_info<string::iterator> info;

	
	do {


		clock_t begintime = clock();///////////////////////////////////////////////////////////////////////////////////////

		info = parse(first, str.end(), calc, space_p);

		float timediff = float(clock() - begintime) / CLOCKS_PER_SEC; /////////////////////////////////////////////////////
		ts->addTime("macro-parse", timediff, "d:/testfile2.txt");

		if (!info.hit || info.length == 0)
		{
			string err(first, str.end());
			CRHMException TExcept(string("cannot parse the command string: ") + err.c_str(), TERMINATE);
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

			if (Op->NameRoot == "Grow_Crop")
			{
				int a = 10;
			}

			//clock_t begintime = clock();///////////////////////////////////////////////////////////////////////////////////////

			(*iter)->pre_run();			
			(*iter)->run();

			//float timediff = float(clock() - begintime) / CLOCKS_PER_SEC; /////////////////////////////////////////////////////
			//ts->addTime(Op->DLLName+"-"+Op->Name+"-"+Op->NameRoot, timediff, "d:/testfile2.txt");
			//ts->addTime(Op->NameRoot, timediff, "d:/testfile2.txt");

			++iter;
		}

		return;
	}

	for (hh = 1; chkStructOff(hh, nhru + 1); ++hh) { // note offset range

		PCiter = Operations.begin();
		while (PCiter != Operations.end()) {
			execbase Op = (*(*PCiter));
			float X = (*(*PCiter))(); // run instruction
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
		if (pos->second.kind == VarCHRM::LOCAL) {
			vars.erase(pos++);
		}
		else {
			++pos;
		}
	}
}

ClassMacro::ClassMacro(string Name, int ThisBegin, string Version, string Desc) : ClassModule(Name, Version, CRHM::MACRO) {

	int ThisEnd = ThisBegin;
	MacroBegin = ThisBegin;
	Description = Desc;

	string S, SS;
	ID = Name;
	Grpnhru = 0;

	while (S = Common::trim(Global::MacroModulesList->Strings[ThisEnd]), SS = S.substr(0, 3),
		!(SS == "end" &&
		(S.length() == 3 || S.find_first_of(" /") != string::npos)) &&
		Global::MacroModulesList->Count > ThisEnd
		)

		++ThisEnd;


	if (!DefCRHM::DefStringList) {
		DefCRHM::DefStringList = new TStringList;
	}

	isGroup = false;
	isStruct = false;

	for (int ii = ThisBegin + 1; ii < ThisEnd - 1; ++ii) {

		string::size_type Indx;
		if (Indx = Global::MacroModulesList->Strings[ii].find("//") != string::npos) {
			string temp = Global::MacroModulesList->Strings[ii].substr(0, Indx - 1);
			temp = Common::trimright(temp);
			DefCRHM::DefStringList->DelimitedText(Add_Quote(temp));
		}
		else
			DefCRHM::DefStringList->DelimitedText(Add_Quote(Global::MacroModulesList->Strings[ii]));

		long Pcnt = DefCRHM::DefStringList->Count;
		if (Pcnt < 1)
			continue;

		DefCRHM::DefStringList->Strings[0] = Common::trimleft(DefCRHM::DefStringList->Strings[0]);

		if (!DefCRHM::DefStringList->Strings[0].compare("//") || DefCRHM::DefStringList->Strings[0].empty()) // comment
			continue;

		if (DefCRHM::DefStringList->Strings[0].find("command") == 0) {
			Begin = ii + 1; End = ThisEnd;
			DefCRHMPtr Call(new Defcommand(this));
			break;
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declgroup")) {
			if (!isGroup) {
				isGroup = true;
				GroupCnt = ++Global::GroupCntTrk;
				GrpStringList = new TStringList;

				if (DefCRHM::DefStringList->Count > 1 && (DefCRHM::DefStringList->Strings[1].find("//") != string::npos)) // ignore comments
					Grpnhru = Strtolong(DefCRHM::DefStringList->Strings[1]);
				else
					Grpnhru = nhru;
			}
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declstruct")) {
			if (!isStruct) {
				isStruct = true;
				StructCnt = ++Global::StructCntTrk;
				GrpStringList = new TStringList;

				if (DefCRHM::DefStringList->Count > 1 && !DefCRHM::DefStringList->Strings[1].find("//")) // ignore comments
					Grpnhru = Strtolong(DefCRHM::DefStringList->Strings[1]);
				else
					Grpnhru = nhru;
			}
		}

		else if (isGroup || isStruct) {
			string S = DefCRHM::DefStringList->Strings[0];
			string V;
			string::size_type N = S.find("#"); // remove any variation
			if (N != string::npos) {
				V = S.substr(N, 2);
				S = S.substr(1, N - 1);
			}

			long jj = -1;
			if (Global::OldModuleName != NULL)
			{
				jj = Global::OldModuleName->IndexOf(S); // find old name
			}
			if (jj == -1) // not changed
				GrpStringList->Add(DefCRHM::DefStringList->Strings[0]); // original name
			else {
				GrpStringList->Add(Global::NewModuleName->Strings[jj] + V); // new name
				string Message = "Converting module " + Global::OldModuleName->Strings[jj] + V + " to " + Global::NewModuleName->Strings[jj] + V + " in macro " + Name.c_str();
				LogMessage(Message.c_str());
			}
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declparam") && Pcnt >= 8) {
			DefCRHMPtr Call(new Defdeclparam(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("decldiagparam") && Pcnt >= 8) {
			DefCRHMPtr Call(new Defdeclparam(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declreadobs") && Pcnt >= 5) {
			DefCRHMPtr Call(new Defdeclreadobs(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declobsfunc") && Pcnt >= 4) {
			DefCRHMPtr Call(new Defdeclobsfunc(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declvar") && Pcnt >= 5) {
			DefCRHMPtr Call(new Defdeclvar(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("decldiag") && Pcnt >= 5) {
			DefCRHMPtr Call(new Defdecldiag(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declstatvar") && Pcnt >= 5) {
			DefCRHMPtr Call(new Defdeclstatvar(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("decllocal") && Pcnt >= 5) {
			DefCRHMPtr Call(new Defdecllocal(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declgetvar") && Pcnt >= 4) {
			DefCRHMPtr Call(new Defdeclgetvar(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declputvar") && Pcnt >= 4) {
			DefCRHMPtr Call(new Defdeclputvar(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declputparam") && Pcnt >= 4) {
			DefCRHMPtr Call(new Defdeclputparam(this));
			Calls.push_back(Call);
		}

		else if (!DefCRHM::DefStringList->Strings[0].compare("declobs") && Pcnt >= 5) {
			DefCRHMPtr Call(new Defdeclobs(this));
			Calls.push_back(Call);
		}
		else if (!DefCRHM::DefStringList->Strings[0].compare("setpeer")) {

			if (DefCRHM::DefStringList->Count > 2)
			{
				PeerVar = DefCRHM::DefStringList->Strings[1];
				PeerRank = Strtolong(DefCRHM::DefStringList->Strings[2]);
			}
		}
		else {
			Common::Message(string(string("function not recognised or too few parameters: ")
				+ "\"" + Global::MacroModulesList->Strings[ii] + "\""), "Macro Error");
		}
	}
}

ClassMacro::~ClassMacro() { // Can be Group or Struct or module

							// list only used by Groups and Structs
	Calls.clear(); // burrows down and deletes modules ???
};

TStringList *DefCRHM::DefStringList = NULL;

CRHM::TDim DefCRHM::getTDim(string D) {
	char table[][7] = {
		"BASIN",
		"ONE",
		"TWO",
		"THREE",
		"FOUR",
		"FIVE",
		"SIX",
		"SEVEN",
		"EIGHT",
		"NINE",
		"TEN",
		"ELEVEN",
		"TWELVE",
		"NHRU",
		"NOBS",
		"NLAY",
		"NDEF",
		"NFREQ",
		"NREB",
		"NDEFN",
		"DEFX"
	};

	for (long ii = 0; ii < 21; ++ii)
		if (D == table[ii])
			return (CRHM::TDim) ii;

	return (CRHM::TDim) - 1;
}

CRHM::TFun DefCRHM::getTFunc(string D) {
	char table[][9] = {
		"FOBS",
		"W_MJ",
		"MJ_W",
		"AVG",
		"MIN",
		"MAX",
		"DTOT",
		"POS",
		"TOT",
		"TOT_INT",
		"FIRST",
		"LAST"
	};

	for (long ii = 1; ii < 11; ++ii)
		if (D == table[ii])
			return (CRHM::TFun) ii;

	return (CRHM::TFun) - 1;
}

Defdeclparam::Defdeclparam(ClassMacro *Macro_) : DefCRHM(Macro_) {

	if (DefStringList->Strings[0] == "decldiagparam")
		visibility = CRHM::DIAGNOSTIC;
	else
		visibility = CRHM::USUAL;

	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Default = DefStringList->Strings[3];
	Min = DefStringList->Strings[4];
	Max = DefStringList->Strings[5];
	Description = DefStringList->Strings[6];
	Units = DefStringList->Strings[7];

	if (DefCRHM::DefStringList->Count > 8 && DefStringList->Strings[8] == "Int")
		Int = true;
	else
		Int = false;

	if (DefCRHM::DefStringList->Count > 9)
		nlay = Strtolong(DefStringList->Strings[9]);
}

Defdeclvar::Defdeclvar(ClassMacro *Macro_) : DefCRHM(Macro_) {
	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Description = DefStringList->Strings[3];
	Units = DefStringList->Strings[4];
	if (DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
		Int = true;
	else
		Int = false;
}

Defdecldiag::Defdecldiag(ClassMacro *Macro_) : DefCRHM(Macro_) {
	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Description = DefStringList->Strings[3];
	Units = DefStringList->Strings[4];
	if (DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
		Int = true;
	else
		Int = false;
}

Defdeclstatvar::Defdeclstatvar(ClassMacro *Macro_) : DefCRHM(Macro_) {
	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Description = DefStringList->Strings[3];
	Units = DefStringList->Strings[4];
	if (DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
		Int = true;
	else
		Int = false;
}

Defdecllocal::Defdecllocal(ClassMacro *Macro_) : DefCRHM(Macro_) {
	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Description = DefStringList->Strings[3];
	Units = DefStringList->Strings[4];
	if (DefCRHM::DefStringList->Count > 5 && DefStringList->Strings[5] == "Int")
		Int = true;
	else
		Int = false;
}

Defdeclobs::Defdeclobs(ClassMacro *Macro_) : DefCRHM(Macro_) {
	string S = DefStringList->Strings[1];
	string::size_type Pos = S.find("#");
	if (Pos == string::npos) //Updated by Manishankar on 2019-09-14. This previously was ------------- if (Pos != string::npos)
		S += "#"; // no # symbol
	else
		S = S.substr(0, Pos+1); // use just one # //Updated by Manishankar on 2019-09-14. This previously was ------------- S.substr(1, Pos)

	name = S;
	Dim = getTDim(DefStringList->Strings[2]);
	Description = DefStringList->Strings[3];
	Units = DefStringList->Strings[4];
}

Defdeclgetvar::Defdeclgetvar(ClassMacro *Macro_) : DefCRHM(Macro_) {
	module = DefStringList->Strings[1];
	name = DefStringList->Strings[2];
	Units = DefStringList->Strings[3];
}

Defdeclputvar::Defdeclputvar(ClassMacro *Macro_) : DefCRHM(Macro_) {
	module = DefStringList->Strings[1];
	name = DefStringList->Strings[2];
	Units = DefStringList->Strings[3];
}

Defdeclputparam::Defdeclputparam(ClassMacro *Macro_) : DefCRHM(Macro_) {
	module = DefStringList->Strings[1];
	name = DefStringList->Strings[2];
	Units = DefStringList->Strings[3];
}

Defdeclreadobs::Defdeclreadobs(ClassMacro *Macro_) : DefCRHM(Macro_) {
	name = DefStringList->Strings[1];
	Dim = getTDim(DefStringList->Strings[2]);
	Description = DefStringList->Strings[3];
	Units = DefStringList->Strings[4];

	if (DefCRHM::DefStringList->Count > 5)
		HRU_OBS_indexed = Strtolong(DefStringList->Strings[5]);
	else
		HRU_OBS_indexed = 0;
}

Defdeclobsfunc::Defdeclobsfunc(ClassMacro *Macro_) : DefCRHM(Macro_) {
	obs = DefStringList->Strings[1];
	name = DefStringList->Strings[2];
	typeFun = getTFunc(DefStringList->Strings[3]);
}

void Defdeclparam::CallDecl() {

	if (Int)
		Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_long_const, &fix2_long_const, nlay, visibility);
	else
		Macro->declparam(name, Dim, Default, Min, Max, Description, Units, &fix_const, &fix2_const, Macro->nhru, visibility);

	if (Global::BuildFlag == CRHM::INIT) {
		FP = Macro->vars.find(name);
		if (FP == Macro->vars.end()) {
			Macro->vars.insert(make_pair(name, VarCHRM()));
			FP = Macro->vars.find(name);
		}

		FP->second.name = name;
		FP->second.Ihh = 0;
		FP->second.IndexMax = Macro->nhru - 1;
		FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
		FP->second.Me = Macro;

		if (Int) {
			if (Dim == CRHM::NDEF || Dim == CRHM::NDEFN) {
				FP->second.kind = VarCHRM::CRHMint2;
				FP->second.ivalue2 = const_cast<long **> (fix2_long_const);
			}
			else {
				FP->second.kind = VarCHRM::CRHMint;
				FP->second.ivalue = const_cast<long *> (fix_long_const);
			}
		}
		else {
			if (Dim == CRHM::NDEF || Dim == CRHM::NDEFN) {
				FP->second.kind = VarCHRM::CRHM2;
				FP->second.value2 = const_cast<float **> (fix2_const);
			}
			else {
				FP->second.kind = VarCHRM::CRHM;
				FP->second.value = const_cast<float *> (fix_const);
			}
		}
	}
}

void Defdeclparam::CallInit(long nhru, long nlay) {
}

void Defdeclvar::CallDecl() {

	if (Int)
		Macro->declvar(name, Dim, Description, Units, &fix_long);
	else
		Macro->declvar(name, Dim, Description, Units, &fix, &fix2);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.Ill = 0;
	FP->second.IndexMax = Global::nhru - 1;
	FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
	FP->second.Me = Macro;

	if (Int) {
		FP->second.kind = VarCHRM::CRHMint;
		FP->second.ivalue = const_cast<long *> (fix_long);
	}
	else if (Dim == CRHM::NDEF || Dim == CRHM::NDEFN) {
		FP->second.value2 = fix2;
		FP->second.kind = VarCHRM::CRHM2;
	}
	else {
		FP->second.kind = VarCHRM::CRHM;
		FP->second.value = fix;
	}
}

void Defdecldiag::CallDecl() {

	if (Int)
		Macro->decldiag(name, Dim, Description, Units, &fix_long);
	else
		Macro->decldiag(name, Dim, Description, Units, &fix, &fix2);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.Ill = 0;
	FP->second.IndexMax = Global::nhru - 1;
	FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
	FP->second.Me = Macro;

	if (Int) {
		FP->second.kind = VarCHRM::CRHMint;
		FP->second.ivalue = const_cast<long *> (fix_long);
	}
	else if (Dim == CRHM::NDEF || Dim == CRHM::NDEFN) {
		FP->second.value2 = fix2;
		FP->second.kind = VarCHRM::CRHM2;
	}
	else {
		FP->second.kind = VarCHRM::CRHM;
		FP->second.value = fix;
	}
}

void Defdeclstatvar::CallDecl() {

	if (Int)
		Macro->declstatvar(name, Dim, Description, Units, &fix_long);
	else
		Macro->declstatvar(name, Dim, Description, Units, &fix);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.Ill = 0;
	FP->second.IndexMax = Global::nhru - 1;
	FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
	FP->second.Me = Macro;

	if (Int) {
		FP->second.kind = VarCHRM::CRHMint;
		FP->second.ivalue = const_cast<long *> (fix_long);
	}
	else if (Dim == CRHM::NDEF || Dim == CRHM::NDEFN) {
		FP->second.value2 = fix2;
		FP->second.kind = VarCHRM::CRHM2;
	}
	else {
		FP->second.kind = VarCHRM::CRHM;
		FP->second.value = fix;
	}
}

void Defdecllocal::CallDecl() {

	if (Int)
		Macro->decllocal(name, Dim, Description, Units, &fix_long);
	else
		Macro->decllocal(name, Dim, Description, Units, &fix);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.Ill = 0;
	FP->second.IndexMax = Global::nhru - 1;
	FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
	FP->second.Me = Macro;

	if (Int) {
		FP->second.kind = VarCHRM::CRHMint;
		FP->second.ivalue = const_cast<long *> (fix_long);
	}
	else if (Dim == CRHM::NDEF || Dim == CRHM::NDEFN) {
		FP->second.value2 = fix2;
		FP->second.kind = VarCHRM::CRHM2;
	}
	else {
		FP->second.kind = VarCHRM::CRHM;
		FP->second.value = fix;
	}
}

void Defdeclgetvar::CallDecl() {

	MapVar::iterator itVar;
	ClassVar *thisVar = NULL;
	long GetUnit;

	GetUnit = Macro->FindWildVarFloat(name, thisVar); // chnaged folowwing 2018 , false, true); // just find name

	if (thisVar != NULL && thisVar->varType == CRHM::Int)
		Int = true;
	else
		Int = false;

	if (Int)
		Macro->declgetvar(module, name, Units, &fix_long_const, &fix2_long_const);
	else
		Macro->declgetvar(module, name, Units, &fix_const, &fix2_const);

	if (Global::BuildFlag == CRHM::INIT) { // moved down 06/20/11

		FP = Macro->vars.find(name);
		if (FP == Macro->vars.end()) {
			Macro->vars.insert(make_pair(name, VarCHRM()));
			FP = Macro->vars.find(name);
		}

		FP->second.name = name;
		FP->second.Ihh = 0;
		FP->second.Ill = 0;
		FP->second.IndexMax = Macro->nhru - 1;
		FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
		FP->second.Me = Macro;

		if (Int) {
			if (thisVar->varType == CRHM::NDEF || thisVar->varType == CRHM::NDEFN) {
				FP->second.kind = VarCHRM::CRHMint2;
				FP->second.ivalue2 = const_cast<long **> (fix2_long_const);
			}
			else {
				FP->second.kind = VarCHRM::CRHMint;
				FP->second.ivalue = const_cast<long *> (fix_long_const);
			}
		}
		else {
			if (thisVar->varType == CRHM::NDEF || thisVar->varType == CRHM::NDEFN) {
				FP->second.kind = VarCHRM::CRHM2;
				FP->second.value2 = const_cast<float **> (fix2_const);
			}
			else {
				FP->second.kind = VarCHRM::CRHM;
				FP->second.value = const_cast<float *> (fix_const);
			}
		}
	}
}

void Defdeclputvar::CallDecl() {
	MapVar::iterator itVar;
	ClassVar *thisVar = NULL;
	long GetUnit;

	GetUnit = Macro->FindWildVarFloat(name, thisVar);//, false, true); // just find name

	if (thisVar != NULL && thisVar->varType == CRHM::Int)
		Int = true;
	else
		Int = false;

	if (Int)
		Macro->declputvar(module, name, Units, &fix_long);
	else
		Macro->declputvar(module, name, Units, &fix, &fix2);

	if (Global::BuildFlag == CRHM::INIT) { // moved down 06/20/11

		FP = Macro->vars.find(name);
		if (FP == Macro->vars.end()) {
			Macro->vars.insert(make_pair(name, VarCHRM()));
			FP = Macro->vars.find(name);
		}

		FP->second.name = name;
		FP->second.Ihh = 0;
		FP->second.Ill = 0;
		FP->second.IndexMax = Macro->nhru - 1;
		FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
		FP->second.Me = Macro;

		if (Int) {
			FP->second.kind = VarCHRM::CRHMint;
			FP->second.ivalue = const_cast<long *> (fix_long);
		}
		else if (thisVar->varType == CRHM::NDEF || thisVar->varType == CRHM::NDEFN) {
			FP->second.kind = VarCHRM::CRHM2;
			FP->second.value2 = const_cast<float **> (fix2);
		}
		else {
			FP->second.kind = VarCHRM::CRHM;
			FP->second.value = const_cast<float *> (fix);
		}
	}
}

void Defdeclputparam::CallDecl() {
	MapPar::iterator itPar;
	ClassPar *thisPar = NULL;
	int GetUnit;

	GetUnit = Macro->FindWildParFloat(name, thisPar, false, false); // name

	if (thisPar != NULL && thisPar->varType == CRHM::Int)
		Int = true;
	else
		Int = false;

	if (Int)
		Macro->declputparam(module, name, Units, &fix_long);
	else
		Macro->declputparam(module, name, Units, &fix, &fix2);

	if (Global::BuildFlag == CRHM::INIT) { // moved down 06/20/11

		FP = Macro->vars.find(name);
		if (FP == Macro->vars.end()) {
			Macro->vars.insert(make_pair(name, VarCHRM()));
			FP = Macro->vars.find(name);
		}

		FP->second.name = name;
		FP->second.Ihh = 0;
		FP->second.Ill = 0;
		FP->second.IndexMax = Macro->nhru - 1;
		FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
		FP->second.Me = Macro;

		if (Int) {
			FP->second.kind = VarCHRM::CRHMint;
			FP->second.ivalue = const_cast<long *> (fix_long);
		}
		else if (thisPar->varType == CRHM::NDEF || thisPar->varType == CRHM::NDEFN) {
			FP->second.kind = VarCHRM::CRHM2;
			FP->second.value2 = const_cast<float **> (fix2);
		}
		else {
			FP->second.kind = VarCHRM::CRHM;
			FP->second.value = const_cast<float *> (fix);
		}
	}
}

void Defdeclobs::CallDecl() {

	long cnt = Macro->declobs(Macro->Name, name, Dim, Description, Units, &fix);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	if (fix)
		FP->second.kind = VarCHRM::CRHM;
	else
		FP->second.kind = VarCHRM::NOP;

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	FP->second.value = fix;
	FP->second.Me = Macro;
}

void Defdeclobs::CallInit(long nhru, long nlay) {
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}

void Defdeclvar::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}

void Defdecldiag::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}

void Defdeclstatvar::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}

void Defdecllocal::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}

void Defdeclgetvar::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	//  for(int hh = 0; hh <= FP->second.IndexMax; ++hh){
	//    FP->second.IndexMaxLay = nlay-1;
	//  }
}

void Defdeclputvar::CallInit(long nhru, long nlay) { // check
	FP->second.IndexMax = nhru - 1;
}

void Defdeclputparam::CallInit(long nhru, long nlay) { // check
	FP->second.IndexMax = nhru - 1;
}

void Defdeclreadobs::CallDecl() {

	long cnt = Macro->declreadobs(name, Dim, Description, Units, &fix_const, HRU_OBS_indexed);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.kind = VarCHRM::CRHM;
	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	FP->second.value = const_cast<float *> (fix_const);
	FP->second.Me = Macro;
}

void Defdeclobsfunc::CallDecl() {

	long cnt = Macro->declobsfunc(obs, name, &fix, typeFun);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.kind = VarCHRM::CRHM;
	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	//  FP->second.value = const_cast<float *> (fix);
	FP->second.value = fix;
	FP->second.Me = Macro;
}

//---------------------------------------------------------------------------
long ClassMacro::declobs(string module, string name, CRHM::TDim dimen, string help, string units, float **value) {
	MapVar::iterator itVar;
	ClassVar *newVar;
	ClassVar *thisVar;

	int cnt = getdim(dimen);

	Convert convert; 
	convert.CheckUnitsString(Name, name, units);

	switch (Global::BuildFlag) {

	case CRHM::BUILD: {

		PairstrV Item2 = PairstrV(name, variation_set);
		PairstrI Item = PairstrI(module, Item2);
		Global::Mapdeclvar.insert(Item);
		Global::Mapdeclobs.insert(Item);

		return(-1);
	}

	case CRHM::DECL: {

		if ((itVar = Global::MapVars.find(Name + " " + name)) != Global::MapVars.end()) {
			thisVar = (*itVar).second;
			if (thisVar->dim < cnt) {
				thisVar->ReleaseM(); // releases everything
				thisVar->dim = cnt;
				if (thisVar->lay > 0) {
					thisVar->layvalues = new float *[thisVar->lay];
					for (int ii = 0; ii < thisVar->lay; ii++) thisVar->layvalues[ii] = new float[cnt];
				}
				thisVar->values = new float[cnt];
			}

			thisVar->dimen = dimen;
			thisVar->module = module;

			thisVar->DLLName = DLLName;
			thisVar->root = ID;

			return(-1);
		}

		newVar = new ClassVar("obs", name, cnt, 0, NULL);

		newVar->varType = CRHM::Float;
		newVar->help = help;
		newVar->units = units;
		newVar->module = module;
		newVar->DLLName = DLLName;
		newVar->root = ID;

		newVar->values = new float[cnt];

		PairVar Item = PairVar("obs " + name, newVar);
		Global::MapVars.insert(Item);

		Item = PairVar(Name + " " + name, newVar);
		Global::MapVars.insert(Item);

		return(-1);
	}

	case CRHM::INIT: {
		if ((itVar = Global::MapVars.find(Name + " " + name)) != Global::MapVars.end()) {
			newVar = (*itVar).second;
			if (newVar->FileData) {
				*value = NULL;
				return(-(newVar->cnt - 1));
			}
			else {
				*value = newVar->values;
				newVar->cnt = cnt; // required if previously an observation file
				LogError(CRHMException(" macro module '" + module + "' creating declared observation: '" + name + "'", WARNING));
				return(newVar->cnt - 1);
			}
		}
		else {
			CRHMException Except("observation not found: " + module + " " + name, TERMINATE);
			LogError(Except);
			throw Except;
		}
	}
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
