/* 
 * File:   LexicalAnalyzer.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on 17 de Março de 2016, 00:56
 */

#include "LexicalAnalyzer.h"
#include "CompilerErrors.h"

namespace Lex {

    unsigned int index = 0;

    std::vector<Token::Token> LexicalAnalyzer::tokens;

    //Regular Expressions
    //Operations
    boost::regex
    o_SUM("^\\+"), o_SUB("^\\-"), o_MUL("^\\*"), o_DIV("^\\/"), o_SME("^<="), o_BGE("^>="),
    o_ATT("^\\:="), o_EQU("^\\="), o_COM("^\\,"), o_DOP("^\\:"), o_SMA("^<"), o_BIG("^>"),
    o_OPA("^\\("), o_CPA("^\\)");

    //Keywords
    boost::regex
    k_IF("^\\bse\\b"), k_TH("^\\bentão\\b"), k_OT("^\\bsenão\\b"), k_EN("^\\bfim\\b"),
    k_RP("^\\brepita\\b"), k_FL("^\\bflutuante\\b"), k_VO("^\\bvazio\\b"), k_TL("^\\bate\\b"),
    k_RE("^\\bleia\\b"), k_WR("^\\bescreve\\b"), k_IN("^\\binteiro\\b"), k_RT("^\\bretorna\\b");

    //Comments
    boost::regex
    c_CM("^\\{\\w.[^}]+"), c_CC("^\\}");

    //Blank space
    boost::regex b_SP("^ ");

    //Numbers
    boost::regex
    n_IN("^\\b[0-9]+\\b"), n_SI("^\\b[0-9]+e[+|-]?[0-9]+\\b"),
    n_FL("^\\b[0-9]+.[0-9]+\\b"), n_SF("^\\b[0-9]+.[0-9]+e[+|-]?[0-9]+\\b");

    //Identifier
    boost::regex i_ID("^\\b[A-Za-zÀ-ú_][A-Za-zÀ-ú0-9_]*");

    LexicalAnalyzer::LexicalAnalyzer(std::string fileName) {

        tokenCollector(fileName);
    }

    LexicalAnalyzer::LexicalAnalyzer() {
    }

    LexicalAnalyzer::~LexicalAnalyzer() {
    }

    void LexicalAnalyzer::tokenInserter(std::string &buffer, std::string string,
            Token::TokenType type, boost::regex operation, int column, int line) {

        Token::Token tokenTemp;

        tokenTemp.setTokenName(string);
        tokenTemp.setTokenType(type);
        tokenTemp.setTokenColumn(column);
        tokenTemp.setTokenLine(line);

        tokens.push_back(tokenTemp);

        buffer = boost::regex_replace(buffer, operation, "");
    }

