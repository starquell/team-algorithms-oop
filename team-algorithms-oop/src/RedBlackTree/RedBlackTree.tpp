#pragma once

#include "RedBlackTree.hpp"
#include "../NodeUtilities.hpp"
#include "RBNodeUtilities.hpp"

namespace tree {

    template <typename T>
    void RedBlackTree<T>::rotateLeft(Node<RedBlackTree<T>>*& currNode) {
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
    void RedBlackTree<T>::rotateRight(Node<RedBlackTree<T>>* &currNode) {
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

    template <typename T>
    void RedBlackTree<T>::fixTree(Node<RedBlackTree<T>>* &currNode) {
        Node<RedBlackTree<T>>* currParent = nullptr;
        Node<RedBlackTree<T>>* currGrandparent = nullptr;

        while (currNode != _root && currNode->color != tree::Node<tree::RedBlackTree<T>>::Black
                && currNode->parent->color == tree::Node<tree::RedBlackTree<T>>::Red) {
            currParent = currNode->parent;
            currGrandparent = currNode->parent->parent;

            //parent of current node is left child
            if (currParent == currGrandparent->left) {
                Node<RedBlackTree<T>>* currUncle = currGrandparent->right;

                //uncle is Red: do only recoloring
                if (currUncle != nullptr && currUncle->color == tree::Node<tree::RedBlackTree<T>>::Red) {
                    currGrandparent->color = tree::Node<tree::RedBlackTree<T>>::Red;
                    currParent->color = tree::Node<tree::RedBlackTree<T>>::Black;
                    currUncle->color = tree::Node<tree::RedBlackTree<T>>::Black;
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
                    tree::utils::swapColors(currParent, currGrandparent);
                    currNode = currParent;
                }
            } else { //parent of current node is right child
                Node<RedBlackTree<T>>* currUncle = currGrandparent->left;

                //uncle is Red: do only recoloring
                if (currUncle != nullptr && currUncle->color == tree::Node<tree::RedBlackTree<T>>::Red) {
                    currGrandparent->color = tree::Node<tree::RedBlackTree<T>>::Red;
                    currParent->color = tree::Node<tree::RedBlackTree<T>>::Black;
                    currUncle->color = tree::Node<tree::RedBlackTree<T>>::Black;
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
                    tree::utils::swapColors(currParent, currGrandparent);
                    currNode = currParent;
                }
            }
        }

        (_root)->color = tree::Node<tree::RedBlackTree<T>>::Black;
    }


        template <typename T>
    void RedBlackTree<T>::fixBothBlack(Node<RedBlackTree<T>>* node) {
        if (node == _root) { // Reached root
            return;
        }

        Node<RedBlackTree<T>>* sibling = tree::utils::sibling(node);
        Node<RedBlackTree<T>>* parent = (node->parent);
        if (sibling == nullptr) {
            // No sibiling, double Black pushed up
            fixBothBlack(parent);
        } else if (sibling->color == tree::Node<tree::RedBlackTree<T>>::Red) {
            // Sibling Red
            parent->color = tree::Node<tree::RedBlackTree<T>>::Red;
            sibling->color = tree::Node<tree::RedBlackTree<T>>::Black;
            if (tree::utils::isLeftSon(sibling)) {
                // left case
                rotateRight(parent);
            } else {
                // right case
                rotateLeft(parent);
            }
            fixBothBlack(node);
        } else {
            // Sibling Black
            if (tree::utils::hasRedChild(sibling)) {
                // at least 1 Red children
                if (sibling->left != nullptr && sibling->left->color == tree::Node<tree::RedBlackTree<T>>::Red) {
                    if (tree::utils::isLeftSon(sibling)) {
                        // left left
                        (sibling->left)->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(parent);
                    } else {
                        // right left
                        (sibling->left)->color = parent->color;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                } else {
                    if (tree::utils::isLeftSon(sibling)) {
                        // left right
                        (sibling->right)->color = parent->color;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    } else {
                        // right right
                        (sibling->right)->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(parent);
                    }
                }
                parent->color = tree::Node<tree::RedBlackTree<T>>::Black;
            } else {
                // 2 Black children
                sibling->color = tree::Node<tree::RedBlackTree<T>>::Red;
                if (parent->color == tree::Node<tree::RedBlackTree<T>>::Black)
                    fixBothBlack(parent);
                else
                    parent->color = tree::Node<tree::RedBlackTree<T>>::Black;
            }
        }
    }

    template <typename T>
    Node<RedBlackTree<T>>* RedBlackTree<T>::simpleReplace(Node<RedBlackTree<T>>* node) {
        // when node have 2 children
        if (node->left != nullptr && node->right != nullptr) {
            return tree::utils::min(node->right);
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
    void RedBlackTree<T>::eraseNode(Node<RedBlackTree<T>>* nodeToDelete) {
        Node<RedBlackTree<T>>* nodeToReplace = simpleReplace(nodeToDelete);

        // True when u and v are both Black
        bool bothBlack = ((nodeToReplace == nullptr
                           ||nodeToReplace->color == tree::Node<tree::RedBlackTree<T>>::Black)
                          && (nodeToDelete->color == tree::Node<tree::RedBlackTree<T>>::Black));
        Node<RedBlackTree<T>>* parent = nodeToDelete->parent;

        if (nodeToReplace == nullptr) {
            // u is NULL therefore v is leaf
            if (nodeToDelete == _root) {
                // v is _root, making _root null
                _root = nullptr;
            } else {
                if (bothBlack) {
                    // u and v both Black
                    // v is leaf, fix double Black at v
                    fixBothBlack(nodeToDelete);
                } else {
                    // u or v is Red
                    if (tree::utils::sibling(nodeToDelete) != nullptr)
                        // sibling is not null, make it Red"
                        tree::utils::sibling(nodeToDelete)->color = tree::Node<tree::RedBlackTree<T>>::Red;
                }

                // delete v from the tree

                if (tree::utils::isLeftSon(nodeToDelete)) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }
            nodeToDelete->left = nullptr;
            nodeToDelete->right = nullptr;
            delete nodeToDelete;
            return;
        }

        if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
            // nodeToDelete has 1 child
            if (nodeToDelete == _root) {
                // v is _root, assign the value of u to v, and delete u
                nodeToDelete->data = nodeToReplace->data;
                nodeToDelete->left = nullptr;
                nodeToDelete->right = nullptr;
                nodeToReplace->left = nullptr;
                nodeToReplace->right = nullptr;
                delete nodeToReplace;
            } else {
                // Detach v from tree and move u up
                if (tree::utils::isLeftSon(nodeToDelete)) {
                    parent->left = nodeToReplace;
                } else {
                    parent->right = nodeToReplace;
                }
                nodeToDelete->left = nullptr;
                nodeToDelete->right = nullptr;
                delete nodeToDelete;
                nodeToReplace->parent = parent;
                if (bothBlack) {
                    // u and v both Black, fix double Black at u
                    fixBothBlack(nodeToReplace);
                } else {
                    // u or v Red, color u Black
                    nodeToReplace->color = tree::Node<tree::RedBlackTree<T>>::Black;
                }
            }
            return;
        }

        // v has 2 children, swap values with successor and recurse
        tree::utils::swapData(nodeToReplace, nodeToDelete);
        eraseNode(nodeToReplace);
    }

    template <typename T>
    template <typename Iter>
    RedBlackTree<T>::RedBlackTree (Iter begin, Iter end)
    {
        _root = nullptr;
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    template <typename T>
    RedBlackTree<T>::RedBlackTree (std::initializer_list<T> elems) {
        for (const auto& elem : elems) {
            insert(elem);
        }
    }

    template <typename T>
    auto RedBlackTree<T>::simpleInsert(Node<RedBlackTree<T>>* currNode, Node<RedBlackTree<T>>* inputNode) { //insert like in ordinary BST
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
    void RedBlackTree<T>::insert(const T& _data) {
        auto inputNode = new Node<RedBlackTree<T>>{_data};
        _root = simpleInsert(_root, inputNode);

        fixTree(inputNode);
        _size++;
    }

    template <typename T>
    void RedBlackTree<T>::erase(const T& _data) {
        if (_root == nullptr) {
            return;
        }

        Node<RedBlackTree<T>>* nodeToDelete = tree::utils::find<RedBlackTree>(_root,  _data);

        if (nodeToDelete == nullptr) {
            return;
        }

        eraseNode(nodeToDelete);
        _size--;
    }

}