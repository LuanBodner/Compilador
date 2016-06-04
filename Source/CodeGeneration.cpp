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

    void CodeGeneration::functionDefinition(Tree::Tree& tree, SymbolTable s, LLVMModuleRef m) {
    }

    void CodeGeneration::globalVariableDeclaration(Tree::Tree& tree, SymbolTable s, LLVMModuleRef m) {

        LLVMValueRef variable;

        const char* name = tree.children[1]->token.getTokenName().c_str();

        switch (tree.children[0]->token.getTokenType()) {

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

    void CodeGeneration::generateCode(Tree::Tree& tree, SymbolTable s, LLVMModuleRef m) {

        if (!tree.exp.compare(VARDECSTRING) && scope == 0)
            globalVariableDeclaration(tree, s, m);

        if (!tree.exp.compare(FUNCDECSTRING))
            functionDefinition(tree, s, m);

        for (unsigned int i = 0; i < tree.children.size(); i++)
            if (!tree.active)
                generateCode(*tree.children[i], s, m);
    }

    void CodeGeneration::treeAnalyzer(Tree::Tree& tree, SymbolTable s) {

        LLVMModuleRef mod = LLVMModuleCreateWithName("mainModule");

        generateCode(tree, s, mod);

        if (LLVMWriteBitcodeToFile(mod, "tiny.bc") != 0)
            fprintf(stderr, "error writing bitcode to file, skipping\n");

    }
}
