// TODO entire implementation and add more header file/s as needed
#include <iostream>
#include <cmath>
#include "node.hpp"
#include "list.hpp"
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

    void insert(int num) {
        node* n = new node();
        n->num = num;
        if(!head){
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        _size++;
    }

    int get(int pos) {
        if(pos > _size || pos < 1) throw out_of_range("Invalid position");
        
        node* curr = head;
        int index = 0;
        
        while(curr){
            index++;
            if(index == pos){
                return curr->num;
            }
            curr = curr->next;
        }
        return 0;
    }

    int remove(int num) {
        node* curr = head;
        int pos = 0;
        
        while(curr){
            pos++;
            if(curr->num == num){
                if(curr->prev) curr->prev->next = curr->next;
                if(curr->next) curr->next->prev = curr->prev;
                if(head == curr) head = curr->next;
                if(tail == curr) tail = curr->prev;
                _size--;
                return pos;
            }
            curr = curr->next;
        }
        
        return 0;
    }

    void print() {
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

    int size() {
        return _size;
    }

    bool isEmpty() {
        return _size == 0;
    }

    void addAt(int num, int pos) {
        
        if (pos < 1 || pos > _size + 1) throw out_of_range("Invalid position");
        
        node* curr = head;
        node* newNode = new node();
        newNode->num = num;
        int position = 0;
        
        if(pos == 1){
            newNode->next = head;
            if(head) head->prev = newNode;
            head = newNode;
            if(isEmpty()) tail = newNode;
            _size++;
            return;
        }
        
        if(pos == _size+1){
            insert(newNode->num);
            return;
        }
        
        while(curr){
            position++;
            if(position == pos){
                _size++;
                if(curr->prev){
                     curr->prev->next = newNode;
                     newNode->prev = curr->prev;
                }
                curr->prev = newNode;
                newNode->next = curr;
                return;
            }
            curr = curr->next;
        }
        return;
    }

    int removeAt(int pos) {
        node* curr = head;
        int posi = 0, deleted = 0;
        
        if(pos > _size || pos < 1) throw out_of_range("Invalid position");
        
        while(curr){
            posi++;
            if(pos == posi){
                deleted = curr->num;
                remove(curr->num);
                return deleted;
            }
            curr = curr->next;
        }
        
        return 0;
    }
};