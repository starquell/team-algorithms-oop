#pragma once

#include "RBNodeUtilities.hpp"

namespace tree::utils {

    template <typename T>
    class DeletionFixRBTRee {
    private:
        Node<RedBlackTree<T>>* root;
        Node<RedBlackTree<T>>* doubleBlackNode; ///DBN
        Node<RedBlackTree<T>>* DBNSibling;
        Node<RedBlackTree<T>>* DBNParent;

        Node<RedBlackTree<T>>* nodeToDelete;
        Node<RedBlackTree<T>>* nodeToReplace;
        Node<RedBlackTree<T>>* parentNodeToDelete;
        bool bothBlack;

        void redSiblingCase() {
            DBNParent->color = Node<RedBlackTree<T>>::Red;
            DBNSibling->color = Node<RedBlackTree<T>>::Black;
            if (utils::isLeftSon(DBNSibling)) {
                // left case
                utils::rotateRight(root, DBNParent);
            } else {
                // right case
                utils::rotateLeft(root, DBNParent);
            }
            fixBothBlack();
        }

        void siblingHasLeftRedChild() {
            if (utils::isLeftSon(DBNSibling)) {
                // left left
                (DBNSibling->left)->color = DBNSibling->color;
                DBNSibling->color = DBNParent->color;
                utils::rotateRight(root, DBNParent);
            } else {
                // right left
                (DBNSibling->left)->color = DBNParent->color;
                utils::rotateRight(root, DBNSibling);
                utils::rotateLeft(root, DBNParent);
            }
        }

        void siblingHasRightRedChild() {
            if (utils::isLeftSon(DBNSibling)) {
                // left right
                (DBNSibling->right)->color = DBNParent->color;
                utils::rotateLeft(root, DBNSibling);
                utils::rotateRight(root, DBNParent);
            } else {
                // right right
                (DBNSibling->right)->color = DBNSibling->color;
                DBNSibling->color = DBNParent->color;
                utils::rotateLeft(root, DBNParent);
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
            if (utils::hasRedChild(DBNSibling)) {
                // at least 1 Red child
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

        void fixBothBlack() {
            if (doubleBlackNode == root) { // Reached root
                return;
            }

            DBNSibling = utils::sibling(doubleBlackNode);
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
                    if (utils::sibling(nodeToDelete) != nullptr)
                        // sibling is not null, make it Red
                        utils::sibling(nodeToDelete)->color = Node<RedBlackTree<T>>::Red;
                }

                // delete node from the tree
                if (utils::isLeftSon(nodeToDelete)) {
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
                // Detach nodeToDelete from tree and move nodeToReplace up
                if (utils::isLeftSon(nodeToDelete)) {
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

        void eraseNode() {
            nodeToReplace = utils::findReplacement(nodeToDelete);
            parentNodeToDelete = nodeToDelete->parent;
            bothBlack = ((nodeToReplace == nullptr
                          || nodeToReplace->color == Node<RedBlackTree<T>>::Black)
                         && (nodeToDelete->color == Node<RedBlackTree<T>>::Black));

            if (nodeToReplace == nullptr) {
                nodeToDeleteIsLeaf();
            } else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
                nodeToDeleteHasOnlyOneChild();
            } else { // nodeToDelete has 2 children, swap values with replacement node and recurse
                utils::swapData(nodeToReplace, nodeToDelete);
                nodeToDelete = nodeToReplace;
                eraseNode();
            }
        }

    public:
        DeletionFixRBTRee(Node<RedBlackTree<T>>*& _root, Node<RedBlackTree<T>>* _nodeToDelete)
                : root(_root), nodeToDelete(_nodeToDelete) {
            eraseNode();
            _root = root;
        }
    };
}
