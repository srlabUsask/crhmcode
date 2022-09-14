#pragma once

#ifndef EXECVGET
#define EXECVGET

#include "execbase.h"

class execVget : public execbase {
public:
	execVget(symtab_t& vars_, stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) :
		execbase(eval_, oper_, "Vget"), vars(vars_), LastVar(LastVar_) {};
	execVget(const execVget& Cl) : execbase(Cl), vars(Cl.vars), LastVar(Cl.LastVar) {}; // copy constructor
	execVget& operator=(const execVget& Cl); //  assigment operator

	void operator()(const string::iterator b, const string::iterator e) const {

		string S(b, e);
		symtab_t::iterator FP = vars.find(S);

		if (FP == vars.end()) {
			string SS("macro code - reading from an undefined variable: " + S);

			for (const auto& kv : vars) {
 				std::cout << kv.first << std::endl;
			}

			CRHMException Except(SS, TExcept::TERMINATE);
			throw CRHMException(Except);
		}

		Lvar = &FP->second;

		string SS(e, e + 1); // !!! wrong ???							 
		if (SS != " ")
		{
			string::size_type eq = SS.find_first_not_of(" \t\n");
			if (SS[eq] == '[')
				LastVar.push(&FP->second);
		}

		Execbase Sp(new execVget(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		Lvar->Ihh = 0;

		double X = Lvar->get(); // in case there is no array element [n]
		eval.push(X);
		return X;
	}

private:
	symtab_t& vars;
	stack<VarCHRM*>& LastVar;
};

#endif // !EXECVGET
