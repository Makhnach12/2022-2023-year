#include "hashtable.h"
#include "syntax.h"
#include "dka.h"
#include <string>
#include <iostream>
#include <fstream>

analizator gg;
//int statement(std::ifstream& stream);
int description(std::ifstream& stream, int _pref, HashTable& gg_2);
int expression(std::ifstream& stream, int& pref, int& flag_lparen, int& flag_rparen, HashTable& gg_2);
int program(std::ifstream& stream, HashTable& gg_2)
{
    int statement_result;
    int lexem;
    lexem = get_lexem(stream,gg, gg_2);
    if (lexem == LEX_ERR)
        return LEX_ERR;

    if (lexem != PROGRAM)
        return EXPECTED_PROGRAM;

    lexem = get_lexem(stream, gg, gg_2);
    if (lexem == LEX_ERR)
        return LEX_ERR;
    if (lexem != INTEGER && lexem != REAL) {
        return EXPECTED_DESCRIPTION;
    }
    else {
        int _pref = lexem;
        statement_result = description(stream, _pref, gg_2);
    }

    if (statement_result == EXPECTED_SEPARATOR) {
        lexem = get_lexem(stream, gg, gg_2);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem != ASSIGN)
            return EXPECTED_ASSIGN;
    }
    else
        return statement_result;

    int pref = 0;
    int l = 0;
    int r = 0;
    statement_result = expression(stream, pref, l, r, gg_2);
    while (statement_result != OK) {
        if (statement_result == EXPECTED_ASSIGN) {
            lexem = get_lexem(stream, gg, gg_2);
            if (lexem == LEX_ERR)
                return LEX_ERR;
            if (lexem == ASSIGN) {
                pref = 0;
                statement_result = expression(stream, pref, l, r, gg_2);
            }
            else
                return EXPECTED_SEPARATOR;
        }
        else
            return statement_result;
    }
        
    return OK;
}

bool require_lexem1(std::ifstream& stream, int expected1, HashTable& gg_2)
{
    int lexem = get_lexem(stream,gg, gg_2);
    return lexem == expected1;
}

bool require_lexem2(std::ifstream& stream, int expected1, int expected2, HashTable& gg_2)
{
    int lexem = get_lexem(stream,gg, gg_2);
    return lexem == expected1 || lexem == expected2;
}

bool require_lexem3(std::ifstream& stream, int expected1, int expected2, int expected3, HashTable& gg_2)
{
    int lexem = get_lexem(stream,gg, gg_2);
    return lexem == expected1 || lexem == expected2 || lexem == expected3;
}

//рекурсивная функция разбора строки
int expression(std::ifstream& stream, int& pref, int& flag_lparen, int& flag_rparen, HashTable& gg_2) {
    int statement_result;
    //берем следующую лексему
    int lexem = get_lexem(stream, gg, gg_2);
    if (lexem == LEX_ERR)
        return LEX_ERR;
    //чтоб не начать разбирать новую строку раньше времени
    if (lexem == END){
        //не может кончаться на плюс или минус
        if (pref == PLUS || pref == MINUS)
            return UNRECOGNIZED_STATEMENT;
        return OK;
    }
    if (lexem == RPAREN){
        //избежание случаев когда перед скобкой стоит (-+
        if (pref == 0 || pref == MINUS || pref == PLUS)
            return EXPECTED_IDENTIFIER;
        pref = lexem;
        if (flag_lparen > 0) {
            flag_rparen += 1;
            pref = RPAREN;
            return OK;
        }
        else
            return EXPECTED_LPAREN;
    }
    if (lexem == LPAREN){
        //избежание случаев когда перед скобкой стоят числа или перменные
        if (pref == INTDIG || pref == REAL || pref == ID)
            return EXPECTED_SEPARATOR;
        pref = 0;
        flag_lparen += 1;
        //идем разбирать что творится внутри скобок
        statement_result = expression(stream, pref, flag_lparen, flag_rparen, gg_2);
        
        //понимаем все ли хорошо внутри написано
        if (statement_result != OK) {
            return UNRECOGNIZED_STATEMENT;
        }

        if (flag_rparen == 0)
            return EXPECTED_RPAREN;

        flag_lparen -= 1;
        flag_rparen -= 1;
        //считываем сразу новый символ так как тогда не до разберем строку
        lexem = get_lexem(stream, gg, gg_2);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem == PLUS || lexem == MINUS) {
            pref = lexem;
            return expression(stream, pref, flag_lparen, flag_rparen, gg_2);
        }
        else if (lexem == RPAREN) {
            flag_rparen += 1;
            if (flag_lparen == 0)
                return SUP_RPAREN;
        }
        else if (lexem == REALDIG || lexem == INTDIG || lexem == RTOI || lexem == ITOR)
            return UNRECOGNIZED_STATEMENT;
        else if (lexem == ID && flag_lparen == flag_rparen && flag_lparen == 0)
            return EXPECTED_ASSIGN;
        else if (lexem == ASSIGN)
            return SUP_ASSIGN;
        pref = lexem;
        if (lexem == LEX_ERR)
            return UNRECOGNIZED_STATEMENT;
        return OK;
    }
    //если действие происходит внутри скобок
    else if (pref == 0){
        if (lexem == PLUS || lexem == MINUS)
            return EXPECTED_IDENTIFIER;
        pref = lexem;
        return expression(stream, pref, flag_lparen, flag_rparen, gg_2);
    }
    else if (pref == ID || pref == REALDIG || pref == INTDIG) {
        if (lexem == REALDIG || lexem == INTDIG || lexem == RTOI || lexem == ITOR)
            return EXPECTED_SEPARATOR;
        if (lexem == ID)
            return EXPECTED_ASSIGN;
        pref = lexem;
        if (lexem == PLUS || lexem == MINUS)
            return expression(stream, pref, flag_lparen, flag_rparen, gg_2);
        else
            return UNRECOGNIZED_STATEMENT;
    }
    else if (pref == PLUS || pref == MINUS) {
        if (lexem == PLUS || lexem == MINUS)
            return EXPECTED_IDENTIFIER;
        pref = lexem;
        if (lexem == INTDIG || lexem == REALDIG || lexem == ID || lexem == RTOI || lexem == ITOR)
            return expression(stream, pref, flag_lparen, flag_rparen, gg_2);
        else
            return UNRECOGNIZED_STATEMENT;
    }
    return UNRECOGNIZED_STATEMENT;
}

int description(std::ifstream& stream, int _pref, HashTable& gg_2){
    int lexem = get_lexem(stream, gg, gg_2);
    if (lexem == LEX_ERR)
        return LEX_ERR;
    if (lexem == ID) {
        if (_pref == APPERAND || _pref == INTEGER || _pref == REAL) {
            _pref = lexem;
            return description(stream, _pref, gg_2);
        }
        else if (_pref == ID) {
            return EXPECTED_SEPARATOR;
        }
    }
    if (lexem == APPERAND) {
        if (_pref == APPERAND || _pref == INTEGER || _pref == REAL) {
            return EXPECTED_IDENTIFIER;
        }
        else if (_pref == ID) {
            _pref = lexem;
            return description(stream, _pref, gg_2);
        }
    }
    if (lexem == PLUS || lexem == MINUS || lexem == ASSIGN || lexem == RPAREN  || lexem == RTOI || lexem == ITOR
        || lexem == LPAREN) {
        return UNRECOGNIZED_STATEMENT;
    }
    if (lexem == REAL || lexem == INTEGER) {
        _pref = lexem;
        return description(stream, _pref, gg_2);
    }
}