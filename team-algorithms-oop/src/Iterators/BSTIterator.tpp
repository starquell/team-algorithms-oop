#pragma once

#include <NodeUtilities.hpp>

namespace tree {

    template <typename T, typename TreeNode>
    bool BSTIterator<T, TreeNode>::operator!= (
            const BSTIterator<T, TreeNode>& other) noexcept
    {
        return m_curr != other.m_curr;
    }

    template <typename T, typename TreeNode>
    bool BSTIterator<T, TreeNode>::operator== (
            const BSTIterator<T, TreeNode>& other) noexcept
    {
        return m_curr == other.m_curr;
    }

    template <typename T, typename TreeNode>
    auto BSTIterator<T, TreeNode>::operator++() noexcept
            -> BSTIterator<T, TreeNode>&
    {
        if (m_curr->right) {
            auto s = m_curr->right->data;
            auto temp = m_curr->right;
            while (temp->left) {
                temp = temp->left;
            }
            m_curr = temp;
            return *this;
        }

        while (true) {
            if (!m_curr->parent) {
                m_curr = nullptr;
                return *this;
            }
            if (utils::isLeftSon(m_curr)) {
                m_curr = m_curr->parent;
                return *this;
            }
            m_curr = m_curr->parent;
        }
    }

    template <typename T, typename TreeNode>
    auto BSTIterator<T, TreeNode>::operator*() noexcept -> const T&
    {
        return m_curr->data;
    }

    template <typename T, typename TreeNode>
    BSTIterator<T, TreeNode>::BSTIterator (TreeNode* root) noexcept
            : m_curr(root)
    {}

    template <typename T, typename TreeNode>
    auto BSTIterator<T, TreeNode>::operator+ (int n) const noexcept
            -> BSTIterator<T, TreeNode>
    {
        BSTIterator<T, TreeNode> temp(*this);
        for (int i = 0; i < n; ++i) {
            ++temp;
        }
        return temp;
    }

    template <typename T, typename TreeNode>
    BSTIterator<T, TreeNode>::operator bool () const noexcept {
        return m_curr;
    }
}