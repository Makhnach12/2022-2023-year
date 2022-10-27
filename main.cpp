#include "hashtable.h"
#include "functions.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
	ifstream fin("input.txt");
	HashTable matr(1003);
	std::string word;
	while (std::getline(fin, word)) {
		fill_table(word, matr);
	}
	matr.displayHash("output.txt");
	return 0;
}