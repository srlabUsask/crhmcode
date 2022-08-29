/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
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
