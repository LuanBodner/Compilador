/* 
 * File:   SemanticAnalysis.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 8, 2016, 5:16 PM
 */

#include "SemanticAnalysis.h"

namespace Semantic {

    int scope = 0;

    SemanticAnalysis::SemanticAnalysis() {
    }

    SemanticAnalysis::~SemanticAnalysis() {
    }

    void SemanticAnalysis::variableDeclaration(Tree::Tree &tree) {

        scopeName t(scope, tree.children[1]->token.getTokenName());

        if (symbolTable.find(t) != symbolTable.end())
            error.declarationScopeError(tree.children[1]->token);

        symbolTable.emplace(t, std::vector<std::string>());
        symbolTable.at(t).push_back(tree.children[0]->token.getTokenName());
    }

    void SemanticAnalysis::functionDeclaration(Tree::Tree &tree) {

        int auxScope = scope;
        scope = 0;

        variableDeclaration(tree);
        scopeName s(scope, tree.children[1]->token.getTokenName());

        symbolTable.at(s).push_back("Function");

        scope = ++auxScope;
    }

    void SemanticAnalysis::operationExpression(Tree::Tree &tree) {

        if (tree.children.size()) {

            if (tree.children[0]->token.getTokenType() == Token::IDENTIFIER) {

                scopeName sn(scope, tree.children[0]->token.getTokenName());

                if (symbolTable.find(sn) == symbolTable.end())
                    error.variableNotDeclared(tree.children[0]->token);
            }

            for (unsigned int i = 0; i < tree.children.size(); i++)
                if (tree.children[i])
                    operationExpression(*tree.children[i]);
        }
    }

    void SemanticAnalysis::attributionExpression(Tree::Tree &tree) {

        scopeName sn(scope, tree.children[0]->token.getTokenName());

        if (symbolTable.find(sn) == symbolTable.end())
            error.variableNotDeclared(tree.children[0]->token);

        operationExpression(*tree.children[1]);
    }

    void SemanticAnalysis::expressionStatement(Tree::Tree & tree) {

        if (!tree.children[0]->exp.compare(IFSTRING))
            operationExpression(*tree.children[0]->children[0]);

        else if (!tree.children[0]->exp.compare(WHILESTRING))
            operationExpression(*tree.children[0]->children[1]);

        else if (!tree.children[0]->exp.compare(ATTSTRING))
            attributionExpression(*tree.children[0]);

    }

    void SemanticAnalysis::treeAnalyzer(Tree::Tree & tree) {

        if (!tree.exp.compare(VARDECSTRING))
            variableDeclaration(tree);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDeclaration(tree);

        if (!tree.exp.compare(EXPSTRING))
            expressionStatement(tree);

        for (unsigned int i = 0; i < tree.children.size(); i++) {

            if (!tree.active)
                treeAnalyzer(*(tree.children[i]));
        }
    }

    void SemanticAnalysis::printTable() {

        std::ofstream file("symbols.txt");

        for (const auto &p : symbolTable) {
            file << p.first.first << ", "
                    << p.first.second;

            for (unsigned int i = 0; i < p.second.size(); i++)
                file << " / " << p.second[i];

            file << "\n";
        }

        file.close();
    }
}
