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
#include <llvm/DebugInfo/DIContext.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm/IR/Value.h>
#include "Tree.h"
#include "SemanticAnalysis.h"

typedef boost::unordered_map<scopeName, vectorString> SymbolTable;
typedef std::pair<int, std::string> ValueReference;

namespace CodeGeneration {

    class CodeGeneration {
    public:
        CodeGeneration();
        virtual ~CodeGeneration();
        void treeAnalyzer(Tree::Tree&, SymbolTable);

    private:
        boost::unordered_map<ValueReference, LLVMValueRef> variablesHash;

        LLVMBuilderRef functionDefinition(Tree::Tree&, SymbolTable, LLVMModuleRef);
        LLVMTypeRef llvmTokenType(int);
        void globalVariableDeclaration(Tree::Tree&, LLVMModuleRef);
        void localVariableDeclaration(Tree::Tree&, LLVMBuilderRef);
        void attributionStatement(Tree::Tree&, LLVMBuilderRef);
        void expressionStatement(Tree::Tree&, SymbolTable, LLVMBuilderRef);
        void generateCode(Tree::Tree&, SymbolTable, LLVMModuleRef, int);
    };
}
#endif /* CODEGENERATION_H */

