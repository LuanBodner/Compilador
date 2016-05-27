/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalysis.h"

namespace Syntax {

    std::ifstream fileIn;
    std::ofstream fileOut;

    Tree::Tree * subTree = NULL;

    std::vector<Token::Token> vecToken;

    SyntaxAnalysis::SyntaxAnalysis() {
    }

    SyntaxAnalysis::~SyntaxAnalysis() {
    }

    /*Operações com a árvore*/
    Tree::Tree SyntaxAnalysis::getTree() {

        return syntaxTree;
    }

    void SyntaxAnalysis::setAndAdvance(std::string exp) {

        subTree->setChild(exp);
        subTree = subTree->children[subTree->children.size() - 1];
    }

    /*Operações com Tokens*/
    Token::Token SyntaxAnalysis::targetAdvance() {

        vecToken.push_back(lexer.getNextToken(fileIn));

        return vecToken.back();
    }

    Token::Token SyntaxAnalysis::eat(int Token) {

        if (!vecToken.size())
            targetAdvance();

        Token::Token token = vecToken[0];
        vecToken.erase(vecToken.begin());

        if (token.getTokenType() != Token)
            error.unidentifiedTokenError(Token, token);

        fileOut << "\"" << token.getTokenName() << "\"" << " == "
                << token.tokenTypeToString() << "\n\tLINE : "
                << token.getTokenLine() << "\n\tCOLUMN : "
                << token.getTokenColumn() << "\n";

        return token;
    }

