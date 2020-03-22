#pragma once

#include "RBNodeUtilities.hpp"

namespace lab::tree::rbutils {

    /**
     * @brief Implementation of algorithm for node deletion and restore RBTree properties after deletion
     */
    template <typename T, typename Compare>
    class DeletionFixRBTRee {
    private:
        using RBNode = Node<RedBlackTree<T, Compare>>;
        RBNode* root;
        RBNode* doubleBlackNode; ///shortly DBN everywhere under
        RBNode* DBNSibling;
        RBNode* DBNParent;

        RBNode* nodeToDelete;
        RBNode* nodeToReplace;
        RBNode* parentNodeToDelete;
        bool bothBlack;

        void redSiblingCase() {
            DBNParent->color = RBNode::Red;
            DBNSibling->color = RBNode::Black;
            if (bstutils::isLeftSon(DBNSibling)) {
                /// left case
                rotateRight(root, DBNParent);
            } else {
                /// right case
                rotateLeft(root, DBNParent);
            }
            fixBothBlack();
        }

        void siblingHasLeftRedChild() {
            if (bstutils::isLeftSon(DBNSibling)) {
                /// left left
                (DBNSibling->left)->color = DBNSibling->color;
                DBNSibling->color = DBNParent->color;
                rotateRight(root, DBNParent);
            } else {
                /// right left
                (DBNSibling->left)->color = DBNParent->color;
                rotateRight(root, DBNSibling);
                rotateLeft(root, DBNParent);
            }
        }

        void siblingHasRightRedChild() {
            if (bstutils::isLeftSon(DBNSibling)) {
                /// left right
                (DBNSibling->right)->color = DBNParent->color;
                rotateLeft(root, DBNSibling);
                rotateRight(root, DBNParent);
            } else {
                /// right right
                (DBNSibling->right)->color = DBNSibling->color;
                DBNSibling->color = DBNParent->color;
                rotateLeft(root, DBNParent);
            }
        }

        void siblingHasOnlyBlackChildren() {
            DBNSibling->color = RBNode::Red;
            if (DBNParent->color == RBNode::Black) {
                doubleBlackNode = DBNParent;
                fixBothBlack();
            }
            else {
                DBNParent->color = RBNode::Black;
            }
        }

        void blackSiblingCase() {
            if (hasRedChild(DBNSibling)) {
                /// at least 1 Red child
                if (DBNSibling->left != nullptr && DBNSibling->left->color == RBNode::Red) {
                    siblingHasLeftRedChild();
                } else {
                    siblingHasRightRedChild();
                }
                DBNParent->color = RBNode::Black;
            } else {
                siblingHasOnlyBlackChildren();
            }
        }

        /**
         * @brief Restoring balance of the tree when deleted node and replacement node are both black
         *          by rotation and recoloring
         */
        void fixBothBlack() {
            if (doubleBlackNode == root) { // Reached root
                return;
            }

            DBNSibling = bstutils::sibling(doubleBlackNode);
            DBNParent = doubleBlackNode->parent;

            if (DBNSibling == nullptr) {
                // No sibling, double Black pushed up
                doubleBlackNode = DBNParent;
                fixBothBlack();
            } else if (DBNSibling->color == RBNode::Red) {
                redSiblingCase();
            } else {
                blackSiblingCase();
            }
        }

        void nodeToDeleteIsLeaf() {
                if (bothBlack) {
                    doubleBlackNode = nodeToDelete;
                    fixBothBlack();
                } else {
                    if (bstutils::sibling(nodeToDelete) != nullptr)
                        // sibling is not null, make it Red
                        bstutils::sibling(nodeToDelete)->color = RBNode::Red;
                }

                // delete node from the tree
                if (bstutils::isLeftSon(nodeToDelete)) {
                    parentNodeToDelete->left = nullptr;
                } else {
                    parentNodeToDelete->right = nullptr;
                }
            delete nodeToDelete;
        }

        void nodeToDeleteHasOnlyOneChild() {
            if (nodeToDelete == root) {
                nodeToDelete->data = nodeToReplace->data;
                delete nodeToReplace;
            } else {
                /// Detach nodeToDelete from tree and move nodeToReplace up
                if (bstutils::isLeftSon(nodeToDelete)) {
                    parentNodeToDelete->left = nodeToReplace;
                } else {
                    parentNodeToDelete->right = nodeToReplace;
                }
                delete nodeToDelete;

                nodeToReplace->parent = parentNodeToDelete;
                if (bothBlack) {
                    doubleBlackNode = nodeToReplace;
                    fixBothBlack();
                } else {
                    nodeToReplace->color = RBNode::Black;
                }
            }
        }

        /**
         * @brief Find replacement for the node that we want to delete
         * and call functions to replace and delete it for all possible variant
         */
        void eraseNode() {
            nodeToReplace = bstutils::findReplacement(nodeToDelete);
            parentNodeToDelete = nodeToDelete->parent;
            bothBlack = ((nodeToReplace == nullptr
                          || nodeToReplace->color == RBNode::Black)
                         && (nodeToDelete->color == RBNode::Black));

            if (nodeToReplace == nullptr) {
                nodeToDeleteIsLeaf();
            } else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
                nodeToDeleteHasOnlyOneChild();
            } else { // nodeToDelete has 2 children, swap values with replacement node and recurse
                bstutils::swapData(nodeToReplace, nodeToDelete);
                nodeToDelete = nodeToReplace;
                eraseNode();
            }
        }

    public:
        DeletionFixRBTRee(RBNode*& _root, RBNode* _nodeToDelete)
                : root(_root), nodeToDelete(_nodeToDelete)
        {
            eraseNode();
            _root = root;
        }
    };
}
