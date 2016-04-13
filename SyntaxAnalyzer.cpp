/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalyzer.h"

namespace SyntaxAnalyzer {

    SyntaxAnalyzer::SyntaxAnalyzer() {
    }

    void SyntaxAnalyzer::createLexer(std::string fileName) {

        lexer = Lex::LexicalAnalyzer(fileName);
    }

    Token::Token SyntaxAnalyzer::targetAdvance() {

        return lexer.getNextToken();
    }

    void SyntaxAnalyzer::mulExpr() {

    }

    void SyntaxAnalyzer::addExprT() {

    }

    void SyntaxAnalyzer::eat(Token::Token &token) {

        token = targetAdvance();
    }

    void SyntaxAnalyzer::targetAnalyzer() {

        Token::Token nextToken = targetAdvance();

        switch (nextToken.getTokenType()) {

            case Token::IDENTIFIER:
                eat(nextToken);
                break;
            default:
                break;
        }
    }

    SyntaxAnalyzer::~SyntaxAnalyzer() {
    }
}
