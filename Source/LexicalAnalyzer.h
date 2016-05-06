/* 
 * File:   LexicalAnalyzer.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
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
#include "CompilerErrors.h"

namespace Lex {

    class LexicalAnalyzer {
    public:
        LexicalAnalyzer(std::string);
        LexicalAnalyzer();
        virtual ~LexicalAnalyzer();

        //Returns the token found first and removes it from the vector
        Token::Token getNextToken(std::ifstream &);

    private:

        CompilerErrors::CompilerErrors error;
        //Collects and stores the tokens
        Token::Token tokenInserter(std::string &, std::string,
                Token::TokenType, boost::regex, int, int);
    };
}
#endif /* LEXICALANALYZER_H */

