#pragma once

#ifndef EXECRHOA
#define EXECRHOA

#include "execbase.h"

class execRHOa : public execbase {
public:
	execRHOa(stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "RHOa") {};
	execRHOa(const execRHOa& Cl) : execbase(Cl) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {
		Execbase Sp(new execRHOa(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double Pa = eval.top();
		eval.pop();

		double ea = eval.top();
		eval.pop();

		double t = eval.top();
		eval.pop();

		double X = RHOa(t, ea, Pa);

		eval.push(X);
		return X;
	}

	double RHOa(double t, double ea, double Pa) const // atmospheric density (kg/m^3)
	{
		const double R = 2870;
		return (1E4 * Pa / (R * (273.15 + t)) * (1.0 - 0.379 * (ea / Pa))); //
	}
};

#endif // !EXECRHOA
