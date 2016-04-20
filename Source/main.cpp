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
#include "SyntaxAnalyzer.h"

void printTokens() {

    Lex::LexicalAnalyzer lex;
    lex = Lex::LexicalAnalyzer("tiny.txt");

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
}

int main(int argc, char** argv) {


    std::ofstream output;

    output.open("treeStr.txt", std::ofstream::out);

    SyntaxAnalyzer::SyntaxAnalyzer synx;

    synx.initialTarget("tiny.txt");

    /*Tree::Tree newTree;
    Tree::Tree * treePointer = NULL;

    Token::Token parentToken, childrenToken;

    parentToken.setTokenColumn(0);
    parentToken.setTokenLine(0);
    parentToken.setTokenName("Teste");
    parentToken.setTokenType(Token::IDENTIFIER);

    childrenToken.setTokenColumn(0);
    childrenToken.setTokenLine(1);
    childrenToken.setTokenName("Ok");
    childrenToken.setTokenType(Token::IDENTIFIER);

    newTree.insertToken(parentToken);

    newTree.insertChild(childrenToken, 0);
    newTree.insertChild(childrenToken, 1);
    
    treePointer = newTree.newSubTree();

    treePointer->insertToken(parentToken);

    treePointer->insertChild(childrenToken, 0);

    newTree.printTree(output);*/

    synx.getTree().printTree(output);

    return 0;
}