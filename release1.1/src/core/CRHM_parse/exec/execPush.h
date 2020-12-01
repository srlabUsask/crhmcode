#pragma once

#ifndef EXECPUSH
#define EXECPUSH

#include "execbase.h"

class execPush : public execbase {
public:
	execPush(stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "Push") {};
	execPush(const execPush& Cl) : execbase(Cl), Ln(Cl.Ln) {}; // copy constructor

	void operator()(double n) const {
		Ln = n;

		Execbase Sp(new execPush(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		eval.push(Ln);
		return Ln;
	}

private:
	mutable double Ln{ 0.0 };
};

#endif // !EXECPUSH
