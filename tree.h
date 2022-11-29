#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>
#include <string>
#include "comp_element.h"
#include "syntax_anal.h"
using namespace std;

#define TYPE 200
#define EXPR 201
#define SEXPR 202
#define DESCRIPTION 203
#define DESCR 204
#define OPERS 205
#define OP 206
#define BEGIN 207
#define FUNCTION 208
#define VAR_LIST 209

class node{
private:
	string trans(int num) {
		switch (num) {
		case EXPECTED_IDENTIFIER:
			return "EXPECTED_IDENTIFIER";
		case EXPECTED_ASSIGN:
			return "EXPECTED_ASSIGN";
		case EXPECTED_SEPARATOR:
			return "EXPECTED_SEPARATOR";
		case EXPECTED_RPAREN:
			return "EXPECTED_RPAREN";
		case EXPECTED_LPAREN:
			return "EXPECTED_LPAREN";
		case UNRECOGNIZED_STATEMENT:
			return "UNRECOGNIZED_STATEMENT";
		case EXPECTED_DESCRIPTION:
			return "EXPECTED_DESCRIPTION";
		case EXPECTED_APPERAND:
			return "EXPECTED_APPERAND";
		case EXPECTED_PROGRAM:
			return "EXPECTED_PROGRAM";
		case SUP_RPAREN:
			return "SUP_RPAREN";
		case SUP_ASSIGN:
			return "SUP_ASSIGN";
		case LEX_ERR:
			return "LEX_ARR";
		case ID:
			return "ID";
		case TYPE:
			return "TYPE";
		case EXPR:
			return "EXPR";
		case SEXPR:
			return "SEXPR";
		case DESCRIPTION:
			return "DESCRIPTION";
		case DESCR:
			return "DESCR";
		case OPERS:
			return "OPERATORS";
		case OP:
			return "OP";
		case BEGIN:
			return "BEGIN";
		case FUNCTION:
			return "FUNCTION";
		case VAR_LIST:
			return "VAR_LIST";
		case INTEGER:
			return "INTEGER";
		case PROGRAM:
			return "PROGRAM";
		case APPERAND:
			return "APPERAND";
		case PLUS:
			return "PLUS";
		case MINUS:
			return "MINUS";
		case ASSIGN:
			return "ASSIGN";
		case LPAREN:
			return "LPAREN";
		case RPAREN:
			return "RPAREN";
		case INTDIG:
			return "INTDIG";
		case REALDIG:
			return "REALDIG";
		case END:
			return "END";
		default:
			return "OK";
		}
	}
public:
	int a;
	int _size;
	vector<node*> arr;
	node* parent;

	node(int _a) {
		a = _a;
		parent = nullptr;
	}
	node* add(node* __node, int a) {
		node* govno = new node(a);
		__node->arr.push_back(govno);
		__node->_size++;
		govno->parent = __node;
		return govno;
	}

	void _print(node* pos, int level) {
		if (pos == 0) return;
		for (int i = 0; i < level; i++)
			cout << ' ';
		cout << trans(pos->a) << '\n';
		for (int i = 0; i < pos->_size; i++) {
			_print(pos->arr[i], level + 1);
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
