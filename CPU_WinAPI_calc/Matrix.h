#pragma once

#include "DynamicArray.h";

template <typename inf> class Matrix : public DynamicArray<inf>
{
private:
    unsigned _width;
    unsigned _height;

public:
    Matrix(unsigned width, unsigned height) : DynamicArray<inf>(width * height)
    {
        _width = width;
        _height = height;
    }

    inf& operator ()(unsigned row, unsigned col)
    {
        return _elements[row * _width + col];
    }

    unsigned GetWidth()
    {
        return _width;
    }

    unsigned GetHeight()
    {
        return _height;
    }
};