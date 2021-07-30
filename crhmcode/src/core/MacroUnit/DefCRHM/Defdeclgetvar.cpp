#include "Defdeclgetvar.h"


Defdeclgetvar::Defdeclgetvar(ClassMacro* Macro_) : DefCRHM(Macro_) 
{
	module = DefStringList->operator[](1);
	name = DefStringList->operator[](2);
	Units = DefStringList->operator[](3);
}


void Defdeclgetvar::CallDecl() {

	MapVar::iterator itVar;
	ClassVar* thisVar = NULL;
	long GetUnit;

	GetUnit = Macro->FindWildVarFloat(name, thisVar); // chnaged folowwing 2018 , false, true); // just find name


	//if (thisVar != NULL && thisVar->varType == CRHM::Int) //Manishankar did this to fix output differences
	if (Global::thisVar != NULL && ((ClassVar*)Global::thisVar)->varType == TVar::Int)

		Int = true;
	else
		Int = false;

	if (Int)
		Macro->declgetvar(module, name, Units, &fix_long_const, &fix2_long_const);
	else
		Macro->declgetvar(module, name, Units, &fix_const, &fix2_const);

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
			//if (thisVar->varType == CRHM::NDEF || thisVar->varType == CRHM::NDEFN) { //Manishankar did this to fix output differences
			if (((ClassVar*)Global::thisVar)->dimen == TDim::NDEF || ((ClassVar*)Global::thisVar)->dimen == TDim::NDEFN) {
				FP->second.kind = TV::CRHMint2;
				FP->second.ivalue2 = const_cast<long**> (fix2_long_const);
			}
			else {
				FP->second.kind = TV::CRHMint;
				FP->second.ivalue = const_cast<long*> (fix_long_const);
			}
		}
		else {
			//if (thisVar->varType == CRHM::NDEF || thisVar->varType == CRHM::NDEFN) { //Manishankar did this to fix output differences
			if (Global::thisVar != NULL && (((ClassVar*)Global::thisVar)->dimen == TDim::NDEF || ((ClassVar*)Global::thisVar)->dimen == TDim::NDEFN)) {
				FP->second.kind = TV::CRHM2;
				FP->second.value2 = const_cast<double**> (fix2_const);
			}
			else {
				FP->second.kind = TV::CRHM;
				FP->second.value = const_cast<double*> (fix_const);
			}
		}
	}
}


void Defdeclgetvar::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	//  for(int hh = 0; hh <= FP->second.IndexMax; ++hh){
	//    FP->second.IndexMaxLay = nlay-1;
	//  }
}