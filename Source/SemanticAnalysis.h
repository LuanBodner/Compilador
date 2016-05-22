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

#define GL "Global"
#define NI "Not Initialized"
#define IN "Initialized"
#define FU "Function"

namespace Semantic {

    class SemanticAnalysis {
    public:
        SemanticAnalysis();
        virtual ~SemanticAnalysis();
        
        /* Kicks off the semantic analysis */
        void treeAnalyzer(Tree::Tree&, int level = 0);
        void printTable();

    private:
        CompilerErrors::CompilerErrors error;

        /* Verifies if variables were already declared */
        int verifyTable(scopeName, Tree::Tree&);

        /* Semantic verification of the language */
        void readStatement(Tree::Tree&);
        void variableDeclaration(Tree::Tree&, int level = 0);
        void functionDeclaration(Tree::Tree&);
        void functionCallStatement(Tree::Tree&);
        void attributionExpression(Tree::Tree&);
        void operationExpression(Tree::Tree&);
        void expressionStatement(Tree::Tree&);

        /* Table of Symbols */
        boost::unordered_map<scopeName, vectorString> symbolTable;
    };
}
#endif /* SEMANTICANALYSIS_H */

