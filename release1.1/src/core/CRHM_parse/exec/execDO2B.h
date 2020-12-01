#pragma once

#ifndef EXECDO2B
#define EXECDO2B

#include "execbase.h"

template<typename op>
class execDO2B : public execbase {
public:
	execDO2B(op m_op_, stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO2B"), m_op(m_op_) {};
	execDO2B(const execDO2B& Cl) : execbase(Cl), m_op(Cl.m_op) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {

		Execbase Sp(new execDO2B(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		double rhs = eval.top();
		eval.pop();
		double lhs = eval.top();
		eval.pop();

		eval.push(m_op(lhs, rhs));
		return  eval.top();
	}
private:
	op m_op;
};

template <class op>
execDO2B<op>
make_op2B(op const& the_op, stack<double>& eval, list<Execbase>& oper)
{
	return execDO2B<op>(the_op, eval, oper);
}

#endif // !EXECDO2B
