#pragma once

#include "SplayTreeAlgorithms.hpp"
#include "../NodeTools.hpp"
#include "SplayTree.hpp"


namespace tree {

    template <typename T>
    auto SplayTree<T>::begin () const -> iterator {
        return iterator {detail::min(m_root)};
    }

    template <typename T>
    auto SplayTree<T>::end () const -> iterator {
        return iterator {nullptr};
    }

    template <typename T>
    auto SplayTree<T>::search (const T& key) noexcept -> bool {
        auto found = detail::find(m_root, key);
        if (found) {
            m_root = detail::splay<T>(found);
            return true;
        }
        else
            return false;
    }

    template <typename T>
    void SplayTree<T>::insert (const T& key) {
        if (!m_root) {
            m_root = new Node {key};
            return;
        }
        auto temp = m_root;
        while (true) {
            if (temp->data > key) {
                if (!temp->left) {
                    temp->left = new Node {key, nullptr,
                                           nullptr, temp};
                    temp = temp->left;
                    break;
                }
                temp = temp->left;
            }
            else if (temp->data < key) {
                if (!temp->right) {
                    temp->right = new Node {key, nullptr,
                                            nullptr, temp};
                    temp = temp->right;
                    break;
                }
                temp = temp->right;
            }
            else
                return;
        }
        m_root = detail::splay<T>(temp);
    }

    template <typename T>
    void SplayTree<T>::erase (const T& key) {
        auto found = detail::find(m_root, key);
        auto splayed = detail::splay<T>(found);
        if (!splayed) {
            return;
        }
        auto lhs_tree = splayed->left;
        auto rhs_tree = splayed->right;
        if (lhs_tree) {
            lhs_tree->parent = nullptr;
        }
        if (rhs_tree) {
            rhs_tree->parent = nullptr;
        }
        delete splayed;
        m_root = detail::merge<T>(lhs_tree, rhs_tree);
    }

    template <typename T>
    SplayTree<T>::~SplayTree () {
        detail::deleteTree(m_root);
    }

    template <typename T>
    SplayTree<T>::SplayTree (std::initializer_list<T> elems)
            : m_root(nullptr) {
        for (const auto& elem : elems) {
            insert(elem);
        }
    }

    template <typename T>
    template <typename Iter>
    SplayTree<T>::SplayTree (Iter begin, Iter end)
            : m_root(nullptr) {
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    template <typename T>
    SplayTree<T>::SplayTree (const SplayTree& other)
            : m_root(nullptr)
    {
        for (const auto& elem : other) {
            insert(elem);
        }
    }

    template <typename T>
    SplayTree<T>& SplayTree<T>::operator= (SplayTree other) noexcept {
        std::swap(*this, other);
        return *this;
    }
}