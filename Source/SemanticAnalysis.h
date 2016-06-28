/* 
 * File:   SemanticAnalysis.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on May 8, 2016, 5:16 PM
 */

#ifndef SEMANTICANALYSIS_H
#define SEMANTICANALYSIS_H
#include <iostream>
#include <string>
#include <boost/unordered_map.hpp>
#include "SyntaxAnalysis.h"

typedef std::pair<int, std::string> ScopeName;
typedef std::vector<std::string> vectorString;

#define GL "Global"
#define NIN "Not Initialized"
#define IN "Initialized"
#define FU "Function"

#define INTS "inteiro"
#define VOIDS "vazio"
#define FLOATS "flutuante"

#define UV "Used"
#define NUV "Unused"

namespace Semantic {

    class SemanticAnalysis {
    public:
        SemanticAnalysis();
        virtual ~SemanticAnalysis();

        /* Kicks off the semantic analysis */
        void treeAnalyzer(Tree::Tree&, int level = 0);
        void printTable(std::string);

        /* Table of Symbols */
        boost::unordered_map<ScopeName, vectorString> symbolTable;

    private:
        CompilerErrors::CompilerErrors error;

        /* Verifies if variables were already declared */
        int verifyTable(ScopeName, Tree::Tree&);

        /* Semantic verification of the language */
        void readStatement(Tree::Tree&);
        void variableDeclaration(Tree::Tree&, int level = 0);
        void functionDeclaration(Tree::Tree&);
        void functionCallStatement(Tree::Tree&);
        void attributionExpression(Tree::Tree&);
        void operationExpression(Tree::Tree&);
        void operationExpression(Tree::Tree&, Token::TokenType);
        void expressionStatement(Tree::Tree&);
        void parameterTypes(Tree::Tree&, ScopeName);
        void returnStatement(Tree::Tree&);
    };
}
#endif /* SEMANTICANALYSIS_H */

