#include "Defdeclreadobs.h"

Defdeclreadobs::Defdeclreadobs(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	name = DefStringList->operator[](1);
	Dim = getTDim(DefStringList->operator[](2));
	Description = DefStringList->operator[](3);
	Units = DefStringList->operator[](4);

	if (DefCRHM::DefStringList->size() > 5)
	{
		HRU_OBS_indexed = Strtolong(DefStringList->operator[](5));
	}
	else
	{
		HRU_OBS_indexed = 0;
	}
}

void Defdeclreadobs::CallDecl() {

	long cnt = Macro->declreadobs(name, Dim, Description, Units, &fix_const, HRU_OBS_indexed);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.kind = TV::CRHM;
	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	FP->second.value = const_cast<double*> (fix_const);
	FP->second.Me = Macro;
}