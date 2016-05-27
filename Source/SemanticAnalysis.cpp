/* 
 * File:   SemanticAnalysis.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 8, 2016, 5:16 PM
 */

#include "SemanticAnalysis.h"

namespace Semantic {

    bool main = false;

    std::string otype;

    int scope = 0;

    typedef std::pair<std::string, std::string> nameFunction;

    std::vector<nameFunction> returnType;

    SemanticAnalysis::SemanticAnalysis() {
    }

    SemanticAnalysis::~SemanticAnalysis() {
    }

    int SemanticAnalysis::verifyTable(scopeName key, Tree::Tree& tree) {

        for (; key.first >= 0; key.first--) {

            boost::unordered_map<scopeName, vectorString>::const_iterator entry;
            entry = symbolTable.find(key);

            if (entry != symbolTable.end())
                if ((key.first != scope && !entry->second[1].compare(GL)) ||
                        (key.first != scope && !entry->second[1].compare(FU)) ||
                        key.first == scope)
                    break;
        }

        if (key.first == -1)
            error.variableNotDeclaredError(tree.token);

        return key.first;
    }

    void SemanticAnalysis::variableDeclaration(Tree::Tree& tree, int level) {

        int scopeL;

        if (level == 1) scopeL = 0;
        else scopeL = scope;

        scopeName t(scopeL, tree.children[1]->token.getTokenName());

        if (symbolTable.find(t) != symbolTable.end())
            error.declarationScopeError(tree.children[1]->token);

        symbolTable.emplace(t, std::vector<std::string>());

        if (!tree.children[0]->token.getTokenName().compare("vazio"))
            error.variableVoidError(tree.children[1]->token);
        symbolTable[t].push_back(tree.children[0]->token.getTokenName());

        if (level == 1)
            symbolTable[t].push_back(GL);

        symbolTable[t].push_back(NI);
    }

    void SemanticAnalysis::parameterTypes(Tree::Tree& tree, scopeName scope) {

        if (!tree.children.empty())
            for (unsigned int i = 0; i < tree.children.size(); i++)
                symbolTable[scope].push_back(tree.children[i]->children[0]->token.getTokenName());
    }

    void SemanticAnalysis::functionDeclaration(Tree::Tree& tree) {

        int auxScope = scope;
        scope = 0;

        scopeName s(scope, tree.children[1]->token.getTokenName());

        if (symbolTable.find(s) != symbolTable.end())
            error.declarationScopeError(tree.children[1]->token);

        symbolTable.emplace(s, std::vector<std::string>());
        symbolTable[s].push_back(tree.children[0]->token.getTokenName());

        nameFunction nf(tree.children[0]->token.getTokenName(), tree.children[1]->token.getTokenName());
        returnType.push_back(nf);

        if (!s.second.compare("principal"))
            main = true;

        symbolTable[s].push_back(FU);
        symbolTable[s].push_back(std::to_string(tree.children[2]->children.size()));

        parameterTypes(*tree.children[2], s);

        scope = ++auxScope;
    }

    void SemanticAnalysis::operationExpression(Tree::Tree& tree) {

        static int counter = 0;

        if (tree.children.size()) {

            scopeName sn(scope, tree.children[0]->token.getTokenName());

            if (tree.children[0]->token.getTokenType() == Token::IDENTIFIER) {

                sn.first = verifyTable(sn, *tree.children[0]);

                if (!symbolTable[sn][symbolTable[sn].size() - 1].compare(NI))
                    error.variableNotDefinedError(tree.children[0]->token);

                if (!symbolTable[sn][1].compare(FU))
                    functionCallStatement(tree);

                if (!counter)
                    otype = symbolTable[sn][0];

                if (!symbolTable[sn][0].compare("vazio"))
                    error.voidAttributionError(tree.children[0]->token);

                else if (symbolTable[sn][0].compare(otype))
                    error.expressionTypeWarning(tree.children[0]->token);
            } else {

                Token::TokenType t = tree.children[0]->token.getTokenType();

                if (!counter) {

                    if (t == Token::NUMBER_FLOAT)
                        otype = "flutuante";
                    else otype = "inteiro";
                }

                if ((otype.compare("inteiro") && t == Token::NUMBER_INTEGER) ||
                        (otype.compare("flutuante") && t == Token::NUMBER_FLOAT))
                    error.expressionTypeWarning(tree.children[0]->token);
            }

            for (unsigned int i = 0; i < tree.children.size(); i++) {

                if (tree.children[i]) {

                    counter++;
                    operationExpression(*tree.children[i]);
                    counter--;
                }
            }
        }
    }

