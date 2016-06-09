/* 
 * File:   CodeGeneration.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 22, 2016, 11:01 AM
 */

#include <llvm/Support/FileSystem.h>

#include "CodeGeneration.h"

namespace CodeGeneration {

    int scope = 0;
    std::string currentFunction;
    llvm::Type* currentType;

    CodeGeneration::CodeGeneration() {
    }

    CodeGeneration::~CodeGeneration() {
    }

    llvm::Type* CodeGeneration::getTypefromString(std::string s) {

        if (!s.compare("vazio"))
            return llvm::Type::getVoidTy(llvm::getGlobalContext());
        if (!s.compare("flutuante"))
            return llvm::Type::getFloatTy(llvm::getGlobalContext());
        if (!s.compare("inteiro"))
            return llvm::Type::getInt32Ty(llvm::getGlobalContext());

        return NULL;
    }

    void CodeGeneration::globalVariableDeclaration(Tree::Tree& t, llvm::Module* m) {

        llvm::Type *type = getTypefromString(t.children[0]->token.getTokenName());

        llvm::GlobalVariable * glvar =
                new llvm::GlobalVariable(*m, type, false,
                llvm::GlobalVariable::CommonLinkage, 0,
                t.children[1]->token.getTokenName());
        glvar->setAlignment(4);
    }

    void CodeGeneration::paramDeclaration(Tree::Tree& t, llvm::Module* m) {

        /*t.children[1]->token.print();

        llvm::Type* ty = llvm::cast<llvm::Type>(currentType);
        llvm::Constant * c = m->getOrInsertFunction(currentFunction, ty);

        llvm::Function *func = llvm::cast<llvm::Function>(c);

        //func->setAttributes();

        llvm::Function::arg_iterator par = func->arg_begin();
        llvm::Value* val = par++;
        val->setName(t.children[1]->token.getTokenName());
        //func->get*/
    }

    void CodeGeneration::functionDefinition(Tree::Tree& t, SymbolTable s, llvm::Module* m) {

        ScopeName sc(0, t.children[1]->token.getTokenName());
        llvm::Constant * c;

        llvm::Function *func = llvm::cast<llvm::Function>(
                c = m->getOrInsertFunction(t.children[1]->token.getTokenName(),
                getTypefromString(t.children[0]->token.getTokenName()),
                NULL));

        for (unsigned int k = 0; k < std::stoi(s[sc][2]); k++) {

            if (!s[sc][3 + k].compare("inteiro"))
                func->setAttributes(llvm::IntegerType::get(llvm::getGlobalContext(), 32));
            if (!s[sc][3 + k].compare("flutuante"))
                func->setAttributes(llvm::);
        }
        //llvm::Constant * c = m->getOrInsertFunction(t.children[1]->token.getTokenName(),
        //        getTypefromString(t.children[0]->token.getTokenName()), NULL);



        currentFunction = t.children[0]->token.getTokenName();
        currentType = getTypefromString(t.children[0]->token.getTokenName());
    }

    void CodeGeneration::generateCode(Tree::Tree& t, SymbolTable s, llvm::Module* m, int l) {

        if (!t.exp.compare(VARDECSTRING) && l == 1)
            globalVariableDeclaration(t, m);

        if (!t.exp.compare(VARDECSTRING) && l == 3)
            paramDeclaration(t, m);

        if (!t.exp.compare(FUNCDECSTRING))
            functionDefinition(t, s, m);

        l++;

        for (unsigned int i = 0; i < t.children.size(); i++)
            if (!t.active)
                generateCode(*t.children[i], s, m, l);
    }

    void CodeGeneration::treeAnalyzer(Tree::Tree& t, SymbolTable s) {

        llvm::Module * mod = new llvm::Module("Tiny", llvm::getGlobalContext());

        bool ver = llvm::verifyModule(*mod);

        if (ver) {

            std::cout << "Error Creating the Module";
            exit(EXIT_FAILURE);
        }

        generateCode(t, s, mod, 0);

        std::error_code ERR;

        llvm::raw_fd_ostream *out = new llvm::raw_fd_ostream("tiny.bc", ERR, llvm::sys::fs::F_None);
        llvm::WriteBitcodeToFile(mod, *out);

        delete out;
        delete mod;

        system("llvm-dis tiny.bc");
    }
}

/*
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

        variable vr(scope, t.children[1]->token.getTokenName());
        llvmVariableValue lvr(value, t.children[1]->token.getTokenName());
        variablesHash.emplace(vr, lvr);
    }

    void CodeGeneration::attributionStatement(Tree::Tree& t, LLVMBuilderRef b) {

        std::cout << "AttStmt\n";
        //t.children[0]->token.print();

        variable vr(scope, t.children[0]->token.getTokenName());

        //std::cout << "Size " << variablesHash.size() << std::endl;
        //std::cout << "Name " << variablesHash[vr].second << std::endl;
        //LLVMValueRef teste = LLVMBuildAlloca(b, LLVMInt32Type(), "NAME");
        variablesHash[vr].first = LLVMConstInt(LLVMInt32Type(), 0, 0);

        LLVMValueRef teste1 = LLVMBuildAdd(b, variablesHash[vr].first, LLVMConstInt(LLVMInt32Type(), 0, 0), "a");

        //variablesHash[vr].
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
 */