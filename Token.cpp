/* 
 * File:   Token.cpp
 * Author: LuanB
 * 
 * Created on 17 de Março de 2016, 00:23
 */

#include "Token.h"

namespace Token {

    Token::Token() {
    }

    Token::~Token() {
    }

    std::string Token::getTokenName() {
        return this->tokenName;
    }

    TokenType Token::getTokenType() {
        return this->token;
    }

    void Token::setTokenName(std::string name) {
        this->tokenName = name;
    }

    void Token::setTokenType(TokenType token) {
        this->token = token;
    }

    void Token::setTokenLine(int line) {
        this->tokenLine = line;
    }

    void Token::setTokenColumn(int column) {
        this->tokenColumn = column;
    }

    std::string Token::tokenTypeToString() {
        switch (this->token) {
            case 0: return "IF";
            case 1: return "THEN";
            case 2: return "OTHERWISE";
            case 3: return "END";
            case 4: return "REPEAT";
            case 5: return "FLOAT";
            case 6: return "VOID";
            case 7: return "UNTIL";
            case 8: return "READ";
            case 9: return "WRITE";
            case 10:return "INTEGER";
            case 11: return "COMMENTS";
            case 12: return "RETURN";
            case 13: return "SUM";
            case 14: return "SUBTRACTION";
            case 15: return "MULTIPLICATION";
            case 16: return "DIVISION";
            case 17: return "EQUAL";
            case 18: return "COMMA";
            case 19: return "ATTRIBUTION";
            case 20: return "SMALLER THAN";
            case 21: return "BIGGER THAN";
            case 22: return "SMALL EQUAL";
            case 23: return "BIGGER EQUAL";
            case 24: return "OPEN PAIR";
            case 25: return "CLOSE PAIR";
            case 26: return "NUMBER";
            case 27: return "DOUBLE POINT";
            case 28: return "IDENTIFIER";
            default: return "UNKNOWN";
        }
    }

    int Token::getTokenLine() {
        return this->tokenLine;
    }

    int Token::getTokenColumn() {
        return this->tokenColumn;
    }

    void Token::print() {

        std::cout << "<" << this->tokenName << "," << this->token << ">" << std::endl;
    }
}
