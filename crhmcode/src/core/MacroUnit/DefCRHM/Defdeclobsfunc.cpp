#include "Defdeclobsfunc.h"

Defdeclobsfunc::Defdeclobsfunc(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	obs = DefStringList->operator[](1);
	name = DefStringList->operator[](2);
	typeFun = getTFunc(DefStringList->operator[](3));
}



void Defdeclobsfunc::CallDecl() {

	long cnt = Macro->declobsfunc(obs, name, &fix, typeFun);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.kind = TV::CRHM;
	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.IndexMax = cnt;
	//  FP->second.value = const_cast<double *> (fix);
	FP->second.value = fix;
	FP->second.Me = Macro;
}