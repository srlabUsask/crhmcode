#pragma once

#ifndef EXECNEGATE
#define EXECNEGATE

#include "execbase.h"

class execNegate : public execbase {
public:
	execNegate(stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "negate") {};
	execNegate(const execNegate& Cl) : execbase(Cl) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {
		Execbase Sp(new execNegate(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double X = eval.top();
		eval.pop();
		eval.push(-X);
		return X;
	}
};

#endif // !EXECNEGATE
