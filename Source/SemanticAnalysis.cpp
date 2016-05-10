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

        typeName t(tree.children[0]->token.getTokenName(),
                tree.children[1]->token.getTokenName());

        t.second.append("@");
        t.second.append(std::to_string(scope));

        if (symbolTable.find(t) != symbolTable.end())
            error.declarationScopeError(tree.children[1]->token);

        switch (t.first.size()) {
            
            case 9:
                symbolTable.emplace(t, "0.0");
                break;

            case 5:
                symbolTable.emplace(t, "auto");
                break;

            default:
                symbolTable.emplace(t, "0");
                break;
        }
    }

    void SemanticAnalysis::functionDeclaration(Tree::Tree &tree) {

    }

    void SemanticAnalysis::treeAnalyzer(Tree::Tree &tree) {

        if (!tree.exp.compare(VARDECSTRING))
            variableDeclaration(tree);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDeclaration(tree);

        if (!tree.exp.compare(ATTSTRING))
            ;

        for (unsigned int i = 0; i < tree.children.size(); i++)
            treeAnalyzer(*(tree.children[i]));
    }

    void SemanticAnalysis::printTable() {

        for (const auto &p : symbolTable)
            std::cout << p.first.first << ", "
                << p.first.second << " / "
                << p.second << std::endl;
    }
}
