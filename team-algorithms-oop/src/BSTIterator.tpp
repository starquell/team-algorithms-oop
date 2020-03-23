#pragma once

#include <NodeUtilities.hpp>

namespace lab::tree {

    template <typename Tree>
    bool BSTIterator<Tree>::operator!= (const BSTIterator& other) noexcept
    {
        return m_curr != other.m_curr;
    }

    template <typename Tree>
    bool BSTIterator<Tree>::operator== (const BSTIterator& other) noexcept
    {
        return m_curr == other.m_curr;
    }

    template <typename Tree>
    auto BSTIterator<Tree>::operator++() noexcept -> BSTIterator<Tree>&
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
            if (bstutils::isLeftSon(m_curr)) {
                m_curr = m_curr->parent;
                return *this;
            }
            m_curr = m_curr->parent;
        }
    }

    template <typename Tree>
    auto BSTIterator<Tree>::operator*() -> const BSTIterator<Tree>::value_type&
    {
        if (!m_curr) {
            throw std::out_of_range("No data under iterator.");
        }
        return m_curr->data;
    }

    template <typename Tree>
    BSTIterator<Tree>::BSTIterator (Node<Tree>* root) noexcept
            : m_curr(root)
    {}

    template <typename Tree>
    auto BSTIterator<Tree>::operator+ (int n) const noexcept -> BSTIterator<Tree>
    {
        BSTIterator<Tree> temp(*this);
        for (int i = 0; i < n; ++i) {
            ++temp;
        }
        return temp;
    }

    template <typename Tree>
    BSTIterator<Tree>::operator bool () const noexcept {
        return m_curr;
    }
}