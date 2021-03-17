#include "ClassCRHM.h"
#include "Convert.h"
#include "Unit_Info.h"
#include "Multiplier_Info.h"
#include "Tresult.h"


Convert::Convert() {
	NumUnits = 0;
	NumBasicUnits = 0;
	NumMultipliers = 0;

	while (!(Infos[NumUnits].Abbr).empty()) {
		if ((Infos[NumUnits].Expr).empty()) {
			Infos[NumUnits].k = NumBasicUnits;
			++NumBasicUnits;
		}

		++NumUnits;
	}

	while (Multipliers[NumMultipliers].Abbr) {
		++NumMultipliers;
	}
}

Unit_Info Convert::Infos[] = {
	Unit_Info("1", "1", 1, "") ,
	Unit_Info("A", "Ampere" , 1, "") ,
	Unit_Info("Bq", "becquerel", 1, "l/s") ,
	Unit_Info("Btu", "InternationalTableBtu", 1055.05585262, "Kg*m^2/s^2") ,
	Unit_Info("C", "Coulomb", 1, "A*s") ,
	Unit_Info("Ci", "Curie", 3.7 * 1010, "l/s") ,
	Unit_Info("F", "Farad", 1, "A^2*s^4/Kg*m^2") ,
	Unit_Info("Fdy", "Faraday", 96487, "A*s") ,
	Unit_Info("Gy", "Gray", 1, "m^2/s^2") ,
	Unit_Info("H", "Henry", 1, "Kg*m^2/A^2*s^2") ,
	Unit_Info("Hz", "Hertz", 1, "s^-1") ,
	Unit_Info("J", "Joule", 1, "Kg*m^2/s^2") ,
	Unit_Info("K", "Kelvin" , 1, ""),
	Unit_Info("Knot", "NauticalMilesPerHour", 463.0 / 900.0, "m/s") ,
	Unit_Info("N", "Newton", 1, "Kg*m/s^2") ,
	Unit_Info("Ohm", "Ohm", 1, "Kg*m^2/A^2*s^3") ,
	Unit_Info("OzUK", "UKFluidOunce", 2.8413075e-5, "m^3") ,
	Unit_Info("P", "Poise", 0.1, "Kg/m*s") ,
	Unit_Info("Pa", "Pascal", 1, "Kg/m*s") ,
	Unit_Info("Pdl", "Poundal", 0.13825495376, "Kg*m/s^2") ,
	Unit_Info("Pica", "Pica", 1.0 / 72.0, "in") ,
	Unit_Info("R", "Roentgen", 0.000258, "A*s/Kg") ,
	Unit_Info("S", "Siemens", 1, "A^2*s^3/Kg*m^2") ,
	Unit_Info("St", "Stokes", 0.0001, "m^2/s") ,
	Unit_Info("Sv", "Sievert", 1, "m^2/s^2") ,
	Unit_Info("T", "Tesla", 1, "Kg/A*s^2") ,
	Unit_Info("U", "UnifiedAtomicMass", 1.6605402e-27, "Kg") ,
	Unit_Info("V", "Volt", 1, "Kg*m^2/A*s^2") ,
	Unit_Info("W", "Watt", 1, "Kg*m^2/s^3") ,
	Unit_Info("Wb", "Weber", 1, "Kg*m^2/A*s^2") ,
	Unit_Info("acre", "Acre", 4046.87260987, "m^2") ,
	Unit_Info("arcmin", "ArcMinute", 2.9088820866e-4, "r") ,
	Unit_Info("arcs", "ArcSecond", 4.848136111e-6, "r") ,
	Unit_Info("atm", "Attmosphere", 101325, "Kg/m*s^2") ,
	Unit_Info("au", "AstronomicalUnit", 1.495979 * 1011, "m") ,
	Unit_Info("b", "Barn", 1e-28, "m^2") ,
	Unit_Info("bar", "Bar", 100000, "Kg/m*s^2") ,
	Unit_Info("bbl", "Barrel", 0.158987294928, "m^3") ,
	Unit_Info("bu", "Bushel", 0.03523907, "m^3") ,
	Unit_Info("c", "LightSpeed", 299792458, "m/s") ,
	Unit_Info("cal", "Calorie", 4.1868, "Kg*m^2/s^2") ,
	Unit_Info("cd", "Candela" , 1, "") ,
	Unit_Info("chain", "Chain", 20.1168402337, "m") ,
	Unit_Info("ct", "Carat", 0.0002, "Kg") ,
	Unit_Info("cu", "USCup", 2.365882365e-4, "m^3") ,
	Unit_Info("d", "day", 86400, "s") ,
	Unit_Info("dyn", "Dyne", 0.00001, "Kg*m/s^2") ,
	Unit_Info("eV", "ElectronVolt", 1.60217733e-19, "Kg*m^2/s^2") ,
	Unit_Info("erg", "Erg", 0.0000001, "Kg*m^2/s^2") ,
	Unit_Info("fath", "Fathom", 1.82880365761, "m") ,
	Unit_Info("fbm", "BoardFoot", 0.002359737216, "m^3") ,
	Unit_Info("fc", "Footcandle", 10.7639104167, "cd*sr/m^2") ,
	Unit_Info("fermi", "Fermi", 1e-15, "m") ,
	Unit_Info("flam", "Footlambert", 3.42625909964, "cd/m^2") ,
	Unit_Info("ft", "InternationalFoot", 0.3048, "m") ,
	Unit_Info("ftUS", "SurveyFoot", 0.304800609601, "m") ,
	Unit_Info("g", "Gram" , 1, "") ,
	Unit_Info("ga", "StandardFreefall", 9.80665, "m/s^2") ,
	Unit_Info("gal", "USGallon", 0.003785411784, "m^3") ,
	Unit_Info("galC", "CanadianGallon", 0.00454609, "m^3") ,
	Unit_Info("galUK", "UKGallon", 0.004546092, "m^3") ,
	Unit_Info("gf", "GramForce", 0.00980665, "Kg*m/s^2") ,
	Unit_Info("grad", "Grade", 1.57079632679e-2, "r") ,
	Unit_Info("grain", "Grain", 0.00006479891, "Kg") ,
	Unit_Info("h", "Hour", 3600, "s") ,
	Unit_Info("ha", "Hectare", 10000, "m^2") ,
	Unit_Info("hp", "horsepower", 745.699871582, "Kg*m^2/s^2") ,
	Unit_Info("in", "Inch", 0.0254, "m") ,
	Unit_Info("inH2O", "InchesOfWater", 248.84, "Kg/m*s^2") ,
	Unit_Info("inHg", "InchesOfMercury", 3386.38815789, "Kg/m*s^2") ,
	Unit_Info("int", "CRHM time step", 3600, "s") ,
	Unit_Info("kip", "KilopoundForce", 4448.22161526, "Kg*m/s^2") ,
	Unit_Info("kph", "KilometersPerHour", 5.0 / 18.0, "m/s") ,
	Unit_Info("l", "Liter", 0.001, "m^3") ,
	Unit_Info("lam", "Lambert", 3183.09886184, "cd/m^2") ,
	Unit_Info("lb", "AvoirdupoisPound", 0.45359267, "Kg") ,
	Unit_Info("lbf", "PoundForce", 4.44822161526, "Kg*m/s^2") ,
	Unit_Info("lbt", "TroyPound", 0.3732417216, "Kg") ,
	Unit_Info("lm", "Lumen", 1, "cd*sr") ,
	Unit_Info("lx", "Lux", 1, "cd*sr/m^2") ,
	Unit_Info("lyr", "LightYear", 9.46052840488 * 1015, "m") ,
	Unit_Info("m", "Meter" , 1, "") ,
	Unit_Info("mho", "Mho", 1, "A^2*s^2/Kg*m^2") ,
	Unit_Info("mi", "InternationalMile", 1609.344, "m") ,
	Unit_Info("miUS", "USStatuteMile", 1609.34721869, "m") ,
	Unit_Info("mil", "Mil", 0.0000254, "m") ,
	Unit_Info("min", "Minute", 60, "s") ,
	Unit_Info("mmHg", "MilimeterOfMercury", 133.322368421, "Kg/m*s^2") ,
	Unit_Info("mol", "Mole" , 1, "") ,
	Unit_Info("mph", "MilesPerHour", 0.44704, "m/s") ,
	Unit_Info("nmi", "NauticalMile", 1852, "m") ,
	Unit_Info("oz", "Ounce", 0.028349523125, "Kg") ,
	Unit_Info("ozfl", "USFluidOunce", 2.95735295625e-5, "m^3") ,
	Unit_Info("ozt", "TroyOunce", 0.0311034768, "Kg") ,
	Unit_Info("pc", "Parsec", 3.08567818585106, "m") ,
	Unit_Info("ph", "Phot", 10000, "cd*sr/m^2") ,
	Unit_Info("pk", "Peck", 0.0088097675, "m^3") ,
	Unit_Info("psi", "PoundsPerSquareInch", 6894.75729317, "Kg/m*s^2") ,
	Unit_Info("pt", "Pint", 0.000473176473, "m^3") ,
	Unit_Info("qt", "Quart", 0.000946352946, "m^3") ,
	Unit_Info("r", "Radian" , 1, "") ,
	Unit_Info("rad", "Rad", 0.01, "m^2/s^2") ,
	Unit_Info("rd", "Rod", 5.02921005842, "m") ,
	Unit_Info("rem", "Rem", 0.01, "m^2/s^2") ,
	Unit_Info("s", "Second" , 1, "") ,
	Unit_Info("sb", "Stilb", 10000, "cd/m^2") ,
	Unit_Info("slug", "Slug", 14.5939029372, "Kg") ,
	Unit_Info("sr", "Steradian" , 1, "") ,
	Unit_Info("st", "Stere", 1, "m^3") ,
	Unit_Info("t", "MetricTon", 1000, "Kg") ,
	Unit_Info("tbsp", "Tablespoon", 1.47867647813e-5, "m^3") ,
	Unit_Info("therm", "EECTherm", 105506000, "Kg*m^2/s^2") ,
	Unit_Info("ton", "ShortTon", 907.18474, "Kg") ,
	Unit_Info("tonUK", "UKLongTon", 1016.0469088, "Kg") ,
	Unit_Info("torr", "Torr", 133.322368421, "Kg/m^2") ,
	Unit_Info("tsp", "Teaspoon", 4.92892159375e-6, "m^3") ,
	Unit_Info("yd", "InternationalYard", 0.9144, "m") ,
	Unit_Info("yr", "Year", 31556925.9747, "s") ,
	//Unit_Info("\B0", "Degree", 1.74532925199e-2, "r") ,
	//Unit_Info("\B0C", "DegreeCelsius", 1.0, "K"),
	//Unit_Info("\B0F", "DegreesFahrenheit", 1.0 / 1.8, "K"),
	//Unit_Info("\B0R", "DegreesRankine", 1.0 / 1.8, "K"),
	//Unit_Info("\B5", "Micron", 1e-6, "m"),
	//Unit_Info("\C5", "Angstrom", 1e-10, "m"),
	Unit_Info(DEGREE, "Degree", 1.74532925199e-2, "r"),
	Unit_Info(DEGREE_CELSIUS, "DegreeCelsius", 1.0, "K") ,
	Unit_Info(DEGREE_FAHRENHEIT, "DegreesFahrenheit", 1.0 / 1.8, "K") ,
	Unit_Info(DEGREE_RANKINE, "DegreesRankine", 1.0 / 1.8, "K") ,
	Unit_Info(MICRON, "Micron", 1e-6, "m") ,
	Unit_Info(ANGSTROM, "Angstrom", 1e-10, "m") ,
	Unit_Info("", "", 0, "") };


