/* 
 * File:   Tree.h
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 *
 * Created on April 19, 2016, 3:49 AM
 */

#ifndef TREE_H
#define TREE_H

#include "Token.h"
#include <vector>

namespace Tree {

    class Tree {
    public:
        Tree();
        virtual ~Tree();

        Token::Token getToken();
        void printTree(std::ofstream&);
        void insertToken(Token::Token);
        void insertChild(Token::Token, int);
        Tree * newSubTree();
        Token::Token token;
        std::vector<Tree*> children;
    };
}

#endif /* TREE_H */

