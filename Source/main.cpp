/* 
 * File:   main.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on 16 de Março de 2016, 02:40
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>
#include <boost/preprocessor.hpp>
#include "Token.h"
#include "LexicalAnalyzer.h"
#include "SyntaxAnalysis.h"
#include "SemanticAnalysis.h"
#include "llvmCodeGeneration.h"

int main(int argc, char** argv) {

    if (argc < 4) {

        std::cout << "Wrong number of arguments\n";
        return EXIT_FAILURE;
    }

    std::ofstream output;
    output.open(argv[3], std::ofstream::out);

    Syntax::SyntaxAnalysis synx;
    synx.initialTarget(argv[1], argv[2]);

    Semantic::SemanticAnalysis semantic;
    Tree::Tree subTree = synx.getTree();
    semantic.treeAnalyzer(subTree);
    semantic.printTable();

    synx.getTree().printTree(output);

    /*
    llvmCodeGeneration::llvmCodeGeneration cgen;
    cgen.treeAnalyzer(subTree, semantic.symbolTable);
     */

    system("rm -f tempTiny.txt");

    return EXIT_SUCCESS;
}