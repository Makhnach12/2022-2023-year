#include "functions.h"
#include "dka.h"
#include "hashtable.h"
#include <vector>
#include <string>

analizator anal;
std::vector<char> opers = {'+','-','=','(',')',','};
std::vector<char> space = { ' ' };
std::vector<std::string> keywords = { "PROGRAM","END","INTEGER","REAL","ITOR","RTOI" };

void fill_table(std::string str, HashTable& matr) {
	std::string word = "";
	for (char ind : str) {
		bool is_space = find(space.begin(), space.end(), ind) != space.end();
		bool is_oper = find(opers.begin(), opers.end(), ind) != opers.end();
		if (is_space || is_oper) {
			if (is_oper) {
				string a;
				a += ind;
				element sep(a,"SEPARATOR");
				matr.insert(sep);
			}
			if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
				element a(word,"KEYWORD");
				matr.insert(a);
				word = "";
			}
			else if (word != "") {
				std::string name = anal.check_word(word);
				element a(word,name);
				matr.insert(a);
				word = "";
			}
		}
		else
			word += ind;
	}
	if (word != "") {
		if (find(keywords.begin(), keywords.end(), word) != keywords.end()) {
			element a(word,"KEYWORD");
			matr.insert(a);
			word = "";
		}
		else {
			std::string name = anal.check_word(word);
			element a(word,name);
			matr.insert(a);
			word = "";
		}
	}
}