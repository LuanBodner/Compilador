/* 
 * File:   SemanticAnalysis.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on May 8, 2016, 5:16 PM
 */

#ifndef SEMANTICANALYSIS_H
#define SEMANTICANALYSIS_H
#include <iostream>
#include <boost/unordered_map.hpp>

#include "SyntaxAnalysis.h"

typedef std::pair<std::string, std::string> typeName;

namespace Semantic {

    class SemanticAnalysis {
    public:
        SemanticAnalysis();
        virtual ~SemanticAnalysis();

        void treeAnalyzer(Syntax::SyntaxAnalysis);
        void printTable();

    private:
        void variableDeclaration(Tree::Tree*);
        boost::unordered_map<typeName, int> symbolTable;
    };
}
#endif /* SEMANTICANALYSIS_H */

