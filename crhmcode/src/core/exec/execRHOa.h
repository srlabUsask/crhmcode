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
