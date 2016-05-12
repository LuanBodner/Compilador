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

        std::string name = tree.children[1]->token.getTokenName();
        scopeName t(scope, name);

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

    void SemanticAnalysis::expressionStatement(Tree::Tree &tree) {
        
        

    }

    void SemanticAnalysis::treeAnalyzer(Tree::Tree &tree) {

        if (!tree.exp.compare(VARDECSTRING))
            variableDeclaration(tree);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDeclaration(tree);

        if (!tree.exp.compare(EXPSTRING))
            ;

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
