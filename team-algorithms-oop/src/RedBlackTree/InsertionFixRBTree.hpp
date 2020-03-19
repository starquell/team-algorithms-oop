#pragma once

#include "RBNodeUtilities.hpp"

namespace tree::utils {

    template <typename T>
    class InsertionFixRBTree {
    private:
        Node<RedBlackTree<T>>* currParent = nullptr;
        Node<RedBlackTree<T>>* currGrandparent = nullptr;
        Node<RedBlackTree<T>>* currNode;
        Node<RedBlackTree<T>>* currUncle = nullptr;
        Node<RedBlackTree<T>>* root;

        void treeFixingRecoloringCase() {
            currGrandparent->color = Node<RedBlackTree<T>>::Red;
            currParent->color = Node<RedBlackTree<T>>::Black;
            currUncle->color = Node<RedBlackTree<T>>::Black;
            currNode = currGrandparent;
        }

        void treeFixingLeftChildCase() {
            currUncle = currGrandparent->right;

            //uncle is Red: do only recoloring
            if (currUncle != nullptr && currUncle->color == Node<RedBlackTree<T>>::Red) {
                treeFixingRecoloringCase();
            } else {
                //current node is right child: left rotation
                if (currNode == currParent->right) {
                    utils::rotateLeft(root, currParent);
                    currNode = currParent;
                    currParent = currNode->parent;
                }

                //current node is left child: right rotation
                utils::rotateRight(root, currGrandparent);
                utils::swapColors(currParent, currGrandparent);
                currNode = currParent;
            }
        }

        void treeFixingRightChildCase() {
            currUncle = currGrandparent->left;

            //uncle is Red: do only recoloring
            if (currUncle != nullptr && currUncle->color == Node<RedBlackTree<T>>::Red) {
                treeFixingRecoloringCase();
            } else {
                //current node is left child: right rotation
                if (currNode == currParent->left) {
                    utils::rotateRight(root, currParent);
                    currNode = currParent;
                    currParent = currNode->parent;
                }

                //current node is right child: left rotation
                utils::rotateLeft(root, currGrandparent);
                utils::swapColors(currParent, currGrandparent);
                currNode = currParent;
            }
        }

    public:
        InsertionFixRBTree(Node<RedBlackTree<T>>*& _root, Node<RedBlackTree<T>>*& _currNode)
               : currNode(_currNode), root(_root)
        {
            while (currNode != root && currNode->color != tree::Node<tree::RedBlackTree<T>>::Black
                   && currNode->parent->color == tree::Node<tree::RedBlackTree<T>>::Red) {
                currParent = currNode->parent;
                currGrandparent = currNode->parent->parent;

                /// parent of current node is left child
                if (currParent == currGrandparent->left) {
                    treeFixingLeftChildCase();
                }else { ///parent of current node is right child
                    treeFixingRightChildCase();
                }
            }
            _root = root;
            _root->color = tree::Node<tree::RedBlackTree<T>>::Black;
        }
    };
}
