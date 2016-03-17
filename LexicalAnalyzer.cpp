/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LexicalAnalyzer.cpp
 * Author: LuanB
 * 
 * Created on 17 de Março de 2016, 00:56
 */

#include <iostream>

#include "LexicalAnalyzer.h"

//Regular Expressions
std::string t_SUM = "^+",
        t_SUB = "^-",
        t_MUL = "^*",
        t_DIV = "^/",
        t_EQU = "^=",
        t_COM = "^,",
        t_ATT = "^:=",
        t_SMA = "^<",
        t_BIG = "^>",
        t_SME = "^<=",
        t_BGE = "^>=",
        t_OPA = "^(",
        t_CPA = "^)";

std::string k_IF = "^se",
        k_TH = "^então",
        k_OT = "^senão",
        k_EN = "^fim",
        k_RP = "^repita",
        k_FL = "^flutuante",
        k_VO = "^vazio",
        k_TL = "^até",
        k_RE = "^leia",
        k_WR = "^escreve",
        k_IN = "^inteiro",
        k_RT = "^retorna";

std::string c_OT = "^{",
        c_CT = "^}";

namespace Lex {

    LexicalAnalyzer::LexicalAnalyzer() {
    }

    LexicalAnalyzer::~LexicalAnalyzer() {
    }

    std::string LexicalAnalyzer::readFile(std::string fileName) {

        std::ifstream tinyFile;

        tinyFile.open(fileName);

        std::string bufferCharVec((std::istreambuf_iterator<char>(tinyFile)),
                std::istreambuf_iterator<char>());

        tinyFile.close();

        return bufferCharVec;
    }

    void LexicalAnalyzer::tokenFinder(std::string fileName) {

        std::string bufferCharVec = readFile(fileName);
        std::string tokenTemp;

        unsigned int sizeCount = 0;

        while (bufferCharVec.size() >= sizeCount) {
            break;
        }

        std::cout << tokenTemp;
    }
}

