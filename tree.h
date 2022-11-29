#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <string>
#include "comp_element.h"
#include "syntax_anal.h"
#include "checker.h"
using namespace std;

class node{
public:
	int a;
	element el;
	int _size;
	vector<node*> arr;
	node* parent;

	node(int _a) {
		a = _a;
		parent = nullptr;
	}

	node(element _el) {
		a = -1;
		el = _el;
		parent = nullptr;
	}

	inline node* add(node* __node, int _a) {
		node* govno = new node(_a);
		__node->arr.push_back(govno);
		__node->_size++;
		govno->parent = __node;
		return govno;
	}

	inline node* add(node* __node, element& _a) {
		node* govno = new node(_a);
		__node->arr.push_back(govno);
		__node->_size++;
		govno->parent = __node;
		return govno;
	}

	inline void _print(node* pos, int level) {
		if (pos == 0) return;
		for (int i = 0; i < level; i++)
			cout << ' ';
		if (pos->a != -1)
			cout << trans(pos->a) << '\n';
		else
			cout << pos->el << "\n";
		for (int i = 0; i < pos->_size; i++) {
			_print(pos->arr[i], level + 1);
		}
	}

	inline void _print(node* pos, int level, ofstream& fout) {
		if (pos == 0) return;
		for (int i = 0; i < level; i++)
			fout << ' ';
		if (pos->a != -1)
			fout << trans(pos->a) << '\n';
		else
			fout << pos->el << "\n";
		for (int i = 0; i < pos->_size; i++) {
			_print(pos->arr[i], level + 1, fout);
		}
	}

	void destroy(node* pos) {
		for (int i = 0; i < pos->_size; i++) {
			destroy(pos->arr[i]);
		}
		delete pos;
	}
};
#endif
