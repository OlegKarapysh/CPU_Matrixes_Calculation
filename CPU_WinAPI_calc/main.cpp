#include "ConsoleInterface.h"

//#define SINGLE_MODE
#define MULTITHREAD_MODE

int main()
{
    SysInf si;
    unsigned width = 0, height = 0, size = 0, choice = FILL_RANDOM, worktime;
    Matrix<INF> matr1, matr2, matr3, matr4, matr5, result;
    HANDLE hThreads[MAX_THREADS];
    ThreadParams<INF>* params;

    PrintSysInfo(si);

    GetMatrixDimensionsFromUser(width, height, size);

    InitMatrixes(width, height, matr1, matr2, matr3, matr4, matr5, result);
   
    FillMatrByChoice(GetMatrFillFromUser(), width, height, matr1, matr2, matr3, matr4, matr5);

    InitThreadParams(matr1, matr2, matr3, matr4, matr5, result, params);

    worktime = GetTickCount64();

#ifdef MULTITHREAD_MODE
    CalculateMatrixesMultithread(hThreads, params);
#endif // MULTITHREAD_MODE

#ifdef SINGLE_MODE
    for (register unsigned i = 0; i < size; ++i)
    {
        result[i] = matr1[i] + matr2[i] * matr3[i] - matr4[i] - matr5[i];
    }
#endif // SINGLE_MODE

    worktime = GetTickCount64() - worktime;
    printf("Time: %u ms \n", worktime);

    WriteResultToFileByChoice(size, result);

    CloseThreadHandles(hThreads);

    return 0;
}
