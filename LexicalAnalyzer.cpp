/* 
 * File:   LexicalAnalyzer.cpp
 * Author: LuanB
 * 
 * Created on 17 de Março de 2016, 00:56
 */

#include "LexicalAnalyzer.h"

namespace Lex {

    std::vector<Token::Token> LexicalAnalyzer::tokens;

    //Regular Expressions
    //Operations
    boost::regex
    o_SUM("^\\+"), o_SUB("^\\-"), o_MUL("^\\*"),
    o_DIV("^\\/"), o_SME("^<="), o_BGE("^>="),
    o_ATT("^\\:="), o_EQU("^\\="), o_COM("^\\,"),
    o_DOP("^\\:"), o_SMA("^<"), o_BIG("^>"),
    o_OPA("^\\("), o_CPA("^\\)");

    //Keywords
    boost::regex
    k_IF("^\\bse\\b"), k_TH("^\\bentão\\b"),
    k_OT("^\\bsenão\\b"), k_EN("^\\bfim\\b"),
    k_RP("^\\brepita\\b"), k_FL("^\\bflutuante\\b"),
    k_VO("^\\bvazio\\b"), k_TL("^\\bate\\b"),
    k_RE("^\\bleia\\b"), k_WR("^\\bescreve\\b"),
    k_IN("^\\binteiro\\b"), k_RT("^\\bretorna\\b");

    //Comments
    boost::regex
    c_CM("^\\{\\w.[^}]+"), c_CC("^\\}");

    //Blank space
    boost::regex b_SP("^ ");

    //Numbers
    boost::regex
    n_IN("^\\b[0-9]+\\b"), n_SI("^\\b[0-9]+e[+|-]?[0-9]+\\b"),
    n_FL("^\\b[0-9]+.[0-9]+\\b"),
    n_SF("^\\b[0-9]+.[0-9]+e[+|-]?[0-9]+\\b");

    //Identifier
    boost::regex i_ID("^\\b[A-Za-zÀ-ú_][A-Za-zÀ-ú0-9_]*");

    LexicalAnalyzer::LexicalAnalyzer(std::string fileName) {

        tokenCollector(fileName);
    }

    LexicalAnalyzer::~LexicalAnalyzer() {
    }

    void LexicalAnalyzer::tokenCollector(std::string fileName) {

        std::ifstream file;
        file.open(fileName);

        std::string remove = "";

        boost::smatch match;

        Token::Token tokenTemp;

        int line = 0, column = 0;

        while (!file.eof()) {

            std::string bufferString;
            std::getline(file, bufferString);
            while (bufferString.size() > 0) {

                if (boost::regex_search(bufferString, match, c_CM)) {

                    bufferString = boost::regex_replace(bufferString, c_CM, remove);
                    bufferString = boost::regex_replace(bufferString, c_CC, remove);
                } else if (boost::regex_search(bufferString, match, b_SP)) {

                    bufferString = boost::regex_replace(bufferString, b_SP, remove);
                } else if (boost::regex_search(bufferString, match, o_SUM)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::SUM);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_SUM, remove);
                } else if (boost::regex_search(bufferString, match, o_SUB)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::SUBTRACTION);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_SUB, remove);
                } else if (boost::regex_search(bufferString, match, o_MUL)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::MULTIPLICATION);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_MUL, remove);
                } else if (boost::regex_search(bufferString, match, o_DIV)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::DIVISION);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_DIV, remove);
                } else if (boost::regex_search(bufferString, match, o_COM)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::COMMA);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_COM, remove);
                } else if (boost::regex_search(bufferString, match, o_SME)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::SMALL_EQUAL);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_SME, remove);
                } else if (boost::regex_search(bufferString, match, o_BGE)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::BIGGER_EQUAL);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_BGE, remove);
                } else if (boost::regex_search(bufferString, match, o_ATT)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::ATTRIBUTION);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_ATT, remove);
                } else if (boost::regex_search(bufferString, match, o_EQU)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::EQUAL);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_EQU, remove);
                } else if (boost::regex_search(bufferString, match, o_DOP)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::DOUBLE_POINT);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_DOP, remove);
                } else if (boost::regex_search(bufferString, match, o_SMA)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::SMALLER_THAN);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_SMA, remove);
                } else if (boost::regex_search(bufferString, match, o_BIG)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::BIGGER_THAN);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_BIG, remove);
                } else if (boost::regex_search(bufferString, match, o_OPA)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::OPEN);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_OPA, remove);
                } else if (boost::regex_search(bufferString, match, o_CPA)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::CLOSE);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, o_CPA, remove);
                } else if (boost::regex_search(bufferString, match, k_IF)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::IF);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_IF, remove);
                } else if (boost::regex_search(bufferString, match, k_TH)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::THEN);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_TH, remove);
                } else if (boost::regex_search(bufferString, match, k_OT)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::OTHERWISE);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_OT, remove);
                } else if (boost::regex_search(bufferString, match, k_RP)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::REPEAT);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_RP, remove);
                } else if (boost::regex_search(bufferString, match, k_FL)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::FLOAT);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_FL, remove);
                } else if (boost::regex_search(bufferString, match, k_VO)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::VOID);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_VO, remove);
                } else if (boost::regex_search(bufferString, match, k_TL)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::UNTIL);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_TL, remove);
                } else if (boost::regex_search(bufferString, match, k_RE)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::READ);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_RE, remove);
                } else if (boost::regex_search(bufferString, match, k_WR)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::WRITE);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_WR, remove);
                } else if (boost::regex_search(bufferString, match, k_IN)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::INTEGER);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_IN, remove);
                } else if (boost::regex_search(bufferString, match, k_RT)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::RETURN);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_RT, remove);
                } else if (boost::regex_search(bufferString, match, k_EN)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::END);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, k_EN, remove);
                } else if (boost::regex_search(bufferString, match, n_SF) ||
                        boost::regex_search(bufferString, match, n_FL) ||
                        boost::regex_search(bufferString, match, n_SI)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::NUMBER_FLOAT);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);
                    if (boost::regex_search(bufferString, match, n_SF))
                        bufferString = boost::regex_replace(bufferString, n_SF, remove);
                    else if (boost::regex_search(bufferString, match, n_FL))
                        bufferString = boost::regex_replace(bufferString, n_FL, remove);
                    else
                        bufferString = boost::regex_replace(bufferString, n_SI, remove);
                } else if (boost::regex_search(bufferString, match, n_IN)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::NUMBER_INTEGER);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, n_IN, remove);
                } else if (boost::regex_search(bufferString, match, i_ID)) {

                    tokenTemp.setTokenName(match.str());
                    tokenTemp.setTokenType(Token::IDENTIFIER);
                    tokenTemp.setTokenColumn(column++);
                    tokenTemp.setTokenLine(line);

                    tokens.push_back(tokenTemp);

                    bufferString = boost::regex_replace(bufferString, i_ID, remove);
                }
            }

            line++;
            column = 0;
        }
    }

    Token::Token LexicalAnalyzer::getNextToken() {

        Token::Token tokenTemp;
        tokenTemp = tokens.front();

        tokens.erase(tokens.begin());

        return tokenTemp;
    }

    bool LexicalAnalyzer::emptyTokenList() {

        return (tokens.empty()) ? true : false;
    }
}