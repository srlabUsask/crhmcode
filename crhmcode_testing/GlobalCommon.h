#pragma once
#ifndef GlobalCommonH
#define GlobalCommonH
//---------------------------------------------------------------------------


#include <map>
#include <algorithm>
#include <bitset>

using namespace std;

class ClassVar;
class ClassPar;

template <class T>
class Classless : binary_function<T, T, bool> { // function object
public:
	bool operator() (T i, T i2) const
	{
	 string s1(i);
	 string s2(i2);
		// uppercase comparison    
		transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
		transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
		// ensure basin is always sorted first
		if (s1.compare(0, 6, "SHARED", 6) == 0)
			s1.replace(0, 6, " ");

		if (s2.compare(0, 6, "SHARED", 6) == 0)
			s2.replace(0, 6, " ");

		return (bool)(s1 < s2);
	}
};

typedef string KeyType;
typedef ClassVar *Var;
typedef ClassPar *Par;
typedef long Dim;
typedef string string;
typedef pair<KeyType, Var>  PairVar;
typedef pair<KeyType, Par>  PairPar;
typedef pair<KeyType, Dim>  PairDim;
typedef map<KeyType, Var>  MapVar;
typedef map<KeyType, Par, Classless<KeyType> >  MapPar;
typedef map<KeyType, Dim>  MapDim;


typedef string KeyType2;
typedef pair<KeyType2, long>  PairstrV;
typedef pair<KeyType2, KeyType2>  Pairstr;
typedef pair<KeyType2, PairstrV>  PairstrI;
typedef multimap<KeyType2, PairstrV>  Mapstr; // build etc.

typedef pair<KeyType, KeyType>  Pairstr2; // used by AKA
typedef map<KeyType, KeyType>  Mapstr2;  // used by AKA
typedef map<KeyType2, KeyType2>  MapstrSS;  // used by main

typedef bitset <1024> BitSet;

template <class K, class V, class P>
class value_equals {
private:
	V value;
public:
	value_equals(const V& v) : value(v) {} // constructor (initialise value to compare)
	bool operator() (pair<const K, P> elem) { // comparison
		return elem.second.first == value;
	}
};

#endif