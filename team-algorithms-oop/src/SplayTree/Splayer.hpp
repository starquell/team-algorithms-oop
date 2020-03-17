#pragma once

#include <NodeUtilities.hpp>

#include <algorithm>
#include <utility>
#include <cassert>

/**
 *  @brief Set of functions and classes that implement algorithms for Splay Tree
 */
namespace tree::utils {

    /**
     *  @brief Implementation of splay algorithm for Splay Tree
     */
    template <typename T>
    class Splayer {
    public:
        explicit Splayer(Node<SplayTree<T>>* node) noexcept
                : m_node(node)
        {}

        auto splay() noexcept -> Node<SplayTree<T>>*
        {
            if (!m_node) {
                return nullptr;
            }
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
            if (isLeftSon(m_node)) {
                rightRotate(m_node);
            }
            else if (isRightSon(m_node)) {
                leftRotate(m_node);
            }
            m_node->parent = nullptr;
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

            if (isLeftSon(m_node) && isLeftSon(m_node->parent)) {
                rightRotate(m_node->parent);
                rightRotate(m_node);
            }

            else if (isRightSon(m_node) && isRightSon(m_node->parent)) {
               leftRotate(m_node->parent);
               leftRotate(m_node);
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
        Node<SplayTree<T>>* m_node;
    };

    template <typename T>
    inline auto splay (Node<SplayTree<T>>* node) noexcept -> Node<SplayTree<T>>*
    {
        return Splayer{node}.splay();
    }

    template <typename T>
    auto merge (Node<SplayTree<T>>* lhs, Node<SplayTree<T>>* rhs) noexcept {
        if (!lhs) {
            return rhs;
        }
        if (!rhs) {
            return lhs;
        }
        auto max_in_lhs = utils::max(lhs);
        assert (max_in_lhs->data < utils::min(rhs)->data);
        auto lhs_root = splay(max_in_lhs);
        lhs_root->right = rhs;
        lhs_root->right->parent = lhs_root;
        return lhs_root;
    }

    template <typename T>
    auto split (Node<SplayTree<T>>* tree, const T& elem) noexcept
                -> std::pair <Node<SplayTree<T>>*, Node<SplayTree<T>>*>
    {
        std::vector<Node<SplayTree<T>>*> elems;
        utils::makeOrderedSequence(tree, elems);

        T upper_bound = std::upper_bound(elems.begin(), elems.back(), elem,
                                        [] (const auto& key, const auto elem) {
                                            return key < *elem;
        });

        auto upper_bound_node = utils::find(tree, elem);
        auto new_tree = splay(upper_bound_node);
        auto leftTree = new_tree->left;
        leftTree->parent = nullptr;
        new_tree->left = nullptr;
        return std::pair(leftTree, new_tree);
    }
}
