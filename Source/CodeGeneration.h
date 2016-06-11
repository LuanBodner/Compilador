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
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/PassManagerInternal.h>
#include <llvm/IR/AssemblyAnnotationWriter.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Bitcode/BitstreamWriter.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include "Tree.h"
#include "SemanticAnalysis.h"

namespace CodeGeneration {

    typedef boost::unordered_map<ScopeName, vectorString> SymbolTable;

    class CodeGeneration {
    public:
        CodeGeneration();
        virtual ~CodeGeneration();
        void treeAnalyzer(Tree::Tree&, SymbolTable);

    private:
        boost::unordered_map<ScopeName, llvm::Instruction*> variablesHash;
        boost::unordered_map<ScopeName, llvm::Value*> paramHash;
        
        

        llvm::Value* getHashValue(std::string);
        llvm::Value* operationsExpression(Tree::Tree&, llvm::Module*);
        void attributionStatement(Tree::Tree&, llvm::Module*);
        void localVariableDeclaration(Tree::Tree&, llvm::Module*);
        void expressionStatement(Tree::Tree&, SymbolTable, llvm::Module*);
        void paramDeclaration(Tree::Tree&, llvm::Module*);
        void globalVariableDeclaration(Tree::Tree&, llvm::Module*);
        llvm::Type* getTypefromString(std::string, llvm::Module*);
        void functionDefinition(Tree::Tree&, SymbolTable, llvm::Module*);
        void generateCode(Tree::Tree&, SymbolTable, llvm::Module*, int);
        void printHashTable();
    };
}
#endif /* CODEGENERATION_H */

