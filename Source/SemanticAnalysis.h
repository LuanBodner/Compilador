/* 
 * File:   SemanticAnalysis.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on May 8, 2016, 5:16 PM
 */

#ifndef SEMANTICANALYSIS_H
#define SEMANTICANALYSIS_H
#include <iostream>
#include <unordered_map>

#include "SyntaxAnalysis.h"

namespace Semantic {

    class SemanticAnalysis {
    public:
        SemanticAnalysis();
        virtual ~SemanticAnalysis();

        void treeAnalyzer(Syntax::SyntaxAnalysis);

    private:
        std::unordered_map<std::string, std::string> symbolTable;
    };
}
#endif /* SEMANTICANALYSIS_H */

