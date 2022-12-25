#pragma once
#include "Matrix.h"

template <typename inf> struct ThreadParams
{
    Matrix<inf>* Matr1;
    Matrix<inf>* Matr2;
    Matrix<inf>* Matr3;
    Matrix<inf>* Matr4;
    Matrix<inf>* Matr5;
    Matrix<inf>* Result;
    unsigned StartIndex;
    unsigned EndIndex;

    ThreadParams()
    {
        Matr1 = nullptr;
        Matr2 = nullptr;
        Matr3 = nullptr;
        Matr4 = nullptr;
        Matr5 = nullptr;
        Result = nullptr;
        StartIndex = 0;
        EndIndex = 0;
    }

    ThreadParams(
                Matrix<inf>* firstMatrix
                , Matrix<inf>* secondMatrix
                , Matrix<inf>* thirdMatrix
                , Matrix<inf>* fourthMatrix
                , Matrix<inf>* fifthMatrix
                , Matrix<inf>* result
                , const unsigned numCores
                , const unsigned numThread)
    {
        Matr1 = firstMatrix;
        Matr2 = secondMatrix;
        Matr3 = thirdMatrix;
        Matr4 = fourthMatrix;
        Matr5 = fifthMatrix;
        Result = result;

        unsigned size = Result->GetSize();
        unsigned workgroup = size / numCores;
        StartIndex = workgroup * (numThread - 1);
        if (numThread == numCores)
        {
            EndIndex = size - 1;
        }
        else
        {
            EndIndex = StartIndex + workgroup - 1;
        }
    }
};