#pragma once

namespace tree::detail {

    template <typename BinaryTreeNode>
    bool isLeftSon (BinaryTreeNode* node) noexcept {
        if (!node->parent) {
            return false;
        }
        if (!node->parent->left) {
            return false;
        }
        return node->parent->left == node;
    }

    template <typename BinaryTreeNode>
    bool isRightSon (BinaryTreeNode* node) noexcept {
        if (!node->parent) {
            return false;
        }
        if (!node->parent->right) {
            return false;
        }
        return node->parent->right == node;
    }

    template <typename BinaryTreeNode, typename T>
    auto find (BinaryTreeNode* node, const T& elem) noexcept -> BinaryTreeNode*
    {
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

    template <typename BinaryTreeNode>
    auto min (BinaryTreeNode* node) noexcept -> BinaryTreeNode*
    {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    template <typename BinaryTreeNode>
    auto max (BinaryTreeNode* node) noexcept -> BinaryTreeNode*
    {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    /**
     *  @brief Assign var to value, setting var's parent new_parent
     */
    template <typename BinaryTreeNode>
    void set (BinaryTreeNode*& var, BinaryTreeNode* value, BinaryTreeNode* new_parent = nullptr) {
        var = value;
        if (var) {
            var->parent = new_parent;
        }
    }

    template <typename BinaryTreeNode>
    void deleteTree (BinaryTreeNode* node) {
        if (!node) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    template <typename BinaryTreeNode>
    BinaryTreeNode* sibling(BinaryTreeNode* node) {
        if (node->parent == nullptr) {
            return nullptr;
        }

        if (isLeftSon(node)) {
            return node->parent->right;
        }

        return node->parent->left;
    }

    template <typename BinaryTreeNode>
    void swapData(BinaryTreeNode* firstNode, BinaryTreeNode* secondNode) {
        auto temp = firstNode->data;
        firstNode->data = secondNode->data;
        secondNode->data = temp;
    }
}