    void SemanticAnalysis::operationExpression(Tree::Tree& tree, Token::TokenType ttype) {

        if (tree.children.size()) {

            scopeName sn(scope, tree.children[0]->token.getTokenName());

            if (tree.children[0]->token.getTokenType() == Token::IDENTIFIER) {

                sn.first = verifyTable(sn, *tree.children[0]);

                if (!symbolTable[sn][symbolTable[sn].size() - 1].compare(NI))
                    error.variableNotDefinedError(tree.children[0]->token);

                if (!symbolTable[sn][1].compare(FU))
                    functionCallStatement(tree);

                if (!symbolTable[sn][0].compare("vazio"))
                    error.voidAttributionError(tree.children[0]->token);

                else if ((symbolTable[sn][0].compare("flutuante") && ttype == Token::FLOAT) ||
                        (symbolTable[sn][0].compare("inteiro") && ttype == Token::INTEGER))
                    error.expressionTypeWarning(tree.children[0]->token);
            } else if ((tree.children[0]->token.getTokenType() == Token::NUMBER_FLOAT
                    && ttype == Token::INTEGER) ||
                    (tree.children[0]->token.getTokenType() == Token::NUMBER_INTEGER
                    && ttype == Token::FLOAT))
                error.expressionTypeWarning(tree.children[0]->token);

            for (unsigned int i = 0; i < tree.children.size(); i++)
                if (tree.children[i])
                    operationExpression(*tree.children[i], ttype);
        }
    }

    void SemanticAnalysis::functionCallStatement(Tree::Tree& tree) {

        scopeName sn(0, tree.children[0]->token.getTokenName());

        boost::unordered_map<scopeName, vectorString>::const_iterator entry;
        entry = symbolTable.find(sn);
        unsigned int index = 3;

        if (entry != symbolTable.end()) {

            unsigned int callParam = tree.children.size();

            if (!symbolTable[sn][2].compare(std::to_string(callParam - 1)) ||
                    (!tree.children[1]->children.size() && !symbolTable[sn][2].compare("0"))) {

                for (unsigned int i = 1; i < tree.children.size(); i++, index++) {

                    if (!symbolTable[sn][index].compare("flutuante"))
                        operationExpression(*tree.children[i], Token::FLOAT);
                    else if (!symbolTable[sn][index].compare("inteiro"))
                        operationExpression(*tree.children[i], Token::INTEGER);
                }
            } else
                error.functionCallError(tree.children[0]->token);
        } else
            error.functionCallScopeError(tree.children[0]->token);
    }

    void SemanticAnalysis::attributionExpression(Tree::Tree& tree) {

        scopeName sn(scope, tree.children[0]->token.getTokenName());

        sn.first = verifyTable(sn, *tree.children[0]);

        if (!symbolTable[sn][0].compare("inteiro"))
            operationExpression(*tree.children[1], Token::INTEGER);
        else
            operationExpression(*tree.children[1], Token::FLOAT);

        symbolTable[sn][symbolTable[sn].size() - 1] = IN;
    }

    void SemanticAnalysis::readStatement(Tree::Tree& tree) {

        scopeName sn(scope, tree.children[0]->token.getTokenName());

        sn.first = verifyTable(sn, *tree.children[0]);

        symbolTable[sn][symbolTable[sn].size() - 1] = IN;
    }

    void SemanticAnalysis::returnStatement(Tree::Tree& tree) {

        int i = returnType.size() - 1;

        if (!returnType[i].first.compare("inteiro")) {

            operationExpression(*tree.children[0], Token::INTEGER);
            returnType.pop_back();
        } else if (!returnType[i].first.compare("flutuante")) {

            operationExpression(*tree.children[0], Token::FLOAT);
            returnType.pop_back();
        } else
            error.returnIgnoredWarning(tree.children[1]->token);
    }

    void SemanticAnalysis::expressionStatement(Tree::Tree & tree) {

        if (!tree.children[0]->exp.compare(IFSTRING))
            operationExpression(*tree.children[0]->children[0]);

        else if (!tree.children[0]->exp.compare(WHILESTRING))
            operationExpression(*tree.children[0]->children[1]);

        else if (!tree.children[0]->exp.compare(ATTSTRING))
            attributionExpression(*tree.children[0]);

        else if (!tree.children[0]->exp.compare(FUNCCALLSTRING))
            functionCallStatement(*tree.children[0]);

        else if (!tree.children[0]->exp.compare(READSTRING))
            readStatement(*tree.children[0]);

        else if (!tree.children[0]->exp.compare(WRITESTRING))
            operationExpression(*tree.children[0]->children[0]);

        else if (!tree.children[0]->exp.compare(RETURNSTRING))
            returnStatement(*tree.children[0]);
    }

    void SemanticAnalysis::treeAnalyzer(Tree::Tree & tree, int level) {

        if (!tree.exp.compare(VARDECSTRING))
            variableDeclaration(tree, level);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDeclaration(tree);

        if (!tree.exp.compare(EXPSTRING))
            expressionStatement(tree);

        level++;

        for (unsigned int i = 0; i < tree.children.size(); i++)
            if (!tree.active)
                treeAnalyzer(*tree.children[i], level);

        level--;

        if (!level) {

            if (!main)
                error.mainDeclarationError();

            for (; returnType.size(); returnType.pop_back())
                if (returnType[returnType.size() - 1].first.compare("vazio"))
                    error.functionWithoutReturnWarning(returnType[returnType.size() - 1].second);
        }
    }

    void SemanticAnalysis::printTable() {

        std::ofstream file("symbols.txt");

        for (const auto &p : symbolTable) {

            file << p.first.first << ", " << p.first.second;

            for (unsigned int i = 0; i < p.second.size(); i++)
                file << " / " << p.second[i];

            file << "\n";
        }
    }
}
