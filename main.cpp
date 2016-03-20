/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: LuanB
 *
 * Created on 16 de Março de 2016, 02:40
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>
#include "Token.h"
#include "LexicalAnalyzer.h"

int main(int argc, char** argv) {

    Lex::LexicalAnalyzer lex;

    lex.tokenFinder("tiny.txt");

    Token::Token tokenTemp;

    std::ofstream output;

    output.open("outputTokens.txt", std::ofstream::out);

    do {

        tokenTemp = lex.getNextToken();
        output << "<" << tokenTemp.getTokenName() << "," << tokenTemp.getTokenType() << ">\n";
    } while (!lex.emptyTokenList());

    return 0;
}

