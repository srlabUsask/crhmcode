#pragma once

#ifndef EXECVSET
#define EXECVSET

#include "execbase.h"

class execVset : public execbase {
public:
	execVset(symtab_t& vars_, stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
		: execbase(eval_, oper_, "Vset"), vars(vars_), LastVas(LastVas_) {};
	execVset(const execVset& Cl) : execbase(Cl), vars(Cl.vars), LastVas(Cl.LastVas) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const {

		string S(b, e);
		int ii = S.find_first_of("[ =\t");

		if (ii > 0)
			S.erase(ii);

		symtab_t::iterator FP = vars.find(S);
		if (FP == vars.end()) {
			string SS("macro code - writing to an undefined variable: \"" + S + "\".  Suggestion - declared observations always end with a # symbol");
			CRHMException Except(SS, TExcept::TERMINATE);
			throw CRHMException(Except);
		}

		Lvar = &FP->second;
		LastVas.push(&FP->second);

		Execbase Sp(new execVset(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		Lvar->Ihh = 0;
		return -888;
	}

private:
	symtab_t& vars;
	stack<VarCHRM*>& LastVas;
};

#endif // !EXECVSET
