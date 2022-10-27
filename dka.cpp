#include "dka.h"

node::node(bool fin_pos, std::string status, int pos_1, int pos_2, int pos_3) {
	_fin_pos = fin_pos;
	_status = status;
	nodes[0] = pos_1;
	nodes[1] = pos_2;
	nodes[2] = pos_3;
}

int node::get_next(char a) {
	if ((int)a <= 57 && (int)a >= 48)
		return nodes[0];
	else if ((int)a >= 65 && (int)a <= 90 || (int)a >= 97 && (int)a <= 122)
		return nodes[1];
	else if ((int)a == 46)
		return nodes[2];
	else
		return -1;
}

analizator::analizator() {
	node q0(0, "not_determinated", 1, 2, 4);
	matr.push_back(q0);
	node q1(1, "intDig", 1, 4, 3);
	matr.push_back(q1);
	node q2(1, "id", 4, 2, 4);
	matr.push_back(q2);
	node q3(1, "realDig", 3, 4, 4);
	matr.push_back(q3);
	node q4(0, "not_determinated", 4, 4, 4);
	matr.push_back(q4);
}

std::string analizator::check_word(std::string word) {
	int k = 0;
	for (char it : word) {
		k = matr[k].get_next(it);
		if (k == -1)
			return "not_determinated";
	}
	return matr[k].status();
}