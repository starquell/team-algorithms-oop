#pragma once

#include "RedBlackTree.h"
#include "NodeTools.hpp"
#include "BinarySearchTreeIterator.hpp"

namespace tree {

    template <typename T>
    bool RedBlackTree<T>::Node::hasRedChild() {
        return (left != nullptr && left->color == red) ||
               (right != nullptr && right->color == red);
    }

    template <typename T>
    void RedBlackTree<T>::Node::swapColors(Node* firstNode, Node* secondNode) {
        Color temp = firstNode->color;
        firstNode->color = secondNode->color;
        secondNode->color = temp;
    }

    template <typename T>
        auto RedBlackTree<T>::simpleInsert(Node *currNode, Node *inputNode) { //insert like in ordinary BST
            if (currNode == nullptr) {
                return inputNode;
            }

            if (inputNode->data < currNode->data) {
                currNode->left = simpleInsert(currNode->left, inputNode);
                currNode->left->parent = currNode;
            } else if (inputNode->data > currNode->data) {
                currNode->right = simpleInsert(currNode->right, inputNode);
                currNode->right->parent = currNode;
            }

            return currNode;
        }

    template <typename T>
    typename RedBlackTree<T>::Node* RedBlackTree<T>::find(const T &elem) {
        Node *node = root;
        while (node) {
            if (node->data > elem) {
                node = node->left;
            } else if (node->data < elem) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }

    template <typename T>
        void RedBlackTree<T>::rotateLeft(Node *&currNode) {
            Node *currChildRight = currNode->right;
            currNode->right = currChildRight->left;

            if (currNode->right != nullptr) {
                currNode->right->parent = currNode;
            }

            currChildRight->parent = currNode->parent;

            if (currNode->parent == nullptr) {
                root = currChildRight;
            } else if (currNode == currNode->parent->left) {
                currNode->parent->left = currChildRight;
            } else {
                currNode->parent->right = currChildRight;
            }

            currChildRight->left = currNode;
            currNode->parent = currChildRight;
        }

    template <typename T>
        void RedBlackTree<T>::rotateRight(Node *&currNode) {
            Node *currChildLeft = currNode->left;
            currNode->left = currChildLeft->right;

            if (currNode->left != nullptr) {
                currNode->left->parent = currNode;
            }

            currChildLeft->parent = currNode->parent;

            if (currNode->parent == nullptr) {
                root = currChildLeft;
            } else if (currNode == currNode->parent->left) {
                currNode->parent->left = currChildLeft;
            } else {
                currNode->parent->right = currChildLeft;
            }

            currChildLeft->right = currNode;
            currNode->parent = currChildLeft;
        }

    template <typename T>
        void RedBlackTree<T>::fixTree(Node *&currNode) {
            Node *currParent = nullptr;
            Node *currGrandparent = nullptr;

            while ((currNode != this->root) && (currNode->color != black) && (currNode->parent->color == red)) {
                currParent = currNode->parent;
                currGrandparent = currNode->parent->parent;

                //parent of current node is left child
                if (currParent == currGrandparent->left) {
                    Node *currUncle = currGrandparent->right;

                    //uncle is red: do only recoloring
                    if (currUncle != nullptr && currUncle->color == red) {
                        currGrandparent->color = red;
                        currParent->color = black;
                        currUncle->color = black;
                        currNode = currGrandparent;

                    } else {
                        //current node is right child: left rotation
                        if (currNode == currParent->right) {
                            rotateLeft(currParent);
                            currNode = currParent;
                            currParent = currNode->parent;
                        }

                        //current node is left child: right rotation
                        rotateRight(currGrandparent);
                        Node::swapColors(currParent, currGrandparent);
                        currNode = currParent;
                    }
                } else { //parent of current node is right child
                    Node *currUncle = currGrandparent->left;

                    //uncle is red: do only recoloring
                    if (currUncle != nullptr && currUncle->color == red) {
                        currGrandparent->color = red;
                        currParent->color = black;
                        currUncle->color = black;
                        currNode = currGrandparent;

                    } else {
                        //current node is left child: right rotation
                        if (currNode == currParent->left) {
                            rotateRight(currParent);
                            currNode = currParent;
                            currParent = currNode->parent;
                        }

                        //current node is right child: left rotation
                        rotateLeft(currGrandparent);
                        Node::swapColors(currParent, currGrandparent);
                        currNode = currParent;
                    }
                }
            }

            root->color = black;
        };

        template <typename T>
        typename RedBlackTree<T>::Node* RedBlackTree<T>::simpleReplace(Node *node) {
            // when node have 2 children
            if (node->left != nullptr && node->right != nullptr) {
                return detail::min(node->right);
            }

            // when leaf
            if (node->left == nullptr && node->right == nullptr) {
                return nullptr;
            }

            // when single child
            if (node->left != nullptr) {
                return node->left;
            } else {
                return node->right;
            }
        }

    template <typename T>
        void RedBlackTree<T>::fixBothBlack(Node *node) {
            if (node == root) { // Reached root
                return;
            }

            Node *sibling = detail::sibling(node);
            Node *parent = node->parent;
            if (sibling == nullptr) {
                // No sibiling, double black pushed up
                fixBothBlack(parent);
            } else if (sibling->color == red) {
                // Sibling red
                parent->color = red;
                sibling->color = black;
                if (detail::isLeftSon(sibling)) {
                    // left case
                    rotateRight(parent);
                } else {
                    // right case
                    rotateLeft(parent);
                }
                fixBothBlack(node);
            } else {
                // Sibling black
                if (sibling->hasRedChild()) {
                    // at least 1 red children
                    if (sibling->left != nullptr && sibling->left->color == red) {
                        if (detail::isLeftSon(sibling)) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rotateRight(parent);
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            rotateRight(sibling);
                            rotateLeft(parent);
                        }
                    } else {
                        if (detail::isLeftSon(sibling)) {
                            // left right
                            sibling->right->color = parent->color;
                            rotateLeft(sibling);
                            rotateRight(parent);
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            rotateLeft(parent);
                        }
                    }
                    parent->color = black;
                } else {
                    // 2 black children
                    sibling->color = red;
                    if (parent->color == black)
                        fixBothBlack(parent);
                    else
                        parent->color = black;
                }
            }
        }

