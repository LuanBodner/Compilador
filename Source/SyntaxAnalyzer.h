/* 
 * File:   SyntaxAnalyzer.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on March 31, 2016, 9:33 AM
 */

#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "Token.h"
#include "LexicalAnalyzer.h"
#include <string>

namespace SyntaxAnalyzer {

    class SyntaxAnalyzer {
    public:
        SyntaxAnalyzer();
        virtual ~SyntaxAnalyzer();
    private:

        Lex::LexicalAnalyzer lexer;

        Token::Token targetAdvance();
        void createLexer(std::string fileName);
        void targetAnalyzer();
        void addExprT();
        void mulExpr();
        void eat(Token::Token&);

    };
}
#endif /* SYNTAXANALYZER_H */

