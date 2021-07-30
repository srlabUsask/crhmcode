#include "Defdeclputvar.h"

Defdeclputvar::Defdeclputvar(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	module = DefStringList->operator[](1);
	name = DefStringList->operator[](2);
	Units = DefStringList->operator[](3);
}

void Defdeclputvar::CallDecl() {
	MapVar::iterator itVar;
	ClassVar* thisVar = NULL;
	long GetUnit;

	GetUnit = Macro->FindWildVarFloat(name, thisVar);//, false, true); // just find name

	//if (thisVar != NULL && thisVar->varType == CRHM::Int) //Manishankar did this to fix output differences
	if (Global::thisVar != NULL && ((ClassVar*)Global::thisVar)->varType == TVar::Int)
		Int = true;
	else
		Int = false;

	if (Int)
		Macro->declputvar(module, name, Units, &fix_long);
	else
		Macro->declputvar(module, name, Units, &fix, &fix2);

	if (Global::BuildFlag == TBuild::INIT) { // moved down 06/20/11

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
			FP->second.kind = TV::CRHMint;
			FP->second.ivalue = const_cast<long*> (fix_long);
		}
		//else if (thisVar->varType == CRHM::NDEF || thisVar->varType == CRHM::NDEFN) { //Manishankar did this to fix output differences.
		else if (Global::thisVar != NULL && (((ClassVar*)Global::thisVar)->dimen == TDim::NDEF || ((ClassVar*)Global::thisVar)->dimen == TDim::NDEFN)) {
			FP->second.kind = TV::CRHM2;
			FP->second.value2 = const_cast<double**> (fix2);
		}
		else {
			FP->second.kind = TV::CRHM;
			FP->second.value = const_cast<double*> (fix);
		}
	}
}

void Defdeclputvar::CallInit(long nhru, long nlay) { // check
	FP->second.IndexMax = nhru - 1;
}