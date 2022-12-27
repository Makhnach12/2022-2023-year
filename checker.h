#ifndef CHECKER_H
#define CHECKER_H
#include <string>
#include <iostream>

#define PROGRAM 7
#define INTEGER 2
#define REAL 3
#define RTOI 4
#define ITOR 5
#define END 6

#define LPAREN 11    /* ( */
#define RPAREN 12   /* ) */
#define ASSIGN 13  /* = */
#define PLUS 14 /* + */
#define MINUS 18 /* - */
#define APPERAND 19 /* , */

#define REALDIG 101
#define INTDIG 102
#define ID 103

#define SYN_ERR 301
#define LEX_ERR 302

#define EXPECTED_IDENTIFIER 111
#define EXPECTED_ASSIGN 112
#define EXPECTED_SEPARATOR 113
#define EXPECTED_RPAREN 114
#define EXPECTED_LPAREN 115
#define UNRECOGNIZED_STATEMENT 116
#define EXPECTED_DESCRIPTION 117
#define EXPECTED_APPERAND 118
#define EXPECTED_PROGRAM 119
#define SUP_RPAREN 120
#define SUP_ASSIGN 121
#define NOT_DETERMINATED_ID 122

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
#define EXPECTED_END 210

#define OK 1
std::string trans(int num) {
	switch (num) {
	case EXPECTED_IDENTIFIER:
		return "EXPECTED IDENTIFIER";
	case EXPECTED_ASSIGN:
		return "EXPECTED ASSIGN";
	case EXPECTED_SEPARATOR:
		return "EXPECTED SEPARATOR";
	case EXPECTED_RPAREN:
		return "EXPECTED RPAREN";
	case EXPECTED_LPAREN:
		return "EXPECTED LPAREN";
	case UNRECOGNIZED_STATEMENT:
		return "UNRECOGNIZED STATEMENT";
	case EXPECTED_DESCRIPTION:
		return "EXPECTED DESCRIPTION";
	case EXPECTED_APPERAND:
		return "EXPECTED APPERAND";
	case EXPECTED_PROGRAM:
		return "EXPECTED PROGRAM";
	case SUP_RPAREN:
		return "EXTRA RPAREN";
	case SUP_ASSIGN:
		return "EXTRA ASSIGN";
	case LEX_ERR:
		return "LEXICAL ERROR";
	case ID:
		return "ID";
	case TYPE:
		return "TYPE";
	case EXPR:
		return "EXPR";
	case SEXPR:
		return "SIMPLE EXPR";
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
		return "VARLIST";
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
		return "LEFT BRACKET";
	case RPAREN:
		return "RIGHT BRACKET";
	case INTDIG:
		return "INT NUM";
	case REALDIG:
		return "REAL NUM";
	case END:
		return "END";
	case EXPECTED_END:
		return "EXPECTED_END";
	case NOT_DETERMINATED_ID:
		return "NOT_DETERMINATED_ID";
	default:
		return "OK";
	}
}

#endif
