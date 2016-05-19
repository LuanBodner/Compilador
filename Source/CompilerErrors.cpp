/* 
 * File:   CompilerErrors.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on April 8, 2016, 4:08 PM
 */

#include <stdlib.h>
#include "CompilerErrors.h"

namespace CompilerErrors {

    CompilerErrors::CompilerErrors() {
    }

    CompilerErrors::~CompilerErrors() {
    }

    static std::string intToString(int i) {

        return std::string(Token::enumString[i]);
    }

    void CompilerErrors::printError(Token::Token token) {

        std::cout << "Line: " << token.getTokenLine() << "; ";
        std::cout << "Column: " << token.getTokenColumn() << "; ";
        std::cout << "Received '" << token.getTokenName() << "';\n";

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::variableDeclarationError(Token::Token token) {

        std::cout << "Variable Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::functionDeclarationError(Token::Token token) {

        std::cout << "Function Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::parameterDeclarationError(Token::Token token) {

        std::cout << "Parameter Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::expressionError(Token::Token token) {

        std::cout << "Expression Error; ";
        printError(token);
    }

    void CompilerErrors::numberOfArgumentsError(Token::Token token) {

        std::cout << "Number Of Arguments Error; ";
        printError(token);
    }

    void CompilerErrors::functionCallError(Token::Token token) {

        std::cout << "Wrong Number Of Arguments In Function Call; ";
        printError(token);
    }

    void CompilerErrors::functionCallScopeError(Token::Token token) {

        std::cout << "Function Not Previously Declared; ";
        printError(token);
    }

    void CompilerErrors::declarationScopeError(Token::Token token) {

        std::cout << "Variable Already Declared In This Scope; ";
        printError(token);
    }

    void CompilerErrors::factorError(Token::Token token) {

        std::cout << "Factor Error; ";
        printError(token);
    }

    void CompilerErrors::typeError(Token::Token token) {

        std::cout << "Unidentified Type Error; ";
        printError(token);
    }

    void CompilerErrors::unidentifiedTokenError(int Token, Token::Token token) {

        std::cout << "Unidentified Token Error; "
                << "Expected : "
                << intToString(Token)
                << "; Received : "
                << token.tokenTypeToString()
                << std::endl;

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::unknownCaracterStringError(int line, int column) {

        std::cout << "Token Not Recognized; ";
        std::cout << "Line: " << line << ";Column: " << column << std::endl;

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::mainDeclarationError() {

        std::cout << "No Main Declaration In File; "
                << "Program Terminated;\n";

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::variableNotDeclared(Token::Token token) {

        std::cout << "Variable Not Declared In This Scope; ";
        printError(token);
    }

    void CompilerErrors::vectorSizeError() {

        std::cout << "No Expression Defined\n";

        exit(EXIT_FAILURE);
    }
}
