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
    *  @brief Copy field of toCopy node to toPaste node, but without fields-pointers
    */
    template <typename TreeType>
    void copyNodeData (Node<TreeType>* toCopy, Node<TreeType>* toPaste) {
        toPaste->data = toCopy->data;
    }

    /**
     *   @return Deep copy of node
     */
    template <typename TreeType>
    auto clone (Node<TreeType>* node, Node<TreeType>* parentNode = nullptr) -> Node<TreeType>* {
        if (!node) {
            return nullptr;
        }

        auto newNode = new Node<TreeType>();
        copyNodeData(node, newNode);
        newNode->parent = parentNode;
        newNode->left = clone(node->left, newNode);
        newNode->right = clone(node->right, newNode);

        return newNode;
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
     *   @brief Computes std::vector of all nodes of subtree 'node' in increasing order
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

    /**
     * @param node left child of current parent after rotation becomes parent
     */
    template <typename TreeType>
    void rightRotate (Node<TreeType>* node) {
        assert(isLeftSon(node));

        set(node->parent->left, node->right, node->parent);
        set(node->right, node->parent, node);
    }

    /**
     * @param node right child of current parent after rotation becomes parent
     */
    template <typename TreeType>
    void leftRotate (Node<TreeType>* node) {
        assert(isRightSon(node));

        set(node->parent->right, node->left, node->parent);
        set(node->left, node->parent, node);
    }

    /**
     * @return another child of node parent and nullptr if there is no parent
     */
    template <typename TreeType>
    Node<TreeType>* sibling(Node<TreeType>* node) {
        if (node->parent == nullptr) {
            return nullptr;
        }

        if (isLeftSon(node)) {
            return node->parent->right;
        }

        return node->parent->left;
    }

    template <typename TreeType>
    void swapData(Node<TreeType>* firstNode, Node<TreeType>* secondNode) {
        auto temp = firstNode->data;
        firstNode->data = secondNode->data;
        secondNode->data = temp;
    }

    /**
     * @brief recurrsively erase whole subtree strating from toDelete node
     */
    template <typename TreeType>
    void eraseSubTree (Node<TreeType>* toDelete) {
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
     * @param node node for which we should find replacement node
     * @return node that should replace given node
     *
     */
    template <typename TreeType>
    Node<TreeType>* findReplacement(Node<TreeType>* node) {
        // when node have 2 children
        if (node->left != nullptr && node->right != nullptr) {
            return utils::min(node->right);
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


