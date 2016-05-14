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

    void SemanticAnalysis::verifyTable(scopeName key, Tree::Tree& tree) {

        while (key.first >= 0) {

            boost::unordered_map<scopeName, vectorString>::const_iterator entry;
            entry = symbolTable.find(key);

            if (entry != symbolTable.end()) {

                if (key.first != scope && !entry->second[1].compare("Global"))
                    break;

                if (key.first == scope)
                    break;
            }

            key.first--;
        }

        if (key.first == -1)
            error.variableNotDeclared(tree.token);
    }

    void SemanticAnalysis::variableDeclaration(Tree::Tree& tree, int level) {

        scopeName t(scope, tree.children[1]->token.getTokenName());

        if (symbolTable.find(t) != symbolTable.end())
            error.declarationScopeError(tree.children[1]->token);

        symbolTable.emplace(t, std::vector<std::string>());
        symbolTable[t].push_back(tree.children[0]->token.getTokenName());

        if (level == 1)
            symbolTable[t].push_back("Global");
    }

    void SemanticAnalysis::functionDeclaration(Tree::Tree& tree) {

        int auxScope = scope;
        scope = 0;

        variableDeclaration(tree);
        scopeName s(scope, tree.children[1]->token.getTokenName());

        symbolTable[s].push_back("Function");
        symbolTable[s].push_back(std::to_string(tree.children[2]->children.size()));

        scope = ++auxScope;
    }

    void SemanticAnalysis::operationExpression(Tree::Tree& tree) {

        if (tree.children.size()) {

            if (tree.children[0]->token.getTokenType() == Token::IDENTIFIER) {

                scopeName sn(scope, tree.children[0]->token.getTokenName());

                verifyTable(sn, *tree.children[0]);
            }

            for (unsigned int i = 0; i < tree.children.size(); i++)
                if (tree.children[i])
                    operationExpression(*tree.children[i]);
        }
    }

    void SemanticAnalysis::functionCallStatement(Tree::Tree& tree) {

        scopeName sn(scope, tree.children[0]->token.getTokenName());

        verifyTable(sn, *tree.children[0]);

        unsigned int callParam = tree.children.size();

        if (!symbolTable[sn][2].compare(std::to_string(callParam - 1)))
            for (unsigned int i = 1; i < tree.children.size(); i++)
                operationExpression(*tree.children[i]);
        else
            error.functionCallError();
    }

    void SemanticAnalysis::attributionExpression(Tree::Tree& tree) {

        scopeName sn(scope, tree.children[0]->token.getTokenName());

        verifyTable(sn, *tree.children[0]);

        operationExpression(*tree.children[1]);
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

    }

    void SemanticAnalysis::treeAnalyzer(Tree::Tree & tree, int level) {

        if (!tree.exp.compare(VARDECSTRING))
            variableDeclaration(tree, level);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDeclaration(tree);

        if (!tree.exp.compare(EXPSTRING))
            expressionStatement(tree);

        level++;

        for (unsigned int i = 0; i < tree.children.size(); i++) {

            if (!tree.active)
                treeAnalyzer(*tree.children[i], level);
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
