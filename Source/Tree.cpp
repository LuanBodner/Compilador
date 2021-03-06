/* 
 * File:   Tree.cpp
 * Author: Luan Bodner do Rosário <luan.rosario.bodner@gmail.com>
 * 
 * Created on April 19, 2016, 3:49 AM
 */

#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Tree.h"

namespace Tree {

    Tree::Tree() {
    }

    Tree::~Tree() {
    }

    Token::Token Tree::getToken() {

        return token;
    }

    std::string Tree::getExp() {

        return exp;
    }

    int Tree::getActive() {

        return active;
    }

    void Tree::setChild(Token::Token token) {

        children.push_back(new Tree());
        children[children.size() - 1]->token = token;
        children[children.size() - 1]->active = 1;
    }

    void Tree::setChild(std::string exp) {

        children.push_back(new Tree());
        children[children.size() - 1]->exp = exp;
        children[children.size() - 1]->active = 0;
    }

    void Tree::setExp(std::string expression) {

        exp = expression;
        active = 0;
    }

    void Tree::setToken(Token::Token token) {

        this->token = token;
        active = 1;
    }

    Tree * Tree::subTree() {

        children.push_back(new Tree());
        return children[children.size() - 1];
    }

    void Tree::printTree(std::ofstream & output, int level) {

        if (level)
            output << std::setw(level) << ' ';

        if (!active)
            output << exp << "\n";
        else
            output << token.getTokenName() << "\n";

        for (const auto &t : children)
            t->printTree(output, level + 4);
    }
}