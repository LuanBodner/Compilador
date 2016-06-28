/* 
 * File:   CompilerErrors.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on April 8, 2016, 4:08 PM
 */

#include <stdlib.h>
#include <fstream>
#include <limits>
#include "CompilerErrors.h"

namespace CompilerErrors {

    std::fstream tinyFile;

    CompilerErrors::CompilerErrors() {
    }

    CompilerErrors::~CompilerErrors() {
    }

    static std::string intToString(int i) {

        return std::string(Token::enumString[i]);
    }

    void CompilerErrors::openTinyFile(std::ifstream& file) {

        tinyFile.open("tempTiny.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

        std::string content;
        file.seekg(std::ifstream::beg);

        while (!file.eof()) {

            std::getline(file, content);
            tinyFile << content << "\n";
        }

        file.seekg(std::ifstream::beg);
    }

    void CompilerErrors::printLine(int line) {

        std::string pline;

        tinyFile.seekg(std::ios::beg);

        for (int i = 0; i < line - 1; i++)
            std::getline(tinyFile, pline);

        std::getline(tinyFile, pline);
        std::cout << "\033[1;30mCode\033[0m: " << pline << "\n\n";
    }

    void CompilerErrors::printError(Token::Token token) {

        std::cout << "\033[1;36mLine\033[0m: " << token.getTokenLine() << "; "
                "\033[1;36mColumn\033[0m: " << token.getTokenColumn() << "; "
                "\033[1;32mReceived\033[0m: " << token.getTokenName() << ".\n";

        printLine(token.getTokenLine());
        system("rm -f tempTiny.txt");

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::variableNotUsedWarning(std::string name, std::string type) {

        std::cout << "\033[1;35mWarning\033[0m; Variable Defined But Not Used;\n"
                << "\033[1;30mCode\033[0m: " << type << ": "
                << name << "\n\n";

        //std::cout << scope << std::endl;
    }

    void CompilerErrors::returnMayBeIgnoredWarning(Token::Token token) {

        std::cout << "\033[1;35mWarning\033[0m; Return Value May Be Ignored; ";
        printError(token);
    }

    void CompilerErrors::tooManyReturnsError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; More Than One Return Statement; ";
        printError(token);
    }

    void CompilerErrors::variableDeclarationError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable Declaration Error; ";
        printError(token);
    }

    void CompilerErrors::returnIgnoredWarning(Token::Token token) {

        std::cout << "\033[1;35mWarning\033[0m; Return Value Ignored; "
                << "\033[1;36mLine\033[0m: " << token.getTokenLine() << "; "
                << "\033[1;36mColumn\033[0m: " << token.getTokenColumn() << "; "
                << "\033[1;32mReceived\033[0m: " << token.getTokenName() << ";\n";

        printLine(token.getTokenLine());
    }

    void CompilerErrors::functionWithoutReturnWarning(std::string name) {

        std::cout << "\033[1;35mWarning\033[0m; Non-Void Function Without Return; "
                << "\033[1;32mFunction Name\033[0m: " << name << "\n\n";
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

        printLine(token.getTokenLine());

        system("rm -f tempTiny.txt");

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::unknownCaracterStringError(int line, int column) {

        std::cout << "\033[1;31mError\033[0m; Token Not Recognized; "
                << "\033[1;36mLine\033[0m: " << line
                << ";\033[1;36mColumn\033[0m: " << column << std::endl;

        printLine(line);

        system("rm -f tempTiny.txt");

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::mainDeclarationError() {

        std::cout << "\033[1;31mError\033[0m; No Main Declaration In File; "
                << "Program Terminated;\n\n";

        system("rm -f tempTiny.txt");

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::variableNotInitialized(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable not Initialized; ";

        printError(token);
    }

    void CompilerErrors::expressionTypeError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Unexpected Type; "
                << "\033[1;36mLine\033[0m: " << token.getTokenLine() << "; "
                << "\033[1;36mColumn\033[0m: " << token.getTokenColumn() << "; "
                << "\033[1;32mReceived\033[0m: " << token.getTokenName() << "';\n";

        printLine(token.getTokenLine());

        exit(EXIT_FAILURE);
    }

    void CompilerErrors::voidAttributionError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Function Type Is Void; ";
        printError(token);
    }

    void CompilerErrors::variableNotDeclaredError(Token::Token token) {

        std::cout << "\033[1;31mError\033[0m; Variable Not Declared In This Scope; ";
        printError(token);
    }

    void CompilerErrors::vectorSizeError() {

        std::cout << "\033[1;31mError\033[0m; No Expression Defined\n\n";

        system("rm -f tempTiny.txt");

        exit(EXIT_FAILURE);
    }
}
