/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalyzer.h"

namespace SyntaxAnalyzer {

    unsigned int lookAhead = 0;

    std::string SyntaxAnalyzer::intToString(int i) {
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
            case 20: return "SMALLER THAN";
            case 21: return "BIGGER THAN";
            case 22: return "SMALL OR EQUAL";
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

    /* Funções básicas da classe SyntaxAnalyzer*/
    SyntaxAnalyzer::SyntaxAnalyzer() {
    }

    SyntaxAnalyzer::~SyntaxAnalyzer() {
    }

    void SyntaxAnalyzer::createLexer(std::string fileName) {

        lexer = Lex::LexicalAnalyzer(fileName);
    }

    /* Percorre pela lista de tokens na frente do eat */
    Token::Token SyntaxAnalyzer::targetAdvance() {

        return lexer.getTokenByPos(lookAhead++);
    }

    /* Faz a mudança de token para o próximo */
    void SyntaxAnalyzer::eat(int Token) {

        Token::Token tokenTemp = lexer.getNextToken();

        if (tokenTemp.getTokenType() != Token) {

            std::cout << "Eat Error\n"
                    << "Received : "
                    << intToString(Token)
                    << "\nExpected : "
                    << tokenTemp.tokenTypeToString()
                    << " Name : " << tokenTemp.getTokenName()
                    << std::endl;
            exit(0);
        }
    }

    /* Gramática para declaração de variável */
    void SyntaxAnalyzer::type() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::FLOAT):
                eat(Token::FLOAT);
                break;

            case(Token::INTEGER):
                eat(Token::INTEGER);
                break;

            case(Token::VOID):
                eat(Token::VOID);
                break;