Multiplier_Info Convert::Multipliers[] = {
	Multiplier_Info('Y',	"Yotta",   1e+24) ,
	Multiplier_Info('Z',	"Zetta",   1e+21) ,
	Multiplier_Info('E',	"Exa",     1e+18) ,
	Multiplier_Info('P',	"Peta",    1e+15) ,
	Multiplier_Info('T',	"Tera",    1e+12) ,
	Multiplier_Info('G',	"Giga",    1e+9) ,
	Multiplier_Info('M',	"Mega",    1e+6) ,
	Multiplier_Info('k',        "kilo",    1e+3) ,
	Multiplier_Info('K',        "Kilo",    1e+3) ,
	Multiplier_Info('h',        "hecto",   1e+2) ,
	Multiplier_Info('H',        "Hecto",   1e+2) ,
	Multiplier_Info('D',	"Deka",    1e+1) ,
	Multiplier_Info('d',	"deci",    1e-1) ,
	Multiplier_Info('c',	"cent",    1e-2) ,
	Multiplier_Info('m',	"mili",    1e-3) ,
	Multiplier_Info('u',	"micro",   1e-6) ,
	//Multiplier_Info('\B5',        "micro",   1e-6) ,
	Multiplier_Info('n',	"nano",    1e-9) ,
	Multiplier_Info('p',	"pico",    1e-12) ,
	Multiplier_Info('f',	"femto",   1e-15) ,
	Multiplier_Info('a',	"atto",    1e-18) ,
	Multiplier_Info('z',	"zepto",   1e-21) ,
	Multiplier_Info('y',	"yocto",   1e-24) ,
	Multiplier_Info('\0',	"",          0.0) };

