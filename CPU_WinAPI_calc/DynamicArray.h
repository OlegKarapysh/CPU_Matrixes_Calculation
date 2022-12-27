#pragma once
#include <iostream>
#include <malloc.h>
#include <stdlib.h>

#define FAIL 0
#define SUCCESS 1
#define NOT_FOUND -1

template <typename inf> class DynamicArray
{
private:
    inf* _arr = nullptr;
    size_t _size;
    size_t _capacity;
    size_t _reserveStep = GetAddingMem();

    size_t GetAddingMem()
    {
        size_t s;
        if (sizeof(inf) < 8) return s = 256;// 1 byte
        else if (sizeof(inf) < 256) return s = 64;// 8 bytes
        else if (sizeof(inf) < 4096) return s = 16;// 4 Kb
        else if (sizeof(inf) < 16384) return s = 4;// 16 Kb
        else if (sizeof(inf) < 131072) return s = 2;// 128 Kb
        else return s = 1; // >128 Kb
    }

    int reserve(size_t newSize)
    {
        if (newSize != 0)
        {
            size_t newCapacity = (newSize / _reserveStep + ((newSize % _reserveStep == 0) ? 0 : 1)) * _reserveStep;
            if (newCapacity != _capacity)
            {
                inf* newArr = (inf*)realloc(_arr, newCapacity * sizeof(inf));
                if (newArr != NULL)
                {
                    _capacity = newCapacity;
                    _arr = newArr;
                    return SUCCESS;
                }
                return FAIL;
            }
            return SUCCESS;
        }

        _arr = (inf*)realloc(_arr, 0);
        _capacity = 0;
        return SUCCESS;
    }

protected:
    int Resize(size_t newSize)
    {
        if (newSize < _size)
        {
            /*for (int i = newSize; i < size; i++)
            {
                (arr + i)->~inf();
            }*/
            _size = newSize;
            return reserve(newSize);
        }

        if (newSize > _capacity)
        {
            if (reserve(newSize) == FAIL)
            {
                return FAIL;
            }
        }

        /*for (size_t i = size; i < newSize; i++)
        {
            new (arr + i) inf();
        }*/
        _size = newSize;
        return SUCCESS;
    }

public:
    DynamicArray()
    {
        Resize(1);
    }

    DynamicArray(size_t userCapacity)
    {
        if (userCapacity)
        {
            Resize(userCapacity);
        }
        else
        {
            _size = 0;
            _capacity = 0;
        }
    }

    ~DynamicArray()
    {
        RemoveAll();
    }

    DynamicArray(const DynamicArray& other)
    {
        *this = other;
    }

    inf& operator [](size_t index)
    {
        /*if (index >= size)
        {
            throw std::exception("index out of range!");
        }*/
        return _arr[index];
    }

    bool operator!()
    {
        return _size == 0;
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this != &other)
        {
            this->_reserveStep = other._reserveStep;
            if (this->Resize(other._size))
            {
                for (size_t i = 0; i < other._size; i++)
                {
                    this->_arr[i] = other._arr[i];
                }
            }
        }
        return *this;
    }

    size_t GetSize()
    {
        return _size;
    }

    size_t GetCapacity()
    {
        return _capacity;
    }

    size_t GetReserveStep()
    {
        return _reserveStep;
    }

    void SetReserveStep(size_t newReserveStep)
    {
        _reserveStep = newReserveStep;
    }

    int PushBack(const inf& data)
    {
        if (Resize(_size + 1))
        {
            _arr[_size - 1] = data;
            return SUCCESS;
        }
        return FAIL;
    }

    int PushFront(const inf& data)
    {
        if (Resize(_size + 1))
        {
            for (int i = _size - 1; i > 0; i--)
            {
                _arr[i] = _arr[i - 1];
            }
            _arr[0] = data;
            return SUCCESS;
        }
        return FAIL;
    }

    int Search(const inf& target)
    {
        for (int i = 0; i < _size; i++)
        {
            if (_arr[i] == target)
            {
                return i;
            }
        }
        return NOT_FOUND;
    }

    int SearchBackward(const inf target)
    {
        for (int i = _size - 1; i >= 0; i--)
        {
            if (_arr[i] == target)
            {
                return i;
            }
        }
        return NOT_FOUND;
    }

    int Remove(const inf& target)
    {
        int targetIndex = Search(target);
        if (targetIndex == NOT_FOUND)
        {
            return FAIL;
        }

        for (size_t i = targetIndex; i < _size - 1; i++)
        {
            _arr[i] = _arr[i + 1];
        }
        Resize(_size - 1);
        return SUCCESS;
    }

    int RemoveAt(size_t index)
    {
        if (index < _size)
        {
            for (; index < _size - 1; index++)
            {
                _arr[index] = _arr[index + 1];
            }
            Resize(_size - 1);
            return SUCCESS;
        }
        return FAIL;
    }

    void RemoveAll()
    {
        Resize(0);
    }
};