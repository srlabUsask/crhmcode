#pragma once

#ifndef EXECVADDN
#define EXECVADDN

#include "execbase.h" 

struct execVaddN : public execbase { // pushed on to stack!
	execVaddN(stack<double>& eval_, list<Execbase>& oper_, stack<VarCHRM*>& LastVar_) : execbase(eval_, oper_, "VaddN"), LastVar(LastVar_), Indices(0) {}
	execVaddN(const execVaddN& Cl) : execbase(Cl), LastVar(Cl.LastVar), Indices(Cl.Indices) {}; // copy constructor

	void operator()(const string::iterator b, const string::iterator e) const {

		string S(b, e);

		if (Lvar != LastVar.top()) { // reset for new variable
			Indices = 0;
			Lvar = LastVar.top();
		}

		++Indices;
		if (Indices == 2) {
			Lvar->IndexMaxLay = -1;
			LastVar.pop();
		}

		Execbase Sp(new execVaddN(*this));
		oper.push_back(Sp);
	}

	double operator()() const { // used
		switch (Indices) {
		case 2: // lay
			Lvar->IndexMaxLay = (int)eval.top();  // set by re-arrange in execbase
			if (Lvar->IndexMaxLay < 1) Lvar->IndexMaxLay = 1;
			eval.pop(); // remove element index

			Lvar->value2 = new double* [Lvar->IndexMaxLay];
			for (int ii = 0; ii < Lvar->IndexMaxLay; ii++)
				Lvar->value2[ii] = new double[Lvar->IndexMax];

			--Lvar->IndexMaxLay; // held as maximum index
			--Lvar->IndexMax; // held as maximum index

			Indices = 0; // one shot
			break;
		case 1:  // hru
			Lvar->IndexMax = (long)eval.top();  // set by re-arrange in execbase
			if (Lvar->IndexMax < 1) Lvar->IndexMax = 1;
			eval.pop(); // remove element index

			if (Lvar->IndexMaxLay) {
				Lvar->kind = TV::CRHM2; // allocated on next entry above
			}
			else {
				Lvar->kind = TV::CRHM;
				Lvar->value = new double[Lvar->IndexMax];
				--Lvar->IndexMax;
			}

			Indices = 0; // one shot
			break;
		default:
			eval.pop(); // remove element index
		}
		int Cnt = eval.size();
		return -555;
	}

private:
	stack<VarCHRM*>& LastVar;
	mutable long Indices;
};

#endif // !EXECVADDN