string tcsinc(string pszIn) {

	return pszIn.substr(1);
}

string tcsSkipSpaces(string pszIn) {
	while (pszIn[0] == ' ')
		pszIn = pszIn.substr(1);
	return pszIn;
}

string tcsSqueeze(string pszIn) {
	string::iterator pos;

	string::size_type Idx;
	//  char const Misc[] = {"( )%\BA\B0\t"};
	//char const Misc[] = { "( )%\BA\t" };
	//xA9 = copywrite symbol
	char const Misc[] = { "( )%\xA9\t" };

	Idx = pszIn.find_first_of(Misc);
	while (Idx != string::npos) {
		pszIn = pszIn.erase(Idx, 1);
		Idx = pszIn.find_first_of(Misc);
	}

	return pszIn;
}

// Main Functions

// Converts the <dValue> from the <pszSrcUnit> to the <pszDstUnit>

bool Convert::ConvertUnit(
	double& dValue,     // [in] value to convert, [out] converted value
	string pszSrcUnit,  // [in] source unit
	string pszDstUnit   // [in] destination unit
) {

	pszSrcUnit = tcsSkipSpaces(pszSrcUnit);
	pszDstUnit = tcsSkipSpaces(pszDstUnit);

	dValue = 1.0;

	if (pszSrcUnit.compare(pszDstUnit) == 0)
		return true;

	Tresult uSrcUnit(NumBasicUnits);
	try
	{
		pszSrcUnit = ParseDivUnitExpr(pszSrcUnit, uSrcUnit);
	}
	catch (int i)
	{
		if (i == 3)
		{
			return false;
		}
	}

	Tresult uDstUnit(NumBasicUnits);
	try
	{
		pszDstUnit = ParseDivUnitExpr(pszDstUnit, uDstUnit);
	}
	catch (int i)
	{
		if (i == 3)
		{
			return false;
		}
	}

	for (int i = 0; i < NumBasicUnits; ++i)
		if (uSrcUnit.aExp[i] != uDstUnit.aExp[i]) {
			dValue = -999;
			return false;
		}

	dValue *= uSrcUnit.k;
	dValue /= uDstUnit.k;

	return true;
}

