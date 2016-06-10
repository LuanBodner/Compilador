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
    unsigned int paramIndex;

    CodeGeneration::CodeGeneration() {
    }

    CodeGeneration::~CodeGeneration() {
    }

    llvm::Type* CodeGeneration::getTypefromString(std::string s, llvm::Module* m) {

        if (!s.compare(VOIDS))
            return llvm::Type::getVoidTy(m->getContext());
        if (!s.compare(FLOATS))
            return llvm::Type::getFloatTy(m->getContext());
        if (!s.compare(INTS))
            return llvm::Type::getInt32Ty(m->getContext());

        return NULL;
    }

    void CodeGeneration::globalVariableDeclaration(Tree::Tree& t, llvm::Module* m) {

        llvm::Type *type = getTypefromString(t.children[0]->token.getTokenName(), m);

        llvm::GlobalVariable * glvar =
                new llvm::GlobalVariable(*m, type, false,
                llvm::GlobalVariable::CommonLinkage, 0,
                t.children[1]->token.getTokenName());
        glvar->setAlignment(4);
    }

    void CodeGeneration::paramDeclaration(Tree::Tree& t, llvm::Module* m) {

        llvm::Function * func = m->getFunction(currentFunction);
        llvm::Function::arg_iterator cargs = func->arg_begin();

        for (int i = 0; i < paramIndex; i++)
            cargs++;
        cargs->setName(t.children[1]->token.getTokenName());

        paramIndex++;
    }

    /*llvm::BasicBlock */
    void CodeGeneration::functionDefinition(Tree::Tree& t, SymbolTable s, llvm::Module* m) {

        ScopeName sc(0, t.children[1]->token.getTokenName());

        std::vector<llvm::Type*> param;

        for (int i = 0; i < std::stoi(s[sc][2]); i++)
            param.push_back(getTypefromString(s[sc][3 + i], m));

        llvm::FunctionType * ftype = llvm::FunctionType::get(
                getTypefromString(t.children[0]->token.getTokenName(), m),
                param, false);

        llvm::Function * func = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, sc.second, m);
        func->setCallingConv(llvm::CallingConv::C);

        currentFunction = sc.second;
        paramIndex = 0;

        llvm::BasicBlock::Create(m->getContext(), std::string("entry_").append(sc.second), func, 0);
        //return block;
    }

    void CodeGeneration::localVariableDeclaration(Tree::Tree& t, llvm::Module* m) {

        llvm::Function * func = m->getFunction(currentFunction);
        llvm::Function::iterator b = func->begin();
       
        llvm::BasicBlock* block = b;

        llvm::AllocaInst * variable = new llvm::AllocaInst(
                getTypefromString(t.children[0]->token.getTokenName(), m),
                t.children[1]->token.getTokenName(), block);
        variable->setAlignment(4);
    }

    void CodeGeneration::expressionStatement(Tree::Tree& t, SymbolTable s, llvm::Module* m) {

        if (!t.children[0]->exp.compare(VARDECSTRING))
            localVariableDeclaration(*t.children[0], m);
    }

    void CodeGeneration::generateCode(Tree::Tree& t, SymbolTable s, llvm::Module* m, int l) {

        if (!t.exp.compare(VARDECSTRING) && l == 1)
            globalVariableDeclaration(t, m);

        if (!t.exp.compare(VARDECSTRING) && l == 3)
            paramDeclaration(t, m);

        if (!t.exp.compare(EXPSTRING))
            expressionStatement(t, s, m);

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

        /*llvm::Constant* c = mod->getOrInsertFunction("mul_add",
                llvm::IntegerType::get(mod->getContext(), 32),
                llvm::IntegerType::get(mod->getContext(), 32),
                llvm::IntegerType::get(mod->getContext(), 32),
                llvm::IntegerType::get(mod->getContext(), 32),
                NULL);

        llvm::Function* mul_add = llvm::cast<llvm::Function>(c);
        mul_add->setCallingConv(llvm::CallingConv::C);

        llvm::Function::arg_iterator args = mul_add->arg_begin();
        llvm::Value* x = args++;
        x->setName("x");
        llvm::Value* y = args++;
        y->setName("y");
        llvm::Value* z = args++;
        z->setName("z");

        llvm::BasicBlock* block = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", mul_add);
        llvm::IRBuilder<> builder(block);

        llvm::Value* tmp = builder.CreateBinOp(llvm::Instruction::Mul,
                x, y, "tmp");
        llvm::Value* tmp2 = builder.CreateBinOp(llvm::Instruction::Add,
                tmp, z, "tmp2");

        builder.CreateRet(tmp2);*/

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