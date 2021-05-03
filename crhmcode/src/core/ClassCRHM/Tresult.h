#pragma once

#ifndef TRESULT
#define TRESULT

class Tresult {
public:
	double k;
	char* aExp;

	Tresult(int size) : k(1.0) {
		aExp = new char[size];
		::memset(aExp, 0, sizeof(char) * size);
	}
	~Tresult() { delete[] aExp; }
};


#endif // !TRESULT
