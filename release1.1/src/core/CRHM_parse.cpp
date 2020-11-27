

//  08/08/12
//---------------------------------------------------------------------------

#if defined(_WIN32)
#include "stdafx.h"
#endif

#include <stdio.h>
//#include <tchar.h>


#include "CRHM_parse.h"

//---------------------------------------------------------------------------

using namespace std;

VarCHRM::~VarCHRM() {
	if (Me == NULL && (kind == TV::CRHM || kind == TV::CRHM2)) {
		switch (kind) {
		case TV::CRHM:
			delete[] value;
			value = NULL;
			break;
		case TV::CRHM2:
			for (int ii = 0; ii <= IndexMaxLay; ii++)
				delete[] value2[ii];
			delete[] value2;
			value2 = NULL;
			break;
		default:
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

void VarCHRM::put(double val_) {

	switch (kind) {
	case TV::LOCAL:
		val = val_;
		break;
	case TV::CRHM:
		value[min<long>(Ihh, IndexMax)] = val_;
		break;
	case TV::CRHM2:
		value2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)] = val_;
		break;
	case TV::CRHMint:
		ivalue[min<long>(Ihh, IndexMax)] = (long)val_;
		break;
	case TV::CRHMint2:
		ivalue2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)] = (long)val_;
		break;
	case TV::FUNobs:
		if (name == "ReadAheadObs")
			val = !Me->ReadAheadObsMacro((long) val_);
		else
			val = !Me->WriteAheadObsMacro((long) val_);
		break;
	default:
		break;
	}
	// NOP falls through
}

double VarCHRM::get(void) {
	switch (kind) {
	case TV::LOCAL:
		return val;
	case TV::CRHM:
		return value[min<long>(Ihh, IndexMax)];
	case TV::CRHM2:
		return value2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)];
	case TV::CRHMint:
		return ivalue[min<long>(Ihh, IndexMax)];
	case TV::CRHMint2:
		return ivalue2[min<long>(Ill, IndexMaxLay)][min<long>(Ihh, IndexMax)];
	case TV::FUNget:
		return (*pget)();
	case TV::FUNobs:
		return (val);
	default:
		break;
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
