#pragma once

#ifndef EXECVASSIGN
#define EXECVASSIGN

#include "execbase.h"

class execVassign : public execbase {
public:
	execVassign(stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
		: execbase(eval_, oper_, "Vassign"), LastVas(LastVas_) {};
	execVassign(const execVassign& Cl) : execbase(Cl), LastVas(Cl.LastVas) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const {

		Lvar = LastVas.top();
		LastVas.pop();

		Execbase Sp(new execVassign(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double X = eval.top();
		Lvar->put(X);
		eval.pop();
		int Cnt = eval.size();
		return X;
	}
	stack<VarCHRM*>& LastVas;
};

#endif // !EXECVASSIGN
