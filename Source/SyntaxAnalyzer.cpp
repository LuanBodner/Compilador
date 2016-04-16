/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalyzer.h"

namespace SyntaxAnalyzer {

    unsigned int lookAhead = 0;

    SyntaxAnalyzer::SyntaxAnalyzer() {
    }

    void SyntaxAnalyzer::createLexer(std::string fileName) {

        lexer = Lex::LexicalAnalyzer(fileName);
    }

    Token::Token SyntaxAnalyzer::targetAdvance() {

        return lexer.getTokenByPos(lookAhead++);
    }

    void SyntaxAnalyzer::eat(int Token) {

        Token::Token tokenTemp = lexer.getNextToken();

        if (tokenTemp.getTokenType() != Token) {
            std::cout << "Eat Error " << tokenTemp.tokenTypeToString() << std::endl;
            exit(0);
        }
    }

    void SyntaxAnalyzer::variableDec() {

        eat(Token::DOUBLE_POINT);
        eat(Token::IDENTIFIER);
    }

    void SyntaxAnalyzer::compoundStmt() {

    }

    void SyntaxAnalyzer::paramFunction() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                eat(Token::DOUBLE_POINT);
                variableDec();
                paramFunction();
                break;
            case(Token::COMMA):
                paramFunction();
                break;
            case(Token::CLOSE):
                compoundStmt();
                eat(Token::END);
                break;
            default:
                std::cout << "Error\nReceived " <<
                        tokenTemp.tokenTypeToString() << std::endl;
                exit(0);
        }
    }

    void SyntaxAnalyzer::prototypeDef() {

        eat(Token::OPEN);
        paramFunction();
    }

    void SyntaxAnalyzer::functionDec() {

        Token::Token tempToken = targetAdvance();

        switch (tempToken.getTokenType()) {
            case(Token::IDENTIFIER):
                prototypeDef();
                break;
            default:
                break;
        }

    }

    void SyntaxAnalyzer::initialTarget(std::string fileName) {

        SyntaxAnalyzer::createLexer(fileName);

        Token::Token token = targetAdvance();

        switch (token.getTokenType()) {

            case(Token::INTEGER):
                token = targetAdvance();

                switch (token.getTokenType()) {

                    case(Token::DOUBLE_POINT):
                        eat(Token::INTEGER);
                        variableDec();
                        break;
                    case(Token::IDENTIFIER):
                        functionDec();
                        break;
                    default:
                        std::cout << "Erro\nExpected TYPE, received "
                                << token.tokenTypeToString() << std::endl;
                        exit(0);
                }
                break;
            case(Token::FLOAT):
                token = targetAdvance();

                switch (token.getTokenType()) {

                    case(Token::DOUBLE_POINT):
                        eat(Token::FLOAT);
                        variableDec();
                        break;
                    case(Token::IDENTIFIER):
                        functionDec();
                        break;
                    default:
                        std::cout << "Erro\nExpected TYPE, received "
                                << token.tokenTypeToString() << std::endl;
                        exit(0);
                }
                break;
            case(Token::VOID):
                //std::cout << "Declaração de função\n";
                functionDec();
                break;
            default: std::cout << "Erro\nExpected TYPE, received "
                        << token.tokenTypeToString() << std::endl;
                exit(0);

        }

    }

    SyntaxAnalyzer::~SyntaxAnalyzer() {
    }
}
