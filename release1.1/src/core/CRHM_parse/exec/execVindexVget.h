#pragma once

#ifndef EXECVINDEXVGET
#define EXECVINDEXVGET

#include "execbase.h"

struct execVindexVget : public execbase {
	execVindexVget(stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "VindexVget"), LastVar(LastVar_), Indices(0), Idle(true) {}
	execVindexVget(const execVindexVget& Cl) : execbase(Cl), LastVar(Cl.LastVar), Indices(Cl.Indices), Idle(Cl.Idle) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const
	{
		if (Lvar != LastVar.top() || Idle) { // reset for new variable
			Indices = 0;
			Idle = false;
			Lvar = LastVar.top();
		}

		++Indices;

		if (e[0] != '[') {
			LastVar.pop();
			Idle = true;

			Execbase Sp(new execVindexVget(*this));
			oper.push_back(Sp);
		}
	}

	double operator()() const {
		switch (Indices) {
		case 2:
			Lvar->Ill = (int)eval.top() - 1;  // set by re-arrange in execbase
			if (Lvar->Ill < 0) Lvar->Ill = 0;
			eval.pop(); // remove element index
		case 1:
			Lvar->Ihh = (int)eval.top() - 1;  // set by re-arrange in execbase
			if (Lvar->Ihh < 0) Lvar->Ihh = 0;
			eval.pop(); // remove element index
		default: break;
		}

		eval.pop(); // remove variable not indexed

		double X = Lvar->get();
		eval.push(X); // push indexed variable to stack
		int Cnt = eval.size();
		return X;
	}

private:
	stack<VarCHRM*>& LastVar; // could be redundant
	mutable long Indices; // handles 1D & 2D
	mutable bool Idle; // Flags all variable dimensions handled. Required when variable has consecutive references
};

#endif // !EXECVINDEXVGET
