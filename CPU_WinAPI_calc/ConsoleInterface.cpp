#define _CRT_SECURE_NO_WARNINGS

#include "ConsoleInterface.h"

void PrintSysInfo(SysInf si)
{
    using namespace std;
    cout << "========== SYSTEM INFO ============ " << endl;
    cout << "Operating system: " << si.GetOpSys() << endl;
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
        matr1.FillFixed(width, height, (INF)FIXED_NUM);
        matr2.FillFixed(width, height, (INF)FIXED_NUM);
        matr3.FillFixed(width, height, (INF)FIXED_NUM);
        matr4.FillFixed(width, height, (INF)FIXED_NUM);
        matr5.FillFixed(width, height, (INF)FIXED_NUM);
        break;
    default:
        matr1.FillRandom(width, height, (INF)FIXED_NUM);
        matr2.FillRandom(width, height, (INF)FIXED_NUM);
        matr3.FillRandom(width, height, (INF)FIXED_NUM);
        matr4.FillRandom(width, height, (INF)FIXED_NUM);
        matr5.FillRandom(width, height, (INF)FIXED_NUM);
    }
}

void InitThreadParams(
    Matrix<INF>& matr1
    , Matrix<INF>& matr2
    , Matrix<INF>& matr3
    , Matrix<INF>& matr4
    , Matrix<INF>& matr5
    , Matrix<INF>& resultMatr
    , ThreadParams<INF>*& params
)
{
    params = new ThreadParams<INF>[MAX_THREADS];
    for (unsigned i = 0; i < MAX_THREADS; ++i)
    {
        params[i] = ThreadParams<INF>(&matr1, &matr2, &matr3, &matr4, &matr5, &resultMatr, MAX_THREADS, i + 1);
    }
}

HANDLE StartNewThread(LPTHREAD_START_ROUTINE threadFunc, LPVOID threadParams)
{
    return CreateThread(NULL, 0, threadFunc, threadParams, 0, NULL);
}

DWORD WaitForThreads(DWORD threadsCount, const HANDLE* hThreads)
{
    return WaitForMultipleObjects(threadsCount, hThreads, TRUE, INFINITE);
}

void CloseThreadHandles(HANDLE  hThreads[])
{
    for (unsigned i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreads[i]);
    }
}

void WriteResultToFile(const unsigned int size, Matrix<INF>& result)
{
    FILE* resFile = _tfopen(OUT_FILE_NAME, __TEXT("w+"));
    if (resFile)
    {
        fprintf(resFile, "The list of pairs: vector index - result value:\n");
        for (unsigned i = 0; i < size; i++)
        {
            fprintf(resFile, "%u - %f\n", i, result[i]);
        }
    }
}

void WriteResultToFileByChoice(const unsigned int size, Matrix<INF>& result)
{
    using namespace std;

    char writeToFileChoice = 'n';
    cout << "Do you want to write the result to a file? [y/n]: ";
    cin >> writeToFileChoice;

    if (writeToFileChoice == 'y' || writeToFileChoice == 'Y')
    {
        WriteResultToFile(size, result);
        cout << "The result has been written to file.";
        return;
    }

    cout << "The result has not been written to file.";
}