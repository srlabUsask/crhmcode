#pragma once

#ifndef EXECDO1
#define EXECDO1

#include "execbase.h"

template<typename op>
class execDO1 : public execbase {
public:
	execDO1(op m_op_, stack<double>& eval_, list<Execbase>& oper_) : execbase(eval_, oper_, "DO1"), m_op(m_op_) {};
	execDO1(const execDO1& Cl) : execbase(Cl), m_op(Cl.m_op) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const {

		Execbase Sp(new execDO1(*this));
		oper.push_back(Sp);
	}

	double operator()() const {
		const double rhs = eval.top();
		eval.pop();

		eval.push(m_op(rhs));
		return eval.top();
	}
private:
	op m_op;
};

template <class op>
execDO1<op>
make_op1(op const& the_op, stack<double>& eval, list<Execbase>& oper)
{
	return execDO1<op>(the_op, eval, oper);
}

#endif // !EXECDO1
