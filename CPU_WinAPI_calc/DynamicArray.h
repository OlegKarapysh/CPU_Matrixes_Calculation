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

    void quickSort(inf* sortingArr, int sizeArr)
    {
        int i = 0;
        int j = sizeArr - 1;

        inf mid = sortingArr[sizeArr >> 1];

        do {
            while (sortingArr[i] < mid)
            {
                i++;
            }
            while (sortingArr[j] > mid)
            {
                j--;
            }
            if (i <= j)
            {
                inf tmp = sortingArr[i];
                sortingArr[i] = sortingArr[j];
                sortingArr[j] = tmp;
                i++;
                j--;
            }
        } while (i <= j);
        if (j > 0)
        {
            quickSort(sortingArr, j + 1);
        }
        if (i < sizeArr)
        {
            quickSort(sortingArr + i, sizeArr - i);
        }
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
    virtual int Resize(size_t newSize)
    {
        if (newSize < size)
        {
            for (int i = newSize; i < size; i++)
            {
                (arr + i)->~inf();
            }
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

        for (size_t i = size; i < newSize; i++)
        {
            new (arr + i) inf();
        }
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
    int SearchBinary(const inf& target, int left = 0, int right = -1)
    {
        if (size)
        {
            int midd = 0;
            if (-1 == right)
            {
                right = size - 1;
            }
            while (true)
            {
                midd = (left + right) >> 1;

                if (target < arr[midd])
                    right = midd - 1;
                else if (target > arr[midd])
                    left = midd + 1;
                else
                    return midd;

                if (left > right)
                    return -1;
            }
        }
        return NOT_FOUND;
    }

    int insertBinarySearch(const inf& target, int left = 0, int right = -1)
    {
        if (size)
        {
            int midd = 0;
            if (-1 == right)
            {
                right = size - 1;
            }
            while (true)
            {
                midd = (left + right) >> 1;

                if (target < arr[midd])
                {
                    right = midd - 1;
                }
                else if (target > arr[midd])
                {
                    left = midd + 1;
                }
                else
                {
                    return midd;
                }

                if (left > right)
                {
                    return left;
                }
            }
        }
        return 0;
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

    int removeIndex(size_t index)
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

    void sort()
    {
        if (size > 1)
        {
            quickSort(arr, size);
        }
    }

    int pushSorted(const inf& data)
    {
        if (Resize(size + 1))
        {
            if (0 == size - 1)
            {
                arr[0] = data;
                return SUCCESS;
            }
            else
            {
                int index = insertBinarySearch(data);
                if (size == index)
                {
                    arr[index - 1] = data;
                    return SUCCESS;
                }

                for (int i = size - 1; i > index; i--)
                {
                    arr[i] = arr[i - 1];
                }
                arr[index] = data;
                return SUCCESS;
            }
        }
        return FAIL;
    }

    int pushSortedForward(const inf& data)
    {
        if (Resize(size + 1))
        {
            for (size_t i = 0; i < size - 1; i++)
            {
                if (arr[i] >= data)
                {
                    for (int j = size - 1; j > i; j--)
                    {
                        arr[j] = arr[j - 1];
                    }
                    arr[i] = data;
                    return SUCCESS;
                }
            }
            arr[size - 1] = data;
            return SUCCESS;
        }
        return FAIL;
    }

    int pushSortedBackward(const inf& data)
    {
        if (Resize(size + 1))
        {
            int i;
            for (i = size - 2; i >= 0 && data < arr[i]; i--)
            {
                arr[i + 1] = arr[i];
            }
            arr[i + 1] = data;
            return SUCCESS;
        }
        return FAIL;
    }

    void placing(size_t index)
    {
        if (size > 1 && index < size)
        {
            inf temp = arr[index];
            int i;
            if (index)
            {
                i = index - 1;
                if (arr[i] > temp)
                {
                    for (i; i >= 0 && temp < arr[i]; i--)
                    {
                        arr[i + 1] = arr[i];
                    }
                    arr[i + 1] = temp;
                    return;
                }
            }

            for (i = index + 1; temp > arr[i] && i <= size - 1; i++)
            {
                arr[i - 1] = arr[i];
            }
            arr[i - 1] = temp;
        }
    }
};


