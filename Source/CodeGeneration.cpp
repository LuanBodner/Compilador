/* 
 * File:   CodeGeneration.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 22, 2016, 11:01 AM
 */

#include "CodeGeneration.h"

namespace CodeGeneration {

    int scope = 0;

    LLVMBasicBlockRef * currentBlock;

    CodeGeneration::CodeGeneration() {
    }

    CodeGeneration::~CodeGeneration() {
    }

    void CodeGeneration::functionDefinition(Tree::Tree& t, SymbolTable s, LLVMModuleRef m) {

        scopeName sc(0, t.children[1]->token.getTokenName());
        scope++;

        int nop = std::stoi(s[sc][2]);

        LLVMTypeRef paramTypes[nop];

        for (int i = 0; i < nop; i++) {

            if (!s[sc][3 + i].compare(TI))
                paramTypes[i] = LLVMInt32Type();

            else if (!s[sc][3 + i].compare(TF))
                paramTypes[i] = LLVMFloatType();
        }
        
        LLVMAlloca
        LLVMTypeRef retType = LLVMFunctionType(LLVMVoidType(), paramTypes, nop, 0);

        if (!s[sc][0].compare(TI))
            retType = LLVMFunctionType(LLVMInt32Type(), paramTypes, nop, 0);

        else if (!s[sc][0].compare(TF))
            retType = LLVMFunctionType(LLVMFloatType(), paramTypes, nop, 0);

        LLVMValueRef func = LLVMAddFunction(m, sc.second.c_str(), retType);

        LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, std::string("entry_").append(sc.second).c_str());

        LLVMBuilderRef builder = LLVMCreateBuilder();
        LLVMPositionBuilderAtEnd(builder, entry);

        currentBlock = &entry;
    }

    void CodeGeneration::globalVariableDeclaration(Tree::Tree& t, SymbolTable s, LLVMModuleRef m) {

        LLVMValueRef variable;

        const char* name = t.children[1]->token.getTokenName().c_str();

        switch (t.children[0]->token.getTokenType()) {

            case(Token::INTEGER):
                variable = LLVMAddGlobal(m, LLVMInt32Type(), name);
                break;

            case(Token::FLOAT):
                variable = LLVMAddGlobal(m, LLVMFloatType(), name);
                break;

            default:
                exit(EXIT_FAILURE);
        }
    }

    void CodeGeneration::expressionStatement(Tree::Tree& t, SymbolTable s, LLVMModuleRef m) {

    }

    void CodeGeneration::generateCode(Tree::Tree& t, SymbolTable s, LLVMModuleRef m, int l) {

        if (!t.exp.compare(VARDECSTRING) && l == 1)
            globalVariableDeclaration(t, s, m);

        if (!t.exp.compare(FUNCDECSTRING))
            functionDefinition(t, s, m);

        if (!t.exp.compare(EXPSTRING))
            expressionStatement(t, s, m);

        l++;

        for (unsigned int i = 0; i < t.children.size(); i++)
            if (!t.active)
                generateCode(*t.children[i], s, m, l);
    }

    void CodeGeneration::treeAnalyzer(Tree::Tree& tree, SymbolTable s) {

        LLVMModuleRef mod = LLVMModuleCreateWithName("mainModule");

        int level = 0;

        generateCode(tree, s, mod, level);

        if (LLVMWriteBitcodeToFile(mod, "tiny.bc") != 0)
            fprintf(stderr, "error writing bitcode to file, skipping\n");

    }
}
