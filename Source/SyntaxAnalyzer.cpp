/* 
 * File:   SyntaxAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on March 31, 2016, 9:33 AM
 */

#include "SyntaxAnalyzer.h"

namespace SyntaxAnalyzer {

    unsigned int lookAhead = 0;

    Tree::Tree * subTree = NULL;

    std::ifstream file;

    /* Funções básicas da classe SyntaxAnalyzer*/
    SyntaxAnalyzer::SyntaxAnalyzer() {
    }

    SyntaxAnalyzer::~SyntaxAnalyzer() {
    }

    /*void SyntaxAnalyzer::createLexer(std::string in, std::string out) {

        lexer = Lex::LexicalAnalyzer(in);
        printTokens(out);
    }*/

    /* Percorre pela lista de tokens na frente do eat */
    Token::Token SyntaxAnalyzer::targetAdvance(std::ifstream & file) {

        this->vecToken.push_back(lexer.getNextToken(file));
        lookAhead++;
        return vecToken[vecToken.size() - 1];
    }

    /* Faz a mudança de token para o próximo */
    void SyntaxAnalyzer::eat(int Token) {

        Token::Token tokenTemp = vecToken[0];

        vecToken.erase(vecToken.begin());

        if (tokenTemp.getTokenType() != Token)
            this->error.unidentifiedTokenError(Token, tokenTemp);
    }

    /* Gramática para declaração de variável */
    void SyntaxAnalyzer::type() {

        Token::Token tokenTemp = vecToken[0];

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

    void SyntaxAnalyzer::variableDecStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(VARDECSTRING);

        type();

        //targetAdvance(file);
        eat(Token::DOUBLE_POINT);

        subTree->setChild(targetAdvance(file));
        eat(Token::IDENTIFIER);

        subTree = tempTree;
    }

    /* Leitura e escrita */
    void SyntaxAnalyzer::readStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(READSTRING);

        targetAdvance(file);
        eat(Token::READ);

        targetAdvance(file);
        eat(Token::OPEN);

        subTree->setChild(targetAdvance(file));
        eat(Token::IDENTIFIER);

        targetAdvance(file);
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    void SyntaxAnalyzer::writeStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(WRITESTRING);

        targetAdvance(file);
        eat(Token::WRITE);

        targetAdvance(file);
        eat(Token::OPEN);

        operationsExp();

        targetAdvance(file);
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /* Caminho da recursividade das operações */
    void SyntaxAnalyzer::relationalExp() {

        additiveExp();
        relationalExpL();
    }