double Convert::quickPow(double k, int nPow)
{
	bool bNegative = (nPow < 0);
	if (bNegative)
		nPow = -nPow;

	double r = 1.0;

	while (nPow != 0)
	{
		if (nPow & 1)
			r *= k;

		k *= k;
		nPow >>= 1;
	}

	if (bNegative)
		r = 1.0 / r;

	return r;
}

int Convert::LookupUnit(string pszIn)
{
	int iFirst = 0;
	int iLast = NumUnits;
	int i;

	string::size_type Idx;

	Idx = pszIn.find_first_of("*/^");
	if (Idx == string::npos)
		Idx = pszIn.size();

	while (iLast >= iFirst)
	{
		i = (iLast + iFirst) / 2;

		int nCmp = pszIn.compare(0, Idx, Infos[i].Abbr);

		if (nCmp == 0)
			return i;  // match

		if (nCmp < 0)
			iLast = i - 1;
		else
			iFirst = i + 1;
	}

	return -1;  // no match
}

void Convert::DivUnit(Tresult& u1, const Tresult& u2)
{
	u1.k /= u2.k;

	for (int i = 0; i < NumBasicUnits; ++i)
		u1.aExp[i] -= u2.aExp[i];
};

void Convert::MulUnit(Tresult& u1, const Tresult& u2)
{
	u1.k *= u2.k;

	for (int i = 0; i < NumBasicUnits; ++i)
		u1.aExp[i] += u2.aExp[i];
};

