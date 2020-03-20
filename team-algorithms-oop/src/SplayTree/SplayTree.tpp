#pragma once

#include <SplayTree/Splayer.hpp>

namespace lab::tree {

    template <typename T, typename Compare>
    void SplayTree<T, Compare>::insert (const T& key) {
        auto new_node = new Node<SplayTree<T>> {key};
        Base::simpleInsert(new_node);
        _root = bstutils::splay(new_node);
        ++_size;
    }

    template <typename T, typename Compare>
    void SplayTree<T, Compare>::erase (const T& key) {
        auto found = bstutils::find(_root, key, _comp);
        auto splayed = bstutils::splay(found);
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
        _root = bstutils::merge<T>(lhs_tree, rhs_tree);
        --_size;
    }

    template <typename T, typename Compare>
    template <typename Iter>
    SplayTree<T, Compare>::SplayTree (Iter begin, Iter end)
    {
        _root = nullptr;
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    template <typename T, typename Compare>
    SplayTree<T, Compare>::SplayTree (std::initializer_list<T> elems)
    {
        _root = nullptr;
        for (const auto& elem : elems) {
            insert(elem);
        }
    }

    template <typename T, typename Compare>
    SplayTree<T, Compare>::SplayTree (const Compare& comp) noexcept
        : Base(comp)
    {}
}