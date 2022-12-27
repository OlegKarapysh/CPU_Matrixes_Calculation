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
    inf* arr = nullptr;
    size_t size;
    size_t capacity;
    size_t reserveStep = addingMem();

    size_t addingMem()
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
            size_t newCapacity = (newSize / reserveStep + ((newSize % reserveStep == 0) ? 0 : 1)) * reserveStep;
            if (newCapacity != capacity)
            {
                inf* newArr = (inf*)realloc(arr, newCapacity * sizeof(inf));
                if (newArr != NULL)
                {
                    capacity = newCapacity;
                    arr = newArr;
                    return SUCCESS;
                }
                return FAIL;
            }
            return SUCCESS;
        }

        arr = (inf*)realloc(arr, 0);
        capacity = 0;
        return SUCCESS;
    }

protected:
    int Resize(size_t newSize)
    {
        if (newSize < size)
        {
            /*for (int i = newSize; i < size; i++)
            {
                (arr + i)->~inf();
            }*/
            size = newSize;
            return reserve(newSize);
        }

        if (newSize > capacity)
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
        size = newSize;
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
            size = 0;
            capacity = 0;
        }
    }

    ~DynamicArray()
    {
        removeAll();
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
        return arr[index];
    }

    bool operator!()
    {
        return size == 0;
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this != &other)
        {
            this->reserveStep = other.reserveStep;
            if (this->Resize(other.size))
            {
                for (size_t i = 0; i < other.size; i++)
                {
                    this->arr[i] = other.arr[i];
                }
            }
        }
        return *this;
    }

    size_t GetSize()
    {
        return size;
    }

    size_t GetCapacity()
    {
        return capacity;
    }

    size_t GetReserveStep()
    {
        return reserveStep;
    }

    void setReserveStep(size_t newReserveStep)
    {
        reserveStep = newReserveStep;
    }

    int pushBack(const inf& data)
    {
        if (Resize(size + 1))
        {
            arr[size - 1] = data;
            return SUCCESS;
        }
        return FAIL;
    }

    int pushFront(const inf& data)
    {
        if (Resize(size + 1))
        {
            for (int i = size - 1; i > 0; i--)
            {
                arr[i] = arr[i - 1];
            }
            arr[0] = data;
            return SUCCESS;
        }
        return FAIL;
    }

    int search(const inf& target)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == target)
            {
                return i;
            }
        }
        return NOT_FOUND;
    }

    int searchBackward(const inf target)
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (arr[i] == target)
            {
                return i;
            }
        }
        return -1;
    }

    int remove(inf& target)
    {
        int targetIndex = search(target);
        if (targetIndex != -1)
        {
            for (size_t i = targetIndex; i < size - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            Resize(size - 1);
            return SUCCESS;
        }
        return FAIL;
    }

    int removeAt(size_t index)
    {
        if (index < size)
        {
            for (; index < size - 1; index++)
            {
                arr[index] = arr[index + 1];
            }
            Resize(size - 1);
            return SUCCESS;
        }
        return FAIL;
    }

    void removeAll()
    {
        Resize(0);
    }
};