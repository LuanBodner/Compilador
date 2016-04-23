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

        // Verifies which attribute is active
        int getActive();

        // Sets the last child in the vector
        void setChild(Token::Token);
        void setChild(std::string);

        // Sets the root expression or token
        void setExp(std::string);
        void setToken(Token::Token);

        // Prints tree
        void printTree(std::ofstream&, int);

        // Creates a subtree
        Tree * subTree();

        // Attributes
        std::string exp;
        Token::Token token;
        int active;
        std::vector<Tree*> children;
    };
}

#endif /* TREE_H */

