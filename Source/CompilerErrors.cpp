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

        switch (i) {
            case 0: return "IF";
            case 1: return "THEN";
            case 2: return "OTHERWISE";
            case 3: return "END";
            case 4: return "REPEAT";
            case 5: return "FLOAT";
            case 6: return "VOID";
            case 7: return "UNTIL";
            case 8: return "READ";
            case 9: return "WRITE";
            case 10: return "INTEGER";
            case 11: return "COMMENTS";
            case 12: return "RETURN";
            case 13: return "SUM";
            case 14: return "SUBTRACTION";
            case 15: return "MULTIPLICATION";
            case 16: return "DIVISION";
            case 17: return "EQUAL";
            case 18: return "COMMA";
            case 19: return "ATTRIBUTION";
            case 20: return "LESS THAN";
            case 21: return "BIGGER THAN";
            case 22: return "LESS THAN OR EQUAL";
            case 23: return "BIGGER OR EQUAL";
            case 24: return "OPEN PAIR";
            case 25: return "CLOSE PAIR";
            case 26: return "INTEGER NUMBER";
            case 27: return "FLOAT NUMBER";
            case 28: return "DOUBLE POINT";
            case 29: return "IDENTIFIER";
            default: return "UNKNOWN";
        }
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
                << "Received : "
                << intToString(Token)
                << "; Expected : "
                << token.tokenTypeToString()
                << "; Name : " << token.getTokenName()
                << std::endl;

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::unknownCaracterStringError(int line, int column) {

        std::cout << "Token Not Recognized; ";
        std::cout << "Line: " << line << ";Column: " << column << std::endl;

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::vectorSizeError() {

        std::cout << "No Expression Defined\n";

        exit(EXIT_FAILURE);
    }
}
