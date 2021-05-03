#pragma once

#ifndef CONVERT
#define CONVERT 

constexpr auto DEGREE = "\xBA";
constexpr auto DEGREE_CELSIUS ="\xBA""C";
constexpr auto DEGREE_FAHRENHEIT = "\xBA""F";
constexpr auto DEGREE_RANKINE = "\xBA""R";
constexpr auto MICRON = "\xB5";
constexpr auto ANGSTROM = "\xC5";

class Convert {
	static Unit_Info Infos[];
	static Multiplier_Info Multipliers[];

	int NumBasicUnits;
	int NumUnits;
	int NumMultipliers;

public:
	Convert();

	bool ConvertUnit(double& dValue, string pszSrcUnit, string pszDstUnit);

	double quickPow(double k, int nPow);
	int LookupUnit(string pszIn);
	void DivUnit(Tresult& u1, const Tresult& u2);
	void MulUnit(Tresult& u1, const Tresult& u2);
	void MulUnitK(Tresult& u, double k);
	void PowUnit(Tresult& u, char nPow);
	void SetBasicUnit(Tresult& u, double k, int iBasicUnit);
	void ExpandUnitExpr(Tresult& u, double k, string pszExpr);

	string ParseDivUnitExpr(string pszIn, Tresult& u);
	string ParseMulUnitExpr(string pszIn, Tresult& u);
	string ParsePowUnitExpr(string pszIn, Tresult& u);
	string ParseUnitPhase1(string pszIn, Tresult& u);
	string ParseUnitPhase2(string pszIn, Tresult& u);

	void CheckUnitsString(string Name, string variable, string units);
	void CheckUnitsObs(string Vunits, string Munits, string declaration); // check original observation units

	bool CheckUnitsTable();

};

#endif // !CONVERT
