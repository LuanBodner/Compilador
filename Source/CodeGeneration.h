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
//Bibliotecas do C
//#include <llvm-c/Core.h>
//#include <llvm/DebugInfo/DIContext.h>
//#include <llvm-c/ExecutionEngine.h>
//#include <llvm-c/Target.h>
//#include <llvm-c/Analysis.h>
//#include <llvm-c/BitWriter.h>
//#include <llvm/IR/Value.h>
//Bibliotecas do C++
#include <llvm/IR/Module.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/PassManagerInternal.h>
#include <llvm/IR/AssemblyAnnotationWriter.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitstreamWriter.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include "Tree.h"
#include "SemanticAnalysis.h"

namespace CodeGeneration {

    typedef boost::unordered_map<scopeName, vectorString> SymbolTable;
    typedef std::pair<int, std::string> variable;
    typedef std::pair <LLVMValueRef, std::string> llvmVariableValue;

    class CodeGeneration {
    public:
        CodeGeneration();
        virtual ~CodeGeneration();
        void treeAnalyzer(Tree::Tree&, SymbolTable);

    private:
        boost::unordered_map<variable, llvmVariableValue> variablesHash;

        LLVMTypeRef llvmTokenType(int);
        void localVariableDeclaration(Tree::Tree&, LLVMBuilderRef);
        void attributionStatement(Tree::Tree&, LLVMBuilderRef);
        void expressionStatement(Tree::Tree&, SymbolTable, LLVMBuilderRef);
        //Transformed
        void globalVariableDeclaration(Tree::Tree&, llvm::Module*);
        llvm::Type* getTypefromString(std::string);
        void functionDefinition(Tree::Tree&, SymbolTable, llvm::Module*);
        void generateCode(Tree::Tree&, SymbolTable, llvm::Module*, int);
    };
}
#endif /* CODEGENERATION_H */

