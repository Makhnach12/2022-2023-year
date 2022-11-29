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
    vector<element>* _table;
public:
    int capacity() { return _capacity; }
    HashTable(){
        _capacity = 20000;
        _table = new vector<element>[20000];
    }
    void insert(element a)
    {
        bool flag = 0;
        int index = hashFunction(a.lexem());
        for (int i = 0; i < _table[index].size(); i++)
            if (a.lexem() == _table[index][i].lexem())
                flag = 1;
        if (!flag)
            _table[index].push_back(a);
    }
    void deleteId(element a)
    {
        int index = hashFunction(a.lexem());

        for (int i = 0; i != _table[index].size(); i++)
        {
            if (_table[index][i].lexem() == a.lexem()) {
                _table[index].erase(_table[index].begin() + i);
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
            if (_table[i].size() != 0) {
                cout << "table[" << i << "]";
                for (auto x : _table[i])
                    cout << " --> " << x;
                cout << "\n";
            }
        }
    }

    inline void displayHash(string file_name)
    {
        ofstream out(file_name);
        for (int i = 0; i < _capacity; i++)
        {
            if (_table[i].size() != 0) {
                out << "table[" << i << "]";
                for (auto x : _table[i])
                    out << " --> " << x;
                out << "\n";
            }
        }
        out.close();
    }

};

#endif

