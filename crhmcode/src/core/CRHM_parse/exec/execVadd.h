#pragma once

#ifndef EXECVADD
#define EXECVADD

#include "execbase.h"

struct execVadd : public execbase { // pushed on to stack!
	execVadd(symtab_t& vars_, stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "Vadd"), vars(vars_), LastVar(LastVar_) {}
	execVadd(const execVadd& Cl) : execbase(Cl), vars(Cl.vars), LastVar(Cl.LastVar) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const {

		string S(b, e);

		symtab_t::iterator FP = vars.find(S);
		if (FP != vars.end()) {
			vars.erase(FP);
		}

		vars.insert(make_pair(S, VarCHRM()));
		FP = vars.find(S);
		FP->second.name = S;
		FP->second.Ihh = 0;

		Lvar = &FP->second;
		LastVar.push(&FP->second);

		Execbase Sp(new execVadd(*this));
		oper.push_back(Sp);
	}

	double operator()() const { // used
		if (!LastVar.empty()) // handles the simple case
			LastVar.pop();

		int Cnt = eval.size();
		return -555;
	}

private:
	symtab_t& vars;
	stack<VarCHRM*>& LastVar;
};

#endif // !EXECVADD
