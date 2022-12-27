#ifndef POLIZ_H
#define POLIZ_H
#include "hashtable.h"
#include "syntax.h"
#include "checker.h"
#include "dka.h"
#include <string>
#include <iostream>
#include <fstream>
#include "tree.h"
#include "comp_element.h"

vector<vector<std::string>> descrs;
void poliz_begin(node* pos, vector<std::string>& _line, int& num_of_args);
void poliz_descr(node* pos, vector<std::string>& _line, int& num_of_args);
void poliz_expr(node* pos, vector<std::string>& _line);
void poliz_op(node* pos, vector<std::string>& _line, std::string& id);
void poliz_end(node* pos, vector<std::string>& _line, int& num_of_args);

void poliz_program(node* pos, ofstream& fout) {
	vector<std::string> _line;
	int num_of_args = 0;
	poliz_begin(pos-> arr[0], _line, num_of_args);
	for (int i = 0; i < _line.size(); i++) {
		fout << _line[i] << " ";
	}
	fout << "\n";
	_line.clear();
	num_of_args = 0;
	bool flag = 0;
	node* descr_node = pos->arr[1];
	while (1) {
		if (descr_node->arr.size() == 2) {
			poliz_descr(descr_node->arr[0], _line, num_of_args);
			for (int i = 0; i < _line.size(); i++) {
				fout << _line[i] << " ";
			}
			fout << num_of_args - 1 << " " << "DESCR\n";
			descr_node = descr_node->arr[1];
			_line.clear();
			num_of_args = 0;
		}
		else {
			poliz_descr(descr_node->arr[0], _line, num_of_args);
			for (int i = 0; i < _line.size(); i++) {
				fout << _line[i] << " ";
			}
			fout << num_of_args - 1 << " " << "DESCR\n";
			break;
		}
	}
	_line.clear();
	descr_node = pos->arr[2];
	std::string id;
	while (1) {
		if (descr_node->arr.size() == 2) {
			poliz_op(descr_node->arr[0], _line, id);
			_line.push_back(id);
			_line.push_back("=");
			for (int i = 0; i < _line.size(); i++) {
				fout << _line[i] << " ";
			}
			descr_node = descr_node->arr[1];
			_line.clear();
			fout << "\n";
		}
		else {
			poliz_op(descr_node->arr[0], _line, id);
			_line.push_back(id);
			_line.push_back("=");
			for (int i = 0; i < _line.size(); i++) {
				fout << _line[i] << " ";
			}
			fout << "\n";
			break;
		}
	}
	_line.clear();
	num_of_args = 0;
	poliz_end(pos->arr[3], _line, num_of_args);
	for (int i = 0; i < _line.size(); i++) {
		fout << _line[i] << " ";
	}
	fout << "\n";
}

void poliz_begin(node* pos, vector<std::string>& _line, int& num_of_args) {
	if (pos == 0) return;
	if (pos->a == -1) {
		_line.push_back(pos->el.lexem());
		num_of_args++;
	}
	for (int i = 0; i < pos->_size; i++) {
		poliz_begin(pos->arr[i], _line, num_of_args);
	}
	if (pos->a == 207) {
		_line.push_back(to_string(num_of_args));
		_line.push_back("FUNCTION");
	}
}

void poliz_descr(node* pos, vector<std::string>& _line, int& num_of_args) {
	if (pos == 0) return;
	if (pos->a == -1 and pos->el.lexem() != ",") {
		auto it = _line.begin();
		_line.insert(it, pos->el.lexem());
		num_of_args++;
	}
	for (int i = 0; i < pos->_size; i++) {
		poliz_descr(pos->arr[i], _line, num_of_args);
	}
}

void poliz_expr(node* pos, vector<std::string>& _line) {
	if (pos == 0) return;
	if (pos->a == -1 and pos->el.lexem() != "(" and pos->el.lexem() != ")") {
		auto it = _line.begin();
		_line.push_back(pos->el.lexem());
	}
	for (int i = pos->_size - 1; i > -1; i--) {
		if (pos->arr[i]->el.lexem() == "+" or pos->arr[i]->el.lexem() == "-") {
			std::string _lexem = pos->arr[i]->el.lexem();
			int line_size = _line.size();
			while (line_size - _line.size() == 0) {
				i -= 1;
				poliz_expr(pos->arr[i], _line);
			}
			_line.push_back(_lexem);
		}
		else
			poliz_expr(pos->arr[i], _line);
	}
}

void poliz_op(node* pos, vector<std::string>& _line, std::string& id) {
	if (pos == 0) return;
	if (pos->a == 201) {
		poliz_expr(pos, _line);
		return;
	}
	if (pos->a == -1 and pos->el.lexem() != "=") {
		id = pos->el.lexem();
	}
	for (int i = 0; i < pos->_size; i++) {
		poliz_op(pos->arr[i], _line, id);
	}
}

void poliz_end(node* pos, vector<std::string>& _line, int& num_of_args) {
	if (pos == 0) return;
	if (pos->a == -1) {
		_line.push_back(pos->el.lexem());
		num_of_args++;
	}
	for (int i = 0; i < pos->_size; i++) {
		poliz_end(pos->arr[i], _line, num_of_args);
	}
	if (pos->a == 6) {
		_line.push_back(to_string(num_of_args));
		_line.push_back("FUNCTION_END");
	}
}


 
#endif