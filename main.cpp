/* 
 * File:   main.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on 16 de Março de 2016, 02:40
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>
#include <boost/preprocessor.hpp>
#include "Token.h"
#include "LexicalAnalyzer.h"

int main(int argc, char** argv) {

    Lex::LexicalAnalyzer lex("tiny.txt");

    Token::Token tokenTemp;

    std::ofstream output;

    output.open("outputTokens.txt", std::ofstream::out);

    do {

        try {

            tokenTemp = lex.getNextToken();

            output << "\"" << tokenTemp.getTokenName() << "\"" << " == "
                    << tokenTemp.tokenTypeToString() << "\n\tLINE : "
                    << tokenTemp.getTokenLine() << "\n\tCOLUMN : "
                    << tokenTemp.getTokenColumn() << "\n";
        } catch (const char * error) {

            output << "End of Vector\n";

            break;
        }
    } while (true);

    return 0;
}

