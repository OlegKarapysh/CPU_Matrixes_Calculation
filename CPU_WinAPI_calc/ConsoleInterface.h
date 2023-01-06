#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

#include "SysInf.h"
#include "Matrix.h"
#include "ThreadCalc.h"
#include "ThreadParams.h"
#include "ConsoleInterface.h"

#define FILL_RANDOM 1
#define FILL_FIXED 2
#define FIXED_NUM 5.5f
#define MAX_THREADS 8
#define OUT_FILE_NAME __TEXT("Result.txt")

typedef double INF;

void PrintSysInfo(SysInf si);

void GetMatrixDimensionsFromUser(unsigned& width, unsigned& height, unsigned& size);

void InitMatrixes(
    const unsigned width
    , const unsigned height
    , Matrix<INF>& matr1
    , Matrix<INF>& matr2
    , Matrix<INF>& matr3
    , Matrix<INF>& matr4
    , Matrix<INF>& matr5
    , Matrix<INF>& result
);

unsigned GetMatrFillFromUser();

void FillMatrByChoice(
    unsigned choice
    , unsigned width
    , unsigned height
    , Matrix<INF>& matr1
    , Matrix<INF>& matr2
    , Matrix<INF>& matr3
    , Matrix<INF>& matr4
    , Matrix<INF>& matr5
);

void InitThreadParams(
    Matrix<INF>& matr1
    , Matrix<INF>& matr2
    , Matrix<INF>& matr3
    , Matrix<INF>& matr4
    , Matrix<INF>& matr5
    , Matrix<INF>& resultMatr
    , ThreadParams<INF>*& params
);

HANDLE StartNewThread(LPTHREAD_START_ROUTINE threadFunc, LPVOID threadParams);

DWORD WaitForThreads(DWORD threadsCount, const HANDLE* hThreads);

void CloseThreadHandles(HANDLE  hThreads[]);

void WriteResultToFileByChoice(Matrix<INF>& result);

void CalculateMatrixesMultithread(HANDLE  hThreads[], ThreadParams<INF>* params);

