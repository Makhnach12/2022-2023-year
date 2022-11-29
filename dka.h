#ifndef DKA_H
#define DKA_H
#include <iostream>
#include <vector>
#include <string>

class cell {
private:
	bool _fin_pos;
	std::string _status;
	int nodes[3];
public:
	cell(bool fin_pos, std::string status, int pos_1, int pos_2, int pos_3);
	bool fin_pos() { return _fin_pos; }
	std::string status() { return _status; }
	int get_next(char a);
};

class analizator {
private:
	std::vector<cell> matr;
public:
	analizator();
	std::string check_word(std::string word);
};

#endif
