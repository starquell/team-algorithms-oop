#pragma once

#include <algorithm>
#include <utility>
#include <cassert>

namespace lab::detail {

    template <typename T>
    class Splayer {
    public:
        explicit Splayer(typename SplayTree<T>::Node* node) noexcept
                : m_node(node)
        {}

        auto splay() noexcept -> typename SplayTree<T>::Node*
        {
            while (m_node->parent) {
                if ((isRightSon(m_node) && isLeftSon(m_node->parent)) ||
                    (isLeftSon(m_node) && isRightSon(m_node->parent))) {
                    zigzag();
                }
                else if ((isLeftSon(m_node) && isLeftSon(m_node->parent)) ||
                         (isRightSon(m_node) && isRightSon(m_node->parent))) {
                    zigzig();
                }
                else {
                    zig();
                    return m_node;
                }
            }
            return m_node;
        }

    private:
        void zig() noexcept {
            auto& parent = m_node->parent;
            if (isLeftSon(m_node)) {
                set(parent->left, m_node->right, parent);
                set(m_node->right, parent, m_node);
            }
            else if (isRightSon(m_node)) {
                set(parent->right, m_node->left, parent);
                set(m_node->left, parent, m_node);
            }
            parent = nullptr;
        }
        void zigzig() noexcept {
            auto mostParent = m_node->parent->parent->parent;
            auto grandparent = m_node->parent->parent;
            if (isLeftSon(grandparent)) {
                mostParent->left = m_node;
            }
            else if (isRightSon(grandparent)){
                mostParent->right = m_node;
            }
            auto parent = m_node->parent;

            if (isLeftSon(m_node) && isLeftSon(parent)) {
                set(grandparent->left, parent->right, grandparent);
                set(parent->right, grandparent, parent);
                set(parent->left, m_node->right, parent);
                set(m_node->right, parent, m_node);
            }

            else if (isRightSon(m_node) && isRightSon(parent)) {
                set(grandparent->right, parent->left, grandparent);
                set(parent->left, grandparent, parent);
                set(parent->right, m_node->left, parent);
                set(m_node->left, parent, m_node);
            }
            m_node->parent = mostParent;
        }
        void zigzag() noexcept {
            auto mostParent = m_node->parent->parent->parent;
            auto grandparent = m_node->parent->parent;
            if (isLeftSon(grandparent)) {
                mostParent->left = m_node;
            }
            else if (isRightSon(grandparent)){
                mostParent->right = m_node;
            }
            auto parent = m_node->parent;

            if (isRightSon(m_node) && isLeftSon(parent)) {
                set(grandparent->left, m_node->right, grandparent);
                set(parent->right, m_node->left, parent);

                set(m_node->left, parent, m_node);
                set(m_node->right, grandparent, m_node);
            }
            else if (isLeftSon(m_node) && isRightSon(parent)){
                set(grandparent->right, m_node->left, grandparent);
                set(parent->left, m_node->right, parent);

                set(m_node->right, parent, m_node);
                set(m_node->left, grandparent, m_node);
            }
            m_node->parent = mostParent;
        }

    private:
        typename SplayTree<T>::Node* m_node;
    };

    template <typename T>
    inline auto splay (typename SplayTree<T>::Node* node) noexcept -> typename SplayTree<T>::Node*
    {
        return Splayer<T>{node}.splay();
    }

    template <typename T>
    auto merge (typename SplayTree<T>::Node* lhs, typename SplayTree<T>::Node* rhs) noexcept {
        if (!lhs) {
            return rhs;
        }
        if (!rhs) {
            return lhs;
        }
        assert(max(lhs)->data < min(rhs)->data);
        auto lhs_root = splay(max(lhs));
        lhs_root->right = rhs;
        lhs_root->right->parent = lhs_root;
        return lhs_root;
    }

    template <typename T>
    auto split (typename SplayTree<T>::Node* tree, const T& elem) noexcept
                -> std::pair<typename SplayTree<T>::Node* ,typename SplayTree<T>::Node*>
    {
        auto begin = SplayTree<T>::Iterator(min(tree));
        auto end = SplayTree<T>::Iterator(nullptr);

        T upper_bound = std::upper_bound(begin, end, elem);
        auto upper_bound_node = find(tree, elem);
        auto new_tree = splay(upper_bound_node);
        auto leftTree = new_tree->left;
        leftTree->parent = nullptr;
        new_tree->left = nullptr;
        return std::pair(leftTree, new_tree);
    }

}
