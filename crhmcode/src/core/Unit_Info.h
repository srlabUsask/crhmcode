#pragma once

#ifndef UNIT_INFO
#define UNIT_INFO

class Unit_Info {
public:
	string Abbr;
	string Name;
	double k;
	string Expr;

	Unit_Info() :
		Abbr(""), Name(""), k(0.0), Expr("") {};

	Unit_Info(string Abbr_, string Name_, double k_, string Expr_) :
		Abbr(Abbr_), Name(Name_), k(k_), Expr(Expr_) {};
};

#endif // !UNIT_INFO
