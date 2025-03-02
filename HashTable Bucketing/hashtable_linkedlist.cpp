#include <iostream>
#include <functional>

using namespace std;

const int TABLE_SIZE = 10;

template <typename K, typename V>
class HashTable
{
private:
    struct Node
    {
        K key;
        V value;
        Node *next;

        Node(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    Node **table;

    int hashFunction(K key)
    {
        return hash<K>{}(key) % TABLE_SIZE;
    }

public:
    HashTable()
    {
        table = new Node *[TABLE_SIZE](); // Initialize with nullptr
    }

    void insert(K key, V value)
    {
        int index = hashFunction(key);
        Node *newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    V *search(K key)
    {
        int index = hashFunction(key);
        Node *current = table[index];
        while (current)
        {
            if (current->key == key)
            {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove(K key)
    {
        int index = hashFunction(key);
        Node *current = table[index];
        Node *prev = nullptr;

        while (current)
        {
            if (current->key == key)
            {
                if (prev)
                {
                    prev->next = current->next;
                }
                else
                {
                    table[index] = current->next;
                }
                delete current;
                cout << "Removed successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Key not found.\n";
    }

    void display()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << "[" << i << "] ";
            Node *current = table[i];
            while (current)
            {
                cout << "(" << current->key << " -> " << current->value << ") ";
                current = current->next;
            }
            cout << "\n";
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            Node *current = table[i];
            while (current)
            {
                Node *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
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
