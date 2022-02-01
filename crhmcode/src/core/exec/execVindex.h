#pragma once

#ifndef EXECVINDEX
#define EXECVINDEX

#include "execbase.h"

struct execVindex : public execbase { // used by execVset
	execVindex(stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVas_)
		: execbase(eval_, oper_, "Vindex"), LastVas(LastVas_) {}
	execVindex(const execVindex& Cl) : execbase(Cl), LastVas(Cl.LastVas) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const
	{
		string S(b, e);

		string::size_type eq = S.find_last_not_of("= \t");

		Lvar = LastVas.top();

		Execbase Sp(new execVindex(*this));
		oper.push_back(Sp);

	}

	double operator()() const {
		int T = eval.size();
		switch (T) {
		case 2:
			Lvar->Ill = (int)eval.top() - 1;  // set by re-arrange in execbase
			if (Lvar->Ill < 0) Lvar->Ill = 0;
			eval.pop(); // remove element index
		case 1:
			Lvar->Ihh = (int)eval.top() - 1;  // set by re-arrange in execbase
			if (Lvar->Ihh < 0) Lvar->Ihh = 0;
			eval.pop(); // remove element index
			break;
		default:
			Lvar->Ihh = 0;
		}
		return Lvar->Ihh;
	}
private:
	stack<VarCHRM*>& LastVas;
};

#endif // !EXECVINDEX