    void SyntaxAnalyzer::relationalExpL() {

        Token::Token tokenTemp = targetAdvance(file);

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

    void SyntaxAnalyzer::equalityExp() {

        relationalExp();
        equalityExpL();
    }

    void SyntaxAnalyzer::equalityExpL() {

        Token::Token tokenTemp = targetAdvance(file);

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

    void SyntaxAnalyzer::additiveExp() {

        multiplicativeExp();
        additiveExpL();
    }

    void SyntaxAnalyzer::additiveExpL() {

        Token::Token tokenTemp = targetAdvance(file);

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

    void SyntaxAnalyzer::multiplicativeExp() {

        factorExp();
        multiplicativeExpL();
    }

    void SyntaxAnalyzer::multiplicativeExpL() {

        Token::Token tokenTemp = targetAdvance(file);

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

    void SyntaxAnalyzer::operationsExp() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(OPEXPSTRING);

        equalityExp();
        subTree = tempTree;
    }

    void SyntaxAnalyzer::factorExp() {

        Token::Token tokenTemp = targetAdvance(file);

        switch (tokenTemp.getTokenType()) {

            case(Token::IDENTIFIER):

                tokenTemp = targetAdvance(file);
                lookAhead -= 2;

                if (tokenTemp.getTokenType() == Token::OPEN)
                    functionCallStmt();
                else {

                    subTree->setChild(targetAdvance(file));
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
                targetAdvance(file);
                eat(Token::CLOSE);
                break;

            default: this->error.factorError(tokenTemp);
        }
    }

    /* Retorno de funções */
    void SyntaxAnalyzer::returnValue() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(RETURNSTRING);

        targetAdvance(file);
        eat(Token::RETURN);

        targetAdvance(file);
        eat(Token::OPEN);

        operationsExp();

        targetAdvance(file);
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /* Expressão IF*/
    void SyntaxAnalyzer::ifStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(IFSTRING);

        targetAdvance(file);
        eat(Token::IF);

        operationsExp();

        targetAdvance(file);
        eat(Token::THEN);

        compoundStmt();

        if (targetAdvance(file).getTokenType() == Token::OTHERWISE) {

            Tree::Tree * newTempTree = subTree;
            eat(Token::OTHERWISE);
            setAndAdvance(OTHERSTRING);

            compoundStmt();

            targetAdvance(file);
            eat(Token::END);

            subTree = newTempTree;
        } else
            eat(Token::END);

        subTree = tempTree;
    }

    /* Expressão While*/
    void SyntaxAnalyzer::whileStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(WHILESTRING);

        targetAdvance(file);
        eat(Token::REPEAT);

        compoundStmt();

        targetAdvance(file);
        eat(Token::UNTIL);

        operationsExp();

        subTree = tempTree;
    }

    /* Expressão de atribuição */
    void SyntaxAnalyzer::attributionStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(ATTSTRING);

        subTree->setChild(targetAdvance(file));
        eat(Token::IDENTIFIER);

        targetAdvance(file);
        eat(Token::ATTRIBUTION);

        operationsExp();

        subTree = tempTree;
    }

    /* Expressão de chamada de função*/
    void SyntaxAnalyzer::paramCallStmt() {

        Token::Token tokenTemp = targetAdvance(file);
        lookAhead--;

        if (tokenTemp.getTokenType() != Token::CLOSE) {

            operationsExp();

            tokenTemp = targetAdvance(file);
            lookAhead--;

            if (tokenTemp.getTokenType() == Token::COMMA) {

                if (targetAdvance(file).getTokenType() == Token::CLOSE)
                    this->error.numberOfArgumentsError(tokenTemp);

                eat(Token::COMMA);

                paramCallStmt();
            }
        }
    }

    void SyntaxAnalyzer::functionCallStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(FUNCCALLSTRING);

        subTree->setChild(targetAdvance(file));
        eat(Token::IDENTIFIER);

        targetAdvance(file);
        eat(Token::OPEN);

        paramCallStmt();

        targetAdvance(file);
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    /* Conjunto de expressões possíveis dentro dos escopos */
    void SyntaxAnalyzer::expression() {

        Token::Token tokenTemp = targetAdvance(file);
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
                tokenTemp = targetAdvance(file);
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

    void SyntaxAnalyzer::compoundStmt() {

        Token::Token tokenTemp = targetAdvance(file);
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
    void SyntaxAnalyzer::paramFunctionStmt() {

        Token::Token tokenTemp = targetAdvance(file);
        tokenTemp.print();

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

    void SyntaxAnalyzer::prototypeDefStmt() {

        Token::Token t = targetAdvance(file);
        t.print();
        eat(Token::OPEN);

        Tree::Tree * tempTree = subTree;
        setAndAdvance(PARAMDECSTRING);

        paramFunctionStmt();

        //targetAdvance(file);
        eat(Token::CLOSE);

        subTree = tempTree;
    }

    void SyntaxAnalyzer::functionDecStmt() {

        Tree::Tree * tempTree = subTree;
        setAndAdvance(FUNCDECSTRING);

        type();

        Token::Token tempToken = vecToken[0];
        tempToken.print();

        subTree->setChild(tempToken);

        switch (tempToken.getTokenType()) {

            case(Token::IDENTIFIER):
                eat(Token::IDENTIFIER);
                prototypeDefStmt();
                lookAhead--;
                compoundStmt();
                targetAdvance(file);
                eat(Token::END);
                break;

            default: this->error.functionDeclarationError(tempToken);
        }

        subTree = tempTree;
    }

    /* Faz a primeira chamada para passar pela gramática */
    void SyntaxAnalyzer::initialTarget(std::string lexIn, std::string lexOut) {

        //SyntaxAnalyzer::createLexer(in, out);
        file.open(lexIn);

        subTree = &(this->syntaxTree);

        while (!file.eof()) {

            subTree->setExp(DECSTRING);

            Token::Token token = targetAdvance(file);
            token.print();

            switch (token.getTokenType()) {

                case(Token::INTEGER): case(Token::FLOAT): case(Token::VOID):

                    token = targetAdvance(file);
                    lookAhead -= 2;

                    switch (token.getTokenType()) {

                        case(Token::DOUBLE_POINT):
                            token.print();
                            variableDecStmt();
                            break;

                        case(Token::IDENTIFIER):
                            token.print();
                            functionDecStmt();
                            break;

                        default: this->error.variableDeclarationError(token);
                    }
                    break;

                default: this->error.variableDeclarationError(token);
            }
        }
    }

    Tree::Tree SyntaxAnalyzer::getTree() {

        return syntaxTree;
    }

    void SyntaxAnalyzer::setAndAdvance(std::string exp) {

        subTree->setChild(exp);
        subTree = subTree->children[subTree->children.size() - 1];
    }

    void SyntaxAnalyzer::printTokens(std::string str) {

        Token::Token tokenTemp;

        std::ofstream output;
        output.open(str, std::ofstream::out);

        do {

            tokenTemp = targetAdvance(file);

            output << "\"" << tokenTemp.getTokenName() << "\"" << " == "
                    << tokenTemp.tokenTypeToString() << "\n\tLINE : "
                    << tokenTemp.getTokenLine() << "\n\tCOLUMN : "
                    << tokenTemp.getTokenColumn() << "\n";
        } while (!tokenTemp.getTokenName().compare("@EOF"));

        lookAhead = 0;
    }
}