#include <cstdlib>
#include <iostream>
#include "hashtable.cpp"
using namespace std;

template <typename K>
class HTLinear : public HashTable<K> {
    // IMPLEMENT ME
    K* table;
    int N;
    int count;
    
    public:
    HTLinear<K>(int n){
        this->N = n;
        table = (K*)malloc(n * sizeof(K));
        count = 0;
    }
    
    int hash_code(K key){
        return key;
    }
    
    int compress(int code){
        return ((59 * code + 17) % 509) % N;
    }
    
    int insert(K key){
        int i = this->hashfn(key);
        int counter = 0;
        
        if(count >= N){
            throw logic_error("Table already full");
        }
        
        int inTable = search(key);
        if(inTable != -1){
            throw logic_error("Already added key " + to_string(key));
        }
        count++;
        while(table[i] != 0){
            if(table[i] == -1){
                break;
            }
            i++;
            counter++;
            if(i == N){
                i = 0;
            }
        }
        
        table[i] = key;
        return counter;
    }
    
    int search(K key){
        int i = this->hashfn(key);
        int count = 0, loop = 0;
        while(table[i] != 0){
            if(table[i] == key){
                if(count > 0){
                    return count;
                } else {
                    return 0;
                }
            }
            count++;
            i++;
            if(loop == 2){
                break;
            }
            if(i == N){
                i = 0;
                loop++;
            }
        }
        
        return -1;
    }
    
    int remove(K key){
        int k = this->hashfn(key);
        int counter = 0;
        
        while(table[k] != 0){
            if(counter == N) return -1;
            if(table[k] == key){
                table[k] = -1;
                count--;
                if(counter > 0){
                    return counter;
                } else {
                    return 0;
                }
            }
            k++;
            counter++;
            if(k == N){
                k = 0;
            }
            if(k == k - 1){
                break;
            }
        }
        return -1;
    }
    
    void print(){
        for(int i = 0; i < N; i++){
            cout << i << "\t";
        }
        cout << endl;
        for(int i = 0; i < N; i++){
            if(table[i] == -1){
                cout << 0 << "\t";
            } else {
                cout << table[i] << "\t";
            }
            
        }
        cout << endl;
    }
};