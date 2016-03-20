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
    /*
        do {

            tokenTemp = lex.getNextToken();
            tokenTemp.print();
        } while (!lex.emptyTokenList());*/

    tokenTemp = lex.getNextToken();
    tokenTemp.print();
    tokenTemp = lex.getNextToken();
    tokenTemp.print();
    return 0;
}

