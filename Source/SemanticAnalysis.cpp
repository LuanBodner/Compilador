/* 
 * File:   SemanticAnalysis.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 8, 2016, 5:16 PM
 */

#include "SemanticAnalysis.h"
#include <unordered_map>

namespace Semantic {

    int scope = 0;

    SemanticAnalysis::SemanticAnalysis() {
    }

    SemanticAnalysis::~SemanticAnalysis() {
    }

    void SemanticAnalysis::variableDeclaration(Tree::Tree &tree) {

        typeName t(tree.children[0]->token.getTokenName(),
                tree.children[1]->token.getTokenName());

        if (!t.first.compare("flutuante"))
            symbolTable.emplace(t, valueScope("0.0", scope));
        else if (!t.first.compare("vazio"))
            symbolTable.emplace(t, valueScope("auto", scope));
        else
            symbolTable.emplace(t, valueScope("0", scope));
    }

    void SemanticAnalysis::functionDeclaration(Tree::Tree &tree) {

    }

    void SemanticAnalysis::treeAnalyzer(Tree::Tree &tree) {

        if (!tree.exp.compare(VARDECSTRING))
            variableDeclaration(tree);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDeclaration(tree);

        for (unsigned int i = 0; i < tree.children.size(); i++)
            treeAnalyzer(*(tree.children[i]));
    }

    void SemanticAnalysis::printTable() {

        for (const auto &p : symbolTable)
            std::cout << p.first.first << ","
                << p.first.second << " / "
                << p.second.first << ","
                << p.second.second << std::endl;
    }
}
