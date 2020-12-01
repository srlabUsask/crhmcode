#pragma once

#ifndef EXECIF
#define EXECIF

#include "execbase.h"

class execIf : public execbase {
public:
	execIf(stack<double>& eval_, list<Execbase>& oper_,
		list<Execbase> ::iterator& PCiter_, stack<list<Execbase> ::iterator>& PCiterIF_)
		: execbase(eval_, oper_, "If"), PCiter(PCiter_), PCiterIF(PCiterIF_), False_iter(oper.end()),
		End_iter(oper.end()) {};

	execIf(const execIf& Cl) : execbase(Cl), PCiter(Cl.PCiter), PCiterIF(Cl.PCiterIF),
		False_iter(Cl.False_iter), End_iter(Cl.End_iter) {}; // copy constructor

	void operator()(const string::iterator, const string::iterator) const { // compilation

		Execbase Sp(new execIf(*this));
		oper.push_back(Sp);

		PCiterIF.push(--oper.end()); // push self
	}

	double operator()() const { // execution

		if (!eval.top()) {
			PCiter = False_iter; // execute false statement, otherwise fall through
			++PCiter; // value before 'else' pushed on to stack and skips 'else'.
		}
		eval.pop();

		return -1;
	}

	void setFalse_iter(list<Execbase> ::iterator PCiter) { // used by execElse
		False_iter = PCiter;
	};

	void setEnd_iter(list<Execbase> ::iterator PCiter) { // used by execEndif
		End_iter = PCiter;

		if (False_iter == oper.end()) { // no 'else' ???
			False_iter = PCiter;
			--False_iter; // make instruction
		}
	};

	void jmpEnd_iter(void) { // used by execElse
		PCiter = End_iter;
	};

private:
	list<Execbase> ::iterator False_iter;
	list<Execbase> ::iterator End_iter;

	list<Execbase> ::iterator& PCiter;   // changes for each if
	stack<list<Execbase> ::iterator>& PCiterIF; // changes for each if
};

#endif // !EXECIF
