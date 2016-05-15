/* 
 * File:   Token.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on 17 de Março de 2016, 00:23
 */

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

namespace Token {

    /* Enum for the possible tokens in the language */
    typedef enum {
        IF, THEN, OTHERWISE, END, REPEAT,
        FLOAT, VOID, UNTIL, READ, WRITE,
        INTEGER, COMMENTS, RETURN, SUM, SUBTRACTION,
        MULTIPLICATION, DIVISION, EQUAL, COMMA, ATTRIBUTION,
        LESS_THAN, BIGGER_THAN, LESS_EQUAL, BIGGER_EQUAL, OPEN,
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
        /* Attributes */
        std::string tokenName;
        TokenType token;
        int tokenColumn;
        int tokenLine;
    };
}

#endif /* TOKEN_H */

