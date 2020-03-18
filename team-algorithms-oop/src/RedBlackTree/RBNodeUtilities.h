#pragma once

#include "RedBlackTree.h"

namespace tree::utils {

    template<typename T>
    bool hasRedChild(tree::Node<tree::RedBlackTree<T>> *node) {
        return (node->left != nullptr && node->left->color == tree::Color::red) ||
               (node->right != nullptr && node->right->color == tree::Color::red);
    }

    template<typename T>
    void swapColors(tree::Node<tree::RedBlackTree<T>> *firstNode, tree::Node<tree::RedBlackTree<T>> *secondNode) {
        tree::Color temp = firstNode->color;
        firstNode->color = secondNode->color;
        secondNode->color = temp;
    }
}
