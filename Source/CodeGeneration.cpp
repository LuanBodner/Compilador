/* 
 * File:   CodeGeneration.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 22, 2016, 11:01 AM
 */

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

        ScopeName sc(scope, t.children[0]->token.getTokenName());

        llvm::GlobalVariable * glvar =
                new llvm::GlobalVariable(*m, type, false,
                llvm::GlobalVariable::CommonLinkage, 0,
                t.children[1]->token.getTokenName());
        glvar->setAlignment(4);

        //variablesHash.emplace()
    }

    void CodeGeneration::paramDeclaration(Tree::Tree& t, llvm::Module* m) {

        llvm::Function * func = m->getFunction(currentFunction);
        llvm::Function::arg_iterator cargs = func->arg_begin();

        for (int i = 0; i < paramIndex; i++)
            cargs++;
        cargs->setName(t.children[1]->token.getTokenName());

        ScopeName sc(scope, t.children[1]->token.getTokenName());
        paramHash[sc] = cargs;

        paramIndex++;
    }

    void CodeGeneration::functionDefinition(Tree::Tree& t, SymbolTable s, llvm::Module* m) {

        ScopeName sc(0, t.children[1]->token.getTokenName());
        scope++;

        std::vector<llvm::Type*> param;

        for (int i = 0; i < std::stoi(s[sc][2]); i++)
            param.push_back(getTypefromString(s[sc][3 + i], m));

        llvm::FunctionType * ftype = llvm::FunctionType::get(
                getTypefromString(t.children[0]->token.getTokenName(), m), param, false);

        llvm::Function * func = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, sc.second, m);
        func->setCallingConv(llvm::CallingConv::C);

        currentFunction = sc.second;
        paramIndex = 0;

        llvm::BasicBlock::Create(m->getContext(), std::string("entry_").append(sc.second), func, 0);
    }

    void CodeGeneration::localVariableDeclaration(Tree::Tree& t, llvm::Module* m) {

        llvm::Function * func = m->getFunction(currentFunction);

        llvm::Function::iterator b = func->begin();

        ScopeName sc(scope, t.children[1]->token.getTokenName());

        llvm::BasicBlock* block = b;

        llvm::AllocaInst * variable = new llvm::AllocaInst(
                getTypefromString(t.children[0]->token.getTokenName(), m),
                t.children[1]->token.getTokenName(), block);
        variable->setAlignment(4);

        variablesHash[sc] = variable;
    }

    void CodeGeneration::printHashTable() {

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

    llvm::Value* CodeGeneration::getHashValue(std::string n) {

        return (variablesHash.find(ScopeName(scope, n)) != variablesHash.end())
                ?
                variablesHash[ScopeName(scope, n)] : paramHash[ScopeName(scope, n)];
    }

    llvm::Value * CodeGeneration::operationsExpression(Tree::Tree& t, llvm::Module* m) {

        for (unsigned int i = 0; i < t.children.size(); i++)
            if (t.children[i])
                operationsExpression(*t.children[i], m);

        //llvm::Function * func = m->getFunction(currentFunction);
        //llvm::Function::iterator b = func->begin();

        //while ((b + 1) != b->end())
        //    b++;


        std::cout << t.exp << std::endl;
        if (t.children.size())
            t.children[0]->token.print();

        if (!t.exp.compare(MULTEXPSTRING)) {

        }

        return NULL;
    }

    void CodeGeneration::attributionStatement(Tree::Tree& t, llvm::Module* m) {

        llvm::Value * val;
        //t.children[0]->token.print();

        llvm::Function * func = m->getFunction(currentFunction);
        llvm::BasicBlock * b = func->begin();

        val = getHashValue(t.children[0]->token.getTokenName());

        //operationsExpression(* t.children[1], m);

        llvm::StoreInst * storeVal = new llvm::StoreInst(varConst, val, b);
    }

    void CodeGeneration::expressionStatement(Tree::Tree& t, SymbolTable s, llvm::Module * m) {

        if (!t.children[0]->exp.compare(VARDECSTRING))
            localVariableDeclaration(*t.children[0], m);

        if (!t.children[0]->exp.compare(ATTSTRING))
            attributionStatement(*t.children[0], m);
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

        printHashTable();

        delete out;
        delete mod;

        system("llvm-dis tiny.bc");
    }
}