/* 
 * File:   llvmCodeGen.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on June 16, 2016, 8:25 AM
 */

#ifndef LLVMCODEGEN_H
#define LLVMCODEGEN_H

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

namespace llvmCodeGeneration {

    typedef boost::unordered_map<ScopeName, vectorString> SymbolTable;

    class llvmCodeGeneration {
    public:
        llvmCodeGeneration();
        virtual ~llvmCodeGeneration();

        /* Kicks off the generation */
        void treeAnalyzer(Tree::Tree&, SymbolTable);

        /* Alloca Instruction table */
        boost::unordered_map<ScopeName, llvm::AllocaInst*> variablesHash;

        /* Function Parameters table */
        boost::unordered_map<ScopeName, llvm::AllocaInst*> paramHash;

        void testFunction();
        llvm::Constant * create();
    private:

        /* Current Builder */
        llvm::IRBuilder<> * builder;

        /* tiny Module */
        llvm::Module * module;

        /* Current function */
        llvm::Function * function;

        /* Current basic block */
        llvm::BasicBlock * block;

        /* Gets the string(inteiro,flutuante) and returns its type */
        llvm::Type * getTypefromString(std::string);

        /* Math OP*/
        llvm::Constant * generateValue(Tree::Tree&);
        void expressionGenerator(Tree::Tree&);
        llvm::Value * operationsExpression(Tree::Tree&, llvm::Type*);

        /* Variable declaration */
        void localVariableDeclaration(Tree::Tree&);

        /* Attribution */
        void attributionStatement(Tree::Tree&, SymbolTable);

        /* Generic expression handler */
        void expressionStatement(Tree::Tree&, SymbolTable);

        /* Function declaration, number of parameters defined and named */
        void functionDefinition(Tree::Tree&, SymbolTable);
        void paramDeclaration(Tree::Tree&);

        /* Global variables */
        void globalVariableDeclaration(Tree::Tree&);

        /* Tree navigator */
        void generateCode(Tree::Tree&, SymbolTable, int);

        /* Table operations */
        void printHashTable();
        llvm::AllocaInst * getParamValue(std::string);
        llvm::AllocaInst * getVariableAllocation(std::string);
    };
}

#endif /* LLVMCODEGEN_H */

