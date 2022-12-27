#include "hashtable.h"
#include "functions.h"
#include "syntax.h"
#include "syntax_anal.h"
#include "dka.h"
#include <string>
#include <iostream>
#include <fstream>
#include "poliz.h"

int main() {
	syntax_anal prog("input.txt");
	int status = prog.program();
	if (status != OK) {
		if (status == LEX_ERR) {
			cout << trans(status) << "\n";
			cout <<"Problem in that moment -> "<<  prog.lexem() << "\n";
			return 0;
		}
		else {
			cout << trans(status) << "\n";
			cout << "Problem in that moments -> " << prog.lexem2() << prog.lexem()<< "\n";
			return 0;
		}
	}
	node* a = prog.root();
	ofstream text("output2.txt");
	a->_print(a,0,text);
	ofstream text2("output3.txt");
	vector<vector<std::string>> matr;
	int cr = poliz_program(prog.root(), matr);
	if (cr == 1) {
		cout_matrix(matr, text2);
	}
	else
		cout << trans(cr);
	a->destroy(a);
	prog.table().displayHash("output.txt");
	return 0;
}