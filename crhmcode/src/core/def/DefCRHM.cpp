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
