#ifndef SYNTAX_H
#define SYNTAX_H
#include <iostream>
#include <fstream>
#include <string>
#include "dka.h"
#include "checker.h"

int get_lexem(ifstream& fin, analizator& gg, HashTable& gg_2, element& el){
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
        element a(word, "LPAREN");
        el = a;
        gg_2.insert(a);
        return LPAREN;
    }
    if (ch == ')') {
        string word = ")";
        element a(word, "RPAREN");
        el = a;
        gg_2.insert(a);
        return RPAREN;
    }

    if (ch == '=') {
        string word = "=";
        element a(word, "ASSIGN");
        el = a;
        gg_2.insert(a);
        return ASSIGN;
    }

    if (ch == ',') {
        string word = ",";
        element a(word, "APPERAND");
        el = a;
        gg_2.insert(a);
        return APPERAND;
    }

    if (ch == '+') {
        string word = "+";
        element a(word, "PLUS");
        el = a;
        gg_2.insert(a);
        return PLUS;
    }

    if (ch == '-') {
        string word = "-";
        element a(word, "MINUS");
        el = a;
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
            el = a;
            return PROGRAM;
        }

        if ("INTEGER" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return INTEGER;
        }

        if ("REAL" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return REAL;
        }

        if ("RTOI" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return RTOI;
        }

        if ("ITOR" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return ITOR;
        }

        if ("END" == buffer) {
            element a(buffer, "KEYWORD");
            gg_2.insert(a);
            el = a;
            return END;
        }

        if (gg.check_word(buffer) == "id") {
            element a(buffer, "id");
            el = a;
            gg_2.insert(a);
            return ID;
        }
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
        if (stat == "realDig") {
            element a(buffer, "REAL NUM");
            el = a;
            gg_2.insert(a);
            return REALDIG;
        }
        else if (stat == "intDig") {
            element a(buffer, "INT NUM");
            el = a;
            gg_2.insert(a);
            return INTDIG;
        }
    }

    return LEX_ERR;
}
#endif