            default:
                std::cout << "Type Error\nReceived " << tokenTemp.tokenTypeToString();
                exit(0);
        }
    }

    void SyntaxAnalyzer::variableDec() {

        type();

        targetAdvance();
        eat(Token::DOUBLE_POINT);

        targetAdvance();
        eat(Token::IDENTIFIER);
    }

    /* Leitura e escrita */
    void SyntaxAnalyzer::readExp() {

        targetAdvance();
        eat(Token::READ);

        targetAdvance();
        eat(Token::OPEN);

        targetAdvance();
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::CLOSE);
    }

    void SyntaxAnalyzer::writeExp() {

        targetAdvance();
        eat(Token::WRITE);

        targetAdvance();
        eat(Token::OPEN);

        operationsExp();

        targetAdvance();
        eat(Token::CLOSE);
    }

    /* Caminho da recursividade das operações */
    void SyntaxAnalyzer::relationalExp() {

        additiveExp();
        relationalExpL();
    }

    void SyntaxAnalyzer::relationalExpL() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::SMALLER_THAN):
                eat(Token::SMALLER_THAN);
                additiveExp();
                relationalExpL();
                break;

            case(Token::BIGGER_THAN):
                eat(Token::BIGGER_THAN);
                additiveExp();
                relationalExpL();
                break;

            case(Token::SMALL_EQUAL):
                eat(Token::SMALL_EQUAL);
                additiveExp();
                relationalExpL();
                break;

            case(Token::BIGGER_EQUAL):
                eat(Token::BIGGER_EQUAL);
                additiveExp();
                relationalExpL();
                break;

            default:
                lookAhead--;
                break;
        }
    }

    void SyntaxAnalyzer::equalityExp() {

        relationalExp();
        equalityExpL();
    }

    void SyntaxAnalyzer::equalityExpL() {

        Token::Token tokenTemp = targetAdvance();

        if (tokenTemp.getTokenType() == Token::EQUAL) {

            eat(Token::EQUAL);
            relationalExp();
            equalityExpL();
        } else
            lookAhead--;
    }

    void SyntaxAnalyzer::additiveExp() {

        multiplicativeExp();
        additiveExpL();
    }

    void SyntaxAnalyzer::additiveExpL() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::SUM):
                eat(Token::SUM);
                multiplicativeExp();
                additiveExpL();
                break;

            case(Token::SUBTRACTION):
                eat(Token::SUBTRACTION);
                multiplicativeExp();
                additiveExpL();
                break;

            default:
                lookAhead--;
                break;
        }

    }

    void SyntaxAnalyzer::multiplicativeExp() {

        factorExp();
        multiplicativeExpL();
    }

    void SyntaxAnalyzer::multiplicativeExpL() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::MULTIPLICATION):
                eat(Token::MULTIPLICATION);
                factorExp();
                multiplicativeExpL();
                break;

            case(Token::DIVISION):
                eat(Token::DIVISION);
                factorExp();
                multiplicativeExpL();
                break;

            default:
                lookAhead--;
                break;
        }
    }

    void SyntaxAnalyzer::operationsExp() {

        relationalExp();
    }

    void SyntaxAnalyzer::factorExp() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::IDENTIFIER):

                tokenTemp = targetAdvance();
                lookAhead--;
                if (tokenTemp.getTokenType() == Token::OPEN) {

                    lookAhead--;
                    functionCallExp();
                } else
                    eat(Token::IDENTIFIER);
                break;

            case(Token::NUMBER_FLOAT):
                eat(Token::NUMBER_FLOAT);
                break;

            case(Token::NUMBER_INTEGER):
                eat(Token::NUMBER_INTEGER);
                break;

            case(Token::OPEN):
                eat(Token::OPEN);
                operationsExp();
                targetAdvance();
                eat(Token::CLOSE);
                break;

            default:
                std::cout << "Factor Error\nReceived : "
                        << tokenTemp.tokenTypeToString()
                        << std::endl;
                exit(0);
        }
    }

    /* Retorno de funções */
    void SyntaxAnalyzer::returnValue() {

        targetAdvance();
        eat(Token::RETURN);

        targetAdvance();
        eat(Token::OPEN);

        operationsExp();

        targetAdvance();
        eat(Token::CLOSE);
    }

    /* Expressão IF*/
    void SyntaxAnalyzer::ifStmt() {

        targetAdvance();
        eat(Token::IF);

        operationsExp();

        targetAdvance();
        eat(Token::THEN);

        compoundStmt();

        if (targetAdvance().getTokenType() == Token::OTHERWISE) {

            eat(Token::OTHERWISE);
            compoundStmt();
        }

        eat(Token::END);
    }

    /* Expressão While*/
    void SyntaxAnalyzer::whileStmt() {

        targetAdvance();
        eat(Token::REPEAT);

        compoundStmt();

        targetAdvance();
        eat(Token::UNTIL);

        operationsExp();
    }

    /* Expressão de atribuição */
    void SyntaxAnalyzer::attributionExp() {

        targetAdvance();
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::ATTRIBUTION);

        operationsExp();
    }

    /* Expressão de chamada de função*/
    void SyntaxAnalyzer::paramCallExp() {

        Token::Token tokenTemp = targetAdvance();
        lookAhead--;

        if (tokenTemp.getTokenType() != Token::CLOSE) {

            operationsExp();

            tokenTemp = targetAdvance();

            if (tokenTemp.getTokenType() == Token::COMMA) {

                if (targetAdvance().getTokenType() == Token::CLOSE) {

                    std::cout << "Arguments Error\n";
                    exit(0);
                }

                lookAhead--;
                eat(Token::COMMA);
                paramCallExp();
            } else
                lookAhead--;
        }
    }

    void SyntaxAnalyzer::functionCallExp() {

        targetAdvance();
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::OPEN);

        paramCallExp();

        targetAdvance();
        eat(Token::CLOSE);
    }

    /* Conjunto de expressões possíveis dentro dos escopos */
    void SyntaxAnalyzer::expression() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                lookAhead--;
                variableDec();
                break;

            case(Token::READ):
                lookAhead--;
                readExp();
                break;

            case(Token::WRITE):
                lookAhead--;
                writeExp();
                break;

            case(Token::RETURN):
                lookAhead--;
                returnValue();
                break;

            case(Token::IDENTIFIER):
                tokenTemp = targetAdvance();
                switch (tokenTemp.getTokenType()) {

                    case(Token::ATTRIBUTION):
                        lookAhead -= 2;
                        attributionExp();
                        break;

                    case(Token::OPEN):
                        lookAhead -= 2;
                        functionCallExp();
                        break;
                    default:
                        std::cout << "Expression Error\nReceived: "
                                << tokenTemp.tokenTypeToString()
                                << std::endl;
                        break;
                }
                break;

            case(Token::IF):
                lookAhead--;
                ifStmt();
                break;

            case(Token::REPEAT):
                lookAhead--;
                whileStmt();
                break;

            default:
                std::cout << "Expression Error\nReceived : "
                        << tokenTemp.tokenTypeToString();
                exit(0);
        }
    }

    void SyntaxAnalyzer::compoundStmt() {

        Token::Token tokenTemp = targetAdvance();
        lookAhead--;

        if (tokenTemp.getTokenType() != Token::END
                && tokenTemp.getTokenType() != Token::OTHERWISE
                && tokenTemp.getTokenType() != Token::UNTIL) {

            expression();
            compoundStmt();
        }
    }

    /* Gramática para declaração de uma função */
    void SyntaxAnalyzer::paramFunction() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                lookAhead--;
                variableDec();
                paramFunction();
                break;

            case(Token::COMMA):
                eat(Token::COMMA);
                variableDec();
                paramFunction();
                break;

            case(Token::CLOSE):
                break;

            default:
                std::cout << "ParamFunc Error\nReceived " <<
                        tokenTemp.tokenTypeToString() << std::endl;
                exit(0);
        }
    }

    void SyntaxAnalyzer::prototypeDef() {

        targetAdvance();
        eat(Token::OPEN);

        paramFunction();

        targetAdvance();
        eat(Token::CLOSE);
    }

    void SyntaxAnalyzer::functionDec() {

        type();

        Token::Token tempToken = targetAdvance();

        switch (tempToken.getTokenType()) {

            case(Token::IDENTIFIER):
                eat(Token::IDENTIFIER);
                prototypeDef();
                lookAhead--;
                compoundStmt();
                targetAdvance();
                eat(Token::END);
                break;

            default:
                std::cout << "FunDec Error\nReceived " <<
                        tempToken.tokenTypeToString() << std::endl;
                break;
        }

    }

    /* Faz a primeira chamada para passar pela gramática */
    void SyntaxAnalyzer::initialTarget(std::string fileName) {

        SyntaxAnalyzer::createLexer(fileName);

        Token::Token token = targetAdvance();

        switch (token.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                token = targetAdvance();

                switch (token.getTokenType()) {

                    case(Token::DOUBLE_POINT):
                        lookAhead -= 2;
                        variableDec();
                        break;

                    case(Token::IDENTIFIER):
                        lookAhead -= 2;
                        functionDec();
                        break;

                    default:
                        std::cout << "Erro\nExpected TYPE, received "
                                << token.tokenTypeToString() << std::endl;
                        exit(0);
                }
                break;

            default: std::cout << "Erro\nExpected TYPE, received "
                        << token.tokenTypeToString() << std::endl;
                exit(0);

        }

    }

}
