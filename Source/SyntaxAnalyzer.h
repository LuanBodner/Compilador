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

#define DECSTRING "Declaration"
#define OPSTRING "Operation"
#define IFSTRING "IfStatement"
#define WHILESTRING "WhileStatement"
#define FUNCDECSTRING "FunctionDecStatement"
#define PARAMDECSTRING "ParametersDecStatement"
#define COMPSTMTSTRING "CompoundStatement"
#define EXPSTRING "ExpressionStatement"
#define FUNCCALLSTRING "FunctionCallStatement"
#define ATTSTRING "AttributionStatement"
#define OTHERSTRING "OtherwiseStement"
#define RETURNSTRING "ReturnStatement"
#define OPEXPSTRING "OperationExpression"
#define MULTEXPSTRING "MultiplicationExpression"
#define DIVEXPSTRING "DivisionExpression"
#define SUMEXPSTRING "SumExpression"
#define SUBEXPSTRING "SubtractionExpression"
#define EQUALSTRING "EqualExpression"
#define LESSTSTRING "LessThanExpression"
#define BIGGERTSTRING "BiggerThanExpression"
#define BIGGERESTRING "BiggerEqualExpression"
#define LESSESTRING "SmallerEqualExpression"
#define WRITESTRING "WriteStatement"
#define READSTRING "ReadStatement"
#define VARDECSTRING "VariableDecStatement"

namespace SyntaxAnalyzer {

    class SyntaxAnalyzer {
    public:
        SyntaxAnalyzer();
        virtual ~SyntaxAnalyzer();

        // Kicks of the analysis
        void initialTarget(std::string, std::string);

        Tree::Tree getTree();

    private:
        Lex::LexicalAnalyzer lexer;

        Tree::Tree syntaxTree;

        CompilerErrors::CompilerErrors error;

        // Creates an instance of the Lexer from the file std::string
        void createLexer(std::string, std::string);

        // Prints the tokens in the file
        void printTokens(std::string);

        // Navigates on the token vector
        Token::Token targetAdvance();

        // Consumes the next token in the vector
        void eat(int Token);

        // Variable declaration
        void type();
        void variableDecStmt();

        // IO operations
        void readStmt();
        void writeStmt();

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
        void attributionStmt();

        // Definition of function call and the possible parameters
        void paramCallStmt();
        void functionCallStmt();

        // Compound statement
        void expression();
        void compoundStmt();

        // Function declaration
        void paramFunctionStmt();
        void prototypeDefStmt();
        void functionDecStmt();

        // Sets the father and advances the pointer
        void setAndAdvance(std::string);
    };
}
#endif /* SYNTAXANALYZER_H */

