/* 
 * File:   CodeGeneration.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on May 22, 2016, 11:01 AM
 */

#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

namespace CodeGeneration {

    class CodeGeneration {
    public:
        CodeGeneration();
        virtual ~CodeGeneration();
        void treeAnalyzer();
    private:

    };
}
#endif /* CODEGENERATION_H */

