#pragma once

#include <NodeBase.hpp>

#include <vector>
#include <cassert>


/**
 *   @brief Set of function to work with binary tree nodes
 */
namespace lab::tree::bstutils {

    /**
     *  @brief Returns node with key elem in subtree node
     */
    template <typename Tree, typename T, typename Compare>
    auto find (Node<Tree>* node,
               const T& elem,
               const Compare& comp) noexcept -> Node<Tree>*
    {
        while (node) {
            if (node->data == elem) {
                return node;
            }
            else if (comp(node->data, elem)) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        return nullptr;
    }

    template <typename Tree>
    bool isLeftSon (Node<Tree>* node) noexcept {
        if (!node->parent) {
            return false;
        }
        if (!node->parent->left) {
            return false;
        }
        return node->parent->left == node;
    }

    template <typename Tree>
    bool isRightSon (Node<Tree>* node) noexcept {
        if (!node->parent) {
            return false;
        }
        if (!node->parent->right) {
            return false;
        }
        return node->parent->right == node;
    }

    /**
     *  @return Node with min element in subtree
     */
    template <typename Tree>
    auto min (Node<Tree>* node) noexcept -> Node<Tree>* {
        if (!node) {
            return nullptr;
        }
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    /**
    *  @return Node with max element in subtree
    */
    template <typename Tree>
    auto max (Node<Tree>* node) noexcept -> Node<Tree>* {
        if (!node) {
            return nullptr;
        }
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    /**
    *  @brief Copy field of toCopy node to toPaste node, but without fields-pointers
    */
    template <typename Tree>
    void copyNodeData (Node<Tree>* toCopy, Node<Tree>* toPaste) {
        toPaste->data = toCopy->data;
    }

    /**
     *   @return Deep copy of node
     */
    template <typename Tree>
    auto clone (Node<Tree>* node, Node<Tree>* parentNode = nullptr) -> Node<Tree>* {
        if (!node) {
            return nullptr;
        }

        auto newNode = new Node<Tree>();
        copyNodeData(node, newNode);
        newNode->parent = parentNode;
        newNode->left = clone(node->left, newNode);
        newNode->right = clone(node->right, newNode);

        return newNode;
    }

    /**
     *  @brief Simple insertion in BST node without parent info, non-recursive approach
     */
    template <typename Tree, typename Compare>
    auto insert (Node<Tree>* node,
                 Node<Tree>* to_insert,
                 const Compare& comp) -> Node<Tree>*
     {

        const auto& key = to_insert->data;

        while (true) {
            if (node->data == key) {
                return node;
            }
            else if (comp(node->data, key)) {
                if (!node->right) {
                    node->right = to_insert;
                }
                node = node->right;
            }
            else {
                if (!node->left) {
                    node->left = to_insert;
                }
                node = node->left;
            }
        }
    }

    /**
     *  @brief Simple insertion in BST node with parent info, non-recursive approach
     */
    template <typename Tree, typename Compare>
    auto insertWithParent (Node<Tree>* node,
                           Node<Tree>* to_insert,
                           const Compare& comp) -> Node<Tree>* {

        const auto& key = to_insert->data;

        while (true) {
            if (node->data == key) {
                return node;
            }
            else if (comp(node->data, key)) {
                if (!node->right) {
                    node->right = to_insert;
                    node->right->parent = node;
                }
                node = node->right;
            }
            else {
                if (!node->left) {
                    node->left = to_insert;
                    node->left->parent = node;
                }
                node = node->left;
            }
        }
    }

    /**
     *  @brief Assign var to value, setting var's parent new_parent
     */
    template <typename Tree>
    void set (Node<Tree>*& var, Node<Tree>* value, Node<Tree>* new_parent = nullptr) {
        var = value;
        if (var) {
            var->parent = new_parent;
        }
    }

    /**
     *   @brief Computes std::vector of all nodes of subtree 'node' in increasing order
     */
    template <typename Tree>
    void makeOrderedSequence (Node<Tree>* node, std::vector<Node<Tree>*>& nodes) {
        if (node->left) {
            makeOrderedSequence(node->left, nodes);
        }
        if (node->right) {
            makeOrderedSequence(node->right, nodes);
        }
        nodes.push_back(node);
    }

    /**
     * @param node left child of current parent after rotation becomes parent
     */
    template <typename Tree>
    void rightRotate (Node<Tree>* node) {
        assert(isLeftSon(node));

        set(node->parent->left, node->right, node->parent);
        set(node->right, node->parent, node);
    }

    /**
     * @param node right child of current parent after rotation becomes parent
     */
    template <typename Tree>
    void leftRotate (Node<Tree>* node) {
        assert(isRightSon(node));

        set(node->parent->right, node->left, node->parent);
        set(node->left, node->parent, node);
    }

    /**
     * @return Another child of node parent and nullptr if there is no parent
     */
    template <typename Tree>
    Node<Tree>* sibling(Node<Tree>* node) {
        if (node->parent == nullptr) {
            return nullptr;
        }

        if (isLeftSon(node)) {
            return node->parent->right;
        }

        return node->parent->left;
    }

    template <typename Tree>
    void swapData(Node<Tree>* firstNode, Node<Tree>* secondNode) {
        auto temp = firstNode->data;
        firstNode->data = secondNode->data;
        secondNode->data = temp;
    }

    /**
     * @brief Recurrsively erase whole subtree strating from toDelete node
     */
    template <typename Tree>
    void eraseSubTree (Node<Tree>* toDelete) {
        if (toDelete == nullptr) {
            return;
        }

        eraseSubTree(toDelete->left);
        eraseSubTree(toDelete->right);

        delete toDelete;
    }

    /**
     *
     * @brief Find the closest node which can be put in place of given node
     * @param node Node for which we should find replacement node
     * @return Node that should replace given node
     *
     */
    template <typename Tree>
    Node<Tree>* findReplacement(Node<Tree>* node) {
        // when node have 2 children
        if (node->left != nullptr && node->right != nullptr) {
            return min(node->right);
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
}


