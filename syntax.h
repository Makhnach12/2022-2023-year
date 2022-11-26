#ifndef SYNTAX_H
#define SYNTAX_H
#define PROGRAM 1
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

#define OK 1

#include <iostream>
#include <fstream>
#include <string>
#include "dka.h"

int get_lexem(ifstream& fin, analizator& gg, HashTable& gg_2){
    char ch;
    fin.get(ch);
    std::string buffer;
    /* пропускаем все пробелы, табул€ции и символы новой строки */
    while (ch == ' ' || ch == '\n')
       fin.get(ch);

    if (ch == '(') {
        string word = "(";
        element a(word, "LPAREN");
        gg_2.insert(a);
        return LPAREN;
    }

    if (ch == ')') {
        string word = ")";
        element a(word, "RPAREN");
        gg_2.insert(a);
        return RPAREN;
    }

    if (ch == '=') {
        string word = "=";
        element a(word, "ASSIGN");
        gg_2.insert(a);
        return ASSIGN;
    }

    if (ch == ',') {
        string word = ",";
        element a(word, "APPERAND");
        gg_2.insert(a);
        return APPERAND;
    }

    if (ch == '+') {
        string word = "+";
        element a(word, "PLUS");
        gg_2.insert(a);
        return PLUS;
    }

    if (ch == '-') {
        string word = "-";
        element a(word, "MINUS");
        gg_2.insert(a);
        return MINUS;
    }

    /* сложный случай 3: идентификатор или ключевое слово */
    if (isalpha(ch) || ch == '_') {
        int i = 0;

        do {
            buffer += ch;
        } while ((fin.get(ch) && (isalpha(ch) || isdigit(ch)) && ch != ' '));
        fin.putback(ch);

        if ("PROGRAM" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            return PROGRAM;
        }

        if ("INTEGER" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            return INTEGER;
        }

        if ("REAL" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            return REAL;
        }

        if ("RTOI" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            return RTOI;
        }

        if ("ITOR" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            return ITOR;
        }

        if ("END" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            return END;
        }

        if (gg.check_word(buffer) == "id")
            return ID;
        else
            return LEX_ERR;
    }

    /* сложный случай 4: число */
    if (isdigit(ch)) {
        int i = 0;
        do {
            buffer += ch;
        } while ((fin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='.') && ch != ' '));
        fin.putback(ch);
        string stat = gg.check_word(buffer);
        if (stat== "realDig")
            return REALDIG;
        else if (stat == "intDig")
            return INTDIG;
    }

    return LEX_ERR;
}
#endif