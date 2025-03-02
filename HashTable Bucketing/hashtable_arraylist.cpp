#include <iostream>
#include <vector>
#include <functional>

using namespace std;

const int TABLE_SIZE = 10;

template <typename K, typename V>
class HashTable
{
private:
    struct Bucket
    {
        vector<K> keys;
        vector<V> values;
    };

    Bucket table[TABLE_SIZE];

    int hashFunction(K key)
    {
        return hash<K>{}(key) % TABLE_SIZE;
    }

public:
    void insert(K key, V value)
    {
        int index = hashFunction(key);
        table[index].keys.push_back(key);
        table[index].values.push_back(value);
    }

    V *search(K key)
    {
        int index = hashFunction(key);
        for (size_t i = 0; i < table[index].keys.size(); i++)
        {
            if (table[index].keys[i] == key)
            {
                return &table[index].values[i];
            }
        }
        return nullptr;
    }

    void remove(K key)
    {
        int index = hashFunction(key);
        for (size_t i = 0; i < table[index].keys.size(); i++)
        {
            if (table[index].keys[i] == key)
            {
                table[index].keys.erase(table[index].keys.begin() + i);
                table[index].values.erase(table[index].values.begin() + i);
                return;
            }
        }
    }

    void display()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << "[" << i << "] ";
            for (size_t j = 0; j < table[i].keys.size(); j++)
            {
                cout << "(" << table[i].keys[j] << " -> " << table[i].values[j] << ") ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    HashTable<int, string> hashTable;
    int choice;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int key;
            string value;
            cout << "Enter key (integer): ";
            cin >> key;
            cout << "Enter value (string): ";
            cin >> value;
            hashTable.insert(key, value);
        }
        else if (choice == 2)
        {
            int key;
            cout << "Enter key to search: ";
            cin >> key;
            string *result = hashTable.search(key);
            if (result)
            {
                cout << "Found: " << *result << "\n";
            }
            else
            {
                cout << "Not Found\n";
            }
        }
        else if (choice == 3)
        {
            int key;
            cout << "Enter key to remove: ";
            cin >> key;
            hashTable.remove(key);
            cout << "Removed successfully.\n";
        }
        else if (choice == 4)
        {
            cout << "Current Hash Table:\n";
            hashTable.display();
        }
        else if (choice == 5)
        {
            cout << "Exiting...\n";
            break;
        }
        else
        {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
