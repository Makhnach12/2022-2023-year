#ifndef SYNTAX_H
#define SYNTAX_H
#include <iostream>
#include <fstream>
#include <string>
#include "dka.h"
#include "checker.h"

int get_lexem(ifstream& fin, analizator& gg, HashTable& gg_2, element& el, int type_int){
    char ch;
    fin.get(ch);
    std::string buffer;
    if ((int)ch == -52)
        return LEX_ERR;
    /* пропускаем все пробелы, табул€ции и символы новой строки */
    while (ch == ' ' || ch == '\n')
       fin.get(ch);
    if (ch == '(') {
        string word = "(";
        element a(word, "LPAREN", LPAREN);
        el = a;
        return LPAREN;
    }
    if (ch == ')') {
        string word = ")";
        element a(word, "RPAREN", RPAREN);
        el = a;
        return RPAREN;
    }

    if (ch == '=') {
        string word = "=";
        element a(word, "ASSIGN", ASSIGN);
        el = a;
        return ASSIGN;
    }

    if (ch == ',') {
        string word = ",";
        element a(word, "APPERAND", APPERAND);
        el = a;
        return APPERAND;
    }

    if (ch == '+') {
        string word = "+";
        element a(word, "PLUS", PLUS);
        el = a;
        return PLUS;
    }

    if (ch == '-') {
        string word = "-";
        element a(word, "MINUS", MINUS);
        el = a;
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
            element a(buffer, "KEYWORD", PROGRAM);
            el = a;
            return PROGRAM;
        }

        if ("INTEGER" == buffer) {
            element a(buffer, "KEYWORD", INTEGER);
            el = a;
            return INTEGER;
        }

        if ("REAL" == buffer) {
            element a(buffer, "KEYWORD", REAL);
            el = a;
            return REAL;
        }

        if ("RTOI" == buffer) {
            element a(buffer, "KEYWORD", RTOI);
            el = a;
            return RTOI;
        }

        if ("ITOR" == buffer) {
            element a(buffer, "KEYWORD", ITOR);
            gg_2.insert(a);
            el = a;
            return ITOR;
        }

        if ("END" == buffer) {
            element a(buffer, "KEYWORD", END);
            el = a;
            return END;
        }

        if (gg.check_word(buffer) == "id") {
            element a(buffer, "id", type_int);
            el = a;
            return ID;
        }
        else {
            element a(buffer, "LEX_ERR");
            el = a;
            return LEX_ERR;
        }
    }

    /* сложный случай 4: число */
    if (isdigit(ch)) {
        int i = 0;
        do {
            buffer += ch;
        } while ((fin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='.') && ch != ' '));
        fin.putback(ch);
        string stat = gg.check_word(buffer);
        if (stat == "realDig") {
            element a(buffer, "REAL NUM", REAL);
            el = a;
            return REALDIG;
        }
        else if (stat == "intDig") {
            element a(buffer, "INT NUM", INTEGER);
            el = a;
            return INTDIG;
        }
        element a(buffer, "LEX_ERR", LEX_ERR);
        el = a;
    }

    return LEX_ERR;
}
#endif