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

namespace Lex {

    class LexicalAnalyzer {
    public:

        //Constructor & destructor
        //Constructor that receives the name of the tpp file
        LexicalAnalyzer(std::string);
        virtual ~LexicalAnalyzer();

        //Other methods
        //Checks if the list is empty 
        bool emptyTokenList();
        //Returns the token found first and removes it from the vector
        Token::Token getNextToken();

    private:
        //Vector of tokens collected
        static std::vector<Token::Token> tokens;
        //Collects and stores the tokens
        void tokenCollector(std::string);
        void tokenInserter(std::string &, std::string, Token::TokenType, boost::regex, int, int);
    };
}
#endif /* LEXICALANALYZER_H */

