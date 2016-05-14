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

typedef std::pair<int, std::string> scopeName;
typedef std::vector<std::string> vectorString;

namespace Semantic {

    class SemanticAnalysis {
    public:
        SemanticAnalysis();
        virtual ~SemanticAnalysis();

        void treeAnalyzer(Tree::Tree&);
        void printTable();

    private:
        CompilerErrors::CompilerErrors error;
        void variableDeclaration(Tree::Tree&);
        void functionDeclaration(Tree::Tree&);
        void attributionExpression(Tree::Tree&);
        void operationExpression(Tree::Tree&);
        void expressionStatement(Tree::Tree&);
        boost::unordered_map<scopeName, vectorString> symbolTable;
    };
}
#endif /* SEMANTICANALYSIS_H */

