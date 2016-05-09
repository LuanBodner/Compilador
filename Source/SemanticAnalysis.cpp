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

    void SemanticAnalysis::variableDeclaration(Tree::Tree *tree) {

        typeName t(tree->children[0]->token.getTokenName(),
                tree->children[1]->token.getTokenName());

        symbolTable.emplace(t, scope);
    }

    void SemanticAnalysis::treeAnalyzer(Syntax::SyntaxAnalysis synx) {

        Tree::Tree tree = synx.getTree();
        Tree::Tree * subTree;

        subTree = tree.children[0];

        for (unsigned int i = 1; i < tree.children.size(); i++) {

            if (!subTree->exp.compare(VARDECSTRING))
                variableDeclaration(subTree);

            subTree = tree.children[i];
        }

        printTable();

    }

    void SemanticAnalysis::printTable() {

        for (const auto &p : symbolTable)
            std::cout << p.first.first << ","
                << p.first.second << ";"
                << p.second << std::endl;
    }
}
