#include "hashtable.cpp"
#include "linkedlist.cpp"
#include <stdexcept>
#include <iostream>
using namespace std;

class HTSepChain : public HashTable
{
private:
    LinkedList *table;
    int N;

public:
    HTSepChain(int capacity)
    {
        N = capacity;
        table = new LinkedList[N];
    }

    int insert(string key) override
    {
        int hashCode = hashfn(key);
        int index = compress(hashCode);

        if (table[index].search(key))
        {
            throw runtime_error("Already added key " + key);
        }

        table[index].insert(key);
        return table[index].count();
    }

    int search(string key) override
    {
        int hashCode = hashfn(key);
        int index = compress(hashCode);

        if (table[index].search(key))
        {
            return table[index].count();
        }
        else
        {
            return -1;
        }
    }

    int remove(string key) override
    {
        int hashCode = hashfn(key);
        int index = compress(hashCode);

        if (table[index].remove(key))
        {
            return table[index].count();
        }
        else
        {
            return -1;
        }
    }

    void print() override
    {
        for (int i = 0; i < N; i++)
        {
            cout << i << "\t";
            table[i].print();
            cout << endl;
        }
        cout << endl;
    }

    int hash_code(string key) override
    {
        int hashValue = 0;
        int a = 5;
        for (int i = 0; i < key.length(); i++)
        {
            hashValue = (hashValue * a + key[i]) % 1000000007;
        }
        return hashValue;
    }

    int compress(int code) override
    {
        return code % N;
    }
};
