#include "DefCRHM.h"

TDim DefCRHM::getTDim(string D) {
	char table[][7] = {
		"BASIN",
		"ONE",
		"TWO",
		"THREE",
		"FOUR",
		"FIVE",
		"SIX",
		"SEVEN",
		"EIGHT",
		"NINE",
		"TEN",
		"ELEVEN",
		"TWELVE",
		"NHRU",
		"NOBS",
		"NLAY",
		"NDEF",
		"NFREQ",
		"NREB",
		"NDEFN",
		"DEFX"
	};

	for (long ii = 0; ii < 21; ++ii)
		if (D == table[ii])
			return (TDim)ii;

	return (TDim)-1;
}

TFun DefCRHM::getTFunc(string D) {
	char table[][9] = {
		"FOBS",
		"W_MJ",
		"MJ_W",
		"AVG",
		"MIN",
		"MAX",
		"DTOT",
		"POS",
		"TOT",
		"FIRST",
		"LAST",
		"CNT",
		"CNT0",
		"INTVL"
	};

	for (long ii = 1; ii < 11; ++ii)
		if (D == table[ii])
			return (TFun)ii;

	return (TFun)-1;
}