    /*Conjunto de Operações*/
    void SyntaxAnalysis::relationalExpL() {

        Token::Token tokenTemp = vecToken[0];

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
                break;
        }
    }

    void SyntaxAnalysis::equalityExpL() {

        Token::Token tokenTemp = vecToken[0];

        Tree::Tree * tempTree = subTree;

        if (tokenTemp.getTokenType() == Token::EQUAL) {

            setAndAdvance(EQUALSTRING);
            eat(Token::EQUAL);
            relationalExp();
            equalityExpL();
            subTree = tempTree;
        }
    }

    void SyntaxAnalysis::additiveExpL() {

        Token::Token tokenTemp = vecToken[0];

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
                break;
        }

    }

    void SyntaxAnalysis::multiplicativeExpL() {

        Token::Token tokenTemp = vecToken[0];

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
                break;
        }
    }

    void SyntaxAnalysis::factorExp() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::IDENTIFIER):

                tokenTemp = targetAdvance();

                if (tokenTemp.getTokenType() == Token::OPEN)
                    functionCallStmt();
                else
                    subTree->setChild(eat(Token::IDENTIFIER));

                break;

            case(Token::NUMBER_FLOAT):
                subTree->setChild(eat(Token::NUMBER_FLOAT));
                vecToken.clear();
                targetAdvance();
                break;

            case(Token::NUMBER_INTEGER):
                subTree->setChild(eat(Token::NUMBER_INTEGER));
                vecToken.clear();
                targetAdvance();
                break;

            case(Token::OPEN):
                eat(Token::OPEN);
                operationsExp();
                eat(Token::CLOSE);
                targetAdvance();
                break;

            case(Token::CLOSE):break;
            default: this->error.factorError(tokenTemp);
        }
    }

    void SyntaxAnalysis::additiveExp() {

        multiplicativeExp();
        additiveExpL();
    }

    void SyntaxAnalysis::relationalExp() {

        additiveExp();
        relationalExpL();
    }

    void SyntaxAnalysis::equalityExp() {

        relationalExp();
        equalityExpL();
    }

    void SyntaxAnalysis::multiplicativeExp() {

        factorExp();
        multiplicativeExpL();
    }

    void SyntaxAnalysis::operationsExp() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(OPEXPSTRING);

        equalityExp();

        subTree = tempTree;
    }

    /*Chamada de função de leitura/escrita*/
    void SyntaxAnalysis::writeStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(WRITESTRING);

        eat(Token::WRITE);
        eat(Token::OPEN);

        operationsExp();

        eat(Token::CLOSE);

        vecToken.clear();

        subTree = tempTree;
    }

    void SyntaxAnalysis::readStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(READSTRING);

        eat(Token::READ);
        eat(Token::OPEN);

        subTree->setChild(eat(Token::IDENTIFIER));

        eat(Token::CLOSE);

        subTree = tempTree;

        vecToken.clear();
    }

    /*Chamada de Retorno*/
    void SyntaxAnalysis::returnValue() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(RETURNSTRING);

        Token::Token t = eat(Token::RETURN);
        eat(Token::OPEN);

        operationsExp();

        subTree->setChild(t);

        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /*Operação de atribuição*/
    void SyntaxAnalysis::attributionStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(ATTSTRING);

        subTree->setChild(eat(Token::IDENTIFIER));

        eat(Token::ATTRIBUTION);
        eat(Token::OPEN);

        operationsExp();

        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /*If Statement*/
    void SyntaxAnalysis::ifStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(IFSTRING);

        eat(Token::IF);
        eat(Token::OPEN);

        operationsExp();

        eat(Token::CLOSE);
        eat(Token::THEN);

        compoundStmt();

        if (vecToken[0].getTokenType() == Token::OTHERWISE) {

            Tree::Tree * newTempTree = subTree;
            setAndAdvance(OTHERSTRING);

            eat(Token::OTHERWISE);

            compoundStmt();

            eat(Token::END);

            subTree = newTempTree;
        } else
            eat(Token::END);

        subTree = tempTree;
    }

    /*Laço de Repetição*/
    void SyntaxAnalysis::whileStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(WHILESTRING);

        eat(Token::REPEAT);

        compoundStmt();

        eat(Token::UNTIL);
        eat(Token::OPEN);

        operationsExp();

        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /*Conjunto de Construções*/
    void SyntaxAnalysis::expression() {

        Token::Token tokenTemp = vecToken[0];

        Tree::Tree * tempTree = subTree;
        setAndAdvance(EXPSTRING);

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                targetAdvance();
                variableDecStmt();
                break;

            case(Token::WRITE):
                writeStmt();
                break;

            case(Token::READ):
                readStmt();
                break;

            case(Token::RETURN):
                returnValue();
                break;

            case(Token::IDENTIFIER):
                tokenTemp = targetAdvance();
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

    /*Identificando Declaração de variáveis*/
    void SyntaxAnalysis::type(Token::Token token) {

        subTree->setChild(token);

        switch (token.getTokenType()) {
            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                eat(token.getTokenType());
                break;
            default:
                error.typeError(token);
        }
    }

    void SyntaxAnalysis::variableDecStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(VARDECSTRING);

        type(vecToken[0]);

        eat(Token::DOUBLE_POINT);

        subTree->setChild(eat(Token::IDENTIFIER));

        subTree = tempTree;

        vecToken.clear();
    }

    /*Identificando Definição de funções*/
    void SyntaxAnalysis::paramFunctionStmt() {

        Token::Token tokenTemp = targetAdvance();

        switch (tokenTemp.getTokenType()) {

            case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):
                variableDecStmt();
                paramFunctionStmt();
                break;

            case(Token::COMMA):
                eat(Token::COMMA);
                targetAdvance();
                variableDecStmt();
                paramFunctionStmt();
                break;

            case(Token::CLOSE):
                break;

            default: this->error.parameterDeclarationError(tokenTemp);
        }
    }

    void SyntaxAnalysis::prototypeDefStmt() {

        eat(Token::OPEN);

        Tree::Tree * tempTree = subTree;
        setAndAdvance(PARAMDECSTRING);

        paramFunctionStmt();

        eat(Token::CLOSE);

        vecToken.clear();

        subTree = tempTree;
    }

    void SyntaxAnalysis::functionDecStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(FUNCDECSTRING);

        type(vecToken[0]);

        subTree->setChild(vecToken[0]);

        switch (vecToken[0].getTokenType()) {
            case(Token::IDENTIFIER):
                eat(Token::IDENTIFIER);
                prototypeDefStmt();
                compoundStmt();
                eat(Token::END);
                break;
            default:
                error.functionDeclarationError(vecToken[0]);
        }

        subTree = tempTree;
    }

    /*Chamada de função*/
    void SyntaxAnalysis::paramCallStmt() {

        Token::Token tokenTemp;

        operationsExp();

        if (vecToken[0].getTokenType() != Token::CLOSE) {

            tokenTemp = vecToken[0];

            if (tokenTemp.getTokenType() == Token::COMMA) {

                eat(Token::COMMA);

                paramCallStmt();
            } else
                this->error.numberOfArgumentsError(tokenTemp);
        }
    }

    void SyntaxAnalysis::functionCallStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(FUNCCALLSTRING);

        subTree->setChild(eat(Token::IDENTIFIER));

        eat(Token::OPEN);

        paramCallStmt();

        eat(Token::CLOSE);

        subTree = tempTree;
    }

    void SyntaxAnalysis::initialTarget(std::string in, std::string out) {

        fileIn.open(in.c_str(), std::ifstream::in);
        fileOut.open(out.c_str(), std::ofstream::out);

        this->error.openTinyFile(fileIn);

        subTree = &(this->syntaxTree);

        Token::Token token = targetAdvance();

        while (token.getTokenName().compare("@EOF")) {

            subTree->setExp(DECSTRING);

            switch (token.getTokenType()) {

                case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):

                    token = targetAdvance();

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

            token = targetAdvance();
        }
    }
}