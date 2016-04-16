/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalyzer.h"

namespace SyntaxAnalyzer {

    unsigned int lookAhead = 0;

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
            std::cout << "Eat Error " << tokenTemp.tokenTypeToString() << std::endl;
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

    /* Gramática para chamada de uma função */

    /* Leitura e escrita */
    void SyntaxAnalyzer::read() {

        targetAdvance();
        eat(Token::READ);

        targetAdvance();
        eat(Token::OPEN);

        targetAdvance();
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::CLOSE);
    }

    /* Expressões das operações

<factor> ::= '(' <operationsExp> ')'
        | 'numberFloat'
        | 'numberInt'
        | 'id'
     *  */
    void SyntaxAnalyzer::equalityExp() {

        relationalExp();
        equalityExpAux();
    }

    void SyntaxAnalyzer::equalityExpAux() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::EQUAL):
                eat(Token::EQUAL);
                relationalExp();
                equalityExpAux();
                break;
            default:
                std::cout << "Equality Error\n";
                exit(0);
        }
    }

    void SyntaxAnalyzer::relationalExp() {

        additiveExp();
        relationalExpAux();
    }

    void SyntaxAnalyzer::relationalExpAux() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::SMALLER_THAN):
                eat(Token::SMALLER_THAN);
                additiveExp();
                relationalExpAux();
                break;
            case(Token::BIGGER_THAN):
                eat(Token::BIGGER_THAN);
                additiveExp();
                relationalExpAux();
                break;
            case(Token::BIGGER_EQUAL):
                eat(Token::BIGGER_EQUAL);
                additiveExp();
                relationalExpAux();
                break;
            case(Token::SMALL_EQUAL):
                eat(Token::SMALL_EQUAL);
                additiveExp();
                relationalExpAux();
                break;
            default:
                std::cout << "Relational Error\n";
                exit(0);

        }
    }

    void SyntaxAnalyzer::additiveExp() {

        multiplicativeExp();
        additiveExpAux();
    }

    void SyntaxAnalyzer::additiveExpAux() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::SUM):
                eat(Token::SUM);
                multiplicativeExp();
                additiveExpAux();
                break;
            case(Token::SUBTRACTION):
                eat(Token::SUBTRACTION);
                multiplicativeExp();
                additiveExpAux();
                break;
            default:
                std::cout << "Addition Error\n";
                exit(0);
        }

    }

    void SyntaxAnalyzer::multiplicativeExp() {

        factor();
        multiplicativeExpAux();
    }

    void SyntaxAnalyzer::multiplicativeExpAux() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::MULTIPLICATION):
                eat(Token::MULTIPLICATION);
                factor();
                multiplicativeExpAux();
                break;
            case(Token::DIVISION):
                eat(Token::DIVISION);
                factor();
                multiplicativeExpAux();
                break;
            default:
                std::cout << "Multiplication Error\n";
                exit(0);
        }
    }

    void SyntaxAnalyzer::operationsExp() {


    }

    void SyntaxAnalyzer::factor() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::IDENTIFIER):
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
                std::cout << "Factor Error\n";
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
                read();
                break;
            case(Token::RETURN):
                lookAhead--;
                returnValue();
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

        if (tokenTemp.getTokenType() != Token::END) {

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