void Convert::MulUnitK(Tresult& u, double k)
{
	u.k *= k;
};

void Convert::PowUnit(Tresult& u, char nPow)
{
	for (int i = 0; i < NumBasicUnits; ++i)
		u.aExp[i] *= nPow;

	u.k = quickPow(u.k, nPow);
};

void Convert::SetBasicUnit(Tresult& u, double k, int iUnit)
{
	u.k = k;

	int iBasicUnit = (int)(Infos[iUnit].k);
	if (0 <= iBasicUnit)
		u.aExp[iBasicUnit] = 1;
}

void Convert::ExpandUnitExpr(Tresult& u, double k, string pszExpr)
{
	pszExpr = ParseDivUnitExpr(pszExpr, u);

	u.k *= k;
}

// Unit interpretation: template declarations

string Convert::ParseDivUnitExpr(string pszIn, Tresult& u)
{
	pszIn = ParseMulUnitExpr(pszIn, u);

	if (pszIn.empty())
	{
		return pszIn;
	}


	string pszMark = pszIn;
	pszIn = tcsSkipSpaces(pszIn);
	if (pszIn[0] != '/')
	{
		throw 3;
	}

	pszIn = tcsinc(pszIn);
	pszIn = tcsSkipSpaces(pszIn);

	Tresult uAux(NumBasicUnits);
	pszIn = ParseMulUnitExpr(pszIn, uAux);

	DivUnit(u, uAux);

	pszMark = pszIn;
	return pszMark;
}

string Convert::ParseMulUnitExpr(string pszIn, Tresult& u)
{
	pszIn = ParsePowUnitExpr(pszIn, u);

	if (pszIn.empty())
		return pszIn;

	string pszMark = pszIn;

	while (pszIn = tcsSkipSpaces(pszIn), pszIn[0] == '*')
	{
		pszIn = tcsinc(pszIn);

		Tresult uAux(NumBasicUnits);
		pszIn = ParsePowUnitExpr(pszIn, uAux);
		if (pszIn == "error")
			return pszMark;

		MulUnit(u, uAux);

		pszMark = pszIn;
	}

	return pszIn;
}

string Convert::ParsePowUnitExpr(string pszIn, Tresult& u)
{
	pszIn = ParseUnitPhase1(pszIn, u);

	if (pszIn.empty())
		return pszIn;

	string pszMark = pszIn;

	pszIn = tcsSkipSpaces(pszIn);
	if (pszIn[0] != '^')
		return pszMark;

	pszIn = tcsinc(pszIn);
	pszIn = tcsSkipSpaces(pszIn);

	bool bNegative = (pszIn[0] == '-');

	if (pszIn[0] == '+' || pszIn[0] == '-')
		pszIn = tcsinc(pszIn);

	//if (!_istdigit(pszIn[0]))
	if (!iswdigit(pszIn[0]))
		return pszMark;

	char nPow = 0;

	//while (_istdigit(pszIn[0]))
	while (iswdigit(pszIn[0]))
	{
		char nPow2 = nPow * 10 + (pszIn[0] - '0');
		if (nPow2 < nPow)
			break;

		nPow = nPow2;
		pszIn = tcsinc(pszIn);
	}

	if (bNegative)
		nPow = -nPow;

	PowUnit(u, nPow);

	return pszIn;
}

