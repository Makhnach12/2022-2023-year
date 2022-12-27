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
void poliz_expr(node* pos, vector<std::string>& _line, int& num_2, int& num_3);
void poliz_op(node* pos, vector<std::string>& _line, std::string& id, int& gg, int& type_id);
void poliz_end(node* pos, vector<std::string>& _line, int& num_of_args);
void cout_matrix(vector<vector<std::string>>& matr, ofstream& fout);

int poliz_program(node* pos, vector<vector<std::string>>& matr) {
	vector<std::string> _line;
	int num_of_args = 0;
	poliz_begin(pos-> arr[0], _line, num_of_args);
	matr.push_back(_line);
	_line.clear();
	num_of_args = 0;
	bool flag = 0;
	node* descr_node = pos->arr[1];
	while (1) {
		if (descr_node->arr.size() == 2) {
			poliz_descr(descr_node->arr[0], _line, num_of_args);
			_line.push_back(to_string(num_of_args));
			_line.push_back("DESCR");
			matr.push_back(_line);
			descr_node = descr_node->arr[1];
			_line.clear();
			num_of_args = 0;
		}
		else {
			poliz_descr(descr_node->arr[0], _line, num_of_args);
			_line.push_back(to_string(num_of_args));
			_line.push_back("DESCR");
			matr.push_back(_line);
			break;
		}
	}
	_line.clear();
	descr_node = pos->arr[2];
	std::string id;
	int gg = 0;
	int type_id = 0;
	while (1) {
		if (descr_node->arr.size() == 2) {
			poliz_op(descr_node->arr[0], _line, id, gg, type_id);
			if (gg == 1)
				return IMPLICT_COERCION;
			_line.push_back(id);
			_line.push_back("=");
			matr.push_back(_line);
			descr_node = descr_node->arr[1];
			_line.clear();
		}
		else {
			poliz_op(descr_node->arr[0], _line, id, gg, type_id);
			if (gg == 1)
				return IMPLICT_COERCION;
			_line.push_back(id);
			_line.push_back("=");
			matr.push_back(_line);
			break;
		}
	}
	_line.clear();
	num_of_args = 0;
	poliz_end(pos->arr[3], _line, num_of_args);
	matr.push_back(_line);
	if (matr[0][1] != matr[matr.size() - 1][1])
		return NOT_DETERMINATED_ID;
	return OK;
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

void poliz_expr(node* pos, vector<std::string>& _line, int& num_2, int& num_3) {
	if (pos == 0) return;
	if (pos->a == -1 and pos->el.lexem() != "(" and pos->el.lexem() != ")") {
		auto it = _line.begin();
		_line.push_back(pos->el.lexem());
		if (pos->el._int_lexem == 2)
			num_2 += 1;
		else if (pos->el._int_lexem == 3)
			num_3 += 1;
		else if (pos->el.lexem() == "RTOI") {
			num_3 -= 1;
			num_2 += 1;
		}
		else {
			num_3 += 1;
			num_2 -= 1;
		}
	}
	for (int i = pos->_size - 1; i > -1; i--) {
		if (pos->arr[i]->el.lexem() == "+" or pos->arr[i]->el.lexem() == "-") {
			std::string _lexem = pos->arr[i]->el.lexem();
			int line_size = _line.size();
			while (line_size - _line.size() == 0) {
				i -= 1;
				poliz_expr(pos->arr[i], _line, num_2, num_3);
			}
			if (num_2 == 2) {
				num_2 = 1;
			}
			else if (num_3 == 2) {
				num_3 = 1;
			}
			else {
				num_2 = 1000;
				num_3 = 1000;
			}
			_line.push_back(_lexem);
		}
		else
			poliz_expr(pos->arr[i], _line, num_2, num_3);
	}
}

void poliz_op(node* pos, vector<std::string>& _line, std::string& id, int& gg, int& type_id) {
	int num_2 = 0;
	int num_3 = 0;
	if (pos == 0) return;
	if (pos->a == 201) {
		poliz_expr(pos, _line, num_2, num_3);
		if (num_2 != 0 and num_3 != 0) {
			gg = 1;
		}
		else if (type_id == 2 and num_3 != 0) {
			gg = 1;
		}
		else if (type_id == 3 and num_2 != 0) {
			gg = 1;
		}
		return;
	}
	if (pos->a == -1 and pos->el.lexem() != "=") {
		id = pos->el.lexem();
		type_id = pos->el._int_lexem;
	}
	for (int i = 0; i < pos->_size; i++) {
		poliz_op(pos->arr[i], _line, id, gg, type_id);
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

void cout_matrix(vector<vector<std::string>>& matr, ofstream& fout){
	for (int i = 0; i < matr.size(); i++){
		for (int j = 0; j < matr[i].size(); j++){
			fout << matr[i][j] << " ";
		}
		fout << "\n";
	}
}



 
#endif