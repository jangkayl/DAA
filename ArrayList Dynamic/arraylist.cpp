// TODO entire implementation
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "list.h"
using namespace std;

class ArrayList : public List
{
    int _size;
    int capacity;
    int *arr;

    // T(n) = 9
    void increaseCap()
    {
        if (_size >= capacity)
        {
            capacity += ceil(capacity * .50);
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
    }

    // T(n) = 12
    void decreaseCap()
    {
        if (_size <= floor(capacity * (2 / 3.0)) && capacity > 5)
        {
            capacity -= floor(capacity * .25);
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
    }

public:
    // T(n) = 6
    ArrayList()
    {
        arr = (int *)calloc(capacity, sizeof(int));
        _size = 0;
        capacity = 5;
    }

    // T(n) = 12
    void insert(int num)
    {
        increaseCap();
        arr[_size] = num;
        _size++;
    }

    // T(n) = 3
    int get(int pos)
    {
        if (pos >= _size + 1)
        {
            throw logic_error("Invalid position");
        }

        return arr[pos - 1];
    }

    // T(n) =
    int remove(int num)
    {
        int posi = -1;

        for (int i = 0; i < _size; i++)
        {
            if (num == arr[i])
            {
                posi = i;
                for (int j = i; j < _size; j++)
                {
                    arr[j] = arr[j + 1];
                }
                break;
            }
        }

        if (posi == -1)
        {
            return 0;
        }

        _size--;
        decreaseCap();

        return posi + 1;
    }

    // T(n) = 8n + 3
    void print()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (arr[i] && i < _size)
            {
                cout << arr[i] << " ";
            }
            else
            {
                cout << "? ";
            }
        }
        cout << endl;
    }

    // T(n) = 1
    int size()
    {
        return _size;
    }

    // T(n) = 1
    bool isEmpty()
    {
        if (_size == 0)
        {
            return true;
        }
        return false;
    }

    // T(n) =
    void addAt(int num, int pos)
    {
        if (pos > capacity)
        {
            throw logic_error("Invalid position");
        }

        increaseCap();
        _size++;
        for (int i = _size; i >= pos; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[pos - 1] = num;
    }

    // T(n) = 6(n-i) + 18
    int removeAt(int pos)
    {
        if (pos > _size)
        {
            throw logic_error("Invalid position");
        }

        int num = arr[pos - 1];
        for (int i = pos - 1; i < _size; i++)
        {
            arr[i] = arr[i + 1];
        }
        _size--;
        decreaseCap();

        return num;
    }
};