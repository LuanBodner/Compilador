/* 
 * File:   Token.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on 17 de Março de 2016, 00:23
 */

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <boost/preprocessor.hpp>
#include <iostream>

namespace Token {

    //Codes for the possible tokens 

    typedef enum {
        IF, THEN, OTHERWISE, END, REPEAT,
        FLOAT, VOID, UNTIL, READ, WRITE,
        INTEGER, COMMENTS, RETURN, SUM, SUBTRACTION,
        MULTIPLICATION, DIVISION, EQUAL, COMMA, ATTRIBUTION,
        SMALLER_THAN, BIGGER_THAN, SMALL_EQUAL, BIGGER_EQUAL, OPEN,
        CLOSE, NUMBER_INTEGER, NUMBER_FLOAT, DOUBLE_POINT, IDENTIFIER
    } TokenType;

    class Token {
    public:

        Token();
        Token(std::string, TokenType, int, int);
        virtual ~Token();

        std::string getTokenName();
        TokenType getTokenType();
        int getTokenLine();
        int getTokenColumn();
        void setTokenName(std::string);
        void setTokenType(TokenType);
        void setTokenLine(int);
        void setTokenColumn(int);
        std::string tokenTypeToString();
        void print();

    private:
        std::string tokenName;
        TokenType token;
        int tokenColumn;
        int tokenLine;
    };
}

#endif /* TOKEN_H */

