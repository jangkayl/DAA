#include "node.cpp"
#include <iostream>
using namespace std;

class LinkedList
{
private:
    node *head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    void insert(string elem)
    {
        node *newNode = new node;
        newNode->elem = elem;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool remove(string elem)
    {
        node *current = head;
        node *previous = nullptr;

        while (current != nullptr)
        {
            if (current->elem == elem)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool search(string elem)
    {
        node *current = head;
        while (current != nullptr)
        {
            if (current->elem == elem)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int count()
    {
        int count = 0;
        node *current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    void print()
    {
        node *current = head;
        while (current != nullptr)
        {
            cout << current->elem << "\t";
            current = current->next;
        }
    }
};
