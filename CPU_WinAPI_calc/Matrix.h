#pragma once

#include "DynamicArray.h"

template <typename inf> class Matrix : public DynamicArray<inf>
{
private:
    unsigned _width;
    unsigned _height;

public:
    Matrix() : DynamicArray<inf>(0) 
    {
        _width = 0;
        _height = 0;
    }

    Matrix(unsigned width, unsigned height) : DynamicArray<inf>(width * height)
    {
        _width = width;
        _height = height;
    }

    inf& operator ()(unsigned row, unsigned col)
    {
        return DynamicArray<inf>::operator[](row * _width + col);
    }

    unsigned GetWidth()
    {
        return _width;
    }

    unsigned GetHeight()
    {
        return _height;
    }

    int Resize(unsigned width, unsigned height)
    {
        _width = width;
        _height = height;
        return DynamicArray<inf>::Resize(width * height);
    }

    void FillRandom(unsigned width, unsigned height, inf seed)
    {
        srand((unsigned)time(NULL));
        unsigned size = width * height;
        for (unsigned i = 0; i < size; ++i)
        {
            inf val = rand() * seed;
            DynamicArray<inf>::operator[](i) = val ? val : val + 1;
        }
    }

    void FillFixed(unsigned width, unsigned height, inf val)
    {
        unsigned size = width * height;
        for (unsigned i = 0; i < size; ++i)
        {
            DynamicArray<inf>::operator[](i) = val;
        }
    }
};