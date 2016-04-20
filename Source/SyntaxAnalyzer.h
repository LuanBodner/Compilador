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
#include "CompilerErrors.h"
#include "Tree.h"
#include <string>

namespace SyntaxAnalyzer {

    class SyntaxAnalyzer : public CompilerErrors::CompilerErrors {
    public:

        SyntaxAnalyzer();
        virtual ~SyntaxAnalyzer();

        // Kicks of the analysis
        void initialTarget(std::string);

        Tree::Tree getTree();
    private:

        Lex::LexicalAnalyzer lexer;

        Tree::Tree syntaxTree;

        // Creates an instance of the Lexer from the file std::string
        void createLexer(std::string);

        // Navigates on the token vector
        Token::Token targetAdvance();

        // Consumes the next token in the vector
        void eat(int Token);

        // Variable declaration
        void type();
        void variableDec();

        // IO operations
        void readExp();
        void writeExp();

        // Definition for the basic operations
        void relationalExp();
        void relationalExpL();
        void equalityExp();
        void equalityExpL();
        void additiveExp();
        void additiveExpL();
        void multiplicativeExp();
        void multiplicativeExpL();
        void operationsExp();
        void factorExp();

        // Return
        void returnValue();

        // If statement
        void ifStmt();

        // While statement
        void whileStmt();

        // Attribution Expression
        void attributionExp();

        // Definition of function call and the possible parameters
        void paramCallExp();
        void functionCallExp();

        // Compound statement
        void expression();
        void compoundStmt();

        // Function declaration
        void paramFunction();
        void prototypeDef();
        void functionDec();

    };
}
#endif /* SYNTAXANALYZER_H */

