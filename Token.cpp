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

    void Token::print() {

        std::cout << "<" << this->tokenName << "," << this->token << ">" << std::endl;
    }
}
