#pragma once

#include <SplayTree/Splayer.hpp>
#include "NodeBase.hpp"

namespace lab::forest {

    namespace detail {

        template <typename T, typename Compare>
        struct Node<SplayTree<T, Compare>> {
            T data;
            lab::forest::detail::Node<SplayTree<T, Compare>>* left = nullptr;
            lab::forest::detail::Node<SplayTree<T, Compare>>* right = nullptr;
            lab::forest::detail::Node<SplayTree<T, Compare>>* parent = nullptr;
        };
    }

    template <typename T, typename Compare>
    void SplayTree<T, Compare>::insertImpl (const T& key) {
        auto new_node = new detail::Node<SplayTree<T, Compare>> {key};
        if (Base::simpleInsert(new_node)) {
            _root = detail::splay(new_node);
            ++_size;
        }
        else {
            delete new_node;
        }
    }

    template <typename T, typename Compare>
    void SplayTree<T, Compare>::eraseImpl (const T& key) {
        auto found = detail::find(_root, key, _comp);
        auto splayed = detail::splay(found);
        if (!splayed) {
            return;
        }
        auto lhs_tree = splayed->left;
        auto rhs_tree = splayed->right;
        if (lhs_tree) {
            lhs_tree->parent = nullptr;
            splayed->left = nullptr;
        }
        if (rhs_tree) {
            rhs_tree->parent = nullptr;
            splayed->right = nullptr;
        }
        delete splayed;
        _root = detail::merge<T>(lhs_tree, rhs_tree);
        --_size;
    }

    template <typename T, typename Compare>
    template <typename Iter>
    SplayTree<T, Compare>::SplayTree (Iter begin, Iter end)
    {
        for (; begin != end; ++begin) {
            this->insert(*begin);
        }
    }

    template <typename T, typename Compare>
    SplayTree<T, Compare>::SplayTree (std::initializer_list<T> elems)
    {
        for (const auto& elem : elems) {
            this->insert(elem);
        }
    }

    template <typename T, typename Compare>
    SplayTree<T, Compare>::SplayTree (const Compare& comp) noexcept
        : Base(comp)
    {}
}