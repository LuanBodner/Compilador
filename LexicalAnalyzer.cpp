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

#include "LexicalAnalyzer.h"

namespace Lex {
    //Regular Expressions


    //Operations
    std::tr1::regex p_SUM("^+"), o_SUB("^-"), o_MUL("^*"), o_DIV("^/"),
    o_EQU("^="), o_COM("^,"), o_ATT("^:="), o_SMA("^<"), o_BIG("^>"),
    o_SME("^<="), o_BGE("^>="), o_OPA("^("), o_CPA("^)");

    //Keywords
    std::tr1::regex k_IF("^\\bse\\b"), k_TH("^\\bentão\\b"),
    k_OT("^\\bsenão\\b"), k_EN("^\\bfim\\b"),
    k_RP("^\\brepita\\b"), k_FL("^\\bflutuante\\b"),
    k_VO("^\\bvazio\\b"), k_TL("^\\baté\\b"),
    k_RE("^\\bleia\\b"), k_WR("^\\bescreve\\b"),
    k_IN("^\\binteiro\\b"), k_RT("^\\bretorna\\b");

    //Comments
    std::tr1::regex c_CM("^{.*}");

    //Numbers
    std::tr1::regex n_IN("^(?:^|(?<=\\s))[0-9]+(?=$|\\s)"),
    n_SI("^(?:^|(?<=\\s))[0-9]+e[+|-]*[0-9]+(?=$|\\s)"),
    n_FL("^[-+]?[0-9]+\\.[0-9]+"),
    n_SF("^(?:^|(?<=\\s))[0-9]+e[+|-]*[0-9]+(?=$|\\s)");

    //Identifier
    std::tr1::regex i_ID("^\\b[A-Za-zÀ-ú_][A-Za-zÀ-ú0-9_]*");

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
        std::tr1::cmatch match;

        std::tr1::regex_search(bufferCharVec.c_str(), match, k_IN);

        std::cout << match.str() << std::endl;

    }
}

