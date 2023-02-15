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
