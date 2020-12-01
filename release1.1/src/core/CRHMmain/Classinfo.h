#pragma once

#ifndef CLASSINFO
#define CLASSINFO

class Classinfo {
public:
	Classinfo() : thisPar(NULL), rootinfo(NULL), matched(false), cnt(0) {};
	Classinfo(ClassPar* thisPar) : thisPar(thisPar), rootinfo(NULL), matched(false), cnt(0) {};
	ClassPar* thisPar;
	Classinfo* rootinfo;
	long cnt;
	bool matched;
};

#endif // !CLASSINFO
