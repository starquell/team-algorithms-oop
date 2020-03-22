#pragma once

#include "RBNodeUtilities.hpp"

namespace lab::tree::rbutils {

    /**
     * @brief Implementation of algorithm that restore RBTree properties after insertion
     */
    template <typename T, typename Compare>
    class InsertionFixRBTree {
    private:
        using RBNode = Node<RedBlackTree<T, Compare>>;
        RBNode* currParent = nullptr;
        RBNode* currGrandparent = nullptr;
        RBNode* currNode;
        RBNode* currUncle = nullptr;
        RBNode* root;

        void treeFixingRecoloringCase() {
            currGrandparent->color = RBNode::Red;
            currParent->color = RBNode::Black;
            currUncle->color = RBNode::Black;
            currNode = currGrandparent;
        }

        void treeFixingLeftChildCase() {
            currUncle = currGrandparent->right;

            //uncle is Red: do only recoloring
            if (currUncle != nullptr && currUncle->color == RBNode::Red) {
                treeFixingRecoloringCase();
            } else {
                //current node is right child: left rotation
                if (currNode == currParent->right) {
                    rotateLeft(root, currParent);
                    currNode = currParent;
                    currParent = currNode->parent;
                }

                //current node is left child: right rotation
                rotateRight(root, currGrandparent);
                swapColors(currParent, currGrandparent);
                currNode = currParent;
            }
        }

        void treeFixingRightChildCase() {
            currUncle = currGrandparent->left;

            //uncle is Red: do only recoloring
            if (currUncle != nullptr && currUncle->color == RBNode::Red) {
                treeFixingRecoloringCase();
            } else {
                //current node is left child: right rotation
                if (currNode == currParent->left) {
                    rotateRight(root, currParent);
                    currNode = currParent;
                    currParent = currNode->parent;
                }

                //current node is right child: left rotation
                rotateLeft(root, currGrandparent);
                swapColors(currParent, currGrandparent);
                currNode = currParent;
            }
        }

    public:
        /**
         * @brief Constructor initialize class fields and call functions for all possible situations of violations
         * @param _currNode - the node that we inserted so there can be violations of properties of RBTree
         */
        InsertionFixRBTree(RBNode*& _root, RBNode*& _currNode)
               : currNode(_currNode), root(_root)
        {
            while (currNode != root && currNode->color != RBNode::Black
                   && currNode->parent->color == RBNode::Red) {
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
            _root->color = RBNode::Black;
        }
    };
}
