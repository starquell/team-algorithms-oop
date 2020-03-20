#pragma once

#include "RBNodeUtilities.hpp"

namespace tree::rbutils {

    /**
     * @brief Implementation of algorithm for node deletion and restore RBTree properties after deletion
     */
    template <typename T>
    class DeletionFixRBTRee {
    private:
        Node<RedBlackTree<T>>* root;
        Node<RedBlackTree<T>>* doubleBlackNode; ///shortly DBN everywhere under
        Node<RedBlackTree<T>>* DBNSibling;
        Node<RedBlackTree<T>>* DBNParent;

        Node<RedBlackTree<T>>* nodeToDelete;
        Node<RedBlackTree<T>>* nodeToReplace;
        Node<RedBlackTree<T>>* parentNodeToDelete;
        bool bothBlack;

        void redSiblingCase() {
            DBNParent->color = Node<RedBlackTree<T>>::Red;
            DBNSibling->color = Node<RedBlackTree<T>>::Black;
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
            DBNSibling->color = Node<RedBlackTree<T>>::Red;
            if (DBNParent->color == Node<RedBlackTree<T>>::Black) {
                doubleBlackNode = DBNParent;
                fixBothBlack();
            }
            else {
                DBNParent->color = Node<RedBlackTree<T>>::Black;
            }
        }

        void blackSiblingCase() {
            if (hasRedChild(DBNSibling)) {
                /// at least 1 Red child
                if (DBNSibling->left != nullptr && DBNSibling->left->color == Node<RedBlackTree<T>>::Red) {
                    siblingHasLeftRedChild();
                } else {
                    siblingHasRightRedChild();
                }
                DBNParent->color = Node<RedBlackTree<T>>::Black;
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
            } else if (DBNSibling->color == Node<RedBlackTree<T>>::Red) {
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
                        bstutils::sibling(nodeToDelete)->color = Node<RedBlackTree<T>>::Red;
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
                    nodeToReplace->color = Node<RedBlackTree<T>>::Black;
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
                          || nodeToReplace->color == Node<RedBlackTree<T>>::Black)
                         && (nodeToDelete->color == Node<RedBlackTree<T>>::Black));

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
        DeletionFixRBTRee(Node<RedBlackTree<T>>*& _root, Node<RedBlackTree<T>>* _nodeToDelete)
                : root(_root), nodeToDelete(_nodeToDelete)
        {
            eraseNode();
            _root = root;
        }
    };
}
