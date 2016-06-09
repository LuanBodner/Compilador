/* 
 * File:   CodeGeneration.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 22, 2016, 11:01 AM
 */

#include "CodeGeneration.h"

namespace CodeGeneration {

    int scope = 0;

    CodeGeneration::CodeGeneration() {
    }

    CodeGeneration::~CodeGeneration() {
    }

    LLVMBuilderRef CodeGeneration::functionDefinition(Tree::Tree& t, SymbolTable s, LLVMModuleRef m) {

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

        LLVMTypeRef retType = LLVMFunctionType(LLVMVoidType(), paramTypes, nop, 0);

        if (!s[sc][0].compare(TI))
            retType = LLVMFunctionType(LLVMInt32Type(), paramTypes, nop, 0);

        else if (!s[sc][0].compare(TF))
            retType = LLVMFunctionType(LLVMFloatType(), paramTypes, nop, 0);

        LLVMValueRef func = LLVMAddFunction(m, sc.second.c_str(), retType);

        LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func, std::string("entry_").append(sc.second).c_str());

        LLVMBuilderRef builder = LLVMCreateBuilder();
        LLVMPositionBuilderAtEnd(builder, entry);

        return builder;
    }

    void CodeGeneration::globalVariableDeclaration(Tree::Tree& t, LLVMModuleRef m) {

        LLVMAddGlobal(m, llvmTokenType(t.children[0]->token.getTokenType()), t.children[1]->token.getTokenName().c_str());
    }

    LLVMTypeRef CodeGeneration::llvmTokenType(int t) {

        return (t == Token::INTEGER) ? LLVMInt32Type() : LLVMFloatType();
    }

    void CodeGeneration::localVariableDeclaration(Tree::Tree& t, LLVMBuilderRef b) {

        LLVMValueRef value = LLVMBuildAlloca(b,
                llvmTokenType(t.children[0]->token.getTokenType()),
                t.children[1]->token.getTokenName().c_str());

        ValueReference vr(scope, t.children[1]->token.getTokenName());

        variablesHash.emplace(vr, value);
    }

    void CodeGeneration::attributionStatement(Tree::Tree& t, LLVMBuilderRef b) {

        std::cout << "AttStmt\n";
        t.children[0]->token.print();

        ValueReference vr(scope, t.children[0]->token.getTokenName());

        LLVMBuildLoad(b, variablesHash[vr], vr.second.c_str());
    }

    void CodeGeneration::expressionStatement(Tree::Tree& t, SymbolTable s, LLVMBuilderRef b) {

        if (!t.exp.compare(VARDECSTRING))
            localVariableDeclaration(t, b);

        if (!t.exp.compare(ATTSTRING))
            attributionStatement(t, b);
    }

    void CodeGeneration::generateCode(Tree::Tree& t, SymbolTable s, LLVMModuleRef m, int l) {

        static LLVMBuilderRef builder;

        if (!t.exp.compare(VARDECSTRING) && l == 1)
            globalVariableDeclaration(t, m);

        if (!t.exp.compare(FUNCDECSTRING))
            builder = functionDefinition(t, s, m);

        if (!t.exp.compare(EXPSTRING))
            expressionStatement(*t.children[0], s, builder);

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
        system("llvm-dis tiny.bc");
    }
}
