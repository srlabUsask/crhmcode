#include "Defdeclobs.h"

Defdeclobs::Defdeclobs(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	string S = DefStringList->operator[](1);
	string::size_type Pos = S.find("#");
	if (Pos == string::npos) //Updated by Manishankar on 2019-09-14. This previously was ------------- if (Pos != string::npos)
		S += "#"; // no # symbol
	else
		S = S.substr(0, Pos + 1); // use just one # //Updated by Manishankar on 2019-09-14. This previously was ------------- S.substr(1, Pos)

	name = S;
	Dim = getTDim(DefStringList->operator[](2));
	Description = DefStringList->operator[](3);
	Units = DefStringList->operator[](4);
}

void Defdeclobs::CallDecl() {

	long cnt = Macro->declobs(Macro->Name, name, Dim, Description, Units, &fix);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	if (fix)
		FP->second.kind = TV::CRHM;
	else
		FP->second.kind = TV::NOP;

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