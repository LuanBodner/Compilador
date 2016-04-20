/* 
 * File:   Tree.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on April 19, 2016, 3:49 AM
 */

#include <fstream>
#include "Tree.h"

namespace Tree {

    Tree::Tree() {

    }

    Tree::~Tree() {

    }

    Token::Token Tree::getToken() {

        return this->token;
    }

    void Tree::insertToken(Token::Token token) {

        this->token = token;
    }

    void Tree::insertChild(Token::Token token, int index) {

        children.push_back(new Tree());
        children[index]->token = token;
    }

    Tree * Tree::newSubTree() {
        
        children.push_back(new Tree());
        
        
        return children[children.size()-1];
    }

    void Tree::printTree(std::ofstream& output) {

        output << token.getTokenName() << "[";

        for (unsigned int index = 0; index != children.size(); index++) {

            children[index]->printTree(output);

            if (index + 1 != children.size())
                output << ",";
        }

        output << "]";
    }
}