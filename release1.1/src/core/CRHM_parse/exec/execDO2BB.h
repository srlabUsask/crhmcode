#pragma once

#ifndef EXECDO2BB
#define EXECDO2BB

#include "execbase.h"

template<typename op>
class execDO2BB : public execbase {
public:
	execDO2BB(op m_op_, stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO2BB"), m_op(m_op_) {};
	execDO2BB(const execDO2BB& Cl) : execbase(Cl), m_op(Cl.m_op) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {

		Execbase Sp(new execDO2BB(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		const bool rhs = eval.top();
		eval.pop();
		const bool lhs = eval.top();
		eval.pop();

		eval.push(m_op(lhs, rhs));
		return eval.top();
	}
private:
	op m_op;
};

template <class op>
execDO2BB<op>
make_op2BB(op const& the_op, stack<double>& eval, list<Execbase>& oper)
{
	return execDO2BB<op>(the_op, eval, oper);
}

#endif // !EXECDO2BB
