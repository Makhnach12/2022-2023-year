#ifndef SYNTAX_ANAL_H
#define SYNTAX_ANAL_H
#include "hashtable.h"
#include "syntax.h"
#include "dka.h"
#include <string>
#include <iostream>
#include <fstream>
#include "tree.h"

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

class syntax_anal {
private:
    ifstream stream;
    HashTable gg_2;
    analizator gg;
    int pref;
    int _pref;
    int flag_lparen;
    int flag_rparen;
    node* _root;
    //����������� ������� ������� ������
    int expression(node* _son) {
        int statement_result;
        //����� ��������� �������
        int lexem = get_lexem(stream, gg, gg_2);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        //���� �� ������ ��������� ����� ������ ������ �������
        if (lexem == END) {
            //�� ����� ��������� �� ���� ��� �����
            if (pref == PLUS || pref == MINUS)
                return UNRECOGNIZED_STATEMENT;
            return OK;
        }
        if (lexem == RPAREN) {
            //��������� ������� ����� ����� ������� ����� (-+
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
        if (lexem == LPAREN) {
            //��������� ������� ����� ����� ������� ����� ����� ��� ���������
            if (pref == INTDIG || pref == REAL || pref == ID)
                return EXPECTED_SEPARATOR;
            _son = _son->add(_son, EXPR);
            _son = _son->add(_son, SEXPR);
            _son->add(_son, LPAREN);
            pref = 0;
            flag_lparen += 1;
            //���� ��������� ��� �������� ������ ������
            statement_result = expression(_son);

            //�������� ��� �� ������ ������ ��������
            if (statement_result != OK) {
                return UNRECOGNIZED_STATEMENT;
            }

            if (flag_rparen == 0)
                return EXPECTED_RPAREN;

            flag_lparen -= 1;
            flag_rparen -= 1;
            _son->add(_son, RPAREN);
            //��������� ����� ����� ������ ��� ��� ����� �� �� �������� ������
            lexem = get_lexem(stream, gg, gg_2);
            if (lexem == LEX_ERR)
                return LEX_ERR;
            if (lexem == PLUS || lexem == MINUS) {
                pref = lexem;
                _son->add(_son, lexem);
                return expression(_son); 
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
        //���� �������� ���������� ������ ������
        else if (pref == 0) {
            if (lexem == PLUS || lexem == MINUS)
                return EXPECTED_IDENTIFIER;
            pref = lexem;
            _son = _son->add(_son, EXPR);
            _son = _son->add(_son, SEXPR);
            _son = _son->add(_son, lexem);
            return expression(_son->parent->parent);
        }
        else if (pref == ID || pref == REALDIG || pref == INTDIG) {
            if (lexem == REALDIG || lexem == INTDIG || lexem == RTOI || lexem == ITOR)
                return EXPECTED_SEPARATOR;
            if (lexem == ID)
                return EXPECTED_ASSIGN;
            pref = lexem;
            if (lexem == PLUS || lexem == MINUS) {
                _son->add(_son, lexem);
                return expression(_son);
            }
            else
                return UNRECOGNIZED_STATEMENT;
        }
        else if (pref == PLUS || pref == MINUS) {
            if (lexem == PLUS || lexem == MINUS)
                return EXPECTED_IDENTIFIER;
            pref = lexem;
            if (lexem == INTDIG || lexem == REALDIG || lexem == ID || lexem == RTOI || lexem == ITOR) {
                _son = _son -> add(_son, EXPR);
                _son = _son->add(_son, SEXPR);
                _son = _son->add(_son, lexem);
                return expression(_son->parent->parent);
            }
            else
                return UNRECOGNIZED_STATEMENT;
        }
        return UNRECOGNIZED_STATEMENT;
    }

    int description(node* _son, node* _description) {
        int lexem = get_lexem(stream, gg, gg_2);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem == ID) {
            if (_pref == APPERAND || _pref == INTEGER || _pref == REAL) {
                _son = _son->add(_son, VAR_LIST);
                _pref = lexem;
                _son = _son->add(_son, ID);
                _son = _son->add(_son, lexem);
                return description(_son->parent, _description);
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
                _son->add(_son, APPERAND);
                return description(_son, _description);
            }
        }
        if (lexem == PLUS || lexem == MINUS || lexem == ASSIGN || lexem == RPAREN || lexem == RTOI || lexem == ITOR
            || lexem == LPAREN) {
            return UNRECOGNIZED_STATEMENT;
        }
        if (lexem == REAL || lexem == INTEGER) {
            _pref = lexem;
            _son = _description->add(_description, DESCRIPTION);
            _description = _son;
            _son = _son->add(_son, DESCR);
            _son = _son->add(_son, TYPE);
            _son = _son->add(_son, lexem);
            return description(_son->parent->parent, _description);
        }
    }
public:
    node* root() { return _root; }
    syntax_anal(string _stream) {
        stream.open(_stream);
        pref = 0;
        _pref = 0;
        flag_lparen = 0;
        flag_rparen = 0;
        _root = new node(PROGRAM);
    }
    int program()
    {
        int statement_result;
        int lexem;
        node* _son = _root->add(_root, BEGIN);
        lexem = get_lexem(stream, gg, gg_2);
        if (lexem == LEX_ERR)
            return LEX_ERR;

        if (lexem != PROGRAM)
            return EXPECTED_PROGRAM;
        _son = _son->add(_son, PROGRAM);

        lexem = get_lexem(stream, gg, gg_2);
        if (lexem == LEX_ERR)
            return LEX_ERR;
        if (lexem != INTEGER && lexem != REAL) {
            return EXPECTED_DESCRIPTION;
        }
        else {
            _pref = lexem;
            _son = _root->add(_root, DESCRIPTION);
            _son = _son->add(_son, DESCR);
            _son = _son->add(_son, TYPE);
            _son = _son->add(_son, INTEGER);
            statement_result = description(_son->parent->parent, _root->arr[1]);
        }

        if (statement_result == EXPECTED_SEPARATOR) {
            lexem = get_lexem(stream, gg, gg_2);
            if (lexem == LEX_ERR)
                return LEX_ERR;
            if (lexem != ASSIGN)
                return EXPECTED_ASSIGN;
            _son = _root->add(_root, OPERS);
            _son = _son->add(_son, OP);
            _son = _son->add(_son, ID);
            _son = _son->add(_son, _pref);
            _son = _son->add(_son->parent->parent, lexem);
        }
        else
            return statement_result;

        statement_result = expression(_son->parent);
        node* _opers = _root->arr[2];
        while (statement_result != OK) {
            if (statement_result == EXPECTED_ASSIGN) {
                lexem = get_lexem(stream, gg, gg_2);
                if (lexem == LEX_ERR)
                    return LEX_ERR;
                if (lexem == ASSIGN) { 
                    pref = 0;
                    _son = _opers->add(_opers, OPERS);
                    _opers = _son;
                    _son = _son->add(_son, OP);
                    _son = _son->add(_son, ID);
                    _son = _son->add(_son, _pref);
                    _son = _son->add(_son->parent->parent, lexem);
                    statement_result = expression(_son->parent);
                }
                else
                    return EXPECTED_SEPARATOR;
            }
            else
                return statement_result;
        }
        _son = _root->add(_root, END);
        return OK;
    }
};

#endif