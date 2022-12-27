#pragma once

#include "ThreadParams.h"

template <class inf> DWORD WINAPI ThreadCalc(LPVOID params)
{
	ThreadParams<inf> *calcParams = (ThreadParams<inf>*)params;
	Matrix<inf>* 
		matr1 = calcParams->Matr1,
		*matr2 = calcParams->Matr2,
		*matr3 = calcParams->Matr3,
		*matr4 = calcParams->Matr4,
		*matr5 = calcParams->Matr5,
		*result = calcParams->Result;

	for (register unsigned i = calcParams->StartIndex; i <= calcParams->EndIndex; ++i)
	{
		(*result)[i] = 
			(*matr1)[i] + 
			(*matr2)[i] * 
			(*matr3)[i] - 
			(*matr4)[i] - 
			(*matr5)[i];
	}
	return 0;
}

