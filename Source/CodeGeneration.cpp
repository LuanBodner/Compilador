/* 
 * File:   CodeGeneration.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on May 22, 2016, 11:01 AM
 */

#include "CodeGeneration.h"

namespace CodeGeneration {

    CodeGeneration::CodeGeneration() {
    }

    CodeGeneration::~CodeGeneration() {
    }

    void CodeGeneration::functionDefinition(Tree::Tree& tree, SymbolTable s) {

    }

    void CodeGeneration::variableDeclaration(Tree::Tree& tree, SymbolTable s) {

    }

    void CodeGeneration::treeAnalyzer(Tree::Tree& tree, SymbolTable s) {

        LLVMModuleRef mod = LLVMModuleCreateWithName("mainModule");
        

    }
}

