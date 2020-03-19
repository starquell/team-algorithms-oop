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

    template <typename T>
    void treeFixingRecoloringCase(Node<RedBlackTree<T>>* currNode, Node<RedBlackTree<T>>* currGrandparent,
                                                   Node<RedBlackTree<T>>* currParent, Node<RedBlackTree<T>>* currUncle) {
        currGrandparent->color = tree::Node<tree::RedBlackTree<T>>::Red;
        currParent->color = tree::Node<tree::RedBlackTree<T>>::Black;
        currUncle->color = tree::Node<tree::RedBlackTree<T>>::Black;
        currNode = currGrandparent;
    }

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
