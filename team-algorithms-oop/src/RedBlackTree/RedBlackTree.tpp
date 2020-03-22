#pragma once

#include "InsertionFixRBTree.hpp"
#include "DeletionFixRBTree.hpp"

namespace lab::tree {

    template <typename T, typename Compare>
    template <typename Iter>
    RedBlackTree<T, Compare>::RedBlackTree (Iter begin, Iter end)
    {
        _root = nullptr;
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    template <typename T, typename Compare>
    RedBlackTree<T, Compare>::RedBlackTree (std::initializer_list<T> elems) {
        for (const auto& elem : elems) {
            insert(elem);
        }
    }

    template <typename T, typename Compare>
    void RedBlackTree<T, Compare>::insert(const T& _data) {

        auto inputNode = new Node<RedBlackTree<T, Compare>>{_data};
        Base::simpleInsert(inputNode);

        rbutils::InsertionFixRBTree(_root, inputNode);
        _size++;
    }

    template <typename T, typename Compare>
    void RedBlackTree<T, Compare>::erase(const T& _data) {
        if (_root == nullptr) {
            return;
        }
        Node<RedBlackTree<T, Compare>>* nodeToDelete = bstutils::find(_root,  _data, _comp);

        if (nodeToDelete == nullptr) {
            return;
        }

        if (nodeToDelete == _root && nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
            _root = nullptr;
        } else {
            rbutils::DeletionFixRBTRee(_root, nodeToDelete);
        }
        _size--;
    }

    template <typename T, typename Compare>
    RedBlackTree<T, Compare>::RedBlackTree (const Compare& comp)
        : Base(comp)
    {}
}