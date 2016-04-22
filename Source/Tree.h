/* 
 * File:   Tree.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on April 19, 2016, 3:49 AM
 */

#ifndef TREE_H
#define TREE_H

#include "Token.h"
#include <string>
#include <vector>
#include <iomanip>

namespace Tree {

    class Tree {
    public:
        Tree();
        virtual ~Tree();

        Token::Token getToken();
        std::string getExp();
        int getActive();
        void setChild(Token::Token);
        void setChild(std::string);
        void setExp(std::string);
        void setToken(Token::Token);
        void printTree(std::ofstream&);
        Tree * subTree();
        std::string exp;
        Token::Token token;

        int active;
        std::vector<Tree*> children;
    };
}

#endif /* TREE_H */

