#pragma once
#ifndef MULTIPLIER_INFO
#define MULTIPLIER_INFO

class Multiplier_Info {
public:
	char Abbr;
	string Name;
	double k;
	Multiplier_Info(char Abbr_, string Name_, double k_) :
		Abbr(Abbr_), Name(Name_), k(k_) {};
};

#endif // !MULTIPLIER_INFO
