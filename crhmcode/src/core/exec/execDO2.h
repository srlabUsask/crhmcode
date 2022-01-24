#pragma once

#ifndef EXECDO2
#define EXECDO2

#include "execbase.h"

template<typename op>
class execDO2 : public execbase {
public:
	execDO2(op m_op_, stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO2"), m_op(m_op_) {};
	execDO2(const execDO2& Cl) : execbase(Cl), m_op(Cl.m_op) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {

		Execbase Sp(new execDO2(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double rhs = eval.top();
		eval.pop();
		double lhs = eval.top();
		eval.pop();

		eval.push(m_op(lhs, rhs));
		return eval.top();
	}
private:
	op m_op;
};

template <class op>
execDO2<op>
make_op2(op const& the_op, stack<double>& eval, list<Execbase>& oper)
{
	return execDO2<op>(the_op, eval, oper);
}

#endif // !EXECDO2
