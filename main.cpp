#include "hashtable.h"
#include "functions.h"
#include "syntax.h"
#include "syntax_anal.h"
#include "dka.h"
#include <string>
#include <iostream>
#include <fstream>

int main() {
	syntax_anal prog("input.txt");
	cout << trans(prog.program()) << "\n";
	node* a = prog.root();
	a->_print(a,0);
	a->destroy(a);
	prog.table().displayHash();
	return 0;
}