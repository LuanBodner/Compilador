/* 
 * File:   llvmCodeGen.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on June 16, 2016, 8:25 AM
 */

#include "llvmCodeGeneration.h"

namespace llvmCodeGeneration {

    int scope = 0;
    std::string currentFunction;
    int paramIndex;

    llvmCodeGeneration::llvmCodeGeneration() {

        module = new llvm::Module("Tiny", llvm::getGlobalContext());
    }

    llvmCodeGeneration::~llvmCodeGeneration() {

        //delete module;
    }

    llvm::Type * llvmCodeGeneration::getTypefromString(std::string s) {

        if (!s.compare(VOIDS))
            return llvm::Type::getVoidTy(module->getContext());
        if (!s.compare(FLOATS))
            return llvm::Type::getFloatTy(module->getContext());
        if (!s.compare(INTS))
            return llvm::Type::getInt32Ty(module->getContext());

        return NULL;
    }

    void llvmCodeGeneration::globalVariableDeclaration(Tree::Tree& t) {

        llvm::Type *type = getTypefromString(t.children[0]->token.getTokenName());

        ScopeName sc(scope, t.children[0]->token.getTokenName());

        llvm::GlobalVariable * glvar =
                new llvm::GlobalVariable(*module, type, false,
                llvm::GlobalVariable::CommonLinkage, 0,
                t.children[1]->token.getTokenName());
        glvar->setAlignment(4);
    }

    void llvmCodeGeneration::paramDeclaration(Tree::Tree& t) {

        llvm::Function::arg_iterator cargs = function->arg_begin();

        for (int i = 0; i < paramIndex; i++)
            cargs++;
        cargs->setName(t.children[1]->token.getTokenName());

        paramIndex++;
    }

    void llvmCodeGeneration::functionDefinition(Tree::Tree& t, SymbolTable s) {

        ScopeName sc(0, t.children[1]->token.getTokenName());
        scope++;

        std::vector<llvm::Type*> param;

        for (int i = 0; i < std::stoi(s[sc][2]); i++)
            param.push_back(getTypefromString(s[sc][3 + i]));

        llvm::FunctionType * ftype = llvm::FunctionType::get(
                getTypefromString(t.children[0]->token.getTokenName()), param, false);

        function = llvm::Function::Create(ftype,
                llvm::GlobalValue::ExternalLinkage, sc.second, module);
        function->setCallingConv(llvm::CallingConv::C);

        currentFunction = sc.second;
        block = llvm::BasicBlock::Create(module->getContext(),
                std::string("entry_").append(sc.second), function, 0);
        builder = new llvm::IRBuilder<>(block);

        paramIndex = 0;
    }

    void llvmCodeGeneration::localVariableDeclaration(Tree::Tree& t) {

        ScopeName sc(scope, t.children[1]->token.getTokenName());

        llvm::AllocaInst * variable = new llvm::AllocaInst(
                getTypefromString(t.children[0]->token.getTokenName()),
                t.children[1]->token.getTokenName(), block);
        variable->setAlignment(4);
    }

    void llvmCodeGeneration::attributionStatement(Tree::Tree& t) {

        llvm::Constant * c0 = llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(module->getContext()), 32, false);
        llvm::Constant * c1 = llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(module->getContext()), 32, false);

        //llvm::Value * v1 = new llvm::Value(llvm::IntegerType::getInt32Ty(module->getContext()));
        // v1->setName("v1");
        //llvm::Value * v2 = new llvm::Value(llvm::IntegerType::getInt32Ty(module->getContext()));
        //v2->setName("v2");
        //builder->SetInsertPoint(block);

        std::cout << builder->GetInsertBlock()->getName().data() << std::endl;
        llvm::Value * v = builder->CreateBinOp(llvm::Instruction::Add, c0, c1, "temp");

        //builder->CreateRet(v);

        //std::error_code ERR;

        //llvm::raw_fd_ostream *out = new llvm::raw_fd_ostream("tiny.bc", ERR, llvm::sys::fs::F_None);
        //llvm::WriteBitcodeToFile(module, *out);

        //delete out;

        //system("llvm-dis tiny.bc");
        //exit(0);
    }

    void llvmCodeGeneration::expressionStatement(Tree::Tree& t, SymbolTable s) {

        if (!t.children[0]->exp.compare(VARDECSTRING))
            localVariableDeclaration(*t.children[0]);

        if (!t.children[0]->exp.compare(ATTSTRING))
            attributionStatement(*t.children[0]);
    }

    void llvmCodeGeneration::generateCode(Tree::Tree& t, SymbolTable s, int l) {

        if (!t.exp.compare(VARDECSTRING) && l == 1)
            globalVariableDeclaration(t);

        if (!t.exp.compare(VARDECSTRING) && l == 3)
            paramDeclaration(t);

        if (!t.exp.compare(EXPSTRING))
            expressionStatement(t, s);

        if (!t.exp.compare(FUNCDECSTRING))
            functionDefinition(t, s);

        l++;

        for (unsigned int i = 0; i < t.children.size(); i++)
            if (!t.active)
                generateCode(*t.children[i], s, l);
    }

    void llvmCodeGeneration::treeAnalyzer(Tree::Tree& t, SymbolTable s) {

        module = new llvm::Module("Tiny", llvm::getGlobalContext());
        bool ver = llvm::verifyModule(*module);

        if (ver) {

            std::cout << "Error Creating the Module";
            exit(EXIT_FAILURE);
        }

        generateCode(t, s, 0);

        std::error_code ERR;

        llvm::raw_fd_ostream *out = new llvm::raw_fd_ostream("tiny.bc", ERR, llvm::sys::fs::F_None);
        llvm::WriteBitcodeToFile(module, *out);

        delete out;

        system("llvm-dis tiny.bc");

    }
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