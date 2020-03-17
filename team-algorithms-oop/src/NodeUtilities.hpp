#pragma once

#include <NodeBase.hpp>

#include <vector>

/**
 *   @brief Set of function to work with binary tree nodes
 */
namespace tree::utils {

    template <typename TreeType, typename T>
    auto find (Node<TreeType>* node, const T& elem) noexcept -> Node<TreeType>* {

        while (node) {
            if (node->data > elem) {
                node = node->left;
            }
            else if (node->data < elem) {
                node = node->right;
            }
            else {
                return node;
            }
        }
        return nullptr;
    }

    template <typename TreeType>
    bool isLeftSon (Node<TreeType>* node) noexcept {
        if (!node->parent) {
            return false;
        }
        if (!node->parent->left) {
            return false;
        }
        return node->parent->left == node;
    }

    template <typename TreeType>
    bool isRightSon (Node<TreeType>* node) noexcept {
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
    template <typename TreeType>
    auto min (Node<TreeType>* node) noexcept -> Node<TreeType>* {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    /**
    *  @return Node with max element in subtree
    */
    template <typename TreeType>
    auto max (Node<TreeType>* node) noexcept -> Node<TreeType>* {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    /**
     *   @return Deep copy of node
     */
    template <typename TreeType>
    auto clone (Node<TreeType>* node) -> Node<TreeType>* {
        // TODO Yano4ka rabotat'
        return nullptr;
    }

    /**
     *  @brief Simple insertion in BST node without parent info, non-recursive approach
     */
    template <typename TreeType>
    auto insert (Node<TreeType>* node, Node<TreeType>* to_insert) -> Node<TreeType>*{

        const auto& key = to_insert->data;

        while (true) {
            if (node->data > key) {
                if (!node->left) {
                    node->left = to_insert;
                }
                node = node->left;
            }
            else if (node->data < key) {
                if (!node->right) {
                    node->right = to_insert;
                }
                node = node->right;
            }
            else
                return node;
        }
    }

    /**
     *  @brief Simple insertion in BST node with parent info, non-recursive approach
     */
    template <typename TreeType>
    auto insertWithParent (Node<TreeType>* node, Node<TreeType>* to_insert) -> Node<TreeType>* {

        const auto& key = to_insert->data;

        while (true) {
            if (node->data > key) {
                if (!node->left) {
                    node->left = to_insert;
                    node->left->parent = node;
                }
                node = node->left;
            }
            else if (node->data < key) {
                if (!node->right) {
                    node->right = to_insert;
                    node->right->parent = node;
                }
                node = node->right;
            }
            else
                return node;
        }
    }

    template <typename TreeType>
    void deleteTree (Node<TreeType>* node) {
        if (node->left) {
            deleteTree(node->left);
        }
        if (node->right)
            deleteTree(node->right);

        delete node;
    }

    /**
     *  @brief Assign var to value, setting var's parent new_parent
     */
    template <typename TreeType>
    void set (Node<TreeType>*& var, Node<TreeType>* value, Node<TreeType>* new_parent = nullptr) {
        var = value;
        if (var) {
            var->parent = new_parent;
        }
    }

    /**
     *   @brief Computes std::vector of all nodes of subtree 'node' in incresing order
     */
    template <typename TreeType>
    void makeOrderedSequence (Node<TreeType>* node, std::vector<Node<TreeType>*>& nodes) {
        if (node->left) {
            makeOrderedSequence(node->left, nodes);
        }
        if (node->right) {
            makeOrderedSequence(node->right, nodes);
        }
        nodes.push_back(node);
    }

    template <typename TreeType>
    void rightRotate (Node<TreeType>* node) {
        assert(isLeftSon(node));

        set(node->parent->left, node->right, node->parent);
        set(node->right, node->parent, node);
    }

    template <typename TreeType>
    void leftRotate (Node<TreeType>* node) {
        assert(isRightSon(node));

        set(node->parent->right, node->left, node->parent);
        set(node->left, node->parent, node);
    }
}


