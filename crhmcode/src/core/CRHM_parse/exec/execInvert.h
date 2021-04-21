#pragma once

#ifndef EXECINVERT
#define EXECINVERT

#include "execbase.h"

class execInvert : public execbase {
public:
	execInvert(stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "invert") {};
	execInvert(const execInvert& Cl) : execbase(Cl) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {
		Execbase Sp(new execInvert(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double X = eval.top();
		eval.pop();

		if (X == 0.0)
			X = 1.0;
		else
			X = 0.0;

		eval.push(X);
		return X;
	}
};

#endif // !EXECINVERT
