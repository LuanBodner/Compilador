/* 
 * File:   Token.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on 17 de Março de 2016, 00:23
 */

#include "Token.h"

namespace Token {

    const char * enumString[] = {
        "IF", "THEN", "OTHERWISE", "END", "REPEAT",
        "FLOAT", "VOID", "UNTIL", "READ", "WRITE",
        "INTEGER", "COMMENTS", "RETURN", "SUM", "SUBTRACTION",
        "MULTIPLICATION", "DIVISION", "EQUAL", "COMMA", "ATTRIBUTION",
        "LESS_THAN", "BIGGER_THAN", "LESS_EQUAL", "BIGGER_EQUAL", "OPEN",
        "CLOSE", "NUMBER_INTEGER", "NUMBER_FLOAT", "DOUBLE_POINT", "IDENTIFIER"
    };

    Token::Token() {
    }

    Token::Token(std::string str, TokenType type, int li, int col)
    : tokenName(str), token(type), tokenColumn(col), tokenLine(li) {
    }

    Token::~Token() {
    }

    std::string Token::getTokenName() {

        return tokenName;
    }

    TokenType Token::getTokenType() {

        return token;
    }

    void Token::setTokenName(std::string name) {

        tokenName = name;
    }

    void Token::setTokenType(TokenType token) {

        this->token = token;
    }

    void Token::setTokenLine(int line) {

        tokenLine = line;
    }

    void Token::setTokenColumn(int column) {

        tokenColumn = column;
    }

    std::string Token::tokenTypeToString() {

        return std::string(enumString[this->getTokenType()]);
    }

    int Token::getTokenLine() {

        return this->tokenLine;
    }

    int Token::getTokenColumn() {

        return this->tokenColumn;
    }

    void Token::print() {

        std::cout << "<" << this->tokenName << "," << enumString[this->token] << ">" << std::endl;
    }
}
