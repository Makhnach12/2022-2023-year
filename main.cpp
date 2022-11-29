#include "hashtable.h"
#include "functions.h"
#include "syntax.h"
#include "syntax_anal.h"
#include "dka.h"
#include <string>
#include <iostream>
#include <fstream>

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
	default:
		return "OK";
	}
}

int main() {
	syntax_anal govno("input.txt");
	cout<< trans(govno.program()) << "\n";
	node* a = govno.root();
	a->_print(a,0);
	a->destroy(a);
	return 0;
}