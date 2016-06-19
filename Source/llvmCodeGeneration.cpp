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
        
        ScopeName sc(scope, cargs->getName().data());
        paramHash[sc] = cargs;

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

        variablesHash[sc] = variable;
    }

    llvm::Value * llvmCodeGeneration::expressionGenerator(Tree::Tree& t) {
        return NULL;
    }

    llvm::Value * llvmCodeGeneration::operationsExpression(Tree::Tree& t, llvm::Type * type) {

        return llvm::ConstantInt::get(type, 10);
    }

    void llvmCodeGeneration::attributionStatement(Tree::Tree& t, SymbolTable s) {

        ScopeName sc(scope, t.children[0]->token.getTokenName());

        llvm::AllocaInst * variable = getVariableAllocation(sc.second);
        llvm::Value * op = operationsExpression(t, getTypefromString(s[sc][0]));

        if (variable != NULL) {

            std::cout << variable->getName().data() << std::endl;
            builder->CreateStore(op, variable);
        } else {

            llvm::Value * param = getParamValue(sc.second);

            std::cout << param->getName().data() << std::endl;
            builder->CreateStore(op, param);
        }
    }

    void llvmCodeGeneration::expressionStatement(Tree::Tree& t, SymbolTable s) {

        if (!t.children[0]->exp.compare(VARDECSTRING))
            localVariableDeclaration(*t.children[0]);

        if (!t.children[0]->exp.compare(ATTSTRING))
            attributionStatement(*t.children[0], s);

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

        printHashTable();

        std::error_code ERR;

        llvm::raw_fd_ostream *out = new llvm::raw_fd_ostream("tiny.bc", ERR, llvm::sys::fs::F_None);
        llvm::WriteBitcodeToFile(module, *out);

        delete out;

        system("llvm-dis tiny.bc");
    }

    void llvmCodeGeneration::printHashTable() {

        std::ofstream out("referenceTable.txt");

        for (const auto &v : variablesHash)
            out << v.first.first << ", "
                << v.first.second << " = "
                << v.second->getName().data() << "\n";

        for (const auto &v : paramHash)
            out << v.first.first << ", "
                << v.first.second << " = "
                << v.second->getName().data() << "\n";
    }

    llvm::AllocaInst * llvmCodeGeneration::getVariableAllocation(std::string n) {

        return (variablesHash.find(ScopeName(scope, n)) != variablesHash.end())
                ? variablesHash[ScopeName(scope, n)] : NULL;
    }

    llvm::Value * llvmCodeGeneration::getParamValue(std::string n) {

        return (paramHash.find(ScopeName(scope, n)) != paramHash.end())
                ? paramHash[ScopeName(scope, n)] : NULL;
    }

    llvm::Constant * llvmCodeGeneration::create() {

        return llvm::ConstantInt::get(llvm::IntegerType::getInt32Ty(module->getContext()), 30);
    }

    void llvmCodeGeneration::testFunction() {

        module = new llvm::Module("Tiny", llvm::getGlobalContext());

        llvm::Constant* c = module->getOrInsertFunction("mul_add",
                llvm::IntegerType::get(module->getContext(), 32),
                llvm::IntegerType::get(module->getContext(), 32),
                llvm::IntegerType::get(module->getContext(), 32),
                llvm::IntegerType::get(module->getContext(), 32),
                NULL);

        function = llvm::cast<llvm::Function>(c);
        function->setCallingConv(llvm::CallingConv::C);

        llvm::Function::arg_iterator args = function->arg_begin();
        llvm::Value* x = args++;
        x->setName("x");
        llvm::Value* y = args++;
        y->setName("y");
        llvm::Value* z = args++;
        z->setName("z");

        block = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", function);
        builder = new llvm::IRBuilder<>(block);

        llvm::AllocaInst * var = new llvm::AllocaInst(llvm::IntegerType::getInt32Ty(module->getContext()), "Name", block);

        llvm::Value * val = create();

        //llvm::StoreInst * str = new llvm::StoreInst(var, val, block);

        builder->CreateStore(val, var);

        builder->CreateRet(val);

        std::error_code ERR;

        llvm::raw_fd_ostream *out = new llvm::raw_fd_ostream("test.bc", ERR, llvm::sys::fs::F_None);
        llvm::WriteBitcodeToFile(module, *out);

        delete out;

        system("llvm-dis test.bc");

    }
}