    void LexicalAnalyzer::tokenCollector(std::string fileName) {

        std::ifstream file;
        file.open(fileName);

        boost::smatch match;

        Token::Token tokenTemp;

        int line = 0, column = 0;

        while (!file.eof()) {

            std::string bufferString;
            std::getline(file, bufferString);
            while (bufferString.size() > 0) {

                if (boost::regex_search(bufferString, match, c_CM)) {

                    bufferString = boost::regex_replace(bufferString, c_CM, "");
                    bufferString = boost::regex_replace(bufferString, c_CC, "");
                } else if (boost::regex_search(bufferString, match, b_SP))
                    bufferString = boost::regex_replace(bufferString, b_SP, "");

                else if (boost::regex_search(bufferString, match, o_SUM))
                    tokenInserter(bufferString, match.str(), Token::SUM, o_SUM, column++, line);

                else if (boost::regex_search(bufferString, match, o_SUB))
                    tokenInserter(bufferString, match.str(), Token::SUBTRACTION, o_SUB, column++, line);

                else if (boost::regex_search(bufferString, match, o_MUL))
                    tokenInserter(bufferString, match.str(), Token::MULTIPLICATION, o_MUL, column++, line);

                else if (boost::regex_search(bufferString, match, o_DIV))
                    tokenInserter(bufferString, match.str(), Token::DIVISION, o_DIV, column++, line);

                else if (boost::regex_search(bufferString, match, o_COM))
                    tokenInserter(bufferString, match.str(), Token::COMMA, o_COM, column++, line);

                else if (boost::regex_search(bufferString, match, o_SME))
                    tokenInserter(bufferString, match.str(), Token::SMALL_EQUAL, o_SME, column++, line);

                else if (boost::regex_search(bufferString, match, o_BGE))
                    tokenInserter(bufferString, match.str(), Token::BIGGER_EQUAL, o_BGE, column++, line);

                else if (boost::regex_search(bufferString, match, o_ATT))
                    tokenInserter(bufferString, match.str(), Token::ATTRIBUTION, o_ATT, column++, line);

                else if (boost::regex_search(bufferString, match, o_EQU))
                    tokenInserter(bufferString, match.str(), Token::EQUAL, o_EQU, column++, line);

                else if (boost::regex_search(bufferString, match, o_DOP))
                    tokenInserter(bufferString, match.str(), Token::DOUBLE_POINT, o_DOP, column++, line);

                else if (boost::regex_search(bufferString, match, o_SMA))
                    tokenInserter(bufferString, match.str(), Token::SMALLER_THAN, o_SMA, column++, line);

                else if (boost::regex_search(bufferString, match, o_BIG))
                    tokenInserter(bufferString, match.str(), Token::BIGGER_THAN, o_BIG, column++, line);

                else if (boost::regex_search(bufferString, match, o_OPA))
                    tokenInserter(bufferString, match.str(), Token::OPEN, o_OPA, column++, line);

                else if (boost::regex_search(bufferString, match, o_CPA))
                    tokenInserter(bufferString, match.str(), Token::CLOSE, o_CPA, column++, line);

                else if (boost::regex_search(bufferString, match, k_IF))
                    tokenInserter(bufferString, match.str(), Token::IF, k_IF, column++, line);

                else if (boost::regex_search(bufferString, match, k_TH))
                    tokenInserter(bufferString, match.str(), Token::THEN, k_TH, column++, line);

                else if (boost::regex_search(bufferString, match, k_OT))
                    tokenInserter(bufferString, match.str(), Token::OTHERWISE, k_OT, column++, line);

                else if (boost::regex_search(bufferString, match, k_RP))
                    tokenInserter(bufferString, match.str(), Token::REPEAT, k_RP, column++, line);

                else if (boost::regex_search(bufferString, match, k_FL))
                    tokenInserter(bufferString, match.str(), Token::FLOAT, k_FL, column++, line);

                else if (boost::regex_search(bufferString, match, k_VO))
                    tokenInserter(bufferString, match.str(), Token::VOID, k_VO, column++, line);

                else if (boost::regex_search(bufferString, match, k_TL))
                    tokenInserter(bufferString, match.str(), Token::UNTIL, k_TL, column++, line);

                else if (boost::regex_search(bufferString, match, k_RE))
                    tokenInserter(bufferString, match.str(), Token::READ, k_RE, column++, line);

                else if (boost::regex_search(bufferString, match, k_WR))
                    tokenInserter(bufferString, match.str(), Token::WRITE, k_WR, column++, line);

                else if (boost::regex_search(bufferString, match, k_IN))
                    tokenInserter(bufferString, match.str(), Token::INTEGER, k_IN, column++, line);

                else if (boost::regex_search(bufferString, match, k_RT))
                    tokenInserter(bufferString, match.str(), Token::RETURN, k_RT, column++, line);

                else if (boost::regex_search(bufferString, match, k_EN))
                    tokenInserter(bufferString, match.str(), Token::END, k_EN, column++, line);

                else if (boost::regex_search(bufferString, match, n_SF))
                    tokenInserter(bufferString, match.str(), Token::NUMBER_FLOAT, n_SF, column++, line);

                else if (boost::regex_search(bufferString, match, n_FL))
                    tokenInserter(bufferString, match.str(), Token::NUMBER_FLOAT, n_FL, column++, line);

                else if (boost::regex_search(bufferString, match, n_SI))
                    tokenInserter(bufferString, match.str(), Token::NUMBER_FLOAT, n_SI, column++, line);

                else if (boost::regex_search(bufferString, match, n_IN))
                    tokenInserter(bufferString, match.str(), Token::NUMBER_INTEGER, n_IN, column++, line);

                else if (boost::regex_search(bufferString, match, i_ID))
                    tokenInserter(bufferString, match.str(), Token::IDENTIFIER, i_ID, column++, line);

            }
            line++;
            column = 0;
        }
    }

    Token::Token LexicalAnalyzer::getNextToken() {

        if (index == tokens.size())
            throw "End\n";

        return tokens[index++];
    }

    Token::Token LexicalAnalyzer::getTokenByPos(unsigned int pos) {

        if (pos >= tokens.size())
            throw "End\n";

        return tokens[pos];
    }
}