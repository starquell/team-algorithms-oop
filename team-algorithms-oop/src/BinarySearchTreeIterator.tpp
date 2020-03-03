#pragma once

#include "NodeTools.hpp"

namespace trees {

    template <typename BSTNode, typename T>
    bool BinarySearchTreeIterator<BSTNode, T>::operator!= (
            const BinarySearchTreeIterator<BSTNode, T>& other) noexcept
    {
        return m_curr != other.m_curr;
    }

    template <typename BSTNode, typename T>
    bool BinarySearchTreeIterator<BSTNode, T>::operator== (
            const BinarySearchTreeIterator<BSTNode, T>& other) noexcept
    {
        return m_curr == other.m_curr;
    }

    template <typename BSTNode, typename T>
    auto BinarySearchTreeIterator<BSTNode, T>::operator++() noexcept
            -> BinarySearchTreeIterator<BSTNode, T>&
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
            if (detail::isLeftSon(m_curr)) {
                m_curr = m_curr->parent;
                return *this;
            }
            m_curr = m_curr->parent;
        }
    }

    template <typename BSTNode, typename T>
    auto BinarySearchTreeIterator<BSTNode, T>::operator*() noexcept
            -> const T&
    {
        return m_curr->data;
    }

    template <typename BSTNode, typename T>
    BinarySearchTreeIterator<BSTNode, T>::BinarySearchTreeIterator (BSTNode* root) noexcept
            : m_curr(root)
    {}

    template <typename BSTNode, typename T>
    auto BinarySearchTreeIterator<BSTNode, T>::operator+ (int n) const noexcept
            -> BinarySearchTreeIterator<BSTNode, T>
    {
        BinarySearchTreeIterator<BSTNode, T> temp(*this);
        for (int i = 0; i < n; ++i) {
            ++temp;
        }
        return temp;
    }
}
