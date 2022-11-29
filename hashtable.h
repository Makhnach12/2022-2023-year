#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>
#include <string>
#include "comp_element.h"
using namespace std;

class HashTable
{
private:
    int _capacity;
    vector<element> _table;
public:
    int capacity() { return _capacity; }
    HashTable(){
        _capacity = 20000;
        _table.resize(20000);
    }
    void insert(element a)
    {
        int index = hashFunction(a.lexem()); // находим его индекс
        for (int i = index; i < _capacity; i++) {
            if (_table[i].lexem() == "") {
                _table[i] = a;
                return;
            }
            if (_table[i].lexem() == a.lexem())
                return;
        }
        _table.push_back(a);
    }

    void deleteId(element a)
    {
        int index = hashFunction(a.lexem());

        for (int i = index; i != _table.size(); i++)
        {
            if (_table[i].lexem() == a.lexem()) {
                _table[i].lexem() = " ";
                break;
            }
        }
    }

    int hashFunction(string word)
    {
        int h = 0;
        int C = 1013;
        for (int i = 0; i < word.size(); i++)
            h = (h * C + (int)word[i]) % _capacity;
        return h;
    }

    inline void displayHash()
    {
        for (int i = 0; i < _capacity; i++)
        {
            if (_table[i].lexem() != "") {
                cout << "table[" << i << "]";
                cout << " --> " << _table[i];
                cout << "\n";
            }
        }
    }

    inline void displayHash(string file_name)
    {
        ofstream out(file_name);
        for (int i = 0; i < _capacity; i++)
        {
            if (_table[i].lexem() != "") {
                out << "table[" << i << "]";
                out << " --> " << _table[i];
                out << "\n";
            }
        }
        out.close();
    }

};

#endif

