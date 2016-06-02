/* 
 * File:   CodeGeneration.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on May 22, 2016, 11:01 AM
 */

#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include "Tree.h"
#include "SemanticAnalysis.h"

typedef boost::unordered_map<scopeName, vectorString> SymbolTable;

namespace CodeGeneration {

    class CodeGeneration {
    public:
        CodeGeneration();
        virtual ~CodeGeneration();
        void treeAnalyzer(Tree::Tree&, SymbolTable);
    private:
        void functionDefinition(Tree::Tree&, SymbolTable);
        void variableDeclaration(Tree::Tree&, SymbolTable);
    };
}
#endif /* CODEGENERATION_H */

