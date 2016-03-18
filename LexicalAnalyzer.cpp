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

//Operations
std::string p_SUM = "^+",
        o_SUB = "^-",
        o_MUL = "^*",
        o_DIV = "^/",
        o_EQU = "^=",
        o_COM = "^,",
        o_ATT = "^:=",
        o_SMA = "^<",
        o_BIG = "^>",
        o_SME = "^<=",
        o_BGE = "^>=",
        o_OPA = "^(",
        o_CPA = "^)";

//Keywords
std::string k_IF = "^\\bse\\b",
        k_TH = "^\\bentão\\b",
        k_OT = "^\\bsenão\\b",
        k_EN = "^\\bfim\\b",
        k_RP = "^\\brepita\\b",
        k_FL = "^\\bflutuante\\b",
        k_VO = "^\\bvazio\\b",
        k_TL = "^\\baté\\b",
        k_RE = "^\\bleia\\b",
        k_WR = "^\\bescreve\\b",
        k_IN = "^\\binteiro\\b",
        k_RT = "^\\bretorna\\b";

//Comments
std::string c_CM = "^{.*}";

//Numbers
std::string n_IN = "^(?:^|(?<=\\s))[0-9]+(?=$|\\s)",
        n_SI = "^(?:^|(?<=\\s))[0-9]+e[+|-]*[0-9]+(?=$|\\s)",
        n_FL = "^[-+]?[0-9]+\\.[0-9]+",
        n_SF = "^(?:^|(?<=\\s))[0-9]+e[+|-]*[0-9]+(?=$|\\s)";

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

