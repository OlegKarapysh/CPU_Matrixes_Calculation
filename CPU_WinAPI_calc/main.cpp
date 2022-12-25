#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "SysInf.h"
#include "Matrix.h"
#include "MatrixProcessor.h"
#include "ThreadParams.h"

#define SINGLE_MODE
//#define MULTITHREAD_MODE

#define FILL_RANDOM 1
#define FILL_FIXED 2
#define FIXED_NUM 5.5f
#define MAX_THREADS 8

typedef float INF;

void PrintSysInfo(SysInf si)
{
    using namespace std;
    cout << "========== SYSTEM INFO ============ " << endl;
    cout << "Opearting system: " << si.GetOpSys() << endl;
    cout << "Number of cores: " << si.GetNumCores() << endl;
    cout << "Processor architecture: " << si.GetProcArch() << endl << endl;
}

void GetMatrixDimensionsFromUser(
      unsigned& width
    , unsigned& height
    , unsigned& size
)
{
    using namespace std;
    cout << "Enter the width of the matrixes: ";
    cin >> width;
    cout << "Enter the height of the matrixes: ";
    cin >> height;
    size = width * height;
}

void InitMatrixes(
    const unsigned width
    , const unsigned height
    , Matrix<INF>& matr1
    , Matrix<INF>& matr2
    , Matrix<INF>& matr3
    , Matrix<INF>& matr4
    , Matrix<INF>& matr5
    , Matrix<INF>& result
)
{
    matr1.Resize(width, height);
    matr2.Resize(width, height);
    matr3.Resize(width, height);
    matr4.Resize(width, height);
    matr5.Resize(width, height);
    result.Resize(width, height);
}

unsigned GetMatrFillFromUser()
{
    using namespace std;
    unsigned choice;
    cout << endl << "Select filling type (default is 1):" << endl
        << "1. Random numbers" << endl
        << "2. Fixed number 5.5" << endl;
    cin >> choice;
    return choice;
}

void FillMatrByChoice(
    unsigned choice
    , unsigned width
    , unsigned height
    , Matrix<INF>& matr1
    , Matrix<INF>& matr2
    , Matrix<INF>& matr3
    , Matrix<INF>& matr4
    , Matrix<INF>& matr5
)
{
    switch (choice)
    {
        case FILL_FIXED:
            FillMatrFixed(matr1, width, height, (INF)FIXED_NUM);
            FillMatrFixed(matr2, width, height, (INF)FIXED_NUM);
            FillMatrFixed(matr3, width, height, (INF)FIXED_NUM);
            FillMatrFixed(matr4, width, height, (INF)FIXED_NUM);
            FillMatrFixed(matr5, width, height, (INF)FIXED_NUM);
            break;
        default:
            FillMatrRandom(matr1, width, height, (INF)FIXED_NUM);
            FillMatrRandom(matr2, width, height, (INF)FIXED_NUM);
            FillMatrRandom(matr3, width, height, (INF)FIXED_NUM);
            FillMatrRandom(matr4, width, height, (INF)FIXED_NUM);
            FillMatrRandom(matr5, width, height, (INF)FIXED_NUM);
    }
}

void InitThreadParams(
    Matrix<INF>* &matr1
    , Matrix<INF>* &matr2
    , Matrix<INF>* &matr3
    , Matrix<INF>* &matr4
    , Matrix<INF>* &matr5
    , Matrix<INF>* &resultMatr
    , ThreadParams<INF>* &params
)
{
    params = new ThreadParams<INF>[MAX_THREADS];
    for (unsigned i = 0; i < MAX_THREADS; ++i)
    {
        params[i] = ThreadParams<INF>(matr1, matr2, matr3, matr4, matr5, resultMatr, MAX_THREADS, i + 1);
    }
}

int main()
{
    SysInf si = SysInf();
    unsigned width = 0, height = 0, size = 0, choice = FILL_RANDOM, worktime;
    Matrix<INF> matr1, matr2, matr3, matr4, matr5, result;
    HANDLE hThreads[MAX_THREADS];
    ThreadParams<INF>* params;

    PrintSysInfo(si);

    GetMatrixDimensionsFromUser(width, height, size);

    InitMatrixes(width, height, matr1, matr2, matr3, matr4, matr5, result);
   
    FillMatrByChoice(GetMatrFillFromUser(), width, height, matr1, matr2, matr3, matr4, matr5);

    //InitThreadParams(matr1, matr2, matr3, matr4, matr5, result, params);

    worktime = GetTickCount64();
#ifdef MULTITHREAD_MODE
    for (unsigned i = 0; i < MAX_THREADS; ++i)
    {
        // TODO: don't return if error, wait for threads and close handles/resources
        if (!(hThreads[i] = CreateThread(NULL, 0, ThreadCalc<INF>, (LPVOID)&(params[i]), 0, NULL)))
        {
            std::cout << "Error: threads haven't been created. " << GetLastError();
            return -1;
        }
    }

    for (unsigned i = 0; i < MAX_THREADS; ++i)
    {
        std::cout << params[i].StartIndex << " | " << params[i].EndIndex << std::endl;
    }

    if (WaitForMultipleObjects(MAX_THREADS, hThreads, TRUE, INFINITE) == WAIT_FAILED)
    {
        std::cout << "Error: failed to wait for threads. " << GetLastError();
        return -1;
    }
#endif // MULTITHREAD_MODE

#ifdef SINGLE_MODE
    for (register unsigned i = 0; i < size; ++i)
    {
        result[i] = 
            matr1[i] + 
            matr2[i] *
            matr3[i] -
            matr4[i] -
            matr5[i];
    }
#endif // SINGLE_MODE

    worktime = GetTickCount64() - worktime;
    printf("Time: %u ms \n", worktime);
    // display first 5 elems
    for (unsigned i = 0; i < 5; i++)
    {
        std::cout << result[i] << std::endl;
        std::cout << result[size - i - 2] << std::endl;
    }

    for (unsigned i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreads[i]);
    }

    return 0;
}