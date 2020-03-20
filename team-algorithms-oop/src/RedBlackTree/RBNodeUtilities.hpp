#pragma once

#include "RedBlackTree.hpp"

namespace tree::rbutils {

    template<typename T>
    bool hasRedChild(Node<RedBlackTree<T>>* node) {
        return (node->left != nullptr && node->left->color == Node<RedBlackTree<T>>::Color::Red) ||
               (node->right != nullptr && node->right->color == Node<RedBlackTree<T>>::Color::Red);
    }

    template<typename T>
    void swapColors(Node<RedBlackTree<T>>* firstNode, Node<RedBlackTree<T>>* secondNode) {
        typename Node<RedBlackTree<T>>::Color temp = firstNode->color;
        firstNode->color = secondNode->color;
        secondNode->color = temp;
    }

    /**
     *
     * @brief Copy field of toCopy node to toPaste node, but without fields-pointers
     *
     */
    template <typename T>
    void copyNodeData (Node<RedBlackTree<T>>* toCopy, Node<RedBlackTree<T>>* toPaste) {
        toPaste->data = toCopy->data;
        toPaste->color = toCopy->color;
    }

    /**
     * @param currNode parent node before rotation
     */
    template <typename T>
    void rotateLeft(Node<RedBlackTree<T>>*& _root, Node<RedBlackTree<T>>*& currNode) {
        Node<RedBlackTree<T>>* currChildRight = currNode->right;
        currNode->right = currChildRight->left;

        if (currNode->right != nullptr) {
            currNode->right->parent = currNode;
        }

        currChildRight->parent = currNode->parent;

        if (currNode->parent == nullptr) {
            _root = currChildRight;
        } else if (currNode == currNode->parent->left) {
            currNode->parent->left = currChildRight;
        } else {
            currNode->parent->right = currChildRight;
        }

        currChildRight->left = currNode;
        currNode->parent = currChildRight;
    }

    /**
     * @param currNode parent node before rotation
     */
    template <typename T>
    void rotateRight(Node<RedBlackTree<T>>*& _root, Node<RedBlackTree<T>>* &currNode) {
        Node<RedBlackTree<T>>* currChildLeft = currNode->left;
        currNode->left = currChildLeft->right;

        if (currNode->left != nullptr) {
            currNode->left->parent = currNode;
        }

        currChildLeft->parent = currNode->parent;

        if (currNode->parent == nullptr) {
            _root = currChildLeft;
        } else if (currNode == currNode->parent->left) {
            currNode->parent->left = currChildLeft;
        } else {
            currNode->parent->right = currChildLeft;
        }

        currChildLeft->right = currNode;
        currNode->parent = currChildLeft;
    }
}