string Convert::ParseUnitPhase1(string pszIn, Tresult& u)
{
	string pszMark = pszIn;

	pszIn = ParseUnitPhase2(pszIn, u);
	if (pszIn != "????")
		return pszIn;

	pszIn = pszMark;

	double k;
	int ii;

	for (ii = 0; ii < NumMultipliers; ++ii)
		if (pszIn[0] == Multipliers[ii].Abbr) {
			k = Multipliers[ii].k;
			break;
		}

	if (ii >= NumMultipliers) {

		bool bNegative = (pszIn[0] == '-');

		if (pszIn[0] == '+' || pszIn[0] == '-')
			pszIn = tcsinc(pszIn);

		//if (!_istdigit(pszIn[0]))
		if (!iswdigit(pszIn[0]))

			throw 1; // cause fault
		else {

			k = 0.0;

			//while (_istdigit(pszIn[0]))
			while (iswdigit(pszIn[0]))
			{
				double nPow2 = (k * 10.0) + ((long long)pszIn[0] - (long long)'0');
				if (nPow2 < k)
					break;

				k = nPow2;
				pszIn = tcsinc(pszIn);
			}

			if (bNegative)
				k = -k;

			if (pszIn[0] == '*') // allow '*'
				pszIn = tcsinc(pszIn);
		}
	}
	else
		pszIn = tcsinc(pszIn);

	pszIn = ParseUnitPhase2(pszIn, u);

	MulUnitK(u, k);

	return pszIn;
}

string Convert::ParseUnitPhase2(string pszIn, Tresult& u)
{
	int iUnit = LookupUnit(pszIn);

	if (iUnit < 0)
		return "????";

	if (Infos[iUnit].Expr.empty())
		SetBasicUnit(u, 1.0, iUnit);
	else
		ExpandUnitExpr(u, Infos[iUnit].k, Infos[iUnit].Expr);

	pszIn = pszIn.substr(Infos[iUnit].Abbr.size());

	return pszIn;
}

bool Convert::CheckUnitsTable()
{
	bool bSuccess = true;

	for (int i = 0; i < NumUnits - 1; ++i)
	{
		const Unit_Info info1 = Infos[i];
		const Unit_Info info2 = Infos[i + 1];

		if (info1.Abbr.compare(info2.Abbr) >= 0)
		{
			bSuccess = false;
		}
	}
	return bSuccess;
}

void Convert::CheckUnitsString(string Name, string variable, string units)
{
	//string::size_type Idx;
	string temp(units);

	units = tcsSqueeze(units);

	if (units.empty()) return;

	Tresult uSrcUnit(NumBasicUnits);

	try {
		units = ParseDivUnitExpr(units, uSrcUnit);
		if (!units.empty()) {
			units = temp;
			throw 2;
		}
	}
	catch (int i) {
		if (i == 3)
		{
			CRHMException Except("Units error ParseDivUnitExpr threw error code 3: '" + units + "' in " + Name + ' ' + variable, TExcept::WARNING);
			LogError(Except);
		}
		else
		{
			CRHMException Except("Units error ParseDivUnitExpr returned empty: '" + units + "' in " + Name + ' ' + variable, TExcept::WARNING);
			LogError(Except);
		}


	}
}

void Convert::CheckUnitsObs(string Vunits, string Munits, string declaration) { // check original observation units
	//string::size_type Idx;
	double d;

	if (!Vunits.empty()) {
		if (!ConvertUnit(d, tcsSqueeze(Vunits), tcsSqueeze(Munits)) || d != 1.0) {
			CRHMException Except("Units error: '" + Vunits + " instead of " + Munits + "' in " + declaration, TExcept::WARNING);
			LogError(Except);
		}
	}
}