/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Token.h
 * Author: LuanB
 *
 * Created on 17 de Março de 2016, 00:23
 */

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

namespace Token {

    typedef enum {
        IF, THEN, OTHERWISE, END, REPEAT,
        FLOAT, VOID, UNTIL, READ, WRITE,
        INTEGER, SCIENTIFIC_INTEGER, COMMENTS, SCIENTIFIC_FLOAT, RETURN,
        SUM, SUBTRACTION, MULTIPLICATION, DIVISION, EQUAL,
        COMMA, ATTRIBUTION, SMALLER_THAN, BIGGER_THAN, SMALL_EQUAL,
        BIGGER_EQUAL, OPEN, CLOSE, NUMBER, DOUBLE_POINT, IDENTIFIER
    } TokenType;

    class Token {
    public:

        //Constructor & destructor
        Token();
        virtual ~Token();

        //Other methods
        std::string getTokenName();
        TokenType getTokenType();
        void setTokenName(std::string);
        void setTokenType(TokenType);
        void print();

    private:
        std::string tokenName;
        TokenType token;
    };
}

#endif /* TOKEN_H */

