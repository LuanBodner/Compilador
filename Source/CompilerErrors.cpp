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

        std::cout << "\033[1;36mLine\033[0m: " << token.getTokenLine() << "; ";
        std::cout << "\033[1;36mColumn\033[0m: " << token.getTokenColumn() << "; ";
        std::cout << "\033[1;32mReceived\033[0m: " << token.getTokenName() << "';\n";

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::variableDeclarationError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::returnIgnoredWarning(Token::Token token) {

        std::cout << "\033[1;35mWarning\033[0m; Return Value Ignored;";
        std::cout << "\033[1;36mLine\033[0m: " << token.getTokenLine() << "; ";
        std::cout << "\033[1;36mColumn\033[0m: " << token.getTokenColumn() << "; ";
        std::cout << "\033[1;32mReceived\033[0m: " << token.getTokenName() << "';\n";
    }

    void CompilerErrors::emptyOperationError() {


    }

    void CompilerErrors::variableVoidError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Void Variable Declared; ";
        printError(token);
    }

    void CompilerErrors::functionDeclarationError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Function Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::parameterDeclarationError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Parameter Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::expressionError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Expression Error; ";
        printError(token);
    }

    void CompilerErrors::numberOfArgumentsError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Number Of Arguments Error; ";
        printError(token);
    }

    void CompilerErrors::functionCallError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Wrong Number Of Arguments In Function Call; ";
        printError(token);
    }

    void CompilerErrors::functionCallScopeError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Function Not Previously Declared; ";
        printError(token);
    }

    void CompilerErrors::declarationScopeError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable Already Declared In This Scope; ";
        printError(token);
    }

    void CompilerErrors::factorError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Factor Error; ";
        printError(token);
    }

    void CompilerErrors::typeError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Unidentified Type Error; ";
        printError(token);
    }

    void CompilerErrors::variableNotDefinedError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable Used But Not Defined In This Scope; ";
        printError(token);
    }

    void CompilerErrors::unidentifiedTokenError(int Token, Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Unidentified Token Error; "
                << "\033[1;32mExpected\033[0m: "
                << intToString(Token)
                << "; \033[1;32mReceived\033[0m: "
                << token.tokenTypeToString()
                << std::endl;

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::unknownCaracterStringError(int line, int column) {

        std::cout << "\033[1;31mError\033[0m; Token Not Recognized; ";
        std::cout << "\033[1;36mLine\033[0m: " << line
                << ";\033[1;36mColumn\033[0m: " << column << std::endl;

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::mainDeclarationError() {

        std::cout << "\033[1;31mError\033[0m; No Main Declaration In File; "
                << "Program Terminated;\n";

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::expressionTypeWarning(Token::Token token) {

        std::cout << "\033[1;35mWarning\033[0m; Expression from unexpected type; ";
        std::cout << "\033[1;36mLine\033[0m: " << token.getTokenLine() << "; ";
        std::cout << "\033[1;36mColumn\033[0m: " << token.getTokenColumn() << "; ";
        std::cout << "\033[1;32mReceived\033[0m: " << token.getTokenName() << "';\n";
    }

    void CompilerErrors::variableNotDeclaredError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable Not Declared In This Scope; ";
        printError(token);
    }

    void CompilerErrors::vectorSizeError() {

        std::cout << "\033[1;31mError\033[0m; No Expression Defined\n";

        exit(EXIT_FAILURE);
    }
}