    template <typename T>
        void RedBlackTree<T>::eraseNode(Node *nodeToDelete) {
            Node *nodeToReplace = simpleReplace(nodeToDelete);

            // True when u and v are both black
            bool bothBlack = ((nodeToReplace == nullptr || nodeToReplace->color == black)
                              && (nodeToDelete->color == black));
            Node *parent = nodeToDelete->parent;

            if (nodeToReplace == nullptr) {
                // u is NULL therefore v is leaf
                if (nodeToDelete == root) {
                    // v is root, making root null
                    root = nullptr;
                } else {
                    if (bothBlack) {
                        // u and v both black
                        // v is leaf, fix double black at v
                        fixBothBlack(nodeToDelete);
                    } else {
                        // u or v is red
                        if (detail::sibling(nodeToDelete) != nullptr)
                            // sibling is not null, make it red"
                            detail::sibling(nodeToDelete)->color = red;
                    }

                    // delete v from the tree

                    if (detail::isLeftSon(nodeToDelete)) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                }
                delete nodeToDelete;
                return;
            }

            if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
                // nodeToDelete has 1 child
                if (nodeToDelete == root) {
                    // v is root, assign the value of u to v, and delete u
                    nodeToDelete->data = nodeToReplace->data;
                    nodeToDelete->left = nullptr;
                    nodeToDelete->right = nullptr;
                    delete nodeToReplace;
                } else {
                    // Detach v from tree and move u up
                    if (detail::isLeftSon(nodeToDelete)) {
                        parent->left = nodeToReplace;
                    } else {
                        parent->right = nodeToReplace;
                    }
                    delete nodeToDelete;
                    nodeToReplace->parent = parent;
                    if (bothBlack) {
                        // u and v both black, fix double black at u
                        fixBothBlack(nodeToReplace);
                    } else {
                        // u or v red, color u black
                        nodeToReplace->color = black;
                    }
                }
                return;
            }

            // v has 2 children, swap values with successor and recurse
            detail::swapData(nodeToReplace, nodeToDelete);
            eraseNode(nodeToReplace);
        }

    template <typename T>
        void RedBlackTree<T>::printTreePreorder(Node *curr) {
            if (curr != nullptr) {
                std::cout << "{" << curr->data << " - " << curr->color << "} ";
                printTreePreorder(curr->left);
                printTreePreorder(curr->right);
            }
        }

    template <typename T>
        auto RedBlackTree<T>::begin () const -> iterator {
            return iterator {detail::min(root)};
        }

    template <typename T>
        auto RedBlackTree<T>::end () const -> iterator {
            return iterator {nullptr};
        }

    template <typename T>
    RedBlackTree<T>::RedBlackTree(std::vector<T> &_data) {
        root = nullptr;
        for (auto &item : _data) {
        insert(item);
    }
    }

    template <typename T>
    void RedBlackTree<T>::insert(const T _data) {
        auto inputNode = new Node(_data);
        this->root = simpleInsert(this->root, inputNode);

        fixTree(inputNode);
    }

    template <typename T>
    void RedBlackTree<T>::erase(T _data) {
        if (root == nullptr) { return; }

        Node *nodeToDelete = find(_data);

        if (nodeToDelete == nullptr) {
            std::cout << "No node with such value to delete:" << _data << std::endl;
            return;
        }

        eraseNode(nodeToDelete);
    }

    template <typename T>
    typename RedBlackTree<T>::iterator RedBlackTree<T>::search(const T &elem) const {
        Node *node = root;
        while (node) {
            if (node->data > elem) {
                node = node->left;
            } else if (node->data < elem) {
                node = node->right;
            } else {
                return iterator(node);
            }
        }
        return end();
    }

    template <typename T>
    void RedBlackTree<T>::print() {
        printTreePreorder(root);
        std::cout << std::endl;
    }

    };