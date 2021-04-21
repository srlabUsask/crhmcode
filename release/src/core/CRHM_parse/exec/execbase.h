#pragma once

#ifndef EXECBASE
#define EXECBASE

#include "../CRHM_parse.h"
#include "spirit_templates.h"

class execbase;
typedef std::shared_ptr<execbase> Execbase;
typedef std::map<std::string, VarCHRM> symtab_t;

class execbase {
public:
	execbase(stack<double>& eval_, list<Execbase>& oper_, string s_, VarCHRM* Lvar_ = NULL)
		: eval(eval_), oper(oper_), s(s_), Lvar(Lvar_), OurOrder(-1) {
		OurIndex = ++Index;
	};

	execbase(const execbase& Cl); // copy constructor
	execbase& operator=(const execbase& Cl);

	virtual double operator()() const { return -777; };

	mutable VarCHRM* Lvar; // pointer to this operation variable

	static  long Index; // reference number

	string s; // class identification string. e.g. Vadd for execVadd etc.

	long OurIndex;
	long OurOrder;

protected:
	stack<double>& eval;
	list<Execbase>& oper;
};

#include "execNegate.h"
#include "execInvert.h"
#include "execRHOa.h"
#include "execIf.h"
#include "execElse.h"
#include "execEndif.h"
#include "execWhile.h"
#include "execWhile2.h"
#include "execEndwhile.h"
#include "execFor.h"
#include "execForC.h"
#include "execForI.h"
#include "execEndFor.h"
#include "execPush.h"
#include "execDO1.h"
#include "execDO1BB.h"
#include "execDO2.h"
#include "execDO2B.h"
#include "execDO2BB.h"
#include "execVset.h"
#include "execVindex.h"
#include "execVassign.h"
#include "execVget.h"
#include "execVindexVget.h"
#include "execVadd.h"
#include "execVaddN.h"
#include "calculator.h"

#endif // !EXECBASE
