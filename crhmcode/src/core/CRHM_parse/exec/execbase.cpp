#include "execbase.h"

long    execbase::Index;

execbase::execbase(const execbase& Cl) : eval(Cl.eval), oper(Cl.oper) {

	s = Cl.s;
	Lvar = Cl.Lvar;

	OurIndex = Cl.OurIndex;
	OurOrder = Cl.OurOrder;
}

execbase& execbase::operator=(const execbase& Cl) {

	if (this == &Cl) return *this;

	eval = Cl.eval;
	oper = Cl.oper;

	s = Cl.s;
	Lvar = Cl.Lvar;

	OurIndex = Cl.OurIndex;
	OurOrder = Cl.OurOrder;
	return *this;
}