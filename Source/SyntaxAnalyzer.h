/* 
 * File:   SyntaxAnalyzer.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on March 31, 2016, 9:33 AM
 */

#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "Token.h"
#include "LexicalAnalyzer.h"
#include <string>

namespace SyntaxAnalyzer {

    class SyntaxAnalyzer {
    public:
        SyntaxAnalyzer();
        virtual ~SyntaxAnalyzer();
        void initialTarget(std::string);
    private:
        Lex::LexicalAnalyzer lexer;
        Token::Token targetAdvance();
        std::string intToString(int);
        void createLexer(std::string);
        void variableDec();
        void functionDec();
        void eat(int);
        void functionCallExp();
        void prototypeDef();
        void ioTypes();
        void readExp();
        void writeExp();
        void equalityExp();
        void equalityExpL();
        void relationalExp();
        void attributionExp();
        void relationalExpL();
        void additiveExp();
        void additiveExpL();
        void multiplicativeExp();
        void multiplicativeExpL();
        void factorExp();
        void operationsExp();
        void returnValue();
        void type();
        void paramFunction();
        void expression();
        void ifStmt();
        void compoundStmt();
        void paramCallExp();
    };
}
#endif /* SYNTAXANALYZER_H */

