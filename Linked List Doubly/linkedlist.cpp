// TODO entire implementation and add more header file/s as needed
#include <iostream>
#include <cmath>
#include "node.cpp"
#include "list.cpp"
using namespace std;

class LinkedList : public List {
    int _size;
    node* head;
    node* tail;

public:
    LinkedList(){
        _size = 0;
        head = NULL;
        tail = NULL;
    }

    void insert(int num) override {
        node* n = new node(num);
        if (!head) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        _size++;
    }

    int get(int pos) override {
        if (pos < 1 || pos > _size) throw out_of_range("Invalid position");
        node* curr = (pos <= _size / 2) ? head : tail;
        int index = (pos <= _size / 2) ? 1 : _size;
        while (curr) {
            if (index == pos) return curr->num;
            curr = (pos <= _size / 2) ? curr->next : curr->prev;
            index += (pos <= _size / 2) ? 1 : -1;
        }
        return -1;
    }

    int remove(int num) override {
        node* curr = head;
        int pos = 1;
        while (curr) {
            if (curr->num == num) {
                if (curr == head) head = head->next;
                if (curr == tail) tail = tail->prev;
                if (curr->prev) curr->prev->next = curr->next;
                if (curr->next) curr->next->prev = curr->prev;
                delete curr;
                _size--;
                return pos;
            }
            curr = curr->next;
            pos++;
        }
        return 0;
    }

    void print() override {
        if (!head) {
            cout << "FROM HEAD: (none)\nFROM TAIL: (none)\n";
            return;
        }
        cout << "FROM HEAD: ";
        node* curr = head;
        while (curr) {
            cout << curr->num;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\nFROM TAIL: ";
        curr = tail;
        while (curr) {
            cout << curr->num;
            if (curr->prev) cout << " <- ";
            curr = curr->prev;
        }
        cout << endl;
    }

    int size() override {
        return _size;
    }

    bool isEmpty() override {
        return _size == 0;
    }

    void addAt(int num, int pos) override {
        if (pos < 1 || pos > _size + 1) throw out_of_range("Invalid position");
        node* n = new node(num);
        if (pos == 1) {
            n->next = head;
            if (head) head->prev = n;
            head = n;
            if (!_size) tail = n;
        } else if (pos == _size + 1) {
            insert(num);
            return;
        } else {
            node* curr = (pos <= _size / 2) ? head : tail;
            int index = (pos <= _size / 2) ? 1 : _size;
            while (curr) {
                if (index == pos) break;
                curr = (pos <= _size / 2) ? curr->next : curr->prev;
                index += (pos <= _size / 2) ? 1 : -1;
            }
            n->prev = curr->prev;
            n->next = curr;
            curr->prev->next = n;
            curr->prev = n;
        }
        _size++;
    }

    int removeAt(int pos) override {
        if (pos < 1 || pos > _size) throw out_of_range("Invalid position");
        node* curr = (pos <= _size / 2) ? head : tail;
        int index = (pos <= _size / 2) ? 1 : _size;
        while (curr) {
            if (index == pos) break;
            curr = (pos <= _size / 2) ? curr->next : curr->prev;
            index += (pos <= _size / 2) ? 1 : -1;
        }
        int removedVal = curr->num;
        if (curr == head) head = head->next;
        if (curr == tail) tail = tail->prev;
        if (curr->prev) curr->prev->next = curr->next;
        if (curr->next) curr->next->prev = curr->prev;
        delete curr;
        _size--;
        return removedVal;
    }
};
