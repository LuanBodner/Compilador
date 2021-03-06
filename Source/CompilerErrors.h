/* 
 * File:   CompilerErrors.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on April 8, 2016, 4:08 PM
 */

#ifndef COMPILERERRORS_H
#define COMPILERERRORS_H

#include <string>
#include "Token.h"

namespace CompilerErrors {

    class CompilerErrors {
    public:
        CompilerErrors();
        virtual ~CompilerErrors();

        /* Semantic errors */
        void declarationScopeError(Token::Token);
        void variableNotDeclaredError(Token::Token);
        void functionCallError(Token::Token);
        void functionCallScopeError(Token::Token);
        void variableNotDefinedError(Token::Token);
        void variableNotInitialized(Token::Token);
        void variableVoidError(Token::Token);
        void expressionTypeError(Token::Token);
        void returnIgnoredWarning(Token::Token);
        void voidAttributionError(Token::Token);
        void functionWithoutReturnWarning(std::string);
        void returnMayBeIgnoredWarning(Token::Token);
        void variableNotUsedWarning(std::string, std::string);
        void mainDeclarationError();
        void tooManyReturnsError(Token::Token);

        /* Syntax errors */
        void variableDeclarationError(Token::Token);
        void functionDeclarationError(Token::Token);
        void parameterDeclarationError(Token::Token);
        void expressionError(Token::Token);
        void numberOfArgumentsError(Token::Token);
        void factorError(Token::Token);
        void typeError(Token::Token);
        void unidentifiedTokenError(int, Token::Token);

        /* Lexical errors */
        void unknownCaracterStringError(int, int);
        void vectorSizeError();

        void openTinyFile(std::ifstream&);

    private:
        void printError(Token::Token);
        void printLine(int);
    };
}

#endif /* COMPILERERRORS_H */

