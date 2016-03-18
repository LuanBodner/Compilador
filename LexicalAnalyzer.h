/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LexicalAnalyzer.h
 * Author: LuanB
 *
 * Created on 17 de Março de 2016, 00:56
 */

#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>

#include "Token.h"

namespace Lex {

    class LexicalAnalyzer {
    public:

        //Constructor & destructor
        LexicalAnalyzer();
        virtual ~LexicalAnalyzer();

        //Other methods
        std::string readFile(std::string); //Leitura do arquivo
        void tokenFinder(std::string);

        static std::vector<Token::Token> tokens;
    };

}

#endif /* LEXICALANALYZER_H */

