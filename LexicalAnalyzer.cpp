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

    std::vector<Token::Token> LexicalAnalyzer::tokens;

    boost::regex o_SUM("^\\+"),
    o_SUB("^\\-"),
    o_MUL("^\\*"),
    o_DIV("^\\/"),
    o_EQU("^\\="),
    o_COM("\\^,"),
    o_ATT("^\\:="),
    o_SMA("^\\<"),
    o_BIG("^\\>"),
    o_SME("^\\<="),
    o_BGE("^\\>="),
    o_OPA("^\\("),
    o_CPA("^\\)");

    //Keywords
    boost::regex k_IF("^\\bse\\b"),
    k_TH("^\\bentão\\b"),
    k_OT("^\\bsenão\\b"),
    k_EN("^\\bfim\\b"),
    k_RP("^\\brepita\\b"),
    k_FL("^\\bflutuante\\b"),
    k_VO("^\\bvazio\\b"),
    k_TL("^\\baté\\b"),
    k_RE("^\\bleia\\b"),
    k_WR("^\\bescreve\\b"),
    k_IN("^\\binteiro\\b"),
    k_RT("^\\bretorna\\b");

    //Comments
    boost::regex c_CM("^{.*}");

    //Numbers
    boost::regex n_IN("^(?:^|(?<=\\s))[0-9]+(?=$|\\s)"),
    n_SI("^(?:^|(?<=\\s))[0-9]+e[+|-]*[0-9]+(?=$|\\s)"),
    n_FL("^[-+]?[0-9]+\\.[0-9]+"),
    n_SF("^(?:^|(?<=\\s))[0-9]+e[+|-]*[0-9]+(?=$|\\s)");

    //Identifier
    boost::regex i_ID("^\\b[A-Za-zÀ-ú_][A-Za-zÀ-ú0-9_]*");

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
        std::string remove = "";

        boost::smatch match;

        Token::Token tokenTemp;

        if (boost::regex_search(bufferCharVec, match, o_SUM)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::SUM);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_SUM, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_SUB)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::SUBTRACTION);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_SUB, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_MUL)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::MULTIPLICATION);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_MUL, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_DIV)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::DIVISION);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_DIV, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_COM)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::COMMA);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_COM, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_SMA)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::SMALLER_THAN);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_SMA, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_BIG)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::BIGGER_THAN);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_BIG, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_OPA)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::OPEN);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_OPA, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_CPA)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::CLOSE);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_CPA, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_EQU)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::EQUAL);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_EQU, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_ATT)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::ATTRIBUTION);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_ATT, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_SME)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::SMALL_EQUAL);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_SME, remove); //
        } else if (boost::regex_search(bufferCharVec, match, o_BGE)) {

            tokenTemp.setTokenName(match.str());
            tokenTemp.setTokenType(Token::BIGGER_EQUAL);

            tokens.push_back(tokenTemp);

            bufferCharVec = boost::regex_replace(bufferCharVec, o_BGE, remove); //
        }
    }
}


