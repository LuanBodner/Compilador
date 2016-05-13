/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalysis.h"

namespace Syntax {

    unsigned int lookAhead = 0;

    Tree::Tree * subTree = NULL;

    /* Funções básicas da classe SyntaxAnalyzer*/
    SyntaxAnalysis::SyntaxAnalysis() {
    }

    SyntaxAnalysis::~SyntaxAnalysis() {
    }

    void SyntaxAnalysis::createLexer(std::string in, std::string out) {

        lexer = Lexical::LexicalAnalyzer(in);
        printTokens(out);
    }

    /* Percorre pela lista de tokens na frente do eat */
    Token::Token SyntaxAnalysis::targetAdvance() {

        return lexer.getTokenByPos(lookAhead++);
    }

    /* Faz a mudança de token para o próximo */
    void SyntaxAnalysis::eat(int Token) {

        Token::Token tokenTemp = lexer.getNextToken();

        if (tokenTemp.getTokenType() != Token)
            this->error.unidentifiedTokenError(Token, tokenTemp);
    }

    /* Gramática para declaração de variável */
    void SyntaxAnalysis::type() {

        Token::Token tokenTemp = targetAdvance();

        subTree->setChild(tokenTemp);

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

            default: this->error.typeError(tokenTemp);
        }
    }

    void SyntaxAnalysis::variableDecStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(VARDECSTRING);

        type();

        targetAdvance();
        eat(Token::DOUBLE_POINT);

        subTree->setChild(targetAdvance());
        eat(Token::IDENTIFIER);

        subTree = tempTree;
    }

    /* Leitura e escrita */
    void SyntaxAnalysis::readStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(READSTRING);

        targetAdvance();
        eat(Token::READ);

        targetAdvance();
        eat(Token::OPEN);

        subTree->setChild(targetAdvance());
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    void SyntaxAnalysis::writeStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(WRITESTRING);

        targetAdvance();
        eat(Token::WRITE);

        targetAdvance();
        eat(Token::OPEN);

        operationsExp();

        targetAdvance();
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /* Caminho da recursividade das operações */
    void SyntaxAnalysis::relationalExp() {

        additiveExp();
        relationalExpL();
    }

    void SyntaxAnalysis::relationalExpL() {

        Token::Token tokenTemp = targetAdvance();

        Tree::Tree * tempTree = subTree;

        switch (tokenTemp.getTokenType()) {

            case(Token::LESS_THAN):
                setAndAdvance(LESSTSTRING);
                eat(Token::LESS_THAN);
                additiveExp();
                relationalExpL();
                subTree = tempTree;
                break;

            case(Token::BIGGER_THAN):
                setAndAdvance(BIGGERTSTRING);
                eat(Token::BIGGER_THAN);
                additiveExp();
                relationalExpL();
                subTree = tempTree;
                break;

            case(Token::LESS_EQUAL):
                setAndAdvance(LESSESTRING);
                eat(Token::LESS_EQUAL);
                additiveExp();
                relationalExpL();
                subTree = tempTree;
                break;

            case(Token::BIGGER_EQUAL):
                setAndAdvance(BIGGERESTRING);
                eat(Token::BIGGER_EQUAL);
                additiveExp();
                relationalExpL();
                subTree = tempTree;
                break;

            default:
                lookAhead--;
                break;
        }
    }

    void SyntaxAnalysis::equalityExp() {

        relationalExp();
        equalityExpL();
    }

    void SyntaxAnalysis::equalityExpL() {

        Token::Token tokenTemp = targetAdvance();

        Tree::Tree * tempTree = subTree;

        if (tokenTemp.getTokenType() == Token::EQUAL) {

            setAndAdvance(EQUALSTRING);
            eat(Token::EQUAL);
            relationalExp();
            equalityExpL();
            subTree = tempTree;
        } else
            lookAhead--;
    }

    void SyntaxAnalysis::additiveExp() {

        multiplicativeExp();
        additiveExpL();
    }

    void SyntaxAnalysis::additiveExpL() {

        Token::Token tokenTemp = targetAdvance();

        Tree::Tree * tempTree = subTree;

        switch (tokenTemp.getTokenType()) {

            case(Token::SUM):
                setAndAdvance(SUMEXPSTRING);
                eat(Token::SUM);
                multiplicativeExp();
                additiveExpL();
                subTree = tempTree;
                break;

            case(Token::SUBTRACTION):
                setAndAdvance(SUBEXPSTRING);
                eat(Token::SUBTRACTION);
                multiplicativeExp();
                additiveExpL();
                subTree = tempTree;
                break;

            default:
                lookAhead--;
                break;
        }

    }

    void SyntaxAnalysis::multiplicativeExp() {

        factorExp();
        multiplicativeExpL();
    }

    void SyntaxAnalysis::multiplicativeExpL() {

        Token::Token tokenTemp = targetAdvance();

        Tree::Tree * tempTree = subTree;

        switch (tokenTemp.getTokenType()) {

            case(Token::MULTIPLICATION):
                setAndAdvance(MULTEXPSTRING);
                eat(Token::MULTIPLICATION);
                factorExp();
                multiplicativeExpL();
                subTree = tempTree;
                break;

            case(Token::DIVISION):
                setAndAdvance(DIVEXPSTRING);
                eat(Token::DIVISION);
                factorExp();
                multiplicativeExpL();
                subTree = tempTree;
                break;

            default:
                lookAhead--;
                break;
        }
    }

    void SyntaxAnalysis::operationsExp() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(OPEXPSTRING);

        equalityExp();
        subTree = tempTree;
    }

    void SyntaxAnalysis::factorExp() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::IDENTIFIER):

                tokenTemp = targetAdvance();
                lookAhead -= 2;

                if (tokenTemp.getTokenType() == Token::OPEN)
                    functionCallStmt();
                else {

                    subTree->setChild(targetAdvance());
                    eat(Token::IDENTIFIER);
                }
                break;

            case(Token::NUMBER_FLOAT):
                subTree->setChild(tokenTemp);
                eat(Token::NUMBER_FLOAT);
                break;

            case(Token::NUMBER_INTEGER):
                subTree->setChild(tokenTemp);
                eat(Token::NUMBER_INTEGER);
                break;

            case(Token::OPEN):
                eat(Token::OPEN);
                operationsExp();
                targetAdvance();
                eat(Token::CLOSE);
                break;

            default: this->error.factorError(tokenTemp);
        }
    }

    /* Retorno de funções */
    void SyntaxAnalysis::returnValue() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(RETURNSTRING);

        targetAdvance();
        eat(Token::RETURN);

        targetAdvance();
        eat(Token::OPEN);

        operationsExp();

        targetAdvance();
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /* Expressão IF*/
    void SyntaxAnalysis::ifStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(IFSTRING);

        targetAdvance();
        eat(Token::IF);

        operationsExp();

        targetAdvance();
        eat(Token::THEN);

        compoundStmt();

        if (targetAdvance().getTokenType() == Token::OTHERWISE) {

            Tree::Tree * newTempTree = subTree;
            eat(Token::OTHERWISE);
            setAndAdvance(OTHERSTRING);

            compoundStmt();

            targetAdvance();
            eat(Token::END);

            subTree = newTempTree;
        } else
            eat(Token::END);

        subTree = tempTree;
    }

    /* Expressão While*/
    void SyntaxAnalysis::whileStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(WHILESTRING);

        targetAdvance();
        eat(Token::REPEAT);

        compoundStmt();

        targetAdvance();
        eat(Token::UNTIL);

        operationsExp();

        subTree = tempTree;
    }

    /* Expressão de atribuição */
    void SyntaxAnalysis::attributionStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(ATTSTRING);

        subTree->setChild(targetAdvance());
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::ATTRIBUTION);

        operationsExp();

        subTree = tempTree;
    }

    /* Expressão de chamada de função*/
    void SyntaxAnalysis::paramCallStmt() {

        Token::Token tokenTemp = targetAdvance();
        lookAhead--;

        if (tokenTemp.getTokenType() != Token::CLOSE) {

            operationsExp();

            tokenTemp = targetAdvance();
            lookAhead--;

            if (tokenTemp.getTokenType() == Token::COMMA) {

                if (targetAdvance().getTokenType() == Token::CLOSE)
                    this->error.numberOfArgumentsError(tokenTemp);

                eat(Token::COMMA);

                paramCallStmt();
            }
        }
    }

    void SyntaxAnalysis::functionCallStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(FUNCCALLSTRING);

        subTree->setChild(targetAdvance());
        eat(Token::IDENTIFIER);

        targetAdvance();
        eat(Token::OPEN);

        paramCallStmt();

        targetAdvance();
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /* Conjunto de expressões possíveis dentro dos escopos */
    void SyntaxAnalysis::expression() {

        Token::Token tokenTemp = targetAdvance();
        lookAhead--;

        Tree::Tree * tempTree = subTree;
        setAndAdvance(EXPSTRING);

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                variableDecStmt();
                break;

            case(Token::READ):
                readStmt();
                break;

            case(Token::WRITE):
                writeStmt();
                break;

            case(Token::RETURN):
                returnValue();
                break;

            case(Token::IDENTIFIER):
                lookAhead++;
                tokenTemp = targetAdvance();
                lookAhead -= 2;
                switch (tokenTemp.getTokenType()) {

                    case(Token::ATTRIBUTION):
                        attributionStmt();
                        break;

                    case(Token::OPEN):
                        functionCallStmt();
                        break;

                    default: this->error.expressionError(tokenTemp);
                }
                break;

            case(Token::IF):
                ifStmt();
                break;

            case(Token::REPEAT):
                whileStmt();
                break;

            default: this->error.expressionError(tokenTemp);
        }

        subTree = tempTree;
    }

    void SyntaxAnalysis::compoundStmt() {

        Token::Token tokenTemp = targetAdvance();
        lookAhead--;

        Tree::Tree * tempTree = subTree;

        if (tokenTemp.getTokenType() != Token::END
                && tokenTemp.getTokenType() != Token::OTHERWISE
                && tokenTemp.getTokenType() != Token::UNTIL) {

            setAndAdvance(COMPSTMTSTRING);

            expression();
            compoundStmt();
        }

        subTree = tempTree;
    }

    /* Gramática para declaração de uma função */
    void SyntaxAnalysis::paramFunctionStmt() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                lookAhead--;
                variableDecStmt();
                paramFunctionStmt();
                break;

            case(Token::COMMA):
                eat(Token::COMMA);
                variableDecStmt();
                paramFunctionStmt();
                break;

            case(Token::CLOSE):
                break;

            default: this->error.parameterDeclarationError(tokenTemp);
        }
    }

    void SyntaxAnalysis::prototypeDefStmt() {

        targetAdvance();
        eat(Token::OPEN);

        Tree::Tree * tempTree = subTree;
        setAndAdvance(PARAMDECSTRING);

        paramFunctionStmt();

        targetAdvance();
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    void SyntaxAnalysis::functionDecStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(FUNCDECSTRING);

        type();

        Token::Token tempToken = targetAdvance();

        subTree->setChild(tempToken);

        switch (tempToken.getTokenType()) {

            case(Token::IDENTIFIER):
                eat(Token::IDENTIFIER);
                prototypeDefStmt();
                lookAhead--;
                compoundStmt();
                targetAdvance();
                eat(Token::END);
                break;

            default: this->error.functionDeclarationError(tempToken);
        }

        subTree = tempTree;
    }

    /* Faz a primeira chamada para passar pela gramática */
    void SyntaxAnalysis::initialTarget(std::string in, std::string out) {

        SyntaxAnalysis::createLexer(in, out);

        subTree = &(this->syntaxTree);

        while (lookAhead < lexer.tokenVectorSize()) {

            subTree->setExp(DECSTRING);

            Token::Token token = targetAdvance();

            switch (token.getTokenType()) {

                case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):

                    token = targetAdvance();
                    lookAhead -= 2;

                    switch (token.getTokenType()) {

                        case(Token::DOUBLE_POINT):
                            variableDecStmt();
                            break;

                        case(Token::IDENTIFIER):
                            functionDecStmt();
                            break;

                        default: this->error.variableDeclarationError(token);
                    }
                    break;

                default: this->error.variableDeclarationError(token);
            }
        }
    }

    Tree::Tree SyntaxAnalysis::getTree() {

        return syntaxTree;
    }

    void SyntaxAnalysis::setAndAdvance(std::string exp) {

        subTree->setChild(exp);
        subTree = subTree->children[subTree->children.size() - 1];
    }

    void SyntaxAnalysis::printTokens(std::string str) {

        Token::Token tokenTemp;

        std::ofstream output;
        output.open(str, std::ofstream::out);

        do {

            tokenTemp = targetAdvance();

            output << "\"" << tokenTemp.getTokenName() << "\"" << " == "
                    << tokenTemp.tokenTypeToString() << "\n\tLINE : "
                    << tokenTemp.getTokenLine() << "\n\tCOLUMN : "
                    << tokenTemp.getTokenColumn() << "\n";
        } while (lookAhead < lexer.tokenVectorSize());

        lookAhead = 0;
    }
}