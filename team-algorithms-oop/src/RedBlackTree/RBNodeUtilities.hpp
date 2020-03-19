#pragma once

#include "RedBlackTree.hpp"

namespace tree::utils {

    template<typename T>
    bool hasRedChild(tree::Node<tree::RedBlackTree<T>>* node) {
        return (node->left != nullptr && node->left->color == tree::Node<tree::RedBlackTree<T>>::Color::Red) ||
               (node->right != nullptr && node->right->color == tree::Node<tree::RedBlackTree<T>>::Color::Red);
    }

    template<typename T>
    void swapColors(tree::Node<tree::RedBlackTree<T>>* firstNode, tree::Node<tree::RedBlackTree<T>>* secondNode) {
        typename tree::Node<tree::RedBlackTree<T>>::Color temp = firstNode->color;
        firstNode->color = secondNode->color;
        secondNode->color = temp;
    }

    /**
     *
     * @brief Copy field of toCopy node to toPaste node, but without fields-pointers
     *
     */
    template <typename T>
    void copyNodeData (tree::Node<tree::RedBlackTree<T>>* toCopy, tree::Node<tree::RedBlackTree<T>>* toPaste) {
        toPaste->data = toCopy->data;
        toPaste->color = toCopy->color;
    }
}
