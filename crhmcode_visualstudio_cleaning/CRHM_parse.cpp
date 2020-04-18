//  08/08/12
//---------------------------------------------------------------------------
#include "stdafx.h"
#include "CRHM_parse.h"

//---------------------------------------------------------------------------

using namespace std;

VarCHRM::~VarCHRM() {
	if (Me == NULL && (kind == CRHM || kind == CRHM2)) {
		switch (kind) {
		case CRHM:
			delete[] value;
			value = NULL;
			break;
		case CRHM2:
			for (int ii = 0; ii <= IndexMaxLay; ii++)
				delete[] value2[ii];
			delete[] value2;
			value2 = NULL;
			break;
		}
	}
};

VarCHRM::VarCHRM(const VarCHRM & Cl) {
	kind = Cl.kind;
	val = Cl.val;
	value = Cl.value;
	ivalue = Cl.ivalue;
	value2 = Cl.value2;
	ivalue2 = Cl.ivalue2;
	Ihh = Cl.Ihh;
	Ill = Cl.Ill;
	IndexMax = Cl.IndexMax;
	IndexMaxLay = Cl.IndexMaxLay;
	name = Cl.name;
	Me = Cl.Me;
}

VarCHRM & VarCHRM::operator=(const VarCHRM & Cl) {

	if (this == &Cl) return *this;

	kind = Cl.kind;
	val = Cl.val;
	value = Cl.value;
	ivalue = Cl.ivalue;
	value2 = Cl.value2;
	ivalue2 = Cl.ivalue2;
	Ihh = Cl.Ihh;
	Ill = Cl.Ill;
	IndexMax = Cl.IndexMax;
	IndexMaxLay = Cl.IndexMaxLay;
	name = Cl.name;
	return *this;
}

void VarCHRM::put(float val_) {

	switch (kind) {
	case LOCAL:
		val = val_;
		break;
	case CRHM:
		value[min<long>(Ihh, IndexMax)] = val_;
		break;
	case CRHM2:
		value2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)] = val_;
		break;
	case CRHMint:
		ivalue[min<long>(Ihh, IndexMax)] = (int)val_;
		break;
	case CRHMint2:
		ivalue2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)] = (int)val_;
		break;
	case FUNobs:
		if (name == "ReadAheadObs")
			val = !Me->ReadAheadObsMacro(val_);
		else
			val = !Me->WriteAheadObsMacro(val_);
		break;
	}
	// NOP falls through
}

float VarCHRM::get(void) {
	switch (kind) {
	case LOCAL:
		return val;
	case CRHM:
		return value[min<long>(Ihh, IndexMax)];
	case CRHM2:
		return value2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)];
	case CRHMint:
		return ivalue[min<long>(Ihh, IndexMax)];
	case CRHMint2:
		return ivalue2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)];
	case FUNget:
		return (*pget)();
	case FUNobs:
		return (val);
	}
	return -999;
}

long    execbase::Index;

execbase::execbase(const execbase & Cl) : eval(Cl.eval), oper(Cl.oper) {

	s = Cl.s;
	Lvar = Cl.Lvar;

	OurIndex = Cl.OurIndex;
	OurOrder = Cl.OurOrder;
}

execbase & execbase::operator=(const execbase & Cl) {

	if (this == &Cl) return *this;

	eval = Cl.eval;
	oper = Cl.oper;

	s = Cl.s;
	Lvar = Cl.Lvar;

	OurIndex = Cl.OurIndex;
	OurOrder = Cl.OurOrder;
	return *this;
}